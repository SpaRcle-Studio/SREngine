//
// Created by Monika on 31.10.2021.
//

#ifndef GAMEENGINE_MESHCLUSTER_H
#define GAMEENGINE_MESHCLUSTER_H

#include <vector>
#include <map>
#include <cctype>

namespace Framework::Graphics {
    namespace Types {
        class IndexedMesh;
        class Mesh;
    }

    typedef std::map <uint32_t, std::vector<Types::IndexedMesh *>> MeshGroups;
    typedef std::map <uint32_t, uint32_t> MeshGroupCounters;

    struct MeshCluster {
        MeshGroups m_groups = MeshGroups();
        MeshGroupCounters m_counters = MeshGroupCounters();
        uint32_t m_total = 0;

        bool Add(Types::Mesh *mesh);

        bool Remove(Types::Mesh *mesh);
    };
}

#endif //GAMEENGINE_MESHCLUSTER_H
