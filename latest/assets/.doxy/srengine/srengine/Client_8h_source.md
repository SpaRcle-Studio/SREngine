

# File Client.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Network**](dir_c7b83f1df097df65b63198ef53f0d275.md) **>** [**Client.h**](Client_8h.md)

[Go to the documentation of this file](Client_8h.md)


```C++
// 
// Created by qlop on 19.02.2024 
// 

#ifndef SR_UTILS_NETWORK_CLIENT_H
#define SR_UTILS_NETWORK_CLIENT_H

#include <Utils/Network/Socket.h>
#include <Utils/Network/Server.h>

namespace SR_NETWORK_NS {
    class Client : public SR_HTYPES_NS::SharedPtr<Client> {
        using Super = SR_HTYPES_NS::SharedPtr<Client>;
    public:
        Client(SocketType type, int32_t domain, int32_t service, int32_t protocol, int32_t port, uint64_t interface);

    public:
        std::string Request(const std::string& serverIp, void* request, uint64_t size);

        void Ping(const std::string& ip, int32_t port);

    private:
        int32_t m_domain = 0;
        int32_t m_service = 0;
        int32_t m_protocol = 0;
        int32_t m_port = 0;
        uint64_t m_interface = 0;

        SR_HTYPES_NS::SharedPtr<Socket> m_socket;
    };
}

#endif
```


