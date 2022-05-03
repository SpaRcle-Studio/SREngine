//
// Created by Nikita on 17.11.2020.
//

#include <Render/Render.h>
#include <Types/Skybox.h>
#include <Types/Material.h>

Framework::Graphics::Render::Render(std::string name)
    : m_env(Environment::Get())
    , m_pipeLine(Environment::Get()->GetPipeLine())
    , m_renderName(name)
{
    m_newMeshes.reserve(500);
}

bool Framework::Graphics::Render::Create(Window* window) {
    if (m_isCreate) {
        SR_ERROR("Render::Create() : render already create!");
        return false;
    }

    SR_GRAPH("Render::Create() : creating render...");

    m_window = window;

    InsertShader(Shader::StandardID::Skybox, Shader::Load(this, "skybox"));
    InsertShader(Shader::StandardID::DebugWireframe, Shader::Load(this, "debugWireframe"));

    m_grid = EditorGrid::Create("engine/grid", this);

    m_isCreate = true;

    return true;
}

bool Framework::Graphics::Render::Init() {
    if (!m_isCreate) {
        SR_ERROR("Render::Init() : render is not created!");
        return false;
    }

    if (m_isInit) {
        SR_ERROR("Render::Init() : render already initialize!");
        return false;
    }

    SR_GRAPH("Render::Init() : initializing render...");

    m_isInit = true;

    return true;
}
bool Framework::Graphics::Render::Run() {
    if (!m_isInit) {
        SR_ERROR("Render::Run() : render is not running!");
        return false;
    }

    if (m_isRun) {
        SR_ERROR("Render::Run() : render already is running!");
        return false;
    }

    SR_GRAPH("Render::Run() : running render...");

    m_isRun = true;

    return true;
}
bool Framework::Graphics::Render::Close() {
    if (!m_isRun) {
        SR_ERROR("Render::Close() : render is not running!");
        return false;
    }

    if (m_isClose) {
        SR_ERROR("Render::Close() : render already is closed");
        return false;
    }

    auto data = std::string();
    data.append("\n\tNew meshes       : " + std::to_string(m_newMeshes.size()));
    data.append("\n\tMeshes to remove : " + std::to_string(m_removeMeshes.size()));
    Debug::Graph("Render::Close() : close render..." + data);

    for (auto& shader : m_shaders) {
        if (shader) {
            shader->RemoveUsePoint();
            shader->FreeVideoMemory();
            shader->Destroy();
            shader = nullptr;
        }
    }

    if (m_grid)
        m_grid->Free();

    if (m_skybox.m_current) {
        if (m_env->IsWindowOpen()) {
            m_skybox.m_current->FreeVideoMemory();
        }
        else {
            SR_WARN("Render::Close() : window is close, can't free skybox video memory!");
        }
        m_skybox.m_current->Free();
        m_skybox.m_current = nullptr;
    }

    m_isRun = false;
    m_isClose = true;

    return true;
}

void Framework::Graphics::Render::RemoveMesh(Framework::Graphics::Types::Mesh *mesh) {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (Debug::GetLevel() >= Debug::Level::High)
        SR_LOG("Render::RemoveMesh() : register \"" + mesh->GetResourceId() + "\" mesh to remove...");

    m_removeMeshes.push(mesh);
}

void Framework::Graphics::Render::RegisterMesh(Framework::Graphics::Types::Mesh *mesh) {
    SRAssert(mesh);
    SRAssert(mesh->GetMaterial());

    if (!mesh->GetShader()) {
        SRAssert2(false, "Render::RegisterMesh() : mesh have not shader! \n\tResource Id: " + mesh->GetResourceId());
        return;
    }

    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (Debug::GetLevel() >= Debug::Level::Full)
        SR_LOG("Render::RegisterMesh() : register new \"" + mesh->GetResourceId() + "\" mesh...");

    mesh->AddUsePoint();
    mesh->SetRender(this);
    m_newMeshes.emplace_back(mesh);
}

void Framework::Graphics::Render::PollEvents() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    bool needRebuild = false;

    //! Check exists new meshes
    if (!m_newMeshes.empty()) {
        for (auto mesh : m_newMeshes) {
            // Add mesh to transparent meshes array or usual mesh array

            if (mesh->GetMaterial()->IsTransparent()) {
                SRVerifyFalse(m_transparentGeometry.Add(mesh))
            }
            else {
                SRVerifyFalse(m_geometry.Add(mesh))
            }
        }

        m_newMeshes.clear(); // Clear new meshes array

        needRebuild = true;
    }

    while (!m_shadersToFree.empty()) {
        const auto &shader = m_shadersToFree.front();

        SRAssert(shader->GetCountUses() == 0);

        shader->FreeVideoMemory();

        if (shader->GetCountUses() == 0 && !shader->IsDestroyed()) {
            shader->Destroy();
        }

        needRebuild = true;
        m_shadersToFree.pop();
    }

    //! Check meshes to remove from render
    while (!m_removeMeshes.empty()) {
        const auto &mesh = m_removeMeshes.front();

        if (mesh->GetMaterial()->IsTransparent()) {
            SRVerifyFalse2(m_transparentGeometry.Remove(mesh), "Mesh not found! Id: " + mesh->GetResourceId());
        }
        else {
            SRVerifyFalse2(m_geometry.Remove(mesh), "Mesh not found! Id: " + mesh->GetResourceId());
        }

        if (mesh->IsCalculated())
            mesh->FreeVideoMemory();

        needRebuild = true;
        m_removeMeshes.pop();
    }

    //! Free textures
    if (!m_texturesToFree.empty()) {
        for (auto& textureToFree : m_texturesToFree) {
            Helper::Debug::Graph("Render::PoolEvents() : free texture \"" + textureToFree->GetName() + "\"");
            if (textureToFree->IsCalculated())
                textureToFree->FreeVideoMemory();

            textureToFree->RemoveUsePoint();
            m_textures.erase(textureToFree);
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

        needRebuild = true;
    }

    //! Set new skybox
    if (m_skybox.m_new != m_skybox.m_current) {
        m_skybox.m_current = m_skybox.m_new;
    }

    if (needRebuild)
        m_env->SetBuildState(false);
}

void Framework::Graphics::Render::SetSkybox(Framework::Graphics::Types::Skybox *skybox) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (skybox) {
        SR_LOG("Render::SetSkybox() : set new \"" + skybox->GetName() + "\" skybox...");
    }
    else {
        SR_LOG("Render::SetSkybox() : set a nullptr skybox...");
    }

    skybox->SetRender(this);
    if (m_skybox.m_current != skybox) {
        m_skybox.m_new = skybox;
        m_env->SetBuildState(false);
    }
}

void Framework::Graphics::Render::FreeTexture(Framework::Graphics::Types::Texture *texture) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (Debug::GetLevel() >= Debug::Level::High) {
        SR_GRAPH("Render::FreeTexture() : register texture to remove...");
    }

    m_texturesToFree.push_back(texture);
}
void Framework::Graphics::Render::RegisterTexture(Types::Texture * texture) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (Debug::GetLevel() >= Debug::Level::High) {
        SR_GRAPH("Render::RegisterTexture() : register new texture...");
    }

    texture->AddUsePoint();
    texture->SetRender(this);
    m_textures.insert(texture);
}

bool Framework::Graphics::Render::FreeSkyboxMemory(SR_GTYPES_NS::Skybox* skybox) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    m_skyboxesToFreeVidMem.emplace_back(skybox);

    return true;
}

void Framework::Graphics::Render::SetCurrentCamera(Framework::Graphics::Camera *camera) noexcept  {
    m_currentCamera = camera;
}

bool Framework::Graphics::Render::InsertShader(uint32_t id, Shader* shader) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (id >= m_shaders.size())
        m_shaders.resize(id + 1);

    if (m_shaders[id]) {
        SR_ERROR("Render::InsertShader() : the specified place is already occupied! \n\tID: " + std::to_string(id));
        return false;
    }

    shader->AddUsePoint();
    m_shaders[id] = shader;

    return true;
}

Framework::Graphics::Shader *Framework::Graphics::Render::FindShader(uint32_t id) const {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_shaders.size() <= id || !m_shaders[id])
        return nullptr;

    return m_shaders[id];
}

void Framework::Graphics::Render::Synchronize() {
    bool empty;

ret:
    {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        empty = m_newMeshes.empty() && m_removeMeshes.empty() && m_texturesToFree.empty() && m_skyboxesToFreeVidMem.empty();
    }

    if (!empty) {
        Helper::Types::Thread::Sleep(50);
        goto ret;
    }
}

bool Framework::Graphics::Render::IsClean() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    return m_newMeshes.empty() &&
           m_removeMeshes.empty() &&
           m_texturesToFree.empty() &&
           m_textures.empty() &&
           m_transparentGeometry.Empty() &&
           m_geometry.Empty() &&
           m_skyboxesToFreeVidMem.empty() &&
           m_shadersToFree.empty();
}

void Framework::Graphics::Render::ReRegisterMesh(SR_GTYPES_NS::Mesh *mesh) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    /*TODO: UNSAFE
    if (!mesh->IsRegistered()) {
        SRAssert2(false, "Mesh isn't registered!");
        return;
    }

    if (!m_geometry.Remove(mesh)) {
        SRVerifyFalse2(m_transparentGeometry.Remove(mesh), "Mesh not found!");
    }

    if (mesh->GetMaterial()->IsTransparent()) {
        SRVerifyFalse(m_transparentGeometry.Add(mesh))
    }
    else {
        SRVerifyFalse(m_geometry.Add(mesh))
    }

    m_env->SetBuildState(false);*/
}

void Framework::Graphics::Render::FreeShader(Framework::Graphics::Shader *shader) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    m_shadersToFree.push(shader);
}
