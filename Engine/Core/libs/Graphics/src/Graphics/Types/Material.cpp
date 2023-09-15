//
// Created by Nikita on 17.11.2020.
//

#include <Graphics/Types/Material.h>

#include <Graphics/Types/Mesh.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/Render/RenderContext.h>

namespace SR_GTYPES_NS {
    Material::Material()
        : Super(SR_COMPILE_TIME_CRC32_TYPE_NAME(Material))
    { }

    Material::~Material() {
        SetShader(nullptr);

        for (auto&& pTexture : GetTexturesFromMatProperties(m_properties)) {
            RemoveDependency(pTexture);
        }
    }

    void Material::Use() {
        InitContext();

        auto&& pShader = m_context->GetCurrentShader() ? m_context->GetCurrentShader() : m_shader;

        for (auto&& property : m_properties) {
            switch (property.type) {
                case ShaderVarType::Int:
                    pShader->SetInt(property.hashId, std::get<int32_t>(property.data));
                    break;
                case ShaderVarType::Float:
                    pShader->SetFloat(property.hashId, std::get<float_t>(property.data));
                    break;
                case ShaderVarType::Vec2:
                    pShader->SetVec2(property.hashId, std::get<SR_MATH_NS::FVector2>(property.data).Cast<float_t>());
                    break;
                case ShaderVarType::Vec3:
                    pShader->SetVec3(property.hashId, std::get<SR_MATH_NS::FVector3>(property.data).Cast<float_t>());
                    break;
                case ShaderVarType::Vec4:
                    pShader->SetVec4(property.hashId, std::get<SR_MATH_NS::FVector4>(property.data).Cast<float_t>());
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

    SR_UTILS_NS::IResource* Material::CopyResource(SR_UTILS_NS::IResource* destination) const {
        SRHalt( "Material is not are copyable!");
        return nullptr;
    }

    Material* Material::Load(SR_UTILS_NS::Path rawPath) {
        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        Material* pMaterial = nullptr;

        resourceManager.Execute([&](){
            auto&& path = rawPath.SelfRemoveSubPath(resourceManager.GetResPathRef());
            if (!resourceManager.GetResPathRef().Concat(path).Exists()) {
                SR_WARN("Material::Load() : path to the shader doesn't exist! Loading is aborted.");
                return;
            }

            if ((pMaterial = resourceManager.Find<Material>(path))) {
                return;
            }

            pMaterial = new Material();

            pMaterial->SetId(path, false);

            if (!pMaterial->Reload()) {
                delete pMaterial;
                pMaterial = nullptr;
                return;
            }

            resourceManager.RegisterResource(pMaterial);
        });

        return pMaterial;
    }

    bool Material::Destroy() {
        return IResource::Destroy();
    }

    void SR_GTYPES_NS::Material::SetShader(Shader *shader) {
        if (m_shader == shader) {
            return;
        }

        m_dirtyShader = true;

        if (m_shader) {
            RemoveDependency(m_shader);
            m_shader = nullptr;
        }

        if (!(m_shader = shader)) {
            return;
        }

        AddDependency(m_shader);
    }

    void Material::SetTexture(MaterialProperty* property, Texture *pTexture) {
        if (!SRVerifyFalse(!property)) {
            return;
        }

        if (auto&& oldTexture = std::get<Texture*>(property->data)) {
            if (oldTexture == pTexture) {
                return;
            }

            RemoveDependency(oldTexture);
        }

        if (pTexture) {
            SRAssert(!(pTexture->GetCountUses() == 0 && pTexture->IsCalculated()));
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
        InitContext();

        if (m_shader && m_context->GetCurrentShader() != m_shader) {
            return;
        }

        if (m_context->GetPipeline()->GetCurrentDescriptorSet() == SR_ID_INVALID) {
            return;
        }

        for (auto&& property : m_properties) {
            switch (property.type) {
                case ShaderVarType::Sampler2D:
                    m_shader->SetSampler2D(property.hashId, std::get<Texture*>(property.data));
                    break;
                default:
                    break;
            }
        }
    }

    bool Material::LoadProperties(const SR_XML_NS::Node &propertiesNode) {
        SRAssert(m_properties.empty());

        if (!m_shader) {
            SR_ERROR("Material::LoadProperties() : shader is nullptr!");
            return false;
        }

        /// Загружаем базовые значения
        for (auto&&[name, property] : m_shader->GetProperties()) {
            MaterialProperty aProperty;

            aProperty.id = name;
            aProperty.hashId = SR_RUNTIME_TIME_CRC32_STR(aProperty.id.c_str());
            aProperty.displayName = name; // TODO: make a pretty name
            aProperty.data = GetVariantFromShaderVarType(property);
            aProperty.type = property;

            m_properties.emplace_back(aProperty);
        }

        /// Применяем сохраненные в материале значения
        for (auto&& loadedProperty : LoadMaterialProperties(propertiesNode)) {
            if (auto&& pProperty = GetProperty(loadedProperty.hashId)) {
                pProperty->data = loadedProperty.data;
            }
        }

        /// Добавляем все текстуры в зависимости
        for (auto&& pTexture : GetTexturesFromMatProperties(m_properties)) {
            SRAssert(!(pTexture->GetCountUses() == 0 && pTexture->IsCalculated()));
            AddDependency(pTexture);
        }

        return true;
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

    void Material::OnResourceUpdated(SR_UTILS_NS::ResourceContainer* pContainer, int32_t depth) {
        if (dynamic_cast<Shader*>(pContainer) == m_shader && m_shader) {
            m_dirtyShader = true;
        }

        IResource::OnResourceUpdated(pContainer, depth);
    }

    MaterialProperty *Material::GetProperty(uint64_t hashId) {
        for (auto&& property : m_properties) {
            if (property.hashId == hashId) {
                return &property;
            }
        }

        return nullptr;
    }

    MaterialProperty *Material::GetProperty(const std::string& id) {
        return GetProperty(SR_RUNTIME_TIME_CRC32_STR(id.c_str()));
    }

    bool Material::Load() {
        const auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(GetResourcePath());

        auto&& document = SR_XML_NS::Document::Load(path);
        if (!document.Valid()) {
            SR_ERROR("Material::Load() : file is not found! \n\tPath: " + path.ToString());
            return false;
        }

        auto&& matXml = document.Root().GetNode("Material");
        if (!matXml) {
            SR_ERROR("Material::Load() : \"Material\" node is not found! \n\tPath: " + path.ToString());
            return false;
        }

        if (auto&& shader = matXml.TryGetNode("Shader")) {
            SetShader(Shader::Load(shader.GetAttribute("Path").ToString()));
        }
        else {
            SR_ERROR("Material::Load() : the material have not shader!");
            return false;
        }

        LoadProperties(matXml.TryGetNode("Properties"));

        return IResource::Load();
    }

    bool Material::Unload() {
        SetShader(nullptr);

        for (auto&& pTexture : GetTexturesFromMatProperties(m_properties)) {
            RemoveDependency(pTexture);
        }

        m_properties.clear();

        return IResource::Unload();
    }

    bool Material::Reload() {
        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Medium) {
            SR_LOG("Material::Reload() : reloading \"" + std::string(GetResourceId()) + "\" material...");
        }

        m_loadState = LoadState::Reloading;

        /// ========= Stash Properties =========
        auto&& stashTextures = GetTexturesFromMatProperties(m_properties);
        for (auto&& pTexture : stashTextures) {
            pTexture->AddUsePoint();
        }
        Shader* stashShader = m_shader;
        if (stashShader) {
            stashShader->AddUsePoint();
        }
        /// ========= Stash Properties =========

        Unload();

        if (!Load()) {
            m_loadState = LoadState::Error;
            return false;
        }

        /// ========= UnStash Properties =========
        for (auto&& pTexture : stashTextures) {
            pTexture->RemoveUsePoint();
        }
        if (stashShader) {
            stashShader->RemoveUsePoint();
        }
        /// ========= UnStash Properties =========

        UpdateResources();

        m_context.Do([](RenderContext* ptr) {
            ptr->SetDirty();
        });

        return true;
    }

    SR_UTILS_NS::Path Material::GetAssociatedPath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetResPath();
    }

    bool Material::IsTransparent() const {
        if (!m_shader) {
            SRHalt("Shader is nullptr!");
            return false;
        }

        return m_shader->IsBlendEnabled();
    }

    bool Material::ContainsTexture(SR_GTYPES_NS::Texture* pTexture) const {
        if (!pTexture) {
            return false;
        }

        for (auto&& property : m_properties) {
            if (std::visit([pTexture](ShaderPropertyVariant&& arg) -> bool {
                if (std::holds_alternative<SR_GTYPES_NS::Texture*>(arg)) {
                    return std::get<SR_GTYPES_NS::Texture*>(arg) == pTexture;
                }
                return false;
            }, property.data)) {
                return true;
            }
        }

        return false;
    }
}