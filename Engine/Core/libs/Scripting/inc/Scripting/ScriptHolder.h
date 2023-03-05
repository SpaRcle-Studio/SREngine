//
// Created by Monika on 04.03.2023.
//

#ifndef SRENGINE_SCRIPTHOLDER_H
#define SRENGINE_SCRIPTHOLDER_H

#include <Utils/Types/SafePointer.h>
#include <Utils/Common/NonCopyable.h>

namespace SR_SCRIPTING_NS {
    class ScriptHolder : public SR_HTYPES_NS::SafePtr<ScriptHolder>, public SR_UTILS_NS::NonCopyable {
    public:
        using Ptr = SR_HTYPES_NS::SafePtr<ScriptHolder>;

    public:
        explicit ScriptHolder(void* pScriptImpl)
            : SR_HTYPES_NS::SafePtr<ScriptHolder>(this)
            , m_scriptImpl(pScriptImpl)
        { }

        ~ScriptHolder() override {
            SRAssert(!m_scriptImpl);
        }

    public:
        void SetScript(void* pScriptImpl) {
            m_scriptImpl = pScriptImpl;
        }

        template<typename T> SR_NODISCARD T* GetScript() const {
            return reinterpret_cast<T*>(m_scriptImpl);
        }

    private:
        void* m_scriptImpl = nullptr;

    };
}

#endif //SRENGINE_SCRIPTHOLDER_H
