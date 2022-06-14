//
// Created by Nikita on 04.03.2021.
//

#ifndef GAMEENGINE_LIST_H
#define GAMEENGINE_LIST_H

#include <Utils/Debug.h>

namespace SR_HTYPES_NS {
    template <typename T> class SR_DLL_EXPORT List {
    private:
        std::vector<T> self = std::vector<T>();
        std::mutex m_mutex = std::mutex();
    public:
        List() {

        }

        List(List& list) {
            this->self = list.self;
        }

        List(const List& list) {
            this->self = list.self;
        }

        explicit List(std::vector<T> list) {
            this->self = list;
        }

        ~List() {
            //m_mutex.lock();
            //self.clear();
            //m_mutex.unlock();
        }
    public:
        [[nodiscard]] inline size_t Size() const {
            return self.size();
        }

        inline const T &operator[](size_t id) const {
            return self[id];
        }

        inline T &operator[](size_t id) {
            return self[id];
        }

        [[nodiscard]] inline T Get(unsigned int id) {
            //std::cout << self.size() << std::endl;
            //std::cout << id << std::endl;
            m_mutex.lock();
            T t = self[id];
            m_mutex.unlock();
            return t;
        }

        inline void Set(unsigned int id, T value) {
            m_mutex.lock();
            self[id] = value;
            m_mutex.unlock();
        }

        inline void PushBack(T value) {
            m_mutex.lock();
            self.push_back(value);
            m_mutex.unlock();
        }
    };
}

#endif //GAMEENGINE_LIST_H
