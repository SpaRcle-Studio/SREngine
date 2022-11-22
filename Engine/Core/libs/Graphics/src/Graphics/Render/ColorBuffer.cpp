//
// Created by Monika on 09.09.2021.
//

#include <Graphics/Render/ColorBuffer.h>

size_t Framework::Graphics::ColorBuffer::GetSelectColorObject(glm::u8vec3 pixel) noexcept  {
    if (pixel != glm::u8vec3(0,0,0))
        for (int i = 0; i < next; i++) {
            if (CheckColor(Names[i].Color, pixel))
                return Names[i].Name;
        }
    #undef max
    return std::numeric_limits<size_t>::max();
}
