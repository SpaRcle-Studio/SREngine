

# File SafeGateArray.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**SafeGateArray.h**](SafeGateArray_8h.md)

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


