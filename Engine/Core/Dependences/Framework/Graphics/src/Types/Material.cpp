//
// Created by Nikita on 17.11.2020.
//

#include <Types/Material.h>

#include <Types/Mesh.h>
#include <Render/Shader.h>
#include <Types/Texture.h>
#include <ResourceManager/IResource.h>

namespace SR_GTYPES_NS {
    Material::Material()
        : SR_UTILS_NS::IResource(typeid(Material).name())
        , m_env(Environment::Get())
    { }

    void Material::Use() {
        for (const Material::Property& property : m_properties) {
            switch (property.type) {
                case ShaderVarType::Int:
                    m_shader->SetInt(property.id, std::get<int32_t>(property.data));
                    break;
                case ShaderVarType::Float:
                    m_shader->SetFloat(property.id, std::get<float_t>(property.data));
                    break;
                case ShaderVarType::Vec2:
                    m_shader->SetVec2(property.id, std::get<SR_MATH_NS::FVector2>(property.data).ToGLM());
                    break;
                case ShaderVarType::Vec3:
                    m_shader->SetVec3(property.id, std::get<SR_MATH_NS::FVector3>(property.data).ToGLM());
                    break;
                case ShaderVarType::Vec4:
                    m_shader->SetVec4(property.id, std::get<SR_MATH_NS::FVector4>(property.data).ToGLM());
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

    bool Material::SetTransparent(bool value) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (IsReadOnly())
            return false;

        m_transparent = value;

        for (auto&& subscriber : m_subscriptions)
            subscriber->OnTransparencyChanged();

        return true;
    }

    SR_UTILS_NS::IResource* Material::Copy(SR_UTILS_NS::IResource* destination) const {
        SRAssert2(false, "Material is not are copyable!");
        return nullptr;
    }

    Material* Material::Load(const std::string &name) {
        SR_GLOBAL_LOCK

        if (auto&& pMaterial = ResourceManager::Instance().Find<Material>(name))
            return pMaterial;

        const auto&& path = ResourceManager::Instance().GetMaterialsPath().Concat(name).ConcatExt("mat");
        if (auto doc = Xml::Document::Load(path); doc.Valid()) {
            auto matXml = doc.Root().GetNode("Material");

            auto material = new Material();

            if (auto&& shader = matXml.TryGetNode("Shader")) {
                auto&& render = RenderManager::Instance().Get("Main");
                auto&& pShader = Shader::Load(render, shader.GetAttribute("path").ToString());

                material->SetShader(pShader);
            }

            if (auto&& properties = matXml.TryGetNode("Properties")) {
                for (auto&& property : properties.GetNodes()) {

                }
            }

            material->SetId(name);

            material->SetReadOnly(matXml.TryGetAttribute("ReadOnly").ToBool(false));

            return material;
        }

        SR_ERROR("Material::Load() : file not found! Path: " + path.ToString());

        return nullptr;
    }

    Material* Material::GetDefault() {
        return m_default;
    }

    bool Material::InitDefault(Render* render) {
        if (!m_default) {
            if ((m_default = Material::Load("Engine/default"))) {
                m_default->AddUsePoint();
                return true;
            }
        }

        return false;
    }

    bool Material::FreeDefault() {
        SR_INFO("Material::FreeDefault() : free default material...");

        if (m_default) {
            if (m_default->GetCountUses() <= 1 && m_default->GetCountSubscriptions() == 0) {
                m_default->RemoveUsePoint();
                m_default->Destroy();

                m_default = nullptr;
                return true;
            }
            else {
                SRAssert2(false, Helper::Format("Material::FreeDefault() : the material is still in use! Count uses: %i", m_default->GetCountUses()).c_str());
                return false;
            }
        }

        SR_ERROR("Material::FreeDefault() : the material is nullptr!");

        return false;
    }

    void Material::Subscribe(Mesh *mesh) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        SRAssert(m_subscriptions.count(mesh) == 0);
        m_subscriptions.insert(mesh);
        AddUsePoint();
    }

    void Material::UnSubscribe(Mesh *mesh) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        SRAssert(GetCountUses() > 0);
        SRAssert(m_subscriptions.count(mesh) == 1);
        m_subscriptions.erase(mesh);

        RemoveUsePoint();

        if (m_subscriptions.empty() && GetCountUses() == 0)
            Destroy();
    }

    uint32_t Material::GetCountSubscriptions() const {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        return m_subscriptions.size();
    }

    bool Material::Destroy() {
        if (IsDestroyed())
            return false;

        SetReadOnly(false);
        SetShader(nullptr);

        for (Property& property : m_properties) {
            switch (property.type) {
                case ShaderVarType::Sampler2D:
                    SetTexture(property, nullptr);
                    break;
                default:
                    break;
            }
        }

        return IResource::Destroy();
    }

    void SR_GTYPES_NS::Material::UpdateSubscribers() {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
    }

    /*
    void SR_GTYPES_NS::Material::SetTexture(Texture *pTexture, MatProperty property) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (property >= MAT_PROPERTY_MAX_ENUM) {
            SRAssert(false);
            return;
        }

        if (IsReadOnly())
            return;

        std::visit([=](Property && arg) {
            if (std::holds_alternative<Texture*>(arg)) {
                if (auto&& oldTexture = std::get<Texture*>(arg)) {
                    oldTexture->RemoveUsePoint();

                    if (oldTexture->GetCountUses() <= 1 && oldTexture->IsEnabledAutoRemove())
                        oldTexture->Destroy();
                }

                if (pTexture)
                    pTexture->AddUsePoint();

                m_properties.at(static_cast<uint32_t>(property)) = pTexture;
            }
            else {
                SRAssert(false);
            }
        }, m_properties.at(static_cast<uint32_t>(property)));

        UpdateSubscribers();

        Environment::Get()->SetBuildState(false);
    }

    Texture *Material::GetTexture(MatProperty property) const {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (property >= MAT_PROPERTY_MAX_ENUM) {
            SRAssert(false);
            return nullptr;
        }

        return std::visit([](Property && arg) -> Texture* {
            if (std::holds_alternative<Texture*>(arg)) {
                return std::get<Texture*>(arg);
            }

            SRAssert(false);

            return nullptr;
        }, m_properties.at(static_cast<uint32_t>(property)));
    }

    void Material::SetColor(MatProperty property, float_t r, float_t g, float_t b) {
        SetColor(property, SR_MATH_NS::FColor(r, g, b, 1.f));
    }

    void Material::SetColor(MatProperty property, float_t r, float_t g, float_t b, float_t a) {
        SetColor(property, SR_MATH_NS::FColor(r, g, b, a));
    }

    void Material::SetColor(MatProperty property, const Framework::Helper::Math::FVector3& color) {
        SetColor(property, SR_MATH_NS::FColor(color.x, color.y, color.z, 1.f));
    }

    void Material::SetColor(MatProperty property, const glm::vec4 &color) {
        SetColor(property, SR_MATH_NS::FColor(color.r, color.g, color.b, color.a));
    }

    void Material::SetColor(MatProperty property, const Math::FColor &color) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (property >= MAT_PROPERTY_MAX_ENUM) {
            SRAssert(false);
            return;
        }

        if (IsReadOnly())
            return;

        std::visit([=](Property && arg) {
            if (std::holds_alternative<Texture*>(arg)) {
                m_properties.at(static_cast<uint32_t>(property)) = color;
            }
            else {
                SRAssert(false);
            }
        }, m_properties.at(static_cast<uint32_t>(property)));

        UpdateSubscribers();
    }

    SR_MATH_NS::FColor Material::GetColor(Framework::Graphics::Types::MatProperty property) const {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (property >= MAT_PROPERTY_MAX_ENUM) {
            SRAssert(false);
            return SR_MATH_NS::FColor();
        }

        return std::visit([](Property && arg) -> SR_MATH_NS::FColor {
            if (std::holds_alternative<SR_MATH_NS::FColor>(arg)) {
                return std::get<SR_MATH_NS::FColor>(arg);
            }

            SRAssert(false);

            return SR_MATH_NS::FColor();
        }, m_properties.at(static_cast<uint32_t>(property)));
    }*/

    void SR_GTYPES_NS::Material::SetBloom(bool value) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        m_bloom = value;

        UpdateSubscribers();
    }

    void SR_GTYPES_NS::Material::SetShader(Shader *shader) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (m_shader == shader) {
            return;
        }

        if (m_shader) {
            auto&& render = m_shader->GetRender();
            m_shader->RemoveUsePoint();
            if (m_shader->GetCountUses() == 0) {
                render->FreeShader(m_shader);
            }
            m_shader = nullptr;
        }

        if (!(m_shader = shader)) {
            return;
        }

        m_shader->AddUsePoint();

        for (auto&& [name, property] : m_shader->GetProperties()) {
            Property aProperty;

            aProperty.id = name;
            aProperty.displayName = name; // TODO: make a pretty name
            aProperty.data = GetVariantFromShaderVarType(property);
            aProperty.type = property;

            m_properties.emplace_back(aProperty);
        }

        UpdateSubscribers();
    }

    void Material::SetTexture(Material::Property &property, Texture *pTexture) {
        if (auto&& oldTexture = std::get<Texture*>(property.data)) {
            if (oldTexture == pTexture) {
                return;
            }

            oldTexture->RemoveUsePoint();

            if (oldTexture->GetCountUses() <= 1 && oldTexture->IsEnabledAutoRemove())
                oldTexture->Destroy();
        }

        if (pTexture)
            pTexture->AddUsePoint();

        property.data = pTexture;

        Environment::Get()->SetBuildState(false);
    }

    void Material::UseSamplers() {
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
}