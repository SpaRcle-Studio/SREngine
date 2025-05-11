

# File PeerToPeer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Network**](dir_fcfa5bace1b3a12e3000ff4cad4809c8.md) **>** [**PeerToPeer.h**](PeerToPeer_8h.md)

[Go to the documentation of this file](PeerToPeer_8h.md)


```C++
//
// Created by Monika on 19.02.2024.
//

#ifndef SR_UTILS_NETWORK_PEER_TO_PEER_H
#define SR_UTILS_NETWORK_PEER_TO_PEER_H

#include <Utils/Network/Socket.h>
#include <Utils/Network/Acceptor.h>

namespace SR_NETWORK_NS {
    class Context;

    class PeerToPeer : public SR_HTYPES_NS::SharedPtr<PeerToPeer> {
        friend class Context;
        using Super = SR_HTYPES_NS::SharedPtr<PeerToPeer>;
        using Callback = std::function<void(const PeerToPeer::Ptr& pP2P, const Socket::Ptr&)>;
    private:
        PeerToPeer(SocketType type, Context::Ptr pContext, std::string address, uint16_t port);

    public:
        virtual ~PeerToPeer() = default;

    public:
        bool Run();
        void Close();

        bool Connect(const std::string& address, uint16_t port);

        void SetOnAcceptCallback(Callback&& callback) { m_onAccept = std::move(callback); }

        SR_NODISCARD const Acceptor::Ptr& GetAcceptor() const { return m_acceptor; }

        SR_NODISCARD uint32_t GetConnectionsCount() const { return m_connections.size(); }
        SR_NODISCARD uint32_t GetNewPeersCount() const { return m_newPeers.size(); }
        SR_NODISCARD bool IsOpen() const { return m_acceptor && m_acceptor->IsOpen(); }
        SR_NODISCARD bool HasConnection(uint32_t address, uint16_t port) const;

        bool SendKnownHosts(const Socket::Ptr& pSocket);

    private:
        void OnAccept(Socket::Ptr&& pSocket);

        bool RegisterSocket(Socket::Ptr pSocket, uint32_t address, uint16_t port);

        bool ConnectInternal(const std::string& address, uint16_t port, bool share);

        void ProcessMessage(const Socket::Ptr& pSocket, const DataPackage::Ptr& pData);

        bool SharePeer(const Socket::Ptr& pTarget, const Socket::Ptr& pNewPeer);
        bool SharePeer(const Socket::Ptr& pNewPeer);
        bool ListerPeer(const Socket::Ptr& pSocket);

    private:
        std::string m_address;
        uint16_t m_port = 0;

        const SocketType m_type = SocketType::Unknown;

        Context::Ptr m_context;

        Acceptor::Ptr m_acceptor;

        struct Connection {
            uint32_t address;
            uint16_t port;
        };

        std::map<Socket::Ptr, Connection> m_connections;

        std::set<Socket::Ptr> m_newPeers;

        Callback m_onAccept;

    };
}


#endif //SR_UTILS_NETWORK_PEER_TO_PEER_H
```


