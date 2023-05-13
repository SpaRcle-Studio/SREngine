//
// Created by Monika on 11.01.2023.
//

#ifndef SRENGINE_IMPORTERS_H
#define SRENGINE_IMPORTERS_H

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_ANIMATIONS_NS {
    class Skeleton;
}

namespace SR_CORE_NS::Importers {
    bool ImportSkeletonFromRawMesh(const SR_HTYPES_NS::RawMesh* pRawMesh, SR_ANIMATIONS_NS::Skeleton* pSkeleton);
    SR_ANIMATIONS_NS::Skeleton* ImportSkeletonFromRawMesh(const SR_HTYPES_NS::RawMesh* pRawMesh);
}

#endif //SRENGINE_IMPORTERS_H
