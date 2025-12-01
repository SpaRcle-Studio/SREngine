import os
from glob import glob

import reflection_utils
import sparcle_utils
import codegen_context
import logger_utils


def generate_stub_vulkan_h(codegen_directory):
    vulkan_h = os.path.abspath(sparcle_utils.normalize_path(f'{codegen_directory}/vulkan/vulkan.h'))
    os.makedirs(os.path.dirname(vulkan_h), exist_ok=True)

    with open(vulkan_h, 'w', encoding='utf8') as f:
        f.write(sparcle_utils.codegen_cpp_header_comment)
        f.write('// Stub file for clang code analyzer.\n')

def generate_class_meta_for_each_sr_class(f, class_structures, class_obj, tabs):
    is_sr_class = class_obj.name == 'SRClass'
    if len(class_obj.variables) == 0 and not is_sr_class:
        return

    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name

    f.write('\t' * tabs + f'void ForEachSRClass(SpaRcle::Utils::SRClass& srClass, const SR_HTYPES_NS::Function<void(SpaRcle::Utils::SRClass&)>& function) const noexcept final {{\n')

    if is_sr_class:
        f.write('\t' * (tabs + 1) + f'function(srClass);\n')
    else:
        f.write('\t' * (tabs + 1) + f'SpaRcle::Utils::SRClassMeta::ForEachSRClass(srClass, function);\n\n')

        f.write('\t' * (tabs + 1) + f'SR_MAYBE_UNUSED auto&& object = static_cast<{class_name}&>(srClass);\n\n')

        for prop in class_obj.variables:
            if prop.virtual:
                continue
            f.write('\t' * (tabs + 1) + f'SpaRcle::Utils::Reflection::ForEachSRClass(object.{prop.name}, function);\n')

    f.write('\t' * tabs + '}\n\n')


def generate_class_meta_properties(f, class_structures, class_obj, tabs):
    if len(class_obj.variables) == 0:
        return

    f.write('\t' * tabs + f'SR_NODISCARD virtual std::span<const SpaRcle::Utils::Reflection::Property> GetProperties() const noexcept final {{\n')
    f.write('\t' * (tabs + 1) + f'static const std::array<const SpaRcle::Utils::Reflection::Property, {len(class_obj.variables)}> properties {{ \n')

    for prop in class_obj.variables:
        f.write('\t' * (tabs + 2) + f'SpaRcle::Utils::Reflection::Property()')
        f.write('\n' + '\t' * (tabs + 3) + f'.SetName("{prop.name}")')
        f.write('\n' + '\t' * (tabs + 3) + f'.SetSerializeName("{prop.serialize_name}")')

        if prop.private:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPublicity(SpaRcle::Utils::PropertyPublicity::Private)')
        elif prop.hidden and prop.read_only:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPublicity(SpaRcle::Utils::PropertyPublicity::HiddenReadOnly)')
        elif prop.hidden:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPublicity(SpaRcle::Utils::PropertyPublicity::Hidden)')
        elif prop.read_only:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPublicity(SpaRcle::Utils::PropertyPublicity::ReadOnly)')
        # else:
        #     f.write('\n' + '\t' * (tabs + 3) + f'.SetPublicity(SpaRcle::Utils::PropertyPublicity::Public)')

        if prop.setter:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetHasExplicitSetter({"true" if prop.setter else "false"})')

        f.write('\n' + '\t' * (tabs + 3) + f'.SetSetter(&SRClassMetaTemplate::Set_{prop.name})')
        f.write('\n' + '\t' * (tabs + 3) + f'.SetGetter(&SRClassMetaTemplate::Get_{prop.name})')

        if prop.change_callback:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetChangeCallback(&SRClassMetaTemplate::OnChange_{prop.name})')

        if prop.virtual:
            f.write('\n' + '\t' * (tabs + 3) + f'.CheckSRClass<decltype(DeclTypeStub()->{prop.getter}())>()')
        else:
            f.write('\n' + '\t' * (tabs + 3) + f'.CheckSRClass<decltype({class_obj.name}::{prop.name})>()')

        if prop.property_condition:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetPropertyCondition(&SRClassMetaTemplate::IsPropertyActive_{prop.serialize_name})')

        default_value = f'decltype({class_obj.name}::{prop.name})()'
        if prop.default_value:
            default_value = f'decltype({class_obj.name}::{prop.name})(GetDefault_{prop.serialize_name}())'
        elif prop.virtual:
            if prop.getter:
                default_value = f'SpaRcle::Utils::RemoveQualifiersT<decltype(DeclTypeStub()->{prop.getter}())>()'
            else:
                default_value = None

        if default_value:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetDefaultValue(SpaRcle::Utils::Reflection::Value::Create({default_value}))')

        if prop.reset_value:
            f.write('\n' + '\t' * (tabs + 3) + f'.SetResetValue(SpaRcle::Utils::Reflection::Value::Create({prop.reset_value}))')

        # editor params

        f.write('\n' + '\t' * (tabs + 3) + f'.SetEditorParams(SpaRcle::Utils::Reflection::EditorPropertyParams()')

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

def generate_class_meta_get_base_metas(f, class_structures, class_obj: reflection_utils.SpaRcleClass, tabs):
    if len(class_obj.inherited_classes) == 0:
        return

    f.write('\t' * tabs + 'SR_NODISCARD virtual std::span<const SRClassMeta*> GetBaseMetas() const noexcept final {\n')

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
        f.write('\t' * (tabs + 2) + f'{inherited_class_formated}::GetMetaStatic(),' + '\n')

    f.write('\t' * (tabs + 1) + '};\n')
    f.write('\t' * (tabs + 1) + 'return baseMetas;\n')
    f.write('\t' * tabs + '}\n\n')


def generate_class_meta_save(f, class_obj: reflection_utils.SpaRcleClass, tabs):
    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name

    if len(class_obj.variables) == 0:
        if class_name == 'SpaRcle::Utils::Serializable':
            f.write('\t' * tabs + f'void Save(SpaRcle::Utils::ISerializer& serializer, const SpaRcle::Utils::Serializable& obj) const final {{\n')
            tabs += 1

            f.write('\t' * tabs + f'if (serializer.IsWriteVersion()) {{\n')
            f.write('\t' * (tabs + 1) + f'const uint64_t version = obj.GetMeta()->GetVersion();\n')
            f.write('\t' * (tabs + 1) + f'if (version != 0) {{\n')
            f.write('\t' * (tabs + 2) + f'static const SpaRcle::Utils::SerializationId keyName_version = SpaRcle::Utils::SerializationId::CreateFromString("@version");\n')
            f.write('\t' * (tabs + 2) + f'SpaRcle::Utils::Serialization::Save(serializer, obj.GetMeta()->GetVersion(), keyName_version);\n')
            f.write('\t' * (tabs + 1) + f'}}\n')
            f.write('\t' * tabs + f'}}\n')

            tabs -= 1
            f.write('\t' * tabs + '}\n\n')

        return

    f.write('\t' * tabs + f'void Save(SpaRcle::Utils::ISerializer& serializer, const SpaRcle::Utils::Serializable& obj) const final {{\n')
    tabs += 1

    f.write('\t' * tabs + f'SpaRcle::Utils::SRClassMeta::Save(serializer, obj);\n\n')
    f.write('\t' * tabs + f'auto&& value = static_cast<{class_name}&>(const_cast<SpaRcle::Utils::Serializable&>(obj));\n\n')

    for prop in class_obj.variables:
        if prop.dontSave:
            continue

        if not prop.getter and prop.virtual:
            continue

        base_condition_str = 'serializer.IsWriteDefaults()'
        can_save_conditions = []

        if len(prop.dont_save_tags) > 0:
            f.write('\t' * tabs + f'const static std::set<SpaRcle::Utils::StringAtom> {prop.serialize_name}_dontSaveTags = {{')
            for tag in prop.dont_save_tags:
                f.write(f'"{tag}", ')
            f.write('};\n')
            can_save_conditions.append(f'serializer.CanSaveByTags({prop.serialize_name}_dontSaveTags)')

        if prop.property_condition:
            can_save_conditions.append(f'IsPropertyActive_{prop.serialize_name}(&value)')

        if len(can_save_conditions) == 0:
            f.write('\t' * tabs + f'{{\n')
        else:
            cond_str = " && ".join(can_save_conditions)
            f.write('\t' * tabs + f'if ({cond_str}) {{\n')

        if prop.getter:
            f.write('\t' * (tabs + 1) + f'auto&& propValue = value.{prop.getter}();\n')

            if prop.default_value:
                f.write('\t' * (tabs + 1) + f'if (({base_condition_str} || propValue != GetDefault_{prop.serialize_name}())) {{\n')
            else:
                f.write('\t' * (tabs + 1) + f'if (({base_condition_str} || !SpaRcle::Utils::IsDefault(propValue))) {{\n')

            f.write('\t' * (tabs + 2) + f'static const SpaRcle::Utils::SerializationId keyName_{prop.serialize_name} = SpaRcle::Utils::SerializationId::CreateFromString("{prop.serialize_name}");\n')
            f.write('\t' * (tabs + 2) + f'SpaRcle::Utils::Serialization::Save(serializer, propValue, keyName_{prop.serialize_name});\n')

            f.write('\t' * (tabs + 1) + f'}}\n')
        else:
            if prop.default_value:
                f.write('\t' * (tabs + 1) + f'if (({base_condition_str} || value.{prop.name} != GetDefault_{prop.serialize_name}())) {{\n')
            else:
                f.write('\t' * (tabs + 1) + f'if (({base_condition_str} || !SpaRcle::Utils::IsDefault(value.{prop.name}))) {{\n')
            f.write('\t' * (tabs + 2) + f'static const SpaRcle::Utils::SerializationId keyName_{prop.serialize_name} = SpaRcle::Utils::SerializationId::CreateFromString("{prop.serialize_name}");\n')
            f.write('\t' * (tabs + 2) + f'SpaRcle::Utils::Serialization::Save(serializer, value.{prop.name}, keyName_{prop.serialize_name});\n')
            f.write('\t' * (tabs + 1) + f'}}\n')

        f.write('\t' * tabs + f'}}\n')

    tabs -= 1
    f.write('\t' * tabs + '}\n\n')
    pass

def generate_class_meta_load(f, class_obj, tabs):
    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name

    if len(class_obj.variables) == 0:
        if class_name == 'SpaRcle::Utils::Serializable':
            f.write('\t' * tabs + 'bool Load(SpaRcle::Utils::IDeserializer& deserializer, SpaRcle::Utils::Serializable& obj) const final {\n')
            tabs += 1

            f.write('\t' * (tabs) + 'static const SpaRcle::Utils::SerializationId keyName_version = SpaRcle::Utils::SerializationId::CreateFromString("@version");\n')
            f.write('\t' * (tabs) + 'uint64_t version = 0;\n')
            f.write('\t' * (tabs) + 'uint64_t currentVersion = obj.GetMeta()->GetVersion();\n')
            f.write('\t' * (tabs) + 'SpaRcle::Utils::Serialization::Load(deserializer, version, keyName_version);\n')
            f.write('\t' * (tabs) + 'if (version != currentVersion) {\n')
            f.write('\t' * (tabs + 1) + 'if (SpaRcle::Utils::MigrationManager::Instance().Migrate(deserializer, obj, version, currentVersion) == SpaRcle::Utils::MigrationResult::Fatal) {\n')
            f.write('\t' * (tabs + 2) + 'return false;\n')
            f.write('\t' * (tabs + 1) + '}\n')
            f.write('\t' * (tabs) + '}\n')

            f.write('\t' * tabs + f'return true;\n')

            tabs -= 1
            f.write('\t' * tabs + '}\n\n')

        return

    f.write('\t' * tabs + 'bool Load(SpaRcle::Utils::IDeserializer& deserializer, SpaRcle::Utils::Serializable& obj) const final {\n')
    tabs += 1

    f.write('\t' * tabs + 'if (!SpaRcle::Utils::SRClassMeta::Load(deserializer, obj)) {\n')
    f.write('\t' * (tabs + 1) + 'return false;\n')
    f.write('\t' * tabs + '}\n\n')
    f.write('\t' * tabs + f'auto&& value = static_cast<{class_name}&>(obj);' + '\n\n')

    for prop in class_obj.variables:
        if prop.dontLoad:
            continue

        if (not prop.setter or not prop.getter) and prop.virtual:
            continue

        can_load_conditions = []

        if len(prop.dont_save_tags) > 0:
            f.write('\t' * tabs + f'const static std::set<SpaRcle::Utils::StringAtom> {prop.serialize_name}_dontLoadTags = {{')
            for tag in prop.dont_save_tags:
                f.write(f'"{tag}", ')
            f.write('};\n')
            can_load_conditions.append(f'deserializer.CanLoadByTags({prop.serialize_name}_dontLoadTags)')

        if prop.load_condition:
            can_load_conditions.append(f'IsPropertyLoadAllowed_{prop.serialize_name}(&value)')

        if len(can_load_conditions) == 0:
            f.write('\t' * tabs + f'{{\n')
        else:
            cond_str = " && ".join(can_load_conditions)
            f.write('\t' * tabs + f'if ({cond_str}) {{\n')

        f.write('\t' * (tabs + 1) + f'static const SpaRcle::Utils::SerializationId keyName_{prop.serialize_name} = SpaRcle::Utils::SerializationId::CreateFromString("{prop.serialize_name}");' + '\n')

        if prop.setter:
            if prop.getter:
                f.write('\t' * (tabs + 1) + f'using Type = SpaRcle::Utils::RemoveQualifiersT<decltype(value.{prop.getter}())>;' + '\n')
            elif prop.virtual:
                raise Exception(f'Virtual property {prop.name} must have getter!')
            else:
                f.write('\t' * (tabs + 1) + f'using Type = SpaRcle::Utils::RemoveQualifiersT<decltype(value.{prop.name})>;' + '\n')

            load_fn = f'SpaRcle::Utils::Serialization::Load(deserializer, propValue, keyName_{prop.serialize_name})'

            f.write('\t' * (tabs + 1) + 'Type propValue {};\n')

            if prop.default_value:
                f.write('\t' * (tabs + 1) + f'if (!{load_fn}) {{' + '\n')
                f.write('\t' * (tabs + 2) + f'propValue = GetDefault_{prop.serialize_name}();' + '\n')
                f.write('\t' * (tabs + 1) + '}\n')
            else:
                f.write('\t' * (tabs + 1) + f'{load_fn};' + '\n')

            f.write('\t' * (tabs + 1) + f'value.{prop.setter}(propValue);' + '\n')

        else:
            load_fn = f'SpaRcle::Utils::Serialization::Load(deserializer, value.{prop.name}, keyName_{prop.serialize_name})'
            if prop.default_value:
                f.write('\t' * (tabs + 1) + f'if (!{load_fn}) {{' + '\n')
                f.write('\t' * (tabs + 2) + f'value.{prop.name} = GetDefault_{prop.serialize_name}();' + '\n')
                f.write('\t' * (tabs + 1) + '}\n')
            else:
                f.write('\t' * (tabs + 1) + f'{load_fn};' + '\n')

        f.write('\t' * tabs + '}\n')

    f.write('\t' * tabs + 'return true;\n')

    tabs -= 1
    f.write('\t' * tabs + '}\n\n')
    pass


def generate_class_meta_clone(f, class_obj: reflection_utils.SpaRcleClass, tabs):
    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name

    f.write('\t' * tabs + f'void CloneTo(const SpaRcle::Utils::SRClass& src, SpaRcle::Utils::SRClass& dest) const noexcept final {{\n')
    tabs += 1

    f.write('\t' * tabs + f'SpaRcle::Utils::SRClassMeta::CloneTo(src, dest);\n\n')

    f.write('\t' * tabs + f'SR_MAYBE_UNUSED auto&& srcObject = const_cast<{class_name}&>(static_cast<const {class_name}&>(src));\n')
    f.write('\t' * tabs + f'SR_MAYBE_UNUSED auto&& destObject = static_cast<{class_name}&>(dest);\n\n')

    for prop in class_obj.variables:
        if prop.virtual and (not prop.setter or not prop.getter):
            continue

        if prop.getter:
            getter_code = f'srcObject.{prop.getter}()'
        else:
            getter_code = f'srcObject.{prop.name}'

        f.write('\t' * (tabs) + f'/// Clone property "{prop.name}"' + '\n')

        if prop.setter:
            f.write('\t' * (tabs) + f'SpaRcle::Utils::RemoveQualifiersT<decltype({getter_code})> clone_{prop.name};\n')
            f.write('\t' * (tabs) + f'SpaRcle::Utils::Reflection::CloneTo({getter_code}, clone_{prop.name});\n')
            f.write('\t' * (tabs) + f'destObject.{prop.setter}(std::move(clone_{prop.name}));\n')
        else:
            f.write('\t' * (tabs) + f'SpaRcle::Utils::Reflection::CloneTo({getter_code}, destObject.{prop.name});\n')

    tabs -= 1
    f.write('\t' * tabs + '}\n\n')


def generate_class_meta(f, context: codegen_context.CodegenContext, class_structures, class_obj, tabs, dll_export_macro):
    #if len(class_obj.inherited_classes) > 0:
    #    f.write('\t' * tabs + f'/// Include inherited classes.\n')
    #    for inherited_class in class_obj.inherited_classes:
    #        inherited_class_obj = None
    #        inherited_class_formated = inherited_class.split('::')[-1]
    #        for class_structure in class_structures:
    #            if class_structure.name == inherited_class_formated:
    #                inherited_class_obj = class_structure
    #                break

    #        if inherited_class_obj:
    #            f.write('\t' * tabs + f'#include "{os.path.abspath(os.path.normpath(inherited_class_obj.path))}"' + '\n')

    #    f.write('\n')

    f.write('\t' * tabs + 'namespace Codegen {\n')
    tabs += 1

    for i, namespace in enumerate(class_obj.namespaces):
        f.write('\t' * tabs + f'using namespace {"::".join(class_obj.namespaces[:i + 1])};' + '\n')

    if len(class_obj.namespaces) > 0:
        f.write('\n')

    class_name = '::'.join(class_obj.namespaces) + '::' + class_obj.name
    f.write('\t' * tabs + f'template<> struct SRClassMetaTemplate<{class_name}> final : public SpaRcle::Utils::SRClassMeta {{' + '\n')
    tabs += 1

    f.write('\t' * tabs + f'static SRClassMetaTemplate<{class_name}>& Instance() {{' + '\n')
    f.write('\t' * (tabs + 1) + f'static SRClassMetaTemplate<{class_name}> instance;' + '\n')
    f.write('\t' * (tabs + 1) + 'return instance;\n')
    f.write('\t' * tabs + '}\n\n')

    f.write('\t' * tabs + f'SR_NODISCARD {class_name}* DeclTypeStub() const noexcept {{ return nullptr; }}' + '\n\n')

    #f.write('\t' * (tabs + 0) + f'template <typename T> T static SetterSharedSRClassConvert(SpaRcle::Utils::SRClass* pSRClass) {{\n')
    #f.write('\t' * (tabs + 1) + f'if constexpr (SpaRcle::Utils::IsSharedPointerV<T>) {{\n')
    #f.write('\t' * (tabs + 2) + f'if (pSRClass) {{\n')
    #f.write('\t' * (tabs + 3) + f'return dynamic_cast<typename T::SharedPointerType*>(pSRClass);\n')
    #f.write('\t' * (tabs + 2) + f'}}\n')
    #f.write('\t' * (tabs + 1) + f'}}\n')
    #f.write('\t' * (tabs + 1) + f'return T();\n')
    #f.write('\t' * (tabs + 0) + f'}}\n\n')

    for prop in class_obj.variables:
        if not prop.default_value:
            continue
        f.write('\t' * tabs + f'// default value for "{prop}"' + '\n')
        f.write('\t' * tabs + f'static auto GetDefault_{prop.serialize_name}() {{ return {prop.default_value}; }}' + '\n\n')

    for prop in class_obj.variables:
        if not prop.property_condition:
            continue
        f.write('\t' * tabs + f'static auto IsPropertyActive_{prop.serialize_name}(SpaRcle::Utils::SRClass* pClass) {{' + '\n')
        f.write('\t' * (tabs + 1) + f'{class_name}& This = *dynamic_cast<{class_name}*>(pClass);' + '\n')
        f.write('\t' * (tabs + 1) + f'return {prop.property_condition};' + '\n')
        f.write('\t' * tabs + '}\n\n')

    for prop in class_obj.variables:
        if not prop.load_condition:
            continue
        f.write('\t' * tabs + f'static auto IsPropertyLoadAllowed_{prop.serialize_name}(SpaRcle::Utils::SRClass* pClass) {{' + '\n')
        f.write('\t' * (tabs + 1) + f'{class_name}& This = *dynamic_cast<{class_name}*>(pClass);' + '\n')
        f.write('\t' * (tabs + 1) + f'return {prop.load_condition};' + '\n')
        f.write('\t' * tabs + '}\n\n')

    #for prop in class_obj.variables:
    #    f.write('\t' * tabs + f'// {prop}\n')
    #    f.write('\t' * tabs + f'const {prop.type_name}& Get_{prop.name}({class_name}* pClass) {{ return pClass->{prop.name}; }}\n')
    #    f.write('\t' * tabs + f'void Set_{prop.name}({class_name}* pClass, const {prop.type_name}& value) {{ pClass->{prop.name} = value; }}\n\n')

    f.write('\t' * tabs + f'SR_NODISCARD bool IsAbstract() const noexcept final {{ return std::is_abstract_v<{class_name}>; }}' + '\n\n')
    f.write('\t' * tabs + f'SR_NODISCARD bool IsHidden() const noexcept final {{ return { "true" if class_obj.hidden else "false" }; }}' + '\n\n')

    if class_obj.version:
        f.write('\t' * tabs + f'SR_NODISCARD uint64_t GetVersionImpl() const noexcept final {{ return {class_obj.version}; }}' + '\n\n')

    if class_obj.category:
        category_split = class_obj.category.split('.')
        f.write('\t' * tabs + 'SR_NODISCARD std::span<const SpaRcle::Utils::StringAtom> GetCategory() const noexcept final {\n')
        f.write('\t' * (tabs + 1) + f'static std::array<const SpaRcle::Utils::StringAtom, {len(category_split)}> categories {{ ')
        for category in category_split:
            f.write(f'"{category}", ')
        f.write('};\n')
        f.write('\t' * (tabs + 1) + 'return categories;\n')
        f.write('\t' * tabs + '}\n\n')

    if class_obj.extension:
        f.write('\t' * tabs + 'SR_NODISCARD SpaRcle::Utils::StringAtom GetExtension() const noexcept final {\n')
        f.write('\t' * (tabs + 1) + f'static const SpaRcle::Utils::StringAtom extension = "{class_obj.extension}";' + '\n')
        f.write('\t' * (tabs + 1) + 'return extension;\n')
        f.write('\t' * tabs + '}\n\n')

    #######################################
    if class_obj.inspector:
        f.write('\t' * tabs + 'SR_NODISCARD SpaRcle::Utils::StringAtom GetInspectorName() const noexcept final {\n')
        f.write('\t' * (tabs + 1) + f'static const SpaRcle::Utils::StringAtom id = "{class_obj.inspector}";' + '\n')
        f.write('\t' * (tabs + 1) + 'return id;\n')
        f.write('\t' * tabs + '}\n\n')
    #######################################

    generate_class_meta_get_base_metas(f, class_structures, class_obj, tabs)
    generate_class_meta_properties(f, class_structures, class_obj, tabs)
    generate_class_meta_for_each_sr_class(f, class_structures, class_obj, tabs)

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
    generate_class_meta_clone(f, class_obj, tabs)

    f.write('\t' * tabs + 'SR_NODISCARD virtual SpaRcle::Utils::StringAtom GetFactoryName() const noexcept final {\n')
    f.write('\t' * (tabs + 1) + f'return {class_name}::GetClassStaticName();' + '\n')
    f.write('\t' * tabs + '}\n\n')

    if class_obj.display_name:
        f.write('\t' * tabs + 'SR_NODISCARD virtual SpaRcle::Utils::StringAtom GetDisplayName() const noexcept final {\n')
        f.write('\t' * (tabs + 1) + f'const static SpaRcle::Utils::StringAtom displayName = \"{class_obj.display_name}\";' + '\n')
        f.write('\t' * (tabs + 1) + f'return displayName;' + '\n')
        f.write('\t' * tabs + '}\n\n')

    f.write('\t' * (tabs - 1) + 'private:\n')
    #f.write('\t' * tabs + f'static inline const bool SR_CODEGEN_REGISTER_FACTORY = SpaRcle::Utils::Factory::Instance().Register<{class_name}>();\n\n')

    f.write('\t' * tabs + f'/// Bindings for class {class_obj.name}' + '\n')

    for property in class_obj.variables:
        f.write('\t' * tabs + f'static void Set_{property.name}(SpaRcle::Utils::SRClass* pClass, const SpaRcle::Utils::Reflection::Value& value) {{' + '\n')
        #f.write('\t' * (tabs + 1) + f'{class_name}* pClassImpl = dynamic_cast<{class_name}*>(pClass);' + '\n')
        get_class_impl_code = f'dynamic_cast<{class_name}*>(pClass)'

        #f.write('\t' * (tabs + 1) + f'const decltype({class_name}::{property.name})* pData;\n')
        #f.write('\t' * (tabs + 1) + f'if (!value.Map(pData)) {{\n')
        #f.write('\t' * (tabs + 2) + f'return;\n')
        #f.write('\t' * (tabs + 1) + f'}}\n')

        bool_do_gen_setter = True
        if property.virtual:
            if not property.setter or not property.getter:
                f.write('\t' * (tabs + 1) + f'SRHalt("Virtual property {property.name} must have getter and setter!");' + '\n')
                f.write('\t' * (tabs + 1) + 'return;\n')
                bool_do_gen_setter = False
            else:
                f.write('\t' * (tabs + 1) + f'using Type = SpaRcle::Utils::RemoveQualifiersT<decltype({get_class_impl_code}->{property.getter}())>;' + '\n')
        else:
            f.write('\t' * (tabs + 1) + f'using Type = decltype({class_name}::{property.name});' + '\n')

        if bool_do_gen_setter:
            #f.write('\t' * (tabs + 1) + f'if constexpr (SpaRcle::Utils::IsSharedPointerV<Type>) {{\n')
            #f.write('\t' * (tabs + 2) + f'auto&& pSRClassRef = value.TryCast<SpaRcle::Utils::SRClass*>();\n')
            #f.write('\t' * (tabs + 2) + f'if (!pSRClassRef) {{\n')
            #f.write('\t' * (tabs + 3) + f'SRHalt("Failed to cast value!");\n')
            #f.write('\t' * (tabs + 3) + f'return;\n')
            #f.write('\t' * (tabs + 2) + f'}}\n')
            #f.write('\t' * (tabs + 2) + f'auto&& pSRClass = const_cast<SpaRcle::Utils::SRClass*>(*pSRClassRef);\n')
            #if property.setter:
            #    f.write('\t' * (tabs + 2) + f'pClassImpl->{property.setter}(SetterSharedSRClassConvert<Type>(pSRClass));\n')
            #else:
            #    f.write('\t' * (tabs + 2) + f'pClassImpl->{property.name} = SetterSharedSRClassConvert<Type>(pSRClass);\n')
            #f.write('\t' * (tabs + 1) + f'}} else {{\n')

            if property.virtual:
                f.write('\t' * (tabs + 1) + 'auto&& pData = value.TryCast<Type>();\n')
                f.write('\t' * (tabs + 1) + 'if (!pData) {\n')
                f.write('\t' * (tabs + 2) + 'SRHalt("Failed to cast value!");\n')
                f.write('\t' * (tabs + 2) + 'return;\n')
                f.write('\t' * (tabs + 1) + '}\n')

                f.write('\t' * (tabs + 1) + f'{get_class_impl_code}->{property.setter}(*pData);' + '\n')
            else:
                f.write('\t' * (tabs + 1) + 'auto&& pData = value.TryCast<Type>();\n')
                f.write('\t' * (tabs + 1) + 'if (!pData) {\n')
                f.write('\t' * (tabs + 2) + 'SRHalt("Failed to cast value!");\n')

                f.write('\t' * (tabs + 2) + 'return;\n')
                f.write('\t' * (tabs + 1) + '}\n')

                if property.setter:
                    f.write('\t' * (tabs + 1) + f'{get_class_impl_code}->{property.setter}(*pData);' + '\n')
                else:
                    f.write('\t' * (tabs + 1) + f'{get_class_impl_code}->{property.name} = *pData;' + '\n')

            #f.write('\t' * (tabs + 1) + f'}}\n')

        f.write('\t' * tabs + '}\n')

        # =================================== getter ===================================

        f.write('\t' * tabs + f'static SpaRcle::Utils::Reflection::Value Get_{property.name}(SpaRcle::Utils::SRClass* pClass) {{\n')
        #f.write('\t' * (tabs + 1) + f'{class_name}* pClassImpl = dynamic_cast<{class_name}*>(pClass);\n')
        if property.getter:
            f.write('\t' * (tabs + 1) + f'auto&& value = {get_class_impl_code}->{property.getter}();\n')

            #f.write('\t' * (tabs + 1) + f'if constexpr (SpaRcle::Utils::IsSharedPointerV<decltype(value)>) {{\n')
            #f.write('\t' * (tabs + 2) + f'return SpaRcle::Utils::Reflection::Value::TryCreateSRClass(value);\n')
            #f.write('\t' * (tabs + 1) + f'}} else ')

            f.write('\t' * (tabs + 1) + 'if constexpr (std::is_lvalue_reference_v<decltype(value)>) {\n')
            f.write('\t' * (tabs + 2) + 'if constexpr (std::is_const_v<std::remove_reference_t<decltype(value)>>) {\n')
            f.write('\t' * (tabs + 3) + 'return SpaRcle::Utils::Reflection::Value::CreateCRef(value);\n')
            f.write('\t' * (tabs + 2) + '} else {\n')
            f.write('\t' * (tabs + 3) + 'return SpaRcle::Utils::Reflection::Value::CreateRef(value);\n')
            f.write('\t' * (tabs + 2) + '}\n')
            f.write('\t' * (tabs + 1) + '} else {\n')
            f.write('\t' * (tabs + 2) + 'return SpaRcle::Utils::Reflection::Value::Create(std::move(value));\n')
            f.write('\t' * (tabs + 1) + '}\n')
        else:
            #f.write('\t' * (tabs + 1) + f'if constexpr (SpaRcle::Utils::IsSharedPointerV<decltype(pClassImpl->{property.name})>) {{\n')
            #f.write('\t' * (tabs + 2) + f'return SpaRcle::Utils::Reflection::Value::TryCreateSRClass(pClassImpl->{property.name});\n')
            #f.write('\t' * (tabs + 1) + f'}}\n')

            if property.read_only:
                f.write('\t' * (tabs + 1) + f'return SpaRcle::Utils::Reflection::Value::CreateCRef({get_class_impl_code}->{property.name});' + '\n')
            else:
                f.write('\t' * (tabs + 1) + f'return SpaRcle::Utils::Reflection::Value::CreateRef({get_class_impl_code}->{property.name});' + '\n')


        f.write('\t' * tabs + '}\n')

        if property.change_callback:
            f.write('\t' * tabs + f'static void OnChange_{property.name}(SpaRcle::Utils::SRClass* pClass) {{' + '\n')
            f.write('\t' * (tabs + 1) + f'dynamic_cast<{class_name}*>(pClass)->{property.change_callback}();\n')
            f.write('\t' * tabs + '}\n\n')

    tabs -= 1
    f.write('\t' * tabs + '};\n\n')

    f.write(f'\t' * tabs + f'extern "C" {dll_export_macro} void RegisterClassMeta_{class_obj.name}() {{' + '\n')
    f.write(f'\t' * (tabs + 1) + f'SpaRcle::Utils::Factory::Instance().Register<{class_name}>("{context.module_name}");' + '\n')
    f.write(f'\t' * tabs + f'}}\n\n')

    f.write(f'\t' * tabs + f'extern "C" {dll_export_macro} void UnregisterClassMeta_{class_obj.name}() {{' + '\n')
    f.write(f'\t' * (tabs + 1) + f'SpaRcle::Utils::Factory::Instance().Unregister<{class_name}>();' + '\n')
    f.write(f'\t' * tabs + '}\n\n')

    #for inherited_class in class_obj.inherited_classes:
    #    inherited_class_formated = inherited_class.split('::')[-1]
    #    f.write('\t' * tabs + f'// class {class_obj.name} inherits from {inherited_class}\n')
    #    f.write('\t' * tabs + f'inline static bool SR_CODEGEN_REGISTER_INHERITANCE_{class_obj.name}_{inherited_class_formated} '
    #                          f'= SpaRcle::Utils::ClassDB::Instance().RegisterInheritance(\"{class_obj.name}\", \"{inherited_class_formated}\");\n\n')

    tabs -= 1
    f.write('\t' * tabs + '}\n\n')
    pass


def generate_enums_fwd_header(logger: logger_utils.Logger, context: codegen_context.CodegenContext, enums):
    basic_full_path = os.path.normpath(f'{context.codegen_dir}/EnumsFwd.generated.hpp')
    f = sparcle_utils.StringStream()

    if True:
        f.write(sparcle_utils.codegen_cpp_header_comment)
        f.write('#ifndef SR_CODEGEN_ENUMS_BASIC_HPP\n')
        f.write('#define SR_CODEGEN_ENUMS_BASIC_HPP\n\n')

        for enum_obj in enums:
            namespace_str = ''
            if len(enum_obj.namespaces) > 0:
                namespace_str = '::'.join(enum_obj.namespaces)

            if len(namespace_str) > 0:
                f.write(f'namespace {namespace_str} {{\n')

            f.write(f'\t{enum_obj.enum_class} {enum_obj.name} : {enum_obj.type};' + '\n')
            f.write(f'\tclass CodegenEnumIncludedChecked_{enum_obj.name};' + '\n')
            #f.write(f'\ttemplate<typename T, typename Enable = void> struct CodegenEnumIncludedChecked_{enum_obj.name} : std::false_type {{}};\n')

            if namespace_str:
                f.write('}\n\n')

        f.write('#endif\n')

    if os.path.isfile(basic_full_path):
        with open(basic_full_path, 'r', encoding='utf8') as old_f:
            if str(f) == old_f.read():
                logger.log_info('EnumsFwd.generated.hpp is up to date')
                return

    with open(basic_full_path, 'w', encoding='utf8') as new_f:
        new_f.write(str(f))


def generate_enums_header(logger: logger_utils.Logger, context: codegen_context.CodegenContext, enums):
    return

    full_path = os.path.normpath(f'{context.codegen_dir}/Enums.generated.hpp')
    f = sparcle_utils.StringStream()
    if True:
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
        #for enum_obj in enums:
        #    namespace_str = ''
        #    if len(enum_obj.namespaces) > 0:
        #        namespace_str = '::'.join(enum_obj.namespaces)

        #    if len(namespace_str) > 0:
        #        namespace_str += '::'

        #    class_full_name = namespace_str + enum_obj.name

        #    f.write('namespace Codegen {\n')

        #    #f.write(f'\ttemplate<> constexpr SpaRcle::Utils::EnumVariant GetEnumVariant(Codegen::EnumSelector<{class_full_name}>) noexcept {{' + '\n')
        #    #f.write(f'\t\treturn SpaRcle::Utils::EnumVariant::{enum_obj.variant};' + '\n')
        #    #f.write('\t}\n\n')
        #    #
        #    #f.write(f'\ttemplate<> constexpr size_t GetEnumItemsCount(Codegen::EnumSelector<{class_full_name}>) noexcept {{' + '\n')
        #    #f.write(f'\t\treturn {enum_obj.count};' + '\n')
        #    #f.write('\t}\n\n')

        #    f.write('}\n\n')

        # operators
        for enum_obj in enums:
            namespace_str = ''
            if len(enum_obj.namespaces) > 0:
                namespace_str = '::'.join(enum_obj.namespaces)

            if len(namespace_str) > 0:
                namespace_str += '::'

            class_full_name = namespace_str + enum_obj.name
            f.write(f'SR_CODEGEN_ENUM_OPERATORS({class_full_name})' + '\n')

        f.write('\n')

        f.write('\n#endif // SR_CODEGEN_ENUMS_HPP\n')

    if os.path.isfile(full_path):
        with open(full_path, 'r', encoding='utf8') as old_f:
            if str(f) == old_f.read():
                logger.log_info('Enums.generated.hpp is up to date')
                return

    with open(full_path, 'w', encoding='utf8') as new_f:
        new_f.write(str(f))


def generate_enums_code(logger: logger_utils.Logger, context: codegen_context.CodegenContext, enums):
    logger.log_info(f'Generating enums utility code...')

    generate_enums_fwd_header(logger, context, enums)
    generate_enums_header(logger, context, enums)

    logger.log_info(f'Generating enum files...')

    os.makedirs(os.path.normpath(f'{context.codegen_dir}/../Enum'), exist_ok=True)

    generated_files = set()
    generated = 0
    skipped = 0

    for enum_obj in enums:
        generated_files.add(f'{enum_obj.name}.hpp')
        f = sparcle_utils.StringStream()

        if True:
            caps_enum_name = enum_obj.name.upper()

            f.write(sparcle_utils.codegen_cpp_header_comment)
            f.write(f'#ifndef SR_CODEGEN_ENUM_{caps_enum_name}_HPP' + '\n')
            f.write(f'#define SR_CODEGEN_ENUM_{caps_enum_name}_HPP' + '\n\n')

            f.write(f'#include \"{enum_obj.source_path}\"' + '\n\n')
            f.write(f'#include <Utils/Common/EnumOperators.h>\n\n')

            #f.write('#include <Codegen/Enums.generated.hpp>\n\n')

            namespace_str = ''
            if len(enum_obj.namespaces) > 0:
                namespace_str = '::'.join(enum_obj.namespaces)

            if len(namespace_str) > 0:
                namespace_str += '::'

            class_full_name = namespace_str + enum_obj.name
            f.write(f'SR_CODEGEN_ENUM_OPERATORS(inline, inline, {class_full_name})' + '\n\n')

            f.write(f'template<> struct fmt::formatter<{namespace_str}{enum_obj.name}> {{' + '\n')
            f.write('\tconstexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }\n')
            f.write(f'\tauto format(const {namespace_str}{enum_obj.name}& val, format_context& ctx) const {{' + '\n')

            #f.write(f'\t\tstatic_assert(SpaRcle::Utils::IsCompleteTypeV<{namespace_str}CodegenEnumIncludedChecked_{enum_obj.name}>, "Formatted enum is not included, please include it!");' + '\n')
            f.write('\t\treturn fmt::format_to(ctx.out(), "{}", SpaRcle::Utils::EnumReflector::ToStringAtom(val).ToStringView());' + '\n')

            f.write('\t}\n')
            f.write('};\n')

            f.write('\n' + f'#endif // SR_CODEGEN_ENUM_{caps_enum_name}_HPP' + '\n')

        enum_gen_path = os.path.normpath(f'{context.codegen_dir}/../Enum/{enum_obj.name}.hpp')
        if os.path.isfile(enum_gen_path):
            with open(enum_gen_path, 'r', encoding='utf8') as old_f:
                if str(f) == old_f.read():
                    skipped += 1
                    continue

        with open(enum_gen_path, 'w', encoding='utf8') as new_f:
            generated += 1
            new_f.write(str(f))

    # delete not used files
    for file in glob(f'{context.codegen_dir}/../Enum/*.hpp', recursive=False):
        if os.path.basename(file) not in generated_files:
            logger.log_info(f'Remove old enum codegen file: {file}')
            os.remove(file)

    logger.log_info(f'Enum files generated: {generated}, skipped: {skipped}')


def generate_meta_module_core_code(logger: logger_utils.Logger, context: codegen_context.CodegenContext, class_structures):
    logger.log_info(f'Generating meta module core code to {context.codegen_dir}...')

    full_path = os.path.normpath(f'{context.codegen_dir}/SpaRcleModule{context.module_name}Core.generated.hpp')
    f = sparcle_utils.StringStream()

    if True:
        f.write(sparcle_utils.codegen_cpp_header_comment)

        f.write(f'#ifndef SR_CODEGEN_SPARCLE_MODULE_{context.module_name.upper()}_CORE_HPP' + '\n')
        f.write(f'#define SR_CODEGEN_SPARCLE_MODULE_{context.module_name.upper()}_CORE_HPP' + '\n\n')

        f.write('#include <Utils/stdInclude.h>\n')

        already_included = set()
        already_included.add('Utils')
        for class_obj in class_structures:
            if not class_obj.is_help_source and class_obj.code_module_name:
                if class_obj.code_module_name not in already_included:
                    already_included.add(class_obj.code_module_name)
                    f.write(f'#include <{class_obj.code_module_name}/stdInclude.h>\n')
        if len(already_included) > 1:
            f.write(f'\n')

        f.write('namespace Codegen {\n')

        tabs = 1

        for class_obj in class_structures:
            if not class_obj.is_help_source:
                dll_export_macro = 'SR_CODEGEN_DLL_API_EXPORT'
                if class_obj.code_module_name:
                    dll_export_macro = f'SR_CODEGEN_DLL_API_EXPORT_{class_obj.code_module_name.upper()}_MODULE'
                f.write(tabs * "\t" + f'extern "C" {dll_export_macro} void RegisterClassMeta_{class_obj.name}();' + '\n')
                f.write(tabs * "\t" + f'extern "C" {dll_export_macro} void UnregisterClassMeta_{class_obj.name}();' + '\n')

        ############################### register #################################
        f.write('\n' + tabs * "\t" + f'void RegisterModule_{context.module_name}() {{' + '\n')

        tabs += 1

        for class_obj in class_structures:
            if not class_obj.is_help_source:
                f.write(tabs * "\t" + f'RegisterClassMeta_{class_obj.name}();' + '\n')

        tabs -= 1

        f.write(tabs * "\t" + '}\n')

        ############################### unregister #################################
        f.write('\n' + tabs * "\t" + f'void UnregisterModule_{context.module_name}() {{' + '\n')

        tabs += 1

        for class_obj in class_structures:
            if not class_obj.is_help_source:
                f.write(tabs * "\t" + f'UnregisterClassMeta_{class_obj.name}();' + '\n')

        tabs -= 1

        f.write(tabs * "\t" + '}\n')

        f.write('}\n\n')

        f.write('#if defined(SR_WIN32) && defined(SR_ENGINE_SCRIPT_API_MODE)')
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
    }}''' + '\n')

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
    }}''' + '\n')
        f.write('#endif\n\n')

        f.write(f'#endif // SR_CODEGEN_SPARCLE_MODULE_{context.module_name.upper()}_CORE_HPP' + '\n')

    if os.path.isfile(context.codegen_dir):
        with open(full_path, 'w', encoding='utf8') as old_f:
            if old_f.read() == str(f):
                logger.log_info(f'Core module is already up to date.')
                return

    with open(full_path, 'w', encoding='utf8') as new_f:
        new_f.write(str(f))



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

    generated_files = {
        f'SpaRcleModule{context.module_name}Core.generated.hpp',
        'Enums.generated.hpp',
        'EnumsFwd.generated.hpp'
    }

    skipped = 0
    generated = 0

    for file_name, class_objs in file_map.items():
        has_non_help_source = False
        for class_obj in class_objs:
            if not class_obj.is_help_source:
                has_non_help_source = True
                break

        if not has_non_help_source:
            continue

        generated_files.add(f'{file_name}.generated.hpp')

        f = sparcle_utils.StringStream()
        def_includes_included = False

        if True:
            f.write(sparcle_utils.codegen_cpp_header_comment)
            f.write(f'#ifndef SR_CODEGEN_{file_name.upper()}_HPP' + '\n')
            f.write(f'#define SR_CODEGEN_{file_name.upper()}_HPP' + '\n\n')
            for class_obj in class_objs:
                if class_obj.is_help_source:
                    continue

                _, ext = os.path.splitext(class_obj.path)

                dll_export_macro = 'SR_CODEGEN_DLL_API_EXPORT'
                if class_obj.code_module_name:
                    f.write(f'/// Code module: {class_obj.code_module_name}' + '\n')
                    dll_export_macro = f'SR_CODEGEN_DLL_API_EXPORT_{class_obj.code_module_name.upper()}_MODULE'

                if ext == '.h':
                    f.write(f'#include "{os.path.abspath(os.path.normpath(class_obj.path))}"' + '\n\n')

                if not def_includes_included:
                    f.write('#include <Utils/Serialization/SerializableDataAccessor.h>\n')
                    f.write('#include <Utils/Reflection/Property.h>\n')
                    f.write('#include <Utils/Reflection/Value.h>\n')
                    f.write('#include <Utils/Reflection/SRClassUtils.h>\n')
                    f.write('#include <Utils/TypeTraits/SRClass.h>\n')
                    f.write('#include <Utils/TypeTraits/Factory.h>\n')
                    f.write('#include <Utils/TypeTraits/SRClassMeta.h>\n')
                    f.write('#include <Utils/Serialization/MigrationManager.h>\n\n')
                    def_includes_included = True

                tabs = 0

                generate_class_meta(f, context, class_structures, class_obj, tabs, dll_export_macro)

                if len(class_obj.namespaces) > 0:
                    tabs = 1
                    namespace_str = '::'.join(class_obj.namespaces)
                    f.write(f'namespace {namespace_str} {{' + '\n')


                f.write('\t' * tabs + f'const SpaRcle::Utils::SRClassMeta* {class_obj.name}::GetMetaStatic() noexcept {{' + '\n')
                f.write('\t' * (tabs + 1) + f'return &::Codegen::SRClassMetaTemplate<{class_obj.name}>::Instance();' + '\n')
                f.write('\t' * tabs + '}\n\n')

                factory_name = class_obj.name.split('::')[-1]
                #factory_name = factory_name[0].lower() + factory_name[1:]
                f.write('\t' * tabs + f'SpaRcle::Utils::StringAtom {class_obj.name}::GetClassStaticName() noexcept {{' + '\n')
                f.write('\t' * (tabs + 1) + f'return \"{factory_name}\";' + '\n')
                f.write('\t' * tabs + '}\n\n')

                f.write('\t' * tabs + f'SpaRcle::Utils::SRClass* {class_obj.name}::AllocateStatic() noexcept {{' + '\n')
                f.write('\t' * (tabs + 1) + f'if constexpr (std::is_abstract_v<{class_obj.name}>) {{' + '\n')
                f.write('\t' * (tabs + 2) + f'SRHalt("Cannot allocate abstract class \\\"{class_obj.name}\\\"!");' + '\n')
                f.write('\t' * (tabs + 2) + 'return nullptr;\n')
                f.write('\t' * (tabs + 1) + '}\n')
                f.write('\t' * (tabs + 1) + 'else {\n')
                f.write('\t' * (tabs + 2) + f'return static_cast<SpaRcle::Utils::SRClass*>(SRNew<{class_obj.name}>());' + '\n')
                f.write('\t' * (tabs + 1) + '}\n')
                f.write('\t' * tabs + '}\n')
                if len(class_obj.namespaces) > 0:
                    f.write('}\n')
            f.write('\n')
            f.write(f'#endif // SR_CODEGEN_{file_name.upper()}_HPP' + '\n')

        full_path = os.path.normpath(f'{context.codegen_dir}/{file_name}.generated.hpp')
        if os.path.isfile(full_path):
            # compare data
            with open(full_path, 'r', encoding='utf8') as old_f:
                old_data = old_f.read()
                if old_data == str(f):
                    skipped += 1
                    continue

        with open(full_path, 'w', encoding='utf8') as new_f:
            new_f.write(str(f))
            generated += 1

    # delete not used files
    for file in glob(f'{context.codegen_dir}/*.generated.hpp', recursive=False):
        if os.path.basename(file) not in generated_files:
            logger.log_info(f'Remove old codegen file: {file}')
            os.remove(file)

    logger.log_info(f'Codegen files generated: {generated}, skipped: {skipped}')
