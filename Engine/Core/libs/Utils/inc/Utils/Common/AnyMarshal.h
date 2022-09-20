//
// Created by Monika on 09.08.2022.
//

#ifndef SRENGINE_ANYMARSHAL_H
#define SRENGINE_ANYMARSHAL_H

#include <Utils/Common/BaseMarshal.h>

namespace SR_UTILS_NS::MarshalUtils {
    template<typename Stream, typename Any> static Any SR_FASTCALL LoadAny(Stream& stream, uint64_t& readCount) {
        auto&& type = static_cast<StandardType>(LoadValue<Stream, uint16_t>(stream, readCount));

        switch (type) {
            case StandardType::Bool: return LoadValue<Stream, bool>(stream, readCount);
            case StandardType::Int8: return LoadValue<Stream, int8_t>(stream, readCount);
            case StandardType::UInt8: return LoadValue<Stream, uint8_t>(stream, readCount);
            case StandardType::Int16: return LoadValue<Stream, int16_t>(stream, readCount);
            case StandardType::UInt16: return LoadValue<Stream, uint16_t>(stream, readCount);
            case StandardType::Int32: return LoadValue<Stream, int32_t>(stream, readCount);
            case StandardType::UInt32: return LoadValue<Stream, uint32_t>(stream, readCount);
            case StandardType::Int64: return LoadValue<Stream, int64_t>(stream, readCount);
            case StandardType::UInt64: return LoadValue<Stream, uint64_t>(stream, readCount);
            case StandardType::Float: return LoadValue<Stream, float_t>(stream, readCount);
            case StandardType::Double: return LoadValue<Stream, double_t>(stream, readCount);
            case StandardType::String: return LoadStr<Stream>(stream, readCount);
            default:
                SRHalt0();
                return Any();
        }
    }

    template<typename Stream, typename Any> static void SR_FASTCALL SaveAny(Stream& stream, const Any& any, uint64_t& bytesCount) {
        try {
            auto&& type = GetStandardType<Any>(any);

            SaveValue(stream, static_cast<uint16_t>(type));

            bytesCount += sizeof(StandardType);

            /// string ignored
            bytesCount += GetTypeSize(type);

            switch (type) {
                case StandardType::Bool: SaveValue(stream, std::any_cast<bool>(any)); break;
                case StandardType::Int8: SaveValue(stream, std::any_cast<int8_t>(any)); break;
                case StandardType::UInt8: SaveValue(stream, std::any_cast<uint8_t>(any)); break;
                case StandardType::Int16: SaveValue(stream, std::any_cast<int16_t>(any)); break;
                case StandardType::UInt16: SaveValue(stream, std::any_cast<uint16_t>(any)); break;
                case StandardType::Int32: SaveValue(stream, std::any_cast<int32_t>(any)); break;
                case StandardType::UInt32: SaveValue(stream, std::any_cast<uint32_t>(any)); break;
                case StandardType::Int64: SaveValue(stream, std::any_cast<int64_t>(any)); break;
                case StandardType::UInt64: SaveValue(stream, std::any_cast<uint64_t>(any)); break;
                case StandardType::Float: SaveValue(stream, std::any_cast<float_t>(any)); break;
                case StandardType::Double: SaveValue(stream, std::any_cast<double_t>(any)); break;
                case StandardType::String: SaveString(stream, std::any_cast<std::string>(any), bytesCount); break;
                default:
                    SRHalt0();
                    break;
            }
        }
        catch(const std::bad_any_cast& e) {
            SRHalt0();
        }
    }
}

#endif //SRENGINE_ANYMARSHAL_H
