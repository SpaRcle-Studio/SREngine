//
// Created by Monika on 20.03.2023.
//

#include <Utils/Types/IRawMeshHolder.h>

namespace SR_HTYPES_NS {
    IRawMeshHolder::~IRawMeshHolder() {
        SetRawMesh(nullptr);
    }

    void IRawMeshHolder::SetRawMesh(IRawMeshHolder::RawMeshPtr pRawMesh) {
        if (m_rawMesh == pRawMesh) {
            return;
        }

        if (m_rawMesh) {
            m_rawMesh->RemoveUsePoint();
        }

        if ((m_rawMesh = pRawMesh)) {
            m_rawMesh->AddUsePoint();
        }

        if (IsValidMeshId()) {
            OnRawMeshChanged();
        }
        else {
            SetMeshId(GetMeshId());
        }
    }

    void IRawMeshHolder::SetMeshId(IRawMeshHolder::MeshIndex meshIndex) {
        if (!m_rawMesh) {
            if (m_meshId != SR_ID_INVALID) {
                m_meshId = SR_ID_INVALID;
                OnRawMeshChanged();
            }
            return;
        }

        auto&& count = static_cast<int32_t>(m_rawMesh->GetMeshesCount());

        IRawMeshHolder::MeshIndex newIndex = SR_CLAMP(meshIndex, SR_MAX(count - 1, 0), 0);

        if (m_meshId != newIndex) {
            m_meshId = newIndex;
            OnRawMeshChanged();
        }
    }

    std::string IRawMeshHolder::GetMeshStringPath() const noexcept {
        if (m_rawMesh) {
            return m_rawMesh->GetResourcePath().ToStringRef();
        }

        static const std::string empty;
        return empty;
    }

    bool IRawMeshHolder::IsValidMeshId() const noexcept {
        if (m_meshId < 0 || !m_rawMesh) {
            return false;
        }

        return m_meshId < m_rawMesh->GetMeshesCount();
    }

    std::vector<SR_UTILS_NS::Vertex> IRawMeshHolder::GetVertices() const noexcept {
        static std::vector<SR_UTILS_NS::Vertex> defaultVertices;

        if (!IsValidMeshId()) {
            return defaultVertices;
        }

        if (auto&& pRawMesh = GetRawMesh()) {
            return pRawMesh->GetVertices(GetMeshId());
        }

        return defaultVertices;
    }

    void IRawMeshHolder::SetRawMesh(const SR_UTILS_NS::Path& path) {
        SR_UTILS_NS::ResourceManager::Instance().Execute([&]() {
            SetRawMesh(SR_HTYPES_NS::RawMesh::Load(path));
        });
    }
}