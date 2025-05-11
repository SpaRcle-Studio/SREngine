

# File PoolSet.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**PoolSet.h**](PoolSet_8h.md)

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


