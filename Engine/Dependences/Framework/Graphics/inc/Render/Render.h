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

#include "Types/ManipulationTool.h"

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
        volatile bool              m_isCreate                          = false;
        volatile bool              m_isInit                            = false;
        volatile bool              m_isRun                             = false;
        volatile bool              m_isClose                           = false;
    private:
        Environment*               m_env                               = nullptr;

        Window*                    m_window                            = nullptr;
        Camera*                    m_currentCamera                     = nullptr;
        std::mutex                 m_mutex                             = std::mutex();
        size_t                     m_t                                 = 0;
        size_t                     m_t2                                = 0;

        /*// Selected meshes
        size_t                     m_countNewSelectedMeshes            = 0;
        std::vector<Mesh*>         m_newSelectedMeshes                 = std::vector<Mesh*>();
        size_t                     m_countRemoveSelectedMeshes         = 0;
        std::vector<Mesh*>         m_removeSelectedMeshes              = std::vector<Mesh*>();
        size_t                     m_countSelectedMeshes               = 0;
        std::vector<Mesh*>         m_selectedMeshes                    = std::vector<Mesh*>();*/

        std::vector<Mesh*>         m_newMeshes                         = std::vector<Mesh*>();
        size_t                     m_countNewMeshes                    = 0;
        std::vector<Mesh*>         m_removeMeshes                      = std::vector<Mesh*>();
        size_t                     m_countMeshesToRemove               = 0;

        std::vector<Mesh*>         m_meshes                            = std::vector<Mesh*>();
        size_t                     m_countMeshes                       = 0;
        std::vector<Mesh*>         m_transparent_meshes                = std::vector<Mesh*>();
        size_t                     m_countTransparentMeshes            = 0;

        size_t                     m_countTexturesToFree               = 0;
        std::vector<Texture*>      m_textureToFree                     = std::vector<Texture*>();

        //std::vector<Skybox*>       m_skyboxesToRemove                  = std::vector<Skybox*>();
        //size_t                     m_countSkyboxesToRemove             = 0;
        bool                       m_needDestroySkybox                 = false;

        Shader*                    m_geometryShader                    = nullptr;
        Shader*                    m_flatGeometryShader                = nullptr;
        //Shader*                    m_skyboxShader                      = nullptr;
        //Shader*                    m_gridShader                        = nullptr;

        EditorGrid*                m_grid                              = nullptr;
        bool                       m_gridEnabled                       = false;

        Skybox*                    m_skybox                            = nullptr;
        ColorBuffer*               m_colorBuffer                       = nullptr;

        std::vector<Light*>        m_light                             = std::vector<Light*>();

        bool                       m_needSelectMeshes                  = false;

        Types::ManipulationTool*   m_manipulate                        = nullptr;
    public:
        [[nodiscard]] ManipulationTool* GetManipulationTool() const {
            return this->m_manipulate;
        }

        [[nodiscard]] size_t GetAbsoluteCountMeshes()     const noexcept { return m_countMeshes + m_countTransparentMeshes; }
        [[nodiscard]] Mesh* GetMesh(size_t absoluteID)    const noexcept { // TODO: See
            if (absoluteID < m_countMeshes)
                return this->m_meshes[absoluteID];
            else
                return this->m_transparent_meshes[absoluteID];
        }

        [[nodiscard]] size_t GetCountMeshesToRemove()     const noexcept { return m_countMeshesToRemove; }
        [[nodiscard]] size_t GetCountNewMeshes()          const noexcept { return m_countNewMeshes; }
        [[nodiscard]] size_t GetCountMeshes()             const noexcept { return m_countMeshes; }
        [[nodiscard]] size_t GetCountTransparentMeshes()  const noexcept { return m_countTransparentMeshes; }
    public:
        [[nodiscard]] inline bool IsRun() const noexcept { return m_isRun; }
        [[nodiscard]] inline bool IsInit() const noexcept { return m_isInit; }
    public:
        [[nodiscard]] inline ColorBuffer* GetColorBuffer() const noexcept { return this->m_colorBuffer; }

        void SetGridEnabled(bool value) { this->m_gridEnabled = value; }
        void SetSkybox(Skybox* skybox);
        inline void SetCurrentCamera(Camera* camera) noexcept { m_currentCamera = camera; }
        [[nodiscard]] inline Camera* GetCurrentCamera() const noexcept { return this->m_currentCamera; }
        //[[nodiscard]] inline bool HasSelectedMeshes() const noexcept { return this->m_countSelectedMeshes != 0; }
    public:
        void RemoveMesh(Mesh* mesh);
        void RegisterMesh(Mesh* mesh);
        void RegisterMeshes(const Helper::Types::List<Mesh*>& meshes) {
            for (size_t i = 0; i < meshes.Size(); i++)
                this->RegisterMesh(meshes[i]);
        }
        //void SelectMesh(Mesh* mesh);
        //void DeselectMesh(Mesh* mesh);

        //void RegisterSkyboxToRemove(Skybox* skybox);
        inline bool DelayedDestroySkybox(){
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

        void RegisterTexture(Texture* texture);
        void FreeTexture(Texture* texture);
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
        void PoolEvents()               noexcept;
        bool DrawGeometry()             noexcept;
        bool DrawSkybox()               noexcept;
        void DrawGrid()                 noexcept;
        void DrawSingleColors()         noexcept;
        bool DrawTransparentGeometry()  noexcept;
    };
}

#endif //GAMEENGINE_RENDER_H
