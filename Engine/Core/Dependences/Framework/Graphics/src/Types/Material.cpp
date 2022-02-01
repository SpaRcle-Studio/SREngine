//
// Created by Nikita on 17.11.2020.
//

#include <Debug.h>
#include "Types/Material.h"
#include <Types/Mesh.h>
#include <Render/Shader.h>
#include <iostream>

using namespace Framework::Graphics::Types;

Material::Material(Texture *diffuse, Texture *normal, Texture *specular, Texture *glossiness)
    : Helper::IResource(typeid(Material).name())
{
    if (!m_env)
        m_env = Environment::Get();

    SetDiffuse(diffuse);
    SetNormal(normal);
    SetSpecular(specular);
    SetGlossiness(glossiness);
}

Material::~Material() {
    if (Debug::GetLevel() >= Debug::Level::Full)
        Debug::Log("Material::FreeTextures() : free material textures...");

    SetReadOnly(false);

    SetDiffuse(nullptr);
    SetNormal(nullptr);
    SetSpecular(nullptr);
    SetGlossiness(nullptr);
}

void Material::UseOpenGL() const {
    if (m_diffuse) {
        m_env->BindTexture(4, m_diffuse->GetID());
        Shader::GetCurrentShader()->SetInt("diffuseMap", 4);
        //m_mesh->m_shader->SetBool("hasDiffuse", true);
    } //else{
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

    if (m_diffuse) {
        m_env->BindTexture(2, m_diffuse->GetID());
    }
}

void Material::SetDiffuse(Texture* texture) {
    if (IsReadOnly()) return;

    if (texture)
        texture->AddUsePoint();

    if (m_diffuse) {
        m_diffuse->RemoveUsePoint();
        if (m_diffuse->GetCountUses() <= 1 && m_diffuse->IsEnabledAutoRemove()) {
            m_diffuse->Destroy();
        }
    }

    m_diffuse = texture;

    Environment::Get()->SetBuildState(false);
}
void Material::SetNormal(Texture *tex) {
    if (IsReadOnly()) return;

    if (tex)
        tex->AddUsePoint();

    if (m_normal) {
        m_normal->RemoveUsePoint();
        if (m_normal->GetCountUses() <= 1 && m_normal->IsEnabledAutoRemove())
            m_normal->Destroy();
    }

    m_normal = tex;

    Environment::Get()->SetBuildState(false);
}
void Material::SetSpecular(Texture* tex) {
    if (IsReadOnly()) return;

    if (tex)
        tex->AddUsePoint();

    if (m_specular) {
        m_specular->RemoveUsePoint();
        if (m_specular->GetCountUses() <= 1 && m_specular->IsEnabledAutoRemove())
            m_specular->Destroy();
    }

    m_specular = tex;

    Environment::Get()->SetBuildState(false);
}

void Material::SetGlossiness(Texture*tex) {
    if (IsReadOnly()) return;

    if (tex)
        tex->AddUsePoint();

    if (m_glossiness) {
        m_glossiness->RemoveUsePoint();
        if (m_glossiness->GetCountUses() <= 1 && m_specular->IsEnabledAutoRemove())
            m_glossiness->Destroy();
    }

    m_glossiness = tex;

    Environment::Get()->SetBuildState(false);
}

bool Material::SetTransparent(bool value) {
    if (IsReadOnly())
        return false;

    m_transparent = value;
    Environment::Get()->SetBuildState(false);
    return true;
}

Framework::Helper::IResource* Material::Copy(Framework::Helper::IResource* destination) const {
    if (destination)
        Helper::Debug::Warn("Material::Copy() : destination ignored!");

    auto material = new Material(m_diffuse, m_normal, m_specular, m_glossiness);

    material->SetBloom(m_bloom);
    material->SetColor(m_color);
    material->SetTransparent(m_transparent);

    return Helper::IResource::Copy(material);
}

Material::Material()
    : Material(nullptr, nullptr, nullptr, nullptr)
{ }

Material *Material::Load(const std::string &name) {
    if (auto resource = ResourceManager::Instance().Find<Material>(name + ".mat"))
        return dynamic_cast<Material*>(resource);

    if (auto doc = Xml::Document::Load(ResourceManager::Instance().GetMaterialsPath().Concat(name).ConcatExt("mat")); doc.Valid()) {
        auto matXml = doc.Root().GetNode("Material");

        auto material = new Material();

        if (auto diffuse = matXml.TryGetNode("Diffuse"))
            material->SetDiffuse(Texture::Load(diffuse.GetAttribute("Path").ToString()));

        if (auto color = matXml.TryGetNode("Color"))
            material->SetColor(Xml::NodeToColor(color));

        material->SetId(name);

        material->SetReadOnly(matXml.TryGetAttribute("ReadOnly").ToBool(false));

        return material;
    }

    Helper::Debug::Error("Material::Load() : file not found! Path: " + name + ".mat");
    return nullptr;
}

Material *Material::GetDefault() {
    return m_default;
}

bool Material::InitDefault(Render* render) {
    if (!m_default) {
        if ((m_default = Material::Load("Engine/default")))
            m_default->AddUsePoint();

        return m_default->Register(render);
    }

    return false;
}

bool Material::FreeDefault() {
    Helper::Debug::Info("Material::FreeDefault() : free default material...");

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

    Helper::Debug::Error("Material::FreeDefault() : the material is nullptr!");
    return false;
}

void Material::Subscribe(Mesh *mesh) {
    std::lock_guard<std::mutex> lock(m_mutex);

    SRAssert(m_subscriptions.count(mesh) == 0);
    m_subscriptions.insert(mesh);
    AddUsePoint();
}

void Material::UnSubscribe(Mesh *mesh) {
    std::lock_guard<std::mutex> lock(m_mutex);

    SRAssert(m_subscriptions.count(mesh) == 1);
    m_subscriptions.erase(mesh);
    RemoveUsePoint();

    if (m_subscriptions.empty() && GetCountUses() == 0)
        Destroy();
}

uint32_t Material::GetCountSubscriptions() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_subscriptions.size();
}

bool Material::Destroy() {
    if (IsDestroy())
        return false;

    Helper::ResourceManager::Instance().Destroy(this);

    return IResource::Destroy();
}

void Material::SetColor(glm::vec4 color) {
    if (IsReadOnly())
        return;

    m_color = color;
    Environment::Get()->SetBuildState(false);
}

void Material::SetColor(const Math::FColor &color) {
    if (IsReadOnly())
        return;

    m_color = color;
    Environment::Get()->SetBuildState(false);
}

bool Material::Register(Framework::Graphics::Render *render) {
    SRAssert(render);

    if (m_render) {
        SRAssert(render == m_render);
        return false;
    }

    m_render = render;

    if (m_diffuse    && !m_diffuse->HasRender())    m_render->RegisterTexture(m_diffuse);
    if (m_normal     && !m_normal->HasRender())     m_render->RegisterTexture(m_normal);
    if (m_specular   && !m_specular->HasRender())   m_render->RegisterTexture(m_specular);
    if (m_glossiness && !m_glossiness->HasRender()) m_render->RegisterTexture(m_glossiness);

    return true;
}


