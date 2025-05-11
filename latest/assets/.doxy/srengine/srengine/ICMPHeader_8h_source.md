

# File ICMPHeader.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Network**](dir_fcfa5bace1b3a12e3000ff4cad4809c8.md) **>** [**Headers**](dir_5fb37d98e33c57c80beb790a969e531f.md) **>** [**ICMPHeader.h**](ICMPHeader_8h.md)

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


