//
// Created by Nikita on 13.12.2020.
//

#ifndef GAMEENGINE_AREALIGHT_H
#define GAMEENGINE_AREALIGHT_H

#include <Graphics/Lighting/ILightComponent.h>

namespace SR_GRAPH_NS {
    class AreaLight : public ILightComponent {
    protected:
        float_t m_radius = 1.f;
        float_t m_distance = 10.f;

    };
}

#endif //GAMEENGINE_AREALIGHT_H
