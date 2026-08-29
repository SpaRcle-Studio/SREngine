import os, subprocess, copy

import reflection_utils
import logger_utils
import sparcle_utils
import cpp_operator
import codegen_context
import pickle
import re

from pathlib import Path
from time import perf_counter

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


def preprocess_cpp(source, output, include_args):
    command = f"clang++ -E {source} -o {output} -fpermissive {' '.join(include_args)} -D WIN32"

    # Запускаем команду
    result = subprocess.run(command, shell=True, capture_output=True, text=True)

    # Проверяем наличие ошибок
    if result.returncode != 0:
        raise Exception(f'Failed to preprocess file: {source}, error: {result.stderr}, command: {command}')


def has_special_tag_comment(node, tag):
    """Извлекаем комментарий, если он есть."""
    raw_comment = node.raw_comment
    if not raw_comment:
        return False

    pattern = rf'(?<!\w)@{re.escape(tag)}(?!\w)'
    return re.search(pattern, raw_comment) is not None


def is_property_comment(node):
    return has_special_tag_comment(node, 'property')


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

    #print(f'[{deep}][Debug] Extract default value for {cursor.kind} \"{cursor.spelling}\" \"{cursor.type.spelling}\", {token_strs}')

    for child in cursor.get_children():
        debug_extract_property_default_value(child, deep + 1)


def _extract_default_value_from_source(cursor):
    """
    Fallback: read the raw source line(s) for a FIELD_DECL and extract the initializer
    after '='. Handles cases where libclang drops the CALL_EXPR node for template typedef
    fields (e.g. FVector3, FVector2) when macro expansions are involved.

    Note: cursor.extent may NOT include the initializer for template typedef fields —
    it ends right after the field name. So we read from extent.start.line to the first ';'
    that ends the declaration.
    """
    try:
        loc = cursor.location
        if not loc.file:
            return None
        src_path = loc.file.name

        with open(src_path, 'r', encoding='utf-8', errors='replace') as f:
            lines = f.readlines()

        # Start from the line where the field is declared
        start_line = cursor.extent.start.line - 1  # 0-based

        # Collect text from start_line onward until we hit a ';'
        # (handles rare multi-line cases, but stops at next ';')
        field_text = ''
        for i in range(start_line, min(start_line + 5, len(lines))):
            field_text += lines[i]
            if ';' in lines[i]:
                break

        # Truncate at the first ';' to avoid spilling into the next declaration
        semi = field_text.find(';')
        if semi != -1:
            field_text = field_text[:semi]

        field_text = field_text.strip()

        # Find '=' that introduces the initializer (skip '==', '!=', '<=', '>=')
        eq_idx = -1
        for i, ch in enumerate(field_text):
            if ch == '=' and i > 0 \
                    and field_text[i - 1] not in ('!', '<', '>', '=') \
                    and (i + 1 >= len(field_text) or field_text[i + 1] != '='):
                eq_idx = i
                break
        if eq_idx == -1:
            return None

        initializer = field_text[eq_idx + 1:].strip()
        if not initializer:
            return None

        # Brace-list initializers like { 1024, 1024 } or { 1, 2, 3 } cannot be used
        # in a `return` statement without an explicit type, so skip them.
        if initializer.startswith('{'):
            return None

        return initializer

    except Exception:
        return None


def extract_property_default_value(cursor):
    #debug_extract_property_default_value(cursor)

    if cursor.kind != clang.cindex.CursorKind.FIELD_DECL:
        return None

    if cursor.kind != clang.cindex.CursorKind.FIELD_DECL:
        return None

    namespace_stack = []
    tokens = list(cursor.get_tokens())
    token_strs = [token.spelling for token in tokens]

    #print(f'Extract default value for {cursor.spelling}, {token_strs}')

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
            # Collect literal arguments directly from CALL_EXPR children.
            # We cannot rely on child.get_tokens() because libclang returns
            # macro-expanded context tokens that contain surrounding code noise.
            # Instead we walk the direct children of CALL_EXPR and pick literals.
            arg_literal_kinds = {
                clang.cindex.CursorKind.FLOATING_LITERAL,
                clang.cindex.CursorKind.INTEGER_LITERAL,
                clang.cindex.CursorKind.STRING_LITERAL,
                clang.cindex.CursorKind.CHARACTER_LITERAL,
                clang.cindex.CursorKind.CXX_BOOL_LITERAL_EXPR,
                clang.cindex.CursorKind.UNARY_OPERATOR,
            }
            call_args = []
            is_static_method_call = False  # e.g. Quaternion::Identity(), FVector3::Zero()
            static_method_owner = None     # fully-qualified owner class (e.g. SpaRcle::Utils::TagManager)
            for call_child in child.get_children():
                if call_child.kind in arg_literal_kinds:
                    arg_tokens = list(call_child.get_tokens())
                    if arg_tokens:
                        call_args.append(''.join(t.spelling for t in arg_tokens))
                elif call_child.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                    # Either wraps a literal (constructor arg) or a DECL_REF_EXPR (static method ref)
                    inner_children = list(call_child.get_children())
                    if inner_children and inner_children[0].kind == clang.cindex.CursorKind.DECL_REF_EXPR:
                        # DECL_REF_EXPR with a function type → static method reference, not an arg
                        decl_ref = inner_children[0]
                        if '()' in decl_ref.type.spelling or decl_ref.type.kind == clang.cindex.TypeKind.FUNCTIONPROTO:
                            is_static_method_call = True
                            # Find the owner class from TYPE_REF inside DECL_REF_EXPR
                            for decl_child in decl_ref.get_children():
                                if decl_child.kind == clang.cindex.CursorKind.TYPE_REF:
                                    static_method_owner = decl_child.type.get_canonical().spelling \
                                        or decl_child.type.spelling
                                    break
                            continue
                    # Otherwise it wraps a literal — unwrap one level
                    for inner in inner_children:
                        if inner.kind in arg_literal_kinds:
                            arg_tokens = list(inner.get_tokens())
                            if arg_tokens:
                                call_args.append(''.join(t.spelling for t in arg_tokens))
                            break

            # Use canonical type to get fully qualified name (e.g. SpaRcle::Utils::Math::Quaternion)
            # child.type.spelling may return a short name (e.g. 'Quaternion') when macros are involved
            canonical_type = child.type.get_canonical()
            type_name = canonical_type.spelling if canonical_type.spelling else child.type.spelling
            method_name = child.spelling     # e.g. 'FColor', 'Identity', 'Zero', 'GetDefaultTag'
            if call_args:
                # Constructor call with arguments: FColor(0.06f, 0.0f, 0.0f)
                return f'{type_name}({", ".join(call_args)})'
            elif is_static_method_call:
                # Static factory method: Quaternion::Identity(), TagManager::GetDefaultTag()
                # Use the owner class (where the method is declared), not the return type.
                owner = static_method_owner or type_name
                return f'{owner}::{method_name}()'
            else:
                # Default constructor: FColor()
                return f'{type_name}()'

    # AST-based extraction failed (e.g. libclang drops CALL_EXPR for template typedef fields
    # when macro expansions are involved). Fall back to reading the raw source text from the file.
    return _extract_default_value_from_source(cursor)


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


def fix_cpp_ctor_name(name: str) -> str:
    # Отделяем сигнатуру конструктора
    paren = name.find('(')
    if paren == -1:
        return name

    prefix = name[:paren]
    suffix = name[paren:]

    parts = prefix.split("::")

    # Ищем дублирование namespace.
    # Например:
    # A B C A B C D D
    #       ^

    n = len(parts)

    for start in range(1, n):
        if parts[:start] == parts[start:start * 2]:
            parts = parts[start:]
            break

    # Убираем FColor::FColor
    if len(parts) >= 2 and parts[-1] == parts[-2]:
        parts.pop()

    return "::".join(parts) + suffix


def process_property(property_obj: reflection_utils.CPPProperty, clang_child):
    property_obj.change_callback = extract_special_tag_comment_data(clang_child, 'onChanged')
    property_obj.setter = extract_special_tag_comment_data(clang_child, 'setter')
    property_obj.getter = extract_special_tag_comment_data(clang_child, 'getter')
    property_obj.reset_value = extract_special_tag_comment_data(clang_child, 'resetValue')
    property_obj.range = extract_special_tag_comment_data(clang_child, 'range')
    property_obj.enum_filter = extract_special_tag_comment_data(clang_child, 'enumFilter')

    if property_obj.range:
        range_split = property_obj.range.split(',')
        if len(range_split) == 2:
            property_obj.range = (range_split[0].strip(), range_split[1].strip())
        else:
            print(f'Error: invalid range for property {property_obj.name}: {property_obj.range}')
            property_obj.range = None

    property_obj.default_value = extract_special_tag_comment_data(clang_child, 'defaultValue')
    property_obj.property_condition = extract_special_tag_comment_data(clang_child, 'condition')
    property_obj.load_condition = extract_special_tag_comment_data(clang_child, 'loadCondition')
    property_obj.drag_value = extract_special_tag_comment_data(clang_child, 'drag')
    property_obj.editor_width = extract_special_tag_comment_data(clang_child, 'editorWidth')
    property_obj.inspector = extract_special_tag_comment_data(clang_child, 'inspector')

    if dont_save_tags := extract_special_tag_comment_data(clang_child, 'dontSaveTags'):
        for tag in dont_save_tags.split(','):
            property_obj.dont_save_tags.append(tag.strip())

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
    property_obj.debug_only = has_special_tag_comment(clang_child, 'debugOnly')
    property_obj.no_header = has_special_tag_comment(clang_child, 'noHeader')
    property_obj.private = has_special_tag_comment(clang_child, 'private')

    property_obj.group = extract_special_tag_comment_data(clang_child, 'group')

    property_obj.dontLoad = has_special_tag_comment(clang_child, 'dontLoad')
    property_obj.dontSave = has_special_tag_comment(clang_child, 'dontSave')
    property_obj.dontClone = has_special_tag_comment(clang_child, 'dontClone')

    if property_obj.dontSave:
        property_obj.dontLoad = True

    # remove m_ and _ prefix from name
    #property_obj.display_name = sparcle_utils.make_display_name(property_obj.name)
    property_obj.serialize_name = sparcle_utils.make_serialize_property_name(property_obj.name)

    if not property_obj.default_value:
        property_obj.default_value = extract_property_default_value(clang_child)
        #if property_obj.default_value:
        #    #print(f'Found default value: {property_obj.default_value}')
        #    # необходимо удалить повторение неймспейса, так как иногда получается вот такое
        #    # SpaRcle::Utils::Math::SpaRcle::Utils::Math::FColor::FColor()
        #    property_obj.default_value = fix_cpp_ctor_name(property_obj.default_value)


def parse_sparcle_enum(logger, context, parent_node, code_structure, namespaces):
    if parent_node.kind != clang.cindex.CursorKind.STRUCT_DECL or not parent_node.is_definition():
        return

    if not parent_node.spelling.startswith('CODEGEN_ENUM_DETAILS_STRUCT_'):
        return

    all_found = 0
    name = '(not found)'
    variant = '(not found)'
    enum_type = '(not found)'
    enum_class = '(not found)'
    va_args = '(not found)'
    count = 0

    for child in parent_node.get_children():
        if child.kind != clang.cindex.CursorKind.FIELD_DECL:
            continue

        if child.spelling == 'CODEGEN_ENUM_VARIANT':
            for child2 in child.get_children():
                if child2.kind == clang.cindex.CursorKind.DECL_REF_EXPR:
                    variant = child2.spelling
                    all_found += 1
            continue

        if child.spelling == 'CODEGEN_ENUM_COUNT':
            for child2 in child.get_children():
                if child2.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                    for child3 in child2.get_children():
                        if child3.kind == clang.cindex.CursorKind.INTEGER_LITERAL:
                            tokens = list(child2.get_tokens())
                            count = int(tokens[0].spelling)
                            all_found += 1
                    break
            continue

        if child.spelling == 'CODEGEN_ENUM_NAME':
            # extract const char* value
            for child2 in child.get_children():
                if child2.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                    for child3 in child2.get_children():
                        if child3.kind == clang.cindex.CursorKind.STRING_LITERAL:
                            name = child3.spelling[1:-1]
                            all_found += 1
                    break
            continue

        if child.spelling == 'CODEGEN_ENUM_TYPE':
            for child2 in child.get_children():
                if child2.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                    for child3 in child2.get_children():
                        if child3.kind == clang.cindex.CursorKind.STRING_LITERAL:
                            enum_type = child3.spelling[1:-1]
                            all_found += 1
                    break
            continue

        if child.spelling == 'CODEGEN_ENUM_VA_ARGS':
            for child2 in child.get_children():
                if child2.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                    for child3 in child2.get_children():
                        if child3.kind == clang.cindex.CursorKind.STRING_LITERAL:
                            va_args = child3.spelling[2:-2]
                            all_found += 1
                    break
            continue

        if child.spelling == 'CODEGEN_ENUM_CLASS':
            for child2 in child.get_children():
                if child2.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
                    for child3 in child2.get_children():
                        if child3.kind == clang.cindex.CursorKind.STRING_LITERAL:
                            enum_class = child3.spelling[1:-1]
                            all_found += 1
                    break
            continue

    if all_found == 6:
        enum_object = reflection_utils.CPPEnum(name, variant, count, enum_type, enum_class, namespaces, parent_node.location.file.name, va_args)
        for module_mask in context.modules_mask:
            if module_mask[1] in enum_object.source_path:
                enum_object.code_module_name = module_mask[0]
                break
        code_structure.enums.append(enum_object)
    else:
        logger.log_fatal_error(f'Error: enum {parent_node.spelling} not found all fields! Found {all_found} of 6! Name: {name}, Variant: {variant}, Count: {count}, Type: {enum_type}, Class: {enum_class}, VA Args: {va_args}')


def parse_sparcle_class(logger, context: codegen_context.CodegenContext, parent_node, code_structure, namespaces):
    is_class_or_struct = parent_node.kind == clang.cindex.CursorKind.CLASS_DECL or parent_node.kind == clang.cindex.CursorKind.STRUCT_DECL
    if is_class_or_struct and parent_node.is_definition():
        if not has_static_function(parent_node, 'GetMetaStatic'):
            return

        # Нашли класс
        class_name = parent_node.spelling
        class_obj = reflection_utils.SpaRcleClass(class_name, namespaces)
        class_obj.path = parent_node.location.file.name

        # classicify code module name by path
        if class_obj.path:
            class_path = sparcle_utils.normalize_path(class_obj.path)
            for module_mask in context.modules_mask:
                if module_mask[1] in class_path:
                    class_obj.code_module_name = module_mask[0]
                    break

        class_obj.inspector = extract_special_tag_comment_data(parent_node, 'inspector')

        # format @version(year.month.day) or @version(any number). convert @version(2025.12.31) to 20251231
        # additional example: @version(2025.02.04) -> 20250204
        class_obj.version = extract_special_tag_comment_data(parent_node, 'version')
        if class_obj.version:
            class_obj.version = class_obj.version.replace('.', '')

        # example: @category(Engine.Render.Something other.Something)
        class_obj.category = extract_special_tag_comment_data(parent_node, 'category')

        # example: @extension(xml) or @extension(json) or @extension(sras)
        class_obj.extension = extract_special_tag_comment_data(parent_node, 'extension')

        class_obj.display_name = extract_special_tag_comment_data(parent_node, 'displayName')

        class_obj.hidden = has_special_tag_comment(parent_node, 'hidden')
        class_obj.abstract = has_special_tag_comment(parent_node, 'abstract')
        class_obj.no_copyable = has_special_tag_comment(parent_node, 'noCopyable')
        class_obj.no_movable = has_special_tag_comment(parent_node, 'noMovable')

        if class_obj.inspector:
            #print(f'Found class inspector: {class_obj.inspector}')
            pass

        # Перебираем все поля класса
        for child in parent_node.get_children():
            #print(f'Fount class child: {child.spelling}, {child.kind}')

            if child.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                class_obj.inherited_classes.append(child.spelling)
                continue

            if child.kind == clang.cindex.CursorKind.TYPEDEF_DECL:
                virtual_property = extract_special_tag_comment_data(child, 'virtualProperty')
                if virtual_property:
                    #print(f'Found virtual property: {virtual_property}')
                    property_obj = reflection_utils.CPPProperty(virtual_property, 'Unknown')
                    property_obj.virtual = True
                    process_property(property_obj, child)
                    class_obj.add_variable(property_obj)

            elif child.kind == clang.cindex.CursorKind.FIELD_DECL and is_property_comment(child):
                variable_name = child.spelling
                variable_type = extract_property_type(child)
                property_obj = reflection_utils.CPPProperty(variable_name, variable_type)
                #print(f'Found property: {property_obj.name}, Type: {property_obj.type_name}')
                process_property(property_obj, child)
                class_obj.add_variable(property_obj)

            elif child.kind == clang.cindex.CursorKind.CXX_METHOD and is_method_comment(child):
                method_name = child.spelling
                method_return_type = child.result_type.spelling
                method_obj = reflection_utils.CPPMethod(method_name, method_return_type)
                method_obj.is_const = child.is_const_method()
                method_obj.condition = extract_special_tag_comment_data(child, 'condition')
                method_obj.editor_button = has_special_tag_comment(child, 'editorButton')
                method_obj.evaluate = has_special_tag_comment(child, 'evaluate')
                method_obj.dontPack = has_special_tag_comment(child, 'dontPack')
                for param in child.get_children():
                    if param.kind == clang.cindex.CursorKind.PARM_DECL:
                        param_name = param.spelling
                        param_type = param.type.spelling
                        method_obj.add_parameter(reflection_utils.CPPParameter(param_name, param_type))

                class_obj.add_method(method_obj)

        code_structure.sparcle_classes.append(class_obj)


NOT_ALLOWED_NAMESPACES = { 'std', 'stdext', 'ax' }

ALLOWED_NODE_KINDS = {
    clang.cindex.CursorKind.CLASS_DECL, clang.cindex.CursorKind.STRUCT_DECL,
    clang.cindex.CursorKind.CLASS_TEMPLATE, clang.cindex.CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION,
    clang.cindex.CursorKind.NAMESPACE, clang.cindex.CursorKind.NAMESPACE_REF,
    clang.cindex.CursorKind.FUNCTION_DECL
}

def parse_header_tree(logger, deep, parent_node, code_structure, namespaces, context: codegen_context.CodegenContext):
    if not parent_node.location.file:
        return

    try:
        if parent_node.kind not in ALLOWED_NODE_KINDS:
            return

        # not working on fucking linux :(
        # optimization gives ~0.15 sec
        #if parent_node.kind == clang.cindex.CursorKind.NAMESPACE:
        #    if parent_node.spelling in NOT_ALLOWED_NAMESPACES:
        #        return

    except ValueError:
        return

    if sparcle_utils.normalize_path(parent_node.location.file.name) not in context.valid_files_for_codegen:
        for child in parent_node.get_children():
            parse_header_tree(logger, deep + 1, child, code_structure, namespaces, context)
        return

    parse_sparcle_enum(logger, context, parent_node, code_structure, namespaces)
    parse_sparcle_class(logger, context, parent_node, code_structure, namespaces)

    # Проверяем, является ли текущий узел пространством имен
    if parent_node.kind == clang.cindex.CursorKind.NAMESPACE:
        #if not parent_node.spelling == 'std':
        namespaces = namespaces + [parent_node.spelling]

    # Рекурсивный обход других узлов
    for child in parent_node.get_children():
        parse_header_tree(logger, deep + 1, child, code_structure, namespaces, context)


def parse_header_file(logger: logger_utils.Logger, file_path, include_args, context: codegen_context.CodegenContext):
    code_structure = reflection_utils.CPPCodeStructure()
    cache_file = os.path.join(context.config_dir, 'engine-code-structure.pkl')
    if context.is_script and os.path.isfile(cache_file):
        with open(cache_file, 'rb') as f:
            code_structure = pickle.load(f)
            code_structure.set_sources_as_help()

    args = include_args
    args += ['-fsyntax-only', '-x', 'c++', '-std=c++20']

    logger.log_info(f'Clang args: {args}')

    start = perf_counter()

    index = clang.cindex.Index.create()
    translation_unit = index.parse(
        file_path,
        args=args,
        options=clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES
    )

    end = perf_counter()
    logger.log_info(f'Parse AST tree time: {end - start:.2f} sec')

    start = perf_counter()

    context.valid_files_for_codegen = set(sparcle_utils.normalize_path(os.path.abspath(f)) for f in context.files_for_codegen)

    for node in translation_unit.cursor.get_children():
        parse_header_tree(logger, 0, node, code_structure, [], context)

    # pass noCopyable, noMovable to inherited classes
    for i in range(8):
        for cls in code_structure.sparcle_classes:
            for inherited_class_name in cls.inherited_classes:
                inherited_class_name = inherited_class_name.split('::')[-1]
                inherited_class = code_structure.find_class_by_name(inherited_class_name)
                if inherited_class:
                    if inherited_class.no_copyable:
                        cls.no_copyable = True
                    if inherited_class.no_movable:
                        cls.no_movable = True

    end = perf_counter()
    logger.log_info(f'Analyze AST tree time: {end - start:.2f} sec')

    if not context.is_script:
        with open(cache_file, 'wb') as f:
            pickle.dump(code_structure, f)

    return code_structure