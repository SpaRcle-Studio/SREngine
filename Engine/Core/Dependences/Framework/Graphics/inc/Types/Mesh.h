//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MESH_H
#define GAMEENGINE_MESH_H

#include <Environment/PipeLine.h>

#include <Utils/Common/Enumerations.h>
#include <Utils/ResourceManager/IResource.h>
#include <Utils/ECS/Component.h>
#include <Memory/IGraphicsResource.h>

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_GRAPH_NS {
    class Environment;
    class RenderScene;
    class RenderContext;
}

namespace SR_GTYPES_NS {
    class Shader;
}

namespace SR_GTYPES_NS {
    class Material;

    SR_ENUM_CLASS(MeshType,
        Unknown = 0,
        Static = 1,
        Wireframe = 2,
        Skinned = 3,
        Sprite2D = 4,
    )

    class Mesh : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource, public SR_UTILS_NS::Component {
        friend class Material;
        using PipelinePtr = Environment*;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
    protected:
        explicit Mesh(MeshType type);
        ~Mesh() override;

    public:
        static std::vector<Mesh*> Load(const SR_UTILS_NS::Path& path, MeshType type);
        static Mesh* TryLoad(const SR_UTILS_NS::Path& path, MeshType type, uint32_t id);
        static Mesh* Load(const SR_UTILS_NS::Path& path, MeshType type, uint32_t id);

    public:
        bool Destroy() override;

    protected:
        virtual void ReCalcModel();
        virtual bool Calculate();
        virtual void SetRawMesh(SR_HTYPES_NS::RawMesh* raw);

    public:
        IResource* Copy(IResource* destination) const override;

        virtual void Draw() = 0;

        void FreeVideoMemory() override;

    public:
        SR_MATH_NS::FVector3 GetBarycenter() const override;

        void OnMove(const SR_MATH_NS::FVector3& newValue) override;
        void OnRotate(const SR_MATH_NS::FVector3& newValue) override;
        void OnScaled(const SR_MATH_NS::FVector3& newValue) override;
        void OnSkewed(const SR_MATH_NS::FVector3& newValue) override;

        void OnAttached() override;
        void OnDestroy() override;

    public:
        bool IsCanCalculate() const;

        SR_NODISCARD Shader* GetShader() const;
        SR_NODISCARD std::string GetGeometryName() const { return m_geometryName; }
        SR_NODISCARD Material* GetMaterial() const { return m_material; }
        SR_NODISCARD bool IsCalculated() const { return m_isCalculated; }
        SR_NODISCARD bool IsInverse() const { return m_inverse; }
        SR_NODISCARD const glm::mat4& GetModelMatrixRef() const { return m_modelMat; }
        SR_NODISCARD glm::mat4 GetModelMatrix() const { return m_modelMat; }
        SR_NODISCARD uint32_t GetMeshId() const { return m_meshId; }
        SR_NODISCARD int32_t GetVirtualUBO() const { return m_virtualUBO; }
        SR_NODISCARD SR_UTILS_NS::Path GetResourcePath() const override;

        void SetInverse(bool value);
        void SetGeometryName(const std::string& name) { m_geometryName = name; }
        void SetMaterial(Material* material);
        void SetContext(const RenderContextPtr& context);
        SR_NODISCARD RenderScenePtr GetRenderScene();

    protected:
        SR_NODISCARD uint64_t GetFileHash() const override { return 0; }
        void OnResourceUpdated(IResource* pResource, int32_t depth) override;
        void OnEnabled() override;
        void OnDisabled() override;

    protected:
        SR_MATH_NS::FVector3         m_barycenter        = SR_MATH_NS::FVector3(SR_MATH_NS::UnitMAX);
        SR_MATH_NS::FVector3         m_position          = SR_MATH_NS::FVector3();
        SR_MATH_NS::FVector3         m_rotation          = SR_MATH_NS::FVector3();
        SR_MATH_NS::FVector3         m_skew              = SR_MATH_NS::FVector3(1);
        SR_MATH_NS::FVector3         m_scale             = SR_MATH_NS::FVector3(1);
        glm::mat4                    m_modelMat          = glm::mat4(0);

        bool                         m_inverse           = false;

        RenderScenePtr               m_renderScene       = { };
        /// Контекст будет задан только после регистрации в RenderScene
        RenderContextPtr             m_context           = { };
        PipelinePtr                  m_pipeline          = nullptr;
        const MeshType               m_type              = MeshType::Unknown;

        std::string                  m_geometryName      = "Unnamed";
        Material*                    m_material          = nullptr;
        SR_HTYPES_NS::RawMesh*       m_rawMesh           = nullptr;

        std::atomic<bool>            m_hasErrors         = false;
        std::atomic<bool>            m_isCalculated      = false;
        std::atomic<bool>            m_dirtyMaterial     = false;

        /// определяет порядок меша в файле, если их там несколько
        int32_t                      m_meshId            = SR_UINT32_MAX;
        int32_t                      m_virtualUBO        = SR_ID_INVALID;

    };
}

#endif //GAMEENGINE_MESH_H
