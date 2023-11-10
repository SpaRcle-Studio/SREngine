//
// Created by Monika on 28.09.2021.
//

#ifndef SR_ENGINE_SINGLETON_H
#define SR_ENGINE_SINGLETON_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Breakpoint.h>
#include <Utils/Common/Stacktrace.h>

#include <Utils/Types/SafePtrLockGuard.h>
#include <Utils/Types/Map.h>

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
        virtual void OnSingletonDestroy() { }
        virtual void InitSingleton() { }
        virtual bool IsSingletonCanBeDestroyed() const { return true; }

    protected:
        mutable std::recursive_mutex m_mutex;

    };

    class SR_DLL_EXPORT SingletonManager : public NonCopyable {
    public:
        void* GetSingleton(uint64_t id) noexcept;
        void DestroyAll();
        void Remove(uint64_t id);

        template<typename T> void Register(uint64_t id, const std::string& name, Singleton<T>* pSingleton) {
            m_singletons[id].pSingleton = (void*)pSingleton;
            m_singletons[id].pSingletonBase = dynamic_cast<SingletonBase*>(pSingleton);
            m_singletons[id].name = name;
        }

    private:
        struct SingletonInfo {
            std::string name;
            void* pSingleton = nullptr;
            SingletonBase* pSingletonBase = nullptr;
        };
        std::unordered_map<uint64_t, SingletonInfo> m_singletons;

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
                GetSingletonManager()->Remove(typeid(Singleton<T>).hash_code());
                delete pSingleton;
            }
        }

        /// TODO: это не потокобезопасно, нужно переделать
        SR_MAYBE_UNUSED static T& Instance() noexcept {
            auto&& pSingleton = GetSingleton();

            if (!pSingleton) {
                pSingleton = new T();
                GetSingletonManager()->Register<T>(GetSingletonId(), typeid(Singleton<T>).name(), pSingleton);
                pSingleton->InitSingleton();
                return *static_cast<T*>(pSingleton);
            }

            return *static_cast<T*>(pSingleton);
        }

        SR_MAYBE_UNUSED static uint64_t GetSingletonId() {
            return typeid(Singleton<T>).hash_code();
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
            void* p = GetSingletonManager()->GetSingleton(GetSingletonId());
            return reinterpret_cast<Singleton<T>*>(p);
        }
    };
}

#endif //SR_ENGINE_SINGLETON_H
