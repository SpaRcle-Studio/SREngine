

# File List.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**List.h**](List_8h.md)

[Go to the documentation of this file](List_8h.md)


```C++
//
// Created by Nikita on 04.03.2021.
//

#ifndef SR_ENGINE_LIST_H
#define SR_ENGINE_LIST_H

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

#endif //SR_ENGINE_LIST_H
```


