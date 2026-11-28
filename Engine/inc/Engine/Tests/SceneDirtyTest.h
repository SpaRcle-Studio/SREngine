//
// Created by Monika on 28.11.2026.
//

#ifndef SR_ENGINE_TESTS_SCENE_DIRTY_TEST_H
#define SR_ENGINE_TESTS_SCENE_DIRTY_TEST_H

#include <Engine/stdInclude.h>

#include <Utils/Tests/TestManager.h>
#include <Utils/ECS/Component.h>

namespace SR_UTILS_NS {
    class GameObject;
    class SceneObject;
}

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_CORE_NS::Tests {
    /// Считает вызовы жизненного цикла. IsAwake() зовут циклы Awake/CheckActivity/Start объекта -
    /// по числу его вызовов видно, обошёл ли SceneUpdater::Build объект
    class SceneDirtyTestComponent final : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void Awake() override;
        void Start() override;
        void OnEnable() override;
        void OnDisable() override;

        SR_NODISCARD bool IsAwake() const noexcept override;
        SR_NODISCARD bool ExecuteInEditMode() const override { return m_executeInEditMode; }

        void SetExecuteInEditMode(bool value) { m_executeInEditMode = value; }
        void ResetVisits() { m_visits = 0; }

        SR_NODISCARD uint32_t GetAwakeCount() const { return m_awakeCount; }
        SR_NODISCARD uint32_t GetStartCount() const { return m_startCount; }
        SR_NODISCARD uint32_t GetEnableCount() const { return m_enableCount; }
        SR_NODISCARD uint32_t GetDisableCount() const { return m_disableCount; }
        SR_NODISCARD uint32_t GetVisits() const { return m_visits; }

    private:
        uint32_t m_awakeCount = 0;
        uint32_t m_startCount = 0;
        uint32_t m_enableCount = 0;
        uint32_t m_disableCount = 0;
        mutable uint32_t m_visits = 0;
        bool m_executeInEditMode = true;

    };

    /// Флаги грязности сцены (SceneObject::m_hasDirtyChildren) и фазы SceneUpdater::Build
    class SceneDirtyTest : public SR_UTILS_NS::ITestController {
        SR_CLASS()
    public:
        SR_UTILS_NS::TestExecutionResult Run() override;

    private:
        SR_NODISCARD bool TestInitialBuild();
        SR_NODISCARD bool TestSiblingsNotVisited();
        SR_NODISCARD bool TestDisabledParent();
        SR_NODISCARD bool TestAddChildToCleanParent();
        SR_NODISCARD bool TestMoveFromDisabledParent();
        SR_NODISCARD bool TestDestroyChild();
        SR_NODISCARD bool TestUnpause();

        SR_NODISCARD static SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene> CreateScene();
        static void DestroyScene(SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>& pScene);
        static void Step(const SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>& pScene, bool isPaused = false);
        SR_NODISCARD static SR_HTYPES_NS::SharedPtr<SceneDirtyTestComponent> AddProbe(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject>& pObject, bool executeInEditMode = true);
        SR_NODISCARD static bool IsProbeRunning(const SR_HTYPES_NS::SharedPtr<SceneDirtyTestComponent>& pProbe);
        SR_NODISCARD static bool IsTreeClean(const SR_UTILS_NS::SceneObject& object);

    };
}

#endif //SR_ENGINE_TESTS_SCENE_DIRTY_TEST_H
