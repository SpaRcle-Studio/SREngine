//
// Created by Monika on 26.01.2022.
//

#ifndef SR_ENGINE_VECTOR4_H
#define SR_ENGINE_VECTOR4_H

#include <Utils/Math/Mathematics.h>
#include <Utils/Math/Vector3.h>

namespace SR_MATH_NS {
    class Matrix4x4;

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

        SR_FAST_CONSTRUCTOR Vector4(const Vector3<T>& v, T w)
            : x(v.x)
            , y(v.y)
            , z(v.z)
            , w(w)
        { }

    public:
        SR_NODISCARD Vector4 Normalize() const {
            auto&& value = x * x + y * y + z * z + w * w;

            if (value > 0) {
                T len = static_cast<T>(std::sqrt(value));

                Vector4 vec4 = *this;

                if (len != static_cast<T>(0.)) {
                    vec4.x /= len;
                    vec4.y /= len;
                    vec4.z /= len;
                    vec4.w /= len;
                }

                return vec4;
            }

            return *this;
        }

        SR_FORCE_INLINE const T& operator[](int32_t axis) const {
            return coord[axis];
        }

        SR_FORCE_INLINE T& operator[](int32_t axis) {
            return coord[axis];
        }

        template<typename U> SR_FORCE_INLINE Vector4 &operator*=(U p_scalar) {
            x *= p_scalar;
            y *= p_scalar;
            z *= p_scalar;
            w *= p_scalar;
            return *this;
        }

        template<typename U> SR_FORCE_INLINE Vector4& operator/=(U p_scalar) {
            x /= p_scalar;
            y /= p_scalar;
            z /= p_scalar;
            w /= p_scalar;
            return *this;
        }

        template<typename U> SR_FORCE_INLINE Vector4& operator*=(const Vector4<U>& p_v) {
            x *= p_v.x;
            y *= p_v.y;
            z *= p_v.z;
            w *= p_v.w;
            return *this;
        }

        template<typename U> SR_FORCE_INLINE Vector4 operator-(const Vector4<U> &p_v) const {
            return Vector4(x - p_v.x, y - p_v.y, z - p_v.z, w - p_v.w);
        }

        template<typename U> SR_FORCE_INLINE Vector4& operator/=(const Vector4<U>& p_v) {
            x /= p_v.x;
            y /= p_v.y;
            z /= p_v.z;
            w /= p_v.w;
            return *this;
        }

        template<typename U> SR_FORCE_INLINE Vector4 &operator%=(const Vector4<U> &p_v) {
            x %= p_v.x;
            y %= p_v.y;
            z %= p_v.z;
            w %= p_v.w;
            return *this;
        }

        template<typename U> SR_FORCE_INLINE Vector4 operator/(const U& v) const {
            return Vector4(x / v, y / v, z / v, w / v);
        }

        template<typename U> SR_FORCE_INLINE Vector4 operator*(const Vector4<U> &p_v) const {
            return Vector4(x * p_v.x, y * p_v.y, z * p_v.z, w * p_v.w);
        }

        template<typename U> SR_FORCE_INLINE Vector4 operator+(const Vector4<U>& v) const {
            return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
        }

        SR_NODISCARD Vector4 Cross(const Vector4& v) const {
            Vector4 res;
            res.x = y * v.z - z * v.y;
            res.y = z * v.x - x * v.z;
            res.z = x * v.y - y * v.x;
            res.w = 0.f;
            return res;
        }

        SR_FORCE_INLINE Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }

        template<typename U> SR_FORCE_INLINE Vector4 operator*(U p_scalar) const {
            return Vector4(x * p_scalar, y * p_scalar, z * p_scalar, w * p_scalar);
        }

        SR_NODISCARD Vector3<T> XYZ() const noexcept { return Vector3<T>(x, y, z); }
        SR_NODISCARD Vector2<T> XY() const noexcept { return Vector2<T>(x, y); }

        SR_NODISCARD glm::vec4 ToGLM() const { return { x, y, z, w }; }

        SR_NODISCARD T Dot3(const Vector3<T>& v) const {
            return (x * v.x) + (y * v.y) + (z * v.z);
        }

        template<typename U> SR_NODISCARD Vector4<U> SR_FASTCALL Cast() const noexcept { return Vector4<U>(
                    static_cast<U>(x),
                    static_cast<U>(y),
                    static_cast<U>(z),
                    static_cast<U>(w)
            );
        }

        SR_NODISCARD Unit IntersectRayPlane(const SR_MATH_NS::FVector3& origin, const SR_MATH_NS::FVector3& vector) const {
            const Unit numer = Dot3(origin) - w;
            const Unit denom = Dot3(vector);

            /// normal is orthogonal to vector, cant intersect
            if (fabsf(denom) < FLT_EPSILON) {
                return -1.0f;
            }

            return -(numer / denom);
        }

        SR_NODISCARD Unit DistanceToPlane(const SR_MATH_NS::FVector3& point) const {
            return Dot3(point) + w;
        }

        SR_NODISCARD T Dot(const Vector4<T>& v) const
        {
            return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
        }

        SR_NODISCARD SR_FORCE_INLINE T Length() const {
            return static_cast<T>(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)));
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

    static FVector4 BuildPlan(const FVector3& point, const FVector3& normal) {
        return SR_MATH_NS::FVector4(normal, normal.Normalize().Dot(point));
    }

    static FVector4 BuildPlan(const FVector4& point, const FVector4& p_normal) {
        FVector4 normal, res;
        normal = p_normal.Normalize();
        res.w = normal.Dot(point);
        res.x = normal.x;
        res.y = normal.y;
        res.z = normal.z;
        return res;
    }

    static constexpr uint32_t RGBToHEX(const IVector3& color) {
        return ((color.x & 0xff) << 16) + ((color.y & 0xff) << 8) + (color.z & 0xff);
    }

    static constexpr uint32_t BGRToHEX(const IVector3& color) {
        return ((color.z & 0xff) << 16) + ((color.y & 0xff) << 8) + (color.x & 0xff);
    }

    static constexpr IVector3 HEXToRGB(uint32_t hex) {
        IVector3 color;

        color.x = static_cast<Unit>(((hex >> 16) & 0xFF));
        color.y = static_cast<Unit>(((hex >> 8) & 0xFF));
        color.z = static_cast<Unit>(((hex) & 0xFF));

        return color;
    }

    static constexpr IVector3 HEXToBGR(uint32_t hex) {
        IVector3 color;

        color.x = static_cast<Unit>(((hex) & 0xFF));
        color.y = static_cast<Unit>(((hex >> 8) & 0xFF));
        color.z = static_cast<Unit>(((hex >> 16) & 0xFF));

        return color;
    }
}

#endif //SR_ENGINE_VECTOR4_H
