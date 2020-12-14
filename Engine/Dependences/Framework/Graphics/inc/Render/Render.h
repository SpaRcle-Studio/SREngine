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

namespace Framework::Graphics::Types {
    class Skybox;
}

namespace Framework::Graphics {
    using namespace Framework::Graphics::Types;

    class Light;
    class Window;
    class Camera;

    class Render {
    public:
        Render();
    private:
        volatile bool           m_isCreate                          = false;
        volatile bool           m_isInit                            = false;
        volatile bool           m_isRun                             = false;
        volatile bool           m_isClose                           = false;
    private:
        Environment*            m_env                               = nullptr;

        Window*                 m_window                            = nullptr;
        Camera*                 m_currentCamera                     = nullptr;
        std::mutex              m_mutex                             = std::mutex();
        size_t                  m_t                                 = 0;
        size_t                  m_t2                                = 0;

        std::vector<Mesh*>      m_newMeshes                         = std::vector<Mesh*>();
        volatile size_t         m_countNewMeshes                    = 0;
        std::vector<Mesh*>      m_removeMeshes                      = std::vector<Mesh*>();
        volatile size_t         m_countMeshesToRemove               = 0;

        std::vector<Mesh*>      m_meshes                            = std::vector<Mesh*>();
        volatile size_t         m_countMeshes                       = 0;
        std::vector<Mesh*>      m_transparent_meshes                = std::vector<Mesh*>();
        volatile size_t         m_countTransparentMeshes            = 0;

        volatile size_t         m_countTexturesToFree               = 0;
        std::vector<Texture*>   m_textureToFree                     = std::vector<Texture*>();

        Shader*                 m_geometryShader                    = nullptr;
        Shader*                 m_stencilShader                     = nullptr;
        Shader*                 m_skyboxShader                      = nullptr;

        Skybox*                 m_skybox                            = nullptr;

        std::vector<Light*>     m_light                             = std::vector<Light*>();
    public:
        [[nodiscard]] size_t GetCountMeshesToRemove()     const noexcept { return m_countMeshesToRemove; }
        [[nodiscard]] size_t GetCountNewMeshes()          const noexcept { return m_countNewMeshes; }
        [[nodiscard]] size_t GetCountMeshes()             const noexcept { return m_countMeshes; }
        [[nodiscard]] size_t GetCountTransparentMeshes()  const noexcept { return m_countTransparentMeshes; }
    public:
        inline bool IsRun() const noexcept { return m_isRun; }
        inline bool IsInit() const noexcept { return m_isInit; }
    public:
        void SetSkybox(Skybox* skybox);
        inline void SetCurrentCamera(Camera* camera) noexcept { m_currentCamera = camera; }
    public:
        void RemoveMesh(Mesh* mesh);
        void RegisterMesh(Mesh* mesh);

        void RegisterTexture(Texture* texture);
        void FreeTexture(Texture* texture);
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
        void PoolEvents()               noexcept;
        bool DrawGeometry()             noexcept;
        bool DrawSkybox()               noexcept;
        bool DrawTransparentGeometry()  noexcept;
    };
}

#endif //GAMEENGINE_RENDER_H
