

# File ICMPHeader.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Network**](dir_c7b83f1df097df65b63198ef53f0d275.md) **>** [**Headers**](dir_9caa5709f83e81decc39517eefafe3cd.md) **>** [**ICMPHeader.h**](ICMPHeader_8h.md)

[Go to the documentation of this file](ICMPHeader_8h.md)


```C++
//
// Created by innerviewer on 2024-02-20.
//
#ifndef SR_UTILS_NETWORK_ICMPHEADER_H
#define SR_UTILS_NETWORK_ICMPHEADER_H

#include <Utils/Common/Enumerations.h>

namespace SR_NETWORK_NS {
    SR_ENUM_NS_CLASS_T(ICMPType, uint8_t,
           EchoReply = 0,
           DestinationUnreachable = 3,
           SourceQuench = 4,
           Redirect = 5,
           EchoRequest = 8,
           TimeExceeded = 11,
           ParameterProblem = 12,
           TimestampRequest = 13,
           TimestampReply = 14,
           InfoRequest = 15,
           InfoReply = 16,
           AddressRequest = 17,
           AddressReply = 18
    );

    class ICMPHeader {
    public:
    public:
        ICMPHeader() { std::fill(rep_, rep_ + sizeof(rep_), 0); }

        uint8_t Type() const { return rep_[0]; }
        uint8_t Code() const { return rep_[1]; }
        uint16_t Checksum() const { return Decode(2, 3); }
        uint16_t Identifier() const { return Decode(4, 5); }
        uint16_t SequenceNumber() const { return Decode(6, 7); }

        void Type(ICMPType type) { rep_[0] = static_cast<uint8_t>(type); }
        void Code(ICMPType type) { rep_[1] = static_cast<uint8_t>(type); }
        void Checksum(uint16_t type) { Encode(2, 3, static_cast<uint8_t>(type)); }
        void Identifier(uint16_t type) { Encode(4, 5, static_cast<uint8_t>(type)); }
        void SequenceNumber(uint16_t type) { Encode(6, 7, static_cast<uint8_t>(type)); }

        friend std::istream& operator>>(std::istream& is, ICMPHeader& header)
        { return is.read(reinterpret_cast<char*>(header.rep_), 8); }

        friend std::ostream& operator<<(std::ostream& os, const ICMPHeader& header)
        { return os.write(reinterpret_cast<const char*>(header.rep_), 8); }

    private:
        uint16_t Decode(int a, int b) const
        { return (rep_[a] << 8) + rep_[b]; }

        void Encode(int a, int b, uint16_t n)
        {
            rep_[a] = static_cast<unsigned char>(n >> 8);
            rep_[b] = static_cast<unsigned char>(n & 0xFF);
        }

        unsigned char rep_[8];
    };

    template <typename Iterator>
    void ComputeChecksum(ICMPHeader& header,
                          Iterator body_begin, Iterator body_end)
    {
        uint32_t sum = (header.Type() << 8) + header.Code()
                           + header.Identifier() + header.SequenceNumber();

        Iterator body_iter = body_begin;
        while (body_iter != body_end)
        {
            sum += (static_cast<unsigned char>(*body_iter++) << 8);
            if (body_iter != body_end)
                sum += static_cast<unsigned char>(*body_iter++);
        }

        sum = (sum >> 16) + (sum & 0xFFFF);
        sum += (sum >> 16);
        header.Checksum(static_cast<uint16_t>(~sum));
    };
}

#endif //SR_UTILS_NETWORK_ICMPHEADER_H
```


