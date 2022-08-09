//
// Created by Monika on 30.03.2022.
//

#ifndef SRENGINE_MARSHALUTILS_H
#define SRENGINE_MARSHALUTILS_H

#include <Utils/Common/StringFormat.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>
#include <Utils/Common/TypeInfo.h>
#include <Utils/Common/AnyMarshal.h>
#include <Utils/Common/BaseMarshal.h>

namespace SR_UTILS_NS {
    namespace MarshalUtils {
        static void Encode(std::stringstream& stream, const std::string& str, StandardType type) {
            uint64_t bytesCount = 0;
            switch (type) {
                case StandardType::Bool: SaveValue(stream, LexicalCast<bool>(str)); break;
                case StandardType::Int8: SaveValue(stream, LexicalCast<int8_t>(str)); break;
                case StandardType::UInt8: SaveValue(stream, LexicalCast<uint8_t>(str)); break;
                case StandardType::Int16: SaveValue(stream, LexicalCast<int16_t>(str)); break;
                case StandardType::UInt16: SaveValue(stream, LexicalCast<uint16_t>(str)); break;
                case StandardType::Int32: SaveValue(stream, LexicalCast<int32_t>(str)); break;
                case StandardType::UInt32: SaveValue(stream, LexicalCast<uint32_t>(str)); break;
                case StandardType::Int64: SaveValue(stream, LexicalCast<int64_t>(str)); break;
                case StandardType::UInt64: SaveValue(stream, LexicalCast<uint64_t>(str)); break;
                case StandardType::Float: SaveValue(stream, LexicalCast<float_t>(str)); break;
                case StandardType::Double: SaveValue(stream, LexicalCast<double_t>(str)); break;
                case StandardType::String: SaveString(stream, str, bytesCount); break;
            }
        }
    }

    enum class MarshalSaveMode {
        Binary,
        Json
    };
}

#endif //SRENGINE_MARSHALUTILS_H
