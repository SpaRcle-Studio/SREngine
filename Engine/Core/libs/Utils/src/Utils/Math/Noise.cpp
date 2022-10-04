//
// Created by Monika on 27.08.2022.
//

#include <Utils/Math/Noise.h>

namespace SR_MATH_NS {
    double_t SNoise(double_t x, double_t y) {
        return NoiseTemplate(TableIndex2D, x, y);
    }

    double_t SNoise(double_t x, double_t y, double_t z) {
        return NoiseTemplate(TableIndex3D, x, y, z);
    }

    double_t SNoise(double_t x, double_t y, double_t z, double_t t) {
        return NoiseTemplate(TableIndex4D, x, y, z, t);
    }
}