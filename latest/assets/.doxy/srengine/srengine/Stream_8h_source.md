

# File Stream.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**Stream.h**](Stream_8h.md)

[Go to the documentation of this file](Stream_8h.md)


```C++
//
// Created by Monika on 18.01.2023.
//

#ifndef SR_ENGINE_STREAM_H
#define SR_ENGINE_STREAM_H

#include <Utils/stdInclude.h>

namespace SR_HTYPES_NS {
    class SR_COMMON_DLL_API Stream {
    public:
        Stream();
        Stream(std::ifstream& ifs);  
        Stream(const std::string& str);  
        Stream(const char* pData, uint64_t size, bool copy = true);

        Stream(const Stream& other) noexcept;
        Stream(Stream&& other) noexcept;

        ~Stream();

    public:
        static char* Allocate(uint64_t size);
        static void Free(char* pData);

    public:
        Stream& SR_FASTCALL operator=(const Stream& other) noexcept;
        Stream& SR_FASTCALL operator=(Stream&& other) noexcept;

        operator bool() const noexcept; 
    public:
        SR_NODISCARD bool Valid() const noexcept;

        SR_NODISCARD std::string ToString() const noexcept;
        SR_NODISCARD std::string_view ToStringView() const noexcept;
        SR_NODISCARD std::string ToBase64() const noexcept;

        SR_NODISCARD uint64_t GetPosition() const noexcept;
        SR_NODISCARD uint64_t Size() const noexcept;
        SR_NODISCARD uint64_t GetCapacity() const noexcept;

        SR_NODISCARD const char* View() const noexcept;

        Stream& SR_FASTCALL Write(const void* pSrc, uint64_t count) noexcept;
        Stream& SR_FASTCALL Read(void* pDst, uint64_t count) noexcept;
        Stream& SR_FASTCALL TryRead(void* pDst, uint64_t count) noexcept;

        Stream& SR_FASTCALL write(const void* pSrc, uint64_t count) noexcept;
        Stream& SR_FASTCALL read(void* pDst, uint64_t count) noexcept;

        void SetData(const char* pData, uint64_t size);
        void SetPosition(uint64_t position);

        void SR_FASTCALL Reserve(uint64_t capacity);

        void Skip(uint64_t count);

    private:
        uint64_t m_size = 0;
        uint64_t m_pos = 0;
        uint64_t m_capacity = 0;

        char* m_data = nullptr;

    };
}

#endif //SR_ENGINE_STREAM_H
```


