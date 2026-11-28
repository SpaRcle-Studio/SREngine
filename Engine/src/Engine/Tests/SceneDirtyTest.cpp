//
// Created by Monika on 28.11.2026.
//

#include <Engine/Tests/SceneDirtyTest.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>
#include <Utils/World/SceneUpdater.h>

#include <Codegen/SceneDirtyTest.generated.hpp>

namespace SR_CORE_NS::Tests {
    void SceneDirtyTestComponent::Awake() {
        ++m_awakeCount;
        Super::Awake();
    }

    void SceneDirtyTestComponent::Start() {
        ++m_startCount;
        Super::Start();
    }

    void SceneDirtyTestComponent::OnEnable() {
        ++m_enableCount;
        Super::OnEnable();
    }

    void SceneDirtyTestComponent::OnDisable() {
        ++m_disableCount;
        Super::OnDisable();
    }

    bool SceneDirtyTestComponent::IsAwake() const noexcept {
        ++m_visits;
        return Super::IsAwake();
    }

    SR_UTILS_NS::TestExecutionResult SceneDirtyTest::Run() {
        SR_TRACY_ZONE;

        bool success = true;

        success &= TestInitialBuild();
        success &= TestSiblingsNotVisited();
        success &= TestDisabledParent();
        success &= TestAddChildToCleanParent();
        success &= TestMoveFromDisabledParent();
        success &= TestDestroyChild();
        success &= TestUnpause();

        if (!success) {
            SR_ERROR("SceneDirtyTest::Run() : test failed!");
            return SR_UTILS_NS::TestExecutionResult::Error;
        }

        SR_LOG_TEST("SceneDirtyTest::Run() : all checks passed.");

        return SR_UTILS_NS::TestExecutionResult::Success;
    }

    bool SceneDirtyTest::TestInitialBuild() {
        auto&& pScene = CreateScene();
        auto&& pRoot = pScene->InstanceGameObject("Root");

        std::array<SR_HTYPES_NS::SharedPtr<SceneDirtyTestComponent>, 3> probes;
        for (auto&& pProbe : probes) {
            pProbe = AddProbe(pRoot->CreateChild("Child"));
        }

        Step(pScene);

        bool success = true;

        for (auto&& pProbe : probes) {
            if (!IsProbeRunning(pProbe) || pProbe->GetAwakeCount() != 1 || pProbe->GetStartCount() != 1 || pProbe->GetEnableCount() != 1) {
                SR_ERROR("SceneDirtyTest::TestInitialBuild() : component lifecycle is not completed once!");
                success = false;
            }
        }

        if (!IsTreeClean(*pRoot)) {
            SR_ERROR("SceneDirtyTest::TestInitialBuild() : objects are still dirty after build!");
            success = false;
        }

        DestroyScene(pScene);

        return success;
    }

    bool SceneDirtyTest::TestSiblingsNotVisited() {
        auto&& pScene = CreateScene();
        auto&& pRoot = pScene->InstanceGameObject("Root");

        std::array<SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject>, 3> children;
        std::array<SR_HTYPES_NS::SharedPtr<SceneDirtyTestComponent>, 3> probes;
        for (uint32_t i = 0; i < children.size(); ++i) {
            children[i] = pRoot->CreateChild("Child");
            probes[i] = AddProbe(children[i]);
        }

        Step(pScene);

        for (auto&& pProbe : probes) {
            pProbe->ResetVisits();
        }

        bool success = true;

        children[1]->SetEnabled(false);
        Step(pScene);

        if (probes[1]->GetDisableCount() != 1 || probes[1]->IsActive()) {
            SR_ERROR("SceneDirtyTest::TestSiblingsNotVisited() : disabled child is still active!");
            success = false;
        }

        children[1]->SetEnabled(true);
        Step(pScene);

        if (probes[1]->GetEnableCount() != 2 || !IsProbeRunning(probes[1])) {
            SR_ERROR("SceneDirtyTest::TestSiblingsNotVisited() : re-enabled child is not active!");
            success = false;
        }

        if (probes[0]->GetVisits() != 0 || probes[2]->GetVisits() != 0) {
            SR_ERROR("SceneDirtyTest::TestSiblingsNotVisited() : clean siblings were visited by build! Visits: {}, {}",
                probes[0]->GetVisits(), probes[2]->GetVisits());
            success = false;
        }

        if (!IsProbeRunning(probes[0]) || !IsProbeRunning(probes[2])) {
            SR_ERROR("SceneDirtyTest::TestSiblingsNotVisited() : siblings lost their state!");
            success = false;
        }

        if (!IsTreeClean(*pRoot)) {
            SR_ERROR("SceneDirtyTest::TestSiblingsNotVisited() : objects are still dirty after build!");
            success = false;
        }

        DestroyScene(pScene);

        return success;
    }

    bool SceneDirtyTest::TestDisabledParent() {
        auto&& pScene = CreateScene();
        auto&& pRoot = pScene->InstanceGameObject("Root");
        auto&& pParent = pRoot->CreateChild("Parent");
        auto&& pChild = pParent->CreateChild("Child");
        auto&& pProbe = AddProbe(pChild);

        Step(pScene);

        bool success = true;

        pParent->SetEnabled(false);
        Step(pScene);

        if (pProbe->GetDisableCount() != 1 || pProbe->IsActive() || pChild->IsActive()) {
            SR_ERROR("SceneDirtyTest::TestDisabledParent() : child of disabled parent is still active!");
            success = false;
        }

        /// Ребёнок выключенного родителя переключается, оставаясь неактивным
        pChild->SetEnabled(false);
        Step(pScene);
        pChild->SetEnabled(true);
        Step(pScene);

        if (pProbe->GetEnableCount() != 1 || pProbe->GetDisableCount() != 1 || pProbe->IsActive() || pChild->IsActive()) {
            SR_ERROR("SceneDirtyTest::TestDisabledParent() : child of disabled parent changed its activity!");
            success = false;
        }

        pParent->SetEnabled(true);
        Step(pScene);

        if (pProbe->GetEnableCount() != 2 || !IsProbeRunning(pProbe) || !pChild->IsActive()) {
            SR_ERROR("SceneDirtyTest::TestDisabledParent() : child is not active after parent is enabled!");
            success = false;
        }

        if (!IsTreeClean(*pRoot)) {
            SR_ERROR("SceneDirtyTest::TestDisabledParent() : objects are still dirty after build!");
            success = false;
        }

        DestroyScene(pScene);

        return success;
    }

    bool SceneDirtyTest::TestAddChildToCleanParent() {
        auto&& pScene = CreateScene();
        auto&& pRoot = pScene->InstanceGameObject("Root");

        std::array<SR_HTYPES_NS::SharedPtr<SceneDirtyTestComponent>, 2> probes;
        for (auto&& pProbe : probes) {
            pProbe = AddProbe(pRoot->CreateChild("Child"));
        }

        Step(pScene);

        for (auto&& pProbe : probes) {
            pProbe->ResetVisits();
        }

        auto&& pNewProbe = AddProbe(pRoot->CreateChild("NewChild"));
        Step(pScene);

        bool success = true;

        if (!IsProbeRunning(pNewProbe) || pNewProbe->GetAwakeCount() != 1 || pNewProbe->GetStartCount() != 1 || pNewProbe->GetEnableCount() != 1) {
            SR_ERROR("SceneDirtyTest::TestAddChildToCleanParent() : new child lifecycle is not completed once!");
            success = false;
        }

        for (auto&& pProbe : probes) {
            if (pProbe->GetVisits() != 0 || !IsProbeRunning(pProbe)) {
                SR_ERROR("SceneDirtyTest::TestAddChildToCleanParent() : existing child was visited or lost its state! Visits: {}", pProbe->GetVisits());
                success = false;
            }
        }

        if (!IsTreeClean(*pRoot)) {
            SR_ERROR("SceneDirtyTest::TestAddChildToCleanParent() : objects are still dirty after build!");
            success = false;
        }

        DestroyScene(pScene);

        return success;
    }

    bool SceneDirtyTest::TestMoveFromDisabledParent() {
        auto&& pScene = CreateScene();
        auto&& pRoot = pScene->InstanceGameObject("Root");
        auto&& pDisabledParent = pRoot->CreateChild("DisabledParent");
        auto&& pEnabledParent = pRoot->CreateChild("EnabledParent");
        auto&& pChild = pDisabledParent->CreateChild("Child");
        auto&& pProbe = AddProbe(pChild);

        pDisabledParent->SetEnabled(false);
        Step(pScene);

        bool success = true;

        if (pProbe->GetAwakeCount() != 0 || pProbe->IsActive()) {
            SR_ERROR("SceneDirtyTest::TestMoveFromDisabledParent() : child of disabled parent is awake or active!");
            success = false;
        }

        if (!pChild->MoveToTree(SR_UTILS_NS::StaticPointerCast<SR_UTILS_NS::SceneObject>(pEnabledParent))) {
            SR_ERROR("SceneDirtyTest::TestMoveFromDisabledParent() : failed to move child!");
            DestroyScene(pScene);
            return false;
        }

        Step(pScene);

        if (!IsProbeRunning(pProbe) || pProbe->GetAwakeCount() != 1 || pProbe->GetStartCount() != 1 || pProbe->GetEnableCount() != 1) {
            SR_ERROR("SceneDirtyTest::TestMoveFromDisabledParent() : moved child lifecycle is not completed once!");
            success = false;
        }

        if (!IsTreeClean(*pRoot)) {
            SR_ERROR("SceneDirtyTest::TestMoveFromDisabledParent() : objects are still dirty after build!");
            success = false;
        }

        DestroyScene(pScene);

        return success;
    }

    bool SceneDirtyTest::TestDestroyChild() {
        auto&& pScene = CreateScene();
        auto&& pRoot = pScene->InstanceGameObject("Root");

        std::array<SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject>, 3> children;
        std::array<SR_HTYPES_NS::SharedPtr<SceneDirtyTestComponent>, 3> probes;
        for (uint32_t i = 0; i < children.size(); ++i) {
            children[i] = pRoot->CreateChild("Child");
            probes[i] = AddProbe(children[i]);
        }

        Step(pScene);

        children[1]->Destroy();
        Step(pScene);

        bool success = true;

        if (pRoot->GetChildrenRef().size() != 2) {
            SR_ERROR("SceneDirtyTest::TestDestroyChild() : destroyed child is still in hierarchy! Children: {}", pRoot->GetChildrenRef().size());
            success = false;
        }

        if (!IsProbeRunning(probes[0]) || !IsProbeRunning(probes[2])) {
            SR_ERROR("SceneDirtyTest::TestDestroyChild() : siblings lost their state!");
            success = false;
        }

        if (!IsTreeClean(*pRoot)) {
            SR_ERROR("SceneDirtyTest::TestDestroyChild() : objects are still dirty after build!");
            success = false;
        }

        DestroyScene(pScene);

        return success;
    }

    bool SceneDirtyTest::TestUnpause() {
        auto&& pScene = CreateScene();
        auto&& pRoot = pScene->InstanceGameObject("Root");

        Step(pScene);

        auto&& pProbe = AddProbe(pRoot->CreateChild("Child"), false);

        Step(pScene, true);
        Step(pScene, true);

        bool success = true;

        if (pProbe->GetAwakeCount() != 0 || pProbe->IsActive()) {
            SR_ERROR("SceneDirtyTest::TestUnpause() : component without ExecuteInEditMode is awake on pause!");
            success = false;
        }

        Step(pScene, false);

        if (!IsProbeRunning(pProbe) || pProbe->GetAwakeCount() != 1 || pProbe->GetStartCount() != 1 || pProbe->GetEnableCount() != 1) {
            SR_ERROR("SceneDirtyTest::TestUnpause() : component lifecycle is not completed after unpause!");
            success = false;
        }

        if (!IsTreeClean(*pRoot)) {
            SR_ERROR("SceneDirtyTest::TestUnpause() : objects are still dirty after build!");
            success = false;
        }

        DestroyScene(pScene);

        return success;
    }

    SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene> SceneDirtyTest::CreateScene() {
        /// SceneAllocator настраивает приложение, а тесты идут до него
        SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene> pScene = new SR_WORLD_NS::Scene();
        pScene->Init();
        return pScene;
    }

    void SceneDirtyTest::DestroyScene(SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>& pScene) {
        pScene.AutoFree([](SR_WORLD_NS::Scene* pRawScene, SR_HTYPES_NS::SharedPtrDynamicData* pControl) {
            pRawScene->Destroy();
            pControl->deleter(static_cast<void*>(pRawScene));
        });
    }

    void SceneDirtyTest::Step(const SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>& pScene, bool isPaused) {
        pScene->Prepare();
        pScene->GetSceneUpdater()->Build(isPaused);
    }

    SR_HTYPES_NS::SharedPtr<SceneDirtyTestComponent> SceneDirtyTest::AddProbe(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject>& pObject, bool executeInEditMode) {
        auto&& pProbe = pObject->AddComponent<SceneDirtyTestComponent>();
        if (pProbe) {
            pProbe->SetExecuteInEditMode(executeInEditMode);
        }
        return pProbe;
    }

    bool SceneDirtyTest::IsProbeRunning(const SR_HTYPES_NS::SharedPtr<SceneDirtyTestComponent>& pProbe) {
        /// Без IsAwake(): он считается посещением
        return pProbe && pProbe->GetAwakeCount() > 0 && pProbe->IsStarted() && pProbe->IsActive();
    }

    bool SceneDirtyTest::IsTreeClean(const SR_UTILS_NS::SceneObject& object) {
        if (object.IsDirty()) {
            return false;
        }

        for (auto&& pChild : object.GetChildrenRef()) {
            if (!IsTreeClean(*pChild)) {
                return false;
            }
        }

        return true;
    }
}
