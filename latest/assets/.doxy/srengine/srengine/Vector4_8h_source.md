

# File Vector4.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Math**](dir_f20ff43999c2f98e3f122645c07885db.md) **>** [**Vector4.h**](Vector4_8h.md)

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

    template<typename T> struct Vector4 {
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
        Vector4();
        Vector4(T scalar);
        Vector4(const glm::vec4& vec4);
        Vector4(T _x, T _y, T _z, T _w);
        Vector4(const Vector3<T>& v, T w);

    public:
        SR_NODISCARD Vector4 Normalize() const;

        const T& operator[](int32_t axis) const;
        T& operator[](int32_t axis);

        bool operator==(const Vector4& v) const;
        bool operator!=(const Vector4& v) const;

        template<typename U> Vector4& operator*=(U p_scalar);
        template<typename U> Vector4& operator/=(U p_scalar);
        template<typename U> Vector4& operator*=(const Vector4<U>& p_v);
        template<typename U> Vector4 operator-(const Vector4<U> &p_v) const;
        template<typename U> Vector4& operator/=(const Vector4<U>& p_v);
        template<typename U> Vector4 &operator%=(const Vector4<U> &p_v);
        template<typename U> Vector4 operator/(const U& v) const;
        template<typename U> Vector4 operator*(const Vector4<U> &p_v) const;
        template<typename U> Vector4 operator+(const Vector4<U>& v) const;

        SR_NODISCARD Vector4 Cross(const Vector4& v) const;
        SR_NODISCARD T SqrMagnitude() const;

        static Vector4<T> UnitX();
        static Vector4<T> UnitY();
        static Vector4<T> UnitZ();
        static Vector4<T> UnitW();

        Vector4 operator-() const;

        template<typename U> Vector4 operator*(U p_scalar) const;

        SR_NODISCARD Vector3<T> XYZ() const noexcept;
        SR_NODISCARD Vector2<T> XY() const noexcept;

        SR_NODISCARD glm::vec4 ToGLM() const { return { x, y, z, w }; }

        SR_NODISCARD T Dot3(const Vector3<T>& v) const;

        template<typename U> SR_NODISCARD Vector4<U> SR_FASTCALL Cast() const noexcept;

        SR_NODISCARD Unit DistanceToPlane(const SR_MATH_NS::FVector3& point) const;

        SR_NODISCARD bool IsFinite() const noexcept;

        SR_NODISCARD T Dot(const Vector4<T>& v) const;

        SR_NODISCARD T Length() const;

        template<typename U, typename Y> SR_NODISCARD Vector4 Clamp(U _max, Y _min) const;
    };

    class SR_COMMON_DLL_API FColor {
    public:
        union {
            struct {
                Unit x;
                Unit y;
                Unit z;
                Unit w;
            };

            struct {
                Unit r;
                Unit g;
                Unit b;
                Unit a;
            };

            Unit coord[4] = { 0 };
        };
    public:
        FColor();
        FColor(Unit scalar);
        FColor(const glm::vec4& vec4);
        FColor(const Vector4<Unit>& v);
        FColor(const FColor& color);
        FColor(FColor&& color);
        FColor(double_t _x, double_t _y, double_t _z, double_t _w = 1.0);
        FColor(float_t _x, float_t _y, float_t _z, float_t _w = 1.f);
        FColor(int32_t _x, int32_t _y, int32_t _z, int32_t _w = 1);

        FColor& operator=(const FColor& color);
        FColor& operator=(FColor&& color);

        bool operator==(const FColor& v) const;
        bool operator!=(const FColor& v) const;

        FColor& operator*=(Unit p_scalar);
        FColor& operator/=(Unit p_scalar);
        FColor& operator*=(const FColor& p_v);
        FColor operator-(const FColor &p_v) const;
        FColor& operator/=(const FColor& p_v);
        FColor &operator%=(const FColor &p_v);
        FColor operator/(const Unit& v) const;
        FColor operator*(const FColor &p_v) const;
        FColor operator+(const FColor& v) const;

        static FColor Red();
        static FColor Green();
        static FColor Blue();
        static FColor White();
        static FColor Black();
        static FColor Yellow();
        static FColor Cyan();
        static FColor Magenta();
        static FColor Alpha();
    };

    extern std::unordered_map<SRHashType, FColor> SR_COLOR_PALETTE;

    typedef Vector4<Unit>     FVector4;
    typedef Vector4<int32_t>  IVector4;
    typedef Vector4<uint32_t> UVector4;
    typedef Vector4<bool>     BVector4;

    SR_INLINE static const FVector4 InfinityFV4 = FVector4 { UnitMAX, UnitMAX, UnitMAX, UnitMAX };

    struct SR_COMMON_DLL_API Ray {
        Ray();
        ~Ray();

        SR_NODISCARD Unit IntersectPlaneDistance(const SR_MATH_NS::FVector4& plane) const;
        SR_NODISCARD SR_MATH_NS::FVector3 RotationVector(const SR_MATH_NS::FVector4& plan, const SR_MATH_NS::FVector3& position) const noexcept;
        SR_NODISCARD Unit ComputeAngleOnPlan(const SR_MATH_NS::FVector4& plan, const SR_MATH_NS::FVector3& position, const SR_MATH_NS::FVector3& sourceRotationVector) const noexcept;

        SR_NODISCARD SR_MATH_NS::FVector3 IntersectPlane(const SR_MATH_NS::FVector4& plan) const noexcept;
        SR_NODISCARD SR_MATH_NS::FVector3 Origin3D() const;
        SR_NODISCARD SR_MATH_NS::FVector3 Direction3D() const;

        FVector3 origin;
        FVector3 direction;
    };

    FVector4 BuildPlan(const FVector3& point, const FVector3& normal);
    FVector4 BuildPlan(const FVector4& point, const FVector4& p_normal);
    uint32_t RGBToHEX(const IVector3& color);
    uint32_t BGRToHEX(const IVector3& color);
    IVector3 HEXToRGB(uint32_t hex);
    IVector3 HEXToBGR(uint32_t hex);


#if 1
    template<typename T> Vector4<T>::Vector4() {
        x = y = z = w = 0;
    }

    template<typename T> Vector4<T>::Vector4(T scalar) {
        x = y = z = w = scalar;
    }

    template<typename T> Vector4<T>::Vector4(const glm::vec4& vec4) {
        x = vec4.x;
        y = vec4.y;
        z = vec4.z;
        w = vec4.w;
    }

    template<typename T> Vector4<T>::Vector4(T _x, T _y, T _z, T _w)
        : x(_x)
        , y(_y)
        , z(_z)
        , w(_w)
    { }

    template<typename T> Vector4<T>::Vector4(const Vector3<T>& v, T w)
        : x(v.x)
        , y(v.y)
        , z(v.z)
        , w(w)
    { }

    template<typename T> SR_NODISCARD Vector4<T> Vector4<T>::Normalize() const {
        const T length = Length();
        return (*this) * (static_cast<T>(1) / (length > SR_FLT_EPSILON ? length : SR_FLT_EPSILON));
    }

    template<typename T> const T& Vector4<T>::operator[](int32_t axis) const {
        return coord[axis];
    }

    template<typename T> T& Vector4<T>::operator[](int32_t axis) {
        return coord[axis];
    }

    template<typename T> bool Vector4<T>::operator==(const Vector4<T>& v) const {
        return SR_EQUALS(x, v.x) && SR_EQUALS(y, v.y) && SR_EQUALS(z, v.z) && SR_EQUALS(w, v.w);
    }

    template<typename T> bool Vector4<T>::operator!=(const Vector4<T>& v) const {
        return !(*this == v);
    }

    template<typename T> template<typename U> Vector4<T>& Vector4<T>::operator*=(U p_scalar) {
        x *= p_scalar;
        y *= p_scalar;
        z *= p_scalar;
        w *= p_scalar;
        return *this;
    }

    template<typename T> template<typename U> Vector4<T>& Vector4<T>::operator/=(U p_scalar) {
        x /= p_scalar;
        y /= p_scalar;
        z /= p_scalar;
        w /= p_scalar;
        return *this;
    }

    template<typename T> template<typename U> Vector4<T>& Vector4<T>::operator*=(const Vector4<U>& p_v) {
        x *= p_v.x;
        y *= p_v.y;
        z *= p_v.z;
        w *= p_v.w;
        return *this;
    }

    template<typename T> template<typename U> Vector4<T> Vector4<T>::operator-(const Vector4<U> &p_v) const {
        return Vector4(x - p_v.x, y - p_v.y, z - p_v.z, w - p_v.w);
    }

    template<typename T> template<typename U> Vector4<T>& Vector4<T>::operator/=(const Vector4<U>& p_v) {
        x /= p_v.x;
        y /= p_v.y;
        z /= p_v.z;
        w /= p_v.w;
        return *this;
    }

    template<typename T> template<typename U> Vector4<T>& Vector4<T>::operator%=(const Vector4<U>& p_v) {
        x %= p_v.x;
        y %= p_v.y;
        z %= p_v.z;
        w %= p_v.w;
        return *this;
    }

    template<typename T> template<typename U> Vector4<T> Vector4<T>::operator/(const U& v) const {
        return Vector4(x / v, y / v, z / v, w / v);
    }

    template<typename T> template<typename U> Vector4<T> Vector4<T>::operator*(const Vector4<U> &p_v) const {
        return Vector4(x * p_v.x, y * p_v.y, z * p_v.z, w * p_v.w);
    }

    template<typename T> template<typename U> Vector4<T> Vector4<T>::operator+(const Vector4<U>& v) const {
        return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    template<typename T> SR_NODISCARD Vector4<T> Vector4<T>::Cross(const Vector4& v) const {
        Vector4 res;
        res.x = y * v.z - z * v.y;
        res.y = z * v.x - x * v.z;
        res.z = x * v.y - y * v.x;
        res.w = 0.f;
        return res;
    }

    template<typename T> SR_NODISCARD T Vector4<T>::SqrMagnitude() const { return x * x + y * y + z * z + w * w; }

    template<typename T> Vector4<T> Vector4<T>::UnitX() { return Vector4(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); }
    template<typename T> Vector4<T> Vector4<T>::UnitY() { return Vector4(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }
    template<typename T> Vector4<T> Vector4<T>::UnitZ() { return Vector4(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }
    template<typename T> Vector4<T> Vector4<T>::UnitW() { return Vector4(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); }

    template<typename T> Vector4<T> Vector4<T>::operator-() const { return Vector4(-x, -y, -z, -w); }

    template<typename T> template<typename U> Vector4<T> Vector4<T>::operator*(U p_scalar) const {
        return Vector4(x * p_scalar, y * p_scalar, z * p_scalar, w * p_scalar);
    }

    template<typename T> SR_NODISCARD Vector3<T> Vector4<T>::XYZ() const noexcept { return Vector3<T>(x, y, z); }
    template<typename T> SR_NODISCARD Vector2<T> Vector4<T>::XY() const noexcept { return Vector2<T>(x, y); }

    template<typename T> SR_NODISCARD T Vector4<T>::Dot3(const Vector3<T>& v) const {
        return (x * v.x) + (y * v.y) + (z * v.z);
    }

    template<typename T> template<typename U> SR_NODISCARD Vector4<U> SR_FASTCALL Vector4<T>::Cast() const noexcept { return Vector4<U>(
        static_cast<U>(x),
            static_cast<U>(y),
            static_cast<U>(z),
            static_cast<U>(w)
        );
    }

    template<typename T> Unit Vector4<T>::DistanceToPlane(const SR_MATH_NS::FVector3& point) const {
        return Dot3(point) + w;
    }

    template<typename T> SR_NODISCARD bool Vector4<T>::IsFinite() const noexcept {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }

    template<typename T> SR_NODISCARD T Vector4<T>::Dot(const Vector4<T>& v) const
    {
        return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
    }

    template<typename T> SR_NODISCARD T Vector4<T>::Length() const {
        return static_cast<T>(sqrt(x * x + y * y + z * z + w * w));
    }

    template<typename T> template<typename U, typename Y> SR_NODISCARD Vector4<T> Vector4<T>::Clamp(U _max, Y _min) const {
        return Vector4(
            SR_CLAMP(x, static_cast<T>(_min), static_cast<T>(_max)),
            SR_CLAMP(y, static_cast<T>(_min), static_cast<T>(_max)),
            SR_CLAMP(z, static_cast<T>(_min), static_cast<T>(_max)),
            SR_CLAMP(w, static_cast<T>(_min), static_cast<T>(_max))
        );
    }
#endif
}

#endif //SR_ENGINE_VECTOR4_H
```


