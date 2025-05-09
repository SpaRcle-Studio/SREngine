

# File SafeGateArray.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**SafeGateArray.h**](SafeGateArray_8h.md)

[Go to the documentation of this file](SafeGateArray_8h.md)


```C++
//
// Created by Monika on 10.02.2022.
//

#ifndef SR_ENGINE_SAFEGATEARRAY_H
#define SR_ENGINE_SAFEGATEARRAY_H

#include <Utils/Debug.h>

namespace SR_HTYPES_NS {
    template<typename T> class SR_COMMON_DLL_API SafeGateArray {
    public:
        SafeGateArray() = default;

    public:
        void Remove(const T& value) {
            SR_LOCK_GUARD;
            m_remove.insert(value);
            m_needFlush = true;
        }

        void SyncRemove(const T& value) {
            Remove(value);

            while(true) {
                SR_LOCK_GUARD;
                if (m_container.count(value) == 0) {
                    return;
                }
            }
        }

        void Add(T value) {
            SR_LOCK_GUARD;
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
            SR_LOCK_GUARD;

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
        std::recursive_mutex m_mutex;
        std::atomic<bool> m_needFlush = false;
        std::atomic<uint32_t> m_count = 0;

    };
}

#endif //SR_ENGINE_SAFEGATEARRAY_H
```


