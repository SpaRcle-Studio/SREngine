//
// Created by Monika on 24.08.2022.
//

#ifndef EVOSCRIPTLIB_VERTICES_H
#define EVOSCRIPTLIB_VERTICES_H

#include "CoreMath.h"

struct StaticMeshVertex {
    float pos[3];
    float uv[2];
    float norm[3];
    float tang[3];
    float bitang[3];

    bool operator==(const StaticMeshVertex& other) const {
        return memcmp(this, &other, sizeof(StaticMeshVertex)) == 0;
    }
};

namespace std {
    template <class T> static inline void hash_combine(std::size_t & s, const T & v) {
        std::hash<T> h;
        s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
    }

    template<> struct hash<StaticMeshVertex> {
        size_t operator()(StaticMeshVertex const& vertex) const {
            std::size_t res = 0;

            hash_combine<float>(res, vertex.pos[0]);
            hash_combine<float>(res, vertex.pos[1]);
            hash_combine<float>(res, vertex.pos[2]);

            hash_combine<float>(res, vertex.uv[0]);
            hash_combine<float>(res, vertex.uv[1]);

            hash_combine<float>(res, vertex.norm[0]);
            hash_combine<float>(res, vertex.norm[1]);
            hash_combine<float>(res, vertex.norm[2]);

            return res;
        }
    };
}

#endif //EVOSCRIPTLIB_VERTICES_H
