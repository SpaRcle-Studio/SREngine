

# File ForwardList.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**ForwardList.h**](ForwardList_8h.md)

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


