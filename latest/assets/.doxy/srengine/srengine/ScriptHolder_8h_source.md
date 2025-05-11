

# File ScriptHolder.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**ScriptHolder.h**](ScriptHolder_8h.md)

[Go to the documentation of this file](ScriptHolder_8h.md)


```C++
//
// Created by Monika on 04.03.2023.
//

#ifndef SR_ENGINE_SCRIPTING_SCRIPT_HOLDER_H
#define SR_ENGINE_SCRIPTING_SCRIPT_HOLDER_H

#include <Utils/Types/SafePointer.h>
#include <Utils/Common/NonCopyable.h>

namespace SR_SCRIPTING_NS {
    class ScriptHolder : public SR_HTYPES_NS::SharedPtr<ScriptHolder>, public SR_UTILS_NS::NonCopyable {
        using Super = SR_HTYPES_NS::SharedPtr<ScriptHolder>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ScriptHolder>;

    public:
        explicit ScriptHolder(void* pScriptImpl)
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Manually)
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

#endif //SR_ENGINE_SCRIPTING_SCRIPT_HOLDER_H
```


