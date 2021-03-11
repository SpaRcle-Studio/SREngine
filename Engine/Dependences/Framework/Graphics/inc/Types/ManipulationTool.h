//
// Created by Nikita on 05.03.2021.
//

#ifndef GAMEENGINE_MANIPULATIONTOOL_H
#define GAMEENGINE_MANIPULATIONTOOL_H

#include <Math/Vector3.h>
#include <Math/Matrix4x4.h>

#include <Types/Mesh.h>

#include <Types/List.h>

namespace Framework::Graphics {
    class Shader;
    class Render;
    class Camera;
}

struct ImGuiWindow;

#include <Environment/Environment.h>

namespace Framework::Graphics::Types {
    enum class Operation {
        Translate, Rotate, Scale
    };

    //! use only from window thread
    class ManipulationTool {
    private:
        ManipulationTool(Render* render);
    private:
        Environment* m_env                  = nullptr;
        Render* m_render                    = nullptr;

        Camera* m_targetCamera              = nullptr;
        ImGuiWindow* m_targetWindow         = nullptr;

        Operation m_operation               = Operation::Translate;

        Math::Axis m_activeAxis             = Math::Axis::NONE;

        bool m_required                     = false;
        bool m_isDraw                       = false;
        bool m_isDestroy                    = false;

        Mesh* m_ringX                       = nullptr;
        Mesh* m_ringY                       = nullptr;
        Mesh* m_ringZ                       = nullptr;

        Mesh* m_arrowX                      = nullptr;
        Mesh* m_arrowY                      = nullptr;
        Mesh* m_arrowZ                      = nullptr;

        Math::Vector3 m_posDrag             = Math::Vector3();
        Math::Vector3 m_rotDrag             = Math::Vector3();
        Math::Vector3 m_sclDrag             = Math::Vector3();

        Math::Vector3 m_position            = Math::Vector3();
        Math::Vector3 m_rotation            = Math::Vector3();
        float m_distance                    = 0.f;

        size_t m_countTargetMeshes          = 0;
        std::vector<Mesh*> m_targetMeshes   = std::vector<Mesh*>();
        std::mutex m_meshesMutex            = std::mutex();

        //double m_dists[2] = { 0.0, 0.0 };
        bool m_mouseNeedReCalc = true;
        double m_oldMouseDist = 0.0;
        Math::Vector2 m_Dirs[2] = {
                Math::Vector2(), // +
                Math::Vector2(), // -
        };

        Mesh
            *x = nullptr,
            *y = nullptr,
            *z = nullptr;
    private:
        bool SelectMeshes();
        void CalculateCenter();
    public:
        [[nodiscard]] inline unsigned int GetOperationInt() const noexcept { return (unsigned int)m_operation; }
        inline void SetOperationInt(unsigned int value) noexcept { this->m_operation = (Operation)value; }
        double GetDrag();
        inline void SetActiveAxis(const Math::Axis& axis) noexcept {this->m_activeAxis = axis; }
        void DisableAxis() noexcept;
        bool Clear();
        bool AddMesh(Mesh* mesh);
        bool RemoveMesh(Mesh* mesh);
    public:
        static ManipulationTool* Create(Render*render);

        Camera* GetTargetCamera() { return m_targetCamera; }

        //\Call only from window context
        bool Destroy();
        void Free();
    public:
        //bool SetRings(Mesh* _ringX, Mesh* _ringY, Mesh* _ringZ);
        bool SetArrows(Helper::Types::List<Mesh*> meshes);
        bool SetRings(Helper::Types::List<Mesh*> meshes);
        void Require(Camera* camera, ImGuiWindow* win);
        void SetOperation(Operation op){
            this->m_operation = op;
        }
    public:
        [[nodiscard]] Math::Axis GetActiveAxis() const noexcept {
            return m_activeAxis;
        }
    public:
        void Draw();
        void SimpleDraw(Shader* shader);
        void Process();
    };
}

#endif //GAMEENGINE_MANIPULATIONTOOL_H

