

# File AsioTCPSocket.h

[**File List**](files.md) **>** [**Asio**](dir_4bb4be5b60be80b4c81abb1862297901.md) **>** [**AsioTCPSocket.h**](AsioTCPSocket_8h.md)

[Go to the documentation of this file](AsioTCPSocket_8h.md)


```C++
//
// Created by Monika on 19.02.2024.
//

#ifndef SR_UTILS_NETWORK_ASIO_TCP_SOCKET_H
#define SR_UTILS_NETWORK_ASIO_TCP_SOCKET_H

#include <Utils/Network/Socket.h>

#include <asio/ip/tcp.hpp>
#include <asio/ip/udp.hpp>
#include <asio/io_context.hpp>

namespace SR_NETWORK_NS {
    class AsioContext;

    class AsioTCPSocket : public Socket {
        using Super = Socket;
        friend class AsioContext;
    private:
        explicit AsioTCPSocket(Context::Ptr pContext);

    public:
        ~AsioTCPSocket() override;

    public:
        bool Connect(const std::string& address, uint16_t port) override;
        bool Send(const void* data, size_t size) override;
        bool SendTo(const void* data, uint64_t size, const std::string& address, uint16_t port) override;
        bool Close() override;

        uint64_t Receive(void* data, size_t size) override;
        uint64_t AsyncReceive(void* data, std::function<void(uint64_t bytesReceived)> callback) override;

        SR_NODISCARD bool IsOpen() const override;

        SR_NODISCARD std::string GetLocalAddress() const override;
        SR_NODISCARD std::string GetRemoteAddress() const override;

        SR_NODISCARD uint16_t GetLocalPort() const override;
        SR_NODISCARD uint16_t GetRemotePort() const override;

        void SetSocket(asio::ip::tcp::socket&& socket) { m_socket = std::move(socket); }

    protected:
        bool ReceiveAsyncInternal() override;

    private:
        std::optional<asio::ip::tcp::socket> m_socket;

    };
}

#endif //SR_UTILS_NETWORK_ASIO_TCP_SOCKET_H
```


