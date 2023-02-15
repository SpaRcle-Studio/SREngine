//
// Created by Monika on 25.12.2022.
//

#ifndef SRENGINE_SCENEINITIALIZER_H
#define SRENGINE_SCENEINITIALIZER_H

#include <Utils/World/SceneBuilder.h>
#include <Utils/World/Scene.h>
#include <Core/Engine.h>

#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderTechnique.h>

#include <Physics/PhysicsScene.h>

namespace SR_CORE_NS {
    static bool DeInitializeScene(SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>& scene, Engine* pEngine) {
        auto&& renderScene = scene->GetDataStorage().GetValue<SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene>>();
        auto&& physicsScene = scene->GetDataStorage().GetValue<SR_HTYPES_NS::SafePtr<SR_PHYSICS_NS::PhysicsScene>>();

        renderScene.Do([pEngine](SR_GRAPH_NS::RenderScene* ptr) {
            ptr->Remove(pEngine->GetEditor());
            ptr->Remove(&Graphics::GUI::GlobalWidgetManager::Instance());
        });

        scene.AutoFree([](SR_WORLD_NS::Scene* pScene) {
            pScene->Destroy();
            delete pScene;
        });

        physicsScene.AutoFree([](SR_PHYSICS_NS::PhysicsScene* pPhysicsScene) {
            delete pPhysicsScene;
        });

        return true;
    }

    static bool InitializeScene(SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>& scene, Engine* pEngine) {
        SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene> renderScene;
        SR_HTYPES_NS::SafePtr<SR_PHYSICS_NS::PhysicsScene> physicsScene;

        if (SR_UTILS_NS::Features::Instance().Enabled("Renderer", true)) {
            if (auto&& pContext = pEngine->GetRenderContext(); pContext.LockIfValid()) {
                renderScene = pContext->CreateScene(scene);
                pContext.Unlock();
            }
            else {
                SR_ERROR("InitializeScene() : failed to get window context!");
                return false;
            }

            if (renderScene) {
                renderScene->SetTechnique("Editor/Configs/OverlayRenderTechnique.xml");

                renderScene->Register(pEngine->GetEditor());
                renderScene->Register(&Graphics::GUI::GlobalWidgetManager::Instance());

                renderScene->SetOverlayEnabled(pEngine->GetEditor()->Enabled());
            }
        }

        if (SR_UTILS_NS::Features::Instance().Enabled("Physics", true)) {
            physicsScene = new SR_PHYSICS_NS::PhysicsScene(scene);

            if (!physicsScene->Init()) {
                SR_ERROR("InitializeScene() : failed to initialize physics scene!");
                return false;
            }
        }

        scene->GetDataStorage().SetValue(renderScene);
        scene->GetDataStorage().SetValue(physicsScene);

        return true;
    }
}

#endif //SRENGINE_SCENEINITIALIZER_H
