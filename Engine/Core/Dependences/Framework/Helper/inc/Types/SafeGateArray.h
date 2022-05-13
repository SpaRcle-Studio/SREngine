//
// Created by Monika on 10.02.2022.
//

#ifndef SRENGINE_SAFEGATEARRAY_H
#define SRENGINE_SAFEGATEARRAY_H

#include <Debug.h>

namespace Framework::Helper::Types {
    template<typename T> class SafeGateArray {
    public:
        SafeGateArray() = default;

    public:
        void Remove(T value) {
            std::lock_guard <std::mutex> lock(m_mutex);
            m_remove.insert(value);
            m_needFlush = true;
        }

        void Add(T value) {
            std::lock_guard <std::mutex> lock(m_mutex);
            m_add.insert(value);
            m_needFlush = true;
        }

        bool NeedFlush() {
            return m_needFlush;
        }

        void Clear() {
            m_count = 0;
            m_container.clear();
        }

        void Flush() {
            std::lock_guard <std::mutex> lock(m_mutex);

            for (auto &value : m_add) {
                m_container.insert(value);
                ++m_count;
            }

            for (auto &value : m_remove) {
                m_container.erase(value);
                --m_count;
            }

            m_add.clear();
            m_remove.clear();
            m_needFlush = false;
        }

        T Front() { return *m_container.begin(); }

        uint32_t Count() const { return m_count; }
        uint32_t Empty() const { return m_count == 0; }
        std::set<T>& GetElements() { return m_container; }
        std::set<T>& GetAddedElements() { return m_add; }
        std::set<T>& GetDeletedElements() { return m_remove; }

    private:
        std::set<T> m_add;
        std::set<T> m_remove;
        std::set<T> m_container;
        std::mutex m_mutex;
        std::atomic<bool> m_needFlush = false;
        std::atomic<uint32_t> m_count = 0;

    };
}

#endif //SRENGINE_SAFEGATEARRAY_H
