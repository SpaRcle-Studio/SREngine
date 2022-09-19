//
// Created by Monika on 31.10.2021.
//

#include <Render/MeshCluster.h>
#include <Types/Geometry/IndexedMesh.h>

namespace SR_GRAPH_NS {
    MeshCluster::MeshCluster() {
        m_subClusters.max_load_factor(0.9f);
        m_subClusters.reserve(25);
    }

   bool ShadedMeshSubCluster::Remove(Types::Mesh *mesh) noexcept {
       auto* indexed = dynamic_cast<Types::IndexedMesh *>(mesh);

       const int32_t groupID = indexed ? indexed->GetVBO<false>() : SR_ID_INVALID;
       if (groupID == SR_ID_INVALID) {
           SR_ERROR("ShadedMeshSubCluster::Remove() : failed get mesh group id to remove mesh!");
           return false;
       }

       if (auto&& groupIt = m_groups.find(groupID); groupIt != m_groups.end()) {
           MeshGroup& group = groupIt->second;

           if (auto pIt = group.find(indexed); pIt != group.end()) {
               group.erase(pIt);

               /// После вызова меш может быть уже не валиден
               mesh->RemoveUsePoint();

               if (group.empty()) {
                   m_groups.erase(groupIt);
               }

               return true;
           }
       }
       else {
           SR_ERROR("ShadedMeshSubCluster::Remove() : mesh group to remove mesh not found!");
           return false;
       }

       SR_ERROR("ShadedMeshSubCluster::Remove() : mesh not found!");

       return false;
   }

    bool ShadedMeshSubCluster::Add(Types::Mesh *mesh) noexcept {
        auto* indexed = dynamic_cast<Types::IndexedMesh *>(mesh);

        const int32_t groupID = indexed ? indexed->GetVBO<false>() : SR_ID_INVALID;
        if (groupID == SR_ID_INVALID) {
            return false;
        }

        if (auto&& pIt = m_groups.find(groupID); pIt == m_groups.end()) {
            m_groups[groupID] = { indexed };
        }
        else if (!pIt->second.insert(indexed).second) {
            SRHalt("ShadedMeshSubCluster::Add() : failed to add mesh to cluster!");
            return false;
        }

        mesh->AddUsePoint();

        return true;
    }

    bool ShadedMeshSubCluster::Empty() const noexcept {
        return m_groups.empty();
    }

    bool MeshCluster::Add(Types::Mesh* pMesh) noexcept {
        const auto&& pShader = pMesh->GetShader();

        SRAssert(pShader);

        if (auto&& subClusterIt = m_subClusters.find(pShader); subClusterIt == m_subClusters.end()) {
            auto&& [subCluster, _] = m_subClusters.insert(std::make_pair(
                    pShader,
                    std::move(ShadedMeshSubCluster())
            ));

            if (!subCluster->second.Add(pMesh)) {
                pMesh->AddUsePoint();
                SRVerifyFalse(!m_invalid.insert(pMesh).second);
            }

            return true;
        }
        else {
            if (!subClusterIt->second.Add(pMesh)) {
                pMesh->AddUsePoint();
                SRVerifyFalse(!m_invalid.insert(pMesh).second);
            }

            return true;
        }
    }

    bool MeshCluster::Remove(Types::Mesh *mesh) noexcept {
        if (auto&& pInvalidIt = m_invalid.find(mesh); pInvalidIt != m_invalid.end()) {
            mesh->RemoveUsePoint();
            m_invalid.erase(pInvalidIt);
            return true;
        }

        const auto&& pShader = mesh->GetShader();

        SRAssert(pShader);

        if (auto&& subCluster = m_subClusters.find(pShader); subCluster == m_subClusters.end()) {
            return false;
        }
        else {
            auto const result = subCluster->second.Remove(mesh);

            if (subCluster->second.Empty()) {
                m_subClusters.erase(subCluster);
            }

            return result;
        }
    }

    bool MeshCluster::Empty() const noexcept {
        return m_subClusters.empty();
    }

    bool MeshCluster::Update() {
        bool dirty = false;

        for (auto pInvalidIt = m_invalid.begin(); pInvalidIt != m_invalid.end(); ) {
            auto&& pMesh = dynamic_cast<SR_GTYPES_NS::IndexedMesh*>(*pInvalidIt);

            if (pMesh->GetCountUses() == 1) {
                if (pMesh->IsCalculated()) {
                    pMesh->FreeVideoMemory();
                }

                pMesh->RemoveUsePoint();
                pInvalidIt = m_invalid.erase(pInvalidIt);

                dirty = true;
            }
            else if (pMesh->GetVBO<false>() != SR_ID_INVALID) {
                Add(pMesh);
                pMesh->RemoveUsePoint();
                pInvalidIt = m_invalid.erase(pInvalidIt);

                dirty = true;
            }
            else {
                ++pInvalidIt;
            }
        }

    repeat:
        for (auto pSubClusterIt = m_subClusters.begin(); pSubClusterIt != m_subClusters.end(); ) {
            auto&& [pShader, subCluster] = *pSubClusterIt;

            for (auto pGroupsIt = subCluster.begin(); pGroupsIt != subCluster.end(); ) {
                auto&& [vbo, group] = *pGroupsIt;

                for (auto pMeshIt = group.begin(); pMeshIt != group.end(); ) {
                    SR_GTYPES_NS::IndexedMesh* pMesh = dynamic_cast<SR_GTYPES_NS::IndexedMesh*>(*pMeshIt); /** copy */
                    auto&& pMaterial = pMesh->GetMaterial();

                    SRAssert2(pMaterial, "Mesh have not material!");

                    if (pMesh->GetCountUses() == 1) {
                        pMesh->RemoveUsePoint();

                        if (pMesh->IsCalculated()) {
                            pMesh->FreeVideoMemory();
                        }

                        pMeshIt = group.erase(pMeshIt);

                        dirty = true;
                        continue;
                    }

                    if (!pMaterial) {
                        ++pMeshIt;
                        continue;
                    }

                    /// Если изменил свой кластер (прозрачность), то убираем его из текущего
                    if (ChangeCluster(pMesh)) {
                        /// use-point от старого саб кластера
                        pMesh->RemoveUsePoint();
                        pMeshIt = group.erase(pMeshIt);
                        dirty = true;
                    }
                    /// Мигрируем меш в другой саб кластер
                    else if (pMesh->GetVBO<false>() != vbo || pMaterial->GetShader() != pShader) {
                        pMeshIt = group.erase(pMeshIt);
                        Add(pMesh);
                        /// use-point от старого саб кластера
                        pMesh->RemoveUsePoint();
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

    bool OpaqueMeshCluster::ChangeCluster(MeshCluster::MeshPtr pMesh) {
        if (pMesh->GetMaterial()->IsTransparent()) {
            SR_LOG("OpaqueMeshCluster::ChangeCluster() : change the cluster \"opaque -> transparent\"");
            m_transparent->Add(pMesh);
            return true;
        }

        return false;
    }

    bool TransparentMeshCluster::ChangeCluster(MeshCluster::MeshPtr pMesh) {
        if (!pMesh->GetMaterial()->IsTransparent()) {
            SR_LOG("TransparentMeshCluster::ChangeCluster() : change the cluster \"transparent -> opaque\"");
            m_opaque->Add(pMesh);
            return true;
        }

        return false;
    }
}

