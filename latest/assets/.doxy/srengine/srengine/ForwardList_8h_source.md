

# File ForwardList.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**ForwardList.h**](ForwardList_8h.md)

[Go to the documentation of this file](ForwardList_8h.md)


```C++
//
// Created by Monika on 23.04.2024.
//

#ifndef SR_ENGINE_UTILS_FORWARD_LIST_H
#define SR_ENGINE_UTILS_FORWARD_LIST_H

#include <Utils/Platform/Platform.h>

namespace SR_HTYPES_NS {
    template<typename T> class ForwardList {
        struct Node {
            explicit Node(T&& dats)
                : data(std::move(dats))
            { }

            T data;
            Node* pData = nullptr;
        };

    public:
        ForwardList() = default;

    private:
        Node* m_head = nullptr;
        Node* m_tail = nullptr;
        uint64_t m_size = 0;

    };
}

#endif //SR_ENGINE_UTILS_FORWARD_LIST_H
```


