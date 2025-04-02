

# File Vector6.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Math**](dir_3900fe4b4d95d895210b9082ab5cdd34.md) **>** [**Vector6.h**](Vector6_8h.md)

[Go to the documentation of this file](Vector6_8h.md)


```C++
//
// Created by Monika on 08.07.2022.
//

#ifndef SR_ENGINE_VECTOR6_H
#define SR_ENGINE_VECTOR6_H

#include <Utils/Math/Mathematics.h>
#include <Utils/Math/Vector3.h>

namespace SR_MATH_NS {
    template<typename T> struct SR_DLL_EXPORT Vector6 {
    public:
        union {
            struct {
                T x;
                T y;
                T z;
                T w;
                T v;
                T u;
            };

            T coord[6] = { 0 };

            struct {
                SR_MATH_NS::Vector3<T> vec3d1;
                SR_MATH_NS::Vector3<T> vec3d2;
            };

            struct {
                SR_MATH_NS::Vector2<T> vec2d1;
                SR_MATH_NS::Vector2<T> vec2d2;
                SR_MATH_NS::Vector2<T> vec2d3;
            };
        };
    public:
        SR_FAST_CONSTRUCTOR Vector6() {
            x = y = z = w = v = u = 0;
        }

        SR_FAST_CONSTRUCTOR Vector6(SR_MATH_NS::Vector3<T> vec3d1, SR_MATH_NS::Vector3<T> vec3d2)
            : vec3d1(vec3d1)
            , vec3d2(vec3d2)
        { }

        SR_FAST_CONSTRUCTOR Vector6(T scalar) {
            x = y = z = w = v = u = scalar;
        }

        SR_FORCE_INLINE bool operator==(const Vector6 &p_v) const {
            return SR_EQUALS(x, p_v.x)
                && SR_EQUALS(y, p_v.y)
                && SR_EQUALS(z, p_v.z)
                && SR_EQUALS(w, p_v.w)
                && SR_EQUALS(v, p_v.v)
                && SR_EQUALS(u, p_v.u);
        }

        SR_FORCE_INLINE bool operator!=(const Vector6 &p_v) const {
            return !(*this == p_v);
        }

        template<typename U> SR_FAST_CONSTRUCTOR explicit Vector6(const Vector3<U>& vec) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
            z = static_cast<T>(vec.z);
            w = static_cast<T>(vec.w);
            v = static_cast<T>(vec.v);
            u = static_cast<T>(vec.u);
        }

        template<typename U> SR_FAST_CONSTRUCTOR explicit Vector6(const Vector3<U>& vec1, const Vector3<U>& vec2) {
            x = static_cast<T>(vec1.x);
            y = static_cast<T>(vec1.y);
            z = static_cast<T>(vec1.z);
            w = static_cast<T>(vec2.x);
            v = static_cast<T>(vec2.y);
            u = static_cast<T>(vec2.z);
        }

        SR_FAST_CONSTRUCTOR Vector6(T _x, T _y, T _z, T _w, T _v, T _u) {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
            v = _v;
            u = _u;
        }
    };

    typedef Vector6<Unit>     FVector6;
    typedef Vector6<int32_t>  IVector6;
    typedef Vector6<uint32_t> UVector6;
}

#endif //SR_ENGINE_VECTOR6_H
```


