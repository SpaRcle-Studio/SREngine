//
// Created by Monika on 05.10.2023.
//

#include <Libraries/Types/Behaviour.h>
#include <Libraries/Utils/Allocator.h>

#include <Libraries/Casts.h>
#include <Libraries/Debug.h>
#include <Libraries/Engine.h>
#include <Libraries/Text.h>
#include <Libraries/Window.h>

class CameraLoader : public Behaviour {
public:
    void Awake() override { auto&& pGameObject = scene->InstanceFromFile("Launcher/Prefabs/ui-camera.prefab"); }
};

REGISTER_BEHAVIOUR(CameraLoader)