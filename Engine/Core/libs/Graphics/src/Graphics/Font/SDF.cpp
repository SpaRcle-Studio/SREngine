//
// Created by Monika on 18.10.2022.
//

#include <Graphics/Font/SDF.h>

namespace SR_GRAPH_NS::SDF {
    SDFImage DFCalculate(const SDFImage& image, int32_t distanceFieldScale, bool transparent) {
        SDFImage result;

        int32_t x, y;
        int32_t w = image.width, h = image.height;

        Grid grid[2] = { Grid(w, h), Grid(w, h) };

        constexpr Point pointInside = { 0, 0, 0 };
        constexpr Point pointEmpty = { 9999, 9999, 9999 * 9999 };

        /** create 1-pixel gap */
        for(x = 0; x < w + 2; ++x) {
            grid[0].Put(x, 0, pointInside);
            grid[1].Put(x, 0, pointEmpty);
        }

        for(y = 1; y <= h; ++y) {
            grid[0].Put(0, y, pointInside);
            grid[1].Put(0, y, pointEmpty);

            for(x = 1; x <= w; ++x)
            {
                // if(qGreen(img->pixel(x - 1, y - 1)) > 128) {
                //     grid[0].Put(x, y, pointEmpty);
                //     grid[1].Put(x, y, pointInside);
                // }
                // else {
                //     grid[0].Put(x, y, pointInside);
                //     grid[1].Put(x, y, pointEmpty);
                // }
            }
            grid[0].Put(w + 1, y, pointInside);
            grid[1].Put(w + 1, y, pointEmpty);
        }

        for(x = 0; x < w + 2; ++x) {
            grid[0].Put(x, h + 1, pointInside);
            grid[1].Put(x, h + 1, pointEmpty);
        }

        grid[0].GenerateSDF();
        grid[1].GenerateSDF();

        for(y = 1; y <= h; y++) {
            for (x = 1; x <= w; x++) {
                double_t dist1 = sqrt((double)(grid[0].Get(x, y).f + 1));
                double_t dist2 = sqrt((double)(grid[1].Get(x, y).f + 1));
                double_t dist = dist1 - dist2;
                /// Clamp and scale
                int c = dist + 128;
                if (c < 0) c = 0;
                if (c > 255) c = 255;

                // if (transparent) {
                //     img->setPixel(x - 1, y - 1, qRgba(255, 255, 255, c));
                // }
                // else {
                //     img->setPixel(x - 1, y - 1, qRgb(c, c, c));
                // }
            }
        }

        free(grid[0].grid);
        free(grid[1].grid);

        return result;
    }
}
