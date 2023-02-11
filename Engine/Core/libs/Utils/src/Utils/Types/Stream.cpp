//
// Created by Monika on 18.01.2023.
//

#include <Utils/Types/Stream.h>
#include <Utils/Common/StringUtils.h>

namespace SR_HTYPES_NS {
    Stream::Stream(const char *pData, uint64_t size)
        : m_capacity(size)
        , m_size(size)
        , m_pos(0)
    {
        m_data = Allocate(m_capacity);
        memcpy(m_data, pData, size);
    }

    Stream::Stream(std::ifstream& ifs)
        : m_pos(0)
    {
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(ifs), { });
        m_size = m_capacity = buffer.size();
        m_data = Allocate(m_capacity);
        memcpy(m_data, buffer.data(), m_capacity);
    }

    Stream::Stream(const std::string& str)
        : m_pos(0)
    {
        m_size = m_capacity = str.size();
        m_data = Allocate(m_capacity);
        memcpy(m_data, str.data(), m_size);
    }

    Stream::Stream(const Stream& other) noexcept
        : m_capacity(other.m_capacity)
        , m_size(other.m_size)
        , m_pos(0)
    {
        if (other.m_data) {
            m_data = Allocate(m_capacity);
            memcpy(m_data, other.m_data, m_capacity);
        }
    }

    Stream::Stream(Stream&& other) noexcept
        : m_data(SR_UTILS_NS::Exchange(other.m_data, { }))
        , m_pos(SR_UTILS_NS::Exchange(other.m_pos, { }))
        , m_size(SR_UTILS_NS::Exchange(other.m_size, { }))
        , m_capacity(SR_UTILS_NS::Exchange(other.m_capacity, { }))
    { }

    Stream::~Stream() {
        if (!m_data) {
            return;
        }
        Free(m_data);
    }

    Stream& Stream::operator=(const Stream& other) noexcept {
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_pos = 0;

        if (other.m_data) {
            m_data = Allocate(m_capacity);
            memcpy(m_data, other.m_data, m_capacity);
        }

        return *this;
    }

    Stream::operator bool() const noexcept {
        return m_data;
    }

    Stream& Stream::operator=(Stream&& other) noexcept {
        m_data = SR_UTILS_NS::Exchange(other.m_data, { });
        m_pos = SR_UTILS_NS::Exchange(other.m_pos, { });
        m_size = SR_UTILS_NS::Exchange(other.m_size, { });
        m_capacity = SR_UTILS_NS::Exchange(other.m_capacity, { });
        return *this;
    }

    Stream& Stream::Read(void* pDst, uint64_t count) noexcept {
        SRAssert(m_pos + count <= m_size);

        memcpy(pDst, m_data + m_pos, count);

        m_pos += count;

        return *this;
    }

    Stream& Stream::Write(const void* pSrc, uint64_t count) noexcept {
        m_size += count;

        if (m_size >= m_capacity) {
            Reserve(SR_MAX(m_size * 2, 64));
        }

        memcpy(m_data + m_pos, pSrc, count);

        m_pos += count;

        return *this;
    }

    void Stream::Reserve(uint64_t capacity) {
        if (m_capacity >= capacity) {
            return;
        }

        if (m_data) {
            char* pNewData = Allocate(capacity);
            char* pOldData = m_data;

            memcpy(pNewData, pOldData, m_capacity);

            Free(pOldData);

            m_data = pNewData;
        }
        else {
            m_data = Allocate(capacity);
        }

        m_capacity = capacity;

        SRAssert(m_capacity >= m_size);
    }

    void Stream::Skip(uint64_t count) {
        SRAssert(m_pos + count <= m_size);
        m_pos += count;
    }

    char* Stream::Allocate(uint64_t size) {
        char* pBlock = (char*)malloc(size);
        return pBlock;
    }

    void Stream::Free(char* pData) {
        free(pData);
    }

    std::string Stream::ToString() const noexcept {
        if (!m_data) {
            return std::string();
        }
        return std::string(m_data, m_size);
    }

    std::string_view Stream::ToStringView() const noexcept {
        if (!m_data) {
            return std::string_view();
        }
        return std::string_view(m_data, m_size);
    }

    std::string Stream::ToBase64() const noexcept {
        return SR_UTILS_NS::StringUtils::Base64Encode(ToString());
    }

    void Stream::SetData(const char* pData, uint64_t size) {
        m_size = m_capacity = size;
        memcpy(m_data, pData, m_capacity);
    }

    void Stream::SetPosition(uint64_t position) {
        m_pos = position;
        SRAssert(m_pos <= m_size);
    }
}
