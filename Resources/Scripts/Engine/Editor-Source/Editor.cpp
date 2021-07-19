//
// Created by Nikita on 19.07.2021.
//

#include "../../Libraries/Debug.h"
#include "../../Libraries/GUISystem.h"
#include "../../Libraries/Camera.h"
#include "../../Libraries/Engine.h"
#include "../../Libraries/Scene.h"

GUISystem* gui = nullptr;
Camera* camera = nullptr;

EXTERN void Start() {
    gui = GUISystem::Get();
}

EXTERN void OnGUI() {
    gui->BeginDockSpace();

    if (auto scene = Engine::Get()->GetScene(); scene) {
        if (gui->BeginWindow("Scene")) {
            if (!camera) {
                if (auto gm = scene->FindByComponent("Camera"); gm)
                    camera = (Camera*)gm->GetComponent("Camera");
            } else {

            }

            gui->EndWindow();
        }
    }

    if (gui->BeginWindow("Inspector")) {
        gui->EndWindow();
    }

    if (gui->BeginWindow("Hierarchy")) {
        gui->EndWindow();
    }

    if (gui->BeginWindow("Assets")) {
        gui->EndWindow();
    }
}

EXTERN void Close() {

}