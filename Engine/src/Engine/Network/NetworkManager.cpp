//
// Created by innerviewer on 2026-03-17.
//

#include <Engine/Network/NetworkManager.h>
#include <Utils/Debug.h>

#include <Codegen/NetworkManager.generated.hpp>

namespace SR_CORE_NS {
    void NetworkManager::Awake() {
        Super::Awake();
    }

    void NetworkManager::Start() {
        Super::Start();

        if (m_role == NetworkRole::Host) {
            HostSession();
        }
        else if (m_role == NetworkRole::Client) {
            if (!m_remoteAddress.empty()) {
                JoinSession(m_remoteAddress, m_remotePort);
            }
            else {
                SR_WARN("NetworkManager::Start() : role is Client but no remote address is set.");
            }
        }
    }

    void NetworkManager::FixedUpdate() {
        SR_TRACY_ZONE;

        if (m_context) {
            m_context->Poll();
        }

        Super::FixedUpdate();
    }

    void NetworkManager::OnDestroy() {
        Disconnect();

        Super::OnDestroy();
    }

    void NetworkManager::OnEnable() {
        Super::OnEnable();
    }

    void NetworkManager::OnDisable() {
        Disconnect();

        Super::OnDisable();
    }

    bool NetworkManager::HostSession() {
        if (m_state != NetworkState::Disconnected) {
            SR_ERROR("NetworkManager::HostSession() : already in a session! Disconnect first.");
            return false;
        }

        m_state = NetworkState::Starting;

        m_context = SR_NETWORK_NS::Context::CreateAndRun();
        if (!m_context) {
            SR_ERROR("NetworkManager::HostSession() : failed to create network context!");
            m_state = NetworkState::Error;
            return false;
        }

        m_peerToPeer = m_context->CreateP2P(SR_NETWORK_NS::SocketType::TCP, m_address, m_port);
        if (!m_peerToPeer) {
            SR_ERROR("NetworkManager::HostSession() : failed to create P2P instance!");
            m_context->Stop();
            m_context = nullptr;
            m_state = NetworkState::Error;
            return false;
        }

        m_peerToPeer->SetOnAcceptCallback([this](const PeerToPeerPtr& pP2P, const SocketPtr& pSocket) {
            OnPeerAccepted(pP2P, pSocket);
        });

        if (!m_peerToPeer->Run()) {
            SR_ERROR("NetworkManager::HostSession() : failed to start P2P session!");
            m_peerToPeer = nullptr;
            m_context->Stop();
            m_context = nullptr;
            m_state = NetworkState::Error;
            return false;
        }

        m_role = NetworkRole::Host;
        m_state = NetworkState::Running;

        SR_LOG("NetworkManager::HostSession() : hosting on {}:{}", m_address, m_port);

        return true;
    }

    bool NetworkManager::JoinSession(const std::string& hostAddress, uint16_t hostPort) {
        if (m_state != NetworkState::Disconnected) {
            SR_ERROR("NetworkManager::JoinSession() : already in a session! Disconnect first.");
            return false;
        }

        m_state = NetworkState::Starting;

        m_context = SR_NETWORK_NS::Context::CreateAndRun();
        if (!m_context) {
            SR_ERROR("NetworkManager::JoinSession() : failed to create network context!");
            m_state = NetworkState::Error;
            return false;
        }

        /// Create a local P2P instance so we can accept incoming connections from other peers.
        m_peerToPeer = m_context->CreateP2P(SR_NETWORK_NS::SocketType::TCP, m_address, m_port);
        if (!m_peerToPeer) {
            SR_ERROR("NetworkManager::JoinSession() : failed to create P2P instance!");
            m_context->Stop();
            m_context = nullptr;
            m_state = NetworkState::Error;
            return false;
        }

        m_peerToPeer->SetOnAcceptCallback([this](const PeerToPeerPtr& pP2P, const SocketPtr& pSocket) {
            OnPeerAccepted(pP2P, pSocket);
        });

        if (!m_peerToPeer->Run()) {
            SR_ERROR("NetworkManager::JoinSession() : failed to start local P2P listener!");
            m_peerToPeer = nullptr;
            m_context->Stop();
            m_context = nullptr;
            m_state = NetworkState::Error;
            return false;
        }

        m_state = NetworkState::Connecting;

        if (!m_peerToPeer->Connect(hostAddress, hostPort)) {
            SR_ERROR("NetworkManager::JoinSession() : failed to connect to {}:{}!", hostAddress, hostPort);
            m_peerToPeer->Close();
            m_peerToPeer = nullptr;
            m_context->Stop();
            m_context = nullptr;
            m_state = NetworkState::Error;
            return false;
        }

        m_role = NetworkRole::Client;
        m_state = NetworkState::Connected;

        SR_LOG("NetworkManager::JoinSession() : connected to {}:{}", hostAddress, hostPort);

        return true;
    }

    void NetworkManager::Disconnect() {
        if (m_state == NetworkState::Disconnected) {
            return;
        }

        SR_LOG("NetworkManager::Disconnect() : disconnecting...");

        {
            std::lock_guard lock(m_peerMutex);
            m_peers.clear();
        }

        {
            std::lock_guard lock(m_messageMutex);
            while (!m_messageQueue.empty()) {
                m_messageQueue.pop();
            }
        }

        if (m_peerToPeer) {
            m_peerToPeer->Close();
            m_peerToPeer = nullptr;
        }

        if (m_context) {
            m_context->Stop();
            m_context = nullptr;
        }

        m_state = NetworkState::Disconnected;
        m_role = NetworkRole::None;
    }

    bool NetworkManager::Broadcast(const void* data, size_t size) {
        if (m_state != NetworkState::Running && m_state != NetworkState::Connected) {
            SR_ERROR("NetworkManager::Broadcast() : not in an active session!");
            return false;
        }

        std::lock_guard lock(m_peerMutex);

        bool allSent = true;
        for (auto&& pPeer : m_peers) {
            if (pPeer && pPeer->IsOpen()) {
                if (!pPeer->Send(data, size)) {
                    SR_ERROR("NetworkManager::Broadcast() : failed to send to a peer.");
                    allSent = false;
                }
            }
        }

        return allSent;
    }

    bool NetworkManager::SendToPeer(uint32_t peerIndex, const void* data, size_t size) {
        std::lock_guard lock(m_peerMutex);

        if (peerIndex >= m_peers.size()) {
            SR_ERROR("NetworkManager::SendToPeer() : peer index {} out of range (count: {})!", peerIndex, m_peers.size());
            return false;
        }

        auto&& pPeer = m_peers[peerIndex];
        if (!pPeer || !pPeer->IsOpen()) {
            SR_ERROR("NetworkManager::SendToPeer() : peer at index {} is not connected!", peerIndex);
            return false;
        }

        return pPeer->Send(data, size);
    }

    void NetworkManager::SetOnMessageReceived(MessageCallback&& callback) {
        m_onMessageReceived = std::move(callback);
    }

    bool NetworkManager::HasPendingMessages() const {
        std::lock_guard lock(m_messageMutex);
        return !m_messageQueue.empty();
    }

    size_t NetworkManager::GetPendingMessageCount() const {
        std::lock_guard lock(m_messageMutex);
        return m_messageQueue.size();
    }

    bool NetworkManager::PopMessage(NetworkMessage& outMessage) {
        std::lock_guard lock(m_messageMutex);
        if (m_messageQueue.empty()) {
            return false;
        }

        outMessage = std::move(m_messageQueue.front());
        m_messageQueue.pop();
        return true;
    }

    std::vector<NetworkMessage> NetworkManager::PopAllMessages() {
        std::lock_guard lock(m_messageMutex);
        std::vector<NetworkMessage> messages;
        messages.reserve(m_messageQueue.size());

        while (!m_messageQueue.empty()) {
            messages.emplace_back(std::move(m_messageQueue.front()));
            m_messageQueue.pop();
        }

        return messages;
    }

    uint32_t NetworkManager::GetPeerCount() const {
        if (m_peerToPeer) {
            return m_peerToPeer->GetConnectionsCount();
        }
        return 0;
    }

    bool NetworkManager::IsConnected() const {
        return m_state == NetworkState::Running || m_state == NetworkState::Connected;
    }

    void NetworkManager::OnPeerAccepted(const PeerToPeerPtr& pP2P, const SocketPtr& pSocket) {
        uint32_t peerId;

        {
            std::lock_guard lock(m_peerMutex);
            peerId = static_cast<uint32_t>(m_peers.size());
            m_peers.emplace_back(pSocket);
        }

        SR_LOG("NetworkManager::OnPeerAccepted() : new peer {} connected! Total connections: {}", peerId, pP2P->GetConnectionsCount());

        /// Set up async receive for this peer.
        SetupSocketReceive(pSocket, peerId);
    }

    void NetworkManager::OnMessageReceived(uint32_t peerId, const void* data, size_t size) {
        NetworkMessage msg;
        msg.peerId = peerId;
        msg.data.resize(size);
        memcpy(msg.data.data(), data, size);

        /// If callback is set, invoke it immediately.
        if (m_onMessageReceived) {
            m_onMessageReceived(msg);
        }

        /// Also queue the message for polling.
        {
            std::lock_guard lock(m_messageMutex);
            m_messageQueue.emplace(std::move(msg));
        }
    }

    void NetworkManager::SetupSocketReceive(const SocketPtr& pSocket, uint32_t peerId) {
        if (!pSocket) {
            return;
        }

        /// Capture peerId by value, and `this` for the callback.
        pSocket->SetReceiveCallback([this, peerId](const SocketPtr& pSock,
                                                    const SR_NETWORK_NS::DataPackage::Ptr& pData,
                                                    uint64_t size) {
            if (pData && size > 0) {
                OnMessageReceived(peerId, pData->GetData(), static_cast<size_t>(size));
            }
        });

        /// Start async receive with a reasonable buffer size (64KB).
        pSocket->AsyncReceive(65536);
    }
}
