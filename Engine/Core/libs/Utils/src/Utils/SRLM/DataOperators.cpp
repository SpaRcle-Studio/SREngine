//
// Created by innerviewer on 8/26/2023.
//

#include <Utils/SRLM/DataOperators.h>

/// --------------------------------------------------------------------------------------------------------------------

#define SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, type, operator)                                                     \
    case DataTypeClass::type:                                                                                           \
        return DataTypeAllocator::Instance().Allocate(DataTypeClass::type)                                              \
            ->SetCustomValue(*pFirst->Get##type() operator *pSecond->Get##type());                                      \

/// --------------------------------------------------------------------------------------------------------------------

#define SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, type, operator)                                                         \
    case DataTypeClass::type:                                                                                           \
        return DataTypeAllocator::Instance().Allocate(DataTypeClass::Bool)                                              \
            ->SetCustomValue(pFirst->Get##type() operator pSecond->Get##type());                                        \

namespace SR_SRLM_NS {

    DataType* DataOperatorAddition::Calculate(DataType* pFirst, DataType* pSecond) {
        if (pFirst->GetClass() != pSecond->GetClass()) {
            SRHalt("Types are not the same!");
            return nullptr;
        }

        switch (pFirst->GetClass()) {
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Float,  +)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int8,   +)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int16,  +)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int32,  +)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int64,  +)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt8,  +)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt16, +)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt32, +)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt64, +)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Double, +)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, String, +)

            default:
                SRHalt("Unknown type!");
                return nullptr;
        }
    }

    DataType* DataOperatorSubtraction::Calculate(DataType* pFirst, DataType* pSecond) {
        if (pFirst->GetClass() != pSecond->GetClass()) {
            SRHalt("Types are not the same!");
            return nullptr;
        }

        switch (pFirst->GetClass()) {
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Float,  -)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int8,   -)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int16,  -)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int32,  -)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int64,  -)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt8,  -)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt16, -)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt32, -)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt64, -)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Double, -)

            default:
                SRHalt("Unknown type!");
                return nullptr;
        }
    }

    DataType* DataOperatorMultiplication::Calculate(DataType* pFirst, DataType* pSecond) {
        if (pFirst->GetClass() != pSecond->GetClass()) {
            SRHalt("Types are not the same!");
            return nullptr;
        }

        switch (pFirst->GetClass()) {
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Float,  *)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int8,   *)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int16,  *)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int32,  *)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int64,  *)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt8,  *)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt16, *)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt32, *)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt64, *)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Double, *)

            default:
                SRHalt("Unknown type!");
                return nullptr;
        }
    }

    DataType* DataOperatorDivision::Calculate(DataType* pFirst, DataType* pSecond) {
        if (pFirst->GetClass() != pSecond->GetClass()) {
            SRHalt("Types are not the same!");
            return nullptr;
        }

        switch (pFirst->GetClass()) {
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Float,  /)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int8,   /)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int16,  /)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int32,  /)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int64,  /)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt8,  /)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt16, /)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt32, /)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt64, /)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Double, /)

            default:
                SRHalt("Unknown type!");
                return nullptr;
        }
    }

    DataType* DataOperatorModulo::Calculate(DataType* pFirst, DataType* pSecond) {
        if (pFirst->GetClass() != pSecond->GetClass()) {
            SRHalt("Types are not the same!");
            return nullptr;
        }

        switch (pFirst->GetClass()) {
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int8,   %)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int16,  %)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int32,  %)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, Int64,  %)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt8,  %)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt16, %)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt32, %)
            SR_LM_OPERATOR_CALCULATION(pFirst, pSecond, UInt64, %)

            default:
                SRHalt("Unknown type!");
                return nullptr;
        }
    }

    DataType* DataOperatorIsEqual::Calculate(DataType* pFirst, DataType* pSecond) {
        if (pFirst->GetClass() != pSecond->GetClass()) {
            SRHalt("Types are not the same!");
            return nullptr;
        }

        switch (pFirst->GetClass()) {
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Float,  ==)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Int8,   ==)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Int16,  ==)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Int32,  ==)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Int64,  ==)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, UInt8,  ==)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, UInt16, ==)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, UInt32, ==)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, UInt64, ==)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Double, ==)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, String, ==)

            default:
                SRHalt("Unknown type!");
                return nullptr;
        }
    }

    DataType* DataOperatorIsNotEqual::Calculate(DataType* pFirst, DataType* pSecond) {
        DataType* result = DataOperatorIsEqual::Calculate(pFirst, pSecond);
        return result->SetCustomValue(!result->GetBool());
    }

    DataType* DataOperatorIsGreater::Calculate(DataType* pFirst, DataType* pSecond) {
        if (pFirst->GetClass() != pSecond->GetClass()) {
            SRHalt("Types are not the same!");
            return nullptr;
        }

        switch (pFirst->GetClass()) {
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Float,  >)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Int8,   >)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Int16,  >)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Int32,  >)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Int64,  >)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, UInt8,  >)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, UInt16, >)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, UInt32, >)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, UInt64, >)
            SR_LM_LOGICAL_OPERATOR(pFirst, pSecond, Double, >)

            default:
                SRHalt("Unknown type!");
                return nullptr;
        }
    }

    DataType* DataOperatorIsLess::Calculate(DataType* pFirst, DataType* pSecond) {
        DataType* result = DataOperatorIsGreater::Calculate(pFirst, pSecond);
        return result->SetCustomValue(!result->GetBool());
    }

    DataType* DataOperatorIsGreaterOrEqual::Calculate(DataType* pFirst, DataType* pSecond) {
        DataType* isGreater = DataOperatorIsGreater::Calculate(pFirst, pSecond);
        DataType* isEqual = DataOperatorIsEqual::Calculate(pFirst, pSecond);
        DataType* result = DataTypeAllocator::Instance().Allocate(DataTypeClass::Bool);

        return isGreater || isEqual ? result->SetCustomValue(true) : result;
    }

    DataType* DataOperatorIsLessOrEqual::Calculate(DataType* pFirst, DataType* pSecond) {
        DataType* isLess = DataOperatorIsLess::Calculate(pFirst, pSecond);
        DataType* isEqual = DataOperatorIsEqual::Calculate(pFirst, pSecond);
        DataType* result = DataTypeAllocator::Instance().Allocate(DataTypeClass::Bool);

        return isLess || isEqual ? result->SetCustomValue(true) : result;
    }
}