

# File BinarySearchTree.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**BinarySearchTree.h**](BinarySearchTree_8h.md)

[Go to the documentation of this file](BinarySearchTree_8h.md)


```C++
//
// Created by Monika on 19.02.2024.
//

#ifndef SR_UTILS_TYPES_BINARY_SEARCH_TREE_H
#define SR_UTILS_TYPES_BINARY_SEARCH_TREE_H

#include <Utils/Types/Node.h>

namespace SR_HTYPES_NS {
    template<typename T> class BinarySearchTree : public SR_UTILS_NS::NonCopyable {
        using Comparator = std::function<uint32_t(T* pA, T* pB)>;
    public:
        explicit BinarySearchTree(Comparator&& comparator)
            : m_comparator(std::move(comparator))
        { }

        SR_NODISCARD SR_FORCE_INLINE int32_t SR_FASTCALL Compare(T* pFirst, T* pSecond) const {
            return m_comparator(pFirst, pSecond);
        }

        SR_NODISCARD Node* Iterate(Node* pCursor, T* pData, int32_t* direction) const;
        SR_NODISCARD T* Search(T* pData) const;

        void Insert(T* pData, uint64_t size);

    private:
        Node* m_head = nullptr;
        Comparator m_comparator;

    };

    template<typename T> void BinarySearchTree<T>::Insert(T* pData, uint64_t size) {
        if (m_head == nullptr) {
            m_head = new Node(pData, size);
            return;
        }

        int32_t direction = 0;
        Node* pCursor = Iterate(m_head, pData, &direction);

        if (direction == 0) {
            return;
        }

        Node* pNewNode = new Node(pData, size);

        if (direction == 1) {
            pCursor->pNext = pNewNode;
        }
        else {
            pCursor->pPrev = pNewNode;
        }
    }

    template<typename T> T* BinarySearchTree<T>::Search(T* pData) const {
        int32_t direction = 0;
        Node* pCursor = Iterate(m_head, pData, &direction);

        if (direction == 0) {
            return pCursor->pData;
        }

        return nullptr;
    }

    template<typename T> Node* BinarySearchTree<T>::Iterate(Node* pCursor, T* pData, int32_t* direction) const {
        if (Compare(pCursor->pData, pData) == 1) {
            if (pCursor->pNext) {
                return Iterate(pCursor->pNext, pData, direction);
            }
            else {
                *direction = 1;
                return pCursor;
            }
        }
        else if (Compare(pCursor->pData, pData) == -1) {
            if (pCursor->pPrev) {
                return Iterate(pCursor->pPrev, pData, direction);
            }
            else {
                *direction = -1;
                return pCursor;
            }
        }
        else {
            *direction = 0;
            return pCursor;
        }

        SRHalt0();
    }
}

#endif //SR_UTILS_TYPES_BINARY_SEARCH_TREE_H
```


