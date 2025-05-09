

# File ScriptHolder.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Old**](dir_7c26f9091b44a892879dd4e8d1d7c144.md) **>** [**ScriptHolder.h**](ScriptHolder_8h.md)

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


