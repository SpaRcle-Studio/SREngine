

# File IPV4Header.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Network**](dir_c7b83f1df097df65b63198ef53f0d275.md) **>** [**Headers**](dir_9caa5709f83e81decc39517eefafe3cd.md) **>** [**IPV4Header.h**](IPV4Header_8h.md)

[Go to the documentation of this file](IPV4Header_8h.md)


```C++
//
// Created by innerviewer on 2024-02-20.
//
#ifndef SR_UTILS_NETWORK_IPV4HEADER_H
#define SR_UTILS_NETWORK_IPV4HEADER_H

#include <Utils/stdInclude.h>
#include <asio/ip/address_v4.hpp>

namespace SR_NETWORK_NS {
    class IPV4Header { 
    public:
        IPV4Header() { std::fill(rep_, rep_ + sizeof(rep_), 0); }

        unsigned char version() const { return (rep_[0] >> 4) & 0xF; }

        unsigned short header_length() const { return (rep_[0] & 0xF) * 4; }

        unsigned char type_of_service() const { return rep_[1]; }

        unsigned short total_length() const { return decode(2, 3); }

        unsigned short identification() const { return decode(4, 5); }

        bool dont_fragment() const { return (rep_[6] & 0x40) != 0; }

        bool more_fragments() const { return (rep_[6] & 0x20) != 0; }

        unsigned short fragment_offset() const { return decode(6, 7) & 0x1FFF; }

        unsigned int time_to_live() const { return rep_[8]; }

        unsigned char protocol() const { return rep_[9]; }

        unsigned short header_checksum() const { return decode(10, 11); }

        asio::ip::address_v4 source_address() const {
            asio::ip::address_v4::bytes_type bytes{{rep_[12], rep_[13], rep_[14], rep_[15]}};
            return asio::ip::address_v4(bytes);
        }

        asio::ip::address_v4 destination_address() const {
            asio::ip::address_v4::bytes_type bytes
                    = {{rep_[16], rep_[17], rep_[18], rep_[19]}};
            return asio::ip::address_v4(bytes);
        }

        friend std::istream &operator>>(std::istream &is, IPV4Header &header) {
            is.read(reinterpret_cast<char *>(header.rep_), 20);
            if (header.version() != 4)
                is.setstate(std::ios::failbit);
            std::streamsize options_length = header.header_length() - 20;
            if (options_length < 0 || options_length > 40)
                is.setstate(std::ios::failbit);
            else
                is.read(reinterpret_cast<char *>(header.rep_) + 20, options_length);
            return is;
        }

    private:
        unsigned short decode(int a, int b) const { return (rep_[a] << 8) + rep_[b]; }

        unsigned char rep_[60];
    };
}
#endif //SR_UTILS_NETWORK_IPV4HEADER_H
```


