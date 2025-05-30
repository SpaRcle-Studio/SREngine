//
// Created by Monika on 04.03.2023.
//

#ifndef SR_ENGINE_SCRIPTING_SCRIPT_HOLDER_H
#define SR_ENGINE_SCRIPTING_SCRIPT_HOLDER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/SafePointer.h>

namespace SR_SCRIPTING_NS {
    class ScriptHolder : public SR_HTYPES_NS::SharedPtr<ScriptHolder>, public SR_UTILS_NS::NonCopyable {
        using Super = SR_HTYPES_NS::SharedPtr<ScriptHolder>;

    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ScriptHolder>;

    public:
        explicit ScriptHolder(void* pScriptImpl)
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Manually), m_scriptImpl(pScriptImpl) {}

        ~ScriptHolder() override { SRAssert(!m_scriptImpl); }

    public:
        void SetScript(void* pScriptImpl) { m_scriptImpl = pScriptImpl; }

        template<typename T> SR_NODISCARD T* GetScript() const { return reinterpret_cast<T*>(m_scriptImpl); }

    private:
        void* m_scriptImpl = nullptr;
    };
} // namespace SR_SCRIPTING_NS

#endif // SR_ENGINE_SCRIPTING_SCRIPT_HOLDER_H
