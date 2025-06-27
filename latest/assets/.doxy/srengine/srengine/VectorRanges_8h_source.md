

# File VectorRanges.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Math**](dir_f20ff43999c2f98e3f122645c07885db.md) **>** [**VectorRanges.h**](VectorRanges_8h.md)

[Go to the documentation of this file](VectorRanges_8h.md)


```C++
//
// Created by Monika on 27.06.2025.
//

#ifndef SR_ENGINE_COMMON_MATH_VECTOR_RANGES_H
#define SR_ENGINE_COMMON_MATH_VECTOR_RANGES_H

#include <Utils/Math/Vector3.h>

namespace SR_MATH_NS {
    class UVector3Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = SR_MATH_NS::UVector3;
        using difference_type = std::ptrdiff_t;
        using pointer = SR_MATH_NS::UVector3 *;
        using reference = SR_MATH_NS::UVector3;

        UVector3Iterator()
            : m_max(SR_MATH_NS::UVector3(0, 0, 0)), m_index(0)
        { }

        UVector3Iterator(SR_MATH_NS::UVector3 max, std::size_t index)
            : m_max(max), m_index(index)
        { }

        SR_MATH_NS::UVector3 operator*() const {
            uint32_t x = m_index % m_max.x;
            uint32_t y = (m_index / m_max.x) % m_max.y;
            uint32_t z = m_index / (m_max.x * m_max.y);
            return SR_MATH_NS::UVector3{x, y, z};
        }

        UVector3Iterator &operator++() { ++m_index; return *this; }
        UVector3Iterator operator++(int) { UVector3Iterator tmp = *this; ++(*this); return tmp; }
        UVector3Iterator &operator--() { --m_index; return *this; }
        UVector3Iterator operator--(int) { UVector3Iterator tmp = *this; --(*this); return tmp; }
        UVector3Iterator &operator+=(difference_type n) { m_index += n; return *this; }
        UVector3Iterator &operator-=(difference_type n) { m_index -= n; return *this; }
        UVector3Iterator operator+(difference_type n) const { return UVector3Iterator(m_max, m_index + n); }
        UVector3Iterator operator-(difference_type n) const { return UVector3Iterator(m_max, m_index - n); }
        difference_type operator-(const UVector3Iterator &other) const { return m_index - other.m_index; }
        SR_MATH_NS::UVector3 operator[](difference_type n) const { return *(*this + n); }
        bool operator==(const UVector3Iterator &other) const { return m_index == other.m_index; }
        bool operator!=(const UVector3Iterator &other) const { return m_index != other.m_index; }
        bool operator<(const UVector3Iterator &other) const { return m_index < other.m_index; }
        bool operator>(const UVector3Iterator &other) const { return m_index > other.m_index; }
        bool operator<=(const UVector3Iterator &other) const { return m_index <= other.m_index; }
        bool operator>=(const UVector3Iterator &other) const { return m_index >= other.m_index; }

    private:
        SR_MATH_NS::UVector3 m_max;
        std::size_t m_index;

    };

    class UVector3Range {
    public:
        UVector3Range(uint32_t minX, uint32_t minY, uint32_t minZ, uint32_t maxX, uint32_t maxY, uint32_t maxZ)
            : min(minX, minY, minZ)
            , max(maxX, maxY, maxZ)
        { }

        UVector3Range(uint32_t maxX, uint32_t maxY, uint32_t maxZ)
            : min(0, 0, 0)
            , max(maxX, maxY, maxZ)
        { }

        SR_NODISCARD UVector3Iterator begin() const {
            return UVector3Iterator(max, min.x * min.y * min.z);
        }

        SR_NODISCARD UVector3Iterator end() const {
            return UVector3Iterator(max, max.x * max.y * max.z);
        }

    private:
        SR_MATH_NS::UVector3 min;
        SR_MATH_NS::UVector3 max;

    };
}

#endif //SR_ENGINE_COMMON_MATH_VECTOR_RANGES_H
```


