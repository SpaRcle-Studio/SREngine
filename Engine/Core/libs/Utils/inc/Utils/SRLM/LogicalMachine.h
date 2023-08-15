//
// Created by Monika on 15.08.2023.
//

#ifndef SRENGINE_LOGICALMACHINE_H
#define SRENGINE_LOGICALMACHINE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Hashes.h>

namespace SR_SRLM_NS {
    static constexpr uint64_t NODE_BOOL_CONDITION = SR_COMPILE_TIME_CRC32_STR("BOOL_CONDITION");
    static constexpr uint64_t NODE_BOOL_AND = SR_COMPILE_TIME_CRC32_STR("BOOL_AND");
    static constexpr uint64_t NODE_BOOL_OR = SR_COMPILE_TIME_CRC32_STR("BOOL_OR");
    static constexpr uint64_t NODE_BOOL_NOT = SR_COMPILE_TIME_CRC32_STR("BOOL_NOT");

    static constexpr uint64_t NODE_INT_PLUS_INT = SR_COMPILE_TIME_CRC32_STR("INT_PLUS_INT");
    static constexpr uint64_t NODE_INT_MINUS_INT = SR_COMPILE_TIME_CRC32_STR("INT_MINUS_INT");
    static constexpr uint64_t NODE_INT_NEGATIVE = SR_COMPILE_TIME_CRC32_STR("INT_NEGATIVE");
    static constexpr uint64_t NODE_INT_TO_FLOAT = SR_COMPILE_TIME_CRC32_STR("INT_TO_FLOAT");

    static constexpr uint64_t NODE_FLOAT_PLUS_FLOAT = SR_COMPILE_TIME_CRC32_STR("FLOAT_PLUS_FLOAT");
    static constexpr uint64_t NODE_FLOAT_MINUS_FLOAT = SR_COMPILE_TIME_CRC32_STR("FLOAT_MINUS_FLOAT");
    static constexpr uint64_t NODE_FLOAT_NEGATIVE = SR_COMPILE_TIME_CRC32_STR("FLOAT_NEGATIVE");
    static constexpr uint64_t NODE_FLOAT_TO_INT = SR_COMPILE_TIME_CRC32_STR("FLOAT_TO_INT");

    static constexpr uint64_t NODE_LINK_DOT = SR_COMPILE_TIME_CRC32_STR("LINK_DOT");

    class LogicalMachine : public SR_UTILS_NS::NonCopyable {

    };
}

#endif //SRENGINE_LOGICALMACHINE_H
