

# File Acceptor.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Network**](dir_fcfa5bace1b3a12e3000ff4cad4809c8.md) **>** [**Acceptor.h**](Acceptor_8h.md)

[Go to the documentation of this file](Acceptor_8h.md)


```C++
//
// Created by Monika on 20.02.2024.
//

#ifndef SR_UTILS_NETWORK_ACCEPTOR_H
#define SR_UTILS_NETWORK_ACCEPTOR_H

#include <Utils/Network/Context.h>

namespace SR_NETWORK_NS {
    class Acceptor : public SR_HTYPES_NS::SharedPtr<Acceptor> {
        friend class Context;
        using Super = SR_HTYPES_NS::SharedPtr<Acceptor>;
    public:
        using Callback = std::function<void(Socket::Ptr)>;

    protected:
        explicit Acceptor(SocketType type, Context::Ptr pContext, std::string address, uint16_t port)
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
            , m_type(type)
            , m_context(std::move(pContext))
            , m_address(std::move(address))
            , m_port(port)
        { }

    public:
        virtual ~Acceptor() = default;

        SR_NODISCARD virtual std::string GetLocalAddress() const = 0;
        SR_NODISCARD virtual std::string GetRemoteAddress() const = 0;

        SR_NODISCARD virtual uint16_t GetLocalPort() const = 0;
        SR_NODISCARD virtual uint16_t GetRemotePort() const = 0;

        SR_NODISCARD virtual bool Init() = 0;

        SR_NODISCARD bool IsOpen() const { return m_isOpen; }
        SR_NODISCARD bool IsRepeated() const { return m_isRepeated; }
        SR_NODISCARD bool IsWaitingAccept() const { return m_isWaitingAccept; }

        void SetCallback(Callback&& callback) { m_callback = std::move(callback); }
        void SetRepeated(bool isRepeated) { m_isRepeated = isRepeated; }

        bool Start();
        bool StartAsync();

        virtual void Close() {
            m_isOpen = false;
        }

    protected:
        virtual bool StartInternal(bool async) = 0;

    protected:
        bool m_isOpen = false;
        bool m_isWaitingAccept = false;

        bool m_isRepeated = true;

        const SocketType m_type = SocketType::Unknown;

        Context::Ptr m_context;
        Callback m_callback;
        std::string m_address;
        uint16_t m_port = 0;

    };
}

#endif //SR_UTILS_NETWORK_ACCEPTOR_H
```


