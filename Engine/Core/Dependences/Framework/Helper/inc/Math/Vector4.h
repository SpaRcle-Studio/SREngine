//
// Created by Monika on 26.01.2022.
//

#ifndef SRENGINE_VECTOR4_H
#define SRENGINE_VECTOR4_H

#include <Math/Mathematics.h>

namespace SR_MATH_NS {
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
        SR_FAST_CONSTRUCTOR Vector4() {
            x = y = z = w = 0;
        }

        SR_FAST_CONSTRUCTOR Vector4 (T scalar) {
            x = y = z = w = scalar;
        }

        SR_FAST_CONSTRUCTOR Vector4(const glm::vec4& vec4) {
            x = vec4.x;
            y = vec4.y;
            z = vec4.z;
            w = vec4.w;
        }

        SR_FAST_CONSTRUCTOR Vector4(T _x, T _y, T _z, T _w) {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }

    public:
        SR_NODISCARD glm::vec4 ToGLM() const { return { x, y, z, w }; }

        template<typename U, typename Y> SR_NODISCARD Vector4 Clamp(U _max, Y _min) const {
            return Vector4(
                SR_CLAMP(x, static_cast<T>(_max), static_cast<T>(_min)),
                SR_CLAMP(y, static_cast<T>(_max), static_cast<T>(_min)),
                SR_CLAMP(z, static_cast<T>(_max), static_cast<T>(_min)),
                SR_CLAMP(w, static_cast<T>(_max), static_cast<T>(_min))
            );
        }
    };

    typedef Vector4<Unit>     FColor;
    typedef Vector4<Unit>     FVector4;
    typedef Vector4<int32_t>  IVector4;
    typedef Vector4<uint32_t> UVector4;
}

#endif //SRENGINE_VECTOR4_H
