

# File NodeManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**GUI**](dir_271010341ad15844ff85fbf4e71592f2.md) **>** [**NodeManager.h**](NodeManager_8h.md)

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


