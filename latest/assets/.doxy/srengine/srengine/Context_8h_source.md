

# File Context.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Network**](dir_fcfa5bace1b3a12e3000ff4cad4809c8.md) **>** [**Context.h**](Context_8h.md)

[Go to the documentation of this file](Context_8h.md)


```C++
//
// Created by Monika on 20.02.2024.
//

#ifndef SR_UTILS_NETWORK_CONTEXT_H
#define SR_UTILS_NETWORK_CONTEXT_H

#include <Utils/Network/Utils.h>

namespace SR_NETWORK_NS {
    class Socket;
    class Acceptor;
    class PeerToPeer;
    class Pinger;

    SR_ENUM_NS_CLASS_T(NetworkLib, uint8_t,
        Unknown,
        Asio
    )

    SR_ENUM_NS_CLASS_T(SocketType, uint8_t,
        Unknown,
        TCP,
        UDP,
        ICMP
    )

    class Context : public SR_HTYPES_NS::SharedPtr<Context> {
        using Super = SR_HTYPES_NS::SharedPtr<Context>;
        using PeerToPeerPtr = SR_HTYPES_NS::SharedPtr<PeerToPeer>;
        using AcceptorPtr = SR_HTYPES_NS::SharedPtr<Acceptor>;
        using SocketPtr = SR_HTYPES_NS::SharedPtr<Socket>;
    protected:
        Context();

    public:
        virtual ~Context() = default;

    public:
        SR_NODISCARD static SR_HTYPES_NS::SharedPtr<Context> Create();
        SR_NODISCARD static SR_HTYPES_NS::SharedPtr<Context> CreateAndRun();

        virtual bool Run() = 0;
        virtual void Stop() = 0;

        virtual bool Poll();

    public:
        void AddAsyncAcceptor(const AcceptorPtr& pAcceptor);
        void AddAsyncReceiveSocket(const SocketPtr& pSocket);
        void AddAsyncSendKnownHostsSocket(const PeerToPeerPtr& pP2P, const SocketPtr& pSocket);

        SR_NODISCARD virtual SR_HTYPES_NS::SharedPtr<Socket> CreateSocket(SocketType type) = 0;
        SR_NODISCARD virtual SR_HTYPES_NS::SharedPtr<Pinger> CreatePinger() = 0;
        SR_NODISCARD virtual SR_HTYPES_NS::SharedPtr<Acceptor> CreateAcceptor(SocketType type, const std::string& address, uint16_t port) = 0;

        SR_NODISCARD SR_HTYPES_NS::SharedPtr<PeerToPeer> CreateP2P(SocketType type, const std::string& address, uint16_t port);

    protected:
        bool m_isRunning = false;

        std::list<AcceptorPtr> m_asyncAcceptors;
        std::list<SocketPtr> m_asyncReceiveSockets;
        std::list<std::pair<PeerToPeerPtr, SocketPtr>> m_asyncSendKnownHostsSockets;

    };
}

#endif //SR_UTILS_NETWORK_CONTEXT_H
```


