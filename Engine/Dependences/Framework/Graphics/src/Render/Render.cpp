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

bool Framework::Graphics::Render::Create(Window* window) {
    if (m_isCreate){
        Debug::Error("Render::Create() : render already create!");
        return false;
    }

    Debug::Graph("Render::Create() : creating render...");

    this->m_window = window;

    {
        this->m_geometryShader = new Shader(this, "engine/geometry");
        this->m_geometryShader->SetVertex(
                {Vertices::Mesh3DVertex::GetDescription()},
                Vertices::Mesh3DVertex::GetAttributes());
        this->m_geometryShader->SetUniforms({
                {{0, UBOType::Common}, sizeof(Mesh3DUBO)},   // binding 0 - mesh   (model mat)
                {{5, UBOType::Shared}, sizeof(ProjViewUBO)}, // binding 1 - shader (view & proj mat)
        });
        /*
                         descriptor write
           [descriptor]       [bind]      [data]
                0               0       model uniform
                0               1       diffuse
                0               2       normal
                0               3       specular
                0               4       glossiness
                1               5       view & proj uniform
         */
        this->m_geometryShader->SetCreateInfo({
              .polygonMode  = PolygonMode::Fill,
              .cullMode     = CullMode::Back,
              .depthCompare = DepthCompare::LessOrEqual,
              .blendEnabled = true,
              .depthWrite   = true,
              .depthTest    = true
        });


        Shader::SetStandardGeometryShader(m_geometryShader);
    }

    {
        this->m_transparentShader = new Shader(this, "engine/transparent");
        this->m_transparentShader->CopyVertexAndUniformsInfo(m_geometryShader);
        this->m_transparentShader->SetCreateInfo({
             .polygonMode  = PolygonMode::Fill,
             .cullMode     = CullMode::Back,
             .depthCompare = DepthCompare::LessOrEqual,
             .blendEnabled = true,
             .depthWrite   = false,
             .depthTest    = true
        });
    }

    this->m_flatGeometryShader = new Shader(this, "engine/flatGeometry");

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
    data.append("\n\tNew meshes       : " + std::to_string(m_countNewMeshes));
    data.append("\n\tMeshes to remove : " + std::to_string(m_countMeshesToRemove));
    Debug::Graph("Render::Close() : close render..." + data);

    if (m_geometryShader)
        m_geometryShader->Free();

    if (m_transparentShader)
        m_transparentShader->Free();

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

void Framework::Graphics::Render::PollEvents() {
    // Temp value
    static Mesh* temp = nullptr;

    // Check exists new meshes
    if (m_countNewMeshes) {
        m_mutex.lock();

        for (m_t = 0; m_t < m_countNewMeshes; m_t++) {
            temp = m_newMeshes[m_t];

            // Add mesh to transparent meshes array or usual mesh array

            if (temp->GetMaterial()->IsTransparent()) {
                if (!m_transparentGeometry.Add(temp))
                    Helper::Debug::Error("Render::PollEvents() : failed to add transparent mesh to cluster!");
            } else
                if (!m_geometry.Add(temp))
                    Helper::Debug::Error("Render::PollEvents() : failed to add mesh to cluster!");

        }

        m_newMeshes.clear(); // Clear new meshes array
        m_countNewMeshes = 0;

        this->m_env->SetBuildState(false);

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
                if (!m_transparentGeometry.Remove(temp))
                    Helper::Debug::Error("Render::PollEvents() : failed to remove transparent geometry mesh!");
            }
            else
                if (!m_geometry.Remove(temp))
                    Helper::Debug::Error("Render::PollEvents() : failed to remove geometry mesh!");
        }

        m_countMeshesToRemove = 0; // Clear meshes to remove array
        m_removeMeshes.clear();

        this->m_env->SetBuildState(false);

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

        this->m_env->SetBuildState(false);

        m_mutex.unlock();
    }

    // If need destroy skybox
    if (m_needDestroySkybox){
        m_mutex.lock();

        Debug::Graph("Render::PoolEvents() : free skybox video memory...");
        if (!m_skybox->FreeVideoMemory())
            Debug::Error("Render::PoolEvents() : failed free skybox video memory!");
        else
            m_skybox->SetIsVideoFree(true);

        m_skybox = nullptr;
        m_needDestroySkybox = false;

        this->m_env->SetBuildState(false);

        m_mutex.unlock();
    }
}

Framework::Graphics::Render::Render() : m_env(Environment::Get()), m_pipeLine(m_env->GetPipeLine()) {
    //std::cout <<  m_meshes.capacity() << std::endl;
    //!!!!!!!!!m_meshes.reserve(500 * 500);
    m_newMeshes.reserve(500);
    m_removeMeshes.reserve(500);
}

void Framework::Graphics::Render::SetSkybox(Framework::Graphics::Types::Skybox *skybox) {
    if (m_skybox) {
        Helper::Debug::Error("Render::SetSkybox() : skybox already exists!");
        return;
    }

    skybox->SetRender(this);
    this->m_skybox = skybox;
    this->m_env->SetBuildState(false);
}

void Framework::Graphics::Render::FreeTexture(Framework::Graphics::Types::Texture *texture) {
    m_mutex.lock();

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Graph("Render::FreeTexture() : register texture to remove...");

    m_textureToFree.push_back(texture);
    m_countTexturesToFree++;

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

bool Framework::Graphics::Render::DelayedDestroySkybox()  {
    if (!this->m_skybox){
        Debug::Error("Render::DelayedDestroySkybox() : skybox already destroyed!");
        return false;
    }

    if (m_needDestroySkybox){
        Debug::Error("Render::DelayedDestroySkybox() : skybox already will bee destroyed!");
        return false;
    }

    Debug::Graph("Render::DelayedDestroySkybox() : destroying skybox...");

    this->m_needDestroySkybox = true;
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
