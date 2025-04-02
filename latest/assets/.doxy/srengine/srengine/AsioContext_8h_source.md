

# File AsioContext.h

[**File List**](files.md) **>** [**Asio**](dir_4bb4be5b60be80b4c81abb1862297901.md) **>** [**AsioContext.h**](AsioContext_8h.md)

[Go to the documentation of this file](AsioContext_8h.md)


```C++
//
// Created by Monika on 20.02.2024.
//

#ifndef SR_UTILS_NETWORK_ASIO_CONTEXT_H
#define SR_UTILS_NETWORK_ASIO_CONTEXT_H

#include <Utils/Network/Context.h>

#include <asio/io_context.hpp>

namespace SR_NETWORK_NS {
    class AsioContext : public Context {
        using Super = Context;
    public:
        AsioContext() = default;
        ~AsioContext() override;

    public:
        asio::io_context& GetContext() { return m_context; }

        bool Run() override;
        bool Poll() override;
        void Stop() override;

        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Socket> CreateSocket(SocketType type) override;
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Pinger> CreatePinger() override;
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Acceptor> CreateAcceptor(SocketType type, const std::string& address, uint16_t port) override;

    private:
        asio::io_context m_context;

    };
}

#endif //SR_UTILS_NETWORK_ASIO_CONTEXT_H
```


