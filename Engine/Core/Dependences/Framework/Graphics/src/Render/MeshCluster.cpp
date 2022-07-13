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

                --m_counters[groupID];
                --m_total;

                mesh->RemoveUsePoint();
                mesh->SetRender(nullptr);

                if (m_counters[groupID] == 0) {
                    m_groups.erase(groupIt);
                    m_counters.erase(groupID);
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
            SR_ERROR("ShadedMeshSubCluster::Add() : failed get mesh group id to remove mesh!");
            return false;
        }

        if (auto&& pIt = m_groups.find(groupID); pIt == m_groups.end()) {
            m_groups[groupID] = { indexed };
        }
        else
            pIt->second.insert(indexed);

        ++m_counters[groupID];
        ++m_total;

        return true;
    }

    bool ShadedMeshSubCluster::Empty() const noexcept {
        return m_total == 0;
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

    bool MeshCluster::Remove(Types::Mesh *mesh) noexcept {
        const auto&& shader = mesh->GetShader();

        if (auto&& subCluster = m_subClusters.find(shader); subCluster == m_subClusters.end()) {
            return false;
        }
        else {
            auto const result = subCluster->second.Remove(mesh);

            if (subCluster->second.Empty())
                m_subClusters.erase(subCluster);

            return result;
        }
    }

    bool MeshCluster::Empty() const noexcept {
        return m_subClusters.empty();
    }
}

