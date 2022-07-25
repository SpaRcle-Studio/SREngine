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

   //bool ShadedMeshSubCluster::Remove(Types::Mesh *mesh) noexcept {
   //    auto* indexed = dynamic_cast<Types::IndexedMesh *>(mesh);

   //    const int32_t groupID = indexed ? indexed->GetVBO<false>() : SR_ID_INVALID;
   //    if (groupID == SR_ID_INVALID) {
   //        SR_ERROR("ShadedMeshSubCluster::Remove() : failed get mesh group id to remove mesh!");
   //        return false;
   //    }

   //    if (auto&& groupIt = m_groups.find(groupID); groupIt != m_groups.end()) {
   //        MeshGroup& group = groupIt->second;

   //        if (auto pIt = group.find(indexed); pIt != group.end()) {
   //            group.erase(pIt);

   //            --m_counters[groupID];
   //            --m_total;

   //            mesh->SetRender(nullptr);
   //            /// После вызова меш может быть уже не валиден
   //            mesh->RemoveUsePoint();

   //            if (m_counters[groupID] == 0) {
   //                m_groups.erase(groupIt);
   //                m_counters.erase(groupID);
   //            }

   //            return true;
   //        }
   //    }
   //    else {
   //        SR_ERROR("ShadedMeshSubCluster::Remove() : mesh group to remove mesh not found!");
   //        return false;
   //    }

   //    SR_ERROR("ShadedMeshSubCluster::Remove() : mesh not found!");

   //    return false;
   //}

    bool ShadedMeshSubCluster::Add(Types::Mesh *mesh) noexcept {
        auto* indexed = dynamic_cast<Types::IndexedMesh *>(mesh);

        const int32_t groupID = indexed ? indexed->GetVBO<false>() : SR_ID_INVALID;
        if (groupID == SR_ID_INVALID) {
            SR_ERROR("ShadedMeshSubCluster::Add() : failed get mesh group id to remove mesh!");
            return false;
        }

        mesh->AddUsePoint();

        if (auto&& pIt = m_groups.find(groupID); pIt == m_groups.end()) {
            m_groups[groupID] = { indexed };
        }
        else
            pIt->second.insert(indexed);

        //++m_counters[groupID];
       // ++m_total;

        return true;
    }

    bool ShadedMeshSubCluster::Empty() const noexcept {
        return m_groups.empty();
    }

    bool MeshCluster::Add(Types::Mesh *mesh) noexcept {
        const auto&& pShader = mesh->GetShader();

        if (auto&& subClusterIt = m_subClusters.find(pShader); subClusterIt == m_subClusters.end()) {
            auto&& [subCluster, _] = m_subClusters.insert(std::make_pair(
                    pShader,
                    std::move(ShadedMeshSubCluster())
            ));
            return subCluster->second.Add(mesh);
        }
        else {
            return subClusterIt->second.Add(mesh);
        }
    }

    //bool MeshCluster::Remove(Types::Mesh *mesh) noexcept {
    //    const auto&& shader = mesh->GetShader();
//
    //    if (auto&& subCluster = m_subClusters.find(shader); subCluster == m_subClusters.end()) {
    //        return false;
    //    }
    //    else {
    //        auto const result = subCluster->second.Remove(mesh);
//
    //        if (subCluster->second.Empty())
    //            m_subClusters.erase(subCluster);
//
    //        return result;
    //    }
    //}

    bool MeshCluster::Empty() const noexcept {
        return m_subClusters.empty();
    }

    void MeshCluster::Update() {
    repeat:
        for (auto pSubClusterIt = m_subClusters.begin(); pSubClusterIt != m_subClusters.end(); ) {
            auto&& [pShader, subCluster] = *pSubClusterIt;

            for (auto pGroupsIt = subCluster.begin(); pGroupsIt != subCluster.end(); ) {
                auto&& [vbo, group] = *pGroupsIt;

                for (auto pMeshIt = group.begin(); pMeshIt != group.end(); ) {
                    auto&& pMesh = *pMeshIt;
                    auto&& pMaterial = pMesh->GetMaterial();

                    SRAssert2(pMaterial, "Mesh have not material!");

                    if (pMesh->GetCountUses() == 1) {
                        pMesh->RemoveUsePoint();

                        if (pMesh->IsCalculated()) {
                            pMesh->FreeVideoMemory();
                        }

                        pMeshIt = group.erase(pMeshIt);
                        continue;
                    }

                    if (!pMaterial) {
                        ++pMeshIt;
                        continue;
                    }

                    /// Если изменил свой кластер, то убираем его из текущего
                    if (ChangeCluster(pMesh)) {
                        pMeshIt = group.erase(pMeshIt);
                    }
                    /// Если изменили шейдер (в связи с проверкой выше он автоматически непрозрачный), то
                    /// добавляем в этот же кластер
                    else if (pMaterial->GetShader() != pShader) {
                        Add(pMesh);
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
    }

    bool OpaqueMeshCluster::ChangeCluster(MeshCluster::MeshPtr pMesh) {
        if (pMesh->GetMaterial()->IsTransparent()) {
            m_transparent->Add(pMesh);
            return true;
        }

        return false;
    }

    bool TransparentMeshCluster::ChangeCluster(MeshCluster::MeshPtr pMesh) {
        if (!pMesh->GetMaterial()->IsTransparent()) {
            m_opaque->Add(pMesh);
            return true;
        }

        return false;
    }
}

