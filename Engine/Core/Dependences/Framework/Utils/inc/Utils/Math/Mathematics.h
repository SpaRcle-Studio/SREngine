//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MATHEMATICS_H
#define GAMEENGINE_MATHEMATICS_H

#include <Utils/macros.h>

#ifndef M_PI
    #define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#endif

#ifndef SR_PI
    #define SR_PI M_PI
#endif

#define SR_POW(value) (value * value)

#define SR_RAD(x) (x * (SR_PI / 180.0))
#define SR_DEG(x) (x * (180.0 / SR_PI))

#define RAD(x) (x * (SR_PI / 180.0))
#define DEG(x) (x * (180.0 / SR_PI))

//#define _FORCE_INLINE_ __attribute__((always_inline))
//#define _ALWAYS_INLINE_ inline __attribute__((always_inline))

#define DegreesToRad(angle) angle*M_PI/180
#define RadToDegrees(angle) angle*180/M_PI

#define CMP_EPSILON 0.00001
#define CMP_BIG_EPSILON 0.001
#define CMP_EPSILON2 (CMP_EPSILON * CMP_EPSILON)
#define UNIT_EPSILON 0.00001

#define CMP_NORMALIZE_TOLERANCE 0.000001
#define CMP_POINT_IN_PLANE_EPSILON 0.00001

#define Math_SQRT12 0.7071067811865475244008443621048490
#define Math_SQRT2 1.4142135623730950488016887242
#define Math_LN2 0.6931471805599453094172321215
#define Math_TAU 6.2831853071795864769252867666
#define Math_E 2.7182818284590452353602874714
#define Math_INF INFINITY

#define SR_INF INFINITY
#define SR_NAN NAN
#define SR_INT16_MAX INT16_MAX
#define SR_UINT16_MAX UINT16_MAX
#define SR_INT32_MAX INT32_MAX
#define SR_INT32_MIN INT32_MIN
#define SR_UINT32_MAX UINT32_MAX
#define SR_INT64_MAX INT64_MAX
#define SR_UINT64_MAX UINT64_MAX
#define SR_UINTPTR_MAX UINTPTR_MAX
#define SR_DOUBLE_MAX DBL_MAX
#define SR_FLOAT_MAX FLT_MAX

#define SR_EARTH_GRAVITY 9.81

#define SR_MAX(a, b) (a > b ? a : b)
#define SR_MIN(a, b) (a < b ? a : b)
#define SR_CLAMP(x, upper, lower) (SR_MIN(upper, SR_MAX(x, lower)))

#define RAD3(v) glm::vec3(RAD(v.x), RAD(v.y), RAD(v.z))
#define DEG3(v) glm::vec3(DEG(v.x), DEG(v.y), DEG(v.z))

#include <cmath>
#include <cfloat>
#include <cstdint>
#include <limits>
#include <string>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/detail/type_quat.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace SR_MATH_NS {
    typedef double Unit; //! can broke render

    const double_t DoubleMAX = DBL_MAX;
    const float_t  FloatMAX  = FLT_MAX;
    const int32_t  Int32MAX  = INT32_MAX;

    const Unit UnitMAX = DoubleMAX;

    SR_FORCE_INLINE double_t Lerp(double_t t, double_t a, double_t b) {
        return a + (b + -a) * t;
    }

    static SR_FORCE_INLINE double_t SR_FASTCALL FastSqrt(double_t value) {
        return std::sqrt(value);
    }

    static SR_FORCE_INLINE bool is_equal_approx(Unit a, Unit b) noexcept {
        // Check for exact equality first, required to handle "infinity" values.
        if (a == b) {
            return true;
        }
        // Then check for approximate equality.
        double tolerance = CMP_EPSILON * abs(a);
        if (tolerance < CMP_EPSILON) {
            tolerance = CMP_EPSILON;
        }
        return abs(a - b) < tolerance;
    }
    static SR_FORCE_INLINE bool is_equal_approx(Unit a, Unit b, Unit tolerance) {
        // Check for exact equality first, required to handle "infinity" values.
        if (a == b) {
            return true;
        }
        // Then check for approximate equality.
        return abs(a - b) < tolerance;
    }

    template<typename T> constexpr bool IsVolatile() {
        return std::is_volatile<T>::value;
    }

    template<typename T> constexpr bool IsLogical() {
        if (!IsVolatile<T>()) {
            return IsLogical<volatile T>();
        }

        return std::is_same_v<T, volatile bool>;
    }

    template<typename T> constexpr bool IsString() {
        if (!IsVolatile<T>()) {
            return IsString<volatile T>();
        }

        return std::is_same_v<T, volatile std::string>;
    }

    template<typename T> constexpr bool IsNumber() {
        if (!IsVolatile<T>()) {
            return IsNumber<volatile T>();
        }

        return
            std::is_same_v<T, volatile bool> ||
            std::is_same_v<T, volatile float> ||
            std::is_same_v<T, volatile double> ||
            std::is_same_v<T, volatile int> ||
            std::is_same_v<T, volatile unsigned short> ||
            std::is_same_v<T, volatile short> ||
            std::is_same_v<T, volatile unsigned int> ||
            std::is_same_v<T, volatile unsigned> ||
            std::is_same_v<T, volatile long> ||
            std::is_same_v<T, volatile long long> ||
            std::is_same_v<T, volatile unsigned long long> ||
            std::is_same_v<T, volatile unsigned long> ||
            std::is_same_v<T, volatile float_t> ||
            std::is_same_v<T, volatile double_t> ||
            std::is_same_v<T, volatile int64_t> ||
            std::is_same_v<T, volatile uint64_t> ||
            std::is_same_v<T, volatile int32_t> ||
            std::is_same_v<T, volatile uint32_t> ||
            std::is_same_v<T, volatile int8_t> ||
            std::is_same_v<T, volatile uint8_t> ||
            std::is_same_v<T, volatile int16_t> ||
            std::is_same_v<T, volatile uint16_t> ||
            std::is_same_v<T, volatile Unit>;
    }
}

#define SR_EQUALS(a, b) (Framework::Helper::Math::is_equal_approx(a, b))
#define SR_EQUALS_T(a, b, tolerance) (Framework::Helper::Math::is_equal_approx(a, b, tolerance))
#define Deg180InRad ((Framework::Helper::Math::Unit)M_PI)
#define Deg90InRad  ((Framework::Helper::Math::Unit)RAD(90.0))

#endif //GAMEENGINE_MATHEMATICS_H
