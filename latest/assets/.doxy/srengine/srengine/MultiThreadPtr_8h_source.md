

# File MultiThreadPtr.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**MultiThreadPtr.h**](MultiThreadPtr_8h.md)

[Go to the documentation of this file](MultiThreadPtr_8h.md)


```C++
//
// Created by Monika on 13.03.2023.
//

#ifndef SR_ENGINE_MULTITHREADPTR_H
#define SR_ENGINE_MULTITHREADPTR_H

#include <Utils/Debug.h>

#define SR_NEW_MULTI_THREAD_PTR() { }
#define SR_DEL_MULTI_THREAD_PTR() { }

namespace SR_HTYPES_NS {
    template<class T> class SR_COMMON_DLL_API MultiThreadPtr {
    public:
        explicit MultiThreadPtr(T *ptr);
        MultiThreadPtr(MultiThreadPtr const& ptr);
        MultiThreadPtr() = default;
        ~MultiThreadPtr(); 

    public:
        MultiThreadPtr<T> &operator=(const MultiThreadPtr<T> &ptr);
        MultiThreadPtr<T> &operator=(T *ptr);

        operator bool() const noexcept { return m_data && m_data->m_valid; } 
        T &operator*() const { return *m_ptr; }
        T *operator->() const { return m_ptr; }

        SR_NODISCARD SR_INLINE bool operator==(const MultiThreadPtr<T>& right) const noexcept {
            return m_ptr == right.m_ptr;
        }
        SR_NODISCARD SR_INLINE bool operator!=(const MultiThreadPtr<T>& right) const noexcept {
            return m_ptr != right.m_ptr;
        }

    public:
        bool Lock() const;
        void Unlock() const;

        template<typename U> U DynamicCast() {
            return dynamic_cast<U>(m_ptr);
        }

        SR_NODISCARD T* Get() const { return m_ptr; }
        SR_NODISCARD void* GetRawPtr() const { return (void*)m_ptr; }
        SR_NODISCARD std::recursive_mutex& GetMutex() const { return m_data->m_mutex; }
        SR_NODISCARD MultiThreadPtr<T> GetThis() { return MultiThreadPtr<T>(*this); }

        SR_NODISCARD bool Valid() const { return m_data && m_data->m_valid; }
        SR_NODISCARD uint32_t GetUseCount() const { return Valid() ? m_data->m_useCount.load() : 0; }

        bool AutoFree(const std::function<void(T *ptr)>& freeFun);

    private:
        bool FreeImpl(const std::function<void(T *ptr)>& freeFun);

    private:
        struct dynamic_data {
            mutable std::recursive_mutex         m_mutex;
            mutable std::atomic<uint32_t>        m_useCount;
            bool                                 m_valid {};
        }* m_data = nullptr;
        T* m_ptr = nullptr;

    };


    template<typename T> MultiThreadPtr<T>::MultiThreadPtr(T *ptr) {
        if ((m_ptr = ptr)) {
            SR_NEW_MULTI_THREAD_PTR();

            m_data = new dynamic_data {
                std::recursive_mutex(), 
                1,                      
                (bool)ptr,              
            };
        }
    }

    template<typename T> MultiThreadPtr<T>::MultiThreadPtr(const MultiThreadPtr& ptr) {
        m_ptr = ptr.m_ptr;

        if ((m_data = ptr.m_data)) {
            ++m_data->m_useCount;
        }
    }

    template<typename T> MultiThreadPtr<T>::~MultiThreadPtr() {
        if (m_data && m_data->m_useCount <= 1) {
            SR_SAFE_PTR_ASSERT(!m_data->m_valid, "Ptr was not freed!");
            SR_DEL_MULTI_THREAD_PTR();
            delete m_data;
        }
        else if (m_data) {
            --(m_data->m_useCount);
        }
    }

    template<typename T> MultiThreadPtr<T>& MultiThreadPtr<T>::operator=(const MultiThreadPtr<T>& ptr) {
        if (m_data && m_data->m_useCount <= 1) {
            SR_SAFE_PTR_ASSERT(!m_data->m_valid, "Ptr was not freed!");
            SR_DEL_MULTI_THREAD_PTR();
            delete m_data;
        }
        else if (m_data) {
            --(m_data->m_useCount);
        }

        if ((m_data = ptr.m_data)) {
            m_data->m_valid = bool(m_ptr = ptr.m_ptr);
            ++(m_data->m_useCount);
        }

        return *this;
    }

    template<typename T> MultiThreadPtr<T>& MultiThreadPtr<T>::operator=(T* ptr) {
        if (m_ptr != ptr) {
            if (m_data && m_data->m_useCount <= 1) {
                SR_SAFE_PTR_ASSERT(!m_data->m_valid, "Ptr was not freed!");
                SR_DEL_MULTI_THREAD_PTR();
                delete m_data;
            }
            else if (m_data) {
                --(m_data->m_useCount);
            }

            SR_NEW_MULTI_THREAD_PTR();

            if (auto&& inherit = dynamic_cast<MultiThreadPtr<T>*>(ptr)) {
                if ((m_data = inherit->m_data)) {
                    ++(m_data->m_useCount);
                }
            }
            else {
                m_data = new dynamic_data{
                        std::recursive_mutex(), 
                        1,                      
                        false,                  
                };
            }
        }

        if (m_data) {
            m_data->m_valid = bool(m_ptr = ptr);
        }

        return *this;
    }

    template<typename T> bool MultiThreadPtr<T>::AutoFree(const std::function<void(T *)>& freeFun) {
        MultiThreadPtr<T> ptrCopy = MultiThreadPtr<T>(*this);

        bool result = false;

        if (ptrCopy.Lock()) {
            result = ptrCopy.FreeImpl(freeFun);
            ptrCopy.Unlock();
        }

        return result;
    }

    template<typename T> bool MultiThreadPtr<T>::FreeImpl(const std::function<void(T *ptr)>& freeFun) {
        if (m_data->m_valid) {
            freeFun(m_ptr);
            m_data->m_valid = false;
            m_ptr = nullptr;
            return true;
        }
        else {
            return false;
        }
    }

    template<typename T> bool MultiThreadPtr<T>::Lock() const {
        if (!Valid()) {
            return false;
        }

        m_data->m_mutex.lock();
    }

    template<typename T> void MultiThreadPtr<T>::Unlock() const {
        if (!Valid()) {
            return;
        }

        m_data->m_mutex.unlock();
    }
}

#endif //SR_ENGINE_MULTITHREADPTR_H
```


