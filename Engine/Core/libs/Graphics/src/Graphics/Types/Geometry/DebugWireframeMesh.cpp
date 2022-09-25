//
// Created by Monika on 29.10.2021.
//

#include <Utils/Types/RawMesh.h>
#include <Graphics/Types/Geometry/DebugWireframeMesh.h>

namespace SR_GTYPES_NS {
    DebugWireframeMesh::DebugWireframeMesh()
        : Super(MeshType::Wireframe)
    { }

    DebugWireframeMesh::~DebugWireframeMesh() {
        SetRawMesh(nullptr);
    }

    SR_UTILS_NS::IResource* DebugWireframeMesh::Copy(IResource* destination) const {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        auto* wireFramed = dynamic_cast<DebugWireframeMesh *>(destination ? destination : new DebugWireframeMesh());
        wireFramed = dynamic_cast<DebugWireframeMesh *>(Framework::Graphics::Types::IndexedMesh::Copy(wireFramed));

        wireFramed->SetRawMesh(m_rawMesh);
        wireFramed->m_meshId = m_meshId;

        if (wireFramed->IsCalculated()) {
            auto &&manager = Memory::MeshManager::Instance();
            wireFramed->m_VBO = manager.CopyIfExists<Vertices::VertexType::SimpleVertex, Memory::MeshMemoryType::VBO>(GetResourceId());
        }

        return wireFramed;
    }

    void DebugWireframeMesh::Draw() {
        if (IsDestroyed()) {
            return;
        }

        if ((!m_isCalculated && !Calculate()) || m_hasErrors)
            return;

        auto &&shader = m_material->GetShader();

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = m_uboManager.ReAllocateUBO(m_virtualUBO, shader->GetUBOBlockSize(), shader->GetSamplersCount());

            if (m_virtualUBO != SR_ID_INVALID) {
                m_uboManager.BindUBO(m_virtualUBO);
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

        switch (m_uboManager.BindUBO(m_virtualUBO)) {
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

    bool DebugWireframeMesh::Calculate() {
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
            SR_LOG("DebugWireframeMesh::Calculate() : calculating \"" + GetGeometryName() + "\"...");
        }

        auto vertices = Vertices::CastVertices<Vertices::SimpleVertex>(m_rawMesh->GetVertices(m_meshId));

        if (!CalculateVBO<Vertices::VertexType::SimpleVertex>(vertices))
            return false;

        return IndexedMesh::Calculate();
    }

    bool DebugWireframeMesh::Unload() {
        SetRawMesh(nullptr);
        return Mesh::Unload();
    }

    void DebugWireframeMesh::SetRawMesh(SR_HTYPES_NS::RawMesh *pRaw) {
        if (m_rawMesh) {
            RemoveDependency(m_rawMesh);
        }

        if (pRaw) {
            AddDependency(pRaw);
        }

        m_rawMesh = pRaw;
    }

    bool DebugWireframeMesh::Load() {
        if (auto&& pRawMesh = SR_HTYPES_NS::RawMesh::Load(GetResourcePath())) {
            if (m_meshId >= pRawMesh->GetMeshesCount()) {
                if (pRawMesh->GetCountUses() == 0) {
                    SRHalt("DebugWireframeMesh::Load() : count uses is zero! Unresolved situation...");
                    pRawMesh->Destroy();
                }
                return false;
            }

            m_countIndices = pRawMesh->GetIndicesCount(m_meshId);
            m_countVertices = pRawMesh->GetVerticesCount(m_meshId);

            SRAssert2(m_countVertices != 0 && m_countIndices != 0, "Invalid mesh!");

            SetGeometryName(pRawMesh->GetGeometryName(m_meshId));
            SetRawMesh(pRawMesh);

            return true;
        }

        return false;
    }

    void DebugWireframeMesh::FreeVideoMemory() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("DebugWireframeMesh::FreeVideoMemory() : free \"" + GetGeometryName() + "\" mesh video memory...");
        }

        if (!FreeVBO<Vertices::VertexType::SimpleVertex>()) {
            SR_ERROR("DebugWireframeMesh::FreeVideoMemory() : failed to free VBO!");
        }

        IndexedMesh::FreeVideoMemory();
    }

    std::vector<uint32_t> DebugWireframeMesh::GetIndices() const {
        return m_rawMesh->GetIndices(m_meshId);
    }

    bool DebugWireframeMesh::Reload() {
        SR_LOG("DebugWireframeMesh::Reload() : reloading \"" + std::string(GetResourceId()) + "\" mesh...");

        m_loadState = LoadState::Reloading;

        Unload();

        if (!Load()) {
            return false;
        }

        m_loadState = LoadState::Loaded;

        UpdateResources();

        return true;
    }

    void DebugWireframeMesh::SetMatrix(const SR_MATH_NS::Matrix4x4& matrix4X4) {
        m_modelMatrix = matrix4X4;
    }

    void DebugWireframeMesh::UseMaterial() {
        Mesh::UseMaterial();
        GetShader()->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
        GetShader()->SetVec4(SR_COMPILE_TIME_CRC32_STR("color"), m_color.Cast<float_t>().ToGLM());
    }

    const SR_MATH_NS::Matrix4x4 &DebugWireframeMesh::GetModelMatrix() const {
        return m_modelMatrix;
    }

    SR_UTILS_NS::Path DebugWireframeMesh::GetResourcePath() const {
        if (m_resourcePath.empty()) {
            m_resourcePath = SR_UTILS_NS::Path(
                    std::move(SR_UTILS_NS::StringUtils::SubstringView(GetResourceId(), '|', 1)),
                    true /** fast */
            );
        }

        return m_resourcePath;
    }

    void DebugWireframeMesh::SetColor(const SR_MATH_NS::FVector4& color) {
        m_color = color;
    }
}