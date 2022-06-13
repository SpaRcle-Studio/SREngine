//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Impl/EvoBehaviour.h>

namespace SR_SCRIPTING_NS {
    bool EvoBehaviour::Load() {
        SR_SCOPED_LOCK

        if (m_script) {
            SR_ERROR("EvoBehaviour::Load() : script already loaded!");
            return false;
        }

        auto&& path = GetResourceId();

        if (!path.empty()) {
            auto&& compiler = GlobalEvoCompiler::Instance();

            m_script = EvoScript::Script::Allocate(path, compiler.GetGenerator()->GetAddresses());

            auto&& fullPath = GetAssociatedPath().Concat(path);
            if (!m_script || !m_script->Load(fullPath, compiler, true)) {
                SR_ERROR("EvoBehaviour::Load() : failed to load script! \n\tPath: " + path);
                return false;
            }
        }

        return Behaviour::Load();
    }

    bool EvoBehaviour::Unload() {
        SR_SCOPED_LOCK

        bool hasErrors = !Behaviour::Unload();

        if (m_script) {
            m_script->Destroy();
            delete m_script;
            m_script = nullptr;
        }

        return !hasErrors;
    }

    uint64_t EvoBehaviour::GetFileHash() const {
        auto&& path = SR_UTILS_NS::Path(GetResourcePath());

        if (!path.IsAbs()) {
            path = GetAssociatedPath().Concat(path);
        }

        if (path.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            if (auto&& hash = path.GetFolderHash(); hash != SR_UINT64_MAX) {
                return hash;
            }
        }

        SRHalt("Failed to get behaviour hash! \n\tResource id: " + GetResourceId() +
               "\n\tResource path: " + path.ToString());

        return 0;
    }
}