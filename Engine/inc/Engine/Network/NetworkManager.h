//
// Created by innerviewer on 2026-03-17.
//

#ifndef SR_ENGINE_NETWORK_MANAGER_H
#define SR_ENGINE_NETWORK_MANAGER_H

#include <Engine/stdInclude.h>

#include <Utils/ECS/Component.h>
#include <Utils/Network/Context.h>
#include <Utils/Network/PeerToPeer.h>
#include <Utils/Network/Socket.h>

namespace SR_CORE_NS {
    SR_ENUM_NS_CLASS_T(NetworkRole, uint8_t,
        None,
        Host,
        Client
    )

    SR_ENUM_NS_CLASS_T(NetworkState, uint8_t,
        Disconnected,
        Starting,
        Running,
        Connecting,
        Connected,
        Error
    )

    /// Represents a received network message.
    struct NetworkMessage {
        uint32_t peerId = 0;
        std::vector<uint8_t> data;

        SR_NODISCARD const void* GetData() const { return data.data(); }
        SR_NODISCARD size_t GetSize() const { return data.size(); }

        template<typename T>
        SR_NODISCARD const T* As() const {
            if (data.size() >= sizeof(T)) {
                return reinterpret_cast<const T*>(data.data());
            }
            return nullptr;
        }
    };

    /// @category(Network)
    class NetworkManager : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
        using SocketPtr = SR_HTYPES_NS::SharedPtr<SR_NETWORK_NS::Socket>;
        using ContextPtr = SR_HTYPES_NS::SharedPtr<SR_NETWORK_NS::Context>;
        using PeerToPeerPtr = SR_HTYPES_NS::SharedPtr<SR_NETWORK_NS::PeerToPeer>;
        using MessageCallback = SR_HTYPES_NS::Function<void(const NetworkMessage&)>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<NetworkManager>;

    public:
        void Awake() override;
        void Start() override;
        void FixedUpdate() override;
        void OnDestroy() override;
        void OnEnable() override;
        void OnDisable() override;

    public:
        /// Start hosting a P2P session on the configured address/port.
        bool HostSession();

        /// Connect to an existing P2P session at the specified host.
        bool JoinSession(const std::string& hostAddress, uint16_t hostPort);

        /// Disconnect from the current session and clean up resources.
        void Disconnect();

        /// Send data to all connected peers.
        bool Broadcast(const void* data, size_t size);

        /// Send data to a specific peer by index.
        bool SendToPeer(uint32_t peerIndex, const void* data, size_t size);

        /// Set a callback to be invoked when a message is received.
        void SetOnMessageReceived(MessageCallback&& callback);

        /// Check if there are pending messages in the queue.
        SR_NODISCARD bool HasPendingMessages() const;

        /// Get the number of pending messages.
        SR_NODISCARD size_t GetPendingMessageCount() const;

        /// Pop the next message from the queue. Returns false if queue is empty.
        bool PopMessage(NetworkMessage& outMessage);

        /// Get all pending messages and clear the queue.
        std::vector<NetworkMessage> PopAllMessages();

        SR_NODISCARD NetworkRole GetRole() const { return m_role; }
        SR_NODISCARD NetworkState GetState() const { return m_state; }
        SR_NODISCARD uint32_t GetPeerCount() const;
        SR_NODISCARD bool IsConnected() const;

        void SetAddress(const std::string& address) { m_address = address; }
        void SetPort(uint16_t port) { m_port = port; }
        void SetRemoteAddress(const std::string& address) { m_remoteAddress = address; }
        void SetRemotePort(uint16_t port) { m_remotePort = port; }

    private:
        void OnPeerAccepted(const PeerToPeerPtr& pP2P, const SocketPtr& pSocket);
        void OnMessageReceived(uint32_t peerId, const void* data, size_t size);
        void SetupSocketReceive(const SocketPtr& pSocket, uint32_t peerId);

    private:
        /// @property
        std::string m_address = "0.0.0.0";
        /// @property
        uint16_t m_port = 27015;
        /// @property
        std::string m_remoteAddress;
        /// @property
        uint16_t m_remotePort = 27015;
        /// @property
        NetworkRole m_role = NetworkRole::None;

        NetworkState m_state = NetworkState::Disconnected;

        ContextPtr m_context;
        PeerToPeerPtr m_peerToPeer;

        std::vector<SocketPtr> m_peers;
        mutable std::mutex m_peerMutex;

        std::queue<NetworkMessage> m_messageQueue;
        mutable std::mutex m_messageMutex;

        MessageCallback m_onMessageReceived;
    };
}

#endif //SR_ENGINE_NETWORK_MANAGER_H
