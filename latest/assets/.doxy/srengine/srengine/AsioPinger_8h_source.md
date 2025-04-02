

# File AsioPinger.h

[**File List**](files.md) **>** [**Asio**](dir_4bb4be5b60be80b4c81abb1862297901.md) **>** [**AsioPinger.h**](AsioPinger_8h.md)

[Go to the documentation of this file](AsioPinger_8h.md)


```C++
//
// Created by innerviewer on 2024-02-20.
//
#ifndef SR_UTILS_NETWORK_ASIOPINGER_H
#define SR_UTILS_NETWORK_ASIOPINGER_H

#include <Utils/Network/Pinger.h>
#include <Utils/Types/Timer.h>

#include <asio/ip/icmp.hpp>
#include <asio/streambuf.hpp>

namespace SR_NETWORK_NS {
    class AsioPinger : public SR_NETWORK_NS::Pinger {
        using Super = SR_NETWORK_NS::Pinger;
    public:
        ~AsioPinger();

    public:
        void Ping(const std::string& address) override;

    private:
        void StartSend();
        void StartReceive();
        void HandleTimeout();
        void HandleReceive(uint64_t bytesReceived);

    private:
        asio::ip::icmp::endpoint m_destination;
        SR_HTYPES_NS::Timer m_sendTimer;
        SR_HTYPES_NS::Timer m_receiveTimer;
        SR_UTILS_NS::TimePointType m_sendTime;
        asio::streambuf m_replyBuffer;
        uint16_t m_sequenceNumber = 0;
        uint16_t m_RepliesNumber = 0;
        uint16_t m_successes = 0;
    };
}
#endif //SR_UTILS_NETWORK_ASIOPINGER_H
```


