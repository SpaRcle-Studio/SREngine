//
// Created by Nikita on 12.07.2021.
//

#ifndef EVOSCRIPTLIB_COREMATH_H
#define EVOSCRIPTLIB_COREMATH_H

#include <Libraries/Utils/Allocator.h>

#ifndef SR_PI
    #define SR_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#endif

#ifndef ESMakePair
    #define ESMakePair(type1, type2) std::pair<type1, type2>
#endif

#ifndef SR_NODISCARD
    #define SR_NODISCARD [[nodiscard]]
#endif

#define SR_EPSILON 0.00001

#define SR_RAD(x) x * SR_PI / 180.0
#define SR_DEG(x) x / SR_PI * 180.0

#define SR_ABS(x) (std::abs(x))
#define SR_MAX(a, b) (a > b ? a : b)
#define SR_MIN(a, b) (a < b ? a : b)
#define SR_CLAMP(x, lower, upper) (SR_MIN(upper, SR_MAX(x, lower)))
#define SR_NOOP (void)0

typedef float Unit;

static bool is_equal_approx(Unit a, Unit b) noexcept {
    /// Check for exact equality first, required to handle "infinity" values.
    if (a == b) {
        return true;
    }
    /// Then check for approximate equality.
    double tolerance = SR_EPSILON * abs(a);
    if (tolerance < SR_EPSILON) {
        tolerance = SR_EPSILON;
    }
    return abs(a - b) < tolerance;
}

static bool is_equal_approx(Unit a, Unit b, Unit tolerance) {
    /// Check for exact equality first, required to handle "infinity" values.
    if (a == b) {
        return true;
    }
    /// Then check for approximate equality.
    return abs(a - b) < tolerance;
}

#define SR_EQUALS(a, b) (is_equal_approx(a, b))
#define SR_EQUALS_T(a, b, tolerance) (is_equal_approx(a, b, tolerance))

#endif //EVOSCRIPTLIB_COREMATH_H
