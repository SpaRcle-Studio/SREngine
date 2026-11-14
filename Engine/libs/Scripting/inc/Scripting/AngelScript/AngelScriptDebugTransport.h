//
// Created by Codex on 14.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_DEBUG_TRANSPORT_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_DEBUG_TRANSPORT_H

#include <Scripting/AngelScript/DebugAdapterProtocol.h>
#include <Utils/Network/LocalTCP.h>
#include <Utils/Types/Thread.h>

namespace SR_SCRIPTING_NS {
    class AngelScriptDebugTransport {
    public:
        ~AngelScriptDebugTransport();
        bool Start(uint16_t port, SR_HTYPES_NS::Function<void(const SR_UTILS_NS::SerializationNode&)> onRequest,
            SR_HTYPES_NS::Function<void()> onDisconnect);
        void Stop();
        void Send(SR_UTILS_NS::SerializationNode message);
        void DisconnectAfterFlush();

    private:
        void Serve();
        void ServeClient(SR_NETWORK_NS::LocalTCP::Handle client);
        bool Flush(SR_NETWORK_NS::LocalTCP::Handle client);

    private:
        SR_NETWORK_NS::LocalTCP::Handle m_listener = SR_NETWORK_NS::LocalTCP::InvalidHandle;
        SR_HTYPES_NS::Thread* m_pThread = nullptr;
        std::atomic<bool> m_stop = false;
        std::atomic<bool> m_disconnect = false;
        std::mutex m_mutex;
        SR_UTILS_NS::Vector<SR_UTILS_NS::SerializationNode> m_outgoing;
        SR_HTYPES_NS::Function<void(const SR_UTILS_NS::SerializationNode&)> m_onRequest;
        SR_HTYPES_NS::Function<void()> m_onDisconnect;
        int64_t m_sequence = 0;
    };
}

#endif
