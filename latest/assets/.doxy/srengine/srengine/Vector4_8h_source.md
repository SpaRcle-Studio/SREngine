

# File Vector4.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Math**](dir_3900fe4b4d95d895210b9082ab5cdd34.md) **>** [**Vector4.h**](Vector4_8h.md)

[Go to the documentation of this file](Vector4_8h.md)


```C++
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
        using ValueType = T;

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
            const T length = Length();
            return (*this) * (static_cast<T>(1) / (length > SR_FLT_EPSILON ? length : SR_FLT_EPSILON));
        }

        SR_FORCE_INLINE const T& operator[](int32_t axis) const {
            return coord[axis];
        }

        SR_FORCE_INLINE T& operator[](int32_t axis) {
            return coord[axis];
        }

        SR_FORCE_INLINE bool operator==(const Vector4& v) const {
            return SR_EQUALS(x, v.x) && SR_EQUALS(y, v.y) && SR_EQUALS(z, v.z) && SR_EQUALS(w, v.w);
        }

        SR_FORCE_INLINE bool operator!=(const Vector4& v) const {
            return !(*this == v);
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

        SR_NODISCARD T SqrMagnitude() const { return x * x + y * y + z * z + w * w; }

        static constexpr Vector4<T> UnitX() { return Vector4(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); }
        static constexpr Vector4<T> UnitY() { return Vector4(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }
        static constexpr Vector4<T> UnitZ() { return Vector4(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }
        static constexpr Vector4<T> UnitW() { return Vector4(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); }

        SR_FORCE_INLINE Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }

        template<typename U> SR_FORCE_INLINE Vector4 operator*(U p_scalar) const {
            return Vector4(x * p_scalar, y * p_scalar, z * p_scalar, w * p_scalar);
        }

        SR_NODISCARD constexpr Vector3<T> XYZ() const noexcept { return Vector3<T>(x, y, z); }
        SR_NODISCARD constexpr Vector2<T> XY() const noexcept { return Vector2<T>(x, y); }

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

        SR_NODISCARD Unit DistanceToPlane(const SR_MATH_NS::FVector3& point) const {
            return Dot3(point) + w;
        }

        SR_NODISCARD bool IsFinite() const noexcept {
            return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
        }

        SR_NODISCARD T Dot(const Vector4<T>& v) const
        {
            return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
        }

        SR_NODISCARD SR_FORCE_INLINE T Length() const {
            return static_cast<T>(sqrt(x * x + y * y + z * z + w * w));
        }

        template<typename U, typename Y> SR_NODISCARD Vector4 Clamp(U _max, Y _min) const {
            return Vector4(
                SR_CLAMP(x, static_cast<T>(_min), static_cast<T>(_max)),
                SR_CLAMP(y, static_cast<T>(_min), static_cast<T>(_max)),
                SR_CLAMP(z, static_cast<T>(_min), static_cast<T>(_max)),
                SR_CLAMP(w, static_cast<T>(_min), static_cast<T>(_max))
            );
        }
    };

    class FColor : public Vector4<Unit> {
    public:
        SR_FAST_CONSTRUCTOR FColor() : Vector4<Unit>() { }
        SR_FAST_CONSTRUCTOR FColor (Unit scalar) : Vector4<Unit>(scalar) { }
        SR_FAST_CONSTRUCTOR FColor(const glm::vec4& vec4) : Vector4<Unit>(vec4) { }
        SR_FAST_CONSTRUCTOR FColor(const Vector4<Unit>& v) : Vector4<Unit>(v) { }
        SR_FAST_CONSTRUCTOR FColor(const FColor& color) : Vector4<Unit>(color.r, color.g, color.b, color.a) { }
        SR_FAST_CONSTRUCTOR FColor(FColor&& color) : Vector4<Unit>(color.r, color.g, color.b, color.a) { }
        SR_FAST_CONSTRUCTOR FColor(double_t _x, double_t _y, double_t _z, double_t _w) : Vector4<Unit>(_x, _y, _z, _w) { }
        SR_FAST_CONSTRUCTOR FColor(float_t _x, float_t _y, float_t _z, float_t _w) : Vector4<Unit>(_x, _y, _z, _w) { }
        SR_FAST_CONSTRUCTOR FColor(int32_t _x, int32_t _y, int32_t _z, int32_t _w) : Vector4<Unit>(_x, _y, _z, _w) { }

        FColor& operator=(const FColor& color) {
            r = color.r;
            g = color.g;
            b = color.b;
            a = color.a;
            return *this;
        }

        FColor& operator=(FColor&& color) {
            r = color.r;
            g = color.g;
            b = color.b;
            a = color.a;
            return *this;
        }

        static constexpr FColor Red() { return FColor(255.f, 0.f, 0.f, 255.f); }
        static constexpr FColor Green() { return FColor(0.f, 255.f, 0.f, 255.f); }
        static constexpr FColor Blue() { return FColor(0.f, 0.f, 255.f, 255.f); }
        static constexpr FColor White() { return FColor(255.f, 255.f, 255.f, 255.f); }
        static constexpr FColor Black() { return FColor(0.f, 0.f, 0.f, 255.f); }
        static constexpr FColor Yellow() { return FColor(255.f, 255.f, 0.f, 255.f); }
        static constexpr FColor Cyan() { return FColor(0.f, 255.f, 255.f, 255.f); }
        static constexpr FColor Magenta() { return FColor(255.f, 0.f, 255.f, 255.f); }
        static constexpr FColor Alpha() { return FColor(0.f, 0.f, 0.f, 0.f); }

    };

    extern std::unordered_map<SRHashType, FColor> SR_COLOR_PALETTE;

    typedef Vector4<Unit>     FVector4;
    typedef Vector4<int32_t>  IVector4;
    typedef Vector4<uint32_t> UVector4;
    typedef Vector4<bool>     BVector4;

    SR_INLINE static const FVector4 InfinityFV4 = FVector4 { UnitMAX, UnitMAX, UnitMAX, UnitMAX };

    struct Ray {
        SR_NODISCARD Unit IntersectPlaneDistance(const SR_MATH_NS::FVector4& plane) const {
            const Unit numer = plane.Dot3(origin) - plane.w;
            const Unit denom = plane.Dot3(direction);

            if (fabsf(denom) < SR_FLT_EPSILON) {
                return -1.0f;
            }

            return -(numer / denom);
        }

        SR_NODISCARD SR_MATH_NS::FVector3 RotationVector(const SR_MATH_NS::FVector4& plan, const SR_MATH_NS::FVector3& position) const noexcept {
            const Unit len = IntersectPlaneDistance(plan);
            auto&& localPos = origin + direction * len - position;
            auto&& rotationVectorSource = localPos.Normalize();
            return rotationVectorSource;
        }


        SR_NODISCARD Unit ComputeAngleOnPlan(const SR_MATH_NS::FVector4& plan, const SR_MATH_NS::FVector3& position, const SR_MATH_NS::FVector3& sourceRotationVector) const noexcept {
            const Unit len = IntersectPlaneDistance(plan);
            auto&& localPos = (origin + direction * len - position).Normalize();

            auto&& perpendicularVector = sourceRotationVector.Cross(plan.XYZ()).Normalize();

            const Unit acosAngle = SR_CLAMP(localPos.Dot(sourceRotationVector), -1.f, 1.f);
            const Unit angle = acosf(acosAngle) * ((localPos.Dot(perpendicularVector) < 0.f) ? 1.f : -1.f);

            return angle;
        }

        SR_NODISCARD SR_MATH_NS::FVector3 IntersectPlane(const SR_MATH_NS::FVector4& plan) const noexcept {
            const float_t signedLength = IntersectPlaneDistance(plan);
            const float_t len = fabsf(signedLength);
            return origin + direction * len;
        }

        SR_NODISCARD SR_MATH_NS::FVector3 Origin3D() const { return origin; }
        SR_NODISCARD SR_MATH_NS::FVector3 Direction3D() const { return direction; }

        FVector3 origin;
        FVector3 direction;
    };



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
```


