

# File SortedVector.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**SortedVector.h**](SortedVector_8h.md)

[Go to the documentation of this file](SortedVector_8h.md)


```C++
//
// Created by Monika on 23.04.2024.
//

#ifndef SR_ENGINE_UTILS_SORTED_VECTOR_H
#define SR_ENGINE_UTILS_SORTED_VECTOR_H

#include <Utils/Types/Stack.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_HTYPES_NS {
    template<typename T, typename Predicate = std::less<T>> class SortedVector {
    public:
        using Iterator = typename std::vector<T>::iterator;
        using ConstIterator = typename std::vector<T>::const_iterator;

        SortedVector() = default;
        SortedVector(SortedVector&& other) noexcept
            : m_data(SR_UTILS_NS::Exchange(other.m_data, { }))
        { }

        SortedVector& operator=(SortedVector&& other) noexcept {
            if (this != &other) {
                m_data = SR_UTILS_NS::Exchange(other.m_data, { });
            }
            return *this;
        }

        SR_NODISCARD SR_CONSTEXPR bool Empty() const { return m_data.empty(); }
        SR_NODISCARD SR_CONSTEXPR bool empty() const { return m_data.empty(); }

        SR_NODISCARD SR_CONSTEXPR uint64_t Size() const { return m_data.size(); }
        SR_NODISCARD SR_CONSTEXPR uint64_t size() const { return m_data.size(); }

        SR_NODISCARD SR_CONSTEXPR uint64_t Capacity() const { return m_data.capacity(); }
        SR_NODISCARD SR_CONSTEXPR uint64_t capacity() const { return m_data.capacity(); }

        SR_NODISCARD SR_CONSTEXPR T* Data() { return m_data.data(); }
        SR_NODISCARD SR_CONSTEXPR const T* Data() const { return m_data.data(); }

        SR_NODISCARD SR_CONSTEXPR T* data() { return m_data.data(); }
        SR_NODISCARD SR_CONSTEXPR const T* data() const { return m_data.data(); }

        SR_NODISCARD SR_CONSTEXPR T& operator[](uint64_t index) {
            return m_data[index];
        }

        SR_NODISCARD SR_CONSTEXPR const T& operator[](uint64_t index) const {
            return m_data[index];
        }

        template<class FwdIt, class Ty, typename CustomPred = Predicate> SR_NODISCARD T* UpperBound(FwdIt pStart, const FwdIt pEnd, const Ty& value, const CustomPred& predicate = CustomPred()) {

            auto length = pEnd - pStart;
            while (length > 0) {
                auto half = length / 2;
                auto middle = pStart + half;
                if (predicate(*middle, value)) {
                    pStart = middle + 1;
                    length -= half + 1;
                }
                else {
                    length = half;
                }
            }
            return pStart;
        }

        template<class Ty> SR_NODISCARD Iterator LowerBound(const Ty& value) {
            if (m_data.empty()) {
                return m_data.end();
            }
            return std::lower_bound(m_data.begin(), m_data.end(), value, m_predicate);
        }

        template<class Ty, typename CustomPred = Predicate> SR_NODISCARD Iterator LowerBound(const Ty& value, const CustomPred& predicate) {
            if (m_data.empty()) {
                return m_data.end();
            }
            return std::lower_bound(m_data.begin(), m_data.end(), value, predicate);
        }

        void Insert(Iterator it, const T& value) {
            m_data.insert(it, value);
        }

        void Erase(Iterator it) {
            m_data.erase(it);
        }

        SR_NODISCARD SR_CONSTEXPR Iterator begin() { return m_data.begin(); }
        SR_NODISCARD SR_CONSTEXPR ConstIterator begin() const { return m_data.begin(); }

        SR_NODISCARD SR_CONSTEXPR Iterator end() { return m_data.end(); }
        SR_NODISCARD SR_CONSTEXPR ConstIterator end() const { return m_data.end(); }

        void Add(const T& value) {
            if (m_data.empty()) {
                m_data.push_back(value);
                return;
            }

            auto it = std::lower_bound(m_data.begin(), m_data.end(), value, m_predicate);
            m_data.insert(it, value);
        }

        void Add(T&& value) {
            if (m_data.empty()) {
                m_data.push_back(std::move(value));
                return;
            }

            auto it = std::lower_bound(m_data.begin(), m_data.end(), value, m_predicate);
            m_data.insert(it, std::move(value));
        }

        template<class Ty, typename CustomPred = Predicate> SR_NODISCARD Iterator GetOrCreate(const Ty& value, const CustomPred& predicate) {
            auto it = std::lower_bound(m_data.begin(), m_data.end(), value, predicate);
            if (it == m_data.end() || *it != value) {
                return m_data.insert(it, T());
            }
            return it;
        }

        bool Remove(const T& value) {
            if (m_data.empty()) {
                SRHalt("SortedVector is empty");
                return false;
            }

            auto it = std::lower_bound(m_data.begin(), m_data.end(), value, m_predicate);
            if (it != m_data.end() && *it == value) {
                m_data.erase(it);
                return true;
            }
            return false;
        }

        void Reserve(uint64_t size) {
            m_data.reserve(size);
        }

        void Clear() {
            SR_TRACY_ZONE;
            m_data.clear();
        }

        void ShrunkToFit() {
            m_data.shrink_to_fit();
        }

    private:
        static constexpr Predicate m_predicate = Predicate();

        std::vector<T> m_data;

    };
}

#endif //SR_ENGINE_UTILS_SORTED_VECTOR_H
```


