//
// Created by Monika on 04.08.2021.
//

#ifndef SMARTPOINTER_SAFEPOINTER_H
#define SMARTPOINTER_SAFEPOINTER_H

#include <Utils/Common/StringFormat.h>

namespace SR_HTYPES_NS {
    static std::atomic<int64_t> SAFE_POINTER_COUNTS = 0;

    #define SR_NEW_SAFE_PTR() {                              \
        }                                                    \

    #define SR_DEL_SAFE_PTR() {                              \
        }                                                    \

    template<typename T> class SR_DLL_EXPORT SafePtr {
    public:
        explicit SafePtr(T *ptr);
        SafePtr(SafePtr const &ptr);
        SafePtr();
        ~SafePtr(); /// не должен быть виртуальным
    public:
        operator bool() const { return Valid(); }
        bool operator==(SafePtr<T> ptr) const { return this->m_ptr == ptr.m_ptr; }
        bool operator!=(SafePtr<T> ptr) const { return this->m_ptr == ptr.m_ptr; }
        SafePtr<T> &operator=(const SafePtr<T> &ptr);
        SafePtr<T> &operator=(T *ptr);
        T &operator*() const { return *m_ptr; }
        T *operator->() const { return m_ptr; }
    public:
        bool TryLock() const;
        void Lock() const;
        void Unlock() const;
        void RecursiveLock() const;

        void Replace(const SafePtr &ptr);

        template<typename U> U DynamicCast() {
           return dynamic_cast<U>(m_ptr);
        }

        template<typename U> U Do(const std::function<U(T* ptr)>& func, U _default) {
            if (LockIfValid()) {
                const auto&& result = func(m_ptr);
                Unlock();
                return result;
            }

            return _default;
        }

        template<typename U> U TryDo(const std::function<U(T* ptr)>& func, U _default) {
            if (TryLockIfValid()) {
                const auto&& result = func(m_ptr);
                Unlock();
                return result;
            }

            return _default;
        }

        SR_NODISCARD bool TryLockIfValid() const;
        SR_NODISCARD bool LockIfValid() const;
        SR_NODISCARD bool RecursiveLockIfValid() const;

        SR_NODISCARD T* Get() const { return m_ptr; }
        SR_NODISCARD void* GetRawPtr() const { return (void*)m_ptr; }
        SR_NODISCARD SafePtr<T>& GetThis() { return *this; }
        SR_NODISCARD bool Valid() const { return m_data && m_data->m_valid; }
        SR_NODISCARD bool IsLocked() const { return Valid() && m_data->m_lock; }
        SR_NODISCARD uint32_t GetUseCount() const;

        [[deprecated("Ref-unsafe. Replaced by AutoFree")]]
        bool Free(const std::function<void(T *ptr)> &freeFun);

        bool AutoFree(const std::function<void(T *ptr)> &freeFun);
    private:
        bool FreeImpl(const std::function<void(T *ptr)> &freeFun);

    private:
        struct dynamic_data {
            mutable std::atomic<bool>            m_lock;
            mutable std::atomic<uint32_t>        m_lockCount;
            mutable std::atomic<uint32_t>        m_useCount;
            bool                                 m_valid{};
            mutable std::atomic<std::thread::id> m_owner;
        }* m_data;
        T* m_ptr;
    };

    template<typename T>SafePtr<T>::SafePtr(T *ptr) {
        m_ptr = ptr;

        SR_NEW_SAFE_PTR();

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

        SR_NEW_SAFE_PTR();

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

            SR_DEL_SAFE_PTR();

            delete m_data;
        }
        else
            --(m_data->m_useCount);
    }

    template<typename T> SafePtr<T> &SafePtr<T>::operator=(const SafePtr<T> &ptr) {
        if (m_data->m_useCount <= 1) {
            SR_SAFE_PTR_ASSERT(!m_data->m_valid, "Ptr was not freed!");
            SR_SAFE_PTR_ASSERT(m_data->m_lockCount == 0 && !m_data->m_lock, "Ptr was not unlocked!");

            SR_DEL_SAFE_PTR();

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

                SR_DEL_SAFE_PTR();

                delete m_data;
            } else
                --(m_data->m_useCount);

            SR_NEW_SAFE_PTR();

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

    template<typename T> bool SafePtr<T>::AutoFree(const std::function<void(T *)> &freeFun) {
        SafePtr<T> ptrCopy = SafePtr<T>(*this);
        /// после вызова FreeImpl this может потенциально инвалидироваться!

        bool result = false;

        if (ptrCopy.LockIfValid()) {
            result = ptrCopy.FreeImpl(freeFun);
            ptrCopy.Unlock();
        }

        return result;
    }

    template<typename T> bool SafePtr<T>::FreeImpl(const std::function<void(T *ptr)> &freeFun) {
        if (m_data->m_valid) {
            freeFun(m_ptr);
            m_data->m_valid = false;
            m_ptr = nullptr;
            return true;
        } else
            return false;
    }

    template<typename T> bool SafePtr<T>::Free(const std::function<void(T *)> &freeFun) {
        SafePtr<T> ptrCopy = SafePtr<T>(*this);
        /// после вызова FreeImpl this может потенциально инвалидироваться!
        return ptrCopy.FreeImpl(freeFun);
    }

    template<typename T> void SafePtr<T>::Lock() const {
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

    template<typename T> void SafePtr<T>::Unlock() const {
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
            SR_SAFE_PTR_ASSERT(false, "lock count = 0!");
    }

    template<typename T> SR_NODISCARD bool SafePtr<T>::LockIfValid() const {
        Lock();

        if (m_data->m_valid)
            return true;

        Unlock();

        return false;
    }

    template<typename T> void SafePtr<T>::RecursiveLock() const {
        const std::thread::id this_id = std::this_thread::get_id();

        if(m_data->m_owner.load() == this_id) {
            /// recursive locking
            ++(m_data->m_lockCount);
            SR_SAFE_PTR_ASSERT("Lock count > 10000!", m_data->m_lockCount < 10000);
        }
        else {
            bool expected = false;
            while (!m_data->m_lock.compare_exchange_weak(expected, true, std::memory_order_acquire))
                expected = false;

            m_data->m_owner.store(this_id);
            m_data->m_lockCount.store(1);
        }
    }

    template<typename T> SR_NODISCARD bool SafePtr<T>::RecursiveLockIfValid() const {
        RecursiveLock();

        if (m_data->m_valid)
            return true;

        Unlock();

        return false;
    }

    template<typename T> void SafePtr<T>::Replace(const SafePtr &ptr) {
        if (ptr.m_ptr == m_ptr)
            return;

        SafePtr copy = *this;
        copy.RecursiveLock();
        *this = ptr;
        copy.Unlock();
    }

    template<typename T> bool SafePtr<T>::TryLockIfValid() const {
        if (!TryLock())
            return false;

        if (m_data->m_valid)
            return true;

        Unlock();

        return false;
    }

    template<typename T> bool SafePtr<T>::TryLock() const {
        const std::thread::id this_id = std::this_thread::get_id();

        if(m_data->m_owner.load() == this_id) {
            SR_SAFE_PTR_ASSERT(false, "Double locking detected!");
            return false;
        }
        else {
            bool expected = false;
            while (!m_data->m_lock.compare_exchange_weak(expected, true, std::memory_order_acquire))
                return false;

            m_data->m_owner.store(this_id);
            m_data->m_lockCount.store(1);

            return true;
        }
    }

    template<typename T> uint32_t SafePtr<T>::GetUseCount() const {
        return Valid() ? m_data->m_useCount.load() : 0;
    }
}

namespace std {
    template<typename T> struct hash<Framework::Helper::Types::SafePtr<T>> {
        size_t operator()(Framework::Helper::Types::SafePtr<T> const& ptr) const {
            return std::hash<void*>()(ptr.GetRawPtr());
        }
    };

    template <typename T> struct less<Framework::Helper::Types::SafePtr<T>> {
        bool operator()(const Framework::Helper::Types::SafePtr<T> &lhs, const Framework::Helper::Types::SafePtr<T> &rhs) const {
            void* a = lhs.GetRawPtr();
            void* b = rhs.GetRawPtr();
            return a < b;
        }
    };
}

#endif //SMARTPOINTER_SAFEPOINTER_H