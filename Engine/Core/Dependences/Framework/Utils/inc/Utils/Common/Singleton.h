//
// Created by Monika on 28.09.2021.
//

#ifndef GAMEENGINE_SINGLETON_H
#define GAMEENGINE_SINGLETON_H

#include <Utils/Common/NonCopyable.h>

namespace SR_UTILS_NS {
    template<typename T> class Singleton;

    class SR_DLL_EXPORT SingletonManager : public NonCopyable {
    public:
        void** GetSingleton(uint64_t id);

    private:
        std::unordered_map<uint64_t, void*> m_singletons;

    };

    SR_DLL_EXPORT SingletonManager* GetSingletonManager();

    template<typename T> class SR_DLL_EXPORT Singleton : public NonCopyable {
    protected:
        Singleton()
            : m_instance(nullptr)
        { }

        ~Singleton() override = default;

    public:
        SR_MAYBE_UNUSED static void Destroy() {
            auto&& singleton = GetSingleton();

            if (!(*singleton)) {
                return;
            }

            (*singleton)->InternalDestroy();

            delete *singleton;
            (*singleton) = nullptr;
        }

        SR_MAYBE_UNUSED static T& Instance() {
            auto&& singleton = GetSingleton();

            if (!(*singleton)) {
                *singleton = new Singleton<T>();
            }

            return (*singleton)->InternalInstance();
        }

        SR_MAYBE_UNUSED static void LockSingleton() {
            if (auto&& singleton = GetSingleton()) {
                (*singleton)->m_mutex.lock();
            }
        }

        SR_MAYBE_UNUSED static void UnlockSingleton() {
            if (auto&& singleton = GetSingleton()) {
                (*singleton)->m_mutex.unlock();
            }
        }

    protected:
        virtual void OnSingletonDestroy() { }

    private:
        static Singleton<T>** GetSingleton() {
            void** p = GetSingletonManager()->GetSingleton(typeid(Singleton<T>).hash_code());

            return reinterpret_cast<Singleton<T>**>(p);
        }

        T& InternalInstance() {
            if (!m_instance) {
                m_instance = new T();
            }

            return *m_instance;
        }

        void InternalDestroy() {
            if (!m_instance) {
                return;
            }

            m_instance->OnSingletonDestroy();

            delete m_instance;
            m_instance = nullptr;
        }

    protected:
        mutable std::recursive_mutex m_mutex;

    private:
        T* m_instance;

    };
}

#endif //GAMEENGINE_SINGLETON_H
