

# File SDF.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Font**](dir_0f9fa5c8aefacabb9ad499652a4f09bc.md) **>** [**SDF.h**](SDF_8h.md)

[Go to the documentation of this file](SDF_8h.md)


```C++
//
// Created by Monika on 18.10.2022.
//

#ifndef SR_ENGINE_SDFL_H
#define SR_ENGINE_SDFL_H

#include <Graphics/macros.h>

#include <Utils/macros.h>

namespace SR_GRAPH_NS::SDF {
    struct Point {
        uint16_t dx, dy;
        int32_t f;
    };

    /* macro is a way faster than inline */
    #define SR_SRF_COMPARE(offsetx, offsety)                                       \
    do {                                                                           \
        int add;                                                                   \
        Point other = Get(x + offsetx, y + offsety);                               \
        if(offsety == 0) {                                                         \
            add = 2 * other.dx + 1;                                                \
        }                                                                          \
        else if(offsetx == 0) {                                                    \
            add = 2 * other.dy + 1;                                                \
        }                                                                          \
        else {                                                                     \
            add = 2 * (other.dy + other.dx + 1);                                   \
        }                                                                          \
        other.f += add;                                                            \
        if (other.f < p.f)                                                         \
        {                                                                          \
            p.f = other.f;                                                         \
            if(offsety == 0) {                                                     \
                p.dx = other.dx + 1;                                               \
                p.dy = other.dy;                                                   \
            }                                                                      \
            else if(offsetx == 0) {                                                \
                p.dy = other.dy + 1;                                               \
                p.dx = other.dx;                                                   \
            }                                                                      \
            else {                                                                 \
                p.dy = other.dy + 1;                                               \
                p.dx = other.dx + 1;                                               \
            }                                                                      \
        }                                                                          \
    } while(0)

    struct Grid {
        int32_t w, h;
        Point* grid;

        void GenerateSDF() const {
            for (int32_t y = 1; y <= h; ++y) {
                for (int32_t x = 1; x <= w; ++x) {
                    Point p = Get(x, y);
                    SR_SRF_COMPARE(-1,  0);
                    SR_SRF_COMPARE( 0, -1);
                    SR_SRF_COMPARE(-1, -1);
                    SR_SRF_COMPARE( 1, -1);
                    Put(x, y, p);
                }
            }

            for(int32_t y = h; y > 0; --y) {
                for(int32_t x = w; x > 0; --x) {
                    Point p = Get(x, y);
                    SR_SRF_COMPARE( 1,  0);
                    SR_SRF_COMPARE( 0,  1);
                    SR_SRF_COMPARE(-1,  1);
                    SR_SRF_COMPARE( 1,  1);
                    Put(x, y, p);
                }
            }
        }

        SR_NODISCARD Point Get(int32_t x, int32_t y) const {
            return grid[y * (w + 2) + x];
        }

        void Put(int32_t x, int32_t y, const Point &p) const {
            grid[y * (w + 2) + x] = p;
        }

        Grid(int32_t width, int32_t height)
            : w(width)
            , h(height)
        {
            grid = new Point[(w + 2) * (h + 2)];
        }

        ~Grid() {
            delete[] grid;
        }
    };

    struct SDFImage {
        void* pData;
        uint32_t width;
        uint32_t height;
    };

    SR_MAYBE_UNUSED static SDFImage DFCalculate(const SDFImage& image, int32_t distanceFieldScale, bool transparent);
}

#endif //SR_ENGINE_SDFL_H
```


