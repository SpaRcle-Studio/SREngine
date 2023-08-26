//
// Created by innerviewer on 8/26/2023.
//

#ifndef SRENGINE_DATAOPERATORS_H
#define SRENGINE_DATAOPERATORS_H

namespace SR_SRLM_NS {
    class DataType;

    class DataOperator : SR_UTILS_NS::NonCopyable {
    public:
        SR_NODISCARD virtual DataType* Calculate(DataType* pFirst, DataType* pSecond) = 0;


    };

    class DataOperatorAddition : public DataOperator {
    public:
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };

    class DataOperatorSubtraction : public DataOperator {
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };

    class DataOperatorMultiplication : public DataOperator {
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };

    class DataOperatorDivision : public DataOperator {
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };

    class DataOperatorModulo : public DataOperator {
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };

    class DataOperatorIsEqual : public DataOperator {
    protected:
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };

    class DataOperatorIsNotEqual : public DataOperatorIsEqual {
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };

    class DataOperatorIsGreater : public DataOperator {
    protected:
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };

    class DataOperatorIsLess : public DataOperatorIsGreater {
    protected:
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };

    class DataOperatorIsGreaterOrEqual : public DataOperatorIsGreater, public DataOperatorIsEqual {
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };

    class DataOperatorIsLessOrEqual : public DataOperatorIsLess, public DataOperatorIsEqual {
        SR_NODISCARD DataType* Calculate(DataType* pFirst, DataType* pSecond) override;

    };
}

#endif //SRENGINE_DATAOPERATORS_H
