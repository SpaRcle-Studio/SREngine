//
// Created by Monika on 02.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_SCRIPT_SYSTEM_H
#define SR_ENGINE_SCRIPTING_CPP_SCRIPT_SYSTEM_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_SCRIPTING_NS {
    class ScriptSystem : public SR_HTYPES_NS::SharedPtr<ScriptSystem> {
        using Super = SR_HTYPES_NS::SharedPtr<ScriptSystem>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ScriptSystem>;
        enum class Mode : uint8_t { Dynamic, Static, Mixed };

    public:
        ScriptSystem()
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        { }

    private:
        void OnFileChanged(const SR_UTILS_NS::Path& path) {
            // Handle file changes
        }

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_SCRIPT_SYSTEM_H
