

# File PeerToPeer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Network**](dir_c7b83f1df097df65b63198ef53f0d275.md) **>** [**PeerToPeer.h**](PeerToPeer_8h.md)

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


