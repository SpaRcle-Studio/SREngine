import os
from glob import glob

import reflection_classes, sparcle_utils, clang_utils, codegen_context, logger_utils


def generate_all_includes_cxx(context: codegen_context.CodegenContext) -> str:
    collected_files = []

    include_dirs = [
        'Engine/Core/libs/Utils/inc/Utils',
        'Engine/Core/libs/Graphics/inc/Graphics',
        'Engine/Core/libs/Audio/inc/Audio',
        'Engine/Core/libs/Physics/inc/Physics',
        'Engine/Core/libs/Scripting/inc/Scripting',
        'Engine/Core/inc',
    ]

    if context.is_script:
        patterns = ['*.h', '*.hpp', '*.cpp']
        include_dirs.append(context.analyze_dir)
    else:
        patterns = ['*.h']

    # Преобразуем пути в include_dirs для разных ОС
    include_dirs = [sparcle_utils.normalize_path(dir) for dir in include_dirs]

    print(f'repo path: {os.path.abspath(context.analyze_dir)}')
    print('collect files...\n')

    for dir_path, _, _ in os.walk(context.analyze_dir):
        for pattern in patterns:
            for file in glob(os.path.join(dir_path, pattern)):
                normalized_file = sparcle_utils.normalize_path(file)
                if context.is_script:
                    collected_files.append(normalized_file)
                else:
                    if any((inc_dir in normalized_file) for inc_dir in include_dirs):
                        collected_files.append(normalized_file)

    print(f'collected files: {len(collected_files)}\n')

    cached_file = os.path.abspath(sparcle_utils.normalize_path(f'{context.codegen_dir}/AllIncludes.cxx'))

    # Получаем директорию из пути к файлу
    directory = os.path.dirname(cached_file)

    # Проверяем, существует ли директория, и создаем ее, если нет
    if not os.path.exists(directory):
        os.makedirs(directory)  # Создает директории рекурсивно

    with open(f'{cached_file}', 'w', encoding='utf8') as f:
        f.write(sparcle_utils.codegen_cpp_header_comment)
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
        for file in collected_files:
            f.write(f'#include "{os.path.abspath(file)}"\n')

    print(f'Parsing header file: {cached_file}\n')
    return cached_file


def generate_stub_vulkan_h(codegen_directory):
    vulkan_h = os.path.abspath(sparcle_utils.normalize_path(f'{codegen_directory}/vulkan/vulkan.h'))
    os.makedirs(os.path.dirname(vulkan_h), exist_ok=True)

    with open(vulkan_h, 'w', encoding='utf8') as f:
        f.write(sparcle_utils.codegen_cpp_header_comment)
        f.write('// Stub file for clang code analyzer.\n')

def generate_class_meta_properties(f, class_structures, class_obj, tabs):
    if len(class_obj.variables) == 0:
        return

    f.write('\t' * tabs + f'SR_NODISCARD virtual std::span<const SR_UTILS_NS::Reflection::Property> GetProperties() const noexcept final {{\n')
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

        f.write('\n' + '\t' * (tabs + 3) + f'.SetHasExplicitSetter({"true" if prop.setter else "false"})')
        f.write('\n' + '\t' * (tabs + 3) + f'.SetSetter(&SRClassMetaTemplate::Set_{prop.name})')
        f.write('\n' + '\t' * (tabs + 3) + f'.SetGetter(&SRClassMetaTemplate::Get_{prop.name})')
        f.write('\n' + '\t' * (tabs + 3) + f'.SetChangeCallback(&SRClassMetaTemplate::OnChange_{prop.name})')

        if prop.property_condition:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPropertyCondition(&SRClassMetaTemplate::IsPropertyActive_{prop.serialize_name})')

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

        for key, value in prop.custom_args.items():
            f.write('\n' + '\t' * (tabs + 4) + f'.SetCustomArg("{key}", "{value}")')

        if prop.no_header:
            f.write('\n' + '\t' * (tabs + 4) + f'.SetNoHeader()')

        if prop.not_null:
            f.write('\n' + '\t' * (tabs + 4) + f'.SetNotNull()')

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

def generate_class_meta_get_base_metas(f, class_structures, class_obj: reflection_classes.SpaRcleClass, tabs):
    if len(class_obj.inherited_classes) == 0:
        return

    f.write('\t' * tabs + f'SR_NODISCARD virtual std::span<const SRClassMeta*> GetBaseMetas() const noexcept final {{\n')

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


def generate_class_meta_save(f, class_obj: reflection_classes.SpaRcleClass, tabs):
    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name

    if len(class_obj.variables) == 0:
        if class_name == 'SpaRcle::Utils::Serializable':
            f.write('\t' * tabs + f'void Save(SR_UTILS_NS::ISerializer& serializer, const SR_UTILS_NS::Serializable& obj) const final {{\n')
            tabs += 1

            f.write('\t' * tabs + f'if (serializer.IsWriteVersion()) {{\n')
            f.write('\t' * (tabs + 1) + f'const uint64_t version = obj.GetMeta()->GetVersion();\n')
            f.write('\t' * (tabs + 1) + f'if (version != 0) {{\n')
            f.write('\t' * (tabs + 2) + f'static constexpr SR_UTILS_NS::SerializationId keyName_version = SR_UTILS_NS::SerializationId::Create("@version");\n')
            f.write('\t' * (tabs + 2) + f'SR_UTILS_NS::Serialization::Save(serializer, obj.GetMeta()->GetVersion(), keyName_version);\n')
            f.write('\t' * (tabs + 1) + f'}}\n')
            f.write('\t' * tabs + f'}}\n')

            tabs -= 1
            f.write('\t' * tabs + '}\n\n')

        return

    f.write('\t' * tabs + f'void Save(SR_UTILS_NS::ISerializer& serializer, const SR_UTILS_NS::Serializable& obj) const final {{\n')
    tabs += 1

    f.write('\t' * tabs + f'SR_UTILS_NS::SRClassMeta::Save(serializer, obj);\n\n')
    f.write('\t' * tabs + f'auto&& value = static_cast<{class_name}&>(const_cast<SR_UTILS_NS::Serializable&>(obj));\n\n')

    for prop in class_obj.variables:
        if prop.dontSave:
            continue

        if not prop.getter and prop.virtual:
            continue

        if prop.property_condition:
            f.write('\t' * tabs + f'if (IsPropertyActive_{prop.serialize_name}(&value)) {{\n')
        else:
            f.write('\t' * tabs + f'{{\n')

        if prop.getter:
            f.write('\t' * (tabs + 1) + f'auto&& propValue = value.{prop.getter}();\n')

            if prop.default_value:
                f.write('\t' * (tabs + 1) + f'if ((serializer.IsWriteDefaults() || propValue != GetDefault_{prop.serialize_name}())) {{\n')
            else:
                f.write('\t' * (tabs + 1) + f'if ((serializer.IsWriteDefaults() || !SR_UTILS_NS::IsDefault(propValue))) {{\n')

            f.write('\t' * (tabs + 2) + f'static constexpr SR_UTILS_NS::SerializationId keyName_{prop.serialize_name} = SR_UTILS_NS::SerializationId::Create("{prop.serialize_name}");\n')
            f.write('\t' * (tabs + 2) + f'SR_UTILS_NS::Serialization::Save(serializer, propValue, keyName_{prop.serialize_name});\n')

            f.write('\t' * (tabs + 1) + f'}}\n')
        else:
            if prop.default_value:
                f.write('\t' * (tabs + 1) + f'if ((serializer.IsWriteDefaults() || value.{prop.name} != GetDefault_{prop.serialize_name}())) {{\n')
            else:
                f.write('\t' * (tabs + 1) + f'if ((serializer.IsWriteDefaults() || !SR_UTILS_NS::IsDefault(value.{prop.name}))) {{\n')
            f.write('\t' * (tabs + 2) + f'static constexpr SR_UTILS_NS::SerializationId keyName_{prop.serialize_name} = SR_UTILS_NS::SerializationId::Create("{prop.serialize_name}");\n')
            f.write('\t' * (tabs + 2) + f'SR_UTILS_NS::Serialization::Save(serializer, value.{prop.name}, keyName_{prop.serialize_name});\n')
            f.write('\t' * (tabs + 1) + f'}}\n')

        f.write('\t' * tabs + f'}}\n')

    tabs -= 1
    f.write('\t' * tabs + '}\n\n')
    pass

def generate_class_meta_load(f, class_obj, tabs):
    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name

    if len(class_obj.variables) == 0:
        if class_name == 'SpaRcle::Utils::Serializable':
            f.write('\t' * tabs + f'bool Load(SR_UTILS_NS::IDeserializer& deserializer, SR_UTILS_NS::Serializable& obj) const final {{\n')
            tabs += 1

            f.write('\t' * (tabs) + f'static constexpr SR_UTILS_NS::SerializationId keyName_version = SR_UTILS_NS::SerializationId::Create("@version");\n')
            f.write('\t' * (tabs) + f'uint64_t version = 0;\n')
            f.write('\t' * (tabs) + f'uint64_t currentVersion = obj.GetMeta()->GetVersion();\n')
            f.write('\t' * (tabs) + f'SR_UTILS_NS::Serialization::Load(deserializer, version, keyName_version);\n')
            f.write('\t' * (tabs) + f'if (version != currentVersion) {{\n')
            f.write('\t' * (tabs + 1) + f'if (SR_UTILS_NS::MigrationManager::Instance().Migrate(deserializer, obj, version, currentVersion) == SR_UTILS_NS::MigrationResult::Fatal) {{\n')
            f.write('\t' * (tabs + 2) + f'return false;\n')
            f.write('\t' * (tabs + 1) + f'}}\n')
            f.write('\t' * (tabs) + f'}}\n')

            f.write('\t' * tabs + f'return true;\n')

            tabs -= 1
            f.write('\t' * tabs + '}\n\n')

        return

    f.write('\t' * tabs + f'bool Load(SR_UTILS_NS::IDeserializer& deserializer, SR_UTILS_NS::Serializable& obj) const final {{\n')
    tabs += 1

    f.write('\t' * tabs + f'if (!SR_UTILS_NS::SRClassMeta::Load(deserializer, obj)) {{\n')
    f.write('\t' * (tabs + 1) + f'return false;\n')
    f.write('\t' * tabs + f'}}\n\n')
    f.write('\t' * tabs + f'auto&& value = static_cast<{class_name}&>(obj);\n\n')

    for prop in class_obj.variables:
        if prop.dontLoad:
            continue

        if (not prop.setter or not prop.getter) and prop.virtual:
            continue

        if prop.load_condition:
            f.write('\t' * tabs + f'if (IsPropertyLoadAllowed_{prop.serialize_name}(&value)) {{\n')
        else:
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

    f.write('\t' * tabs + f'return true;\n')

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

    #f.write('\t' * (tabs + 0) + f'template <typename T> T static SetterSharedSRClassConvert(SR_UTILS_NS::SRClass* pSRClass) {{\n')
    #f.write('\t' * (tabs + 1) + f'if constexpr (SR_UTILS_NS::IsSharedPointerV<T>) {{\n')
    #f.write('\t' * (tabs + 2) + f'if (pSRClass) {{\n')
    #f.write('\t' * (tabs + 3) + f'return dynamic_cast<typename T::SharedPointerType*>(pSRClass);\n')
    #f.write('\t' * (tabs + 2) + f'}}\n')
    #f.write('\t' * (tabs + 1) + f'}}\n')
    #f.write('\t' * (tabs + 1) + f'return T();\n')
    #f.write('\t' * (tabs + 0) + f'}}\n\n')

    for prop in class_obj.variables:
        if not prop.default_value:
            continue
        f.write('\t' * tabs + f'// default value for \"{prop}\"\n')
        f.write('\t' * tabs + f'static auto GetDefault_{prop.serialize_name}() {{ return {prop.default_value}; }}\n\n')

    for prop in class_obj.variables:
        if not prop.property_condition:
            continue
        f.write('\t' * tabs + f'static auto IsPropertyActive_{prop.serialize_name}(SR_UTILS_NS::SRClass* pClass) {{\n')
        f.write('\t' * (tabs + 1) + f'{class_name}& This = *dynamic_cast<{class_name}*>(pClass);\n')
        f.write('\t' * (tabs + 1) + f'return {prop.property_condition};\n')
        f.write('\t' * tabs + f'}}\n\n')

    for prop in class_obj.variables:
        if not prop.load_condition:
            continue
        f.write('\t' * tabs + f'static auto IsPropertyLoadAllowed_{prop.serialize_name}(SR_UTILS_NS::SRClass* pClass) {{\n')
        f.write('\t' * (tabs + 1) + f'{class_name}& This = *dynamic_cast<{class_name}*>(pClass);\n')
        f.write('\t' * (tabs + 1) + f'return {prop.load_condition};\n')
        f.write('\t' * tabs + f'}}\n\n')

    #for prop in class_obj.variables:
    #    f.write('\t' * tabs + f'// {prop}\n')
    #    f.write('\t' * tabs + f'const {prop.type_name}& Get_{prop.name}({class_name}* pClass) {{ return pClass->{prop.name}; }}\n')
    #    f.write('\t' * tabs + f'void Set_{prop.name}({class_name}* pClass, const {prop.type_name}& value) {{ pClass->{prop.name} = value; }}\n\n')

    f.write('\t' * tabs + f'SR_NODISCARD bool IsAbstract() const noexcept final {{ return std::is_abstract_v<{class_name}>; }}\n\n')
    f.write('\t' * tabs + f'SR_NODISCARD bool IsHidden() const noexcept final {{ return { "true" if class_obj.hidden else "false" }; }}\n\n')

    if class_obj.version:
        f.write('\t' * tabs + f'SR_NODISCARD uint64_t GetVersionImpl() const noexcept final {{ return {class_obj.version}; }}\n\n')

    if class_obj.category:
        category_split = class_obj.category.split('.')
        f.write('\t' * tabs + f'SR_NODISCARD std::span<const SR_UTILS_NS::StringAtom> GetCategory() const noexcept final {{\n')
        f.write('\t' * (tabs + 1) + f'static std::array<const SR_UTILS_NS::StringAtom, {len(category_split)}> categories {{ ')
        for category in category_split:
            f.write(f'"{category}", ')
        f.write('};\n')
        f.write('\t' * (tabs + 1) + f'return categories;\n')
        f.write('\t' * tabs + '}\n\n')

    #######################################
    if class_obj.inspector:
        f.write('\t' * tabs + f'SR_NODISCARD SR_UTILS_NS::StringAtom GetInspectorName() const noexcept final {{ \n')
        f.write('\t' * (tabs + 1) + f'static const SR_UTILS_NS::StringAtom id = "{class_obj.inspector}";\n')
        f.write('\t' * (tabs + 1) + f'return id;\n')
        f.write('\t' * tabs + '}\n\n')
    #######################################

    generate_class_meta_get_base_metas(f, class_structures, class_obj, tabs)
    generate_class_meta_properties(f, class_structures, class_obj, tabs)

    #has_serializable_fields = len(class_obj.variables) > 0
    #f.write('\t' * tabs + f'SR_NODISCARD virtual bool HasSerializableFields() const noexcept final {{\n')
    #f.write('\t' * (tabs + 1) + f'for (auto&& pBaseMeta : GetBaseMetas()) {{\n')
    #f.write('\t' * (tabs + 2) + f'if (pBaseMeta->HasSerializableFields()) {{\n')
    #f.write('\t' * (tabs + 3) + f'return true;\n')
    #f.write('\t' * (tabs + 2) + f'}}\n')
    #f.write('\t' * (tabs + 1) + f'}}\n')
    #f.write('\t' * (tabs + 1) + f'return { "true" if has_serializable_fields else "false" };\n')
    #f.write('\t' * tabs + '}\n\n')

    generate_class_meta_save(f, class_obj, tabs)
    generate_class_meta_load(f, class_obj, tabs)

    f.write('\t' * tabs + f'SR_NODISCARD virtual SR_UTILS_NS::StringAtom GetFactoryName() const noexcept final {{\n')
    f.write('\t' * (tabs + 1) + f'return {class_name}::GetClassStaticName();\n')
    f.write('\t' * tabs + '}\n\n')

    f.write('\t' * (tabs - 1) + f'private:\n')
    #f.write('\t' * tabs + f'static inline const bool SR_CODEGEN_REGISTER_FACTORY = SR_UTILS_NS::Factory::Instance().Register<{class_name}>();\n\n')

    f.write('\t' * tabs + f'/// Bindings for class {class_obj.name}\n')

    for property in class_obj.variables:
        f.write('\t' * tabs + f'static void Set_{property.name}(SR_UTILS_NS::SRClass* pClass, const SR_UTILS_NS::Reflection::Value& value) {{\n')
        f.write('\t' * (tabs + 1) + f'{class_name}* pClassImpl = dynamic_cast<{class_name}*>(pClass);\n')

        #f.write('\t' * (tabs + 1) + f'const decltype({class_name}::{property.name})* pData;\n')
        #f.write('\t' * (tabs + 1) + f'if (!value.Map(pData)) {{\n')
        #f.write('\t' * (tabs + 2) + f'return;\n')
        #f.write('\t' * (tabs + 1) + f'}}\n')

        bool_do_gen_setter = True
        if property.virtual:
            if not property.setter or not property.getter:
                f.write('\t' * (tabs + 1) + f'SRHalt("Virtual property {property.name} must have getter and setter!");\n')
                f.write('\t' * (tabs + 1) + f'return;\n')
                bool_do_gen_setter = False
            else:
                f.write('\t' * (tabs + 1) + f'using Type = SR_UTILS_NS::RemoveQualifiersT<decltype(pClassImpl->{property.getter}())>;\n')
        else:
            f.write('\t' * (tabs + 1) + f'using Type = decltype({class_name}::{property.name});\n')

        if bool_do_gen_setter:
            #f.write('\t' * (tabs + 1) + f'if constexpr (SR_UTILS_NS::IsSharedPointerV<Type>) {{\n')
            #f.write('\t' * (tabs + 2) + f'auto&& pSRClassRef = value.TryCast<SR_UTILS_NS::SRClass*>();\n')
            #f.write('\t' * (tabs + 2) + f'if (!pSRClassRef) {{\n')
            #f.write('\t' * (tabs + 3) + f'SRHalt("Failed to cast value!");\n')
            #f.write('\t' * (tabs + 3) + f'return;\n')
            #f.write('\t' * (tabs + 2) + f'}}\n')
            #f.write('\t' * (tabs + 2) + f'auto&& pSRClass = const_cast<SR_UTILS_NS::SRClass*>(*pSRClassRef);\n')
            #if property.setter:
            #    f.write('\t' * (tabs + 2) + f'pClassImpl->{property.setter}(SetterSharedSRClassConvert<Type>(pSRClass));\n')
            #else:
            #    f.write('\t' * (tabs + 2) + f'pClassImpl->{property.name} = SetterSharedSRClassConvert<Type>(pSRClass);\n')
            #f.write('\t' * (tabs + 1) + f'}} else {{\n')

            if property.virtual:
                f.write('\t' * (tabs + 1) + f'auto&& pData = value.TryCast<Type>();\n')
                f.write('\t' * (tabs + 1) + f'if (!pData) {{\n')
                f.write('\t' * (tabs + 2) + f'SRHalt("Failed to cast value!");\n')
                f.write('\t' * (tabs + 2) + f'return;\n')
                f.write('\t' * (tabs + 1) + f'}}\n')

                f.write('\t' * (tabs + 1) + f'pClassImpl->{property.setter}(std::move(*pData));\n')
            else:
                f.write('\t' * (tabs + 1) + f'auto&& pData = value.TryCast<Type>();\n')
                f.write('\t' * (tabs + 1) + f'if (!pData) {{\n')
                f.write('\t' * (tabs + 2) + f'SRHalt("Failed to cast value!");\n')

                f.write('\t' * (tabs + 2) + f'return;\n')
                f.write('\t' * (tabs + 1) + f'}}\n')

                if property.setter:
                    f.write('\t' * (tabs + 1) + f'pClassImpl->{property.setter}(std::move(*pData));\n')
                else:
                    f.write('\t' * (tabs + 1) + f'pClassImpl->{property.name} = std::move(*pData);\n')

            #f.write('\t' * (tabs + 1) + f'}}\n')

        f.write('\t' * tabs + f'}}\n')

        # =================================== getter ===================================

        f.write('\t' * tabs + f'static SR_UTILS_NS::Reflection::Value Get_{property.name}(SR_UTILS_NS::SRClass* pClass) {{\n')
        f.write('\t' * (tabs + 1) + f'{class_name}* pClassImpl = dynamic_cast<{class_name}*>(pClass);\n')
        if property.getter:
            f.write('\t' * (tabs + 1) + f'auto&& value = pClassImpl->{property.getter}();\n')

            #f.write('\t' * (tabs + 1) + f'if constexpr (SR_UTILS_NS::IsSharedPointerV<decltype(value)>) {{\n')
            #f.write('\t' * (tabs + 2) + f'return SR_UTILS_NS::Reflection::Value::TryCreateSRClass(value);\n')
            #f.write('\t' * (tabs + 1) + f'}} else ')

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
            #f.write('\t' * (tabs + 1) + f'if constexpr (SR_UTILS_NS::IsSharedPointerV<decltype(pClassImpl->{property.name})>) {{\n')
            #f.write('\t' * (tabs + 2) + f'return SR_UTILS_NS::Reflection::Value::TryCreateSRClass(pClassImpl->{property.name});\n')
            #f.write('\t' * (tabs + 1) + f'}}\n')

            if property.read_only:
                f.write('\t' * (tabs + 1) + f'return SR_UTILS_NS::Reflection::Value::CreateCRef(pClassImpl->{property.name});\n')
            else:
                f.write('\t' * (tabs + 1) + f'return SR_UTILS_NS::Reflection::Value::CreateRef(pClassImpl->{property.name});\n')


        f.write('\t' * tabs + f'}}\n')

        f.write('\t' * tabs + f'static void OnChange_{property.name}(SR_UTILS_NS::SRClass* pClass) {{\n')
        if property.change_callback:
            f.write('\t' * (tabs + 1) + f'{class_name}* pClassImpl = dynamic_cast<{class_name}*>(pClass);\n')
            f.write('\t' * (tabs + 1) + f'pClassImpl->{property.change_callback}();\n')
        f.write('\t' * tabs + f'}}\n')

        f.write('\n')

    tabs -= 1
    f.write('\t' * tabs + '};\n\n')

    f.write(f'\t' * tabs + f'extern "C" SR_CODEGEN_DLL_API_EXPORT void RegisterClassMeta_{class_obj.name}() {{\n')
    f.write(f'\t' * (tabs + 1) + f'SR_UTILS_NS::Factory::Instance().Register<{class_name}>();\n')
    f.write(f'\t' * tabs + f'}}\n\n')

    f.write(f'\t' * tabs + f'extern "C" SR_CODEGEN_DLL_API_EXPORT void UnregisterClassMeta_{class_obj.name}() {{\n')
    f.write(f'\t' * (tabs + 1) + f'SR_UTILS_NS::Factory::Instance().Unregister<{class_name}>();\n')
    f.write(f'\t' * tabs + f'}}\n\n')

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
        f.write(sparcle_utils.codegen_cpp_header_comment)
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
        f.write(sparcle_utils.codegen_cpp_header_comment)
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

                f.write(sparcle_utils.codegen_cpp_header_comment)
                f.write(f'#ifndef SR_CODEGEN_ENUM_{caps_enum_name}_HPP\n')
                f.write(f'#define SR_CODEGEN_ENUM_{caps_enum_name}_HPP\n\n')

                f.write(f'#include \"{enum_obj.source_path}\"\n\n')

                f.write(f'#include <Codegen/Enums.generated.hpp>\n\n')

                namespace_str = ''
                if len(enum_obj.namespaces) > 0:
                    namespace_str = '::'.join(enum_obj.namespaces)

                if len(namespace_str) > 0:
                    namespace_str += '::'

#                f.write(
#f'''
#SR_UTILS_NS::EnumReflector* SR_CODEGEN_ALLOCATE_ENUM_REFLECTOR({namespace_str}{enum_obj.name});
#
#SR_UTILS_NS::EnumReflector* SR_CODEGEN_ALLOCATE_ENUM_REFLECTOR({namespace_str}{enum_obj.name}) {{
#    static {enum_obj.type} _detail_sval;
#    _detail_sval = 0;
#    struct _detail_val_t
#    {{
#        _detail_val_t(const _detail_val_t& rhs)
#            : _val(rhs)
#        {{ _detail_sval = _val + 1; }}
#
#        _detail_val_t({enum_obj.type} val) /** NOLINT(google-explicit-constructor) */
#            : _val(val)
#        {{  _detail_sval = _val + 1; }}
#
#        _detail_val_t()
#            : _val(_detail_sval)
#        {{ _detail_sval = _val + 1; }}
#
#        _detail_val_t& operator=(const _detail_val_t&) {{ return *this; }}
#
#        _detail_val_t& operator=({enum_obj.type}) {{ return *this; }}
#        operator {enum_obj.type}() const {{ return _val; }}
#        {enum_obj.type} _val;
#    }} {enum_obj.va_args};
#
#    const {enum_obj.type} _detail_vals[] = {{ {enum_obj.va_args} }};
#
#    return new SR_UTILS_NS::EnumReflector(SR_UTILS_NS::EnumVariant::{enum_obj.variant}, _detail_vals, sizeof(_detail_vals) / sizeof({enum_obj.type}), "{enum_obj.name}", "({enum_obj.va_args})");
#}}\n
#'''
#                )

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


def generate_meta_module_core_code(logger: logger_utils.Logger, context: codegen_context.CodegenContext, class_structures):
    logger.log_info(f'Generating meta module core code to {context.codegen_dir}...')

    full_path = os.path.normpath(f'{context.codegen_dir}/SpaRcleModule{context.module_name}Core.generated.hpp')
    with open(full_path, 'w', encoding='utf8') as f:
        f.write(sparcle_utils.codegen_cpp_header_comment)

        f.write(f'#ifndef SR_CODEGEN_SPARCLE_MODULE_{context.module_name.upper()}_CORE_HPP\n')
        f.write(f'#define SR_CODEGEN_SPARCLE_MODULE_{context.module_name.upper()}_CORE_HPP\n\n')

        f.write(f'#include <Utils/stdInclude.h>\n\n')

        f.write(f'namespace Codegen {{\n')

        tabs = 1

        for class_obj in class_structures:
            if not class_obj.is_help_source:
                f.write(f'{tabs * "\t"}extern "C" SR_CODEGEN_DLL_API_IMPORT void RegisterClassMeta_{class_obj.name}();\n')
                f.write(f'{tabs * "\t"}extern "C" SR_CODEGEN_DLL_API_IMPORT void UnregisterClassMeta_{class_obj.name}();\n')

        ############################### register #################################
        f.write(f'\n{tabs * "\t"}void RegisterModule_{context.module_name}() {{\n')

        tabs += 1

        for class_obj in class_structures:
            if not class_obj.is_help_source:
                f.write(f'{tabs * "\t"}RegisterClassMeta_{class_obj.name}();\n')

        tabs -= 1

        f.write(f'{tabs * "\t"}}}\n')

        ############################### unregister #################################
        f.write(f'\n{tabs * "\t"}void UnregisterModule_{context.module_name}() {{\n')

        tabs += 1

        for class_obj in class_structures:
            if not class_obj.is_help_source:
                f.write(f'{tabs * "\t"}UnregisterClassMeta_{class_obj.name}();\n')

        tabs -= 1

        f.write(f'{tabs * "\t"}}}\n')

        f.write(f'}}\n\n')

        f.write(f'#if defined(SR_WIN32) && defined(SR_ENGINE_SCRIPT_API_MODE)')
        f.write(f'''
    bool __stdcall DllMain(void* hModule, unsigned long ulReasonForCall, void* lpReserved) {{
        switch (ulReasonForCall) {{
        case 1: /// DLL_PROCESS_ATTACH
            Codegen::RegisterModule_{context.module_name}();
            break;
        case 0: /// DLL_PROCESS_DETACH
            Codegen::UnregisterModule_{context.module_name}();
            break;
        }}
        return true;
    }}\n''')

        f.write('#endif\n\n')

        f.write(f'#if defined(SR_LINUX) && defined(SR_ENGINE_SCRIPT_API_MODE)')
        f.write(f'''
    __attribute__((constructor))
    void OnLibraryLoad() {{
        Codegen::RegisterModule_{context.module_name}();
    }}
    
    __attribute__((destructor))
    void OnLibraryUnload() {{
        Codegen::UnregisterModule_{context.module_name}();
    }}\n''')
        f.write('#endif\n\n')

        f.write(f'#endif // SR_CODEGEN_SPARCLE_MODULE_{context.module_name.upper()}_CORE_HPP\n')


def generate_classes_code(logger: logger_utils.Logger, context: codegen_context.CodegenContext, class_structures):
    logger.log_info(f'Generating classes code...')

    generate_meta_module_core_code(logger, context, class_structures)

    file_map = {}
    for class_obj in class_structures:
        if not class_obj.path:
            raise Exception(f'Path is not set for class: {class_obj.name}')

        file_name = class_obj.path.replace('\\', '/')
        file_name = str(file_name.split('/')[-1]) # get file name

        if os.path.exists(file_name):
            raise Exception(f'Absolute path is not allowed: {file_name}, source: {class_obj.path}')

        file_name, ext = os.path.splitext(file_name)

        if file_name not in file_map:
            file_map[file_name] = []
            file_map[file_name].append(class_obj)
        else:
            file_map[file_name].append(class_obj)

    if not os.path.exists(context.codegen_dir):
        os.makedirs(context.codegen_dir)

    if not os.path.exists(context.codegen_dir):
        raise Exception(f'Failed to create directory: {context.codegen_dir}')

    for file_name, class_objs in file_map.items():
        has_non_help_source = False
        for class_obj in class_objs:
            if not class_obj.is_help_source:
                has_non_help_source = True
                break

        if not has_non_help_source:
            continue

        full_path = os.path.normpath(f'{context.codegen_dir}/{file_name}.generated.hpp')
        with open(full_path, 'w', encoding='utf8') as f:
            f.write(sparcle_utils.codegen_cpp_header_comment)
            f.write(f'#ifndef SR_CODEGEN_{file_name.upper()}_HPP\n')
            f.write(f'#define SR_CODEGEN_{file_name.upper()}_HPP\n\n')
            for class_obj in class_objs:
                if class_obj.is_help_source:
                    continue

                _, ext = os.path.splitext(class_obj.path)

                if ext == '.h':
                    f.write(f'#include "{os.path.abspath(os.path.normpath(class_obj.path))}"\n\n')

                f.write(f'#include <Utils/Reflection/Property.h>\n')
                f.write(f'#include <Utils/TypeTraits/ClassDB.h>\n')
                f.write(f'#include <Utils/TypeTraits/SRClass.h>\n')
                f.write(f'#include <Utils/TypeTraits/Factory.h>\n')
                f.write(f'#include <Utils/TypeTraits/SRClassMeta.h>\n')
                f.write(f'#include <Utils/Serialization/MigrationManager.h>\n\n')

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