//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_SREVOSCRIPT_H
#define GAMEENGINE_SREVOSCRIPT_H

#include <Base/Script.h>

#include <ResourceManager/ResourceManager.h>
#include <EvoScript/Script.h>

namespace Framework::Scripting {
    class Compiler;

    class EvoScriptImpl : public Scripting::Script {
    public:
        EvoScriptImpl(Compiler* compiler, const std::string& name, const Helper::Path& path)
            : Script(compiler, name, path.ToString())
        { }

        EvoScriptImpl(const EvoScriptImpl&) = delete;
        ~EvoScriptImpl() override = default;

    public:
        void ForcedFree() override {
            delete this;
        }
        bool AwaitDestroy() override;
        bool Compile() override;
        bool DelayedDestroyAndFree() override;

    public:
        void Awake() override;
        void Start() override;
        void Close() override;
        void Update() override;
        void FixedUpdate() override;
        void OnGUI() override;

    private:
        EvoScript::Script* m_script = nullptr;

    };
}

#endif //GAMEENGINE_SREVOSCRIPT_H
