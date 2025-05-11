

# File AsioICMPSocket.h

[**File List**](files.md) **>** [**Asio**](dir_1cfa5756459a2c0a929c2f3bb67979f7.md) **>** [**AsioICMPSocket.h**](AsioICMPSocket_8h.md)

[Go to the documentation of this file](AsioICMPSocket_8h.md)


```C++
//
// Created by innerviewer on 2024-02-20.
//

#ifndef SR_UTILS_NETWORK_ASIOICMPSOCKET_H
#define SR_UTILS_NETWORK_ASIOICMPSOCKET_H

#include <Utils/Network/Socket.h>

#include <asio/ip/icmp.hpp>
#include <asio/io_context.hpp>

namespace SR_NETWORK_NS {
    class AsioContext;

    class AsioICMPSocket : public Socket {
        using Super = Socket;
        friend class AsioContext;
    private:
        explicit AsioICMPSocket(Context::Ptr pContext);

    public:
        ~AsioICMPSocket() override;

    public:
        bool Connect(const std::string& address, uint16_t port) override;
        bool Bind(uint16_t port);
        bool Listen(int32_t backlog);
        bool Send(const void* data, size_t size) override;
        bool SendTo(const void* data, uint64_t size, const std::string& address, uint16_t port) override;
        SR_NODISCARD uint64_t Receive(void* data, size_t size) override;
        SR_NODISCARD uint64_t AsyncReceive(void* data, std::function<void(uint64_t bytesReceived)> callback) override;
        bool Close() override;

        SR_NODISCARD bool IsOpen() const override;

        SR_NODISCARD std::string GetLocalAddress() const override;
        SR_NODISCARD std::string GetRemoteAddress() const override;

        SR_NODISCARD uint16_t GetLocalPort() const override;
        SR_NODISCARD uint16_t GetRemotePort() const override;

    protected:
        bool ReceiveAsyncInternal() override;

        void SetSocket(asio::ip::icmp::socket&& socket) { m_socket = std::move(socket); }

    private:
        std::optional<asio::ip::icmp::socket> m_socket;

    };
}

#endif //SR_UTILS_NETWORK_ASIOICMPSOCKET_H
```


