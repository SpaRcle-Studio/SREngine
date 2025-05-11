

# File Server.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Network**](dir_fcfa5bace1b3a12e3000ff4cad4809c8.md) **>** [**Server.h**](Server_8h.md)

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


