

# File Stack.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**Stack.h**](Stack_8h.md)

[Go to the documentation of this file](Stack_8h.md)


```C++
//
// Created by Monika on 23.04.2024.
//

#ifndef SR_ENGINE_UTILS_STACK_H
#define SR_ENGINE_UTILS_STACK_H

#include <Utils/Platform/Platform.h>
#include <Utils/Common/NonCopyable.h>

namespace SR_HTYPES_NS {
    template<typename T> class Stack {
        struct Node : SR_UTILS_NS::NonCopyable {
            explicit Node(T&& data)
                : data(std::move(data))
            { }

            explicit Node(const T& data)
                : data(data)
            { }

            T data;
            Node* pData = nullptr;
        };

    public:
        Stack() = default;

        Stack(const Stack& other) {
            Node* pOther = other.m_head;
            while (pOther) {
                Push(pOther->data);
                pOther = pOther->pData;
            }
        }

        Stack(Stack&& other) noexcept {
            m_head = std::exchange(other.m_head, nullptr);
            m_size = std::exchange(other.m_size, 0);
        }

        Stack& operator=(const Stack& other) {
            if (this == &other) {
                return *this;
            }
            Clear();
            Node* pOther = other.m_head;
            while (pOther) {
                Push(pOther->data);
                pOther = pOther->pData;
            }
            return *this;
        }

        Stack& operator=(Stack&& other) noexcept {
            if (this == &other) {
                return *this;
            }
            Clear();
            m_head = std::exchange(other.m_head, nullptr);
            m_size = std::exchange(other.m_size, 0);
            return *this;
        }

        ~Stack() {
            Clear();
        }

        void Clear() {
            while (m_head) {
                Node* pNext = m_head->pData;
                delete m_head;
                m_head = pNext;
            }
            m_size = 0;
        }

        SR_NODISCARD uint64_t Size() const noexcept {
            return m_size;
        }

        SR_NODISCARD bool IsEmpty() const noexcept {
            return m_size == 0;
        }

        void Push(T&& value) {
            Node* pNew = new Node(std::move(value));
            pNew->pData = m_head;
            m_head = pNew;
            ++m_size;
        }

        void Push(const T& value) {
            Node* pNew = new Node(value);
            pNew->pData = m_head;
            m_head = pNew;
            ++m_size;
        }

        T Pop() {
            if (!m_head) {
                SR_PLATFORM_NS::WriteConsoleError("Stack is empty!");
                SR_UTILS_NS::Breakpoint();
            }

            Node* pNext = m_head->pData;
            T data = std::move(m_head->data);
            delete m_head;
            m_head = pNext;
            --m_size;
            return data;
        }

        SR_NODISCARD T& Top() {
            if (!m_head) {
                SR_PLATFORM_NS::WriteConsoleError("Stack is empty!");
                SR_UTILS_NS::Breakpoint();
            }
            return m_head->data;
        }

    private:
        Node* m_head = nullptr;
        uint64_t m_size = 0;

    };
}

#endif //SR_ENGINE_UTILS_STACK_H
```


