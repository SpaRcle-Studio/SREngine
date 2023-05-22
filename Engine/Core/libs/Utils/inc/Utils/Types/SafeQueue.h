//
// Created by Monika on 19.05.2022.
//

#ifndef SRENGINE_SAFEQUEUE_H
#define SRENGINE_SAFEQUEUE_H

#include <Utils/Debug.h>
#include <Utils/Types/Mutex.h>
#include <Utils/Types/Thread.h>

namespace SR_HTYPES_NS {
    template <typename T> class SR_DLL_EXPORT SafeQueue : public SR_UTILS_NS::NonCopyable {
    public:
        SR_NODISCARD uint64_t Size() const noexcept;
        SR_NODISCARD bool Empty() const noexcept;

        void Flush(const std::function<void(T&)>& callBack);

        void Push(const T& value) noexcept;

        SR_NODISCARD std::shared_lock<std::shared_mutex> ReadLock() const { return std::shared_lock<std::shared_mutex>(m_accessMutex); }
        SR_NODISCARD std::lock_guard<std::shared_mutex> WriteLock() const { return std::lock_guard<std::shared_mutex>(m_accessMutex); }

    private:
        std::queue<T> m_data;

        /// защищает буфер m_data от порчи данных
        mutable std::mutex m_dataMutex;
        /// позволяет управляющей стороне синхронизироваться с очередью.
        /// блокируется для записи только в точке синхронизации очереди.
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

#endif //SRENGINE_SAFEQUEUE_H
