//
// Created by OpenAI Codex on 22.11.2026.
//

#ifndef SR_ENGINE_TESTS_TEXTURE_PIPELINE_TEST_H
#define SR_ENGINE_TESTS_TEXTURE_PIPELINE_TEST_H

#include <Engine/stdInclude.h>

#include <Utils/Tests/TestManager.h>

namespace SR_CORE_NS::Tests {
    class TexturePipelineTest : public SR_UTILS_NS::ITestController {
        SR_CLASS()
    public:
        SR_UTILS_NS::TestExecutionResult Run() override;
    };
}

#endif //SR_ENGINE_TESTS_TEXTURE_PIPELINE_TEST_H
