//
// Created by Monika on 05.10.2023.
//

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>

#include <Libraries/Debug.h>
#include <Libraries/Text.h>
#include <Libraries/Window.h>
#include <Libraries/Engine.h>
#include <Libraries/Casts.h>

class CharacterLoader : public Behaviour {
public:
    void Awake() override {
        auto&& pGameObject = scene->InstanceFromFile("Samples/CapsuleCharacter.prefab");
        if (auto&& pTransform = pGameObject->GetTransform()) {
            pTransform->SetTranslation({0.f, 5.f, 0.f});
        }
    }
};

REGISTER_BEHAVIOUR(CharacterLoader)