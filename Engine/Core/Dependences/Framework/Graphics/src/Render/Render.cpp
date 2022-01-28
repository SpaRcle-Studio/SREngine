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

    //Codegen::ShaderGenerator::Instance()->Generate("geometry", "", Shader::Flags::Diffuse | Shader::Flags::Normal | Shader::Flags::GBuffer);

    this->InsertShader(Shader::StandardID::Geometry, Shader::Load(this, "geometry"));
    this->InsertShader(Shader::StandardID::Transparent, Shader::Load(this, "transparent"));
    this->InsertShader(Shader::StandardID::Skybox, Shader::Load(this, "skybox"));
    this->InsertShader(Shader::StandardID::DebugWireframe, Shader::Load(this, "debugWireframe"));

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
        Debug::Log("Render::RemoveMesh() : register \"" + mesh->GetResourceId() + "\" mesh to remove...");

    this->m_removeMeshes.push(mesh);
}

void Framework::Graphics::Render::RegisterMesh(Framework::Graphics::Types::Mesh *mesh) {
    SRAssert(mesh);
    SRAssert(mesh->GetMaterial());

    if (!mesh->GetShader()) {
        Debug::Error("Render::RegisterMesh() : mesh have not shader! \n\tResource Id: " + mesh->GetResourceId());
        return;
    }

    const std::lock_guard<std::mutex> lock(m_mutex);

    if (Debug::GetLevel() >= Debug::Level::Full)
        Debug::Log("Render::RegisterMesh() : register new \"" + mesh->GetResourceId() + "\" mesh...");

    mesh->AddUsePoint();
    mesh->SetRender(this);
    this->m_newMeshes.emplace_back(mesh);
}

void Framework::Graphics::Render::PollEvents() {
    std::lock_guard<std::mutex> lock(m_mutex);
    bool needRebuild = false;

    //! Check exists new meshes
    if (!m_newMeshes.empty()) {
        for (auto mesh : m_newMeshes) {
            // Add mesh to transparent meshes array or usual mesh array

            if (mesh->GetMaterial()->IsTransparent()) {
                SRAssert(m_transparentGeometry.Add(mesh))
            } else {
                SRAssert(m_geometry.Add(mesh))
            }
        }

        m_newMeshes.clear(); // Clear new meshes array

        this->m_env->SetBuildState(false);
    }

    //! Check meshes to remove from render
    while (!m_removeMeshes.empty()) {
        const auto &mesh = m_removeMeshes.front();
        if (mesh->IsCalculated())
            mesh->FreeVideoMemory();

        // Remove mesh from transparent meshes array or usual mesh array

        if (mesh->GetMaterial()->IsTransparent()) {
            SRAssert(m_transparentGeometry.Remove(mesh))
        } else {
            SRAssert(m_geometry.Remove(mesh))
        }

        needRebuild = true;
        m_removeMeshes.pop();
    }

    //! Free textures
    if (!m_texturesToFree.empty()) {
        for (auto& textureToFree : m_texturesToFree) {
            if (textureToFree->IsCalculated())
                textureToFree->FreeVideoMemory();
            else
                Debug::Error("Render::PoolEvents() : texture is not calculated! Something went wrong...");

            textureToFree->RemoveUsePoint();
        }

        m_texturesToFree.clear();

        needRebuild = true;
    }

    //! Free skyboxes
    if (!m_skyboxesToFreeVidMem.empty()) {
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
    }

    //! Set new skybox
    if (m_skybox.m_new != m_skybox.m_current) {
        m_skybox.m_current = m_skybox.m_new;
    }

    if (needRebuild)
        this->m_env->SetBuildState(false);
}

Framework::Graphics::Render::Render() : m_env(Environment::Get()), m_pipeLine(m_env->GetPipeLine()) {
    m_newMeshes.reserve(500);
}

void Framework::Graphics::Render::SetSkybox(Framework::Graphics::Types::Skybox *skybox) {
    std::lock_guard<std::mutex> lock(m_mutex);

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
    std::lock_guard<std::mutex> lock(m_mutex);

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Graph("Render::FreeTexture() : register texture to remove...");

    m_texturesToFree.push_back(texture);
}
void Framework::Graphics::Render::RegisterTexture(Types::Texture * texture) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Graph("Render::RegisterTexture() : register new texture...");

    texture->AddUsePoint();
    texture->SetRender(this);
}

bool Framework::Graphics::Render::FreeSkyboxMemory(Skybox* skybox) {
    std::lock_guard<std::mutex> lock(m_mutex);

    this->m_skyboxesToFreeVidMem.emplace_back(skybox);

    return true;
}

Framework::Graphics::Render *Framework::Graphics::Render::Allocate() {
    if (Environment::Get()->GetPipeLine() == PipeLine::OpenGL)
        return static_cast<Render *>(new Impl::OpenGLRender());
    else if (Environment::Get()->GetPipeLine() == PipeLine::Vulkan) {
        return static_cast<Render *>(new Impl::VulkanRender());
    } else
        return nullptr;
}

void Framework::Graphics::Render::SetCurrentCamera(Framework::Graphics::Camera *camera) noexcept  {
    m_currentCamera = camera;
}

bool Framework::Graphics::Render::InsertShader(uint32_t id, Shader* shader) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (id >= m_shaders.size())
        m_shaders.resize(id + 1);

    if (m_shaders[id]) {
        Helper::Debug::Error("Render::InsertShader() : the specified place is already occupied! \n\tID: " + std::to_string(id));
        return false;
    }

    m_shaders[id] = shader;

    return true;
}

Framework::Graphics::Shader *Framework::Graphics::Render::FindShader(uint32_t id) const {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_shaders.size() <= id || !m_shaders[id])
        return nullptr;

    return m_shaders[id];
}

void Framework::Graphics::Render::Synchronize() {
    bool empty;

ret:
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        empty = m_newMeshes.empty() && m_removeMeshes.empty() && m_texturesToFree.empty() && m_skyboxesToFreeVidMem.empty();
    }

    if (!empty) {
        Helper::Types::Thread::Sleep(50);
        goto ret;
    }
}
