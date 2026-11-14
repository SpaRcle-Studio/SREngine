//
// Created by Codex on 14.11.2026.
//

#include <Scripting/AngelScript/AngelScriptDebugTransport.h>

#if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
namespace SR_SCRIPTING_NS {
    AngelScriptDebugTransport::~AngelScriptDebugTransport() {
        Stop();
    }

    bool AngelScriptDebugTransport::Start(uint16_t port,
        SR_HTYPES_NS::Function<void(const SR_UTILS_NS::SerializationNode&)> onRequest,
        SR_HTYPES_NS::Function<void()> onDisconnect)
    {
    #if !defined(SR_THREADS_ALLOWED)
        SR_ERROR("AngelScriptDebugTransport::Start() : DAP requires native threads.");
        return false;
    #else
        m_listener = SR_NETWORK_NS::LocalTCP::Listen(port);
        if (m_listener == SR_NETWORK_NS::LocalTCP::InvalidHandle) {
            SR_ERROR("AngelScriptDebugTransport::Start() : cannot listen on 127.0.0.1:{}.", port);
            return false;
        }

        m_onRequest = std::move(onRequest);
        m_onDisconnect = std::move(onDisconnect);
        SR_LOG("AngelScriptDebugTransport::Start() : AngelScript DAP listening on 127.0.0.1:{}.", port);
        return SR_HTYPES_NS::Thread::Factory::Instance().Create(m_pThread, [this]() {
            Serve();
            return false;
        });
    #endif
    }

    void AngelScriptDebugTransport::Stop() {
        m_stop = true;
        if (m_pThread) {
            m_pThread->Join();
            m_pThread->Free();
            m_pThread = nullptr;
        }

        if (m_listener != SR_NETWORK_NS::LocalTCP::InvalidHandle) {
            SR_NETWORK_NS::LocalTCP::CloseListener(m_listener);
            m_listener = SR_NETWORK_NS::LocalTCP::InvalidHandle;
        }
    }

    void AngelScriptDebugTransport::Send(SR_UTILS_NS::SerializationNode message) {
        std::lock_guard lock(m_mutex);
        DebugAdapterProtocol::Set(message, "seq", ++m_sequence);
        m_outgoing.emplace_back(std::move(message));
    }

    void AngelScriptDebugTransport::DisconnectAfterFlush() {
        m_disconnect = true;
    }

    void AngelScriptDebugTransport::Serve() {
        m_pThread->SetName("AngelScript DAP");
        while (!m_stop) {
            const auto client = SR_NETWORK_NS::LocalTCP::Accept(m_listener);
            if (client == SR_NETWORK_NS::LocalTCP::InvalidHandle) {
                continue;
            }

            m_disconnect = false;
            ServeClient(client);
            m_onDisconnect();
            SR_NETWORK_NS::LocalTCP::Close(client);
            std::lock_guard lock(m_mutex);
            m_outgoing.clear();
        }
    }

    bool AngelScriptDebugTransport::Flush(SR_NETWORK_NS::LocalTCP::Handle client) {
        SR_UTILS_NS::Vector<SR_UTILS_NS::SerializationNode> outgoing;
        {
            std::lock_guard lock(m_mutex);
            outgoing.swap(m_outgoing);
        }

        for (auto&& message : outgoing) {
            const auto body = DebugAdapterProtocol::Serialize(message);
            const auto packet = "Content-Length: {}\r\n\r\n{}"_format(body.size(), body);
            uint64_t offset = 0;
            while (offset < packet.size() && !m_stop) {
                const auto count = SR_NETWORK_NS::LocalTCP::Send(client, packet.data() + offset,
                    static_cast<uint32_t>(SR_MIN(packet.size() - offset, 65536)));
                if (count <= 0) {
                    return false;
                }
                offset += count;
            }
        }
        return !m_stop;
    }

    void AngelScriptDebugTransport::ServeClient(SR_NETWORK_NS::LocalTCP::Handle client) {
        SR_UTILS_NS::String incoming;
        char buffer[8192];
        while (!m_stop && Flush(client)) {
            if (m_disconnect) {
                return;
            }
            const auto readable = SR_NETWORK_NS::LocalTCP::WaitReadable(client, 20);
            if (readable < 0) {
                return;
            }
            if (!readable) {
                continue;
            }

            const auto count = SR_NETWORK_NS::LocalTCP::Receive(client, buffer, sizeof(buffer));
            if (count <= 0) {
                return;
            }
            incoming.append(buffer, count);

            while (!incoming.empty()) {
                const auto end = incoming.find("\r\n\r\n");
                if (end == SR_UTILS_NS::String::npos) {
                    if (incoming.size() > 8192) {
                        return;
                    }
                    break;
                }

                uint64_t length = 0;
                bool hasLength = false;
                uint64_t line = 0;
                while (line < end) {
                    const auto next = incoming.find("\r\n", line);
                    const auto header = incoming.substr(line, next - line);
                    if (header.starts_with("Content-Length: ")) {
                        if (hasLength || header.size() == 16) {
                            return;
                        }
                        hasLength = true;
                        for (uint64_t i = 16; i < header.size(); ++i) {
                            if (header[i] < '0' || header[i] > '9' || length > 1048576) {
                                return;
                            }
                            length = length * 10 + header[i] - '0';
                        }
                    }
                    line = next + 2;
                }

                if (!hasLength || !length || length > 1048576 || end > 8192) {
                    return;
                }
                if (incoming.size() < end + 4 + length) {
                    break;
                }

                SR_UTILS_NS::SerializationNode request;
                if (!DebugAdapterProtocol::Parse(incoming.substr(end + 4, length), request)) {
                    return;
                }
                incoming.erase(0, end + 4 + length);
                m_onRequest(request);
                if (m_disconnect) {
                    Flush(client);
                    return;
                }
            }
        }
    }
}
#endif
