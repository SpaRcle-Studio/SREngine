

# File List.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**List.h**](List_8h.md)

[Go to the documentation of this file](List_8h.md)


```C++
//
// Created by Nikita on 04.03.2021.
//

#ifndef SR_ENGINE_LIST_H
#define SR_ENGINE_LIST_H

#include <Utils/Debug.h>

namespace SR_HTYPES_NS {
    template <typename T> class List {
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


