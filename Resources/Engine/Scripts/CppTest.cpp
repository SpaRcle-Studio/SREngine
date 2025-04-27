//
// Created by Monika on 03.04.2025.
//

#include <Utils/Debug.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/SceneObject.h>

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

namespace SpaRcle::Scripts::Engine {
    class TestComponent : public SpaRcle::Utils::Component {
        SR_CLASS()
    public:


    };
}

extern "C" __declspec(dllexport) void TestFunction() {
    SR_UTILS_NS::Debug::Instance().ScriptLog("TestFunction() called!");
}