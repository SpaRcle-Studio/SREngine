//
// Created by Nikita on 17.11.2020.
//

#ifndef SRENGINE_GRAPHICS_MESH_H
#define SRENGINE_GRAPHICS_MESH_H

#include <Utils/Math/Matrix4x4.h>
#include <Utils/Common/Enumerations.h>

#include <Graphics/Utils/MeshTypes.h>
#include <Graphics/Memory/IGraphicsResource.h>
#include <Graphics/Memory/UBOManager.h>

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
    class Material;

    class Mesh : public SR_UTILS_NS::NonCopyable, public Memory::IGraphicsResource {
        friend class Material;
    public:
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using ShaderPtr = Shader*;
        using MaterialPtr = Material*;
        using Ptr = Mesh*;

    public:
        ~Mesh() override;

    protected:
        explicit Mesh(MeshType type);

    public:
        static std::vector<Mesh::Ptr> Load(const SR_UTILS_NS::Path& path, MeshType type);
        static Mesh::Ptr TryLoad(const SR_UTILS_NS::Path& path, MeshType type, uint32_t id);
        static Mesh::Ptr Load(const SR_UTILS_NS::Path& path, MeshType type, uint32_t id);

    public:
        SR_NODISCARD virtual int32_t GetIBO() { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t GetVBO() { return SR_ID_INVALID; }

        SR_NODISCARD virtual int32_t GetIBO() const { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t GetVBO() const { return SR_ID_INVALID; }

        SR_NODISCARD virtual bool IsCanCalculate() const;
        SR_NODISCARD virtual bool IsUniqueMesh() const { return false; }
        SR_NODISCARD virtual bool IsMeshDestroyed() const { return m_isMeshDestroyed; }

        SR_NODISCARD virtual SR_FORCE_INLINE bool IsMeshActive() const noexcept { return true; }
        SR_NODISCARD virtual SR_FORCE_INLINE bool IsDebugMesh() const noexcept { return false; }
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetTranslation() const { return SR_MATH_NS::FVector3::Zero(); }
        SR_NODISCARD virtual const SR_MATH_NS::Matrix4x4& GetModelMatrix() const;
        SR_NODISCARD virtual std::vector<uint32_t> GetIndices() const { return { }; }
        SR_NODISCARD virtual std::string GetGeometryName() const { return std::string(); }
        SR_NODISCARD virtual std::string GetMeshIdentifier() const;

        SR_NODISCARD ShaderPtr GetShader() const;
        SR_NODISCARD MaterialPtr GetMaterial() const { return m_material; }
        SR_NODISCARD int32_t GetVirtualUBO() const { return m_virtualUBO; }
        SR_NODISCARD MeshType GetMeshType() const noexcept { return m_meshType; }

        virtual void SetGeometryName(const std::string& name) { }
        virtual void BindMesh() const;

        virtual void Draw() = 0;

        virtual void UseMaterial();
        virtual void UseModelMatrix() { }
        virtual void UseSamplers();

        void FreeVideoMemory() override;

        /// Если меш был зарегистрирован, то помечает его на уничтожение
        /// Если меш не зарегистрировали, удаляет экземпляр
        void MarkMeshDestroyed();

        void SetMaterial(Material* material);
        void SetMaterial(const SR_UTILS_NS::Path& path);

    protected:
        virtual bool Calculate();

    protected:
        Memory::UBOManager& m_uboManager;

        const MeshType m_meshType = MeshType::Unknown;

        MaterialPtr m_material = nullptr;

        std::atomic<bool> m_hasErrors = false;
        std::atomic<bool> m_dirtyMaterial = false;
        std::atomic<bool> m_isMeshDestroyed = false;

        int32_t m_virtualUBO = SR_ID_INVALID;

    };
}

#endif //SRENGINE_GRAPHICS_MESH_H
