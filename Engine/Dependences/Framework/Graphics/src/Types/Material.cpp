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

    if (diffuse){
        diffuse->AddUsePoint();
        this->m_diffuse = diffuse;
    }

    if (normal){
        normal->AddUsePoint();
        this->m_normal = normal;
    }

    if (specular){
        specular->AddUsePoint();
        this->m_specular = specular;
    }

    if (glossiness){
        glossiness->AddUsePoint();
        this->m_glossiness = glossiness;
    }
}

Material::~Material() {
    if (!m_texturesIsFree)
        Debug::Warn("Material::~Material() : textures is not free! Something went wrong... Memory leak possible...");

    if (m_diffuse){
        //m_diffuse->RemoveUsePoint();
        //if (m_diffuse->GetCountUses() == 1 && m_diffuse->EnableAutoRemove())
        //    m_diffuse->Destroy();
        m_diffuse = nullptr;
    }

    if (m_normal){
        //m_normal->RemoveUsePoint();
        //if (m_normal->GetCountUses() == 1 && m_normal->EnableAutoRemove())
        //    m_normal->Destroy();
        m_normal = nullptr;
    }

    if (m_specular){
        //m_specular->RemoveUsePoint();
        //if (m_specular->GetCountUses() == 1 && m_specular->EnableAutoRemove())
        //    m_specular->Destroy();
        m_specular = nullptr;
    }

    if (m_glossiness){
        //m_glossiness->RemoveUsePoint();
        //if (m_glossiness->GetCountUses() == 1 && m_glossiness->EnableAutoRemove())
        //    m_glossiness->Destroy();
        m_glossiness = nullptr;
    }
}

void Material::UseOpenGL() const {
    if (m_diffuse) {
        m_env->BindTexture(4, m_diffuse->GetID());
        m_mesh->m_shader->SetInt("diffuseMap", 4);
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

bool Material::SetMesh(Mesh *mesh) {
    if (m_mesh) {
        Helper::Debug::Error("Material::SetMesh() : mesh already set in material!\n\tOld mesh: " +
            m_mesh->GetResourceID() + "\n\tNew mesh: "+mesh->GetResourceID());
        return false;
    }

    m_mesh = mesh;
    return true;
}

void Material::SetDiffuse(Texture * tex) {
    if (tex)
        tex->AddUsePoint();

    if (m_diffuse)
        m_diffuse->RemoveUsePoint();

    m_diffuse = tex;
}

void Material::SetNormal(Texture *tex) {
    if (tex)
        tex->AddUsePoint();

    if (m_normal)
        m_normal->RemoveUsePoint();

    m_normal = tex;
}

void Material::SetSpecular(Texture* tex) {
    if (tex)
        tex->AddUsePoint();

    if (m_specular)
        m_specular->RemoveUsePoint();

    m_specular = tex;
}

void Material::SetGlossiness(Texture*tex) {
    if (tex)
        tex->AddUsePoint();

    if (m_glossiness)
        m_glossiness->RemoveUsePoint();

    m_glossiness = tex;
}

/*
Material*  Material::Copy() {
    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Material::Copy() : copy material...");

    auto* copy = new Material(m_diffuse, m_normal, m_specular, m_glossiness);

    copy->m_transparent = m_transparent;

    //copy->mesh - not copy!!!!

    return copy;
}*/

bool Material::SetTransparent(bool value) {
    if (m_mesh->IsCalculated()) {
        Debug::Error("Material::SetTransparent() : The mesh that this texture belongs to has already been calculated. It is no longer possible to set transparency properties.");
        return false;
    }

    m_transparent = value;

    return true;
}

bool Material::FreeTextures() {
    if (m_texturesIsFree) {
        Debug::Error("Material::FreeTextures() : textures already free! Something went wrong...");
        return false;
    }

    if (Debug::GetLevel() >= Debug::Level::Full)
        Debug::Log("Material::FreeTextures() : free material textures...");

    if (m_diffuse) {
        m_diffuse->RemoveUsePoint();
        if (m_diffuse->GetCountUses() <= 1 && m_diffuse->IsEnabledAutoRemove())
            m_diffuse->Destroy();
    }

    if (m_normal) {
        m_normal->RemoveUsePoint();
        if (m_normal->GetCountUses() <= 1 && m_normal->IsEnabledAutoRemove())
            m_normal->Destroy();
    }

    if (m_specular) {
        m_specular->RemoveUsePoint();
        if (m_specular->GetCountUses() <= 1 && m_specular->IsEnabledAutoRemove())
            m_specular->Destroy();
    }

    if (m_glossiness) {
        m_glossiness->RemoveUsePoint();
        if (m_glossiness->GetCountUses() <= 1 && m_glossiness->IsEnabledAutoRemove())
            m_glossiness->Destroy();
    }

    this->m_texturesIsFree = true;

    return true;
}

Material *Material::Copy() {
    auto mat = new Material(m_diffuse, m_normal, m_specular, m_glossiness);

    mat->m_bloom = m_bloom;
    mat->m_color = m_color;
    mat->m_transparent = m_transparent;

    return mat;
}

