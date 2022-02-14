//
// Created by Monika on 28.09.2021.
//

#ifndef GAMEENGINE_SINGLETON_H
#define GAMEENGINE_SINGLETON_H

namespace Framework::Helper {
    template<typename T>
    class Singleton {
    public:
        static void Destroy();

        static T& Instance();

    private:
        Singleton(Singleton const&) = default;
        Singleton& operator=(Singleton const&) { };

    protected:
        static T* m_instance;

        Singleton() { m_instance = static_cast <T*> (this); };
        virtual ~Singleton() = default;

        virtual void OnSingletonDestroy() { }
    };

    template<typename T> T* Singleton<T>::m_instance = 0;

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
}

#endif //GAMEENGINE_SINGLETON_H
