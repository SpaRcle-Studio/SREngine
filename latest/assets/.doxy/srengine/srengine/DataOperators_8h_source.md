

# File DataOperators.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**SRLM**](dir_a6f28b551a04c8f6c9ec3f9b059c2feb.md) **>** [**DataOperators.h**](DataOperators_8h.md)

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


