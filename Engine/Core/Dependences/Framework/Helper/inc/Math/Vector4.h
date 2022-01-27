//
// Created by Monika on 26.01.2022.
//

#ifndef SRENGINE_VECTOR4_H
#define SRENGINE_VECTOR4_H

#include <Math/Mathematics.h>
#include <macros.h>
#include <glm/vec4.hpp>

namespace Framework::Helper::Math {
    template<typename T> struct Vector4 {
    public:
        union {
            struct {
                T x;
                T y;
                T z;
                T w;
            };

            struct {
                T r;
                T g;
                T b;
                T a;
            };

            T coord[4] = { 0 };
        };
    public:
        _FORCE_INLINE_ Vector4() {
            x = y = z = w = 0;
        }

        _FORCE_INLINE_ Vector4(T scalar) {
            x = y = z = w = scalar;
        }

        _FORCE_INLINE_ Vector4(const glm::vec4& vec4) {
            x = vec4.x;
            y = vec4.y;
            z = vec4.z;
            w = vec4.w;
        }

        _FORCE_INLINE_ Vector4(T _x, T _y, T _z, T _w) {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }

        glm::vec4 ToGLM() const { return { x, y, z, w }; }
    };

    typedef Vector4<Unit>     FColor;
    typedef Vector4<Unit>     FVector4;
    typedef Vector4<int32_t>  IVector4;
    typedef Vector4<uint32_t> UVector4;
}

#endif //SRENGINE_VECTOR4_H
