//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_SREVOSCRIPT_H
#define GAMEENGINE_SREVOSCRIPT_H

#include "Base/Script.h"

#include <ResourceManager/ResourceManager.h>
#include <EvoScript/Script.h>

namespace Framework::Scripting {
    class Compiler;

    class EvoScriptImpl : public Scripting::Script {
    public:
        EvoScriptImpl(Compiler* compiler, const std::string& name, const std::string& path)
            : Script(compiler, name, Helper::ResourceManager::Instance().GetResourcesFolder() + "/Scripts/" + path) { }
        ~EvoScriptImpl() override = default;
        EvoScriptImpl(const EvoScriptImpl&) = delete;
    public:
        void ForcedFree() override {
            delete this;
        }
        bool AwaitDestroy() override;
        bool Compile() override;
        bool DelayedDestroyAndFree() override;
    private:
        EvoScript::Script* m_script = nullptr;
    public:
        void Awake() override;
        void Start() override;
        void Close() override;
        void Update() override;
        void FixedUpdate() override;
        void OnGUI() override;
    };
}

#endif //GAMEENGINE_SREVOSCRIPT_H
