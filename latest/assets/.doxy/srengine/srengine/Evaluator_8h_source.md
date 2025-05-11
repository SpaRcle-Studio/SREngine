

# File Evaluator.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**Evaluator.h**](Evaluator_8h.md)

[Go to the documentation of this file](Evaluator_8h.md)


```C++
//
// Created by Monika on 06.02.2023.
//

#ifndef SR_ENGINE_SRSL_EVALUATOR_H
#define SR_ENGINE_SRSL_EVALUATOR_H

#include <Graphics/SRSL/LexicalTree.h>
#include <Graphics/SRSL/ShaderType.h>

namespace SR_SRSL_NS {
    class SRSLEvaluator : public SR_UTILS_NS::Singleton<SRSLEvaluator> {
        SR_REGISTER_SINGLETON(SRSLEvaluator)
    public:
        SR_NODISCARD double_t Evaluate(const std::string& code);
        SR_NODISCARD double_t Evaluate(const SRSLExpr* pExpr);

    private:
        SR_NODISCARD double_t ApplyOperator(const std::string& op, double_t left, double_t right) const;

    };
}

#endif //SR_ENGINE_SRSL_EVALUATOR_H
```


