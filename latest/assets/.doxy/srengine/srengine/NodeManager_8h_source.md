

# File NodeManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**NodeManager.h**](NodeManager_8h.md)

[Go to the documentation of this file](NodeManager_8h.md)


```C++
//
// Created by Monika on 16.01.2022.
//

#ifndef SR_ENGINE_NODEMANAGER_H
#define SR_ENGINE_NODEMANAGER_H

#include <Graphics/macros.h>

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Thread.h>

namespace SR_GRAPH_NS::GUI {
    class NodeManager : public SR_UTILS_NS::Singleton<NodeManager> {
        SR_REGISTER_SINGLETON(NodeManager)
    public:
        ~NodeManager() override = default;

    public:
        SR_NODISCARD uintptr_t AllocUniqueId(void* ptr);
        void FreeUniqueId(const uintptr_t& id);

        template<typename T> T* GetUnique(uintptr_t id) const {
            SR_LOCK_GUARD;

            if (m_uniques.count(id) == 0)
                return nullptr;

            return reinterpret_cast<T*>(m_uniques.at(id));
        }

    private:
        void OnSingletonDestroy() override;

    private:
        std::unordered_map<uintptr_t, void*> m_uniques;

    };
}

#endif //SR_ENGINE_NODEMANAGER_H
```


