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

        m_properties.ForEachProperty<MaterialProperty>([this](auto&& pProperty){
            auto&& hashId = pProperty->GetName().GetHash();

            switch (pProperty->GetShaderVarType()) {
                case ShaderVarType::Int:
                    m_shader->SetInt(hashId, std::get<int32_t>(pProperty->GetData()));
                    break;
                case ShaderVarType::Float:
                    m_shader->SetFloat(hashId, std::get<float_t>(pProperty->GetData()));
                    break;
                case ShaderVarType::Vec2:
                    m_shader->SetVec2(hashId, std::get<SR_MATH_NS::FVector2>(pProperty->GetData()).template Cast<float_t>());
                    break;
                case ShaderVarType::Vec3:
                    m_shader->SetVec3(hashId, std::get<SR_MATH_NS::FVector3>(pProperty->GetData()).template Cast<float_t>());
                    break;
                case ShaderVarType::Vec4:
                    m_shader->SetVec4(hashId, std::get<SR_MATH_NS::FVector4>(pProperty->GetData()).template Cast<float_t>());
                    break;
                case ShaderVarType::Sampler2D:
                    /// samplers used at UseSamplers
                    break;
                default:
                    SRAssertOnce(false);
                    break;
            }
        });
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
                SR_WARN("Material::Load() : path to the material doesn't exist! Loading is aborted.\n\tPath: " + path.ToStringRef());
                return;
            }

            if ((pMaterial = resourceManager.Find<Material>(path))) {
                return;
            }

            pMaterial = new Material();

            pMaterial->SetId(path.ToStringRef(), false);

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

        if (auto&& oldTexture = std::get<Texture*>(property->GetData())) {
            if (oldTexture == pTexture) {
                return;
            }

            RemoveDependency(oldTexture);
        }

        if (pTexture) {
            SRAssert(!(pTexture->GetCountUses() == 0 && pTexture->IsCalculated()));
            AddDependency(pTexture);
        }

        property->SetData(pTexture);

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

        m_properties.ForEachProperty<MaterialProperty>([this](auto&& pProperty){
            switch (pProperty->GetShaderVarType()) {
                case ShaderVarType::Sampler2D:
                    m_shader->SetSampler2D(pProperty->GetName().GetHash(), std::get<Texture*>(pProperty->GetData()));
                    break;
                default:
                    break;
            }
        });
    }

    bool Material::LoadProperties(const SR_XML_NS::Node &propertiesNode) {
        if (!m_shader) {
            SR_ERROR("Material::LoadProperties() : shader is nullptr!");
            return false;
        }

        m_properties.ClearContainer();

        /// Загружаем базовые значения
        for (auto&& [id, propertyType] : m_shader->GetProperties()) {
            m_properties.AddCustomProperty<MaterialProperty>(id.c_str())
                .SetData(GetVariantFromShaderVarType(propertyType))
                .SetShaderVarType(propertyType)
                .SetMaterial(this)
                .SetDisplayName(id); // TODO: make a pretty name
        }

        /// Применяем сохраненные в материале значения
        LoadMaterialProperties(this, propertiesNode, &m_properties);

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

    MaterialProperty* Material::GetProperty(uint64_t hashId) {
        return m_properties.Find<MaterialProperty>(hashId);
    }

    MaterialProperty* Material::GetProperty(const SR_UTILS_NS::StringAtom& id) {
        return GetProperty(id.GetHash());
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

        m_properties.ClearContainer();

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

        return !m_properties.ForEachPropertyRet<MaterialProperty>([pTexture](auto&& pProperty) -> bool {
            if (std::visit([pTexture](ShaderPropertyVariant&& arg) -> bool {
                if (std::holds_alternative<SR_GTYPES_NS::Texture*>(arg)) {
                    return std::get<SR_GTYPES_NS::Texture*>(arg) == pTexture;
                }
                return false;
            }, pProperty->GetData())) {
                return false;
            }
            return true;
        });
    }
}