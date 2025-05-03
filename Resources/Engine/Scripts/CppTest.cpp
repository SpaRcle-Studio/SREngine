//
// Created by Monika on 03.04.2025.
//

#include <Utils/Debug.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/SceneObject.h>
#include <Utils/Types/RawMesh.h>

#include <Scripting/Cpp/CppBehaviour.h>

#include <Enum/SceneObjectType.hpp>

//#include <string>
//
//#include <SpaRcle/Utils/Debug.h>
//
//namespace Core {
//    /// @behaviour
//    class TestBehaviour {
//
//    private:
//        /// @property
//        std::string m_name;
//
//    };
//}



namespace SpaRcle::Scripts::SREngine {
    class ScriptTestComponent : public SpaRcle::Utils::Component {
        SR_CLASS()
    public:
    };

    class TestBehaviour : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()

        /// @property
        int privateInt = 0;
    };
}

extern "C" SR_DLL_API_EXPORT void TestFunction() {
    SR_UTILS_NS::Debug::Instance().ScriptLog("TestFunction() called!");
    SR_UTILS_NS::Debug::Instance().ScriptLog("Enum value: {}"_format(SR_UTILS_NS::SceneObjectType::GameObject));
    SR_UTILS_NS::Debug::Instance().ScriptLog("Enum value: {}"_format(2));
    SR_UTILS_NS::Debug::Instance().ScriptLog("Enum value: " + SR_UTILS_NS::EnumReflector::ToStringAtom(SR_UTILS_NS::SceneObjectType::GameObject).ToStringRef());
}

#include <Codegen/CppTest.generated.hpp>
