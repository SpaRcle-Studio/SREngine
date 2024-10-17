import sys, os, subprocess
from glob import glob
import clang.cindex

def normalize_path(path):
    """Нормализует слеши в путях для различных ОС."""
    return os.path.normpath(path)


class Property:
    def __init__(self, name, type_name):
        self.name = name
        self.type_name = type_name
        self.default_value = None

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
    def __init__(self, name):
        self.name = name
        self.variant = ''
        self.count = 0

class Class:
    def __init__(self, name, namespaces):
        self.name = name
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
    if raw_comment and "/// @property" in raw_comment:
        return True
    return False

def is_method_comment(node):
    """Извлекаем комментарий, если он есть."""
    raw_comment = node.raw_comment
    if raw_comment and "/// @method" in raw_comment:
        return True
    return False

def extract_property_type(variable_node):
    if variable_node.type.spelling:
        return variable_node.type.spelling
    return 'Unknown'

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


def parse_tree(deep, parent_node, code_structure, namespaces):
    try:
        if parent_node.kind == clang.cindex.CursorKind.FUNCTION_DECL and parent_node.is_definition():
            if parent_node.spelling.startswith('sr_detail_reflector_'):
                all_found = 0
                name = ''
                variant = ''
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
                                            print(child2.kind, child2.spelling)
                                            if child2.kind == clang.cindex.CursorKind.DECL_REF_EXPR:
                                                count = int(child2.spelling)
                                                all_found += 1
                                                break
                                        break
                                    if variable_name == 'CODEGEN_ENUM_NAME':
                                        # extract const char* value
                                        for child2 in child.get_children():
                                            if child2.kind == clang.cindex.CursorKind.DECL_REF_EXPR:
                                                name = child2.spelling
                                                all_found += 1
                                                break
                                        break

                    print(f'Found enum: {name} Variant: {variant} Count: {count}')
                    if all_found == 3:
                        break

            return

        if parent_node.kind == clang.cindex.CursorKind.CLASS_DECL and parent_node.is_definition():
            if not has_static_function(parent_node, 'GetMetaStatic'):
                return

            # Нашли класс
            class_name = parent_node.spelling
            class_obj = Class(class_name, namespaces)
            class_obj.path = parent_node.location.file.name

            # Перебираем все поля класса
            for child in parent_node.get_children():
                if child.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                    class_obj.inherited_classes.append(child.spelling)

                if child.kind == clang.cindex.CursorKind.FIELD_DECL and is_property_comment(child):
                    variable_name = child.spelling
                    #class_obj.add_variable(variable_name)
                    variable_name = child.spelling
                    variable_type = extract_property_type(child)
                    property_obj = Property(variable_name, variable_type)
                    class_obj.add_variable(property_obj)

                if child.kind == clang.cindex.CursorKind.CXX_METHOD and is_method_comment(child):
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
            new_namespace = namespaces + [parent_node.spelling]

        # Рекурсивный обход других узлов
        for child in parent_node.get_children():
            parse_tree(deep + 1, child, code_structure, new_namespace)



    except Exception as e:
        print(f'Error: {e}')


def get_repo_path():
    return normalize_path('../')

def parse_header_file(file_path):
    code_structure = CodeStructure()

    includes = [f'{get_repo_path()}/Engine/Core/inc',
                f'{get_repo_path()}/Engine/Core/libs/Utils/inc',
                f'{get_repo_path()}/Engine/Core/libs/Scripts/inc',
                f'{get_repo_path()}/Engine/Core/libs/Audio/inc',
                f'{get_repo_path()}/Engine/Core/libs/Physics/inc',
                f'{get_repo_path()}/Engine/Core/libs/Graphics/inc',
    ]

    # Передаем каждый путь как отдельный аргумент
    args = [f'-I{ os.path.abspath(normalize_path(inc))}' for inc in includes]
    args += ['-fsyntax-only', '-x', 'c++']

    index = clang.cindex.Index.create()
    translation_unit = index.parse(file_path, args=args)

    print('check diagnostics...')
    #if translation_unit.diagnostics:
    #    for diagnostic in translation_unit.diagnostics:
    #        print(diagnostic)

    # Проходим по узлам файла
    for node in translation_unit.cursor.get_children():
        parse_tree(0, node, code_structure, [])

    return code_structure


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
    f.write('\t' * tabs + f'auto&& value = static_cast<const {class_name}&>(obj);\n\n')

    for prop in class_obj.variables:
        f.write('\t' * tabs + f'if ((serializer.IsWriteDefaults() || !SR_UTILS_NS::IsDefault(value.{prop.name}))) {{\n')
        f.write('\t' * (tabs + 1) + f'static constexpr SR_UTILS_NS::SerializationId keyName_{prop.name} = SR_UTILS_NS::SerializationId::Create("{prop.name}");\n')
        f.write('\t' * (tabs + 1) + f'SR_UTILS_NS::Serialization::Save(serializer, value.{prop.name}, keyName_{prop.name});\n')
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
        f.write('\t' * tabs + f'{{\n')
        f.write('\t' * (tabs + 1) + f'static constexpr SR_UTILS_NS::SerializationId keyName_{prop.name} = SR_UTILS_NS::SerializationId::Create("{prop.name}");\n')
        f.write('\t' * (tabs + 1) + f'SR_UTILS_NS::Serialization::Load(deserializer, value.{prop.name}, keyName_{prop.name});\n')
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

    if len(class_obj.namespaces) > 0:
        f.write('\t' * tabs + f"using namespace {'::'.join(class_obj.namespaces)};\n\n")

    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name
    f.write('\t' * tabs + f'template<> struct SRClassMetaTemplate<{class_name}> final : public SR_UTILS_NS::SRClassMeta {{\n')
    tabs += 1

    f.write('\t' * tabs + f'static SRClassMetaTemplate<{class_name}>& Instance() {{ \n')
    f.write('\t' * (tabs + 1) + f'static SRClassMetaTemplate<{class_name}> instance;\n')
    f.write('\t' * (tabs + 1) + 'return instance;\n')
    f.write('\t' * tabs + '}\n\n')

    for prop in class_obj.variables:
        f.write('\t' * tabs + f'// {prop}\n')
        f.write('\t' * tabs + f'const {prop.type_name}& Get_{prop.name}({class_name}* pClass) {{ return pClass->{prop.name}; }}\n')
        f.write('\t' * tabs + f'void Set_{prop.name}({class_name}* pClass, const {prop.type_name}& value) {{ pClass->{prop.name} = value; }}\n\n')

    generate_class_meta_get_base_metas(f, class_structures, class_obj, tabs)

    generate_class_meta_save(f, class_obj, tabs)
    generate_class_meta_load(f, class_obj, tabs)

    f.write('\t' * tabs + f'SR_NODISCARD virtual std::string_view GetFactoryName() const noexcept override {{\n')
    f.write('\t' * (tabs + 1) + f'return {class_name}::GetClassStaticName();\n')
    f.write('\t' * tabs + '}\n\n')

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

def generate_classes_code(codegen_directory, class_structures):
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

    if not os.path.exists(codegen_directory):
        os.makedirs(codegen_directory)

    if not os.path.exists(codegen_directory):
        raise Exception(f'Failed to create directory: {codegen_directory}')

    for file_name, class_objs in file_map.items():
        full_path = os.path.normpath(f'{codegen_directory}/{file_name}.generated.hpp')
        with open(full_path, 'w', encoding='utf8') as f:
            f.write('// This file is generated by SpaRcle Studio code-generator ^_^\n\n')
            f.write(f'#ifndef SR_CODEGEN_{file_name.upper()}_HPP\n')
            f.write(f'#define SR_CODEGEN_{file_name.upper()}_HPP\n\n')
            for class_obj in class_objs:
                f.write(f'#include "{os.path.abspath(os.path.normpath(class_obj.path))}"\n\n')
                f.write(f'#include <Utils/TypeTraits/ClassDB.h>\n')
                f.write(f'#include <Utils/TypeTraits/SRClass.h>\n')
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

    codegen_directory = sys.argv[1:][0]
    cached_file = os.path.abspath(normalize_path(f'{codegen_directory}/Codegen/Codegen/AllIncludes.cxx'))

    # Получаем директорию из пути к файлу
    directory = os.path.dirname(cached_file)

    # Проверяем, существует ли директория, и создаем ее, если нет
    if not os.path.exists(directory):
        os.makedirs(directory)  # Создает директории рекурсивно

    with open(f'{cached_file}', 'w', encoding='utf8') as f:
        f.write('// This file is generated by SpaRcle Studio code-generator ^_^\n\n')
        std_template = ('namespace std {\n'
                        '\ttemplate <typename T> struct vector { };\n'
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
        f.write(std_template)
        #std_include = ('#include <vector>\n\n')
        #f.write(std_include)
        for file in collected_files:
            f.write(f'#include "{os.path.abspath(file)}"\n')

    print(f'Parsing header file: {cached_file}\n')

    code_structures: CodeStructure = parse_header_file(cached_file)
    if code_structures.classes:
        print(f'File: {cached_file}\n')
        for class_obj in code_structures.classes:
            print(class_obj.to_string(0))

    codegen_directory = sys.argv[1:][0]
    if not codegen_directory:
        print('codegen_directory is not set!')
        return False

    codegen_directory = normalize_path(codegen_directory + '/Codegen/Codegen') # double "Codegen" for cmake pretty include
    print(f'Codegen directory: {codegen_directory}')

    print('Remove old generated files...')
    # delete old files
    for file in glob(f'{codegen_directory}/*.hpp'):
        os.remove(file)

    print('Generate new files...')

    print('Count of classes:', len(code_structures.classes))
    print('Count of enums:', len(code_structures.enums))

    generate_classes_code(codegen_directory, code_structures.classes)

    return True


if __name__ == "__main__":
    lib_path = os.path.join(os.path.dirname(clang.cindex.__file__), 'native')
    is_unix = sys.platform.startswith('linux') or sys.platform.startswith('darwin')
    lib_file = ''

    if is_unix:
        lib_file = os.path.join(lib_path, 'libclang.so')
    else:
        lib_file = os.path.join(lib_path, 'libclang.dll')
    
    lib_file = os.path.join(lib_path, lib_file)
    clang.cindex.Config.set_library_file(lib_file)
    print(f'Using libclang: {lib_file}')

    # check file exists
    if not os.path.exists(lib_file):
        print(f'libclang not found: {lib_file}')
        sys.exit(1)

    if not main():
        input()
    print('end script...')