//
// Created by Monika on 28.09.2021.
//

#ifndef GAMEENGINE_SINGLETON_H
#define GAMEENGINE_SINGLETON_H

#include <Utils/Common/NonCopyable.h>

namespace SR_UTILS_NS {
    template<typename T> class SR_DLL_EXPORT Singleton : public NonCopyable {
    public:
        static void Destroy();

        static T& Instance();

    public:
        static void LockSingleton();
        static void UnlockSingleton();

    protected:
        static T* m_instance;
        static std::recursive_mutex m_mutex;

        Singleton() { m_instance = static_cast <T*> (this); };
        ~Singleton() override = default;

        virtual void OnSingletonDestroy() { }
    };

    template<typename T> T* Singleton<T>::m_instance = 0;
    template<typename T> std::recursive_mutex Singleton<T>::m_mutex = std::recursive_mutex();

    template<typename T> T& Singleton<T>::Instance() {
        if(!m_instance)
            Singleton<T>::m_instance = new T();

        return *m_instance;
    }

    template<typename T> void Singleton<T>::Destroy() {
        if (!m_instance) {
            return;
        }
        m_instance->OnSingletonDestroy();
        delete Singleton<T>::m_instance;
        Singleton<T>::m_instance = 0;
    }

    template<typename T> void Singleton<T>::LockSingleton() {
        m_mutex.lock();
    }

    template<typename T> void Singleton<T>::UnlockSingleton() {
        m_mutex.unlock();
    }
}

#endif //GAMEENGINE_SINGLETON_H
