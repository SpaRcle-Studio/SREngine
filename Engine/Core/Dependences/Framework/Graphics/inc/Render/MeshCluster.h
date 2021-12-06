//
// Created by Monika on 31.10.2021.
//

#ifndef GAMEENGINE_MESHCLUSTER_H
#define GAMEENGINE_MESHCLUSTER_H

#include <vector>
#include <unordered_map>
#include <cctype>

namespace Framework::Graphics {
    namespace Types {
        class IndexedMesh;
        class Mesh;
    }

    class Shader;

    typedef std::unordered_map<uint32_t, std::vector<Types::IndexedMesh *>> MeshGroups;
    typedef std::unordered_map<uint32_t, uint32_t> MeshGroupCounters;

    struct ShadedMeshSubCluster {
        MeshGroups        m_groups   = MeshGroups();
        MeshGroupCounters m_counters = MeshGroupCounters();
        uint32_t          m_total    = 0;

        bool Add(Types::Mesh *mesh);
        bool Remove(Types::Mesh *mesh);

        [[nodiscard]] bool Empty() const;
    };

    struct MeshCluster {
        std::unordered_map<Shader*, ShadedMeshSubCluster> m_subClusters;

        bool Add(Types::Mesh *mesh);
        bool Remove(Types::Mesh *mesh);
    };
}

#define SRDrawMeshCluster(cluster, PipeLine, postShaderBindingCode)        \
    {                                                                      \
        static Environment* env = Environment::Get();                      \
                                                                           \
        for (auto const& [shader, subCluster] : cluster.m_subClusters) {   \
            if (shader) shader->Use();                                     \
            else                                                           \
                continue;                                                  \
                                                                           \
            postShaderBindingCode                                          \
                                                                           \
            for (auto const& [key, meshGroup] : subCluster.m_groups) {     \
                env->BindVBO(meshGroup[0]->GetVBO<true>());                \
                env->BindIBO(meshGroup[0]->GetIBO<true>());                \
                                                                           \
                for (const auto &mesh : meshGroup)                         \
                    mesh->Draw##PipeLine();                                \
            }                                                              \
                                                                           \
            env->UnUseShader();                                            \
        }                                                                  \
    }                                                                      \

#endif //GAMEENGINE_MESHCLUSTER_H
