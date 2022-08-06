//
// Created by Nikita on 17.11.2020.
//

#include <Render/Render.h>
#include <Types/Skybox.h>
#include <Types/Material.h>
#include <Types/Shader.h>

namespace SR_GRAPH_NS {
    Render::Render(std::string name)
        : m_env(Environment::Get())
        , m_pipeLine(Environment::Get()->GetPipeLine())
        , m_renderName(name)
    {
        m_newMeshes.reserve(500);
    }

    Render::~Render() {
        SRAssert(IsClean());
    }

    bool Render::Create(Window* window) {
        if (m_isCreate) {
            SR_ERROR("Render::Create() : render already create!");
            return false;
        }

        SR_GRAPH("Render::Create() : creating render...");

        m_window = window;

        //InsertShader(Shader::StandardID::Skybox, Shader::Load("skybox"));
        //InsertShader(Shader::StandardID::DebugWireframe, Shader::Load("debugWireframe"));

        //m_grid = EditorGrid::Create("engine/grid", this);

        m_isCreate = true;

        return true;
    }

    bool Render::Init() {
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
    bool Render::Run() {
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

    bool Render::Close() {
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
        SR_GRAPH_LOG("Render::Close() : close render..." + data);

        //if (m_grid) {
        //    m_grid->Free();
        //}

        m_isRun = false;
        m_isClose = true;

        return true;
    }

    void Render::RemoveMesh(SR_GTYPES_NS::Mesh *mesh) {
        const std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("Render::RemoveMesh() : register \"" + mesh->GetResourceId() + "\" mesh to remove...");
        }

        m_removeMeshes.push(mesh);
    }

    void Render::RegisterMesh(SR_GTYPES_NS::Mesh *mesh) {
        if (!SRVerifyFalse(!mesh)) {
            return;
        }

        //if (!mesh->GetMaterial()) {
        //    SR_WARN("Render::RegisterMesh() : mesh have not material! Try use default material... \n\tMesh resource id: " + mesh->GetResourceId());
        //    if (auto&& material = SR_GTYPES_NS::Material::GetDefault()) {
        //        mesh->SetMaterial(material);
        //    }
        //    else {
        //        SR_ERROR("Render::RegisterMesh() : failed to get default material, something went wrong...");
        //        return;
        //    }
        //}

        if (!mesh->GetShader()) {
            SRAssert2(false, "Render::RegisterMesh() : mesh have not shader! \n\tResource Id: " + mesh->GetResourceId());
            return;
        }

        const std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Full) {
            SR_LOG("Render::RegisterMesh() : register new \"" + mesh->GetResourceId() + "\" mesh...");
        }

        mesh->AddUsePoint();
        //mesh->SetRender(this);
        m_newMeshes.emplace_back(mesh);
    }

    void Render::PollEvents() {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        bool needRebuild = false;

        //! Check exists new meshes
        //if (!m_newMeshes.empty()) {
        //    for (auto mesh : m_newMeshes) {
        //        // Add mesh to transparent meshes array or usual mesh array
//
        //        if (mesh->GetMaterial()->IsTransparent()) {
        //            SRVerifyFalse(!m_transparentGeometry.Add(mesh));
        //        }
        //        else {
        //            SRVerifyFalse(!m_geometry.Add(mesh));
        //        }
        //    }
//
        //    m_newMeshes.clear(); // Clear new meshes array
//
        //    needRebuild = true;
        //}

        while (auto&& shader = m_shadersToFree.Pop(nullptr)) {
            SRAssert(shader->GetCountUses() == 0);

            shader->FreeVideoMemory();

            if (shader->GetCountUses() == 0 && !shader->IsDestroyed()) {
                shader->Destroy();
            }

            needRebuild = true;
        }

        ////! Check meshes to remove from render
        //while (!m_removeMeshes.empty()) {
        //    const auto &mesh = m_removeMeshes.front();
//
        //    if (mesh->GetMaterial()->IsTransparent()) {
        //        SRVerifyFalse2(!m_transparentGeometry.Remove(mesh), "Mesh not found! Id: " + mesh->GetResourceId());
        //    }
        //    else {
        //        SRVerifyFalse2(!m_geometry.Remove(mesh), "Mesh not found! Id: " + mesh->GetResourceId());
        //    }
//
        //    if (mesh->IsCalculated())
        //        mesh->FreeVideoMemory();
//
        //    needRebuild = true;
        //    m_removeMeshes.pop();
        //}

        //! Free textures
      // if (!m_texturesToFree.empty()) {
      //     for (auto& textureToFree : m_texturesToFree) {
      //         SR_GRAPH_LOG("Render::PoolEvents() : free texture...\n\tResource id:" +
      //                      textureToFree->GetResourceId() + "\n\tTexture id: " + std::to_string(textureToFree->FastGetId()));

      //         if (textureToFree->IsCalculated()) {
      //             textureToFree->FreeVideoMemory();
      //         }

      //         textureToFree->RemoveUsePoint();

      //         m_textures.erase(textureToFree);
      //     }

      //     m_texturesToFree.clear();

      //     needRebuild = true;
      // }

      // if (needRebuild)
      //     m_env->SetBuildState(false);
    }

    void Render::SetSkybox(SR_GTYPES_NS::Skybox *skybox) {
        SR_SCOPED_LOCK

        if (skybox == m_skybox) {
            return;
        }

        if (skybox) {
            SR_LOG("Render::SetSkybox() : set new \"" + skybox->GetResourceId() + "\" skybox...");
        }
        else {
            SR_LOG("Render::SetSkybox() : set a nullptr skybox...");
        }

        if (m_skybox) {
            m_skybox->FreeVideoMemory();
            m_skybox->RemoveUsePoint();
        }

        if ((m_skybox = skybox)) {
            m_skybox->AddUsePoint();
        }

        m_env->SetBuildState(false);
    }

    void Render::FreeTexture(SR_GTYPES_NS::Texture *texture) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_GRAPH("Render::FreeTexture() : register texture to remove...");
        }

        m_texturesToFree.push_back(texture);
    }

    void Render::RegisterTexture(Types::Texture * texture) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_GRAPH("Render::RegisterTexture() : register new texture...");
        }

        texture->AddUsePoint();
        //texture->SetRender(this);
        m_textures.insert(texture);
    }

    bool Render::FreeSkyboxMemory(SR_GTYPES_NS::Skybox* skybox) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        m_skyboxesToFreeVidMem.emplace_back(skybox);

        return true;
    }

    void Render::SetCurrentCamera(Framework::Graphics::Types::Camera *camera)  {
        m_currentCamera = camera;
    }

    void Render::Synchronize() {
        bool empty = false;

    ret:
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex);
            empty = m_newMeshes.empty() && m_removeMeshes.empty() && !m_skybox && m_texturesToFree.empty() && m_skyboxesToFreeVidMem.empty();
        }

        if (!empty) {
            Helper::Types::Thread::Sleep(50);
            goto ret;
        }
    }

    bool Render::IsClean() {
        SR_SCOPED_LOCK

        return m_newMeshes.empty() &&
               m_removeMeshes.empty() &&
               m_texturesToFree.empty() &&
               m_textures.empty() &&
              // m_transparentGeometry.Empty() &&
              // m_geometry.Empty() &&
               m_skyboxesToFreeVidMem.empty() &&
               m_shadersToFree.Empty();
    }

    void Framework::Graphics::Render::ReRegisterMesh(SR_GTYPES_NS::Mesh *mesh) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        SRAssert(false);
    }

    void Render::FreeShader(Types::Shader *shader) {
        m_shadersToFree.Push(shader);
    }
}