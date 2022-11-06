//
// Created by Monika on 23.08.2022.
//

#ifndef SRENGINE_SHAREDPTR_H
#define SRENGINE_SHAREDPTR_H

#include <Utils/Common/StringFormat.h>
#include <Utils/Types/Function.h>

namespace SR_HTYPES_NS {
    template<class T> class SR_DLL_EXPORT SharedPtr {
    public:
        SharedPtr() = default;
        explicit SharedPtr(T *ptr);
        SharedPtr(SharedPtr const &ptr);
        SharedPtr(SharedPtr&& ptr) noexcept
            : m_ptr(std::exchange(ptr.m_ptr, { }))
            , m_data(std::exchange(ptr.m_data, { }))
        { }
        ~SharedPtr(); /// не должен быть виртуальным

    public:
        SR_NODISCARD SR_FORCE_INLINE operator bool() const noexcept { return m_data && m_data->m_valid; }
        SharedPtr<T> &operator=(const SharedPtr<T> &ptr);
        SharedPtr<T> &operator=(T *ptr);
        SharedPtr<T> & operator=(SharedPtr<T>&& ptr) noexcept {
            m_data = std::exchange(ptr.m_data, {});
            m_ptr = std::exchange(ptr.m_ptr, {});
            return *this;
        }
        SR_NODISCARD SR_FORCE_INLINE T *operator->() const noexcept { return m_ptr; }
        SR_NODISCARD SR_INLINE bool operator==(const SharedPtr<T>& right) const noexcept {
            return m_ptr == right.m_ptr;
        }
        SR_NODISCARD SR_INLINE bool operator!=(const SharedPtr<T>& right) const noexcept {
            return m_ptr != right.m_ptr;
        }
        template<typename U> U DynamicCast() {
            if constexpr (std::is_same_v<T, void>) {
                return nullptr;
            }
            else {
                return dynamic_cast<U>(m_ptr);
            }
        }

        template<typename U> U ReinterpretCast() {
            return reinterpret_cast<U>(m_ptr);
        }

        SR_NODISCARD SR_FORCE_INLINE T* Get() const noexcept { return m_ptr; }
        SR_NODISCARD SR_FORCE_INLINE void* GetRawPtr() const noexcept { return (void*)m_ptr; }
        SR_NODISCARD SharedPtr<T> GetThis() {
            return SharedPtr<T>(*this);
        }
        SR_NODISCARD SR_FORCE_INLINE bool Valid() const noexcept { return m_data && m_data->m_valid; }

        bool AutoFree(const std::function<void(T *ptr)> &freeFun);

        /// Оставляем методы для совместимости с SafePtr
        void Replace(const SharedPtr &ptr);
        SR_NODISCARD SR_FORCE_INLINE bool RecursiveLockIfValid() const noexcept;
        SR_NODISCARD SR_FORCE_INLINE bool TryRecursiveLockIfValid() const noexcept;
        SR_FORCE_INLINE void Unlock() const noexcept { /** nothing */  }

    private:
        bool FreeImpl(const std::function<void(T *ptr)> &freeFun);

    private:
        struct dynamic_data {
            uint32_t m_useCount {};
            bool m_valid {};
        }* m_data = nullptr;
        T* m_ptr = nullptr;
    };

    template<class T> SharedPtr<T>::SharedPtr(T *ptr) {
        m_data = new dynamic_data {
            1,                  /// m_useCount
            (bool)(m_ptr = ptr) /// m_valid
        };
    }

    template<class T> SharedPtr<T>::SharedPtr(const SharedPtr &ptr) {
        m_ptr = ptr.m_ptr;
        if ((m_data = ptr.m_data)) {
            ++(m_data->m_useCount);
        }
    }

    template<class T> SharedPtr<T>::~SharedPtr() {
        if (m_data && m_data->m_useCount <= 1) {
            SR_SAFE_PTR_ASSERT(!m_data->m_valid, "Ptr was not freed!");
            delete m_data;
        }
        else if (m_data) {
            --(m_data->m_useCount);
        }
    }

    template<class T> SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &ptr) {
        if (m_data && m_data->m_useCount <= 1) {
            SR_SAFE_PTR_ASSERT(!m_data->m_valid, "Ptr was not freed!");
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

    template<class T> SharedPtr<T> &SharedPtr<T>::operator=(T *ptr) {
        if (m_ptr != ptr) {
            if (m_data && m_data->m_useCount <= 1) {
                SR_SAFE_PTR_ASSERT(!m_data->m_valid, "Ptr was not freed!");
                delete m_data;
            }
            else if (m_data) {
                --(m_data->m_useCount);
            }

            bool isInherit = false;

            if constexpr (!std::is_same_v<T, void>) {
                if (auto &&inherit = dynamic_cast<SharedPtr<T> *>(ptr)) {
                    SR_SAFE_PTR_ASSERT(m_data, "Inherit ptr data invalid!");
                    if ((m_data = inherit->m_data)) {
                        ++(m_data->m_useCount);
                    }
                    isInherit = true;
                }
            }

            if (!isInherit) {
                m_data = new dynamic_data{
                        1,     /// m_useCount
                        false, /// m_valid
                };
            }
        }

        if (m_data) {
            m_data->m_valid = (bool)(m_ptr = ptr);
        }

        return *this;
    }

    template<typename T> bool SharedPtr<T>::AutoFree(const std::function<void(T *)> &freeFun) {
        SharedPtr<T> ptrCopy = SharedPtr<T>(*this);
        /// после вызова FreeImpl this может потенциально инвалидироваться!

        return ptrCopy.Valid() ? ptrCopy.FreeImpl(freeFun) : false;
    }

    template<typename T> bool SharedPtr<T>::FreeImpl(const std::function<void(T *ptr)> &freeFun) {
        if (m_data && m_data->m_valid) {
            freeFun(m_ptr);
            m_data->m_valid = false;
            m_ptr = nullptr;
            return true;
        } else {
            return false;
        }
    }

    template<class T> void SharedPtr<T>::Replace(const SharedPtr &ptr) {
        if (ptr.m_ptr == m_ptr && ptr.m_data == m_data) {
            return;
        }

        SharedPtr copy = *this;
        *this = ptr;
    }

    template<class T> bool SharedPtr<T>::RecursiveLockIfValid() const noexcept {
        return m_data && m_data->m_valid;
    }

    template<class T> bool SharedPtr<T>::TryRecursiveLockIfValid() const noexcept {
        return m_data && m_data->m_valid;
    }
}

namespace std {
    template<typename T> struct hash<SR_HTYPES_NS::SharedPtr<T>> {
        size_t operator()(SR_HTYPES_NS::SharedPtr<T> const& ptr) const {
            return std::hash<void*>()(ptr.GetRawPtr());
        }
    };

    template <typename T> struct less<SR_HTYPES_NS::SharedPtr<T>> {
        bool operator()(const SR_HTYPES_NS::SharedPtr<T> &lhs, const SR_HTYPES_NS::SharedPtr<T> &rhs) const {
            void* a = lhs.GetRawPtr();
            void* b = rhs.GetRawPtr();
            return a < b;
        }
    };
}

#endif //SRENGINE_SHAREDPTR_H
