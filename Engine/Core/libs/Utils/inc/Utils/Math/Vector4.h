//
// Created by Monika on 26.01.2022.
//

#ifndef SRENGINE_VECTOR4_H
#define SRENGINE_VECTOR4_H

#include <Utils/Math/Mathematics.h>

namespace SR_MATH_NS {
    template<typename T> struct SR_DLL_EXPORT Vector4 {
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

        SR_FAST_CONSTRUCTOR Vector4(T _x, T _y, T _z, T _w)
            : x(_x)
            , y(_y)
            , z(_z)
            , w(_w)
        { }

    public:
        SR_NODISCARD glm::vec4 ToGLM() const { return { x, y, z, w }; }

        template<typename U> SR_NODISCARD Vector4<U> SR_FASTCALL Cast() const noexcept { return Vector4<U>(
                    static_cast<U>(x),
                    static_cast<U>(y),
                    static_cast<U>(z),
                    static_cast<U>(w)
            );
        }

        template<typename U, typename Y> SR_NODISCARD Vector4 Clamp(U _max, Y _min) const {
            return Vector4(
                SR_CLAMP(x, static_cast<T>(_max), static_cast<T>(_min)),
                SR_CLAMP(y, static_cast<T>(_max), static_cast<T>(_min)),
                SR_CLAMP(z, static_cast<T>(_max), static_cast<T>(_min)),
                SR_CLAMP(w, static_cast<T>(_max), static_cast<T>(_min))
            );
        }
    };

    class FColor : public Vector4<Unit> {
    public:
        SR_FAST_CONSTRUCTOR FColor() : Vector4<Unit>() { }
        SR_FAST_CONSTRUCTOR FColor (Unit scalar) : Vector4<Unit>(scalar) { }
        SR_FAST_CONSTRUCTOR FColor(const glm::vec4& vec4) : Vector4<Unit>(vec4) { }
        SR_FAST_CONSTRUCTOR FColor(double_t _x, double_t _y, double_t _z, double_t _w) : Vector4<Unit>(_x, _y, _z, _w) { }
        SR_FAST_CONSTRUCTOR FColor(float_t _x, float_t _y, float_t _z, float_t _w) : Vector4<Unit>(_x, _y, _z, _w) { }
        SR_FAST_CONSTRUCTOR FColor(int32_t _x, int32_t _y, int32_t _z, int32_t _w) : Vector4<Unit>(_x, _y, _z, _w) { }
    };

    typedef Vector4<Unit>     FVector4;
    typedef Vector4<int32_t>  IVector4;
    typedef Vector4<uint32_t> UVector4;

    static constexpr FVector3 RGBFromUInt32(uint32_t integral) {
        const uint32_t red = (integral & 0xff000000) >> 16;
        const uint32_t green = (integral & 0x00ff0000) >> 8;
        const uint32_t blue = (integral & 0x0000ff00);

        return FVector3(red / 255.f, green / 255.f, blue / 255.f);
    }
}

#endif //SRENGINE_VECTOR4_H
