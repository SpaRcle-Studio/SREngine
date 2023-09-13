//
// Created by kiper220 on 23.05.2020.
//

#ifndef SR_ENGINE_MAP_H
#define SR_ENGINE_MAP_H

#include <Utils/stdInclude.h>

#ifdef SR_ANDROID
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wconstant-conversion"
    #pragma clang diagnostic ignored "-Wshift-count-overflow"
    #pragma clang diagnostic ignored "-Wc++11-narrowing"
#endif

#include <sparsehash/dense_hash_map>
#include <flat_hash_map/flat_hash_map.hpp>

#ifdef SR_ANDROID
    #pragma clang diagnostic pop
#endif

namespace SR_HTYPES_NS {

}

#endif //SR_ENGINE_MAP_H
