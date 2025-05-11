

# File Base64.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**Base64.h**](Base64_8h.md)

[Go to the documentation of this file](Base64_8h.md)


```C++
//
// Created by Monika on 01.02.2025.
//

#ifndef SR_ENGINE_UTILS_BASE64_H
#define SR_ENGINE_UTILS_BASE64_H

#include <Utils/stdInclude.h>

namespace SR_UTILS_NS {
    namespace Base64 {
        template <size_t N>
        struct FixedString : std::array<char, N> {
            constexpr explicit FixedString(const char (&input)[N]) : FixedString(input, std::make_index_sequence<N>{}) {}
            template <size_t... Is>
            constexpr FixedString(const char (&input)[N], std::index_sequence<Is...>) : std::array<char, N>{ input[Is]... } {}
        };

        template <size_t N> constexpr std::array<char, ((((N-1) >> 2) * 3) + 1)> CompileTimeDecode(const char(&input)[N]) {
            constexpr unsigned char kDecodingTable[] = {
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
                    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
                    64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
                    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
                    64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
                    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
            };

            static_assert(((N-1) & 3) == 0, "Input data size is not a multiple of 4");

            char out[(((N-1) >> 2) * 3) + 1] {0};

            size_t out_len = (N-1) / 4 * 3;
            if (input[(N-1) - 1] == '=') out_len--;
            if (input[(N-1) - 2] == '=') out_len--;

            for (size_t i = 0, j = 0; i < N-1;) {
                uint32_t a = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
                uint32_t b = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
                uint32_t c = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];
                uint32_t d = input[i] == '=' ? 0 & i++ : kDecodingTable[static_cast<int>(input[i++])];

                uint32_t triple = (a << 3 * 6) + (b << 2 * 6) + (c << 1 * 6) + (d << 0 * 6);

                if (j < out_len) out[j++] = (triple >> 2 * 8) & 0xFF;
                if (j < out_len) out[j++] = (triple >> 1 * 8) & 0xFF;
                if (j < out_len) out[j++] = (triple >> 0 * 8) & 0xFF;
            }
            return FixedString<(((N-1) >> 2) * 3) + 1>(out);
        }
    }
}

#endif //SR_ENGINE_UTILS_BASE64_H
```


