//
// Created by Nikita on 16.03.2021.
//

#ifndef GAMEENGINE_RIGIDBODY_H
#define GAMEENGINE_RIGIDBODY_H

#include <ECS/Component.h>

namespace Framework::Physics::Types {
    class Rigidbody : public Helper::Component {
    public:
        Rigidbody();
    private:
        ~Rigidbody() override = default;

    public:
        static Helper::Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
            return nullptr;
        }

    protected:
        void OnDestroy() override {
            delete this;
        }
    };
}

#endif //GAMEENGINE_RIGIDBODY_H
