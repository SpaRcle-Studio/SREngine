

# File DataOperators.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**SRLM**](dir_ccfa529a2c413666958bcf1b1fc32cf9.md) **>** [**DataOperators.h**](DataOperators_8h.md)

[Go to the documentation of this file](DataOperators_8h.md)


```C++
//
// Created by innerviewer on 8/26/2023.
//

#ifndef SR_ENGINE_DATAOPERATORS_H
#define SR_ENGINE_DATAOPERATORS_H

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

#endif //SR_ENGINE_DATAOPERATORS_H
```


