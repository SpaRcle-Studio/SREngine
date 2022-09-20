//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_BOXCOLLIDER3D_H
#define SRENGINE_BOXCOLLIDER3D_H

#include <Physics/Base/Collider.h>

namespace SR_PHYSICS_NS::Types {
    class BoxCollider3D : public Collider {
    SR_ENTITY_SET_VERSION(1000);
    public:
        BoxCollider3D();
        ~BoxCollider3D() override = default;

    public:
        static ComponentPtr LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    };
}

#endif //SRENGINE_BOXCOLLIDER3D_H
