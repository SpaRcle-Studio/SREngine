//
// Created by Monika on 19.05.2022.
//

#ifndef SRENGINE_SAFEQUEUE_H
#define SRENGINE_SAFEQUEUE_H

#include <Utils/Debug.h>
#include <Utils/Types/Thread.h>

namespace SR_HTYPES_NS {
    template <typename T> class SR_DLL_EXPORT SafeQueue {
        using Mutex = std::recursive_mutex;
    public:
        SR_NODISCARD uint64_t Size() const noexcept;
        SR_NODISCARD bool Empty() const noexcept;

        void Push(const T& value) noexcept;
        SR_NODISCARD T Pop(const T& def) noexcept;

        void Lock() const;
        void Unlock() const;

    private:
        std::queue<T> m_data;
        mutable Mutex m_mutex;

    };

    template<typename T> void SafeQueue<T>::Push(const T &value) noexcept {
        SR_SCOPED_LOCK

        m_data.push(value);
    }

    template<typename T> uint64_t SafeQueue<T>::Size() const noexcept {
        SR_SCOPED_LOCK

        return m_data.size();
    }

    template<typename T> bool SafeQueue<T>::Empty() const noexcept {
        return Size() == 0;
    }

    template<typename T> T SafeQueue<T>::Pop(const T &def) noexcept {
        SR_SCOPED_LOCK

        if (Empty()) {
            return def;
        }

        T data = m_data.front();
        m_data.pop();
        return data;
    }

    template<typename T> void SafeQueue<T>::Lock() const {
        m_mutex.lock();
    }

    template<typename T> void SafeQueue<T>::Unlock() const {
        m_mutex.unlock();
    }
}

#endif //SRENGINE_SAFEQUEUE_H
