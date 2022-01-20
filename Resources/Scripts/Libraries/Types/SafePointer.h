//
// Created by Monika on 04.08.2021.
//

#ifndef SMARTPOINTER_SAFEPOINTER_H
#define SMARTPOINTER_SAFEPOINTER_H

#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include <atomic>
#include <unordered_set>

#define SR_SAFE_PTR_ASSERT(expr, msg)                                                                                      \
        if (!(expr)) {                                                                                                     \
            fprintf(stderr, "[SafePtr<%s>] %s\n\tLine: %i\n\tPtr: %p\n", typeid(T).name(), msg, __LINE__, (void *) m_ptr); \
        }                                                                                                                  \

template<typename T> class SafePtr {
public:
    explicit SafePtr(T *ptr);
    SafePtr(SafePtr const &ptr);
    SafePtr();
    ~SafePtr();
public:
    bool operator==(SafePtr<T> ptr) const { return this->m_ptr == ptr.m_ptr; }
    bool operator!=(SafePtr<T> ptr) const { return this->m_ptr == ptr.m_ptr; }
    SafePtr<T> &operator=(const SafePtr<T> &ptr);
    SafePtr<T> &operator=(T *ptr);
    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
public:
    void Lock();
    void RecursiveLock();

    void Unlock();

    bool LockIfValid();
    bool RecursiveLockIfValid();

    [[nodiscard]] void* GetRawPtr() const { return (void*)m_ptr; }
    [[nodiscard]] SafePtr<T>& GetThis() { return *this; }
    [[nodiscard]] bool Valid() const { return m_data && m_data->m_valid; }
    [[nodiscard]] bool IsLocked() const { return Valid() && m_data->m_lock; }
    bool Free(const std::function<void(T *ptr)> &freeFun);
private:
    T*                               m_ptr;

    struct dynamic_data {
        std::atomic<bool>            m_lock;
        std::atomic<uint32_t>        m_lockCount;
        std::atomic<uint32_t>        m_useCount;
        bool                         m_valid{};
        std::atomic<std::thread::id> m_owner;
    }* m_data;
};

template<typename T>SafePtr<T>::SafePtr(T *ptr) {
    m_ptr = ptr;

    m_data = new dynamic_data {
            false,                         // m_lock
            0,                             // m_lockCount
            1,                             // m_useCount
            (bool)ptr,                     // m_valid
            std::atomic<std::thread::id>() // m_owner
    };
}
template<typename T>SafePtr<T>::SafePtr() {
    m_ptr = nullptr;

    m_data = new dynamic_data {
            false,                         // m_lock
            0,                             // m_lockCount
            1,                             // m_useCount
            false,                         // m_valid
            std::atomic<std::thread::id>() // m_owner
    };
}
template<typename T> SafePtr<T>::SafePtr(const SafePtr &ptr) {
    m_ptr = ptr.m_ptr;
    m_data = ptr.m_data;

    ++m_data->m_useCount;
}
template<typename T> SafePtr<T>::~SafePtr() {
    if (m_data->m_useCount <= 1) {
        SR_SAFE_PTR_ASSERT(!m_data->m_valid, "Ptr was not freed!");
        SR_SAFE_PTR_ASSERT(m_data->m_lockCount == 0 && !m_data->m_lock, "Ptr was not unlocked!");

        delete m_data;
    } else
        --(m_data->m_useCount);
}

template<typename T> SafePtr<T> &SafePtr<T>::operator=(const SafePtr<T> &ptr) {
    if (m_data->m_useCount <= 1) {
        SR_SAFE_PTR_ASSERT(!m_data->m_valid, "Ptr was not freed!");
        SR_SAFE_PTR_ASSERT(m_data->m_lockCount == 0 && !m_data->m_lock, "Ptr was not unlocked!");

        delete m_data;
    }
    else
        --(m_data->m_useCount);

    m_ptr = ptr.m_ptr;
    m_data = ptr.m_data;

    ++(m_data->m_useCount);

    return *this;
}

template<typename T> SafePtr<T> &SafePtr<T>::operator=(T *ptr) {
    if (m_ptr != ptr) {
        if (m_data->m_useCount <= 1) {
            SR_SAFE_PTR_ASSERT(!m_data->m_valid, "Ptr was not freed!");
            SR_SAFE_PTR_ASSERT(m_data->m_lockCount == 0 && !m_data->m_lock, "Ptr was not unlocked!");

            delete m_data;
        } else
            --(m_data->m_useCount);

        m_data = new dynamic_data {
                false,                         // m_lock
                0,                             // m_lockCount
                1,                             // m_useCount
                false,                         // m_valid
                std::atomic<std::thread::id>() // m_owner
        };
    }

    m_data->m_valid = bool(m_ptr = ptr);

    return *this;
}

template<typename T> bool SafePtr<T>::Free(const std::function<void(T *)> &freeFun) {
    if (m_data->m_valid) {
        freeFun(m_ptr);
        m_data->m_valid = false;
        m_ptr = nullptr;
        return true;
    } else
        return false;
}
template<typename T> void SafePtr<T>::Lock() {
    const std::thread::id this_id = std::this_thread::get_id();

    if(m_data->m_owner.load() == this_id) {
        SR_SAFE_PTR_ASSERT(false, "Double locking detected!");
    }
    else {
        bool expected = false;
        while (!m_data->m_lock.compare_exchange_weak(expected, true, std::memory_order_acquire))
            expected = false;

        m_data->m_owner.store(this_id);
        m_data->m_lockCount.store(1);
    }
}

template<typename T> void SafePtr<T>::Unlock() {
    if(m_data->m_lockCount > 1) {
        /// recursive unlocking
        --(m_data->m_lockCount);
    }
    else if (m_data->m_lockCount) {
        /// normal unlocking

        m_data->m_owner.store(std::thread::id());
        m_data->m_lockCount.store(0);

        m_data->m_lock.store(false, std::memory_order_release);
    }
    else
        SR_SAFE_PTR_ASSERT(false, "lock count = 0!")
}

template<typename T> bool SafePtr<T>::LockIfValid() {
    Lock();

    if (m_data->m_valid)
        return true;

    Unlock();

    return false;
}

template<typename T> void SafePtr<T>::RecursiveLock() {
    const std::thread::id this_id = std::this_thread::get_id();

    if(m_data->m_owner.load() == this_id) {
        /// recursive locking
        ++(m_data->m_lockCount);
    }
    else {
        bool expected = false;
        while (!m_data->m_lock.compare_exchange_weak(expected, true, std::memory_order_acquire))
            expected = false;

        m_data->m_owner.store(this_id);
        m_data->m_lockCount.store(1);
    }
}

template<typename T> bool SafePtr<T>::RecursiveLockIfValid() {
    RecursiveLock();

    if (m_data->m_valid)
        return true;

    Unlock();

    return false;
}

namespace std {
    template<typename T> struct hash<SafePtr<T>> {
        size_t operator()(SafePtr<T> const& ptr) const {
            return std::hash<void*>()(ptr.GetRawPtr());
        }
    };

    template <typename T> struct less<SafePtr<T>> {
        bool operator()(const SafePtr<T> &lhs, const SafePtr<T> &rhs) const {
            void* a = lhs.GetRawPtr();
            void* b = rhs.GetRawPtr();
            return a < b;
        }
    };
}


#endif //SMARTPOINTER_SAFEPOINTER_H