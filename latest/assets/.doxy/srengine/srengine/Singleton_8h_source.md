

# File Singleton.h

[**File List**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**Singleton.h**](Singleton_8h.md)

[Go to the documentation of this file](Singleton_8h.md)


```C++
//
// Created by Monika on 28.09.2021.
//

#ifndef SR_ENGINE_SINGLETON_H
#define SR_ENGINE_SINGLETON_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Breakpoint.h>

#include <Utils/Platform/Stacktrace.h>

#include <Utils/Types/StringAtom.h>
#include <Utils/Types/SafePtrLockGuard.h>
#include <Utils/Types/Map.h>

#define SR_REGISTER_SINGLETON(className)                                                                                \
    private:                                                                                                            \
        friend class SR_UTILS_NS::Singleton<className>;                                                                 \
        static SR_UTILS_NS::StringAtom GetStaticSingletonName() {                                                       \
            static SR_UTILS_NS::StringAtom staticSingletonName = #className;                                            \
            return staticSingletonName;                                                                                 \
        }                                                                                                               \
        SR_UTILS_NS::StringAtom GetSingletonName() const noexcept final { return GetStaticSingletonName(); };           \

#define SR_REGISTER_TEMPLATE_SINGLETON(className, T)                                                                    \
    private:                                                                                                            \
        friend class SR_UTILS_NS::Singleton<className>;                                                                 \
                                               \
        SR_NODISCARD static SR_UTILS_NS::StringAtom GetStaticTemplatedSingletonName() noexcept {                        \
            return SR_FORMAT("{}<{}>", #className, typeid(T).name());                                                   \
        }                                                                                                               \
        static SR_UTILS_NS::StringAtom GetStaticSingletonName() { return GetStaticTemplatedSingletonName(); }           \
        SR_UTILS_NS::StringAtom GetSingletonName() const noexcept final { return GetStaticSingletonName(); };           \

namespace SR_UTILS_NS {
    class SingletonManager;
    template<typename T> class Singleton;

    class SR_COMMON_DLL_API SingletonBase : public NonCopyable  {
        friend class SingletonManager;
    public:
        ~SingletonBase() override;

    protected:
        SingletonBase();

    protected:
        virtual StringAtom GetSingletonName() const noexcept = 0;
        virtual void OnSingletonDestroy();
        virtual void InitSingleton();
        virtual bool IsSingletonCanBeDestroyed() const;

    protected:
        mutable std::recursive_mutex m_mutex;

    };

    class SR_COMMON_DLL_API SingletonManager : public NonCopyable {
    public:
        void* GetSingleton(StringAtom name) noexcept;
        std::recursive_mutex& GetCreationMutex(StringAtom name);
        void DestroyAll();
        void Remove(StringAtom name);

        template<typename T> void Register(Singleton<T>* pSingleton);

    private:
        struct SingletonInfo {
            StringAtom name;
            void* pSingleton = nullptr;
            SingletonBase* pSingletonBase = nullptr;
        };
        ska::flat_hash_map<StringAtom, SingletonInfo> m_singletons;
        mutable std::recursive_mutex m_mutex;
        std::map<StringAtom, std::recursive_mutex> m_creationMutexes;

    };

    SR_COMMON_DLL_API SingletonManager* GetSingletonManager() noexcept;

    template<typename T> class Singleton : public SingletonBase {
    protected:
        Singleton();
        ~Singleton() override = default;

    public:
        SR_MAYBE_UNUSED static T& Instance() noexcept;

        SR_MAYBE_UNUSED SR_NODISCARD static SR_HTYPES_NS::SingletonRecursiveLockGuard<Singleton<T>*> ScopeLockSingleton();
        SR_MAYBE_UNUSED static bool IsSingletonInitialized() noexcept;
        SR_MAYBE_UNUSED static void DestroySingleton();
        SR_MAYBE_UNUSED static void LockSingleton() noexcept;
        SR_MAYBE_UNUSED static void UnlockSingleton() noexcept;
        SR_MAYBE_UNUSED static std::recursive_mutex& GetMutex() noexcept;

    private:
        static Singleton<T>* GetSingleton() noexcept;

    };


    template<typename T> Singleton<T> *Singleton<T>::GetSingleton() noexcept {
        void* p = GetSingletonManager()->GetSingleton(T::GetStaticSingletonName());
        return reinterpret_cast<Singleton<T>*>(p);
    }

    template<typename T> std::recursive_mutex &Singleton<T>::GetMutex() noexcept {
        return Instance().m_mutex;
    }

    template<typename T> void Singleton<T>::UnlockSingleton() noexcept {
        if (auto&& pSingleton = GetSingleton()) {
            pSingleton->m_mutex.unlock();
        }
        else {
            std::cerr << "Singleton isn't initialized!\n";
            std::cerr << GetStacktrace() << std::endl;
            SR_MAKE_BREAKPOINT;
        }
    }

    template<typename T> void Singleton<T>::LockSingleton() noexcept {
        GetMutex().lock();
    }

    template<typename T> T &Singleton<T>::Instance() noexcept {
        auto&& pSingleton = GetSingleton();

        if (!pSingleton) {
            std::lock_guard lock(GetSingletonManager()->GetCreationMutex(T::GetStaticSingletonName()));

            pSingleton = GetSingleton();

            if (!pSingleton) {
                pSingleton = new T();
                GetSingletonManager()->Register<T>(pSingleton);
                pSingleton->InitSingleton();
                return *static_cast<T*>(pSingleton);
            }
        }

        return *static_cast<T*>(pSingleton);
    }

    template<typename T> void Singleton<T>::DestroySingleton() {
        if (auto&& pSingleton = GetSingleton()) {
            if (!pSingleton->IsSingletonCanBeDestroyed()) {
                return;
            }

            pSingleton->OnSingletonDestroy();
            GetSingletonManager()->Remove(T::GetStaticSingletonName());
            delete pSingleton;
        }
    }

    template<typename T> bool Singleton<T>::IsSingletonInitialized() noexcept {
        return GetSingleton();
    }

    template<typename T>
    Types::SingletonRecursiveLockGuard<Singleton<T> *> Singleton<T>::ScopeLockSingleton() {
        return SR_HTYPES_NS::SingletonRecursiveLockGuard<Singleton<T>*>(&Instance());
    }

    template<typename T> Singleton<T>::Singleton()
        : SingletonBase()
    {
        if (GetSingleton()) {
            std::cerr << "Singleton already exists!\n";
            std::cerr << GetStacktrace() << std::endl;
            SR_MAKE_BREAKPOINT;
        }
    }

    template<typename T> void SingletonManager::Register(Singleton<T> *pSingleton) {
        std::lock_guard lock(m_mutex);
        auto&& name = pSingleton->GetSingletonName();

        m_singletons[name].pSingleton = (void*)pSingleton;
        m_singletons[name].pSingletonBase = dynamic_cast<SingletonBase*>(pSingleton);
        m_singletons[name].name = name;
    }
}

#endif //SR_ENGINE_SINGLETON_H
```


