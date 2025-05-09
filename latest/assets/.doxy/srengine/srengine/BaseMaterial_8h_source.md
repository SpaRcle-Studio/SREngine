

# File BaseMaterial.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Material**](dir_2ed0f653e9a17ea2b9386330cebea31f.md) **>** [**BaseMaterial.h**](BaseMaterial_8h.md)

[Go to the documentation of this file](BaseMaterial_8h.md)


```C++
//
// Created by Monika on 19.05.2024.
//

#ifndef SR_ENGINE_GRAPHICS_BASE_MATERIAL_H
#define SR_ENGINE_GRAPHICS_BASE_MATERIAL_H

#include <Graphics/macros.h>

#include <Utils/Resources/IResource.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>
#include <Utils/Types/ObjectPool.h>
#include <Utils/Serialization/Serializable.h>

#include <Graphics/Loaders/ShaderProperties.h>
#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/Material/MaterialType.h>
#include <Graphics/Material/MaterialData.h>
#include <Graphics/Material/MaterialProperty.h>

namespace SR_GTYPES_NS {
    class Mesh;
    class Texture;
    class Shader;
}

namespace SR_GRAPH_NS {
    class RenderContext;

    class BaseMaterial : public SR_UTILS_NS::Serializable, public SR_UTILS_NS::NonCopyable, public SR_HTYPES_NS::SharedPtr<BaseMaterial> {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<BaseMaterial>;

    protected:
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using TexturePtr = SR_GTYPES_NS::Texture*;

    public:
        BaseMaterial();
        ~BaseMaterial() override;

    public:
        void SR_FASTCALL SetVec4(SR_UTILS_NS::StringAtom id, const SR_MATH_NS::FVector4& v) noexcept;
        void SR_FASTCALL SetColor(SR_UTILS_NS::StringAtom id, const SR_MATH_NS::FColor& v) noexcept;
        void SR_FASTCALL SetBool(SR_UTILS_NS::StringAtom id, bool v) noexcept;
        void SR_FASTCALL SetTexture(SR_UTILS_NS::StringAtom id, SR_GTYPES_NS::Texture* pTexture) noexcept;

        SR_NODISCARD SR_UTILS_NS::StringAtom GetRenderStageId() const noexcept;
        SR_NODISCARD bool IsTransparent() const;
        SR_NODISCARD ShaderPtr GetShader() const;
        SR_NODISCARD RenderContextPtr GetContext() const { return m_context; }
        SR_NODISCARD virtual const MaterialData::Ptr& GetMaterialData() const noexcept = 0;

        SR_NODISCARD virtual MaterialType GetMaterialType() const noexcept = 0;

        SR_NODISCARD virtual uint32_t RegisterMesh(MeshPtr pMesh);
        virtual void UnregisterMesh(uint32_t* pId);

        virtual void SetShader(ShaderPtr pShader, SR_UTILS_NS::StringAtom stage = SR_UTILS_NS::StringAtom());
        void SetShader(const SR_UTILS_NS::Path& path, SR_UTILS_NS::StringAtom stage = SR_UTILS_NS::StringAtom());

        void OnPropertyChanged(bool onlyUniforms) const;
        void OnShaderChanged() const;

        void Use();
        void UseSamplers();

    protected:
        virtual void InitContext() const;
        void InitMaterialDataSubscriptions() const;
        void DeInitMaterialDataSubscriptions() const;

    protected:
        mutable RenderContextPtr m_context;

        SR_HTYPES_NS::ObjectPool<MeshPtr, uint32_t> m_meshes;

        mutable SR_UTILS_NS::Subscription m_shaderChangedSubscription;
        mutable SR_UTILS_NS::Subscription m_propertyChangedSubscription;

    };
}

#endif //SR_ENGINE_GRAPHICS_BASE_MATERIAL_H
```


