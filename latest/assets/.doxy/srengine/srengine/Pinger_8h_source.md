

# File Pinger.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Network**](dir_fcfa5bace1b3a12e3000ff4cad4809c8.md) **>** [**Pinger.h**](Pinger_8h.md)

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


