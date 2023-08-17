//
// Created by Monika on 18.01.2023.
//

#ifndef SRENGINE_STREAM_H
#define SRENGINE_STREAM_H

#include <Utils/stdInclude.h>

namespace SR_HTYPES_NS {
    class SR_DLL_EXPORT Stream {
    public:
        Stream() = default;
        Stream(std::ifstream& ifs);  /** NOLINT */
        Stream(const std::string& str);  /** NOLINT */
        Stream(const char* pData, uint64_t size);

        Stream(const Stream& other) noexcept;
        Stream(Stream&& other) noexcept;

        ~Stream();

    public:
        Stream& SR_FASTCALL operator=(const Stream& other) noexcept;
        Stream& SR_FASTCALL operator=(Stream&& other) noexcept;

        operator bool() const noexcept; /** NOLINT */

    public:
        SR_NODISCARD bool Valid() const noexcept { return m_data; }

        SR_NODISCARD std::string ToString() const noexcept;
        SR_NODISCARD std::string_view ToStringView() const noexcept;
        SR_NODISCARD std::string ToBase64() const noexcept;

        SR_NODISCARD uint64_t GetPosition() const noexcept { return m_pos; }
        SR_NODISCARD uint64_t Size() const noexcept { return m_size; }
        SR_NODISCARD uint64_t GetCapacity() const noexcept { return m_capacity; }

        SR_NODISCARD const char* View() const noexcept { return m_data; }

        Stream& SR_FASTCALL Write(const void* pSrc, uint64_t count) noexcept;
        Stream& SR_FASTCALL Read(void* pDst, uint64_t count) noexcept;
        Stream& SR_FASTCALL TryRead(void* pDst, uint64_t count) noexcept;

        Stream& SR_FASTCALL write(const void* pSrc, uint64_t count) noexcept { return Write(pSrc, count); }
        Stream& SR_FASTCALL read(void* pDst, uint64_t count) noexcept { return Read(pDst, count); }

        void SetData(const char* pData, uint64_t size);
        void SetPosition(uint64_t position);

        void SR_FASTCALL Reserve(uint64_t capacity);

        void Skip(uint64_t count);

    private:
        static char* Allocate(uint64_t size);
        static void Free(char* pData);

    private:
        uint64_t m_size = 0;
        uint64_t m_pos = 0;
        uint64_t m_capacity = 0;

        char* m_data = nullptr;

    };
}

#endif //SRENGINE_STREAM_H
