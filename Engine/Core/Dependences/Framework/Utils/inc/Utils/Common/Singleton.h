//
// Created by Monika on 28.09.2021.
//

#ifndef GAMEENGINE_SINGLETON_H
#define GAMEENGINE_SINGLETON_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Breakpoint.h>
#include <Utils/Common/Stacktrace.h>

namespace SR_UTILS_NS {
    template<typename T> class Singleton;

    class SR_DLL_EXPORT SingletonManager : public NonCopyable {
    public:
        void** GetSingleton(uint64_t id) noexcept;

    private:
        std::unordered_map<uint64_t, void*> m_singletons;

    };

    SR_DLL_EXPORT SingletonManager* GetSingletonManager() noexcept;

    template<typename T> class SR_DLL_EXPORT Singleton : public NonCopyable {
    protected:
        Singleton() = default;
        ~Singleton() override = default;

    public:
        SR_MAYBE_UNUSED static bool IsSingletonInitialized() noexcept {
            return GetSingleton() != nullptr;
        }

        SR_MAYBE_UNUSED static void DestroySingleton() {
            auto&& singleton = GetSingleton();

            if (!(*singleton)) {
                return;
            }

            if (!(*singleton)->IsSingletonCanBeDestroyed()) {
                std::cerr << "Singleton can't be destroyed!\n";
                std::cerr << GetStacktrace() << std::endl;
                SR_MAKE_BREAKPOINT;
                return;
            }

            (*singleton)->OnSingletonDestroy();

            delete *singleton;
            (*singleton) = nullptr;
        }

        SR_MAYBE_UNUSED static T& Instance() noexcept {
            auto&& singleton = GetSingleton();

            if (!(*singleton)) {
                *singleton = new T();
                (*singleton)->InitSingleton();
            }

            return *static_cast<T*>(*singleton);
        }

        SR_MAYBE_UNUSED static void LockSingleton() {
            if (auto&& singleton = GetSingleton()) {
                if (!(*singleton)) {
                    *singleton = new T();
                    (*singleton)->InitSingleton();
                }

                (*singleton)->m_mutex.lock();
            }
        }

        SR_MAYBE_UNUSED static void UnlockSingleton() {
            if (auto&& singleton = GetSingleton()) {
                if (!(*singleton)) {
                    std::cerr << "Singleton isn't initialized!\n";
                    std::cerr << GetStacktrace() << std::endl;
                    SR_MAKE_BREAKPOINT;
                    return;
                }

                (*singleton)->m_mutex.unlock();
            }
        }

    protected:
        virtual void OnSingletonDestroy() { }
        virtual void InitSingleton() { }
        virtual bool IsSingletonCanBeDestroyed() const { return true; }

    private:
        static Singleton<T>** GetSingleton() noexcept {
            void** p = GetSingletonManager()->GetSingleton(typeid(Singleton<T>).hash_code());
            return reinterpret_cast<Singleton<T>**>(p);
        }

    protected:
        mutable std::recursive_mutex m_mutex;

    };
}

#endif //GAMEENGINE_SINGLETON_H
