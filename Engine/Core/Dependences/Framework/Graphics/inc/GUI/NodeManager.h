//
// Created by Monika on 16.01.2022.
//

#ifndef SRENGINE_NODEMANAGER_H
#define SRENGINE_NODEMANAGER_H

#include <Utils/Singleton.h>
#include <Types/Thread.h>

namespace SR_GRAPH_NS::GUI {
    class NodeManager : public SR_UTILS_NS::Singleton<NodeManager> {
        friend class SR_UTILS_NS::Singleton<NodeManager>;
    public:
        ~NodeManager() override = default;

    public:
        SR_NODISCARD uintptr_t AllocUniqueId(void* ptr);
        void FreeUniqueId(const uintptr_t& id);

        template<typename T> T* GetUnique(uintptr_t id) const {
            SR_LOCK_GUARD

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

#endif //SRENGINE_NODEMANAGER_H
