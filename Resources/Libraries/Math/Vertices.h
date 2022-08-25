//
// Created by Monika on 24.08.2022.
//

#ifndef EVOSCRIPTLIB_VERTICES_H
#define EVOSCRIPTLIB_VERTICES_H

#include "Math.h"

struct StaticMeshVertex {
    float pos[3];
    float uv[2];
    float norm[3];
    float tang[3];
    float bitang[3];
};

#endif //EVOSCRIPTLIB_VERTICES_H
