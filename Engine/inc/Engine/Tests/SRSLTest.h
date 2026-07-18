//
// Created by Monika on 30.06.2025.
//

#ifndef SR_ENGINE_CORE_SRSL_TEST_H
#define SR_ENGINE_CORE_SRSL_TEST_H

#include <Engine/macros.h>

#include <Graphics/SRSL/Shader.h>
#include <Graphics/SRSL/GLSLCodeGenerator.h>
#include <Graphics/SRSL/WGSLCodeGenerator.h>
#include <Graphics/Pipeline/ShaderUtils.h>

#include <Utils/Resources/ResourceManager.h>
#include <Utils/Tests/TestManager.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Memory/Allocator.h>
#include <Utils/Memory/MemoryLiterals.h>

#include <Enum/ShaderStage.hpp>

namespace SR_CORE_NS::Tests {
    class SRSLTest : public SR_UTILS_NS::ITestController {
        SR_CLASS()
    public:
        SR_UTILS_NS::TestExecutionResult Run() override {
            SR_TRACY_ZONE;

            SR_SRSL_NS::SRSLShader::ClearShadersCache();

            const SR_UTILS_NS::Path path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("ModuleTests/SRSL");
            auto&& expectedFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("ModuleTests/SRSL/Expected");
            auto&& resultFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("ModuleTests/SRSL/Result");

            SR_UTILS_NS::Vector<SR_UTILS_NS::Path> files;
            path.GetFiles(files);
            for (auto file : files) {
                if (file.GetExtension() != "srsl") {
                    continue;
                }

                file = file.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
                SR_TRACY_ZONE_TEXT_VIEW(file.View());

                m_allocator.ResetMemory();
                if (auto&& pShader = SR_SRSL_NS::SRSLShader::Load(&m_allocator, file, SR_SRSL_NS::ShaderParams::GetDefault())) {
                    SR_SRSL_NS::ISRSLCodeGenerator::SRSLCodeGenRes result = SR_SRSL_NS::GLSLCodeGenerator::Instance().GenerateStages(pShader->GetAllocator(), pShader.Get());
                    for (auto&& [stage, code] : result.second) {
                        resultFolder.CreateIfNotExists();
                        auto outputFile = resultFolder.Concat(file.GetBaseNameAndExt()).ConcatExt(SR_UTILS_NS::EnumReflector::ToStringAtom(stage).ToString() + ".glsl");
                        if (!SR_UTILS_NS::FileSystem::WriteToFile(outputFile, code)) {
                            SR_ERROR("SRSLTest::Run() : failed to write shader stage to file: {}", outputFile);
                            return SR_UTILS_NS::TestExecutionResult::Error;
                        }
                    }

                    pShader->GetCreateInfo().vertexLayoutDescriptions.AddLayout()
                        .AddAttribute(SR_UTILS_NS::VertexAttribute::Position, SR_UTILS_NS::VertexAttributeFormat::Float32, 3)
                        .AddAttribute(SR_UTILS_NS::VertexAttribute::Normal, SR_UTILS_NS::VertexAttributeFormat::Float32, 3)
                        .AddAttribute(SR_UTILS_NS::VertexAttribute::Tangent, SR_UTILS_NS::VertexAttributeFormat::Float32, 4)
                        .AddAttribute(SR_UTILS_NS::VertexAttribute::UV0, SR_UTILS_NS::VertexAttributeFormat::Float32, 2)
                    ;

                    result = SR_SRSL_NS::WGSLCodeGenerator::Instance().GenerateStages(pShader->GetAllocator(), pShader.Get());
                    resultFolder.CreateIfNotExists();
                    auto outputFile = resultFolder.Concat(file.GetBaseName()).ConcatExt("wgsl");
                    if (!SR_UTILS_NS::FileSystem::WriteToFile(outputFile, result.second[SR_GRAPH_NS::ShaderStage::All])) {
                        SR_ERROR("SRSLTest::Run() : failed to write shader stage to file: {}", outputFile);
                        return SR_UTILS_NS::TestExecutionResult::Error;
                    }
                }
                else {
                    SR_ERROR("SRSLTest::Run() : failed to load SRSL shader: {}", file);
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }
            }

            resultFolder.GetFiles(files);
            const uint32_t resultCount = files.size();

            expectedFolder.GetFiles(files);
            const uint32_t expectedCount = files.size();

            if (expectedCount != resultCount) {
                SR_ERROR("SRSLTest::Run() : expected {} shader files, but found {} in result folder!", expectedCount, resultCount);
                return SR_UTILS_NS::TestExecutionResult::Error;
            }

            uint32_t errors = 0;
            const uint32_t maxErrors = 128;

            for (auto file : files) {
                auto expectedFile = expectedFolder.Concat(file.GetBaseNameAndExt());
                auto resultFile = resultFolder.Concat(file.GetBaseNameAndExt());

                if (!resultFile.Exists()) {
                    SR_ERROR("SRSLTest::Run() : result file does not exist: {}", resultFile);
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }

                std::vector<std::string> expectedCode = SR_UTILS_NS::FileSystem::ReadAllLines(expectedFile);
                std::vector<std::string> resultCode = SR_UTILS_NS::FileSystem::ReadAllLines(resultFile);

                if (expectedCode.size() != resultCode.size()) {
                    SR_ERROR("SRSLTest::Run() : expected and result shader files have different number of lines: {} vs {}", expectedFile, resultFile);
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }

                for (size_t i = 0; i < expectedCode.size(); ++i) {
                    if (expectedCode[i] != resultCode[i]) {
                        SR_ERROR("SRSLTest::Run() : expected and result shader files differ at line {}: \nExpected: {}\nResult: {}", i + 1, expectedCode[i], resultCode[i]);
                        ++errors;
                        if (errors >= maxErrors) {
                            SR_ERROR("SRSLTest::Run() : too many errors, stopping test!");
                            return SR_UTILS_NS::TestExecutionResult::Error;
                        }
                    }
                }
            }

            if (errors > 0) {
                SR_ERROR("SRSLTest::Run() : found {} errors in shader files!", errors);
                return SR_UTILS_NS::TestExecutionResult::Error;
            }
            return SR_UTILS_NS::TestExecutionResult::Success;
        }

    private:
        SR_UTILS_NS::MonotonicAllocator m_allocator { 1_MB };

    };
}

#endif //SR_ENGINE_CORE_SRSL_TEST_H
