//
// Created by Nikita on 17.11.2020.
//

#include <Debug.h>
#include "Types/Material.h"
#include <Types/Mesh.h>
#include <Render/Shader.h>
#include <iostream>

using namespace Framework::Graphics::Types;

Material::Material(Texture *diffuse, Texture *normal, Texture *specular, Texture *glossiness) {
    if (!m_env)
        m_env = Environment::Get();

    SetDiffuse(diffuse);
    SetNormal(normal);
    SetSpecular(specular);
    SetGlossiness(glossiness);
}

Material::~Material() { }

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

void Material::SetDiffuse(Texture * tex) {
    if (tex)
        tex->AddUsePoint();

    if (m_diffuse) {
        m_diffuse->RemoveUsePoint();
        if (m_diffuse->GetCountUses() <= 1 && m_diffuse->IsEnabledAutoRemove())
            m_diffuse->Destroy();
    }

    m_diffuse = tex;
}
void Material::SetNormal(Texture *tex) {
    if (tex)
        tex->AddUsePoint();

    if (m_normal) {
        m_normal->RemoveUsePoint();
        if (m_normal->GetCountUses() <= 1 && m_normal->IsEnabledAutoRemove())
            m_normal->Destroy();
    }

    m_normal = tex;
}
void Material::SetSpecular(Texture* tex) {
    if (tex)
        tex->AddUsePoint();

    if (m_specular) {
        m_specular->RemoveUsePoint();
        if (m_specular->GetCountUses() <= 1 && m_specular->IsEnabledAutoRemove())
            m_specular->Destroy();
    }

    m_specular = tex;
}
void Material::SetGlossiness(Texture*tex) {
    if (tex)
        tex->AddUsePoint();

    if (m_glossiness) {
        m_glossiness->RemoveUsePoint();
        if (m_glossiness->GetCountUses() <= 1 && m_specular->IsEnabledAutoRemove())
            m_glossiness->Destroy();
    }

    m_glossiness = tex;
}

bool Material::SetTransparent(bool value) {
    m_transparent = value;

    return true;
}

bool Material::FreeTextures() {
    if (Debug::GetLevel() >= Debug::Level::Full)
        Debug::Log("Material::FreeTextures() : free material textures...");

    SetDiffuse(nullptr);
    SetNormal(nullptr);
    SetSpecular(nullptr);
    SetGlossiness(nullptr);

    return true;
}

Material *Material::Copy() {
    auto mat = new Material(m_diffuse, m_normal, m_specular, m_glossiness);

    mat->m_bloom = m_bloom;
    mat->m_color = m_color;
    mat->m_transparent = m_transparent;

    return mat;
}

