//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MATHEMATICS_H
#define GAMEENGINE_MATHEMATICS_H

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#endif

#define RAD(x) x*M_PI/180.0
#define DEG(x) x/M_PI*180.0

#define DegreesToRad(angle) angle*M_PI/180
#define RadToDegrees(angle) angle*180/M_PI
#include <cmath>

namespace Framework::Helper::Math {

}

#endif //GAMEENGINE_MATHEMATICS_H
