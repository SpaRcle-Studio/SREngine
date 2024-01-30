//
// Created by Monika on 27.08.2022.
//

#ifndef SR_ENGINE_NOISE_H
#define SR_ENGINE_NOISE_H

#include <Utils/Math/NoiseTable.h>

/// Table mask which is used to create indexing values
/// (must be length of the tables - 1)
#define SR_NOISE_TABLE_MASK 0xff

namespace SR_MATH_NS {
    SR_FORCE_INLINE uint8_t TableIndex2D(int32_t ix, int32_t iy) {
        return NoiseTable::perm[(ix + NoiseTable::perm[iy & SR_NOISE_TABLE_MASK]) & SR_NOISE_TABLE_MASK];
    }

    SR_FORCE_INLINE uint8_t TableIndex3D(int32_t ix, int32_t iy, int32_t iz) {
        return NoiseTable::perm[(ix + NoiseTable::perm[(iy + NoiseTable::perm[iz & SR_NOISE_TABLE_MASK]) & SR_NOISE_TABLE_MASK]) & SR_NOISE_TABLE_MASK];
    }

    SR_FORCE_INLINE uint8_t TableIndex4D(int32_t ix, int32_t iy, int32_t iz, int32_t it) {
        return NoiseTable::perm[(it + NoiseTable::perm[(ix + NoiseTable::perm[(iy + NoiseTable::perm[iz & SR_NOISE_TABLE_MASK]) & SR_NOISE_TABLE_MASK]) & SR_NOISE_TABLE_MASK]) & SR_NOISE_TABLE_MASK];
    }

    template<class T_IndexFunc> double_t NoiseTemplate(T_IndexFunc idxfunc, double_t x, double_t y);
    template<class T_IndexFunc> double_t NoiseTemplate(T_IndexFunc idxfunc, double_t x, double_t y, double_t z);
    template<class T_IndexFunc> double_t NoiseTemplate(T_IndexFunc idxfunc, double_t x, double_t y, double_t z, double_t t);

    double_t SNoise(double_t x, double_t y);
    double_t SNoise(double_t x, double_t y, double_t z);
    double_t SNoise(double_t x, double_t y, double_t z, double_t t);
}

namespace SR_MATH_NS {
    template<class T_IndexFunc> double_t NoiseTemplate(T_IndexFunc idxfunc, double_t x, double_t y) {
        /// Determine cell
        int32_t ix = int32_t(floor(x));
        int32_t iy = int32_t(floor(y));

        /// Coordinate components relative to the cell vertices
        double_t rx0 = x - ix;
        double_t ry0 = y - iy;
        double_t rx1 = rx0 - 1.0;
        double_t ry1 = ry0 - 1.0;

        double_t sx = rx0 * rx0 * (3.0 - 2.0 * rx0);
        double_t sy = ry0 * ry0 * (3.0 - 2.0 * ry0);

        const double_t *g;
        double_t u, v;
        double_t a, b;

        g = NoiseTable::grads2[idxfunc(ix, iy)];
        u = g[0] * rx0 + g[1] * ry0;
        g = NoiseTable::grads2[idxfunc(ix + 1, iy)];
        v = g[0] * rx1 + g[1] * ry0;
        a = Lerp(sx, u, v);

        g = NoiseTable::grads2[idxfunc(ix, iy + 1)];
        u = g[0] * rx0 + g[1] * ry1;
        g = NoiseTable::grads2[idxfunc(ix + 1, iy + 1)];
        v = g[0] * rx1 + g[1] * ry1;
        b = Lerp(sx, u, v);

        return Lerp(sy, a, b);
    }

    template<class T_IndexFunc> double_t NoiseTemplate(T_IndexFunc idxfunc, double_t x, double_t y, double_t z) {
        /// Determine cell
        int32_t ix = int32_t(floor(x));
        int32_t iy = int32_t(floor(y));
        int32_t iz = int32_t(floor(z));

        /// Coordinate components relative to the cell vertices
        double_t rx0 = x - ix;
        double_t ry0 = y - iy;
        double_t rz0 = z - iz;
        double_t rx1 = rx0 - 1.0;
        double_t ry1 = ry0 - 1.0;
        double_t rz1 = rz0 - 1.0;

        double_t sx = rx0 * rx0 * (3.0 - 2.0 * rx0);
        double_t sy = ry0 * ry0 * (3.0 - 2.0 * ry0);
        double_t sz = rz0 * rz0 * (3.0 - 2.0 * rz0);

        const double_t *g;
        double_t u, v;
        double_t a, b, c, d;

        g = NoiseTable::grads3[idxfunc(ix, iy, iz)];
        u = g[0] * rx0 + g[1] * ry0 + g[2] * rz0;
        g = NoiseTable::grads3[idxfunc(ix + 1, iy, iz)];
        v = g[0] * rx1 + g[1] * ry0 + g[2] * rz0;
        a = Lerp(sx, u, v);

        g = NoiseTable::grads3[idxfunc(ix, iy + 1, iz)];
        u = g[0] * rx0 + g[1] * ry1 + g[2] * rz0;
        g = NoiseTable::grads3[idxfunc(ix + 1, iy + 1, iz)];
        v = g[0] * rx1 + g[1] * ry1 + g[2] * rz0;
        b = Lerp(sx, u, v);

        c = Lerp(sy, a, b);

        g = NoiseTable::grads3[idxfunc(ix, iy, iz + 1)];
        u = g[0] * rx0 + g[1] * ry0 + g[2] * rz1;
        g = NoiseTable::grads3[idxfunc(ix + 1, iy, iz + 1)];
        v = g[0] * rx1 + g[1] * ry0 + g[2] * rz1;
        a = Lerp(sx, u, v);

        g = NoiseTable::grads3[idxfunc(ix, iy + 1, iz + 1)];
        u = g[0] * rx0 + g[1] * ry1 + g[2] * rz1;
        g = NoiseTable::grads3[idxfunc(ix + 1, iy + 1, iz + 1)];
        v = g[0] * rx1 + g[1] * ry1 + g[2] * rz1;
        b = Lerp(sx, u, v);

        d = Lerp(sy, a, b);

        return Lerp(sz, c, d);
    }

    template<class T_IndexFunc> double_t NoiseTemplate(T_IndexFunc idxfunc, double_t x, double_t y, double_t z, double_t t) {
        /// Determine cell
        int32_t ix = int32_t(floor(x));
        int32_t iy = int32_t(floor(y));
        int32_t iz = int32_t(floor(z));
        int32_t it = int32_t(floor(t));

        /// Coordinate components relative to the cell vertices
        double_t rx0 = x - ix;
        double_t ry0 = y - iy;
        double_t rz0 = z - iz;
        double_t rt0 = t - it;
        double_t rx1 = rx0 - 1.0;
        double_t ry1 = ry0 - 1.0;
        double_t rz1 = rz0 - 1.0;
        double_t rt1 = rt0 - 1.0;

        double_t sx = rx0 * rx0 * (3.0 - 2.0 * rx0);
        double_t sy = ry0 * ry0 * (3.0 - 2.0 * ry0);
        double_t sz = rz0 * rz0 * (3.0 - 2.0 * rz0);
        double_t st = rt0 * rt0 * (3.0 - 2.0 * rt0);

        const double_t *g;
        double_t u, v;
        double_t a, b, c, d, e, f;

        /// at it
        g = NoiseTable::grads4[idxfunc(ix, iy, iz, it)];
        u = g[0] * rx0 + g[1] * ry0 + g[2] * rz0 + g[3] * rt0;
        g = NoiseTable::grads4[idxfunc(ix + 1, iy, iz, it)];
        v = g[0] * rx1 + g[1] * ry0 + g[2] * rz0 + g[3] * rt0;
        a = Lerp(sx, u, v);

        g = NoiseTable::grads4[idxfunc(ix, iy + 1, iz, it)];
        u = g[0] * rx0 + g[1] * ry1 + g[2] * rz0 + g[3] * rt0;
        g = NoiseTable::grads4[idxfunc(ix + 1, iy + 1, iz, it)];
        v = g[0] * rx1 + g[1] * ry1 + g[2] * rz0 + g[3] * rt0;
        b = Lerp(sx, u, v);

        c = Lerp(sy, a, b);

        g = NoiseTable::grads4[idxfunc(ix, iy, iz + 1, it)];
        u = g[0] * rx0 + g[1] * ry0 + g[2] * rz1 + g[3] * rt0;
        g = NoiseTable::grads4[idxfunc(ix + 1, iy, iz + 1, it)];
        v = g[0] * rx1 + g[1] * ry0 + g[2] * rz1 + g[3] * rt0;
        a = Lerp(sx, u, v);

        g = NoiseTable::grads4[idxfunc(ix, iy + 1, iz + 1, it)];
        u = g[0] * rx0 + g[1] * ry1 + g[2] * rz1 + g[3] * rt0;
        g = NoiseTable::grads4[idxfunc(ix + 1, iy + 1, iz + 1, it)];
        v = g[0] * rx1 + g[1] * ry1 + g[2] * rz1 + g[3] * rt0;
        b = Lerp(sx, u, v);

        d = Lerp(sy, a, b);

        e = Lerp(sz, c, d);

        /// at it+1
        g = NoiseTable::grads4[idxfunc(ix, iy, iz, it + 1)];
        u = g[0] * rx0 + g[1] * ry0 + g[2] * rz0 + g[3] * rt1;
        g = NoiseTable::grads4[idxfunc(ix + 1, iy, iz, it + 1)];
        v = g[0] * rx1 + g[1] * ry0 + g[2] * rz0 + g[3] * rt1;
        a = Lerp(sx, u, v);

        g = NoiseTable::grads4[idxfunc(ix, iy + 1, iz, it + 1)];
        u = g[0] * rx0 + g[1] * ry1 + g[2] * rz0 + g[3] * rt1;
        g = NoiseTable::grads4[idxfunc(ix + 1, iy + 1, iz, it + 1)];
        v = g[0] * rx1 + g[1] * ry1 + g[2] * rz0 + g[3] * rt1;
        b = Lerp(sx, u, v);

        c = Lerp(sy, a, b);

        g = NoiseTable::grads4[idxfunc(ix, iy, iz + 1, it + 1)];
        u = g[0] * rx0 + g[1] * ry0 + g[2] * rz1 + g[3] * rt1;
        g = NoiseTable::grads4[idxfunc(ix + 1, iy, iz + 1, it + 1)];
        v = g[0] * rx1 + g[1] * ry0 + g[2] * rz1 + g[3] * rt1;
        a = Lerp(sx, u, v);

        g = NoiseTable::grads4[idxfunc(ix, iy + 1, iz + 1, it + 1)];
        u = g[0] * rx0 + g[1] * ry1 + g[2] * rz1 + g[3] * rt1;
        g = NoiseTable::grads4[idxfunc(ix + 1, iy + 1, iz + 1, it + 1)];
        v = g[0] * rx1 + g[1] * ry1 + g[2] * rz1 + g[3] * rt1;
        b = Lerp(sx, u, v);

        d = Lerp(sy, a, b);

        f = Lerp(sz, c, d);

        return Lerp(st, e, f);
    }
}

#endif //SR_ENGINE_NOISE_H
