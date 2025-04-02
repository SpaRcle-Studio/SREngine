

# File Node.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**Node.h**](Utils_2inc_2Utils_2Types_2Node_8h.md)

[Go to the documentation of this file](Utils_2inc_2Utils_2Types_2Node_8h.md)


```C++
//
// Created by Monika on 19.02.2024.
//

#ifndef SR_UTILS_TYPES_NODE_H
#define SR_UTILS_TYPES_NODE_H

#include <Utils/Common/NonCopyable.h>

namespace SR_HTYPES_NS {
    struct Node : public SR_UTILS_NS::NonCopyable {
    private:
        using Super = SR_UTILS_NS::NonCopyable;

    public:
        Node(void* pData, uint64_t size)
            : Super()
            , size(size)
        {
            this->pData = malloc(size);
            memcpy(this->pData, pData, size);
        }

        ~Node() override {
            if (pData != nullptr) {
                free(pData);
                pData = nullptr;
            }
        }

    public:
        void* pData = nullptr;
        Node* pNext = nullptr;
        Node* pPrev = nullptr;
        uint64_t size = 0;

    };
}

#endif //SR_UTILS_TYPES_NODE_H
```


