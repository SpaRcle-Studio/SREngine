

# File VectorUtils.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**VectorUtils.h**](VectorUtils_8h.md)

[Go to the documentation of this file](VectorUtils_8h.md)


```C++
//
// Created by Monika on 01.09.2021.
//

#ifndef SR_ENGINE_VECTORUTILS_H
#define SR_ENGINE_VECTORUTILS_H

#include <Utils/Common/StringFormat.h>

namespace SR_UTILS_NS {
    class VectorUtils {
    public:
        VectorUtils() = delete;
        VectorUtils(VectorUtils &) = delete;
        ~VectorUtils() = delete;
        VectorUtils operator=(VectorUtils&) = delete;
    public:
        template<typename T> static std::vector<T> Combine(const std::vector<T>& A, const std::vector<T>& B) {
            std::vector<T> AB(A.size() + B.size()); // preallocate memory
            AB.insert(AB.end(), A.begin(), A.end());
            AB.insert(AB.end(), B.begin(), B.end());
            return AB;
        }

        template<typename A, typename B> static std::vector<B> Cast(const std::vector<A>& source) {
            std::vector<B> result;

            if constexpr (std::is_same_v<A, std::string>) {
                for (const auto& src : source)
                    result.emplace_back(LexicalCast<B>(src));
            } else
                static_assert("Unsupported type!");

            return result;
        }

        inline static std::string Merge(const std::vector<std::string>& lines) {
            std::string merged;

            for (auto&& line : lines)
                merged.append(line).append("\n");

            return merged;
        }
    };

    template<typename T, typename U> bool ForEach(const std::function<bool(T& type, const uint32_t& index)> &fn, std::vector<U>& vector) {
        uint32_t index = 0;
        for (T& folder : vector) {
            if (!fn(folder, index))
                return false;
            ++index;
        }
        return true;
    }

    template<typename T, typename U> bool ForEach(const std::function<bool(T& type, const uint32_t& index)> &fn, std::list<U>& vector) {
        uint32_t index = 0;
        for (T& folder : vector) {
            if (!fn(folder, index))
                return false;
            ++index;
        }
        return true;
    }

    template<typename T, typename U> bool ForEach(const std::function<bool(const T& type, const uint32_t& index)> &fn, const std::vector<U>& vector) {
        uint32_t index = 0;
        for (const T& folder : vector) {
            if (!fn(folder, index))
                return false;
            ++index;
        }
        return true;
    }

    template<typename T, typename U> bool ForEach(const std::function<bool(const T& type, const uint32_t& index)> &fn, const std::list<U>& vector) {
        uint32_t index = 0;
        for (const T& folder : vector) {
            if (!fn(folder, index))
                return false;
            ++index;
        }
        return true;
    }
}

#endif //SR_ENGINE_VECTORUTILS_H
```


