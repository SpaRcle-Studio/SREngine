

# File SafeQueue.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**SafeQueue.h**](SafeQueue_8h.md)

[Go to the documentation of this file](SafeQueue_8h.md)


```C++
//
// Created by Monika on 19.05.2022.
//

#ifndef SR_ENGINE_SAFEQUEUE_H
#define SR_ENGINE_SAFEQUEUE_H

#include <Utils/Debug.h>
#include <Utils/Types/Mutex.h>
#include <Utils/Types/Thread.h>

namespace SR_HTYPES_NS {
    template <typename T> class SR_COMMON_DLL_API SafeQueue : public SR_UTILS_NS::NonCopyable {
    public:
        SR_NODISCARD uint64_t Size() const noexcept;
        SR_NODISCARD bool Empty() const noexcept;

        void Flush(const std::function<void(T&)>& callBack);

        void Push(const T& value) noexcept;

        SR_NODISCARD std::shared_lock<std::shared_mutex> ReadLock() const { return std::shared_lock<std::shared_mutex>(m_accessMutex); }
        SR_NODISCARD std::lock_guard<std::shared_mutex> WriteLock() const { return std::lock_guard<std::shared_mutex>(m_accessMutex); }

    private:
        std::queue<T> m_data;

        mutable std::mutex m_dataMutex;
        mutable std::shared_mutex m_accessMutex;

    };

    template<typename T> void SafeQueue<T>::Push(const T &value) noexcept {
        std::lock_guard lock(m_dataMutex);

        m_data.push(value);
    }

    template<typename T> uint64_t SafeQueue<T>::Size() const noexcept {
        std::lock_guard lock(m_dataMutex);

        return m_data.size();
    }

    template<typename T> bool SafeQueue<T>::Empty() const noexcept {
        return Size() == 0;
    }

    template<typename T> void SafeQueue<T>::Flush(const std::function<void(T&)>& callBack) {
        std::lock(m_accessMutex, m_dataMutex);

        std::lock_guard lk1(m_accessMutex, std::adopt_lock);
        std::lock_guard lk2(m_dataMutex, std::adopt_lock);

        while (!m_data.empty()) {
            callBack(m_data.front());
            m_data.pop();
        }
    }
}

#endif //SR_ENGINE_SAFEQUEUE_H
```


