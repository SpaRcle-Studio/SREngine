

# File Pinger.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Network**](dir_c7b83f1df097df65b63198ef53f0d275.md) **>** [**Pinger.h**](Pinger_8h.md)

[Go to the documentation of this file](Pinger_8h.md)


```C++
//
// Created by innerviewer on 2024-02-20.
//
#ifndef SR_UTILS_NETWORK_PINGER_H
#define SR_UTILS_NETWORK_PINGER_H

#include <Utils/Network/Socket.h>
#include <Utils/Network/Context.h>

namespace SR_NETWORK_NS {
    class Pinger {
    public:
        Pinger() = default;

    public:
        virtual void Ping(const std::string& address) = 0;

    public:
        void SetContext(Context::Ptr context) { m_context = std::move(context); }
        void SetSocket(Socket::Ptr socket) { m_socket = std::move(socket); }

    protected:
        Context::Ptr m_context;
        Socket::Ptr m_socket;
    };
}

#endif //SR_UTILS_NETWORK_PINGER_H
```


