//
// Created by Nikita on 19.07.2021.
//

#include "../../Libraries/Debug.h"
#include "../../Libraries/GUISystem.h"
#include "../../Libraries/Camera.h"
#include "../../Libraries/Engine.h"
#include "../../Libraries/Scene.h"

#include "../../Libraries/Types/SafePointer.h"

GUISystem* gui = nullptr;
Window* window = nullptr;
Camera* camera = nullptr;

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

    if (SafePtr<Scene> scene = Engine::Get()->GetScene(); scene.Valid()) {
        if (gui->BeginWindow("Scene")) {
            if (completeTexID < 0) {
                if (SafePtr<GameObject> gm = scene->FindByComponent("Camera"); gm.Valid()) {
                    camera = (Camera *)gm->GetComponent("Camera");
                    completeTexID = camera->GetPostProcessing()->GetFinally();
                }
            } else
                if (camera->IsReady() && gui->BeginChildWindow("Texture")) {
                    auto winSize = gui->GetWindowSize();
                    gui->DrawTexture(winSize, window->GetWindowSize(), completeTexID, true);

                    if (camera)
                        gui->DrawGuizmo(camera, scene->GetSelected());

                    gui->DrawGuizmoTools();

                    gui->EndChildWindow();
                }

            gui->EndWindow();
        }
    }

    if (gui->BeginWindow("Inspector")) {
        gui->DrawInspector(Engine::Get()->GetScene());
        gui->EndWindow();
    }

    if (gui->BeginWindow("Hierarchy")) {
        gui->DrawHierarchy(Engine::Get()->GetScene());
        gui->EndWindow();
    }

    if (gui->BeginWindow("Assets")) {
        gui->EndWindow();
    }
}

EXTERN void Close() {

}