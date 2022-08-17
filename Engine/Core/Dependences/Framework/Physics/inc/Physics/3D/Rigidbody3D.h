//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_RIGIDBODY3D_H
#define SRENGINE_RIGIDBODY3D_H

#include <Physics/Base/Rigidbody.h>

namespace SR_PHYSICS_NS::Types {
    class Rigidbody3D : public Rigidbody {
        SR_ENTITY_SET_VERSION(1000);
    public:
        Rigidbody3D();
        ~Rigidbody3D() override = default;

    public:
        static ComponentPtr LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    protected:
        void OnAttached() override;

    private:


    };
}

#endif //SRENGINE_RIGIDBODY3D_H
