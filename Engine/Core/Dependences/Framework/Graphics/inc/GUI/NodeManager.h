//
// Created by Monika on 16.01.2022.
//

#ifndef SRENGINE_NODEMANAGER_H
#define SRENGINE_NODEMANAGER_H

#include <unordered_set>
#include <unordered_map>
#include <mutex>
#include <Utils/Singleton.h>

namespace Framework::Graphics::GUI {
    class NodeManager : public Helper::Singleton<NodeManager> {
        friend class Helper::Singleton<NodeManager>;
    public:
        ~NodeManager() override = default;

    public:
        [[nodiscard]] uintptr_t AllocUniqueId(void* ptr);
        void FreeUniqueId(const uintptr_t& id);

        template<typename T> T* GetUnique(uintptr_t id) const {
            std::lock_guard<std::mutex> lock(m_mutex);

            if (m_uniques.count(id) == 0)
                return nullptr;

            return reinterpret_cast<T*>(m_uniques.at(id));
        }

    private:
        void OnSingletonDestroy() override;

    private:
        mutable std::mutex m_mutex;
        std::unordered_map<uintptr_t, void*> m_uniques;

    };
}

#endif //SRENGINE_NODEMANAGER_H
