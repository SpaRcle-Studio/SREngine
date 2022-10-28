//
// Created by Monika on 14.02.2022.
//

#ifndef SRENGINE_TEXT_H
#define SRENGINE_TEXT_H

#include <Graphics/Types/Mesh.h>
#include <Graphics/Types/Geometry/MeshComponent.h>
#include <Utils/Types/UnicodeString.h>

namespace SR_GTYPES_NS {
    class Text : public Mesh, public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1001);
        friend class Mesh;
        using Super = Mesh;
    public:
        typedef Vertices::SimpleVertex VertexType;

    public:
        Text();
        ~Text() override = default;

    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

        SR_UTILS_NS::IResource* Copy(SR_UTILS_NS::IResource* destination) const override;
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        void UseMaterial() override;
        void UseModelMatrix() override;

        void UseSamplers() override;

        void OnAttached() override;
        void OnDestroy() override;
        void OnMatrixDirty() override;
        void OnEnable() override;
        void OnDisable() override;

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }
        SR_NODISCARD SR_FORCE_INLINE bool IsCanUpdate() const noexcept override { return false; }

        SR_NODISCARD SR_FORCE_INLINE bool IsMeshActive() const noexcept override {
            return SR_UTILS_NS::Component::IsActive();
        }

        const SR_MATH_NS::Matrix4x4& GetModelMatrix() const override {
            return m_modelMatrix;
        }

        SR_NODISCARD SR_UTILS_NS::Path GetResourcePath() const override;

        void Draw() override;

        bool Calculate() override;
        void FreeVideoMemory() override;

    private:
        SR_NODISCARD RenderScenePtr GetRenderScene();
        SR_NODISCARD bool BuildAtlas();

    private:
        RenderScenePtr m_renderScene;

        SR_MATH_NS::Matrix4x4 m_modelMatrix = SR_MATH_NS::Matrix4x4::Identity();

        int32_t m_id = SR_ID_INVALID;
        uint32_t m_width = 0;
        uint32_t m_height = 0;

        SR_HTYPES_NS::UnicodeString m_text;

    };
}

#endif //SRENGINE_TEXT_H
