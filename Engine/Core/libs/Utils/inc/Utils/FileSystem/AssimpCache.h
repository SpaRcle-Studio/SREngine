//
// Created by Monika on 15.02.2023.
//

#ifndef SRENGINE_ASSIMPCACHE_H
#define SRENGINE_ASSIMPCACHE_H

#include <Utils/Debug.h>

namespace Assimp {
    class Importer;
}

class aiScene;

namespace SR_UTILS_NS {
    class AssimpCache : public Singleton<AssimpCache> {
        friend class Singleton<AssimpCache>;
        static const uint64_t VERSION = 1002;
    public:
        bool Save(const SR_UTILS_NS::Path& path, const aiScene* pScene) const;
        aiScene* Load(const SR_UTILS_NS::Path& path) const;

    };
}

#endif //SRENGINE_ASSIMPCACHE_H
