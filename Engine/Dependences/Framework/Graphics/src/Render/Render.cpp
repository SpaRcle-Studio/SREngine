//
// Created by Nikita on 17.11.2020.
//

#include <iostream>

#include <Render/Render.h>
#include <Render/Camera.h>
#include <Lighting/Light.h>
#include <Types/Skybox.h>
#include <Window/Window.h>

#include <Render/Implementations/VulkanRender.h>
#include <Render/Implementations/OpenGLRender.h>

#include <Render/ShaderGenerator.h>

bool Framework::Graphics::Render::Create(Window* window) {
    if (m_isCreate){
        Debug::Error("Render::Create() : render already create!");
        return false;
    }

    Debug::Graph("Render::Create() : creating render...");

    this->m_window = window;

    Codegen::ShaderGenerator::Instance()->Generate("geometry", "", Shader::Flags::Diffuse | Shader::Flags::Normal | Shader::Flags::GBuffer);

    this->InsertShader(Shader::StandardID::Geometry, Shader::Load(this, "geometry"));
    this->InsertShader(Shader::StandardID::Transparent, Shader::Load(this, "transparent"));
    this->InsertShader(Shader::StandardID::Skybox, Shader::Load(this, "skybox"));
    this->InsertShader(Shader::StandardID::DebugWireframe, Shader::Load(this, "debugWireframe"));

    Shader::SetStandardGeometryShader(m_shaders[Shader::StandardID::Geometry]);

    this->m_grid = EditorGrid::Create("engine/grid", this);

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

    auto data = std::string();
    data.append("\n\tT meshes         : " + std::to_string(m_geometry.m_total));
    data.append("\n\tNew meshes       : " + std::to_string(m_newMeshes.size()));
    data.append("\n\tMeshes to remove : " + std::to_string(m_removeMeshes.size()));
    Debug::Graph("Render::Close() : close render..." + data);

    for (auto& shader : m_shaders) {
        if (shader) {
            shader->Free();
            shader = nullptr;
        }
    }

    if (this->m_grid)
        m_grid->Free();

    if (m_skybox.m_current) {
        if (m_env->IsWindowOpen())
            m_skybox.m_current->FreeVideoMemory();
        else
            Helper::Debug::Warn("Render::Close() : window is close, can't free skybox video memory!");
        m_skybox.m_current->Free();
        m_skybox.m_current = nullptr;
    }

    m_isRun = false;
    m_isClose = true;

    return true;
}

void Framework::Graphics::Render::RemoveMesh(Framework::Graphics::Types::Mesh *mesh) {
    const std::lock_guard<std::mutex> lock(m_mutex);

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Render::RemoveMesh() : register \"" + mesh->GetResourceID() + "\" mesh to remove...");

    this->m_removeMeshes.emplace_back(mesh);
}
void Framework::Graphics::Render::RegisterMesh(Framework::Graphics::Types::Mesh *mesh) {
    if (!mesh){
        Debug::Error("Render::RegisterMesh() : mesh is nullptr!");
        return;
    }

    const std::lock_guard<std::mutex> lock(m_mutex);

    if (Debug::GetLevel() >= Debug::Level::Full)
        Debug::Log("Render::RegisterMesh() : register new \""+mesh->GetResourceID()+"\" mesh...");

    mesh->AddUsePoint();
    mesh->SetRender(this);
    this->m_newMeshes.emplace_back(mesh);
}

void Framework::Graphics::Render::PollEvents() {
    //! Check exists new meshes
    if (!m_newMeshes.empty()) {
        m_mutex.lock();

        for (auto & m_newMesh : m_newMeshes) {
            // Add mesh to transparent meshes array or usual mesh array

            if (m_newMesh->GetMaterial()->IsTransparent()) {
                if (!m_transparentGeometry.Add(m_newMesh))
                    Helper::Debug::Error("Render::PollEvents() : failed to add transparent mesh to cluster!");
            } else
                if (!m_geometry.Add(m_newMesh))
                    Helper::Debug::Error("Render::PollEvents() : failed to add mesh to cluster!");

        }

        m_newMeshes.clear(); // Clear new meshes array

        this->m_env->SetBuildState(false);

        m_mutex.unlock();
    }

    //! Check meshes to remove from render
    if (!m_removeMeshes.empty()) {
        m_mutex.lock();

        for (auto & m_removeMesh : m_removeMeshes) {
            if (m_removeMesh->IsCalculated())
                m_removeMesh->FreeVideoMemory();

            // Remove mesh from transparent meshes array or usual mesh array

            if (m_removeMesh->GetMaterial()->IsTransparent()) {
                if (!m_transparentGeometry.Remove(m_removeMesh))
                    Helper::Debug::Error("Render::PollEvents() : failed to remove transparent geometry mesh!");
            }
            else
                if (!m_geometry.Remove(m_removeMesh))
                    Helper::Debug::Error("Render::PollEvents() : failed to remove geometry mesh!");
        }

        m_removeMeshes.clear();

        this->m_env->SetBuildState(false);

        m_mutex.unlock();
    }

    //! Free textures
    if (!m_texturesToFree.empty()) {
        m_mutex.lock();

        for (auto& textureToFree : m_texturesToFree) {
            if (textureToFree->IsCalculated())
                textureToFree->FreeVideoMemory();
            else
                Debug::Error("Render::PoolEvents() : texture is not calculated! Something went wrong...");

            textureToFree->RemoveUsePoint();
        }

        m_texturesToFree.clear();

        this->m_env->SetBuildState(false);

        m_mutex.unlock();
    }

    //! Free skyboxes
    if (!m_skyboxesToFreeVidMem.empty()) {
        m_mutex.lock();

        Debug::Graph("Render::PoolEvents() : free skyboxes video memory...");
        for (auto skybox : m_skyboxesToFreeVidMem) {
            if (skybox == m_skybox.m_current)
                m_skybox.m_current = nullptr;

            if (skybox == m_skybox.m_new) {
                Debug::Warn("Render::PoolEvents() : skybox installed as new but marked for removal!");
                m_skybox.m_new = nullptr;
            }

            if (!skybox->FreeVideoMemory())
                Debug::Error("Render::PoolEvents() : failed to free skybox video memory!");
        }
        m_skyboxesToFreeVidMem.clear();

        m_mutex.unlock();
    }

    //! Set new skybox
    if (m_skybox.m_new != m_skybox.m_current) {
        m_skybox.m_current = m_skybox.m_new;
    }
}

Framework::Graphics::Render::Render() : m_env(Environment::Get()), m_pipeLine(m_env->GetPipeLine()) {
    //std::cout <<  m_meshes.capacity() << std::endl;
    //!!!!!!!!!m_meshes.reserve(500 * 500);
    m_newMeshes.reserve(500);
    m_removeMeshes.reserve(500);
}

void Framework::Graphics::Render::SetSkybox(Framework::Graphics::Types::Skybox *skybox) {
    if (skybox)
        Helper::Debug::Log("Render::SetSkybox() : set new \"" + skybox->GetName() + "\" skybox...");
    else
        Helper::Debug::Log("Render::SetSkybox() : set a nullptr skybox...");

    skybox->SetRender(this);
    if (m_skybox.m_current != skybox) {
        m_skybox.m_new = skybox;
        this->m_env->SetBuildState(false);
    }
}

void Framework::Graphics::Render::FreeTexture(Framework::Graphics::Types::Texture *texture) {
    m_mutex.lock();

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Graph("Render::FreeTexture() : register texture to remove...");

    m_texturesToFree.push_back(texture);

    m_mutex.unlock();
}
void Framework::Graphics::Render::RegisterTexture(Types::Texture * texture) {
    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Graph("Render::RegisterTexture() : register new texture...");

    texture->AddUsePoint();
    texture->SetRender(this);
}

Framework::Graphics::Types::Mesh *Framework::Graphics::Render::GetMesh(size_t absoluteID) noexcept {
    // TODO: See
    if (absoluteID < m_geometry.m_total) {
        for (auto const& [key, val] : m_geometry.m_groups) {
            if (absoluteID < m_geometry.m_counters[key]) {
                return val[abs(int32_t(m_geometry.m_total - m_geometry.m_counters[key]) - (int32_t)absoluteID)]; // TODO: can be reason crash!
            } else continue;
        }
    }
    else {
        //return this->m_transparent_meshes[absoluteID];
        Helper::Debug::Error("Render::GetMesh() : TODO!");
        // TODO!
        return nullptr;
    }

    return nullptr;
}

bool Framework::Graphics::Render::FreeSkyboxMemory(Skybox* skybox) {
    m_mutex.lock();
    this->m_skyboxesToFreeVidMem.emplace_back(skybox);
    m_mutex.unlock();
    return true;
}

Framework::Graphics::Render *Framework::Graphics::Render::Allocate() {
    if (Environment::Get()->GetPipeLine() == PipeLine::OpenGL)
        return new Impl::OpenGLRender();
    else if (Environment::Get()->GetPipeLine() == PipeLine::Vulkan) {
        return new Impl::VulkanRender();
    } else
        return nullptr;
}

void Framework::Graphics::Render::SetCurrentCamera(Framework::Graphics::Camera *camera) noexcept  {
    m_currentCamera = camera;
}

bool Framework::Graphics::Render::InsertShader(uint32_t id, Shader* shader) {
    if (id >= m_shaders.size())
        m_shaders.resize(id + 1);

    if (m_shaders[id]) {
        Helper::Debug::Error("Render::InsertShader() : the specified place is already occupied! \n\tID: " + std::to_string(id));
        return false;
    }

    m_shaders[id] = shader;

    return true;
}
