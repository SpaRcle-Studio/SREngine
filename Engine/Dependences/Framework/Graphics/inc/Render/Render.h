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
    typedef std::map<uint32_t, std::vector<Types::Mesh*>> MeshGroups;

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
        size_t                        m_t                        = 0;
        size_t                        m_t2                       = 0;

        std::vector<Types::Mesh*>     m_newMeshes                = std::vector<Mesh*>();
        size_t                        m_countNewMeshes           = 0;
        std::vector<Types::Mesh*>     m_removeMeshes             = std::vector<Mesh*>();
        size_t                        m_countMeshesToRemove      = 0;

        MeshGroups                    m_meshGroups               = MeshGroups();
        std::map<uint32_t, uint32_t>  m_countMeshesInGroups      = std::map<uint32_t, uint32_t>();
        uint32_t                      m_totalCountMeshesInGroups = 0;

        std::vector<Types::Mesh*>     m_transparent_meshes       = std::vector<Types::Mesh*>();
        size_t                        m_countTransparentMeshes   = 0;

        size_t                        m_countTexturesToFree      = 0;
        std::vector<Types::Texture*>  m_textureToFree            = std::vector<Types::Texture*>();

        bool                          m_needDestroySkybox        = false;
        bool                          m_needSelectMeshes         = false;

        Shader*                       m_geometryShader           = nullptr;
        Shader*                       m_flatGeometryShader       = nullptr;
        //Shader*                     m_skyboxShader             = nullptr;
        //Shader*                     m_gridShader               = nullptr;

        EditorGrid*                   m_grid                     = nullptr;
        bool                          m_gridEnabled              = false;
        bool                          m_skyboxEnabled            = true;
        bool                          m_wireFrame                = false;

        Types::Skybox*                m_skybox                   = nullptr;
        ColorBuffer*                  m_colorBuffer              = nullptr;

        std::vector<Light*>           m_light                    = std::vector<Light*>();

        const PipeLine                m_pipeLine                 = PipeLine::Unknown;
    public:
        static Render* Allocate();
    public:
        [[nodiscard]] size_t GetAbsoluteCountMeshes() const noexcept { return m_totalCountMeshesInGroups + m_countTransparentMeshes; }
        [[nodiscard]] Types::Mesh* GetMesh(size_t absoluteID) noexcept;

        [[nodiscard]] size_t GetCountMeshesToRemove()     const noexcept { return m_countMeshesToRemove; }
        [[nodiscard]] size_t GetCountNewMeshes()          const noexcept { return m_countNewMeshes; }
        [[nodiscard]] size_t GetCountTransparentMeshes()  const noexcept { return m_countTransparentMeshes; }
    public:
        [[nodiscard]] SR_FORCE_INLINE bool IsRun() const noexcept { return m_isRun; }
        [[nodiscard]] SR_FORCE_INLINE bool IsInit() const noexcept { return m_isInit; }
    public:
        [[nodiscard]] SR_FORCE_INLINE ColorBuffer* GetColorBuffer() const noexcept { return this->m_colorBuffer; }

        SR_FORCE_INLINE void SetWireFrameEnabled(const bool& value) noexcept { this->m_wireFrame = value; }
        [[nodiscard]] SR_FORCE_INLINE bool GetWireFrameEnabled() const noexcept { return this->m_wireFrame; }
        SR_FORCE_INLINE void SetGridEnabled(bool value) { this->m_gridEnabled = value; }
        void SetSkybox(Skybox* skybox);
        SR_FORCE_INLINE void SetCurrentCamera(Camera* camera) noexcept { m_currentCamera = camera; }
        [[nodiscard]] SR_FORCE_INLINE Camera* GetCurrentCamera() const noexcept { return this->m_currentCamera; }
    public:
        void RemoveMesh(Types::Mesh* mesh);
        void RegisterMesh(Types::Mesh* mesh);
        void RegisterMeshes(const Helper::Types::List<Types::Mesh*>& meshes) {
            for (size_t i = 0; i < meshes.Size(); i++)
                this->RegisterMesh(meshes[i]);
        }
        bool DelayedDestroySkybox();
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
        virtual void UpdateGeometry() { }

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
