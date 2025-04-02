

# File Acceptor.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Network**](dir_c7b83f1df097df65b63198ef53f0d275.md) **>** [**Acceptor.h**](Acceptor_8h.md)

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


