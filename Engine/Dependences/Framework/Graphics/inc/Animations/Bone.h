//
// Created by Monika on 19.08.2021.
//

#ifndef GAMEENGINE_BONE_H
#define GAMEENGINE_BONE_H

#include <EntityComponentSystem/Component.h>
#include <Debug.h>

namespace Framework::Graphics::Animations {
    class Bone : Helper::Component {
    public:
        Bone() : Component("Bone") {

        }
    private:
        ~Bone() = default;
    public:
        void OnDestroyGameObject() noexcept override {
            delete this;
        }
        void OnRemoveComponent() noexcept override {
            OnDestroyGameObject();
        }
    };
}

#endif //GAMEENGINE_BONE_H
