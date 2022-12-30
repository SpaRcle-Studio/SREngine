//
// Created by Monika on 12.03.2022.
//

#ifndef SRENGINE_MARSHAL_H
#define SRENGINE_MARSHAL_H

#include <Utils/Common/MarshalUtils.h>

#include <Utils/FileSystem/Path.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/StringFormat.h>

namespace SR_HTYPES_NS {
    class SR_DLL_EXPORT Marshal {
    public:
        using Ptr = Marshal*;

    public:
        Marshal() = default;

        Marshal(Marshal&& marshal) noexcept;
        Marshal& operator=(Marshal&& marshal) noexcept;
        Marshal& operator=(const Marshal& marshal) = delete;
        Marshal(const Marshal& marshal) = delete;

    public:
        bool Save(const Path& path) const;
        SR_NODISCARD Marshal Copy() const;
        SR_NODISCARD Marshal::Ptr CopyPtr() const;

        static Marshal Load(const Path& path);
        static Marshal::Ptr LoadPtr(const Path& path);
        static Marshal LoadFromMemory(const std::string& data);
        static Marshal LoadFromBase64(const std::string& base64);

        SR_NODISCARD bool Valid() const { return BytesCount() > 0; }
        SR_NODISCARD uint64_t GetPosition() const { return m_position; }
        SR_NODISCARD uint64_t BytesCount() const { return m_size; }
        SR_NODISCARD std::string ToString() const;
        SR_NODISCARD std::string ToBase64() const;

        void Append(Marshal&& marshal) {
            if (marshal.m_size > 0) {
                m_size += marshal.m_size;
                m_stream << marshal.m_stream.rdbuf();
            }
        }

        void Append(Marshal::Ptr& pMarshal) {
            if (pMarshal && pMarshal->m_size > 0) {
                m_size += pMarshal->m_size;
                m_stream << pMarshal->m_stream.rdbuf();
            }

            SR_SAFE_DELETE_PTR(pMarshal);
        }

        void SkipBytes(uint32_t size) {
            std::string buffer;
            buffer.resize(size);
            m_stream.read((char*)&buffer[0], size * sizeof(char));
            m_position += size * sizeof(char);
        }

        Marshal ReadBytes(uint32_t size) {
            Marshal marshal;

            std::string buffer;
            buffer.resize(size);
            m_stream.read((char*)&buffer[0], size * sizeof(char));
            m_position += size * sizeof(char);

            marshal.m_stream << buffer;
            marshal.m_size = size;

            return marshal;
        }

        SR_NODISCARD Marshal::Ptr ReadBytesPtr(uint32_t size) {
            auto&& pMarshal = new Marshal();

            std::string buffer;
            buffer.resize(size);
            m_stream.read((char*)&buffer[0], size * sizeof(char));
            m_position += size * sizeof(char);

            pMarshal->m_stream << buffer;
            pMarshal->m_size = size;

            return pMarshal;
        }

        template<typename T> void Write(const T& value) {
            if constexpr (std::is_same_v<T, std::any>) {
                MarshalUtils::SaveAny<std::stringstream, std::any>(m_stream, value, m_size);
            }
            else if constexpr (Math::IsString<T>()) {
                MarshalUtils::SaveShortString(m_stream, value, m_size);
            }
            else if constexpr (IsSTLVector<T>()) {
                MarshalUtils::SaveVector(m_stream, value, m_size);
            }
            else {
                m_size += sizeof(T);
                MarshalUtils::SaveValue(m_stream, value);
            }
        }

        template<typename T> void Write(const T& value, const T& def) {
            if (value == def) {
                Write<bool>(true);
            }
            else {
                Write<bool>(false);
                Write<T>(value);
            }
        }

        template<typename T> T View(uint64_t offset) const {
            T value = T();
            const auto buff = m_stream.rdbuf();

            memcpy(
                    &value,
                    buff->str().substr(offset, sizeof(T)).data(),
                    sizeof(T)
            );
            return value;
        }


        template<typename T> T Read() {
            if constexpr (std::is_same_v<T, std::any>) {
                return MarshalUtils::LoadAny<std::stringstream, std::any>(m_stream, m_position);
            }
            else if constexpr (Math::IsString<T>()) {
                return MarshalUtils::LoadShortStr<std::stringstream>(m_stream, m_position);
            }
            else {
                return MarshalUtils::LoadValue<std::stringstream, T>(m_stream, m_position);
            }
        }

        template<typename T> T Read(const T& def) {
            if (Read<bool>()) {
                return def;
            }

            return Read<T>();
        }

    private:
        std::stringstream m_stream;
        uint64_t m_size = 0;
        uint64_t m_position = 0;

    };
}

#endif //SRENGINE_MARSHAL_H
