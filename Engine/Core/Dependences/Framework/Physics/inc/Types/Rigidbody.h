//
// Created by Nikita on 16.03.2021.
//

#ifndef GAMEENGINE_RIGIDBODY_H
#define GAMEENGINE_RIGIDBODY_H

#include <EntityComponentSystem/Component.h>

namespace Framework::Physics::Types {
    class Rigidbody : public Helper::Component {
    public:
        Rigidbody();
    private:
        ~Rigidbody() override = default;

    public:
        static Helper::Component* LoadComponent(const Helper::MarshalDecodeNode& node, const Helper::Types::DataStorage* dataStorage) {
            return nullptr;
        }

    protected:
        void OnDestroyGameObject() override {
            delete this;
        }
        void OnRemoveComponent() override {
            OnRemoveComponent();
        }
    };
}

#endif //GAMEENGINE_RIGIDBODY_H
