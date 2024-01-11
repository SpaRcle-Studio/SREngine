//
// Created by Monika on 09.08.2022.
//

#ifndef SR_ENGINE_ANYMARSHAL_H
#define SR_ENGINE_ANYMARSHAL_H

#include <Utils/Common/BaseMarshal.h>
#include <Utils/Types/Stream.h>

namespace SR_UTILS_NS::MarshalUtils {
    template<typename Any> static Any SR_FASTCALL LoadAny(SR_HTYPES_NS::Stream& stream) {
        auto&& type = static_cast<StandardType>(LoadValue<uint16_t>(stream));

        switch (type) {
            case StandardType::Bool: return LoadValue<bool>(stream);
            case StandardType::Int8: return LoadValue<int8_t>(stream);
            case StandardType::UInt8: return LoadValue<uint8_t>(stream);
            case StandardType::Int16: return LoadValue<int16_t>(stream);
            case StandardType::UInt16: return LoadValue<uint16_t>(stream);
            case StandardType::Int32: return LoadValue<int32_t>(stream);
            case StandardType::UInt32: return LoadValue<uint32_t>(stream);
            case StandardType::Int64: return LoadValue<int64_t>(stream);
            case StandardType::UInt64: return LoadValue<uint64_t>(stream);
            case StandardType::Float: return LoadValue<float_t>(stream);
            case StandardType::Double: return LoadValue<double_t>(stream);
            case StandardType::String: return LoadStr(stream);
            default:
                SRHalt0();
                return Any();
        }
    }

    template<typename Any> static void SR_FASTCALL SaveAny(SR_HTYPES_NS::Stream& stream, const Any& any) {
        try {
            auto&& type = GetStandardType<Any>(any);

            SaveValue(stream, static_cast<uint16_t>(type));

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
                case StandardType::String: SaveString(stream, std::any_cast<std::string>(any)); break;
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

#endif //SR_ENGINE_ANYMARSHAL_H
