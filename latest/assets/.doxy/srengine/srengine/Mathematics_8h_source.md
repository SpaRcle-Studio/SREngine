

# File Mathematics.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Math**](dir_3900fe4b4d95d895210b9082ab5cdd34.md) **>** [**Mathematics.h**](Mathematics_8h.md)

[Go to the documentation of this file](Mathematics_8h.md)


```C++
//
// Created by Nikita on 17.11.2020.
//

#ifndef SR_ENGINE_UTILS_MATHEMATICS_H
#define SR_ENGINE_UTILS_MATHEMATICS_H

#include <Utils/stdInclude.h>

#ifndef M_PI
    #define M_PI (std::numbers::pi)
#endif

#ifndef SR_PI
    #define SR_PI M_PI
#endif

#define SR_RAD(x) (x * (SR_PI / 180.0))
#define SR_DEG(x) (x * (180.0 / SR_PI))

#define RAD(x) (x * (SR_PI / 180.0))
#define DEG(x) (x * (180.0 / SR_PI))

#define SR_DEG_2_RAD (SR_PI * 2.f / 360.f)
#define SR_RAD_2_DEG (1.f / SR_DEG_2_RAD)

#define DegreesToRad(angle) (angle * M_PI / 180)
#define RadToDegrees(angle) (angle * 180 / M_PI)

#define CMP_EPSILON (0.00001)
#define CMP_BIG_EPSILON (0.001)

#define SR_EPSILON (0.00001)
#define SR_BIG_EPSILON (0.001)
#define SR_LARGE_EPSILON (0.00005)
#define SR_EPSILON_NORMAL_SQRT (1e-15)

#define CMP_EPSILON2 (CMP_EPSILON * CMP_EPSILON)
#define UNIT_EPSILON (0.00001)

#define CMP_NORMALIZE_TOLERANCE (0.000001)
#define CMP_POINT_IN_PLANE_EPSILON (0.00001)

#define Math_SQRT12 (0.7071067811865475244008443621048490)
#define Math_SQRT2 (1.4142135623730950488016887242)
#define Math_LN2 (0.6931471805599453094172321215)
#define Math_TAU (6.2831853071795864769252867666)
#define Math_E (2.7182818284590452353602874714)
#define Math_INF (INFINITY)

#define SR_INF std::numeric_limits<double_t>::infinity()
#define SR_NAN NAN
#define SR_INT16_MAX std::numeric_limits<int16_t>::max()
#define SR_UINT16_MAX std::numeric_limits<uint16_t>::max()
#define SR_UINT8_MAX std::numeric_limits<uint8_t>::max()
#define SR_INT8_MAX std::numeric_limits<int8_t>::max()
#define SR_INT32_MAX std::numeric_limits<int32_t>::max()
#define SR_INT32_MIN std::numeric_limits<int32_t>::min()
#define SR_UINT32_MAX std::numeric_limits<uint32_t>::max()
#define SR_INT64_MAX std::numeric_limits<int64_t>::max()
#define SR_UINT64_MAX std::numeric_limits<uint64_t>::max()
#define SR_UINTPTR_MAX std::numeric_limits<uintptr_t>::max()
#define SR_DOUBLE_MAX std::numeric_limits<double_t>::max()
#define SR_FLOAT_MAX std::numeric_limits<float_t>::max()

#define SR_EARTH_GRAVITY_CONST (9.81) // Gravitational Constant (m/s^2)

#define SR_SQUARE(value) (value * value)
#define SR_POW(x, n) std::pow(x, n)
#define SR_SQRT(x) std::sqrt(x)
#define SR_SIN(x) std::sin(x)
#define SR_COS(x) std::cos(x)
#define SR_ARC_SIN(x) std::asin(x)
#define SR_ARC_COS(x) std::acos(x)

#define SR_ABS(x) (SR_MATH_NS::Abs(x))
#define SR_MAX(a, b) (a > b ? a : b)
#define SR_MIN(a, b) (a < b ? a : b)
#define SR_CLAMP(x, lower, upper) (SR_MIN(upper, SR_MAX(x, lower)))

#define RAD3(v) glm::vec3(RAD(v.x), RAD(v.y), RAD(v.z))
#define DEG3(v) glm::vec3(DEG(v.x), DEG(v.y), DEG(v.z))

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>

namespace SR_MATH_NS {
    static SR_FORCE_INLINE bool IsNumber(std::string_view str) {
        bool hasDot = false;
        bool hasNumber = false;

        for (const char* c = str.data(); *c; c++) {
            if (*c == '-' && c == str.data()) {
                continue;
            }

            if (*c == '.' || *c == ',') {
                if (hasDot) {
                    return false;
                }
                hasDot = true;
                continue;
            }

            if (*c < '0' || *c > '9') {
                return false;
            }
            hasNumber = true;
        }

        return hasNumber;
    }

    static SR_FORCE_INLINE bool IsIntegerNumber(std::string_view str) {
        bool hasNumber = false;
        for (const char* c = str.data(); *c; c++) {
            if (*c == '-' && c == str.data()) {
                continue;
            }
            if (*c < '0' || *c > '9') {
                return false;
            }
            hasNumber = true;
        }

        return hasNumber;
    }

    typedef float Unit; 

    constexpr double_t DoubleMAX = std::numeric_limits<double_t>::max();
    constexpr float_t  FloatMAX  = std::numeric_limits<float_t>::max();
    constexpr int32_t  Int32MAX  = std::numeric_limits<int32_t>::max();

    constexpr Unit UnitMAX = FloatMAX;

    template<typename T> SR_NODISCARD SR_FORCE_INLINE static constexpr T Abs(T value) {
        if constexpr (std::is_same_v<T, bool>) {
            return value;
        }
        else {
            return value >= static_cast<T>(0) ? value : -value;
        }
    }

    static SR_FORCE_INLINE Unit Sign(Unit value) {
        return value >= static_cast<Unit>(0) ? static_cast<Unit>(1) : static_cast<Unit>(-1);
    }

    static SR_FORCE_INLINE double_t Lerp(double_t t, double_t a, double_t b) {
        return a + (b + -a) * t;
    }

    template<typename MaskLeft, typename MakeRight> static SR_FORCE_INLINE bool IsMaskIncludedSubMask(MaskLeft mask, MakeRight subMask) {
        return (subMask & mask) == subMask;
    }

    template<typename MaskLeft, typename MakeRight> static SR_FORCE_INLINE bool IsAnyMaskIncludedSubMask(MaskLeft mask, std::initializer_list<MakeRight> subMasks) {
        bool included = false;

        for (auto&& subMask : subMasks) {
            included |= IsMaskIncludedSubMask(mask, subMask);
        }

        return included;
    }

    static SR_FORCE_INLINE double_t SR_FASTCALL FastSqrt(double_t value) {
        return std::sqrt(value);
    }

    template<typename T, typename Y> static SR_FORCE_INLINE bool IsEquals(const T& a, const Y& b) noexcept {
        // Check for exact equality first, required to handle "infinity" values.

        constexpr bool isNeedTolerance = std::is_floating_point_v<T> || std::is_floating_point_v<Y>;

        if constexpr (!isNeedTolerance) {
            return a == b;
        }
        else {
            if (a == b) {
                return true;
            }
            // Then check for approximate equality.
            double tolerance = CMP_EPSILON * Abs(a);
            if (tolerance < CMP_EPSILON) {
                tolerance = CMP_EPSILON;
            }
            return Abs(a - b) < tolerance;
        }
    }

    template<typename T, typename Y, typename Z> static SR_FORCE_INLINE bool IsEquals(const T& a, const Y& b, const Z& tolerance) noexcept {
        // Check for exact equality first, required to handle "infinity" values.
        if (a == b) {
            return true;
        }
        else {
            // Then check for approximate equality.
            return Abs(a - b) < tolerance;
        }
    }

    template<typename T> constexpr bool IsFloat() {
        using Type = RemoveQualifiersT<T>;
        return
            std::is_same_v<Type, float> ||
            std::is_same_v<Type, double> ||
            std::is_same_v<Type, float_t> ||
            std::is_same_v<Type, double_t> ||
            std::is_same_v<Type, Unit>;
    }

    template<typename T> constexpr bool IsBool() {
        using Type = RemoveQualifiersT<T>;
        return std::is_same_v<Type, bool>;
    }

    template<typename T> constexpr bool IsInt() {
        using Type = RemoveQualifiersT<T>;
        return
            std::is_same_v<Type, int> ||
            std::is_same_v<Type, unsigned short> ||
            std::is_same_v<Type, short> ||
            std::is_same_v<Type, unsigned int> ||
            std::is_same_v<Type, unsigned> ||
            std::is_same_v<Type, long> ||
            std::is_same_v<Type, long long> ||
            std::is_same_v<Type, unsigned long long> ||
            std::is_same_v<Type, unsigned long> ||
            std::is_same_v<Type, int64_t> ||
            std::is_same_v<Type, uint64_t> ||
            std::is_same_v<Type, int32_t> ||
            std::is_same_v<Type, uint32_t> ||
            std::is_same_v<Type, int8_t> ||
            std::is_same_v<Type, uint8_t> ||
            std::is_same_v<Type, int16_t> ||
            std::is_same_v<Type, uint16_t>;
    }

    template<typename T> constexpr bool IsNumber() {
        return IsInt<T>() || IsFloat<T>() || IsBool<T>();
    }
}

#define SR_EQUALS(a, b) (SR_MATH_NS::IsEquals(a, b))
#define SR_EQUALS_T(a, b, tolerance) (SR_MATH_NS::IsEquals(a, b, tolerance))
#define Deg180InRad ((SR_MATH_NS::Unit)M_PI)
#define Deg90InRad  ((SR_MATH_NS::Unit)RAD(90.0))

#endif //SR_ENGINE_UTILS_MATHEMATICS_H
```


