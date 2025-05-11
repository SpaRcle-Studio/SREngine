

# File SafeVariable.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**SafeVariable.h**](SafeVariable_8h.md)

[Go to the documentation of this file](SafeVariable_8h.md)


```C++
//
// Created by Monika on 03.08.2022.
//

#ifndef SR_ENGINE_SAFE_VARIABLE_H
#define SR_ENGINE_SAFE_VARIABLE_H

#include <Utils/Types/Function.h>

namespace SR_HTYPES_NS {
    template<typename T> class SafeVar : public NonCopyable {
    public:
        SafeVar(const T& data);
        SafeVar() = default;

    public:
        SafeVar<T>& operator=(const T& data);

        operator const T&() const noexcept; 
        operator bool() const noexcept; 

        T &operator*() const noexcept;
        T operator->() const noexcept;

        SR_NODISCARD bool operator==(const SafeVar<T> &right) const noexcept;
        SR_NODISCARD bool operator!=(const SafeVar<T> &right) const noexcept;

        SR_NODISCARD T& Get() noexcept;
        SR_NODISCARD const T& Get() const noexcept;

        void Increment() noexcept;

        void Lock() const noexcept;
        void Unlock() const noexcept;
        void RecursiveLock() const noexcept;

        void Do(const std::function<void(T& data)>& func) noexcept;
        void Do(const std::function<void(const T& data)>& func) const noexcept;
        template<typename U> U Do(const std::function<U(const T& data)>& func) const noexcept;
        template<typename U> U Do(const std::function<U(T& data)>& func) noexcept;

    private:
        T m_data;

        mutable std::atomic<bool> m_lock = false;
        mutable std::atomic<uint32_t> m_lockCount = 0;
        mutable std::atomic<std::thread::id> m_owner;

    };

    template<typename T> SafeVar<T>::operator const T&() const noexcept { return m_data; } 
    template<typename T> SafeVar<T>::operator bool() const noexcept { return m_data; } 

    template<typename T> T& SafeVar<T>::operator*() const noexcept { return *m_data; }
    template<typename T> T SafeVar<T>::operator->() const noexcept { return m_data; }

    template<typename T> SR_NODISCARD bool SafeVar<T>::operator==(const SafeVar<T> &right) const noexcept {
        return m_data == right.m_data;
    }

    template<typename T> SR_NODISCARD bool SafeVar<T>::operator!=(const SafeVar<T> &right) const noexcept {
        return m_data != right.m_data;
    }

    template<typename T> SR_NODISCARD T& SafeVar<T>::Get() noexcept { return m_data; }
    template<typename T> SR_NODISCARD const T& SafeVar<T>::Get() const noexcept { return m_data; }

    template<typename T> void SafeVar<T>::Increment() noexcept {
        RecursiveLock();
        ++m_data;
        Unlock();
    }

    template<typename T> template<typename U> U SafeVar<T>::Do(const std::function<U(T& data)> &func) noexcept {
        RecursiveLock();

        auto&& result = func(m_data);

        Unlock();

        return result;
    }

    template<typename T> template<typename U> U SafeVar<T>::Do(const std::function<U(const T& data)> &func) const noexcept {
        RecursiveLock();

        auto&& result = func(m_data);

        Unlock();

        return result;
    }

    template<typename T> void SafeVar<T>::Lock() const noexcept {
        const std::thread::id this_id = std::this_thread::get_id();

        if(m_owner.load() == this_id) {
            SRHalt("Double locking detected!");
        }
        else {
            bool expected = false;
            while (!m_lock.compare_exchange_weak(expected, true, std::memory_order_acquire))
                expected = false;

            m_owner.store(this_id);
            m_lockCount.store(1);
        }
    }

    template<typename T> void SafeVar<T>::Unlock() const noexcept {
        if (m_lockCount > 1) {
            --(m_lockCount);
        }
        else if (m_lockCount) {

            m_owner.store(std::thread::id());
            m_lockCount.store(0);

            m_lock.store(false, std::memory_order_release);
        }
        else {
            SRHalt("lock count = 0!");
        }
    }

    template<typename T> void SafeVar<T>::RecursiveLock() const noexcept {
        const std::thread::id this_id = std::this_thread::get_id();

        if (m_owner.load() == this_id) {
            ++(m_lockCount);
            SRAssert2(m_lockCount < 10000, "Lock count > 10000!");
        }
        else {
            bool expected = false;
            while (!m_lock.compare_exchange_weak(expected, true, std::memory_order_acquire))
                expected = false;

            m_owner.store(this_id);
            m_lockCount.store(1);
        }
    }

    template<typename T> SafeVar<T>::SafeVar(const T& data) {
        m_data = data;
    }

    template<typename T> SafeVar<T>& SafeVar<T>::operator=(const T& data) {
        RecursiveLock();
        m_data = data;
        Unlock();
        return *this;
    }

    template<typename T> void SafeVar<T>::Do(const std::function<void(T &)>& func) noexcept {
        RecursiveLock();
        func(m_data);
        Unlock();
    }

    template<typename T> void SafeVar<T>::Do(const std::function<void(const T &)>& func) const noexcept {
        RecursiveLock();
        func(m_data);
        Unlock();
    }
}

#endif //SR_ENGINE_SAFE_VARIABLE_H
```


