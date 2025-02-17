import sys, os, subprocess, re
from glob import glob

try:
    import clang.cindex
except ImportError:
    print("Please install 'clang' package!")

def normalize_path(path):
    """Нормализует слеши в путях для различных ОС."""
    return os.path.normpath(path)

def get_repo_path():
    return normalize_path('../')

codegen_directory = sys.argv[1]

if not codegen_directory:
    raise Exception('Codegen directory is not set')

includes = [
    f'{get_repo_path()}/Engine/Core/inc',
    f'{get_repo_path()}/Engine/Core/libs',
    f'{get_repo_path()}/Engine/Core/libs/Utils/inc',
    f'{get_repo_path()}/Engine/Core/libs/Utils/libs',
    f'{get_repo_path()}/Engine/Core/libs/Utils/libs/openssl/include',
    f'{get_repo_path()}/Engine/Core/libs/Utils/libs/litehtml/include',
    f'{get_repo_path()}/Engine/Core/libs/Utils/libs/cppcoro/include',
    f'{get_repo_path()}/Engine/Core/libs/Utils/libs/assimp/include',
    f'{get_repo_path()}/Engine/Core/libs/Utils/libs/fmt/include',
    f'{get_repo_path()}/Engine/Core/libs/Scripting/inc',
    f'{get_repo_path()}/Engine/Core/libs/Scripting/libs',
    f'{get_repo_path()}/Engine/Core/libs/Scripting/libs/EvoScript/Core/inc',
    f'{get_repo_path()}/Engine/Core/libs/Audio/inc',
    f'{get_repo_path()}/Engine/Core/libs/Audio/libs',
    f'{get_repo_path()}/Engine/Core/libs/Audio/libs/libmodplug/src',
    f'{get_repo_path()}/Engine/Core/libs/Physics/inc',
    f'{get_repo_path()}/Engine/Core/libs/Physics/libs',
    f'{get_repo_path()}/Engine/Core/libs/Graphics/inc',
    f'{get_repo_path()}/Engine/Core/libs/Graphics/libs',
    f'{get_repo_path()}/Engine/Core/libs/Graphics/libs/imgui',
    f'{get_repo_path()}/Engine/Core/libs/Graphics/libs/EvoVulkan/Core/inc',
    f'{codegen_directory}/Engine/Core/libs/Utils/libs/assimp/include',
    f'{codegen_directory}',
]

include_args = [f'-I{ os.path.abspath(normalize_path(inc))}' for inc in includes]

def preprocess_cpp(source, output):
    command = f"clang++ -E {source} -o {output} -fpermissive {' '.join(include_args)} -D WIN32"

    # Запускаем команду
    result = subprocess.run(command, shell=True, capture_output=True, text=True)

    # Проверяем наличие ошибок
    if result.returncode != 0:
        raise Exception(f'Failed to preprocess file: {source}, error: {result.stderr}, command: {command}')

def make_serialize_property_name(name):
    if name.startswith('m_'):
        name = name[2:]
    if name.startswith('_'):
        name = name[1:]
    return name

# display name for UI
# example: m_isSomeProperty -> Is Some Property
# example: isSomeProperty -> Is Some Property
# example: is_some_property -> Is Some Property
def make_display_name(name):
    name = make_serialize_property_name(name)
    # 1. Замена snake_case на пробелы и приведение к правильному регистру
    name = re.sub(r'_+', ' ', name)
    # 2. Разделение camelCase и PascalCase на слова
    name = re.sub(r'([a-z])([A-Z])', r'\1 \2', name)
    # 3. Приведение первой буквы каждого слова к верхнему регистру
    name = ' '.join(word.capitalize() for word in name.split())
    return name

class Property:
    def __init__(self, name, type_name):
        self.name = name
        self.display_name = name
        self.serialize_name = name
        self.type_name = type_name
        self.default_value = None
        self.change_callback = None
        self.setter = None
        self.getter = None
        self.reset_value = None
        self.drag_value = None
        self.editor_width = None
        self.read_only = False
        self.no_header = False
        self.hidden = False
        self.private = False
        self.dontLoad = False
        self.virtual = False

    def __str__(self):
        return f'Property: {self.name}, Type: {self.type_name}, Default value: {self.default_value}'


class Method:
    def __init__(self, name, return_type):
        self.name = name
        self.return_type = return_type
        self.parameters = []

    def add_parameter(self, parameter):
        self.parameters.append(parameter)

    def __str__(self):
        return f'Method: {self.name}, Return type: {self.return_type}, Parameters: {self.parameters}'

class CodeStructure:
    def __init__(self):
        self.classes = []
        self.enums = []

class Enum:
    def __init__(self, name, variant, count, type, enum_class, namespaces, source_path):
        self.name = name
        self.variant = variant
        self.count = count
        self.namespaces = namespaces
        self.type = type
        self.enum_class = enum_class
        self.source_path = os.path.normpath(source_path)

class Class:
    def __init__(self, name, namespaces):
        self.name = name
        self.inspector = None
        self.namespaces = namespaces
        self.variables = []
        self.methods = []
        self.path = None
        self.inherited_classes = []

    def add_variable(self, variable):
        self.variables.append(variable)

    def add_method(self, method):
        self.methods.append(method)

    def to_string(self, depth):
        namespace_str = '::'.join(self.namespaces)
        #properties_str = ', '.join([str(prop) for prop in self.variables])
        #return f'Class: {namespace_str}::{self.name}, Variables: {properties_str}'
        str = f'{namespace_str} Class: {self.name} Path: {self.path}\n'

        for prop in self.inherited_classes:
            str += "\t" * depth
            str += f'Inherited: {prop}\n'
        for prop in self.variables:
            str += "\t" * depth
            str += f'{prop}\n'
        for method in self.methods:
            str += "\t" * depth
            str += f'{method}\n'

        return str


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
    start = raw_comment.find(f"@{tag}")
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

#def extract_property_default_value(cursor):
#    # Проверяем детей узла, чтобы найти выражение инициализации
#    for child in cursor.get_children():
#        if child.kind == clang.cindex.CursorKind.CALL_EXPR:
#            tokens = list(child.get_tokens())
#            if tokens:
#                # Собираем токены и исключаем '=' в начале, если он присутствует
#                tokens_str = " ".join([token.spelling for token in tokens])
#                if tokens_str.startswith('=') or tokens_str.startswith('{'):
#                    tokens_str = tokens_str[1:].strip()
#
#                return tokens_str
#        if child.kind == clang.cindex.CursorKind.UNEXPOSED_EXPR:
#            tokens = list(child.get_tokens())
#            if tokens:
#                # Собираем токены, начиная со следующего после '=', если он есть
#                tokens_str = " ".join([token.spelling for token in tokens])
#
#                # Убираем знак '=' или '{', если он есть
#                if tokens_str.startswith('=') or tokens_str.startswith('{'):
#                    tokens_str = tokens_str[1:].strip()
#
#                return tokens_str
#    return None  # Если значение по умолчанию не найдено

#def extract_property_default_value(cursor):
#    for child in cursor.get_children():
#        default_value = extract_property_default_value(child)
#        if default_value:
#            return default_value
#
#    tokens = list(cursor.get_tokens())
#    if tokens:
#        tokens_str = [token.spelling for token in tokens]
#        if '=' in tokens_str:
#            eq_index = tokens_str.index('=')
#            default_value_tokens = tokens_str[eq_index + 1:]
#            default_value = " ".join(default_value_tokens).strip()
#            return default_value
#        else :
#            print(f'Error: default value not found for {cursor.spelling}')

def debug_extract_property_default_value(cursor, deep=0):
    tokens = list(cursor.get_tokens())
    token_strs = [token.spelling for token in tokens]

    print(f'[{deep}] Extract default value for {cursor.kind} \"{cursor.spelling}\" \"{cursor.type.spelling}\", {token_strs}')

    for child in cursor.get_children():
        debug_extract_property_default_value(child, deep + 1)

def extract_property_default_value(cursor):
    debug_extract_property_default_value(cursor)

    if cursor.kind != clang.cindex.CursorKind.FIELD_DECL:
        return None

    namespace_stack = []
    tokens = list(cursor.get_tokens())
    token_strs = [token.spelling for token in tokens]

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

    return None

#def extract_property_default_value(cursor):
#    # Извлекаем все токены узла, включая '=' и вызовы функций
#    tokens = list(cursor.get_tokens())
#    if tokens:
#        # Ищем '=', чтобы разделить имя переменной и её значение
#        token_strs = [token.spelling for token in tokens]
#
#        if '=' in token_strs:
#            # Находим индекс '='
#            eq_index = token_strs.index('=')
#            # Все, что после '=', это значение по умолчанию
#            default_value_tokens = token_strs[eq_index + 1:]
#
#            # Соединяем их в строку
#            default_value = " ".join(default_value_tokens).strip()
#
#            # Возвращаем строку без лишних пробелов и символов
#            return default_value
#    return None  # Если значение по умолчанию не найдено

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

def process_property(property_obj, child):
    property_obj.change_callback = extract_special_tag_comment_data(child, 'changeCallback')
    property_obj.setter = extract_special_tag_comment_data(child, 'setter')
    property_obj.getter = extract_special_tag_comment_data(child, 'getter')
    property_obj.reset_value = extract_special_tag_comment_data(child, 'resetValue')
    property_obj.drag_value = extract_special_tag_comment_data(child, 'drag')
    property_obj.editor_width = extract_special_tag_comment_data(child, 'editorWidth')
    property_obj.inspector = extract_special_tag_comment_data(child, 'inspector')

    if property_obj.virtual and not property_obj.getter:
        raise Exception(f'Virtual property {property_obj.name} must have getter!')

    property_obj.hidden = has_special_tag_comment(child, 'hidden')
    property_obj.read_only = has_special_tag_comment(child, 'readOnly')
    property_obj.no_header = has_special_tag_comment(child, 'noHeader')
    property_obj.private = has_special_tag_comment(child, 'private')

    property_obj.dontLoad = has_special_tag_comment(child, 'dontLoad')
    property_obj.dontSave = has_special_tag_comment(child, 'dontSave')

    if property_obj.dontSave:
        property_obj.dontLoad = True

    # remove m_ and _ prefix from name
    property_obj.display_name = make_display_name(property_obj.name)
    property_obj.serialize_name = make_serialize_property_name(property_obj.name)

    property_obj.default_value = extract_property_default_value(child)
    if property_obj.default_value:
        print(f'Found default value: {property_obj.default_value}')

def parse_tree(file_path, deep, parent_node, code_structure, namespaces):
    try:
        if parent_node.kind == clang.cindex.CursorKind.FUNCTION_DECL and parent_node.is_definition():
            if parent_node.spelling.startswith('sr_detail_reflector_'):
                all_found = 0
                name = '(not found)'
                variant = '(not found)'
                enum_type = '(not found)'
                enum_class = '(not found)'
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

                    if all_found == 5:
                        print(f'Found enum: {name} Variant: {variant} Count: {count}, Type: {enum_type}, Class: {enum_class}')
                        enum_object = Enum(name, variant, count, enum_type, enum_class, namespaces, parent_node.location.file.name)
                        code_structure.enums.append(enum_object)
                        break

            return

        is_class_or_struct = parent_node.kind == clang.cindex.CursorKind.CLASS_DECL or parent_node.kind == clang.cindex.CursorKind.STRUCT_DECL
        if is_class_or_struct and parent_node.is_definition():
            if not has_static_function(parent_node, 'GetMetaStatic'):
                return

            # Нашли класс
            class_name = parent_node.spelling
            class_obj = Class(class_name, namespaces)
            class_obj.inspector = extract_special_tag_comment_data(parent_node, 'inspector')
            class_obj.path = parent_node.location.file.name

            if class_obj.inspector:
                print(f'Found class inspector: {class_obj.inspector}')

            # Перебираем все поля класса
            for child in parent_node.get_children():
                if child.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                    class_obj.inherited_classes.append(child.spelling)
                    continue

                if child.kind == clang.cindex.CursorKind.TYPEDEF_DECL:
                    virtual_property = extract_special_tag_comment_data(child, 'virtualProperty')
                    if virtual_property:
                        print(f'Found virtual property: {virtual_property}')
                        property_obj = Property(virtual_property, 'Unknown')
                        property_obj.virtual = True
                        process_property(property_obj, child)
                        class_obj.add_variable(property_obj)

                elif child.kind == clang.cindex.CursorKind.FIELD_DECL and is_property_comment(child):
                    variable_name = child.spelling
                    variable_type = extract_property_type(child)
                    property_obj = Property(variable_name, variable_type)
                    print(f'Found property: {property_obj.name}, Type: {property_obj.type_name}')
                    process_property(property_obj, child)
                    class_obj.add_variable(property_obj)

                elif child.kind == clang.cindex.CursorKind.CXX_METHOD and is_method_comment(child):
                    method_name = child.spelling
                    method_return_type = child.result_type.spelling
                    method_obj = Method(method_name, method_return_type)
                    for param in child.get_children():
                        if param.kind == clang.cindex.CursorKind.PARM_DECL:
                            param_name = param.spelling
                            param_type = param.type.spelling
                            method_obj.add_parameter(Property(param_name, param_type))

                    class_obj.add_method(method_obj)

            code_structure.classes.append(class_obj)

        new_namespace = namespaces
        # Проверяем, является ли текущий узел пространством имен
        if parent_node.kind == clang.cindex.CursorKind.NAMESPACE:
            if not parent_node.spelling == 'std':
                new_namespace = namespaces + [parent_node.spelling]

        # Рекурсивный обход других узлов
        for child in parent_node.get_children():
            parse_tree(file_path, deep + 1, child, code_structure, new_namespace)



    except Exception as e:
        if str(e).startswith('Unknown template argument kind'):
            return
        print(f'Error parse_tree: {e}')




def parse_header_file(file_path):
    code_structure = CodeStructure()

    # Передаем каждый путь как отдельный аргумент
    args = include_args
    args += ['-fsyntax-only', '-x', 'c++', '-std=c++20']

    index = clang.cindex.Index.create()
    translation_unit = index.parse(file_path, args=args)

    print('check diagnostics...')
    #if translation_unit.diagnostics:
    #    for diagnostic in translation_unit.diagnostics:
    #        if 'warning: ' in str(diagnostic):
    #            continue
    #        print(diagnostic)

    # Проходим по узлам файла
    for node in translation_unit.cursor.get_children():
        parse_tree(file_path, 0, node, code_structure, [])

    return code_structure


def generate_class_meta_properties(f, class_structures, class_obj, tabs):
    if len(class_obj.variables) == 0:
        return

    f.write('\t' * tabs + f'SR_NODISCARD virtual std::span<const SR_UTILS_NS::Reflection::Property> GetProperties() const noexcept override {{\n')
    f.write('\t' * (tabs + 1) + f'static const std::array<const SR_UTILS_NS::Reflection::Property, {len(class_obj.variables)}> properties {{ \n')

    for prop in class_obj.variables:
        f.write('\t' * (tabs + 2) + f'SR_UTILS_NS::Reflection::Property()')
        f.write('\n' + '\t' * (tabs + 3) + f'.SetName("{prop.name}")')
        f.write('\n' + '\t' * (tabs + 3) + f'.SetSerializeName("{prop.serialize_name}")')

        if prop.private:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPublicity(SR_UTILS_NS::PropertyPublicity::Private)')
        elif prop.hidden and prop.read_only:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPublicity(SR_UTILS_NS::PropertyPublicity::HiddenReadOnly)')
        elif prop.hidden:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPublicity(SR_UTILS_NS::PropertyPublicity::Hidden)')
        elif prop.read_only:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPublicity(SR_UTILS_NS::PropertyPublicity::ReadOnly)')
        else:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPublicity(SR_UTILS_NS::PropertyPublicity::Public)')

        f.write('\n' + '\t' * (tabs + 3) + f'.SetSetter(&SRClassMetaTemplate::Set_{prop.name})')
        f.write('\n' + '\t' * (tabs + 3) + f'.SetGetter(&SRClassMetaTemplate::Get_{prop.name})')
        f.write('\n' + '\t' * (tabs + 3) + f'.SetChangeCallback(&SRClassMetaTemplate::OnChange_{prop.name})')

        default_value = f'decltype({class_obj.name}::{prop.name})()'
        if prop.default_value:
            default_value = f'decltype({class_obj.name}::{prop.name})(GetDefault_{prop.serialize_name}())'
        elif prop.virtual:
            if prop.getter:
                default_value = f'SR_UTILS_NS::RemoveQualifiersT<decltype(DeclTypeStub()->{prop.getter}())>()'
            else:
                default_value = None

        if default_value:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetDefaultValue(SR_UTILS_NS::Reflection::Value::Create({default_value}))')

        if prop.reset_value:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetResetValue(SR_UTILS_NS::Reflection::Value::Create({prop.reset_value}))')

        # editor params

        f.write('\n' + '\t' * (tabs + 3) + f'.SetEditorParams(SR_UTILS_NS::Reflection::EditorPropertyParams()')

        if prop.no_header:
            f.write('\n' + '\t' * (tabs + 4) + f'.SetNoHeader()')

        f.write('\n' + '\t' * (tabs + 4) + f'.SetDisplayName("{prop.display_name}")')

        if prop.inspector:
            f.write('\n' + '\t' * (tabs + 4) + f'.SetInspector("{prop.inspector}")')

        if prop.drag_value:
            f.write('\n' + '\t' * (tabs + 4) + f'.SetDragSpeed({prop.drag_value})')

        if prop.editor_width:
            f.write('\n' + '\t' * (tabs + 4) + f'.SetEditorWidth({prop.editor_width})')

        f.write('\n' + '\t' * (tabs + 3) + f')')

        f.write(',\n')

    f.write('\t' * (tabs + 1) + '};\n')
    f.write('\t' * (tabs + 1) + 'return properties;\n')
    f.write('\t' * tabs + '}\n\n')

def generate_class_meta_get_base_metas(f, class_structures, class_obj, tabs):
    if len(class_obj.inherited_classes) == 0:
        return

    f.write('\t' * tabs + f'SR_NODISCARD virtual std::span<const SRClassMeta*> GetBaseMetas() const noexcept override {{\n')

    correct_inherited_classes = []
    for inherited_class in class_obj.inherited_classes:
        inherited_class_obj = None
        inherited_class_formated = inherited_class.split('::')[-1]
        for class_structure in class_structures:
            if class_structure.name == inherited_class_formated:
                inherited_class_obj = class_structure
                break

        if inherited_class_obj:
            correct_inherited_classes.append(inherited_class_obj)

    f.write('\t' * (tabs + 1) + f'static std::array<const SRClassMeta*, {len(correct_inherited_classes)}> baseMetas {{ \n')

    for inherited_class_obj in correct_inherited_classes:
        inherited_class_formated = '::'.join(inherited_class_obj.namespaces) + '::' + inherited_class_obj.name
        f.write('\t' * (tabs + 2) + f'{inherited_class_formated}::GetMetaStatic(),\n')

    f.write('\t' * (tabs + 1) + '};\n')
    f.write('\t' * (tabs + 1) + 'return baseMetas;\n')
    f.write('\t' * tabs + '}\n\n')


def generate_class_meta_save(f, class_obj, tabs):
    if len(class_obj.variables) == 0:
        return

    f.write('\t' * tabs + f'void Save(SR_UTILS_NS::ISerializer& serializer, const SR_UTILS_NS::Serializable& obj) const override {{\n')
    tabs += 1

    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name

    f.write('\t' * tabs + f'SR_UTILS_NS::SRClassMeta::Save(serializer, obj);\n\n')
    f.write('\t' * tabs + f'auto&& value = static_cast<{class_name}&>(const_cast<SR_UTILS_NS::Serializable&>(obj));\n\n')

    for prop in class_obj.variables:
        if prop.dontSave:
            continue

        if not prop.getter and prop.virtual:
            continue

        if prop.getter:
            f.write('\t' * tabs + f'{{\n')

            f.write('\t' * (tabs + 1) + f'auto&& propValue = value.{prop.getter}();\n')

            if prop.default_value:
                f.write('\t' * (tabs + 1) + f'if ((serializer.IsWriteDefaults() || propValue != GetDefault_{prop.serialize_name}())) {{\n')
            else:
                f.write('\t' * (tabs + 1) + f'if ((serializer.IsWriteDefaults() || !SR_UTILS_NS::IsDefault(propValue))) {{\n')

            f.write('\t' * (tabs + 2) + f'static constexpr SR_UTILS_NS::SerializationId keyName_{prop.serialize_name} = SR_UTILS_NS::SerializationId::Create("{prop.serialize_name}");\n')
            f.write('\t' * (tabs + 2) + f'SR_UTILS_NS::Serialization::Save(serializer, propValue, keyName_{prop.serialize_name});\n')

            f.write('\t' * (tabs + 1) + f'}}\n')
            f.write('\t' * tabs + f'}}\n')
        else:
            if prop.default_value:
                f.write('\t' * tabs + f'if ((serializer.IsWriteDefaults() || value.{prop.name} != GetDefault_{prop.serialize_name}())) {{\n')
            else:
                f.write('\t' * tabs + f'if ((serializer.IsWriteDefaults() || !SR_UTILS_NS::IsDefault(value.{prop.name}))) {{\n')
            f.write('\t' * (tabs + 1) + f'static constexpr SR_UTILS_NS::SerializationId keyName_{prop.serialize_name} = SR_UTILS_NS::SerializationId::Create("{prop.serialize_name}");\n')
            f.write('\t' * (tabs + 1) + f'SR_UTILS_NS::Serialization::Save(serializer, value.{prop.name}, keyName_{prop.serialize_name});\n')
            f.write('\t' * tabs + f'}}\n')

    tabs -= 1
    f.write('\t' * tabs + '}\n\n')
    pass

def generate_class_meta_load(f, class_obj, tabs):
    if len(class_obj.variables) == 0:
        return

    f.write('\t' * tabs + f'void Load(SR_UTILS_NS::IDeserializer& deserializer, SR_UTILS_NS::Serializable& obj) const override {{\n')
    tabs += 1

    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name

    f.write('\t' * tabs + f'SR_UTILS_NS::SRClassMeta::Load(deserializer, obj);\n\n')
    f.write('\t' * tabs + f'auto&& value = static_cast<{class_name}&>(obj);\n\n')

    for prop in class_obj.variables:
        if prop.dontLoad:
            continue

        if (not prop.setter or not prop.getter) and prop.virtual:
            continue

        f.write('\t' * tabs + f'{{\n')
        f.write('\t' * (tabs + 1) + f'static constexpr SR_UTILS_NS::SerializationId keyName_{prop.serialize_name} = SR_UTILS_NS::SerializationId::Create("{prop.serialize_name}");\n')

        if prop.setter:
            if prop.getter:
                f.write('\t' * (tabs + 1) + f'using Type = SR_UTILS_NS::RemoveQualifiersT<decltype(value.{prop.getter}())>;\n')
            elif prop.virtual:
                raise Exception(f'Virtual property {prop.name} must have getter!')
            else:
                f.write('\t' * (tabs + 1) + f'using Type = SR_UTILS_NS::RemoveQualifiersT<decltype(value.{prop.name})>;\n')

            f.write('\t' * (tabs + 1) + f'Type propValue {{}};\n')
            f.write('\t' * (tabs + 1) + f'if (!SR_UTILS_NS::Serialization::Load(deserializer, propValue, keyName_{prop.serialize_name})) {{\n')
            if prop.default_value:
                f.write('\t' * (tabs + 2) + f'propValue = GetDefault_{prop.serialize_name}();\n')
            f.write('\t' * (tabs + 1) + f'}}\n')
            f.write('\t' * (tabs + 1) + f'value.{prop.setter}(propValue);\n')

        else:
            f.write('\t' * (tabs + 1) + f'if (!SR_UTILS_NS::Serialization::Load(deserializer, value.{prop.name}, keyName_{prop.serialize_name})) {{\n')
            if prop.default_value:
                f.write('\t' * (tabs + 2) + f'value.{prop.name} = GetDefault_{prop.serialize_name}();\n')
            f.write('\t' * (tabs + 1) + f'}}\n')

        f.write('\t' * tabs + f'}}\n')

    tabs -= 1
    f.write('\t' * tabs + '}\n\n')
    pass

def generate_class_meta(f, class_structures, class_obj, tabs):
    if len(class_obj.inherited_classes) > 0:
        f.write('\t' * tabs + f'/// Include inherited classes.\n')
        for inherited_class in class_obj.inherited_classes:
            inherited_class_obj = None
            inherited_class_formated = inherited_class.split('::')[-1]
            for class_structure in class_structures:
                if class_structure.name == inherited_class_formated:
                    inherited_class_obj = class_structure
                    break

            if inherited_class_obj:
                f.write('\t' * tabs + f'#include "{os.path.abspath(os.path.normpath(inherited_class_obj.path))}"\n')

        f.write('\n')

    f.write('\t' * tabs + f'namespace Codegen {{\n')
    tabs += 1

    for i, namespace in enumerate(class_obj.namespaces):
        f.write('\t' * tabs + f'using namespace {"::".join(class_obj.namespaces[:i + 1])};\n')

    if len(class_obj.namespaces) > 0:
        f.write('\n')

    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name
    f.write('\t' * tabs + f'template<> struct SRClassMetaTemplate<{class_name}> final : public SR_UTILS_NS::SRClassMeta {{\n')
    tabs += 1

    f.write('\t' * tabs + f'static SRClassMetaTemplate<{class_name}>& Instance() {{ \n')
    f.write('\t' * (tabs + 1) + f'static SRClassMetaTemplate<{class_name}> instance;\n')
    f.write('\t' * (tabs + 1) + 'return instance;\n')
    f.write('\t' * tabs + '}\n\n')

    f.write('\t' * tabs + f'SR_NODISCARD {class_name}* DeclTypeStub() const noexcept {{ return nullptr; }}\n\n')

    for prop in class_obj.variables:
        if not prop.default_value:
            continue
        f.write('\t' * tabs + f'// default value for \"{prop}\"\n')
        f.write('\t' * tabs + f'static auto GetDefault_{prop.serialize_name}() {{ return {prop.default_value}; }}\n\n')

    #for prop in class_obj.variables:
    #    f.write('\t' * tabs + f'// {prop}\n')
    #    f.write('\t' * tabs + f'const {prop.type_name}& Get_{prop.name}({class_name}* pClass) {{ return pClass->{prop.name}; }}\n')
    #    f.write('\t' * tabs + f'void Set_{prop.name}({class_name}* pClass, const {prop.type_name}& value) {{ pClass->{prop.name} = value; }}\n\n')

    f.write('\t' * tabs + f'SR_NODISCARD bool IsAbstract() const noexcept override {{ return std::is_abstract_v<{class_name}>; }}\n\n')

    #######################################
    if class_obj.inspector:
        f.write('\t' * tabs + f'SR_NODISCARD SR_UTILS_NS::StringAtom GetInspectorName() const noexcept override {{ \n')
        f.write('\t' * (tabs + 1) + f'static const SR_UTILS_NS::StringAtom id = "{class_obj.inspector}";\n')
        f.write('\t' * (tabs + 1) + f'return id;\n')
        f.write('\t' * tabs + '}\n\n')
    #######################################

    generate_class_meta_get_base_metas(f, class_structures, class_obj, tabs)
    generate_class_meta_properties(f, class_structures, class_obj, tabs)

    #has_serializable_fields = len(class_obj.variables) > 0
    #f.write('\t' * tabs + f'SR_NODISCARD virtual bool HasSerializableFields() const noexcept override {{\n')
    #f.write('\t' * (tabs + 1) + f'for (auto&& pBaseMeta : GetBaseMetas()) {{\n')
    #f.write('\t' * (tabs + 2) + f'if (pBaseMeta->HasSerializableFields()) {{\n')
    #f.write('\t' * (tabs + 3) + f'return true;\n')
    #f.write('\t' * (tabs + 2) + f'}}\n')
    #f.write('\t' * (tabs + 1) + f'}}\n')
    #f.write('\t' * (tabs + 1) + f'return { "true" if has_serializable_fields else "false" };\n')
    #f.write('\t' * tabs + '}\n\n')

    generate_class_meta_save(f, class_obj, tabs)
    generate_class_meta_load(f, class_obj, tabs)

    f.write('\t' * tabs + f'SR_NODISCARD virtual std::string_view GetFactoryName() const noexcept override {{\n')
    f.write('\t' * (tabs + 1) + f'return {class_name}::GetClassStaticName();\n')
    f.write('\t' * tabs + '}\n\n')

    f.write('\t' * (tabs - 1) + f'private:\n')
    f.write('\t' * tabs + f'static inline const bool SR_CODEGEN_REGISTER_FACTORY = SR_UTILS_NS::Factory::Instance().Register<{class_name}>();\n\n')

    f.write('\t' * tabs + f'/// Bindings for class {class_obj.name}\n')

    for property in class_obj.variables:
        f.write('\t' * tabs + f'static void Set_{property.name}(void* pClass, const SR_UTILS_NS::Reflection::Value& value) {{\n')

        #f.write('\t' * (tabs + 1) + f'const decltype({class_name}::{property.name})* pData;\n')
        #f.write('\t' * (tabs + 1) + f'if (!value.Map(pData)) {{\n')
        #f.write('\t' * (tabs + 2) + f'return;\n')
        #f.write('\t' * (tabs + 1) + f'}}\n')

        if property.virtual:
            if not property.setter or not property.getter:
                f.write('\t' * (tabs + 1) + f'SRHalt("Virtual property {property.name} must have getter and setter!");\n')
                f.write('\t' * (tabs + 1) + f'return;\n')
            else:
                f.write('\t' * (tabs + 1) + f'auto&& pClassImpl = (({class_name}*)pClass);\n')
                f.write('\t' * (tabs + 1) + f'using Type = std::remove_const_t<SR_UTILS_NS::RemoveQualifiersT<decltype(pClassImpl->{property.getter}())>>;\n')
                f.write('\t' * (tabs + 1) + f'auto&& pData = value.TryCast<Type>();\n')
                f.write('\t' * (tabs + 1) + f'if (!pData) {{\n')
                f.write('\t' * (tabs + 2) + f'SRHalt("Failed to cast value!");\n')
                f.write('\t' * (tabs + 2) + f'return;\n')
                f.write('\t' * (tabs + 1) + f'}}\n')

                f.write('\t' * (tabs + 1) + f'pClassImpl->{property.setter}(std::move(*pData));\n')
        else:
            f.write('\t' * (tabs + 1) + f'auto&& pData = value.TryCast<decltype({class_name}::{property.name})>();\n')
            f.write('\t' * (tabs + 1) + f'if (!pData) {{\n')
            f.write('\t' * (tabs + 2) + f'SRHalt("Failed to cast value!");\n')

            f.write('\t' * (tabs + 2) + f'return;\n')
            f.write('\t' * (tabs + 1) + f'}}\n')

            if property.setter:
                f.write('\t' * (tabs + 1) + f'(({class_name}*)pClass)->{property.setter}(std::move(*pData));\n')
            else:
                f.write('\t' * (tabs + 1) + f'(({class_name}*)pClass)->{property.name} = std::move(*pData);\n')

        f.write('\t' * tabs + f'}}\n')

        f.write('\t' * tabs + f'static SR_UTILS_NS::Reflection::Value Get_{property.name}(void* pClass) {{\n')
        if property.getter:
            f.write('\t' * (tabs + 1) + f'auto&& value = (({class_name}*)pClass)->{property.getter}();\n')
            f.write('\t' * (tabs + 1) + f'if constexpr (std::is_lvalue_reference_v<decltype(value)>) {{\n')
            f.write('\t' * (tabs + 2) + f'if constexpr (std::is_const_v<std::remove_reference_t<decltype(value)>>) {{\n')
            f.write('\t' * (tabs + 3) + f'return SR_UTILS_NS::Reflection::Value::CreateCRef(value);\n')
            f.write('\t' * (tabs + 2) + f'}} else {{\n')
            f.write('\t' * (tabs + 3) + f'return SR_UTILS_NS::Reflection::Value::CreateRef(value);\n')
            f.write('\t' * (tabs + 2) + f'}}\n')
            f.write('\t' * (tabs + 1) + f'}} else {{\n')
            f.write('\t' * (tabs + 2) + f'return SR_UTILS_NS::Reflection::Value::Create(std::move(value));\n')
            f.write('\t' * (tabs + 1) + f'}}\n')
        else:
            if property.read_only:
                f.write('\t' * (tabs + 1) + f'return SR_UTILS_NS::Reflection::Value::CreateCRef((({class_name}*)pClass)->{property.name});\n')
            else:
                f.write('\t' * (tabs + 1) + f'return SR_UTILS_NS::Reflection::Value::CreateRef((({class_name}*)pClass)->{property.name});\n')


        f.write('\t' * tabs + f'}}\n')

        f.write('\t' * tabs + f'static void OnChange_{property.name}(void* pClass) {{\n')
        if property.change_callback:
            f.write('\t' * (tabs + 1) + f'(({class_name}*)pClass)->{property.change_callback}();\n')
        f.write('\t' * tabs + f'}}\n')

        f.write('\n')

    tabs -= 1
    f.write('\t' * tabs + '};\n\n')

    #for inherited_class in class_obj.inherited_classes:
    #    inherited_class_formated = inherited_class.split('::')[-1]
    #    f.write('\t' * tabs + f'// class {class_obj.name} inherits from {inherited_class}\n')
    #    f.write('\t' * tabs + f'inline static bool SR_CODEGEN_REGISTER_INHERITANCE_{class_obj.name}_{inherited_class_formated} '
    #                          f'= SR_UTILS_NS::ClassDB::Instance().RegisterInheritance(\"{class_obj.name}\", \"{inherited_class_formated}\");\n\n')

    tabs -= 1
    f.write('\t' * tabs + '}\n\n')
    pass

def generate_enums_code(codegen_dir, enums):
    basic_full_path = os.path.normpath(f'{codegen_dir}/EnumsFwd.generated.hpp')
    with open(basic_full_path, 'w', encoding='utf8') as f:
        f.write('// This file is generated by SpaRcle Studio code-generator ^_^\n\n')
        f.write(f'#ifndef SR_CODEGEN_ENUMS_BASIC_HPP\n')
        f.write(f'#define SR_CODEGEN_ENUMS_BASIC_HPP\n\n')

        for enum_obj in enums:
            namespace_str = ''
            if len(enum_obj.namespaces) > 0:
                namespace_str = '::'.join(enum_obj.namespaces)

            if len(namespace_str) > 0:
                f.write(f'namespace {namespace_str} {{\n')

            f.write(f'\t{enum_obj.enum_class} {enum_obj.name} : {enum_obj.type};\n')
            f.write(f'\tclass CodegenEnumIncludedChecked_{enum_obj.name};\n')
            #f.write(f'\ttemplate<typename T, typename Enable = void> struct CodegenEnumIncludedChecked_{enum_obj.name} : std::false_type {{}};\n')

            if namespace_str:
                f.write('}\n\n')

        f.write('#endif\n')

    full_path = os.path.normpath(f'{codegen_dir}/Enums.generated.hpp')
    with open(full_path, 'w', encoding='utf8') as f:
        f.write('// This file is generated by SpaRcle Studio code-generator ^_^\n\n')
        f.write(f'#include "EnumsFwd.generated.hpp"\n\n')
        f.write(f'#ifndef SR_CODEGEN_ENUMS_HPP\n')
        f.write(f'#define SR_CODEGEN_ENUMS_HPP\n\n')

        f.write('#define SR_CODEGEN_ENUM_OPERATORS(enumName)                                                                             \\\n')
        f.write('\tinline constexpr enumName operator|(enumName lhs, enumName rhs) {                                                   \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(lhs) |                                                        \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(rhs)                                                          \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator&(enumName lhs, enumName rhs) {                                                   \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(lhs) &                                                        \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(rhs)                                                          \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator^(enumName lhs, enumName rhs) {                                                   \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(lhs) ^                                                        \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(rhs)                                                          \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator~(enumName lhs) {                                                                 \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        ~static_cast<std::underlying_type_t<enumName>>(lhs)                                                         \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName& operator|=(enumName& lhs, enumName rhs) {                                                \\\n')
        f.write('\t    lhs = lhs | rhs;                                                                                                \\\n')
        f.write('\t    return lhs;                                                                                                     \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName& operator&=(enumName& lhs, enumName rhs) {                                                \\\n')
        f.write('\t    lhs = lhs & rhs;                                                                                                \\\n')
        f.write('\t    return lhs;                                                                                                     \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName& operator^=(enumName& lhs, enumName rhs) {                                                \\\n')
        f.write('\t    lhs = lhs ^ rhs;                                                                                                \\\n')
        f.write('\t    return lhs;                                                                                                     \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr bool operator!(enumName lhs) {                                                                     \\\n')
        f.write('\t    return !static_cast<std::underlying_type_t<enumName>>(lhs);                                                     \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr bool operator&&(enumName lhs, enumName rhs) {                                                      \\\n')
        f.write('\t    return static_cast<std::underlying_type_t<enumName>>(lhs) &&                                                    \\\n')
        f.write('\t             static_cast<std::underlying_type_t<enumName>>(rhs);                                                    \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr bool operator||(enumName lhs, enumName rhs) {                                                      \\\n')
        f.write('\t    return static_cast<std::underlying_type_t<enumName>>(lhs) ||                                                    \\\n')
        f.write('\t             static_cast<std::underlying_type_t<enumName>>(rhs);                                                    \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr bool operator==(enumName lhs, enumName rhs) {                                                      \\\n')
        f.write('\t    return static_cast<std::underlying_type_t<enumName>>(lhs) ==                                                    \\\n')
        f.write('\t             static_cast<std::underlying_type_t<enumName>>(rhs);                                                    \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr bool operator!=(enumName lhs, enumName rhs) {                                                      \\\n')
        f.write('\t    return static_cast<std::underlying_type_t<enumName>>(lhs) !=                                                    \\\n')
        f.write('\t             static_cast<std::underlying_type_t<enumName>>(rhs);                                                    \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr bool operator<(enumName lhs, enumName rhs) {                                                       \\\n')
        f.write('\t    return static_cast<std::underlying_type_t<enumName>>(lhs) <                                                     \\\n')
        f.write('\t             static_cast<std::underlying_type_t<enumName>>(rhs);                                                    \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr bool operator>(enumName lhs, enumName rhs) {                                                       \\\n')
        f.write('\t    return static_cast<std::underlying_type_t<enumName>>(lhs) >                                                     \\\n')
        f.write('\t             static_cast<std::underlying_type_t<enumName>>(rhs);                                                    \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr bool operator<=(enumName lhs, enumName rhs) {                                                      \\\n')
        f.write('\t    return static_cast<std::underlying_type_t<enumName>>(lhs) <=                                                    \\\n')
        f.write('\t             static_cast<std::underlying_type_t<enumName>>(rhs);                                                    \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr bool operator>=(enumName lhs, enumName rhs) {                                                      \\\n')
        f.write('\t    return static_cast<std::underlying_type_t<enumName>>(lhs) >=                                                    \\\n')
        f.write('\t             static_cast<std::underlying_type_t<enumName>>(rhs);                                                    \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator+(enumName lhs, enumName rhs) {                                                   \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(lhs) +                                                        \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(rhs)                                                          \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator-(enumName lhs, enumName rhs) {                                                   \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(lhs) -                                                        \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(rhs)                                                          \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator*(enumName lhs, enumName rhs) {                                                   \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(lhs) *                                                        \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(rhs)                                                          \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator/(enumName lhs, enumName rhs) {                                                   \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(lhs) /                                                        \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(rhs)                                                          \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator%(enumName lhs, enumName rhs) {                                                   \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(lhs) %                                                        \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(rhs)                                                          \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName& operator++(enumName& lhs) {                                                              \\\n')
        f.write('\t    lhs = static_cast<enumName>(static_cast<std::underlying_type_t<enumName>>(lhs) + 1);                            \\\n')
        f.write('\t    return lhs;                                                                                                     \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator++(enumName& lhs, int) {                                                          \\\n')
        f.write('\t    enumName result = lhs;                                                                                          \\\n')
        f.write('\t    ++lhs;                                                                                                          \\\n')
        f.write('\t    return result;                                                                                                  \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName& operator--(enumName& lhs) {                                                              \\\n')
        f.write('\t    lhs = static_cast<enumName>(static_cast<std::underlying_type_t<enumName>>(lhs) - 1);                            \\\n')
        f.write('\t    return lhs;                                                                                                     \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator--(enumName& lhs, int) {                                                          \\\n')
        f.write('\t    enumName result = lhs;                                                                                          \\\n')
        f.write('\t    --lhs;                                                                                                          \\\n')
        f.write('\t    return result;                                                                                                  \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator<<(enumName lhs, enumName rhs) {                                                  \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(lhs) <<                                                       \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(rhs)                                                          \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName operator>>(enumName lhs, enumName rhs) {                                                  \\\n')
        f.write('\t    return static_cast<enumName>(                                                                                   \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(lhs) >>                                                       \\\n')
        f.write('\t        static_cast<std::underlying_type_t<enumName>>(rhs)                                                          \\\n')
        f.write('\t    );                                                                                                              \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName& operator<<=(enumName& lhs, enumName rhs) {                                               \\\n')
        f.write('\t    lhs = lhs << rhs;                                                                                               \\\n')
        f.write('\t    return lhs;                                                                                                     \\\n')
        f.write('\t}                                                                                                                   \\\n')
        f.write('\tinline constexpr enumName& operator>>=(enumName& lhs, enumName rhs) {                                               \\\n')
        f.write('\t    lhs = lhs >> rhs;                                                                                               \\\n')
        f.write('\t    return lhs;                                                                                                     \\\n')
        f.write('\t}                                                                                                                   \\\n\n')

        # generate code
        for enum_obj in enums:
            namespace_str = ''
            if len(enum_obj.namespaces) > 0:
                namespace_str = '::'.join(enum_obj.namespaces)

            if len(namespace_str) > 0:
                namespace_str += '::'

            class_full_name = namespace_str + enum_obj.name

            f.write(f'namespace Codegen {{\n')

            f.write(f'\ttemplate<> constexpr SR_UTILS_NS::EnumVariant GetEnumVariant(Codegen::EnumSelector<{class_full_name}>) noexcept {{\n')
            f.write(f'\t\treturn SR_UTILS_NS::EnumVariant::{enum_obj.variant};\n')
            f.write(f'\t}}\n\n')

            f.write(f'\ttemplate<> constexpr size_t GetEnumItemsCount(Codegen::EnumSelector<{class_full_name}>) noexcept {{\n')
            f.write(f'\t\treturn {enum_obj.count};\n')
            f.write(f'\t}}\n\n')

            f.write(f'}}\n\n')

        # operators
        for enum_obj in enums:
            namespace_str = ''
            if len(enum_obj.namespaces) > 0:
                namespace_str = '::'.join(enum_obj.namespaces)

            if len(namespace_str) > 0:
                namespace_str += '::'

            class_full_name = namespace_str + enum_obj.name
            f.write(f'SR_CODEGEN_ENUM_OPERATORS({class_full_name})\n')

        f.write('\n')

        #for enum_obj in enums:
        #    namespace_str = ''
        #    if len(enum_obj.namespaces) > 0:
        #        namespace_str = '::'.join(enum_obj.namespaces)
        #
        #    if len(namespace_str) > 0:
        #        namespace_str += '::'
        #
        #    f.write(f'template<> struct fmt::formatter<{namespace_str}{enum_obj.name}> {{\n')
        #    f.write(f'\tconstexpr auto parse(format_parse_context& ctx) {{ return ctx.begin(); }}\n')
        #    f.write(f'\tauto format(const {namespace_str}{enum_obj.name}& val, format_context& ctx) const {{\n')
        #
        #    f.write(f'\t\tif constexpr (SR_UTILS_NS::IsCompleteTypeV<{namespace_str}CodegenEnumIncludedChecked_{enum_obj.name}>) {{\n')
        #    f.write(f'\t\t\treturn fmt::format_to(ctx.out(), "{{}}", SR_UTILS_NS::EnumReflector::ToStringAtom(val).ToStringView());\n')
        #    f.write(f'\t\t}} else {{\n')
        #    f.write(f'\t\t\tSRHalt("Formatted enum \\\"{enum_obj.name}\\\" is not included, please include it!");\n')
        #    #f.write(f'\t\t\tstatic_assert(SR_UTILS_NS::AlwaysFalseV<{namespace_str}{enum_obj.name}>, "Formatted enum is not included, please include it!");\n')
        #    f.write(f'\t\t\treturn fmt::format_to(ctx.out(), "{{}}", static_cast<int>(val));\n')
        #    f.write(f'\t\t}}\n')

        #    f.write(f'\t}}\n')
        #    f.write(f'}};\n')

        f.write(f'\n#endif // SR_CODEGEN_ENUMS_HPP\n')

        print(f'Remove old enum files: {codegen_dir}/../Enum/*.hpp')

        for file in glob(f'{codegen_dir}/../Enum/*.hpp'):
            os.remove(file)

        print(f'Generating new enum files: {codegen_dir}/../Enum/*.hpp')

        # formatting
        for enum_obj in enums:
            enum_gen_path = os.path.normpath(f'{codegen_dir}/../Enum/{enum_obj.name}.hpp')
            os.makedirs(os.path.dirname(enum_gen_path), exist_ok=True)
            with open(enum_gen_path, 'w', encoding='utf8') as f:
                caps_enum_name = enum_obj.name.upper()

                f.write('// This file is generated by SpaRcle Studio code-generator ^_^\n\n')
                f.write(f'#ifndef SR_CODEGEN_ENUM_{caps_enum_name}_HPP\n')
                f.write(f'#define SR_CODEGEN_ENUM_{caps_enum_name}_HPP\n\n')

                f.write(f'#include \"{enum_obj.source_path}\"\n\n')

                f.write(f'#include <Codegen/Enums.generated.hpp>\n\n')

                namespace_str = ''
                if len(enum_obj.namespaces) > 0:
                    namespace_str = '::'.join(enum_obj.namespaces)

                if len(namespace_str) > 0:
                    namespace_str += '::'

                f.write(f'template<> struct fmt::formatter<{namespace_str}{enum_obj.name}> {{\n')
                f.write(f'\tconstexpr auto parse(format_parse_context& ctx) {{ return ctx.begin(); }}\n')
                f.write(f'\tauto format(const {namespace_str}{enum_obj.name}& val, format_context& ctx) const {{\n')

                f.write(f'\t\tstatic_assert(SR_UTILS_NS::IsCompleteTypeV<{namespace_str}CodegenEnumIncludedChecked_{enum_obj.name}>, "Formatted enum is not included, please include it!");\n')
                f.write(f'\t\treturn fmt::format_to(ctx.out(), "{{}}", SR_UTILS_NS::EnumReflector::ToStringAtom(val).ToStringView());\n')

                #f.write(f'\t\tif constexpr (SR_UTILS_NS::IsCompleteTypeV<{namespace_str}CodegenEnumIncludedChecked_{enum_obj.name}>) {{\n')
                #f.write(f'\t\t\treturn fmt::format_to(ctx.out(), "{{}}", SR_UTILS_NS::EnumReflector::ToStringAtom(val).ToStringView());\n')
                #f.write(f'\t\t}} else {{\n')
                #f.write(f'\t\t\tSRHalt("Formatted enum \\\"{enum_obj.name}\\\" is not included, please include it!");\n')
                #f.write(f'\t\t\tstatic_assert(SR_UTILS_NS::AlwaysFalseV<{namespace_str}{enum_obj.name}>, "Formatted enum is not included, please include it!");\n')
                #f.write(f'\t\t\treturn fmt::format_to(ctx.out(), "{{}}", static_cast<int>(val));\n')
                #f.write(f'\t\t}}\n')

                f.write(f'\t}}\n')
                f.write(f'}};\n')

                f.write(f'\n#endif // SR_CODEGEN_ENUM_{caps_enum_name}_HPP\n')

def generate_classes_code(codegen_dir, class_structures):
    file_map = {}
    for class_obj in class_structures:
        if not class_obj.path:
            raise Exception(f'Path is not set for class: {class_obj.name}')

        file_name = class_obj.path.replace('\\', '/')
        file_name = str(file_name.split('/')[-1]) # get file name

        if os.path.exists(file_name):
            raise Exception(f'Absolute path is not allowed: {file_name}, source: {class_obj.path}')

        file_name = file_name[:-2] # remove .h

        if file_name not in file_map:
            file_map[file_name] = []
            file_map[file_name].append(class_obj)
        else:
            file_map[file_name].append(class_obj)

    if not os.path.exists(codegen_dir):
        os.makedirs(codegen_dir)

    if not os.path.exists(codegen_dir):
        raise Exception(f'Failed to create directory: {codegen_dir}')

    for file_name, class_objs in file_map.items():
        full_path = os.path.normpath(f'{codegen_dir}/{file_name}.generated.hpp')
        with open(full_path, 'w', encoding='utf8') as f:
            f.write('// This file is generated by SpaRcle Studio code-generator ^_^\n\n')
            f.write(f'#ifndef SR_CODEGEN_{file_name.upper()}_HPP\n')
            f.write(f'#define SR_CODEGEN_{file_name.upper()}_HPP\n\n')
            for class_obj in class_objs:
                f.write(f'#include "{os.path.abspath(os.path.normpath(class_obj.path))}"\n\n')
                f.write(f'#include <Utils/TypeTraits/ClassDB.h>\n')
                f.write(f'#include <Utils/TypeTraits/SRClass.h>\n')
                f.write(f'#include <Utils/TypeTraits/Factory.h>\n')
                f.write(f'#include <Utils/TypeTraits/SRClassMeta.h>\n\n')

                tabs = 0

                generate_class_meta(f, class_structures, class_obj, tabs)

                if len(class_obj.namespaces) > 0:
                    tabs = 1
                    namespace_str = '::'.join(class_obj.namespaces)
                    f.write(f'namespace {namespace_str} {{\n')


                f.write('\t' * tabs + f'const SR_UTILS_NS::SRClassMeta* {class_obj.name}::GetMetaStatic() noexcept {{\n')
                f.write('\t' * (tabs + 1) + f'return &::Codegen::SRClassMetaTemplate<{class_obj.name}>::Instance();\n')
                f.write('\t' * tabs + '}\n\n')

                factory_name = class_obj.name.split('::')[-1]
                #factory_name = factory_name[0].lower() + factory_name[1:]
                f.write('\t' * tabs + f'SR_UTILS_NS::StringAtom {class_obj.name}::GetClassStaticName() noexcept {{\n')
                f.write('\t' * (tabs + 1) + f'return \"{factory_name}\";\n')
                f.write('\t' * tabs + '}\n\n')

                f.write('\t' * tabs + f'SR_UTILS_NS::SRClass* {class_obj.name}::AllocateStatic() noexcept {{\n')
                f.write('\t' * (tabs + 1) + f'if constexpr (std::is_abstract_v<{class_obj.name}>) {{\n')
                f.write('\t' * (tabs + 2) + f'SRHalt("Cannot allocate abstract class \\\"{class_obj.name}\\\"!");\n')
                f.write('\t' * (tabs + 2) + f'return nullptr;\n')
                f.write('\t' * (tabs + 1) + f'}}\n')
                f.write('\t' * (tabs + 1) + f'else {{\n')
                f.write('\t' * (tabs + 2) + f'return static_cast<SR_UTILS_NS::SRClass*>(SRNew<{class_obj.name}>());\n')
                f.write('\t' * (tabs + 1) + f'}}\n')
                f.write('\t' * tabs + '}\n\n')

                f.write('\t' * tabs + f'bool {class_obj.name}::RegisterPropertiesCodegen() {{\n')
                f.write('\t' * (tabs + 1))
                f.write(f'return true; // Register properties\n')
                f.write(('\t' * tabs) + '}\n')
                if len(class_obj.namespaces) > 0:
                    f.write('}\n')
            f.write('\n')
            f.write(f'#endif // SR_CODEGEN_{file_name.upper()}_HPP\n')

    pass

def main() -> bool:
    print('start script...')

    collected_files = []
    patterns = ['*.h']
    include_dirs = [
        'Engine/Core/libs/Utils/inc/Utils',
        'Engine/Core/libs/Graphics/inc/Graphics',
        'Engine/Core/libs/Audio/inc/Audio',
        'Engine/Core/libs/Physics/inc/Physics',
        'Engine/Core/libs/Scripting/inc/Scripting',
        'Engine/Core/inc',
    ]

    # Преобразуем пути в include_dirs для разных ОС
    include_dirs = [normalize_path(dir) for dir in include_dirs]

    print(f'repo path: {get_repo_path()}')
    print('collect files...\n')

    for dir_path, _, _ in os.walk(get_repo_path()):
        for pattern in patterns:
            for file in glob(os.path.join(dir_path, pattern)):
                normalized_file = normalize_path(file)
                if any((inc_dir in normalized_file) for inc_dir in include_dirs):
                    collected_files.append(normalized_file)

    print(f'collected files: {len(collected_files)}\n')

    print('create cxx file with all includes...')

    cached_file = os.path.abspath(normalize_path(f'{codegen_directory}/Codegen/Codegen/AllIncludes.cxx'))

    vulkan_h = os.path.abspath(normalize_path(f'{codegen_directory}/vulkan/vulkan.h'))
    os.makedirs(os.path.dirname(vulkan_h), exist_ok=True)

    with open(vulkan_h, 'w', encoding='utf8') as f:
        f.write('// This file is generated by SpaRcle Studio code-generator ^_^\n\n')

    # Получаем директорию из пути к файлу
    directory = os.path.dirname(cached_file)

    # Проверяем, существует ли директория, и создаем ее, если нет
    if not os.path.exists(directory):
        os.makedirs(directory)  # Создает директории рекурсивно

    with open(f'{cached_file}', 'w', encoding='utf8') as f:
        f.write('// This file is generated by SpaRcle Studio code-generator ^_^\n\n')
        std_template = ('namespace std {\n'
                        '\ttemplate <class _Ty, class _Alloc = allocator<_Ty>> class vector { };\n'
                        '\ttemplate <typename T> struct list { };\n'
                        '\ttemplate <typename T> struct deque { };\n'
                        '\ttemplate <typename T> struct set { };\n'
                        '\ttemplate <typename T> struct multiset { };\n'
                        '\ttemplate <typename T> struct map { };\n'
                        '\ttemplate <typename T> struct multimap { };\n'
                        '\ttemplate <typename T> struct unordered_map { };\n'
                        '\ttemplate <typename T> struct unordered_multimap { };\n'
                        '\ttemplate <typename T> struct unordered_set { };\n'
                        '\ttemplate <typename T> struct unordered_multiset { };\n'
                        '}\n\n'
                        )
        #f.write(std_template)
        f.write(
            '#define WIN32\n'
            '\n'
            '#include <vector>\n'
            '#include <set>\n'
            '#include <map>\n'
            '#include <string>\n'
            '#include <string_view>\n'
            '\n'
        )
        #std_include = ('#include <vector>\n\n')
        #f.write(std_include)
        for file in collected_files:
            f.write(f'#include "{os.path.abspath(file)}"\n')

    #cached_file = os.path.abspath(normalize_path(f'{codegen_directory}/Codegen/Codegen/AllIncludes.cxx'))

    #preprocess_cpp(cached_file_raw, cached_file)
    #if not os.path.exists(cached_file):
    #    raise Exception(f'Failed to create file: {cached_file}')
    #os.remove(cached_file)
    #os.rename(cached_file_raw, cached_file)

    print(f'Parsing header file: {cached_file}\n')

    code_structures: CodeStructure = parse_header_file(cached_file)
    if code_structures.classes:
        print(f'File: {cached_file}\n')
        #for class_obj in code_structures.classes:
        #    print(class_obj.to_string(0))

    codegen_dir = normalize_path(codegen_directory + '/Codegen/Codegen') # double "Codegen" for cmake pretty include
    print(f'Codegen directory: {codegen_dir}')

    print('Remove old generated files...')
    # delete old files
    for file in glob(f'{codegen_dir}/*.hpp'):
        os.remove(file)

    print('Generate new files...')

    print('Count of classes:', len(code_structures.classes))
    print('Count of enums:', len(code_structures.enums))

    generate_classes_code(codegen_dir, code_structures.classes)
    generate_enums_code(codegen_dir, code_structures.enums)

    return True


if __name__ == "__main__":
    print("Start codegen.py... Codegen directory: ", codegen_directory)
    print("Repo path: ", get_repo_path())

    lib_path = os.path.join(os.path.dirname(clang.cindex.__file__), 'native')
    is_unix = sys.platform.startswith('linux') or sys.platform.startswith('darwin')
    lib_file = ''

    if is_unix:
        lib_file = os.path.join(lib_path, 'libclang.so')
    else:
        lib_file = os.path.join(lib_path, 'libclang.dll')
    
    lib_file = os.path.join(lib_path, lib_file)

    # check file exists
    if not os.path.exists(lib_file):
        print(f'libclang not found: {lib_file}')
        if is_unix:
            print("Try to install libclang, e.g. 'pip install libclang'.")
        sys.exit(1)

    print(f'Using libclang: {lib_file}')
    clang.cindex.Config.set_library_file(lib_file)

    if not main():
        input()
    print('end script...')