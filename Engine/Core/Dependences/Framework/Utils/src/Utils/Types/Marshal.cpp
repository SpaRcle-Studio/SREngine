//
// Created by Monika on 12.03.2022.
//

#include <Utils/Types/Marshal.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_HTYPES_NS {
    Marshal::Marshal(Marshal &&marshal) noexcept {
#ifdef SR_MINGW
        m_stream.swap(marshal.m_stream);
#else
        m_stream = std::exchange(marshal.m_stream, {});
#endif
        m_size = std::exchange(marshal.m_size, {});
        m_position = std::exchange(marshal.m_position, {});
    }

    Marshal &Marshal::operator=(Marshal &&marshal) noexcept {
#ifdef SR_MINGW
        m_stream.swap(marshal.m_stream);
#else
        m_stream = std::exchange(marshal.m_stream, {});
#endif
        m_size = std::exchange(marshal.m_size, {});
        m_position = std::exchange(marshal.m_position, {});
        return *this;
    }

    bool Marshal::Save(const Path &path) const {
        std::ofstream file;

        file.open(path.ToString(), std::ios::binary);
        if (!file.is_open())
            return false;

        /// copy buffer
        file << m_stream.str();

        file.close();

        return true;
    }

    Marshal Marshal::Load(const Path &path) {
        Marshal marshal;

        std::ifstream file(path.ToString(), std::ios::binary);
        if (!file.is_open())
            return marshal;

        marshal.m_stream << file.rdbuf();
        marshal.m_size = file.tellg();

        file.close();

        return marshal;
    }

    Marshal Marshal::Copy() const {
        Marshal marshal;

        /// copy buffer
        marshal.m_stream << m_stream.str();
        marshal.m_size = m_size;
        marshal.m_position = 0;

        return marshal;
    }

    std::string Marshal::ToString() const {
        return m_stream.str();
    }

    Marshal Marshal::LoadFromMemory(const std::string &data) {
        Marshal marshal;

        marshal.m_size = data.size();
        marshal.m_stream = std::stringstream(data);

        return marshal;
    }

    Marshal Marshal::LoadFromBase64(const std::string &base64) {
        return LoadFromMemory(SR_UTILS_NS::StringUtils::Base64Decode(base64));
    }

    std::string Marshal::ToBase64() const {
        return SR_UTILS_NS::StringUtils::Base64Encode(ToString());
    }
}