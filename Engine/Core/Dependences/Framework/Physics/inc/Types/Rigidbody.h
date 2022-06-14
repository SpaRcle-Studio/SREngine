//
// Created by Nikita on 16.03.2021.
//

#ifndef GAMEENGINE_RIGIDBODY_H
#define GAMEENGINE_RIGIDBODY_H

#include <Utils/ECS/Component.h>

namespace Framework::Physics::Types {
    class Rigidbody : public SR_UTILS_NS::Component {
    public:
        Rigidbody();
    private:
        ~Rigidbody() override = default;

    public:
        static SR_UTILS_NS::Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
            return nullptr;
        }

    protected:
        void OnDestroy() override {
            delete this;
        }
    };
}

#endif //GAMEENGINE_RIGIDBODY_H
