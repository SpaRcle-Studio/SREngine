//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_RENDER_H
#define GAMEENGINE_RENDER_H

#include <Render/Shader.h>
#include <Types/Mesh.h>
#include <vector>
#include <mutex>
#include <Environment/Environment.h>
#include <Types/EditorGrid.h>
#include <Render/ColorBuffer.h>
#include <Types/List.h>
#include <iostream>

namespace Framework::Graphics::Types {
    class Skybox;
}

namespace Framework::Graphics {
    typedef std::map<uint32_t, std::vector<Types::Mesh*>> MeshGroups;   // sizeof = 24
    typedef std::map<uint32_t, uint32_t> MeshGroupCounters;             // sizeof = 24

    struct MeshCluster { // sizeof = 52 without methods
        MeshGroups        m_groups   = MeshGroups();        // sizeof = 24
        MeshGroupCounters m_counters = MeshGroupCounters(); // sizeof = 24
        uint32_t          m_total    = 0;    // sizeof = 4

        inline bool Add(Types::Mesh* mesh) {
            //int32_t groupID =  Environment::Get()->GetPipeLine() == PipeLine::OpenGL ? mesh->GetVAO() : mesh->GetVBO();
            int32_t groupID = mesh->GetVBO();
            if (groupID < 0) {
                Helper::Debug::Error("MeshCluster::Add() : failed get mesh group id to add mesh!");
                return false;
            }

            auto find = this->m_groups.find(groupID);
            if (find == m_groups.end())
                m_groups[groupID] = {mesh};
            else
                find->second.push_back(mesh);

            m_counters[groupID]++;
            m_total++;

            return true;
        }

        inline bool Remove(Types::Mesh* mesh) {
            //int32_t groupID =  Environment::Get()->GetPipeLine() == PipeLine::OpenGL ? mesh->GetVAO() : mesh->GetVBO();
            int32_t groupID = mesh->GetVBO();
            if (groupID < 0) {
                Helper::Debug::Error("MeshCluster::Remove() : failed get mesh group id to remove mesh!");
                return false;
            }

            auto find = m_groups.find(groupID);
            if (find == m_groups.end()) {
                Helper::Debug::Error("MeshCluster::Remove() : mesh group to remove mesh not found!");
                return false;
            }

            auto& meshes = find->second;
            for (uint32_t i = 0; i < m_counters[groupID]; i++) {
                if (meshes[i] == mesh) {
                    m_counters[groupID]--;
                    m_total--;

                    meshes.erase(meshes.begin() + i);
                    mesh->RemoveUsePoint();

                    if (m_counters[groupID] == 0) {
                        m_groups.erase(groupID);
                        m_counters.erase(groupID);
                    }
                    return true;
                }
            }

            Helper::Debug::Error("MeshCluster::Remove() : mesh not found!");

            return false;
        }
    };

    using namespace Framework::Graphics::Types;

    class Light;
    class Window;
    class Camera;

    class Render {
    protected:
        Render();
    public:
        Render(const Render&) = delete;
    protected:
        volatile bool                 m_isCreate                 = false;
        volatile bool                 m_isInit                   = false;
        volatile bool                 m_isRun                    = false;
        volatile bool                 m_isClose                  = false;
    protected:
        Environment*                  m_env                      = nullptr;

        Window*                       m_window                   = nullptr;
        Camera*                       m_currentCamera            = nullptr;
        std::mutex                    m_mutex                    = std::mutex();

        std::vector<Types::Mesh*>     m_newMeshes                = std::vector<Mesh*>();
        std::vector<Types::Mesh*>     m_removeMeshes             = std::vector<Mesh*>();
        std::vector<Types::Texture*>  m_texturesToFree           = std::vector<Types::Texture*>();
        std::vector<Skybox*>          m_skyboxesToFreeVidMem     = std::vector<Skybox*>();

        MeshCluster                   m_geometry                 = { };
        MeshCluster                   m_transparentGeometry      = { };

        Types::Skybox*                m_newSkybox                = nullptr;
        Types::Skybox*                m_skybox                   = nullptr;

        Shader*                       m_geometryShader           = nullptr;
        Shader*                       m_transparentShader        = nullptr;
        Shader*                       m_flatGeometryShader       = nullptr;
        Shader*                       m_skyboxShader             = nullptr;

        ColorBuffer*                  m_colorBuffer              = nullptr;
        EditorGrid*                   m_grid                     = nullptr;

        bool                          m_gridEnabled              = false;
        bool                          m_skyboxEnabled            = true;
        bool                          m_wireFrame                = false;

        const PipeLine                m_pipeLine                 = PipeLine::Unknown;
    public:
        static Render* Allocate();
    public:
        [[nodiscard]] size_t GetAbsoluteCountMeshes() const noexcept { return m_geometry.m_total + m_transparentGeometry.m_total; }
        [[nodiscard]] Types::Mesh* GetMesh(size_t absoluteID) noexcept;

        [[nodiscard]] size_t GetCountTransparentMeshes()  const noexcept { return m_transparentGeometry.m_total; }
    public:
        [[nodiscard]] SR_FORCE_INLINE bool IsRun() const noexcept { return m_isRun; }
        [[nodiscard]] SR_FORCE_INLINE bool IsInit() const noexcept { return m_isInit; }
    public:
        [[nodiscard]] SR_FORCE_INLINE ColorBuffer* GetColorBuffer() const noexcept { return this->m_colorBuffer; }

        SR_FORCE_INLINE void SetWireFrameEnabled(const bool& value) noexcept { this->m_wireFrame = value; }
        [[nodiscard]] SR_FORCE_INLINE bool GetWireFrameEnabled() const noexcept { return this->m_wireFrame; }
        SR_FORCE_INLINE void SetGridEnabled(bool value) { this->m_gridEnabled = value; }
        void SetCurrentCamera(Camera* camera) noexcept;
        [[nodiscard]] SR_FORCE_INLINE Camera* GetCurrentCamera() const noexcept { return this->m_currentCamera; }
    public:
        void RemoveMesh(Types::Mesh* mesh);
        void RegisterMesh(Types::Mesh* mesh);
        void RegisterMeshes(const Helper::Types::List<Types::Mesh*>& meshes) {
            for (size_t i = 0; i < meshes.Size(); i++)
                this->RegisterMesh(meshes[i]);
        }

        /** \brief Can get a nullptr value for removing skybox */
        void SetSkybox(Skybox* skybox);
        bool FreeSkyboxMemory(Skybox* skybox);
        [[nodiscard]] Skybox* GetSkybox() const { return m_skybox; }

        void RegisterTexture(Types::Texture* texture);
        void FreeTexture(Types::Texture* texture);
    public:
        [[nodiscard]] inline Window* GetWindow() const noexcept { return m_window; }
    public:
        bool Create(Window* window); //, Camera* camera
        /** \warning call only from window thread */
        bool Init();
        /** \warning call only from window thread */
        bool Run();
        /** \warning call only from window thread */
        bool Close();
    public:
        /** \brief Check all render events. For example: new meshes, remove old meshes */
        void PollEvents();
    public:
        virtual void UpdateUBOs() { }

        virtual bool DrawGeometry() = 0;
        virtual bool DrawSkybox()   = 0;
    public:
        virtual void DrawGrid()                 noexcept = 0;
        virtual void DrawSingleColors()         noexcept = 0;
        virtual bool DrawTransparentGeometry()  noexcept = 0;
        virtual bool DrawSettingsPanel()        noexcept = 0;
    };
}

#endif //GAMEENGINE_RENDER_H
