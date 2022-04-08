//
// Created by Nikita on 17.11.2020.
//

#include <Types/Material.h>

#include <Types/Mesh.h>
#include <Render/Shader.h>
#include <Types/Texture.h>

using namespace Framework::Graphics::Types;

Material::Material(Texture *diffuse, Texture *normal, Texture *specular, Texture *glossiness)
    : Helper::IResource(typeid(Material).name())
    , m_env(Environment::Get())
{
    SetTexture(diffuse, MAT_PROPERTY_DIFFUSE_TEXTURE);
    SetTexture(normal, MAT_PROPERTY_NORMAL_TEXTURE);
    SetTexture(specular, MAT_PROPERTY_SPECULAR_TEXTURE);
    SetTexture(glossiness, MAT_PROPERTY_GLOSSINESS_TEXTURE);
}

Material::~Material() {
    if (Debug::GetLevel() >= Debug::Level::Full) {
        SR_LOG("Material::FreeTextures() : free material textures...");
    }

    SetReadOnly(false);

    for (auto&& property : MAT_TEXTURE_PROPERTIES) {
        SetTexture(nullptr, property);
    }
}

void Material::UseOpenGL() const {
    //if (m_diffuse) {
    //    m_env->BindTexture(4, m_diffuse->GetID());
    //    Shader::GetCurrentShader()->SetInt("diffuseMap", 4);
        //m_mesh->m_shader->SetBool("hasDiffuse", true);
    // } //else{
        //m_env->BindTexture(1, 0);
        //m_mesh->m_shader->SetInt("diffuseMap", 1);
        //_mesh->m_shader->SetBool("hasDiffuse", false);
    //}
}

void Material::UseVulkan() {
    /*
     *   0 - model
     *   1 - view/proj
     *   2 - diffuse
     */

    if (auto&& diffuse = GetTexture(MAT_PROPERTY_DIFFUSE_TEXTURE)) {
        m_env->BindTexture(2, diffuse->GetID());
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

Framework::Helper::IResource* Material::Copy(Framework::Helper::IResource* destination) const {
    if (destination) {
        SR_WARN("Material::Copy() : destination ignored!");
    }

    auto material = new Material();

    material->SetBloom(m_bloom);
    material->SetTransparent(m_transparent);

    for (auto&& property : MAT_TEXTURE_PROPERTIES) {
        material->SetTexture(GetTexture(property), property);
    }

    for (auto&& property : MAT_COLOR_PROPERTIES) {
        material->SetColor(property, GetColor(property));
    }

    return Helper::IResource::Copy(material);
}

Material::Material()
    : Material(nullptr, nullptr, nullptr, nullptr)
{ }

Material *Material::Load(const std::string &name) {
    SR_GLOBAL_LOCK

    if (auto&& pMaterial = ResourceManager::Instance().Find<Material>(name))
        return pMaterial;

    const auto&& path = ResourceManager::Instance().GetMaterialsPath().Concat(name).ConcatExt("mat");
    if (auto doc = Xml::Document::Load(path); doc.Valid()) {
        auto matXml = doc.Root().GetNode("Material");

        auto material = new Material();

        if (auto shader = matXml.TryGetNode("Shader")) {
            auto&& render = RenderManager::Instance().Get("Main");
            auto&& pShader = Shader::Load(render, shader.GetAttribute("path").ToString());

            material->SetShader(pShader);
        }

        if (auto diffuse = matXml.TryGetNode("Diffuse"))
            material->SetTexture(Texture::Load(diffuse.GetAttribute("path").ToString()), MAT_PROPERTY_DIFFUSE_TEXTURE);

        if (auto color = matXml.TryGetNode("Color"))
            material->SetColor(MAT_PROPERTY_DIFFUSE_COLOR, Xml::NodeToColor<true>(color));

        material->SetId(name);

        material->SetReadOnly(matXml.TryGetAttribute("ReadOnly").ToBool(false));

        return material;
    }

    SR_ERROR("Material::Load() : file not found! Path: " + path.ToString());

    return nullptr;
}

Material *Material::GetDefault() {
    return m_default;
}

bool Material::InitDefault(Render* render) {
    if (!m_default) {
        if ((m_default = Material::Load("Engine/default")))
            m_default->AddUsePoint();

        return m_default->Register(render) && m_default->GetTexture(MAT_PROPERTY_DIFFUSE_TEXTURE);
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

    return IResource::Destroy();
}

bool Material::Register(Framework::Graphics::Render *render) {
    SRAssert(render);

    if (m_render) {
        SRAssert(render == m_render);
        return false;
    }

    m_render = render;

    for (auto&& property : MAT_TEXTURE_PROPERTIES) {
        if (auto&& pTexture = GetTexture(property); pTexture && !pTexture->HasRender()) {
            m_render->RegisterTexture(pTexture);
        }
    }

    return true;
}

void Material::UpdateSubscribers() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    for (auto&& subscriber : m_subscriptions)
        subscriber->UpdateUBO();
}

void Material::SetTexture(Texture *pTexture, MatProperty property) {
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
}

void Material::SetBloom(bool value) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    m_bloom = value;

    UpdateSubscribers();
}

void Material::SetShader(Framework::Graphics::Shader *shader) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    SRVerifyFalse(m_shader = shader);

    if (!m_shader)
        return;

    UpdateSubscribers();
}


