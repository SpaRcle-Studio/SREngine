//
// Created by Nikita on 16.03.2021.
//

#ifndef GAMEENGINE_RIGIDBODY_H
#define GAMEENGINE_RIGIDBODY_H

#include <EntityComponentSystem/Component.h>
#include <Debug.h>

using namespace Framework::Helper;

namespace Framework::Physics::Types {
    class Rigidbody : public Component {
    public:
        Rigidbody();
    private:
        ~Rigidbody() override = default;

    public:
        static Component* LoadComponent(const Xml::Node& xml, const Helper::Types::DataStorage* dataStorage) {
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
