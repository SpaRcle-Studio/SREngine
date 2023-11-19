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

#define SR_REGISTER_SINGLETON(name)                                                                                     \
    private:                                                                                                            \
        friend class SR_UTILS_NS::Singleton<name>;                                                                      \
        static SR_UTILS_NS::StringAtom GetStaticSingletonName() {                                                       \
            static SR_UTILS_NS::StringAtom staticSingletonName = #name;                                                 \
            return staticSingletonName;                                                                                 \
        }                                                                                                               \
        SR_UTILS_NS::StringAtom GetSingletonName() const noexcept final { return GetStaticSingletonName(); };           \

namespace SR_UTILS_NS {
    class SingletonManager;
    template<typename T> class Singleton;

    class SR_DLL_EXPORT SingletonBase : public NonCopyable  {
        friend class SingletonManager;
    public:
        ~SingletonBase() override = default;

    protected:
        SingletonBase() = default;

    protected:
        virtual StringAtom GetSingletonName() const noexcept = 0;
        virtual void OnSingletonDestroy() { }
        virtual void InitSingleton() { }
        virtual bool IsSingletonCanBeDestroyed() const { return true; }

    protected:
        mutable std::recursive_mutex m_mutex;

    };

    class SR_DLL_EXPORT SingletonManager : public NonCopyable {
    public:
        void* GetSingleton(StringAtom name) noexcept;
        std::recursive_mutex& GetMutex() noexcept { return m_mutex; }
        void DestroyAll();
        void Remove(StringAtom name);

        template<typename T> void Register(Singleton<T>* pSingleton) {
            std::lock_guard lock(m_mutex);
            auto&& name = pSingleton->GetSingletonName();

            m_singletons[name].pSingleton = (void*)pSingleton;
            m_singletons[name].pSingletonBase = dynamic_cast<SingletonBase*>(pSingleton);
            m_singletons[name].name = name;
        }

    private:
        struct SingletonInfo {
            StringAtom name;
            void* pSingleton = nullptr;
            SingletonBase* pSingletonBase = nullptr;
        };
        ska::flat_hash_map<StringAtom, SingletonInfo> m_singletons;
        mutable std::recursive_mutex m_mutex;

    };

    SR_DLL_EXPORT SingletonManager* GetSingletonManager() noexcept;

    template<typename T> class SR_DLL_EXPORT Singleton : public SingletonBase {
    protected:
        Singleton()
            : SingletonBase()
        {
            if (GetSingleton()) {
                std::cerr << "Singleton already exists!\n";
                std::cerr << GetStacktrace() << std::endl;
                SR_MAKE_BREAKPOINT;
            }
        }

        ~Singleton() override = default;

    public:
        SR_MAYBE_UNUSED static SR_HTYPES_NS::SingletonRecursiveLockGuard<Singleton<T>*> ScopeLockSingleton() {
            return SR_HTYPES_NS::SingletonRecursiveLockGuard<Singleton<T>*>(&Instance());
        }

        SR_MAYBE_UNUSED static bool IsSingletonInitialized() noexcept {
            return GetSingleton();
        }

        SR_MAYBE_UNUSED static void DestroySingleton() {
            if (auto&& pSingleton = GetSingleton()) {
                if (!pSingleton->IsSingletonCanBeDestroyed()) {
                    return;
                }

                pSingleton->OnSingletonDestroy();
                GetSingletonManager()->Remove(T::GetStaticSingletonName());
                delete pSingleton;
            }
        }

        /// TODO: (Multi-threading) Refactor Singleton::Instance().
        SR_MAYBE_UNUSED static T& Instance() noexcept {
            auto&& pSingleton = GetSingleton();

            if (!pSingleton) {
                pSingleton = new T();
                GetSingletonManager()->Register<T>(pSingleton);
                pSingleton->InitSingleton();
                return *static_cast<T*>(pSingleton);
            }

            return *static_cast<T*>(pSingleton);
        }

        SR_MAYBE_UNUSED static void LockSingleton() noexcept {
            GetMutex().lock();
        }

        SR_MAYBE_UNUSED static void UnlockSingleton() noexcept {
            if (auto&& pSingleton = GetSingleton()) {
                pSingleton->m_mutex.unlock();
            }
            else {
                std::cerr << "Singleton isn't initialized!\n";
                std::cerr << GetStacktrace() << std::endl;
                SR_MAKE_BREAKPOINT;
            }
        }

        SR_MAYBE_UNUSED static std::recursive_mutex& GetMutex() noexcept {
            return Instance().m_mutex;
        }

    private:
        static Singleton<T>* GetSingleton() noexcept {
            void* p = GetSingletonManager()->GetSingleton(T::GetStaticSingletonName());
            return reinterpret_cast<Singleton<T>*>(p);
        }
    };
}

#endif //SR_ENGINE_SINGLETON_H
