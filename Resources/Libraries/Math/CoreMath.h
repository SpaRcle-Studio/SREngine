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

#define SR_RAD(x) x * SR_PI / 180.0
#define SR_DEG(x) x / SR_PI * 180.0

typedef double Unit;

#endif //EVOSCRIPTLIB_COREMATH_H
