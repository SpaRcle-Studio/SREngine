//
// Created by Monika on 23.08.2022.
//

#ifndef SR_ENGINE_SHAREDPTR_H
#define SR_ENGINE_SHAREDPTR_H

#include <Utils/Common/StringFormat.h>
#include <Utils/Types/Function.h>
#include <Utils/Common/TypeInfo.h>
#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    enum class SharedPtrPolicy : uint8_t {
        Automatic, Manually
    };
}

namespace SR_HTYPES_NS {
    struct SharedPtrDynamicData {
        SharedPtrDynamicData(uint16_t strongCount, uint16_t weakCount, bool valid, SharedPtrPolicy policy)
            : strongCount(strongCount)
            , weakCount(weakCount)
            , valid(valid)
            , policy(policy)
        { }

        uint16_t strongCount = 0;
        uint16_t weakCount = 0;
        bool valid = false;
        SharedPtrPolicy policy = SharedPtrPolicy::Automatic;

    };

    template<class T> class SR_DLL_EXPORT SharedPtr {
    public:
        SharedPtr() = default;
        SharedPtr(const T* constPtr); /** NOLINT */
        SharedPtr(const T* constPtr, SharedPtrPolicy policy); /** NOLINT */
        SharedPtr(SharedPtr const &ptr);
        SharedPtr(SharedPtr&& ptr) noexcept
            : m_data(SR_UTILS_NS::Exchange(ptr.m_data, { }))
            , m_ptr(SR_UTILS_NS::Exchange(ptr.m_ptr, { }))
        { }
        ~SharedPtr(); /// не должен быть виртуальным

    public:
        template<typename... Args> SR_NODISCARD static SharedPtr<T> MakeShared(Args&&... args) {
            auto&& pData = new T(std::forward<Args>(args)...);
            return pData->GetThis();
        }

        SR_NODISCARD SR_FORCE_INLINE operator bool() const noexcept { return m_data && m_data->valid; } /** NOLINT */
        SharedPtr<T>& operator=(const SharedPtr<T> &ptr);
        SharedPtr<T>& operator=(T *ptr);
        SharedPtr<T>& operator=(SharedPtr<T>&& ptr) noexcept {
            if (m_data) {
                SRAssert(m_data->strongCount > 0);
                --m_data->strongCount;
            }

            m_data = SR_UTILS_NS::Exchange(ptr.m_data, {});

            if (m_data) {
                ++m_data->strongCount;
            }

            m_ptr = SR_UTILS_NS::Exchange(ptr.m_ptr, {});

            return *this;
        }
        SR_NODISCARD SR_FORCE_INLINE T& operator*() const noexcept { return *m_ptr; }
        SR_NODISCARD SR_FORCE_INLINE T* operator->() const noexcept { return m_ptr; }
        SR_NODISCARD SR_INLINE bool operator==(const SharedPtr<T>& right) const noexcept {
            return m_ptr == right.m_ptr;
        }
        SR_NODISCARD SR_INLINE bool operator!=(const SharedPtr<T>& right) const noexcept {
            return m_ptr != right.m_ptr;
        }
        template<typename U> SharedPtr<U> DynamicCast() const {
            if constexpr (std::is_same_v<T, void>) {
                return SharedPtr<U>();
            }
            return SharedPtr<U>(dynamic_cast<U*>(m_ptr));
        }

        template<typename U> U ReinterpretCast() {
            return reinterpret_cast<U>(m_ptr);
        }

        SR_NODISCARD SR_FORCE_INLINE T* Get() const noexcept { return m_ptr; }
        SR_NODISCARD SR_FORCE_INLINE SharedPtrDynamicData* GetPtrData() const noexcept { return m_data; }
        SR_NODISCARD SR_FORCE_INLINE void* GetRawPtr() const noexcept { return (void*)m_ptr; }
        SR_NODISCARD SharedPtr<T> GetThis() const {
            return *this;
        }
        SR_NODISCARD SR_FORCE_INLINE bool Valid() const noexcept { return m_data && m_data->valid; }

        bool AutoFree(const SR_HTYPES_NS::Function<void(T *ptr)>& freeFun);
        bool AutoFree();

        /// Оставляем методы для совместимости с SafePtr
        void Replace(const SharedPtr &ptr);
        void Reset();
        SR_NODISCARD SR_FORCE_INLINE bool RecursiveLockIfValid() const noexcept;
        SR_NODISCARD SR_FORCE_INLINE bool TryRecursiveLockIfValid() const noexcept;
        SR_FORCE_INLINE void Unlock() const noexcept { /** nothing */  }

    private:
        bool FreeImpl(const SR_HTYPES_NS::Function<void(T *ptr)> &freeFun);

    private:
        SharedPtrDynamicData* m_data = nullptr;
        T* m_ptr = nullptr;

    };

    template<class T> SharedPtr<T>::SharedPtr(const T* constPtr)
        : SharedPtr(constPtr, SharedPtrPolicy::Automatic)
    { }

    template<class T> SharedPtr<T>::SharedPtr(const T* constPtr, SharedPtrPolicy policy) {
        T* ptr = const_cast<T*>(constPtr);
        bool needAlloc = true;

        if constexpr (IsDerivedFrom<SharedPtr, T>::value) {
            if (ptr && (m_data = ptr->GetPtrData())) {
                ++(m_data->strongCount);
                needAlloc = false;
                m_ptr = ptr;
            }
        }

        if (needAlloc && ptr) {
            m_data = new SharedPtrDynamicData(
                1,                   /// strong
                0,                   /// weak
                (bool)(m_ptr = ptr), /// valid
                policy               /// policy
            );
        }
    }

    template<class T> SharedPtr<T>::SharedPtr(const SharedPtr &ptr) {
        m_ptr = ptr.m_ptr;
        if ((m_data = ptr.m_data)) {
            ++(m_data->strongCount);
        }
    }

    template<class T> SharedPtr<T>::~SharedPtr() {
        Reset();
    }

    template<class T> SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T> &ptr) {
        Reset();

        m_ptr = ptr.m_ptr;

        if ((m_data = ptr.m_data)) {
            m_data->valid = bool(m_ptr);
            ++(m_data->strongCount);
        }

        return *this;
    }

    template<class T> SharedPtr<T>& SharedPtr<T>::operator=(T *ptr) {
        if (m_ptr != ptr) {
            Reset();

            bool needAlloc = true;

            if constexpr (IsDerivedFrom<SharedPtr, T>::value) {
                if (ptr && (m_data = ptr->GetPtrData())) {
                    ++(m_data->strongCount);
                    needAlloc = false;
                    m_ptr = ptr;
                }
                else if (ptr) {
                    SR_SAFE_PTR_ASSERT(false, "Class was inherit, but not initialized!");
                }
            }

            if (needAlloc && ptr) {
                m_data = new SharedPtrDynamicData(
                    1,    /// strong
                    0,    /// weak
                    true, /// valid
                    SharedPtrPolicy::Automatic /// policy
                );
            }
        }

        m_ptr = ptr;

        if (m_data) {
            m_data->valid = bool(m_ptr);
        }

        return *this;
    }

    template<typename T> bool SharedPtr<T>::AutoFree(const SR_HTYPES_NS::Function<void(T *ptr)> &freeFun) {
        SharedPtr<T> ptrCopy = SharedPtr<T>(*this);
        /// после вызова FreeImpl this может потенциально инвалидироваться!

        return ptrCopy.Valid() ? ptrCopy.FreeImpl(freeFun) : false;
    }

    template<typename T> bool SharedPtr<T>::AutoFree() {
        SharedPtr<T> ptrCopy = SharedPtr<T>(*this);
        /// после вызова FreeImpl this может потенциально инвалидироваться!

        return ptrCopy.Valid() ? ptrCopy.FreeImpl([](auto&& pData) { delete pData; }) : false;
    }

    template<typename T> bool SharedPtr<T>::FreeImpl(const SR_HTYPES_NS::Function<void(T *ptr)> &freeFun) {
        if (m_data && m_data->valid) {
            freeFun(m_ptr);
            m_data->valid = false;
            m_ptr = nullptr;
            return true;
        }
        else {
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
        return m_data && m_data->valid;
    }

    template<class T> bool SharedPtr<T>::TryRecursiveLockIfValid() const noexcept {
        return m_data && m_data->valid;
    }

    template<class T> void SharedPtr<T>::Reset() {
        /// Делаем копию, так как в процессе удаления можем потярять this,
        /// а так же зануляем m_data, чтобы не войти в рекурсию
        SharedPtrDynamicData* pData = m_data;
        T* pPtr = m_ptr;
        m_data = nullptr;
        m_ptr = nullptr;

        if (!pData) {
            return;
        }

        if (pData->strongCount <= 1) {
            pData->strongCount = 0;

            if (pData->policy == SharedPtrPolicy::Manually) {
                SR_SAFE_PTR_ASSERT(!pData->valid, "Ptr was not freed!");
                delete pData;
                return;
            }
            else if (pData->policy == SharedPtrPolicy::Automatic && pData->valid) {
                pData->valid = false;
                SR_SAFE_DELETE_PTR(pPtr);
            }

            if (pData->weakCount == 0) {
                delete pData;
            }
        }
        else {
            --(pData->strongCount);
        }
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

#endif //SR_ENGINE_SHAREDPTR_H
