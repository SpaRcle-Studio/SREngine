//
// Created by innerviewer on 2/28/2023.
//

#ifndef SRENGINE_VEHICLE4W3D_H
#define SRENGINE_VEHICLE4W3D_H

#include <Physics/Vehicle.h>

namespace SR_PTYPES_NS {
    class Vehicle4W3D : public Vehicle {
        using Super = Vehicle;
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Vehicle4W3D);
    public:
        explicit Vehicle4W3D(LibraryPtr pLibrary);
        ~Vehicle4W3D() override = default;
    public:

    };
}

#endif //SRENGINE_VEHICLE4W3D_H
