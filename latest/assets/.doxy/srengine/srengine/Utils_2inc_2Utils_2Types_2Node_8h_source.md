

# File Node.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**Node.h**](Utils_2inc_2Utils_2Types_2Node_8h.md)

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


