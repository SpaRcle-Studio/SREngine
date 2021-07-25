//
// Created by Nikita on 12.07.2021.
//

#ifndef EVOSCRIPTLIB_MATH_H
#define EVOSCRIPTLIB_MATH_H

#include <cmath>
#include <string>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#endif

#define RAD(x) x * M_PI / 180.0
#define DEG(x) x / M_PI * 180.0

#define _FORCE_INLINE_ __forceinline

typedef double Unit;

#endif //EVOSCRIPTLIB_MATH_H
