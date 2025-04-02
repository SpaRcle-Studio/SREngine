

# File Evaluator.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**Evaluator.h**](Evaluator_8h.md)

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


