//
// Created by Nikita on 17.11.2020.
//
#include <easy/profiler.h>
#include "Render/Render.h"
#include <Render/Camera.h>
#include <iostream>

#include <Lighting/Light.h>
#include <Types/Skybox.h>
#include <Window/Window.h>
#include <Utils/StringUtils.h>

bool Framework::Graphics::Render::DrawGeometry() noexcept {
    //if (Helper::Debug::Profile()) {
    //    EASY_FUNCTION(profiler::colors::RichGreen);
    //    EASY_NONSCOPED_BLOCK("Render: drawing geometry", profiler::colors::DarkCyan);
    //}

    Shader::GetDefaultGeometryShader()->Use();
    this->m_currentCamera->UpdateShader(Shader::GetDefaultGeometryShader());

    //this->m_geometryShader->Use();
    //this->m_currentCamera->UpdateShader(m_geometryShader);

    if (m_wireFrame) {
        this->m_env->SetDepthTestEnabled(false);
        this->m_env->SetWireFrameEnabled(true);
        this->m_env->SetCullFacingEnabled(false);

        for (m_t = 0; m_t < m_countMeshes; m_t++)
            m_meshes[m_t]->Draw();

        this->m_env->SetWireFrameEnabled(false);
        this->m_env->SetDepthTestEnabled(true);
        this->m_env->SetCullFacingEnabled(true);
    } else {
        for (m_t = 0; m_t < m_countMeshes; m_t++)
            m_meshes[m_t]->Draw();
    }

    //this->m_env->UseShader(0);

    //if (Helper::Debug::Profile())
    //    EASY_END_BLOCK;

    return true;
}

bool Framework::Graphics::Render::DrawSkybox() noexcept {
    //if (Helper::Debug::Profile()) { EASY_FUNCTION(profiler::colors::Coral); }

    if (m_skybox && m_skyboxEnabled) {
        //m_skyboxShader->Use();
        //m_currentCamera->UpdateShader(m_skyboxShader);
        //m_skyboxShader->SetVec3("CamPos", m_currentCamera->GetGLPosition());
        m_skybox->Draw(m_currentCamera);
    }

    return true;
}

void Framework::Graphics::Render::DrawGrid() noexcept {
    if (!m_gridEnabled)
        return;

    if (this->m_grid)
        this->m_grid->Draw();
}

bool Framework::Graphics::Render::DrawTransparentGeometry() noexcept {
    return false;
}

bool Framework::Graphics::Render::Create(Window* window) { //, Camera* camera
    if (m_isCreate){
        Debug::Error("Render::Create() : render already create!");
        return false;
    }

    Debug::Graph("Render::Create() : creating render...");

    this->m_window = window;

    {
        this->m_geometryShader = new Shader(this, "geometry");
        this->m_flatGeometryShader  = new Shader(this, "flatGeometry");

        Shader::SetStandartGeometryShader(m_geometryShader);
    }

    this->m_grid = EditorGrid::Create("grid", this);

    this->m_isCreate = true;

    return true;
}

bool Framework::Graphics::Render::Init() {
    if (!m_isCreate) {
        Debug::Error("Render::Init() : render is not created!");
        return false;
    }

    if (m_isInit) {
        Debug::Error("Render::Init() : render already initialize!");
        return false;
    }

    Debug::Graph("Render::Init() : initializing render...");

    {
        //if (!m_geometryShader->Init()) {
        //    Debug::Error("Render::Init() : failed init geometry shader!");
        //    return false;
        //}
        //if (!m_skyboxShader->Init()) {
        //    Debug::Error("Render::Init() : failed init skybox shader!");
        //    return false;
        //}

        /*if (!m_stencilShader->Init()) {
            Debug::Error("Render::Init() : failed init stencil shader!");
            return false;
        }*/
    }

    m_isInit = true;

    return true;
}

bool Framework::Graphics::Render::Run() {
    if (!m_isInit) {
        Debug::Error("Render::Run() : render is not running!");
        return false;
    }

    if (m_isRun) {
        Debug::Error("Render::Run() : render already is running!");
        return false;
    }

    Debug::Graph("Render::Run() : running render...");

    this->m_isRun = true;

    return true;
}

bool Framework::Graphics::Render::Close() {
    if (!m_isRun) {
        Debug::Error("Render::Close() : render is not running!");
        return false;
    }

    if (m_isClose) {
        Debug::Error("Render::Close() : render already is closed");
        return false;
    }

    Debug::Graph("Render::Close() : close render...");

    //if (m_skyboxShader)
    //   m_skyboxShader->Free();

    this->m_manipulate->Destroy();
    this->m_manipulate->Free();

    if (m_geometryShader)
        m_geometryShader->Free();

    if (m_flatGeometryShader)
        m_flatGeometryShader->Free();

    if (this->m_grid)
        m_grid->Free();

    m_isRun = false;
    m_isClose = true;

    return true;
}

void Framework::Graphics::Render::RemoveMesh(Framework::Graphics::Types::Mesh *mesh) {
    m_mutex.lock();

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Render::RemoveMesh() : register \""+mesh->GetResourceID()+"\" mesh to remove...");

    this->m_removeMeshes.push_back(mesh);
    m_countMeshesToRemove++;
    m_mutex.unlock();
}

void Framework::Graphics::Render::RegisterMesh(Framework::Graphics::Types::Mesh *mesh) {
    if (!mesh){
        Debug::Error("Render::RegisterMesh() : mesh is nullptr!");
        return;
    }

    m_mutex.lock();

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Render::RegisterMesh() : register new \""+mesh->GetResourceID()+"\" mesh...");

    mesh->AddUsePoint();
    mesh->SetRender(this);
    this->m_newMeshes.push_back(mesh);
    m_countNewMeshes++;
    m_mutex.unlock();
}

void Framework::Graphics::Render::PollEvents() noexcept {
    // Temp value
    static Mesh* temp = nullptr;

    /*// New selected meshes
    if (m_countNewSelectedMeshes) {
        for (m_t = 0; m_t < m_countNewSelectedMeshes; m_t++)
            m_selectedMeshes.push_back(m_newSelectedMeshes[m_t]);
        m_countSelectedMeshes += m_countNewSelectedMeshes;

        m_countNewSelectedMeshes = 0;
        m_newSelectedMeshes.clear();
    }

    // Selected meshes to remove
    if (m_countRemoveSelectedMeshes){
        for (m_t = 0; m_t < m_countRemoveSelectedMeshes; m_t++) {
            temp = m_removeSelectedMeshes[m_t];
            for (m_t2 = 0; m_t2 < m_countSelectedMeshes; m_t2++)
                if (temp == m_selectedMeshes[m_t2]){
                    m_selectedMeshes.erase(m_selectedMeshes.begin() + m_t2);
                    break;
                }
        }
        m_countSelectedMeshes -= m_countRemoveSelectedMeshes;
        m_countRemoveSelectedMeshes = 0;

        m_removeSelectedMeshes.clear();
    }*/

    // Check exists new meshes
    if (m_countNewMeshes) {
        m_mutex.lock();

        for (m_t = 0; m_t < m_countNewMeshes; m_t++) {
            temp = m_newMeshes[m_t];

            // Add mesh to transparent meshes array or usual mesh array
            if (temp->GetMaterial()->IsTransparent()) {
                m_transparent_meshes.push_back(temp);
                m_countTransparentMeshes++;
            } else {
                m_meshes.push_back(temp);
                m_countMeshes++;
            }
        }

        m_newMeshes.clear(); // Clear new meshes array
        m_countNewMeshes = 0;

        m_mutex.unlock();
    }

    // Check meshes to remove from render
    if (m_countMeshesToRemove) {
        m_mutex.lock();

        for (m_t = 0; m_t < m_countMeshesToRemove; m_t++) {
            temp = m_removeMeshes[m_t];
            if (temp->IsCalculated())
                temp->FreeVideoMemory();

            // Remove mesh from transparent meshes array or usual mesh array
            if (temp->GetMaterial()->IsTransparent()) {
                for (m_t2 = 0; m_t2 < m_countTransparentMeshes; m_t2++)
                    if (m_transparent_meshes[m_t2] == temp) {
                        m_countTransparentMeshes--;
                        m_transparent_meshes.erase(m_transparent_meshes.begin() + m_t2);
                        temp->RemoveUsePoint();
                        break;
                    }
            } else {
                for (m_t2 = 0; m_t2 < m_countMeshes; m_t2++)
                    if (m_meshes[m_t2] == temp) {
                        m_countMeshes--;
                        m_meshes.erase(m_meshes.begin() + m_t2);
                        temp->RemoveUsePoint();
                        break;
                    }
            }
        }

        m_countMeshesToRemove = 0; // Clear meshes to remove array
        m_removeMeshes.clear();

        m_mutex.unlock();
    }

    // Free textures
    if (m_countTexturesToFree) {
        m_mutex.lock();

        for (m_t = 0; m_t < m_countTexturesToFree; m_t++) {
            if (m_textureToFree[m_t]->IsCalculated()) {
                m_textureToFree[m_t]->FreeVideoMemory();
            }
            else
                Debug::Error("Render::PoolEvents() : texture is not calculated! Something went wrong...");

            m_textureToFree[m_t]->RemoveUsePoint();
        }

        m_textureToFree.clear();
        m_countTexturesToFree = 0;

        m_mutex.unlock();
    }

    /*if (m_countSkyboxesToRemove){
        for (m_t = 0; m_t < m_countSkyboxesToRemove; m_t++) {
            Debug::Log("Render::PoolEvents() : free skybox video memory...");
            if (!m_skyboxesToRemove[m_t]->FreeVideoMemory())
                Debug::Error("Render::PoolEvents() : failed free skybox video memory!");
            else
                m_skyboxesToRemove[m_t]->SetIsVideoFree(true);
        }

        m_skyboxesToRemove.clear();
        m_countSkyboxesToRemove = 0;
        m_skybox = nullptr;
    }*/
    if (m_needDestroySkybox){
        m_mutex.lock();

        Debug::Graph("Render::PoolEvents() : free skybox video memory...");
        if (!m_skybox->FreeVideoMemory())
            Debug::Error("Render::PoolEvents() : failed free skybox video memory!");
        else
            m_skybox->SetIsVideoFree(true);

        m_skybox = nullptr;

        m_needDestroySkybox = false;

        m_mutex.unlock();
    }
}

Framework::Graphics::Render::Render() : m_env(Environment::Get()) {
    //std::cout <<  m_meshes.capacity() << std::endl;
    m_meshes.reserve(500 * 500);
    m_newMeshes.reserve(500);
    m_removeMeshes.reserve(500);

    this->m_manipulate = ManipulationTool::Create(this);
}

void Framework::Graphics::Render::SetSkybox(Framework::Graphics::Types::Skybox *skybox) {
    skybox->SetRender(this);
    this->m_skybox = skybox;
}

void Framework::Graphics::Render::FreeTexture(Framework::Graphics::Types::Texture *texture) {
    m_mutex.lock();

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Graph("Render::FreeTexture() : register texture to remove...");

    m_textureToFree.push_back(texture);
    m_countTexturesToFree++;

    m_mutex.unlock();
}

void Framework::Graphics::Render::RegisterTexture(Texture * texture) {
    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Graph("Render::RegisterTexture() : register new texture...");

    texture->AddUsePoint();
    texture->SetRender(this);
}

void Framework::Graphics::Render::DrawSingleColors() noexcept {
    this->m_flatGeometryShader->Use();

    this->m_currentCamera->UpdateShader(m_flatGeometryShader);

    if (!m_colorBuffer)
        this->m_colorBuffer = new ColorBuffer();

    this->m_colorBuffer->InitNames(this->GetAbsoluteCountMeshes());

    for (m_t = 0; m_t < m_countMeshes; m_t++){
        this->m_flatGeometryShader->SetInt("id", (int)m_t);
        this->m_flatGeometryShader->SetMat4("modelMat", m_meshes[m_t]->GetModelMatrix());

        this->m_colorBuffer->LoadName(m_t, Helper::StringUtils::IntToColor(m_t + 1));

        m_meshes[m_t]->SimpleDraw();
    }

    //this->m_manipulate->SimpleDraw(m_flatGeometryShader);

    this->m_env->UseShader(nullptr);
}

bool Framework::Graphics::Render::DrawSettingsPanel() {
    if (!m_isRun)
        return false;

    ImGui::Begin("Render settings");

    ImGui::Text("Pipeline name: %s", m_env->GetPipeLineName().c_str());

    ImGui::Text("Count meshes: %zu", m_countMeshes);
    ImGui::Text("Count transparent meshes: %zu", m_countTransparentMeshes);

    ImGui::Checkbox("Grid", &m_gridEnabled);
    ImGui::Checkbox("Skybox", &m_skyboxEnabled);
    ImGui::Checkbox("WireFrame", &m_wireFrame);

    ImGui::End();

    return true;
}

/*
void Framework::Graphics::Render::SelectMesh(Framework::Graphics::Types::Mesh *mesh) {
    m_mutex.lock();

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Graph("Render::SelectMesh() : select \""+ mesh->GetGeometryName() +"\"...");

    this->m_newSelectedMeshes.push_back(mesh);
    this->m_countNewSelectedMeshes++;

    m_mutex.unlock();
}

void Framework::Graphics::Render::DeselectMesh(Framework::Graphics::Types::Mesh *mesh) {
    m_mutex.lock();

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Graph("Render::DeselectMesh() : deselect \""+ mesh->GetGeometryName() +"\"...");

    this->m_removeSelectedMeshes.push_back(mesh);
    this->m_countRemoveSelectedMeshes++;

    m_mutex.unlock();
}

void Framework::Graphics::Render::DrawStencil() noexcept {

}*/

/*
void Framework::Graphics::Render::RegisterSkyboxToRemove(Framework::Graphics::Types::Skybox *skybox) {
    m_mutex.lock();

    Debug::Graph("Render::RegisterSkyboxToRemove() : register skybox to remove...");

    this->m_skyboxesToRemove.push_back(skybox);
    this->m_countSkyboxesToRemove++;

    m_mutex.unlock();
}
*/