//
// Created by Monika on 04.08.2021.
//

#ifndef SMARTPOINTER_SAFEPOINTER_H
#define SMARTPOINTER_SAFEPOINTER_H

#include <iostream>
#include <functional>
#include <string>
#include <atomic>

#include <string>
#include <cstdlib>

namespace Framework::Helper::Types {
    template<typename T>
    class SafePtr {
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
        void Unlock();

        bool LockIfValid();

        [[nodiscard]] void* GetRawPtr() const { return (void*)m_ptr; }
        bool Valid() { return *m_valid; }
        bool Free(const std::function<void(T *ptr)> &freeFun);
    private:
        T*                     m_ptr;
        std::atomic<uint32_t>* m_count;
        std::atomic<bool>*     m_lock;
        bool*                  m_valid;
    };

    template<typename T>
    SafePtr<T>::SafePtr(T *ptr) {
        m_ptr = ptr;
        m_count = new std::atomic<uint32_t>(1);
        m_valid = new bool(true);
        m_lock = new std::atomic<bool>(false);
    }

    template<typename T>
    SafePtr<T>::SafePtr() {
        m_ptr = nullptr;
        m_count = new std::atomic<uint32_t>(1);
        m_lock = new std::atomic<bool>(false);
        m_valid = new bool(false);
    }

    template<typename T>
    SafePtr<T>::SafePtr(const SafePtr &ptr) {
        m_ptr = ptr.m_ptr;
        m_valid = ptr.m_valid;
        m_count = ptr.m_count;
        m_lock = ptr.m_lock;
        (*m_count)++;
    }

    template<typename T>
    SafePtr<T>::~SafePtr() {
        if (*m_count == 1) {
            delete m_count;

            if (*m_valid)
                fprintf(stderr, (std::string("~SafePtr<")
                                //.append(typeid(T).name())
                                .append(">(): ptr was not freed! Address: %p\n")).c_str(),
                        (void *) m_ptr);

            delete m_valid;
            delete m_lock;
        } else
            (*m_count)--;
    }

    template<typename T>
    SafePtr<T> &SafePtr<T>::operator=(const SafePtr<T> &ptr) {
        if (m_count != ptr.m_count)
            (*m_count)--;

        m_count = ptr.m_count;
        m_ptr = ptr.m_ptr;
        m_valid = ptr.m_valid;
        m_lock = ptr.m_lock;

        (*m_count)++;

        return *this;
    }

    template<typename T>
    SafePtr<T> &SafePtr<T>::operator=(T *ptr) {
        if (m_ptr != ptr) {
            if (*m_count == 1) {
                if (*m_valid)
                    fprintf(stderr, (std::string("SafePtr<")
                                    //.append(typeid(T).name())
                                    .append(">&operator=(T* ptr): ptr was not freed! Address: %p\n")).c_str(),
                            (void *) m_ptr);
                delete m_count;
                delete m_valid;
                delete m_lock;
            } else
                (*m_count)--;

            m_count = new std::atomic<uint32_t>(1);
            m_valid = new bool(false);
            m_lock = new std::atomic<bool>(false);
        }

        if (ptr)
            *m_valid = true;
        this->m_ptr = ptr;
        return *this;
    }

    template<typename T>
    bool SafePtr<T>::Free(const std::function<void(T *)> &freeFun) {
        if (*m_valid) {
            *m_valid = false;
            freeFun(m_ptr);
            m_ptr = nullptr;
            return true;
        } else
            return false;
    }

    template<typename T>
    void SafePtr<T>::Lock() {
        bool expected = false;
        while (!m_lock->compare_exchange_weak(expected, true, std::memory_order_acquire))
            expected = false;
    }

    template<typename T>
    void SafePtr<T>::Unlock() {
        m_lock->store(false, std::memory_order_release);
    }

    template<typename T> bool SafePtr<T>::LockIfValid() {
        Lock();

        if (*m_valid)
            return true;

        Unlock();

        return false;
    }
}

namespace std {
    template <typename T> struct less<Framework::Helper::Types::SafePtr<T>> {
        bool operator()(const Framework::Helper::Types::SafePtr<T> &lhs, const Framework::Helper::Types::SafePtr<T> &rhs) const {
            void* a = lhs.GetRawPtr();
            void* b = rhs.GetRawPtr();
            return a < b;
        }
    };
}

#endif //SMARTPOINTER_SAFEPOINTER_H