

# File PoolSet.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**PoolSet.h**](PoolSet_8h.md)

[Go to the documentation of this file](PoolSet_8h.md)


```C++
//
// Created by Monika on 29.04.2024.
//

#ifndef SR_ENGINE_UTILS_POOL_SET_H
#define SR_ENGINE_UTILS_POOL_SET_H

#include <Utils/Math/Mathematics.h>

namespace SR_HTYPES_NS {
    template<typename T> class PoolSet : SR_UTILS_NS::NonCopyable {
    public:
        ~PoolSet() override {
            if (m_maskPool != nullptr) {
                delete[] m_maskPool;
            }
        }

        void Fill(T value) {
            if (m_maskPool == nullptr) {
                return;
            }

            memset(m_maskPool, value, (m_max + 1) * sizeof(T));
        }

        void Set(uint32_t index, T value) {
            m_min = SR_MIN(m_min, index);
            m_max = SR_MAX(m_max, index);

            if (m_maskPool == nullptr) SR_UNLIKELY_ATTRIBUTE {
                m_maskPool = new T[index + 1];
            }
            else if (index >= m_max) SR_UNLIKELY_ATTRIBUTE {
                T* newPool = new T[index + 1];
                memcpy(newPool, m_maskPool, m_max * sizeof(T));
                delete[] m_maskPool;
                m_maskPool = newPool;
            }

            m_maskPool[index] = value;
        }

        T Get(uint32_t index, T defaultValue) {
            if (m_maskPool == nullptr || index < m_min || index > m_max) SR_UNLIKELY_ATTRIBUTE {
                return defaultValue;
            }
            return m_maskPool[index];
        }

        T Get(uint32_t index, T defaultValue) const {
            if (m_maskPool == nullptr || index < m_min || index > m_max) {
                return defaultValue;
            }
            return m_maskPool[index];
        }

    private:
        uint32_t m_min = SR_UINT32_MAX;
        uint32_t m_max = 0;
        T* m_maskPool = nullptr;

    };
}

#endif //SR_ENGINE_UTILS_MASKED_POOL_SET_H
```


