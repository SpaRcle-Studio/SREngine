//
// Created by Monika on 03.04.2025.
//

#include <Utils/Debug.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/SceneObject.h>
#include <Utils/Types/RawMesh.h>

#include <Scripting/Cpp/CppBehaviour.h>

#include <Enum/SceneObjectType.hpp>

namespace SpaRcle::Scripts::SREngine {
    class TestBehaviour : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
        SR_NODISCARD bool ExecuteInEditMode() const noexcept override { return true; }

    public:
        void Update(float_t dt) override {
            if (deltaTime > 0.f) {
                deltaTime -= dt;
                return;
            }
            deltaTime = logInterval;
            SR_DEBUG_LOG("TestBehaviour::Update() : dt log 2 = {}", dt);
        }

    private:
        /// @property
        int privateInt = 0;
        /// @property
        int privateInt2 = 0;
        /// @property
        int privateInt32 = 0;

        /// @property @readOnly @dontSave
        float_t deltaTime = 0.f;
        /// @property
        float_t logInterval = 1.f;

    };
}

#include <Codegen/CppTest.generated.hpp>
