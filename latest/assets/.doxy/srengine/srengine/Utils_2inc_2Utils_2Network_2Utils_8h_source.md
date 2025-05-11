

# File Utils.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Network**](dir_fcfa5bace1b3a12e3000ff4cad4809c8.md) **>** [**Utils.h**](Utils_2inc_2Utils_2Network_2Utils_8h.md)

[Go to the documentation of this file](Utils_2inc_2Utils_2Network_2Utils_8h.md)


```C++
//
// Created by Monika on 21.02.2024.
//

#ifndef SR_UTILS_NETWORK_UTILS_H
#define SR_UTILS_NETWORK_UTILS_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/Function.h>

namespace SR_NETWORK_NS {
    SR_ENUM_NS_CLASS_T(P2PMessageType, uint8_t,
        Unknown,
        PeerConnection,
        PeerDisconnection,
        KnownHostsListInfo,
        KnownHost,
        Announce
    )

    struct P2PBaseHeader {
        P2PMessageType type = P2PMessageType::Unknown;
    };

    struct P2PAnnounceHeader {
        P2PMessageType type = P2PMessageType::Announce;
        uint8_t version = 0;
        uint32_t iPv4 = 0;
        uint16_t port = 0;
    };

    struct P2PKnownHostHeader {
        P2PMessageType type = P2PMessageType::KnownHost;
        uint8_t version = 0;
        uint32_t iPv4 = 0;
        uint16_t port = 0;
    };

    struct P2PKnownHostsListInfoHeader {
        P2PMessageType type = P2PMessageType::KnownHostsListInfo;
        uint8_t version = 0;
        uint64_t count = 0;
    };

    struct P2PConnectionHeader {
        P2PMessageType type = P2PMessageType::PeerConnection;
        uint8_t version = 0;
        uint32_t iPv4 = 0;
        uint16_t port = 0;
    };

    struct P2PDisconnectionHeader {
        P2PMessageType type = P2PMessageType::PeerDisconnection;
        uint8_t version = 0;
        uint32_t iPv4 = 0;
        uint16_t port = 0;
    };

    class DataPackage : public SR_HTYPES_NS::SharedPtr<DataPackage> {
        using Super = SR_HTYPES_NS::SharedPtr<DataPackage>;
    public:
        DataPackage(void* pData, uint64_t size, bool copy)
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        {
            m_size = size;

            if (copy) {
                m_data = malloc(size);
                memcpy(m_data, pData, size);
            }
            else {
                m_data = pData;
            }
        }

        virtual ~DataPackage() {
            if (m_data) {
                free(m_data);
                m_data = nullptr;
            }
        }

        static SR_HTYPES_NS::SharedPtr<DataPackage> Allocate(uint64_t size) {
            auto&& pData = malloc(size);
            return DataPackage::MakeShared(pData, size, false);
        }

        SR_NODISCARD const void* GetData() const { return m_data; }
        SR_NODISCARD void* GetData() { return m_data; }
        SR_NODISCARD uint64_t GetSize() const { return m_size; }

    private:
        void* m_data = nullptr;
        uint64_t m_size = 0;

    };

    SR_MAYBE_UNUSED SR_CONSTEXPR SR_INLINE_STATIC size_t GetMaxP2PHeaderSize() {
        return
               SR_MAX(sizeof(P2PKnownHostHeader),
               SR_MAX(sizeof(P2PConnectionHeader),
               SR_MAX(sizeof(P2PDisconnectionHeader),
               SR_MAX(sizeof(P2PKnownHostsListInfoHeader),
               SR_MAX(sizeof(P2PAnnounceHeader),
                      sizeof(P2PBaseHeader)
               )))));
    }

    SR_MAYBE_UNUSED SR_INLINE_STATIC uint32_t StringToIPv4(const std::string& address) {
        std::stringstream ss(address);
        uint32_t a, b, c, d;
        int8_t dot;
        ss >> a >> dot >> b >> dot >> c >> dot >> d;
        return (a << 24) | (b << 16) | (c << 8) | d;
    }

    SR_MAYBE_UNUSED SR_INLINE_STATIC std::string IPv4ToString(uint32_t address) {
        std::stringstream ss;
        ss << ((address >> 24) & 0xFF) << '.' << ((address >> 16) & 0xFF) << '.' << ((address >> 8) & 0xFF) << '.' << (address & 0xFF);
        return ss.str();
    }
}

#endif //SR_UTILS_NETWORK_UTILS_H
```


