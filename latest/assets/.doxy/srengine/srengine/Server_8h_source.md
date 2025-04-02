

# File Server.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Network**](dir_c7b83f1df097df65b63198ef53f0d275.md) **>** [**Server.h**](Server_8h.md)

[Go to the documentation of this file](Server_8h.md)


```C++
//
// Created by Monika on 19.02.2024.
//

#ifndef SR_UTILS_NETWORK_SERVER_H
#define SR_UTILS_NETWORK_SERVER_H

#include <Utils/Network/Socket.h>
#include <Utils/Types/NodeDictionary.h>

namespace SR_NETWORK_NS {
    class Server : public SR_HTYPES_NS::SharedPtr<Server> {
        using Super = SR_HTYPES_NS::SharedPtr<Server>;
    public:
        Server(SocketType type, int32_t domain, int32_t service, int32_t protocol, uint64_t interface, int32_t port, int32_t backlog);
        ~Server();

    public:
        bool Start();
        bool Stop();

    private:
        int32_t m_domain = 0;
        int32_t m_service = 0;
        int32_t m_protocol = 0;
        int32_t m_port = 0;
        int32_t m_backlog = 0;
        uint64_t m_interface = 0;


        SR_HTYPES_NS::SharedPtr<Socket> m_socket;

    };
}

#endif //SR_UTILS_NETWORK_SERVER_H
```


