//
// Created by Nikita on 11.07.2021.
//

#ifndef GAMEENGINE_SREVOSCRIPT_H
#define GAMEENGINE_SREVOSCRIPT_H

#include <Scripting/Base/Script.h>
#include <EvoScript/Script.h>
#include <FileSystem/Path.h>

namespace SR_SCRIPTING_NS {
    class Compiler;

    class EvoScriptImpl : public Script {
        using Super = Script;
    public:
        EvoScriptImpl(Compiler* compiler, const std::string& name, const SR_UTILS_NS::Path& path)
            : Super(compiler, name, path.ToString())
        { }

        ~EvoScriptImpl() override = default;

    public:
        bool Compile() override;

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
