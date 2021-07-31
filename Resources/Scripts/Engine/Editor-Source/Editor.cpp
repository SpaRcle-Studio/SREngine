//
// Created by Nikita on 19.07.2021.
//

#include "../../Libraries/Debug.h"
#include "../../Libraries/GUISystem.h"
#include "../../Libraries/Camera.h"
#include "../../Libraries/Engine.h"
#include "../../Libraries/Scene.h"

GUISystem* gui = nullptr;
Window* window = nullptr;

int32_t geometryTexID = -1;
int32_t skyboxTexID   = -1;
int32_t completeTexID = -1;

EXTERN void Start() {
    gui = GUISystem::Get();
    Engine* engine = Engine::Get();
    window = engine->GetWindow();
}

EXTERN void OnGUI() {
    gui->BeginDockSpace();

    if (auto scene = Engine::Get()->GetScene(); scene) {
        if (gui->BeginWindow("Scene")) {
            if (completeTexID < 0) {
                if (auto gm = scene->FindByComponent("Camera"); gm) {
                    Camera *camera = (Camera *)gm->GetComponent("Camera");
                    completeTexID = camera->GetPostProcessing()->GetFinally();
                }
            } else
                if (gui->BeginChildWindow("Texture")) {
                    auto winSize = gui->GetWindowSize();
                    gui->DrawTexture(winSize, window->GetWindowSize(), completeTexID, true);
                    gui->EndChildWindow();
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