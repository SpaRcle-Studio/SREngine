//
// Created by Monika on 30.07.2022.
//

#include <Utils/Types/RawMesh.h>
#include <Utils/Types/DataStorage.h>

#include <Graphics/UI/Sprite2D.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Environment/Environment.h>
#include <Graphics/Types/Uniforms.h>
#include <Graphics/Types/Shader.h>

namespace SR_GRAPH_NS::UI {
    Sprite2D::Sprite2D()
        : Super(Types::MeshType::Sprite2D)
    {
        /// override component
        Component::InitComponent<Sprite2D>();

        m_countIndices = SPRITE_INDICES.size();
        m_countVertices = SPRITE_VERTICES.size();

        SetId("Sprite2DFromMemory");
    }

    SR_UTILS_NS::IResource* Sprite2D::Copy(SR_UTILS_NS::IResource *destination) const {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        auto* sprite2D = dynamic_cast<Sprite2D *>(destination ? destination : new Sprite2D());
        sprite2D = dynamic_cast<Sprite2D *>(IndexedMesh::Copy(sprite2D));

        if (sprite2D->IsCalculated()) {
            auto &&manager = Memory::MeshManager::Instance();
            sprite2D->m_VBO = manager.CopyIfExists<Vertices::VertexType::UIVertex, Memory::MeshMemoryType::VBO>(GetResourceId());
        }

        return sprite2D;
    }

    SR_UTILS_NS::Component* Sprite2D::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        SR_MAYBE_UNUSED const auto &&type = static_cast<Types::MeshType>(marshal.Read<int32_t>());

        const auto &&material = marshal.Read<std::string>();

        auto&& pSprite = new Sprite2D();

        if (material != "None") {
            if (auto&& pMaterial = Types::Material::Load(material)) {
                pSprite->SetMaterial(pMaterial);
            }
            else
                SR_ERROR("Sprite2D::LoadComponent() : failed to load material! Name: " + material);
        }

        return pSprite;
    }

    bool Sprite2D::Calculate() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_isCalculated)
            return true;

        const bool iboOK = m_IBO != SR_ID_INVALID;
        if (m_VBO != SR_ID_INVALID && iboOK && !m_hasErrors) {
            m_isCalculated = true;
            return true;
        }

        if (!IsCanCalculate()) {
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("Sprite2D::Calculate() : calculating \"" + m_geometryName + "\"...");
        }

        if (!CalculateVBO<Vertices::VertexType::UIVertex>(SPRITE_VERTICES))
            return false;

        return IndexedMesh::Calculate();
    }

    void Sprite2D::FreeVideoMemory() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("Sprite2D::FreeVideoMemory() : free \"" + m_geometryName + "\" mesh video memory...");
        }

        if (!FreeVBO<Vertices::VertexType::UIVertex>()) {
            SR_ERROR("Sprite2D::FreeVideoMemory() : failed to free VBO!");
        }

        IndexedMesh::FreeVideoMemory();
    }

    void Sprite2D::Draw() {
        if (!IsActive() || IsDestroyed())
            return;

        if ((!m_isCalculated && !Calculate()) || m_hasErrors)
            return;

        auto&& shader = m_material->GetShader();
        auto&& uboManager = Memory::UBOManager::Instance();

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = uboManager.ReAllocateUBO(m_virtualUBO, shader->GetUBOBlockSize(), shader->GetSamplersCount());

            if (m_virtualUBO != SR_ID_INVALID) {
                uboManager.BindUBO(m_virtualUBO);
            }
            else {
                m_pipeline->ResetDescriptorSet();
                m_hasErrors = true;
                return;
            }

            shader->InitUBOBlock();
            shader->Flush();

            m_material->UseSamplers();
        }

        switch (uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                shader->InitUBOBlock();
                shader->Flush();
                m_material->UseSamplers();
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Success:
                m_pipeline->DrawIndices(m_countIndices);
                break;
            case Memory::UBOManager::BindResult::Failed:
            default:
                break;
        }
    }

    SR_HTYPES_NS::Marshal::Ptr Sprite2D::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Component::Save(pMarshal, flags);

        pMarshal->Write(static_cast<int32_t>(m_type));

        pMarshal->Write(m_material ? m_material->GetResourceId() : "None");

        return pMarshal;
    }

    SR_MATH_NS::FVector2 Sprite2D::GetSizes() const {
        return SR_MATH_NS::FVector2(2.f, 2.f);
    }

    std::vector<uint32_t> Sprite2D::GetIndices() const {
        return SPRITE_INDICES;
    }
}