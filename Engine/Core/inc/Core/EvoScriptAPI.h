//
// Created by Nikita on 11.07.2021.
//

#ifndef SR_ENGINE_EVOSCRIPTAPI_H
#define SR_ENGINE_EVOSCRIPTAPI_H

#include <Scripting/Impl/EvoCompiler.h>

namespace EvoScript {
    class AddressTableGen;
}

namespace SR_CORE_NS {
    class Engine;
}

namespace SpaRcle {
    class API {
    public:
        API() = delete;
        API(const API &) = delete;
        ~API() = delete;
    public:
        static void RegisterEvoScriptClasses(SR_CORE_NS::Engine* pEngine);
        static void Initialize();
        static void RegisterDebug(EvoScript::AddressTableGen* generator);
        static void RegisterRaycast(EvoScript::AddressTableGen* generator);
        static void RegisterEngine(EvoScript::AddressTableGen* generator);
        static void RegisterScene(EvoScript::AddressTableGen* generator);
        static void RegisterComponent(EvoScript::AddressTableGen* generator);
        static void RegisterMesh(EvoScript::AddressTableGen* generator);
        static void RegisterProceduralMesh(EvoScript::AddressTableGen* generator);
        static void RegisterResourceManager(EvoScript::AddressTableGen* generator);
        static void RegisterGameObject(EvoScript::AddressTableGen* generator);
        static void RegisterCamera(EvoScript::AddressTableGen* generator);
        static void RegisterRigidbody(EvoScript::AddressTableGen* generator);
        static void RegisterButton(EvoScript::AddressTableGen* generator);
        static void RegisterRender(EvoScript::AddressTableGen* generator);
        static void RegisterUtils(EvoScript::AddressTableGen* generator);
        static void RegisterWindow(EvoScript::AddressTableGen* generator);
        static void RegisterShader(EvoScript::AddressTableGen* generator);
        static void RegisterTransform(EvoScript::AddressTableGen* generator);
        static void RegisterInput(EvoScript::AddressTableGen* generator);
        static void RegisterSkybox(EvoScript::AddressTableGen* generator);
        static void RegisterTexture(EvoScript::AddressTableGen* generator);
        static void RegisterMaterial(EvoScript::AddressTableGen* generator);
        static void RegisterGUISystem(EvoScript::AddressTableGen* generator);
        static void RegisterPostProcessing(EvoScript::AddressTableGen* generator);
        static void RegisterISavable(EvoScript::AddressTableGen* generator);
        static void RegisterBehaviour(EvoScript::AddressTableGen* generator);
        static void RegisterObserver(EvoScript::AddressTableGen* generator);
        static void RegisterMath(EvoScript::AddressTableGen* generator);
        static void RegisterText(EvoScript::AddressTableGen* generator);
        static void RegisterAnimator(EvoScript::AddressTableGen* generator);
        static void RegisterAudioSource(EvoScript::AddressTableGen* generator);

        static void RegisterCasts(EvoScript::CastingGen* generator);
    };
}

#endif //SR_ENGINE_EVOSCRIPTAPI_H
