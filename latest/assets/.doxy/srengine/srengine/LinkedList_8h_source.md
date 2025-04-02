

# File LinkedList.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**LinkedList.h**](LinkedList_8h.md)

[Go to the documentation of this file](LinkedList_8h.md)


```C++
//
// Created by Monika on 19.02.2024.
//

#include <Utils/Types/Node.h>

#ifndef SR_UTILS_NETWORK_LISTS_LINKED_LIST_H
#define SR_UTILS_NETWORK_LISTS_LINKED_LIST_H

namespace SR_HTYPES_NS {
    template<typename T> class LinkedList : public SR_UTILS_NS::NonCopyable {
        using Comparator = std::function<uint32_t(T* pA, T* pB)>;
    public:
        LinkedList() = default;
        ~LinkedList() override = default;

    public:
        void Insert(uint64_t index, T* pData, uint64_t size);
        void Remove(uint64_t index);
        void Sort(const Comparator& comparator);

        uint64_t Search(T* pQuery, const Comparator& comparator);

        T* Retrieve(uint64_t index);

        SR_NODISCARD Node* Iterate(uint64_t index) const;

    private:
        Node* m_head = nullptr;
        uint64_t m_length = 0;

    };

    template<typename T> uint64_t LinkedList<T>::Search(T* pQuery, const Comparator& comparator) {
        int64_t position = m_length / 2;
        int64_t minChecked = 0;
        int64_t maxChecked = m_length;

        while (maxChecked > minChecked)
        {
            void* pData = Retrieve(position);

            if (compare(pData, pQuery) == 1) {
                maxChecked = position;

                if (position != (minChecked + position) / 2) {
                    position = (minChecked + position) / 2;
                }
                else {
                    break;
                }
            }
            else if (compare(pData, pQuery) == -1) {
                minChecked = position;

                if (position != (maxChecked + position) / 2) {
                    position = (maxChecked + position) / 2;
                }
                else {
                    break;
                }
            }
            else {
                return 1;
            }
        }

        return 0;
    }

    template<typename T> void LinkedList<T>::Sort(const Comparator& comparator) {

        for (uint64_t i = 0; i < m_length; ++i) {
            Node* pCursor = m_head;

            for (uint64_t j = 0; j < m_length - 1; ++j) {
                T* pA = static_cast<T*>(pCursor->pData);
                T* pB = static_cast<T*>(pCursor->pNext->pData);

                if (comparator(pA, pB) > 0) {
                    std::swap(pCursor->pData, pCursor->pNext->pData);
                }

                pCursor = pCursor->pNext;
            }
        }
    }

    template<typename T> T* LinkedList<T>::Retrieve(uint64_t index) {
        Node* pNode = Iterate(index);
        return pNode ? static_cast<T*>(pNode->pData) : nullptr;
    }

    template<typename T> void LinkedList<T>::Remove(uint64_t index) {
        if (index == 0) {
            Node* pNodeToRemove = m_head;

            if (pNodeToRemove) {
                m_head = pNodeToRemove->pNext;
                delete pNodeToRemove;
            }
        }
        else {
            Node* pCursor = Iterate(index - 1);
            Node* pNodeToRemove = pCursor->pNext;
            pCursor->pNext = pNodeToRemove->pNext;
            delete pNodeToRemove;
        }

        --m_length;
    }

    template<typename T> Node* LinkedList<T>::Iterate(uint64_t index) const {
        if (index >= m_length) {
            return nullptr;
        }

        Node* pCursor = m_head;

        for (uint64_t i = 0; i < index; ++i) {
            pCursor = pCursor->pNext;
        }

        return pCursor;
    }

    template<typename T> void LinkedList<T>::Insert(uint64_t index, T* pData, uint64_t size) {
        Node* pNewNode = new Node(pData, size);

        if (index == 0) {
            pNewNode->pNext = m_head;
            m_head = pNewNode;
        }
        else {
            Node* pCursor = Iterate(index - 1);
            pNewNode->pNext = pCursor->pNext;
            pCursor->pNext = pNewNode;
        }

        ++m_length;
    }
}

#endif //SR_UTILS_NETWORK_LISTS_LINKED_LIST_H
```


