//
// Created by Monika on 31.10.2021.
//

#include <Graphics/Render/MeshCluster.h>
#include <Graphics/Types/Geometry/IndexedMesh.h>

namespace SR_GRAPH_NS {
    MeshCluster::MeshCluster() {
        m_subClusters.max_load_factor(0.9f);
        m_subClusters.reserve(25);
    }

    ShadedMeshSubCluster::ShadedMeshSubCluster(SR_GTYPES_NS::Shader *pShader)
        : Super()
        , m_shader(pShader)
    { }

    bool ShadedMeshSubCluster::Add(SR_GTYPES_NS::Mesh::Ptr pMesh) noexcept {
        SR_TRACY_ZONE;

        const int32_t groupID = pMesh->GetVBO();

        if (auto&& pIt = m_groups.find(groupID); pIt == m_groups.end()) {
            m_groups[groupID] = { pMesh };
        }
        else if (!pIt->second.insert(pMesh).second) {
            SRHalt("ShadedMeshSubCluster::Add() : failed to add mesh to cluster!");
            return false;
        }

        return true;
    }

    bool ShadedMeshSubCluster::Empty() const noexcept {
        return m_groups.empty();
    }

    SR_SRSL_NS::ShaderType ShadedMeshSubCluster::GetShaderType() const noexcept {
        return m_shader ? m_shader->GetType() : SR_SRSL_NS::ShaderType::Unknown;
    }

    void ShadedMeshSubCluster::OnResourceReloaded(SR_UTILS_NS::IResource* pResource) {
        for (auto&& [VBO, meshes] : m_groups) {
            for (auto&& pMesh : meshes) {
                pMesh->OnResourceReloaded(pResource);
            }
        }
    }

    bool MeshCluster::Add(Types::Mesh* pMesh) noexcept {
        SR_TRACY_ZONE;

        const auto&& pShader = pMesh->GetShader();

        SRAssert(pMesh->GetPipeline());
        SRAssert(pShader);

        if (auto&& subClusterIt = m_subClusters.find(pShader); subClusterIt == m_subClusters.end()) {
            auto&& [subCluster, _] = m_subClusters.insert(std::make_pair(
                    pShader,
                    ShadedMeshSubCluster(pShader)
            ));

            if (!subCluster->second.Add(pMesh)) {
                SRHalt0();
            }

            return true;
        }
        else {
            if (!subClusterIt->second.Add(pMesh)) {
                SRHalt0();
            }

            return true;
        }
    }

    bool MeshCluster::Empty() const noexcept {
        return m_subClusters.empty();
    }

    bool MeshCluster::Update() {
        SR_TRACY_ZONE;

        bool dirty = false;

    repeat:
        for (auto pSubClusterIt = m_subClusters.begin(); pSubClusterIt != m_subClusters.end(); ) {
            auto&& [pShader, subCluster] = *pSubClusterIt;

            for (auto pGroupsIt = subCluster.begin(); pGroupsIt != subCluster.end(); ) {
                auto&& [vbo, group] = *pGroupsIt;

                for (auto pMeshIt = group.begin(); pMeshIt != group.end(); ) {
                    SR_GTYPES_NS::Mesh* pMesh = *pMeshIt; /** copy */
                    auto&& pMaterial = pMesh->GetMaterial();

                    SRAssert2(pMaterial, "Mesh have not material!");

                    /*if (pMesh->IsMeshDestroyed()) {
                        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();
                        SR_MAYBE_UNUSED SR_HTYPES_NS::SingletonRecursiveLockGuard lock(&resourceManager);

                        if (pMesh->IsCalculated()) {
                            pMesh->FreeVideoMemory();
                            pMesh->DeInitGraphicsResource();
                        }

                        pMesh->FreeMesh();

                        pMeshIt = group.erase(pMeshIt);

                        dirty = true;
                        continue;
                    }*/

                    if (!pMaterial) {
                        ++pMeshIt;
                        continue;
                    }

                    /// Если изменил свой кластер (прозрачность), то убираем его из текущего
                    if (ChangeCluster(pMesh)) {
                        pMeshIt = group.erase(pMeshIt);
                        dirty = true;
                    }
                    /// Мигрируем меш в другой саб кластер
                    else if (pMesh->GetVBO() != vbo || pMaterial->GetShader() != pShader) {
                        pMeshIt = group.erase(pMeshIt);
                        Add(pMesh);
                        dirty = true;
                        goto repeat;
                    }
                    else {
                        ++pMeshIt;
                    }
                }

                if (group.empty()) {
                    pGroupsIt = subCluster.erase(pGroupsIt);
                }
                else {
                    ++pGroupsIt;
                }
            }

            if (subCluster.Empty()) {
                pSubClusterIt = m_subClusters.erase(pSubClusterIt);
            }
            else {
                ++pSubClusterIt;
            }
        }

        return dirty;
    }

    void MeshCluster::OnResourceReloaded(SR_UTILS_NS::IResource* pResource) {
        for (auto&& [pShader, subCluster] : m_subClusters) {
            subCluster.OnResourceReloaded(pResource);
        }
    }

    bool OpaqueMeshCluster::ChangeCluster(MeshCluster::MeshPtr pMesh) {
        SR_TRACY_ZONE;

        if (pMesh->GetMaterial()->IsTransparent()) {
            SR_LOG("OpaqueMeshCluster::ChangeCluster() : change the cluster \"opaque -> transparent\"");
            m_transparent->Add(pMesh);
            return true;
        }

        return false;
    }

    bool TransparentMeshCluster::ChangeCluster(MeshCluster::MeshPtr pMesh) {
        SR_TRACY_ZONE;

        if (!pMesh->GetMaterial()->IsTransparent()) {
            SR_LOG("TransparentMeshCluster::ChangeCluster() : change the cluster \"transparent -> opaque\"");
            m_opaque->Add(pMesh);
            return true;
        }

        return false;
    }
}

