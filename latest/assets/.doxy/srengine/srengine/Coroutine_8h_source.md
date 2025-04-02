

# File Coroutine.h

[**File List**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**Coroutine.h**](Coroutine_8h.md)

[Go to the documentation of this file](Coroutine_8h.md)


```C++
//
// Created by Monika on 05.04.2024.
//

#ifndef SR_UTILS_ENGINE_COROUTINE_H
#define SR_UTILS_ENGINE_COROUTINE_H

#include <Utils/stdInclude.h>

#ifdef SR_USE_CPP_CORO
#include <cppcoro/coroutine.hpp>
#include <cppcoro/generator.hpp>

namespace SR_UTILS_NS {
    template<typename T> class SR_NODISCARD CoroutineGenerator : public cppcoro::generator<T> {
        using Super = cppcoro::generator<T>;
    public:
        using Iterator = typename cppcoro::generator<T>::iterator;

        CoroutineGenerator() = default;
        CoroutineGenerator(const CoroutineGenerator&) = delete;

        CoroutineGenerator(cppcoro::generator<T>&& other) noexcept 
            : Super(std::move(other))
        { }

        CoroutineGenerator(CoroutineGenerator&& other) noexcept
            : Super(std::move(other))
        { }

        CoroutineGenerator& operator=(const CoroutineGenerator& other) = delete;

        CoroutineGenerator& operator=(CoroutineGenerator other) noexcept {
            Swap(other);
            return *this;
        }

        void Swap(CoroutineGenerator& other) noexcept {
            std::swap(this->m_coroutine, other.m_coroutine);
        }
    };
}
#endif

#endif //SR_UTILS_ENGINE_COROUTINE_H
```


