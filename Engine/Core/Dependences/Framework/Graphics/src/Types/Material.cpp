//
// Created by Nikita on 17.11.2020.
//

#include <Types/Material.h>

#include <Types/Mesh.h>
#include <Types/Shader.h>
#include <Types/Texture.h>

namespace SR_GTYPES_NS {
    Material::Material()
        : SR_UTILS_NS::IResource(typeid(Material).name(), true /** autoRemove */)
    { }

    void Material::Use() {
        InitShader();
        InitContext();

        for (const Material::Property& property : m_properties) {
            switch (property.type) {
                case ShaderVarType::Int:
                    m_shader->SetValue(SR_RUNTIME_TIME_CRC32_STR(property.id.c_str()), std::get<int32_t>(property.data));
                    break;
                case ShaderVarType::Float:
                    m_shader->SetValue(SR_RUNTIME_TIME_CRC32_STR(property.id.c_str()), std::get<float_t>(property.data));
                    break;
                case ShaderVarType::Vec2:
                    m_shader->SetValue(SR_RUNTIME_TIME_CRC32_STR(property.id.c_str()), std::get<SR_MATH_NS::FVector2>(property.data).Cast<float_t>());
                    break;
                case ShaderVarType::Vec3:
                    m_shader->SetValue(SR_RUNTIME_TIME_CRC32_STR(property.id.c_str()), std::get<SR_MATH_NS::FVector3>(property.data).Cast<float_t>());
                    break;
                case ShaderVarType::Vec4:
                    m_shader->SetValue(SR_RUNTIME_TIME_CRC32_STR(property.id.c_str()), std::get<SR_MATH_NS::FVector4>(property.data).Cast<float_t>());
                    break;
                case ShaderVarType::Sampler2D:
                    /// samplers used at UseSamplers
                    break;
                default:
                    SRAssertOnce(false);
                    break;
            }
        }
    }

    SR_UTILS_NS::IResource* Material::Copy(SR_UTILS_NS::IResource* destination) const {
        SRAssert2(false, "Material is not are copyable!");
        return nullptr;
    }

    Material* Material::Load(const std::string &rawPath) {
        SR_GLOBAL_LOCK

        SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(rawPath).RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetMaterialsPath());

        if (auto&& pMaterial = SR_UTILS_NS::ResourceManager::Instance().Find<Material>(path))
            return pMaterial;

        auto&& pMaterial = new Material();

        pMaterial->SetId(path, false);

        if (!pMaterial->Reload()) {
            delete pMaterial;
            return nullptr;
        }

        SR_UTILS_NS::ResourceManager::Instance().RegisterResource(pMaterial);

        return pMaterial;
    }

    bool Material::Destroy() {
        if (IsDestroyed())
            return false;

        SetReadOnly(false);
        SetShader(nullptr);

        for (auto&& property : m_properties) {
            switch (property.type) {
                case ShaderVarType::Sampler2D:
                    SetTexture(&property, nullptr);
                    break;
                default:
                    break;
            }
        }

        return IResource::Destroy();
    }

    void SR_GTYPES_NS::Material::SetShader(Shader *shader) {
        SR_LOCK_GUARD

        if (m_shader == shader) {
            return;
        }

        m_dirtyShader = true;

        if (m_shader) {
            RemoveDependency(m_shader);
            m_shader = nullptr;
        }

        if ((m_shader = shader)) {
            m_transparent = shader->IsBlendEnabled();
        }
        else {
            return;
        }

        AddDependency(m_shader);
    }

    void Material::SetTexture(Material::Property* property, Texture *pTexture) {
        if (!SRVerifyFalse(!property)) {
            return;
        }

        SR_SCOPED_LOCK

        if (auto&& oldTexture = std::get<Texture*>(property->data)) {
            if (oldTexture == pTexture) {
                return;
            }

            RemoveDependency(oldTexture);
        }

        if (pTexture) {
            AddDependency(pTexture);
        }

        property->data = pTexture;

        /// обновляем всю иерархию вверх (меши)
        UpdateResources(1);

        /// сработает только если хоть раз была отрендерина текстура материала
        m_context.Do([](RenderContext* ptr) {
            ptr->SetDirty();
        });
    }


    void Material::UseSamplers() {
        InitShader();
        InitContext();

        if (m_context->GetPipeline()->GetCurrentDescriptorSet() == SR_ID_INVALID) {
            return;
        }

        for (const Material::Property& property : m_properties) {
            switch (property.type) {
                case ShaderVarType::Sampler2D:
                    m_shader->SetSampler2D(property.id, std::get<Texture*>(property.data));
                    break;
                default:
                    break;
            }
        }
    }

    void Material::InitShader() {
        if (m_dirtyShader) {
            Properties properties = m_properties;

            m_properties.clear();

            if (m_shader) {
                for (auto&&[name, property] : m_shader->GetProperties()) {
                    Property aProperty;

                    aProperty.id = name;
                    aProperty.displayName = name; // TODO: make a pretty name
                    aProperty.data = GetVariantFromShaderVarType(property);
                    aProperty.type = property;

                    m_properties.emplace_back(aProperty);
                }
            }

            for (auto&& property : properties) {
                if (auto&& pProperty = GetProperty(property.id); pProperty && pProperty->type == property.type) {
                    pProperty->data = property.data;
                }
                else if (property.type == ShaderVarType::Sampler2D) {
                    auto&& pTexture = std::get<Texture*>(property.data);

                    if (!pTexture) {
                        continue;
                    }

                    RemoveDependency(pTexture);
                }
            }

            m_dirtyShader = false;
        }
    }

    void Material::InitContext() {
        if (!m_context) {
            if (!(m_context = SR_THIS_THREAD->GetContext()->GetValue<RenderContextPtr>())) {
                SRHalt("Is not render context!");
                return;
            }
            m_context->Register(this);
        }
    }

    void Material::OnResourceUpdated(IResource *pResource, int32_t depth) {
        if (dynamic_cast<Shader*>(pResource) == m_shader && m_shader) {
            m_dirtyShader = true;
        }

        IResource::OnResourceUpdated(pResource, depth);
    }

    Material::Property *Material::GetProperty(const std::string& id) {
        for (auto&& property : m_properties) {
            if (property.id == id) {
                return &property;
            }
        }

        return nullptr;
    }

    bool Material::Reload() {
        SR_LOG("Material::Reload() : reloading \"" + GetResourceId() + "\" material...");

        m_loadState = LoadState::Reloading;

        /// clear old data
        {
            SetReadOnly(false);
            SetShader(nullptr);
            InitShader();
        }

        const auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetMaterialsPath().Concat(GetResourcePath());

        auto&& document = SR_XML_NS::Document::Load(path);
        if (!document.Valid()) {
            SR_ERROR("Material::Reload() : file is not found! \n\tPath: " + path.ToString());
            return false;
        }

        auto&& matXml = document.Root().GetNode("Material");
        if (!matXml) {
            SR_ERROR("Material::Reload() : \"Material\" node is not found! \n\tPath: " + path.ToString());
            return false;
        }

        if (auto&& shader = matXml.TryGetNode("Shader")) {
            auto&& render = RenderManager::Instance().Get("Main");
            auto&& pShader = Shader::Load(shader.GetAttribute("Path").ToString());

            SetShader(pShader);
            InitShader();
        }

        if (auto&& properties = matXml.TryGetNode("Properties")) {
            for (auto&& propertyXml : properties.GetNodes()) {
                const std::string id = propertyXml.GetAttribute("Id").ToString();
                auto&& typeName = propertyXml.GetAttribute("Type").ToString();
                auto&& type = StringToEnumShaderVarType(typeName);

                Property* pProperty = GetProperty(id);

                if (!pProperty) {
                    SR_WARN("Material::Reload() : failed to load \"" + id + "\" property! \n\tType: "
                        + typeName + "\n\tProperty count: " + std::to_string(m_properties.size()));

                    continue;
                }

                if (pProperty->type != type) {
                    SR_WARN("Material::Reload() : incompatible types in \"" + id + "\" property!")
                    continue;
                }

                switch (type) {
                    case ShaderVarType::Int:
                        pProperty->data = propertyXml.GetAttribute<int32_t>();
                        break;
                    case ShaderVarType::Float:
                        pProperty->data = propertyXml.GetAttribute<float_t>();
                        break;
                    case ShaderVarType::Vec2:
                        pProperty->data = propertyXml.GetAttribute<SR_MATH_NS::FVector2>();
                        break;
                    case ShaderVarType::Vec3:
                        pProperty->data = propertyXml.GetAttribute<SR_MATH_NS::FVector3>();
                        break;
                    case ShaderVarType::Vec4:
                        pProperty->data = propertyXml.GetAttribute<SR_MATH_NS::FVector4>();
                        break;
                    case ShaderVarType::Sampler2D:
                        SetTexture(pProperty, Texture::Load(propertyXml.GetAttribute<std::string>()));
                        break;
                    case ShaderVarType::Mat2:
                    case ShaderVarType::Mat3:
                    case ShaderVarType::Mat4:
                    case ShaderVarType::Sampler1D:
                    case ShaderVarType::Sampler3D:
                    case ShaderVarType::SamplerCube:
                    case ShaderVarType::Sampler1DShadow:
                    case ShaderVarType::Sampler2DShadow:
                    case ShaderVarType::Unknown:
                    default:
                        SRAssert(false);
                        break;
                }
            }
        }

        SetReadOnly(matXml.TryGetAttribute("ReadOnly").ToBool(false));

        m_loadState = LoadState::Loaded;

        UpdateResources();

        return true;
    }

    SR_UTILS_NS::Path Material::GetAssociatedPath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetMaterialsPath();
    }
}