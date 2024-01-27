//
// Created by Nikita on 17.11.2020.
//

#ifndef SR_ENGINE_GRAPHICS_MESH_H
#define SR_ENGINE_GRAPHICS_MESH_H

#include <Utils/Math/Matrix4x4.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/Function.h>

#include <Graphics/Utils/MeshUtils.h>
#include <Graphics/Memory/IGraphicsResource.h>
#include <Graphics/Memory/UBOManager.h>
#include <Graphics/Loaders/ShaderProperties.h>

namespace SR_UTILS_NS {
    class IResource;
}

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
        static Mesh::Ptr TryLoad(SR_HTYPES_NS::RawMesh* pRawMesh, MeshType type, uint32_t id);
        static Mesh::Ptr TryLoad(const SR_UTILS_NS::Path& path, MeshType type, uint32_t id);
        static Mesh::Ptr Load(const SR_UTILS_NS::Path& path, MeshType type, uint32_t id);
        static Mesh::Ptr Load(const SR_UTILS_NS::Path& path, MeshType type, SR_UTILS_NS::StringAtom name);

    public:
        SR_NODISCARD virtual int32_t GetIBO() { return SR_ID_INVALID; }
        SR_NODISCARD virtual int32_t GetVBO() { return SR_ID_INVALID; }

        SR_NODISCARD virtual bool IsCalculatable() const;
        SR_NODISCARD virtual bool IsUniqueMesh() const { return false; }

        SR_NODISCARD virtual SR_FORCE_INLINE bool IsMeshActive() const noexcept { return !m_hasErrors; }
        SR_NODISCARD virtual SR_FORCE_INLINE bool IsFlatMesh() const noexcept { return false; }
        SR_NODISCARD virtual SR_MATH_NS::FVector3 GetTranslation() const { return SR_MATH_NS::FVector3::Zero(); }
        SR_NODISCARD virtual const SR_MATH_NS::Matrix4x4& GetModelMatrix() const;
        SR_NODISCARD virtual std::vector<uint32_t> GetIndices() const { return { }; }
        SR_NODISCARD virtual std::string GetGeometryName() const { return std::string(); }
        SR_NODISCARD virtual std::string GetMeshIdentifier() const;
        SR_NODISCARD virtual int64_t GetSortingPriority() const { return 0; }
        SR_NODISCARD virtual bool HasSortingPriority() const { return false; }
        SR_NODISCARD virtual SR_UTILS_NS::StringAtom GetMeshLayer() const { return SR_UTILS_NS::StringAtom(); }

        SR_NODISCARD std::vector<MaterialProperty>& GetOverrideUniforms() noexcept { return m_overrideUniforms; }
        SR_NODISCARD ShaderPtr GetShader() const;
        SR_NODISCARD MaterialPtr GetMaterial() const { return m_material; }
        SR_NODISCARD int32_t GetVirtualUBO() const { return m_virtualUBO; }
        SR_NODISCARD MeshType GetMeshType() const noexcept { return m_meshType; }
        SR_NODISCARD bool IsMeshRegistered() const noexcept { return m_registrationInfo.has_value(); }
        SR_NODISCARD const MeshRegistrationInfo& GetMeshRegistrationInfo() const noexcept { return m_registrationInfo.value(); }

        MaterialProperty& OverrideUniform(SR_UTILS_NS::StringAtom name);
        void RemoveUniformOverride(SR_UTILS_NS::StringAtom name);

        void SetMeshRegistrationInfo(const std::optional<MeshRegistrationInfo>& info) { m_registrationInfo = info; }

        virtual bool OnResourceReloaded(SR_UTILS_NS::IResource* pResource);
        virtual void SetGeometryName(const std::string& name) { }
        virtual bool BindMesh();

        virtual void Draw() = 0;

        virtual void UseMaterial();
        virtual void UseModelMatrix() { }
        virtual void UseSamplers();

        bool UnRegisterMesh();
        void ReRegisterMesh();

        void MarkMaterialDirty();

        void SetMaterial(Material* material);
        void SetMaterial(const SR_UTILS_NS::Path& path);

    protected:
        void FreeVideoMemory() override;

        virtual bool Calculate();

    protected:
        Memory::UBOManager& m_uboManager;

        MeshType m_meshType = MeshType::Unknown;

        MaterialPtr m_material = nullptr;

        std::atomic<bool> m_hasErrors = false;
        std::atomic<bool> m_dirtyMaterial = false;

        int32_t m_virtualUBO = SR_ID_INVALID;

        std::vector<MaterialProperty> m_overrideUniforms;
        std::vector<MaterialProperty> m_overrideConstant;

    private:
        std::optional<MeshRegistrationInfo> m_registrationInfo;

    };
}

#endif //SR_ENGINE_GRAPHICS_MESH_H
