//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_RENDER_H
#define GAMEENGINE_RENDER_H

#include <Types/Mesh.h>
#include <Environment/Environment.h>
#include <Types/EditorGrid.h>
#include <Render/ColorBuffer.h>
#include <Utils/Types/List.h>

#include <Render/MeshCluster.h>

#include <Types/Geometry/IndexedMesh.h>
#include <Utils/Types/SafeQueue.h>

namespace SR_GRAPH_NS::Types {
    class Skybox;
    class Texture;
    class Camera;
    class Shader;
}

namespace SR_GRAPH_NS {
    /// TODO: to refactoring

    // first - current, second - new
    struct RenderSkybox {
        Types::Skybox* m_current;
        Types::Skybox* m_new;
    };

    class Light;
    class Window;

    class Render : public Helper::NonCopyable {
    protected:
        Render(std::string name);

    public:
        ~Render() override;

    public:
        SR_NODISCARD bool IsRun() const { return m_isRun; }
        SR_NODISCARD bool IsInit() const { return m_isInit; }
        SR_NODISCARD bool GetWireFrameEnabled() const { return m_wireFrame; }
        SR_NODISCARD ColorBuffer* GetColorBuffer() const { return m_colorBuffer; }
        SR_NODISCARD Types::Camera* GetCurrentCamera() const { return m_currentCamera; }

        void SetWireFrameEnabled(const bool& value) { m_wireFrame = value; }
        void SetGridEnabled(bool value) { m_gridEnabled = value; }
        void SetCurrentCamera(Types::Camera* camera);

    public:
        void Synchronize();
        bool IsClean();

        void ReRegisterMesh(SR_GTYPES_NS::Mesh* mesh);
        void RemoveMesh(Types::Mesh* mesh);
        void RegisterMesh(Types::Mesh* mesh);
        void RegisterMeshes(const Helper::Types::List<Types::Mesh*>& meshes) {
            for (size_t i = 0; i < meshes.Size(); i++)
                this->RegisterMesh(meshes[i]);
        }

        /** \brief Can get a nullptr value for removing skybox */
        void SetSkybox(SR_GTYPES_NS::Skybox* skybox);
        bool FreeSkyboxMemory(SR_GTYPES_NS::Skybox* skybox);
        [[nodiscard]] SR_GTYPES_NS::Skybox* GetSkybox() const { return m_skybox; }

        void RegisterTexture(SR_GTYPES_NS::Texture* texture);
        void FreeTexture(SR_GTYPES_NS::Texture* texture);
        void FreeShader(Types::Shader* shader);
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

        virtual void CalculateAll() = 0;
        virtual void DrawGeometry() = 0;
        virtual void DrawSkybox()   = 0;
    public:
        virtual void DrawGrid()                 = 0;
        virtual void DrawSingleColors()         = 0;
        virtual void DrawTransparentGeometry()  = 0;
        virtual void DrawSettingsPanel()        = 0;

    protected:
        std::atomic<bool>             m_isCreate                 = false;
        std::atomic<bool>             m_isInit                   = false;
        std::atomic<bool>             m_isRun                    = false;
        std::atomic<bool>             m_isClose                  = false;

        bool                          m_gridEnabled              = false;
        bool                          m_wireFrame                = false;

        Window*                       m_window                   = nullptr;
        Types::Camera*                m_currentCamera            = nullptr;
        mutable std::recursive_mutex  m_mutex                    = std::recursive_mutex();

        // TO_REFACTORING
        std::vector<Types::Mesh*>     m_newMeshes                = std::vector<Types::Mesh*>();
        std::queue<Types::Mesh*>      m_removeMeshes             = std::queue<Types::Mesh*>();
        std::vector<Types::Texture*>  m_texturesToFree           = std::vector<Types::Texture*>();
        std::vector<Types::Skybox*>   m_skyboxesToFreeVidMem     = std::vector<Types::Skybox*>();
        std::unordered_set<Types::Texture*>  m_textures          = std::unordered_set<Types::Texture*>();

        MeshCluster                   m_geometry                 = { };
        MeshCluster                   m_transparentGeometry      = { };

        Types::Skybox*                m_skybox                   = nullptr;

        SR_HTYPES_NS::SafeQueue<Types::Shader*> m_shadersToFree         = {};

        ColorBuffer*                  m_colorBuffer              = nullptr;
        //EditorGrid*                   m_grid                     = nullptr;
        Environment*                  m_env                      = nullptr;

        const PipeLine                m_pipeLine                 = PipeLine::Unknown;
        const std::string             m_renderName               = "Unnamed";

    };
}

#endif //GAMEENGINE_RENDER_H
