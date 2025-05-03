import os, subprocess, copy
import logger_utils
import sparcle_utils
import cpp_operator
import codegen_context
import reflection_utils

try:
    import clang.cindex
except ImportError:
    print("Please install 'clang' package!")
except Exception:
    print('Failed to import clang.cindex! Please install "clang" package!')


def has_default_constructor(cls):
    """Проверяет, можно ли создать объект без аргументов"""
    has_explicit_ctor = False
    has_default_ctor = False

    for c in cls.get_children():
        if c.kind == clang.cindex.CursorKind.CONSTRUCTOR:
            has_explicit_ctor = True
            if len(list(c.get_arguments())) == 0:
                has_default_ctor = True

    # Если нет конструкторов - значит компилятор создаст дефолтный
    if not has_explicit_ctor:
        return True
    return has_default_ctor


def is_deleted(c):
    """Проверяет, является ли конструктор `= delete`"""
    for token in c.get_tokens():
        if token.spelling == "delete":
            return True
    return False


def has_copy_constructor(cls):
    """Проверяет, есть ли конструктор копирования"""
    has_explicit_copy_ctor = False
    has_deleted_copy_ctor = False
    has_other_ctors = False

    for c in cls.get_children():
        if c.kind == clang.cindex.CursorKind.CONSTRUCTOR:
            params = list(c.get_arguments())
            if len(params) == 1:
                param_type = params[0].type.spelling

                # Проверяем, что аргумент имеет тип `ClassName &` или `const ClassName &`
                if param_type == f"{c.spelling} &" or param_type == f"const {c.spelling} &":
                    if is_deleted(c):
                        has_deleted_copy_ctor = True  # Конструктор копирования удалён
                    else:
                        has_explicit_copy_ctor = True
                else:
                    has_other_ctors = True
            else:
                has_other_ctors = True

    # Если есть явно запрещённый конструктор -> NO
    if has_deleted_copy_ctor:
        return False

    # Если есть явно объявленный -> YES
    if has_explicit_copy_ctor:
        return True

    # Если нет других конструкторов -> компилятор его создаст
    return not has_other_ctors


def get_engine_include_args(context: codegen_context.CodegenContext):
    engine_root = ''
    if context.is_script:
        engine_root = context.help_sources_dir
    else:
        engine_root = context.analyze_dir + '/Engine'

    includes = [
        f'{engine_root}/Core/inc',
        f'{engine_root}/Core/libs',
        f'{engine_root}/Core/libs/Utils/inc',
        f'{engine_root}/Core/libs/Scripting/inc',
        f'{engine_root}/Core/libs/Audio/inc',
        f'{engine_root}/Core/libs/Physics/inc',
        f'{engine_root}/Core/libs/Graphics/inc',
    ]

    if not context.is_script:
        includes.append(f'{engine_root}/Core/libs/Audio/libs')
        includes.append(f'{engine_root}/Core/libs/Audio/libs/libmodplug/src')
        includes.append(f'{engine_root}/Core/libs/Graphics/libs/EvoVulkan/Core/inc')
        includes.append(f'{engine_root}/Core/libs/Graphics/libs')
        includes.append(f'{engine_root}/Core/libs/Graphics/libs/imgui')
        includes.append(f'{engine_root}/Core/libs/Physics/libs')
        includes.append(f'{engine_root}/Core/libs/Utils/libs')
        includes.append(f'{engine_root}/Core/libs/Utils/libs/openssl/include')
        includes.append(f'{engine_root}/Core/libs/Utils/libs/litehtml/include')
        includes.append(f'{engine_root}/Core/libs/Utils/libs/cppcoro/include')
        includes.append(f'{engine_root}/Core/libs/Utils/libs/assimp/include')
        includes.append(f'{engine_root}/Core/libs/Utils/libs/fmt/include')
        includes.append(f'{engine_root}/Core/libs/Scripting/libs')

        includes.append(f'{context.build_dir}/Engine/Core/libs/Utils/libs/assimp/include')
        includes.append(f'{context.build_dir}')

    include_args = [f'-I{ os.path.abspath(sparcle_utils.normalize_path(inc))}' for inc in includes]
    return include_args


def preprocess_cpp(source, output, include_args):
    command = f"clang++ -E {source} -o {output} -fpermissive {' '.join(include_args)} -D WIN32"

    # Запускаем команду
    result = subprocess.run(command, shell=True, capture_output=True, text=True)

    # Проверяем наличие ошибок
    if result.returncode != 0:
        raise Exception(f'Failed to preprocess file: {source}, error: {result.stderr}, command: {command}')


def is_property_comment(node):
    """Извлекаем комментарий, если он есть."""
    raw_comment = node.raw_comment
    if raw_comment and "@property" in raw_comment:
        return True
    return False


def has_special_tag_comment(node, tag):
    """Извлекаем комментарий, если он есть."""
    raw_comment = node.raw_comment
    if raw_comment and f"@{tag}" in raw_comment:
        return True
    return False


def extract_special_tag_comment_data(node, tag):
    """ /// @someTage(data, data, data), get data between ( and ) """
    """ /// @resetValue(someFunc()), get someFunc() """
    raw_comment = node.raw_comment
    if not raw_comment:
        return None
    start = raw_comment.find(f"@{tag}(")
    if start == -1:
        return None

    start = raw_comment.find('(', start)
    if start == -1:
        return None

    deep = 0
    end = -1

    for i in range(start, len(raw_comment)):
        if raw_comment[i] == '(':
            deep += 1
        if raw_comment[i] == ')':
            deep -= 1
            if deep == 0:
                end = i
                break

    if end == -1:
        return None

    return raw_comment[start + 1:end]


def extract_all_special_tags_comment_data(node, tag):
    """ @customArgs(name1: value1) """
    """ @customArgs(name2: value2, name3: value3) """
    """ @customArg(name4: value4) """

    tags = []
    raw_comment = node.raw_comment
    if not raw_comment:
        return tags

    index = 0
    loop_limit = 100
    while True:
        index = raw_comment.find(f"@{tag}(", index)
        start = raw_comment.find('(', index)
        end = raw_comment.find(')', start)
        if index == -1 or start == -1 or end == -1:
            break
        tags.append(raw_comment[start + 1:end])
        index = end
        loop_limit -= 1
        if loop_limit == 0:
            raise Exception(f'Loop limit reached for {tag} in {node.spelling}, raw_comment: {raw_comment}, tags: {tags}')

    return tags


def is_method_comment(node):
    """Извлекаем комментарий, если он есть."""
    raw_comment = node.raw_comment
    if raw_comment and "@method" in raw_comment:
        return True
    return False


def extract_property_type(variable_node):
    if variable_node.type.spelling:
        return variable_node.type.spelling
    return 'Unknown'


def debug_extract_property_default_value(cursor, deep=0):
    tokens = list(cursor.get_tokens())
    token_strs = [token.spelling for token in tokens]

    print(f'[{deep}][Debug] Extract default value for {cursor.kind} \"{cursor.spelling}\" \"{cursor.type.spelling}\", {token_strs}')

    for child in cursor.get_children():
        debug_extract_property_default_value(child, deep + 1)


def extract_property_default_value(cursor):
    debug_extract_property_default_value(cursor)

    if cursor.kind != clang.cindex.CursorKind.FIELD_DECL:
        return None

    namespace_stack = []
    tokens = list(cursor.get_tokens())
    token_strs = [token.spelling for token in tokens]

    print(f'Extract default value for {cursor.spelling}, {token_strs}')

    for child in cursor.get_children():
        tokens = list(child.get_tokens())
        if child.kind == clang.cindex.CursorKind.CXX_BOOL_LITERAL_EXPR:
            return tokens[0].spelling
        if child.kind == clang.cindex.CursorKind.INTEGER_LITERAL:
            return tokens[0].spelling
        if child.kind == clang.cindex.CursorKind.FLOATING_LITERAL:
            return tokens[0].spelling
        if child.kind == clang.cindex.CursorKind.STRING_LITERAL:
            return tokens[0].spelling
        if child.kind == clang.cindex.CursorKind.CHARACTER_LITERAL:
            return tokens[0].spelling
        if child.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR or child.kind == clang.cindex.CursorKind.DECL_REF_EXPR:
            expression = ''
            for token in tokens:
                expression += token.spelling
            return expression
        if child.kind == clang.cindex.CursorKind.NAMESPACE_REF:
            namespace_stack.append(child.spelling)
            continue
        #if child.kind == clang.cindex.CursorKind.TYPE_REF:
        #    namespace_stack.append(child.spelling)
        #    continue
        if child.kind == clang.cindex.CursorKind.CALL_EXPR:
            if len(token_strs) == 0:
                namespace = '::'.join(namespace_stack)
                #print(f'Extract default value for {child.kind} \"{child.spelling}\" \"{child.type.spelling}\", {token_strs}')
                if len(namespace):
                    return f'{namespace}::{child.type.spelling}::{child.spelling}()'
                return f'{child.type.spelling}::{child.spelling}()'
            else:
                expression = ''
                for token in tokens:
                    expression += token.spelling
                return expression

    print(f'Default value not found for {cursor.spelling}')
    return None


def has_static_function(class_node, function_name):
    """Проверяет наличие статической функции в классе."""
    for node in class_node.get_children():
        # Проверяем, является ли узел функцией
        if node.kind == clang.cindex.CursorKind.CXX_METHOD:
            # Проверяем, является ли функция статической и соответствует ли имя
            if node.spelling == function_name:
                return True
    return False


def is_class_inherited_from(class_node, class_name):
    """Проверяет, наследуется ли класс от другого класса."""
    for node in class_node.get_children():
        # Проверяем, является ли узел базовым классом
        if node.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
            # Проверяем, является ли имя базового класса искомым
            if node.spelling == class_name:
                return True
    return False


def process_property(property_obj: reflection_utils.CPPProperty, clang_child):
    property_obj.change_callback = extract_special_tag_comment_data(clang_child, 'onChanged')
    property_obj.setter = extract_special_tag_comment_data(clang_child, 'setter')
    property_obj.getter = extract_special_tag_comment_data(clang_child, 'getter')
    property_obj.reset_value = extract_special_tag_comment_data(clang_child, 'resetValue')
    property_obj.default_value = extract_special_tag_comment_data(clang_child, 'defaultValue')
    property_obj.property_condition = extract_special_tag_comment_data(clang_child, 'propertyCondition')
    property_obj.load_condition = extract_special_tag_comment_data(clang_child, 'loadCondition')
    property_obj.drag_value = extract_special_tag_comment_data(clang_child, 'drag')
    property_obj.editor_width = extract_special_tag_comment_data(clang_child, 'editorWidth')
    property_obj.inspector = extract_special_tag_comment_data(clang_child, 'inspector')

    if custom_args_list := extract_all_special_tags_comment_data(clang_child, 'customArgs'):
        for custom_args in custom_args_list:
            custom_args_split = custom_args.split(',')
            for arg in custom_args_split:
                index = arg.find(':')
                if index == -1:
                    print(f'Error: invalid custom arg: {arg}')
                    continue
                property_obj.add_custom_arg(arg, index)

    if custom_arg_list := extract_all_special_tags_comment_data(clang_child, 'customArg'):
        for arg in custom_arg_list:
            index = arg.find(':')
            if index == -1:
                print(f'Error: invalid custom arg: {arg}')
                continue
            property_obj.add_custom_arg(arg, index)

    if property_obj.virtual and not property_obj.getter:
        raise Exception(f'Virtual property {property_obj.name} must have getter!')

    property_obj.not_null = has_special_tag_comment(clang_child, 'notNull')
    property_obj.hidden = has_special_tag_comment(clang_child, 'hidden')
    property_obj.read_only = has_special_tag_comment(clang_child, 'readOnly')
    property_obj.no_header = has_special_tag_comment(clang_child, 'noHeader')
    property_obj.private = has_special_tag_comment(clang_child, 'private')

    property_obj.dontLoad = has_special_tag_comment(clang_child, 'dontLoad')
    property_obj.dontSave = has_special_tag_comment(clang_child, 'dontSave')

    if property_obj.dontSave:
        property_obj.dontLoad = True

    # remove m_ and _ prefix from name
    property_obj.display_name = sparcle_utils.make_display_name(property_obj.name)
    property_obj.serialize_name = sparcle_utils.make_serialize_property_name(property_obj.name)

    if not property_obj.default_value:
        property_obj.default_value = extract_property_default_value(clang_child)
        if property_obj.default_value:
            print(f'Found default value: {property_obj.default_value}')


def parse_sparcle_enum(logger, parent_node, code_structure, namespaces):
    if parent_node.kind == clang.cindex.CursorKind.FUNCTION_DECL and parent_node.is_definition():
        if parent_node.spelling.startswith('CODEGEN_ENUM_DETAILS_FUNCTION_'):
            all_found = 0
            name = '(not found)'
            variant = '(not found)'
            enum_type = '(not found)'
            enum_class = '(not found)'
            va_args = '(not found)'
            count = 0

            for function_part in parent_node.get_children():
                if function_part.kind == clang.cindex.CursorKind.COMPOUND_STMT:
                    for function_body in function_part.get_children():
                        if function_body.kind ==  clang.cindex.CursorKind.DECL_STMT:
                            for child in function_body.get_children():
                                variable_name = child.spelling
                                if variable_name == 'CODEGEN_ENUM_VARIANT':
                                    for child2 in child.get_children():
                                        if child2.kind == clang.cindex.CursorKind.DECL_REF_EXPR:
                                            variant = child2.spelling
                                            all_found += 1
                                    break
                                if variable_name == 'CODEGEN_ENUM_COUNT':
                                    for child2 in child.get_children():
                                        if child2.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                                            for child3 in child2.get_children():
                                                if child3.kind == clang.cindex.CursorKind.INTEGER_LITERAL:
                                                    tokens = list(child2.get_tokens())
                                                    count = int(tokens[0].spelling)
                                                    all_found += 1
                                                    break
                                            break
                                    break
                                if variable_name == 'CODEGEN_ENUM_NAME':
                                    # extract const char* value
                                    for child2 in child.get_children():
                                        if child2.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                                            for child3 in child2.get_children():
                                                if child3.kind == clang.cindex.CursorKind.STRING_LITERAL:
                                                    name = child3.spelling[1:-1]
                                                    all_found += 1
                                                    break
                                        break
                                    break
                                if variable_name == 'CODEGEN_ENUM_TYPE':
                                    for child2 in child.get_children():
                                        if child2.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                                            for child3 in child2.get_children():
                                                if child3.kind == clang.cindex.CursorKind.STRING_LITERAL:
                                                    enum_type = child3.spelling[1:-1]
                                                    all_found += 1
                                                    break
                                        break
                                    break
                                if variable_name == 'CODEGEN_ENUM_VA_ARGS':
                                    for child2 in child.get_children():
                                        if child2.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                                            for child3 in child2.get_children():
                                                if child3.kind == clang.cindex.CursorKind.STRING_LITERAL:
                                                    va_args = child3.spelling[2:-2]
                                                    all_found += 1
                                                    break
                                        break
                                    break
                                if variable_name == 'CODEGEN_ENUM_CLASS':
                                    for child2 in child.get_children():
                                        if child2.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                                            for child3 in child2.get_children():
                                                if child3.kind == clang.cindex.CursorKind.STRING_LITERAL:
                                                    enum_class = child3.spelling[1:-1]
                                                    all_found += 1
                                                    break
                                        break
                                    break

                if all_found == 6:
                    print(f'Found enum: {name} Variant: {variant} Count: {count}, Type: {enum_type}, Class: {enum_class}, VA_ARGS: {va_args}')
                    enum_object = reflection_utils.CPPEnum(name, variant, count, enum_type, enum_class, namespaces, parent_node.location.file.name, va_args)
                    code_structure.enums.append(enum_object)
                    break

        return


def parse_sparcle_class(logger, parent_node, code_structure, namespaces, is_help_source):
    is_class_or_struct = parent_node.kind == clang.cindex.CursorKind.CLASS_DECL or parent_node.kind == clang.cindex.CursorKind.STRUCT_DECL
    if is_class_or_struct and parent_node.is_definition():
        if not has_static_function(parent_node, 'GetMetaStatic'):
            return

        # Нашли класс
        class_name = parent_node.spelling
        class_obj = reflection_utils.SpaRcleClass(class_name, namespaces)
        class_obj.path = parent_node.location.file.name

        if is_help_source:
            class_obj.is_help_source = True
            code_structure.sparcle_classes.append(class_obj)
            return

        class_obj.inspector = extract_special_tag_comment_data(parent_node, 'inspector')

        # format @version(year.month.day) or @version(any number). convert @version(2025.12.31) to 20251231
        # additional example: @version(2025.02.04) -> 20250204
        class_obj.version = extract_special_tag_comment_data(parent_node, 'version')
        if class_obj.version:
            class_obj.version = class_obj.version.replace('.', '')

        # example: @category(Engine.Render.Something other.Something)
        class_obj.category = extract_special_tag_comment_data(parent_node, 'category')

        class_obj.hidden = has_special_tag_comment(parent_node, 'hidden')

        if class_obj.inspector:
            print(f'Found class inspector: {class_obj.inspector}')

        # Перебираем все поля класса
        for child in parent_node.get_children():
            #print(f'Fount class child: {child.spelling}, {child.kind}')

            if child.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                class_obj.inherited_classes.append(child.spelling)
                continue

            if child.kind == clang.cindex.CursorKind.TYPEDEF_DECL:
                virtual_property = extract_special_tag_comment_data(child, 'virtualProperty')
                if virtual_property:
                    print(f'Found virtual property: {virtual_property}')
                    property_obj = reflection_utils.CPPProperty(virtual_property, 'Unknown')
                    property_obj.virtual = True
                    process_property(property_obj, child)
                    class_obj.add_variable(property_obj)

            elif child.kind == clang.cindex.CursorKind.FIELD_DECL and is_property_comment(child):
                variable_name = child.spelling
                variable_type = extract_property_type(child)
                property_obj = reflection_utils.CPPProperty(variable_name, variable_type)
                print(f'Found property: {property_obj.name}, Type: {property_obj.type_name}')
                process_property(property_obj, child)
                class_obj.add_variable(property_obj)

            #elif child.kind == clang.cindex.CursorKind.CXX_METHOD and is_method_comment(child):
            #    method_name = child.spelling
            #    method_return_type = child.result_type.spelling
            #    method_obj = reflection_utils.CPPMethod(method_name, method_return_type)
            #    for param in child.get_children():
            #        if param.kind == clang.cindex.CursorKind.PARM_DECL:
            #            param_name = param.spelling
            #            param_type = param.type.spelling
            #            method_obj.add_parameter(reflection_utils.CPPProperty(param_name, param_type))
            #
            #    class_obj.add_method(method_obj)

        code_structure.sparcle_classes.append(class_obj)


def parse_scriptable_class(logger: logger_utils.Logger, parent_node, code_structure, namespaces):
    is_class_or_struct = parent_node.kind == clang.cindex.CursorKind.CLASS_DECL or parent_node.kind == clang.cindex.CursorKind.STRUCT_DECL
    is_template_class_or_struct = parent_node.kind == clang.cindex.CursorKind.CLASS_TEMPLATE or parent_node.kind == clang.cindex.CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION

    if (is_class_or_struct or is_template_class_or_struct) and parent_node.is_definition():
        is_scriptable_class = has_special_tag_comment(parent_node, 'scriptableClass')
        if not is_scriptable_class:
            return

        class_name = '::'.join(namespaces) + f'::{parent_node.spelling}'
        logger.log_debug(f'Found scriptable class: {class_name}')
        class_obj = reflection_utils.ScriptableClass(parent_node.spelling, namespaces)
        class_obj.path = parent_node.location.file.name
        class_obj.has_default_constructor = has_default_constructor(parent_node)
        class_obj.has_copy_constructor = has_copy_constructor(parent_node)

        template_variants = []

        if is_template_class_or_struct:
            '''
            Example:
            /// @templateImpl(FVector3, T = float_t)
            /// @templateImpl(IVector3, T = int32_t)
            /// @templateImpl(UVector3, T = uint32_t)
            /// @templateImpl(BVector3, T = bool)
            '''
            template_impls = extract_all_special_tags_comment_data(parent_node, 'templateImpl')
            if not template_impls:
                logger.log_fatal_error(f'Error: template class {class_name} has no templateImpl!')
            for template_impl in template_impls:
                logger.log_debug(f'Found scriptable class template implementation: {template_impl}')
                args = template_impl.split(',')

                code_structure.add_class_name_correction(args[0].strip(), '::'.join(namespaces) + f'::{args[0].strip()}')

                template_replacements = []
                for arg in args[1:]:
                    template_typename = arg.split('=')[0].strip()
                    template_type = arg.split('=')[1].strip()
                    template_replacements.append((template_typename, template_type))
                    logger.log_debug(f'Found scriptable class template argument: {template_typename}, Type: {template_type}')
                template_variants.append((args[0].strip(), template_replacements))
        else:
            code_structure.add_class_name_correction(parent_node.spelling, class_name)


        for child in parent_node.get_children():
            # find all constructors with special tag @constructor
            if child.kind == clang.cindex.CursorKind.CONSTRUCTOR:
                if has_special_tag_comment(child, 'constructor'):
                    logger.log_debug(f'Found scriptable constructor: {child.spelling}')
                    constructor = reflection_utils.CPPConstructor()

                    # find all parameters
                    for param in child.get_children():
                        if param.kind == clang.cindex.CursorKind.PARM_DECL:
                            param_name = param.spelling
                            param_type = param.type.spelling
                            logger.log_debug(f'Found scriptable constructor parameter: {param_name}, Type: {param_type}')
                            constructor.add_parameter(reflection_utils.CPPParameter(param_name, param_type))

                    class_obj.add_constructor(constructor)

            # find all operators with special tag @operator
            elif child.kind == clang.cindex.CursorKind.CXX_METHOD and child.spelling.startswith('operator'):
                if has_special_tag_comment(child, 'operator'):
                    logger.log_debug(f'Found scriptable operator: {child.spelling}, return type {child.result_type.spelling}')
                    operator = reflection_utils.CPPOperator(cpp_operator.OperatorType.from_string(child.spelling), child.result_type.spelling)
                    operator.is_const = child.is_const_method()

                    # find all parameters
                    for param in child.get_children():
                        if param.kind == clang.cindex.CursorKind.PARM_DECL:
                            logger.log_debug(f'Found scriptable operator parameter: {param.spelling}, Type: {param.type.spelling}')
                            operator.add_parameter(reflection_utils.CPPParameter(param.spelling, param.type.spelling))

                    class_obj.add_operator(operator)

            # find all method with special tag @method
            elif child.kind == clang.cindex.CursorKind.CXX_METHOD:
                if has_special_tag_comment(child, 'method'):
                    logger.log_debug(f'Found scriptable method: {child.spelling}, return type {child.result_type.spelling}')
                    method = reflection_utils.CPPMethod(child.spelling, child.result_type.spelling)
                    method.is_const = child.is_const_method()

                    # find all parameters
                    for param in child.get_children():
                        if param.kind == clang.cindex.CursorKind.PARM_DECL:
                            logger.log_debug(f'Found scriptable method parameter: {param.spelling}, Type: {param.type.spelling}')
                            method.add_parameter(reflection_utils.CPPParameter(param.spelling, param.type.spelling))

                    class_obj.add_method(method)

        if len(template_variants) > 0:
            for template_variant in template_variants:
                class_obj_template = copy.deepcopy(class_obj)
                class_obj_template.alias = template_variant[0]

                full_template_name = f'{parent_node.spelling}<' + f', '.join([template_replacement[0] for template_replacement in template_variant[1]]) + '>'

                for template_replacement in template_variant[1]:
                    full_template_name = sparcle_utils.replace_type_templated_name(full_template_name, template_replacement[0], template_replacement[1])
                    class_obj_template.replace_type(template_replacement[0], template_replacement[1])
                code_structure.add_scriptable_class(class_obj_template)

                code_structure.add_class_name_correction(full_template_name, '::'.join(namespaces) + f'::{class_obj_template.alias}')
        else:
            code_structure.add_scriptable_class(class_obj)


def parse_header_tree(logger, file_path, deep, parent_node, code_structure, namespaces, context: codegen_context.CodegenContext):
    is_help_source = False
    if context.help_sources_dir != '' and parent_node.location.file:
        is_help_source = context.help_sources_dir in parent_node.location.file.name.replace("\\", "/")

    try:
        if not is_help_source:
            parse_sparcle_enum(logger, parent_node, code_structure, namespaces)
        parse_sparcle_class(logger, parent_node, code_structure, namespaces, is_help_source)
        #parse_scriptable_class(logger, parent_node, code_structure, namespaces)

        new_namespace = namespaces
        # Проверяем, является ли текущий узел пространством имен
        if parent_node.kind == clang.cindex.CursorKind.NAMESPACE:
            if not parent_node.spelling == 'std':
                new_namespace = namespaces + [parent_node.spelling]

        # Рекурсивный обход других узлов
        for child in parent_node.get_children():
            parse_header_tree(logger, file_path, deep + 1, child, code_structure, new_namespace, context)

    except Exception as e:
        if str(e).startswith('Unknown template argument kind'):
            return
        logger.log_fatal_error(f'Error parse_tree: {e}')


def parse_header_file(logger: logger_utils.Logger, file_path, include_args, context: codegen_context.CodegenContext):
    code_structure = reflection_utils.CPPCodeStructure()

    # Передаем каждый путь как отдельный аргумент
    args = include_args
    args += ['-fsyntax-only', '-x', 'c++', '-std=c++20']

    index = clang.cindex.Index.create()
    translation_unit = index.parse(file_path, args=args)

    #print('check diagnostics...')
    #if translation_unit.diagnostics:
    #    for diagnostic in translation_unit.diagnostics:
    #        if 'warning: ' in str(diagnostic):
    #            continue
    #        print(diagnostic)

    # Проходим по узлам файла
    for node in translation_unit.cursor.get_children():
        parse_header_tree(logger, file_path, 0, node, code_structure, [], context)

    return code_structure

