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
#include <Utils/FileSystem/VFS.h>
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

            const SR_UTILS_NS::Path path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/ModuleTests/SRSL");
            auto&& expectedFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/ModuleTests/SRSL/Expected");
            auto&& resultFolder = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Tests/SRSL/Result");
            if (resultFolder.IsExists()) {
                SR_UTILS_NS::VFS::Instance().Delete(resultFolder);
            }

            SR_UTILS_NS::Vector<SR_UTILS_NS::Path> files;
            path.GetFiles(files);
            for (auto file : files) {
                if (file.GetExtension() != "srsl") {
                    continue;
                }

                file = file.RemoveSubPath(CoreResLoader::GetResPath());
                file = CoreResLoader::GetResPath().Concat(file);
                SR_TRACY_ZONE_TEXT_VIEW(file.View());

                m_allocator.ResetMemory();
                if (auto&& pShader = SR_SRSL_NS::SRSLShader::Load(&m_allocator, file, SR_SRSL_NS::ShaderParams::GetDefault())) {
                    SR_SRSL_NS::ISRSLCodeGenerator::SRSLCodeGenRes result = SR_SRSL_NS::GLSLCodeGenerator::Instance().GenerateStages(pShader->GetAllocator(), pShader.Get());
                    if (result.first.HasErrors() || result.second.empty()) {
                        SR_ERROR("SRSLTest::Run() : GLSL generation failed: {}", file);
                        return SR_UTILS_NS::TestExecutionResult::Error;
                    }
                    for (auto&& [stage, code] : result.second) {
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

                    if (result.first.HasErrors() || result.second.empty()) {
                        SR_ERROR("SRSLTest::Run() : WGSL generation failed: {}", file);
                        return SR_UTILS_NS::TestExecutionResult::Error;
                    }
                    const auto& moduleCode = result.second.begin()->second;
                    for (auto&& [stage, code] : result.second) {
                        if (stage == SR_GRAPH_NS::ShaderStage::All || code != moduleCode) {
                            SR_ERROR("SRSLTest::Run() : inconsistent WGSL stage module: {}", file);
                            return SR_UTILS_NS::TestExecutionResult::Error;
                        }
                    }
                    for (auto&& [stage, code] : result.second) {
                        auto outputFile = resultFolder.Concat(file.GetBaseNameView()).ConcatExt("wgsl");
                        if (!SR_UTILS_NS::FileSystem::WriteToFile(outputFile, code)) {
                            SR_ERROR("SRSLTest::Run() : failed to write shader stage to file: {}", outputFile);
                            return SR_UTILS_NS::TestExecutionResult::Error;
                        }
                        break;
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

            for (auto&& file : files) {
                auto expectedFile = expectedFolder.Concat(file.GetBaseNameAndExt());
                auto resultFile = resultFolder.Concat(file.GetBaseNameAndExt());

                if (!resultFile.IsFile()) {
                    SR_ERROR("SRSLTest::Run() : result file does not exist: {}", resultFile);
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }

                SR_UTILS_NS::String expectedBuffer, resultBuffer;
                auto&& expectedCode = SR_UTILS_NS::FileSystem::ReadAllLines(expectedFile, expectedBuffer);
                auto&& resultCode = SR_UTILS_NS::FileSystem::ReadAllLines(resultFile, resultBuffer);

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
            return RunRegressions();
        }

    private:
        SR_UTILS_NS::TestExecutionResult RunRegressions() {
            const auto invalidGLSL = SR_SRSL_NS::GLSLCodeGenerator::Instance().GenerateStages(&m_allocator, nullptr);
            const auto invalidWGSL = SR_SRSL_NS::WGSLCodeGenerator::Instance().GenerateStages(&m_allocator, nullptr);
            if (!invalidGLSL.first.HasErrors() || !invalidGLSL.second.empty()
                || !invalidWGSL.first.HasErrors() || !invalidWGSL.second.empty())
            {
                return SR_UTILS_NS::TestExecutionResult::Error;
            }
            struct Regression {
                const char* file;
                const char* expected;
                uint32_t count;
                bool packedVertex = false;
            };
            const Regression cases[] = {
                { "nested-while", "loop {", 2 },
                { "shared-function", "fn SharedValue(", 1 },
                { "type-scopes", "sr_mat3_from_mat4(m)", 1 },
                { "vertex-formats", "VERTEX_INPUT : vec4<f32>", 1, true },
                { "early-return", "return vsOut;", 2 },
                { "matrix-helpers", "fn sr_inverse3(", 1 },
                { "member-ssbo", "item.weight", 2 },
                { "sampler-parameter", "ReadTexture(source, source_sampler,", 1 },
            };
            for (const auto& regression : cases) {
                SR_UTILS_NS::MonotonicAllocator allocator;
                const auto path = SR_UTILS_NS::ResourceManager::Instance().GetResPath()
                    .Concat("Engine/ModuleTests/SRSL/Regression");
                const auto file = path.Concat(regression.file).ConcatExt("srsl");
                auto shader = SR_SRSL_NS::SRSLShader::Load(&allocator, file, SR_SRSL_NS::ShaderParams::GetDefault());
                if (!shader) {
                    SR_ERROR("SRSLTest: failed to load regression {}", file);
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }
                if (regression.packedVertex) {
                    shader->GetCreateInfo().vertexLayoutDescriptions.AddLayout().AddAttribute(
                        SR_UTILS_NS::VertexAttribute::Position, SR_UTILS_NS::VertexAttributeFormat::R10G10B10A2_UNorm, 4);
                }
                auto result = SR_SRSL_NS::WGSLCodeGenerator::Instance().GenerateStages(&allocator, shader.Get());
                if (result.first.HasErrors() || result.second.empty()) {
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }
                const auto& code = result.second.begin()->second;
                uint32_t count = 0;
                for (auto offset = code.find(regression.expected); offset != SR_UTILS_NS::String::npos;
                     offset = code.find(regression.expected, offset + 1))
                {
                    ++count;
                }
                if (count != regression.count) {
                    SR_ERROR("SRSLTest: {}: expected {} occurrences of '{}', got {}",
                        file, regression.count, regression.expected, count);
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }
                const auto outputFolder = SR_UTILS_NS::ResourceManager::Instance().GetCachePath()
                    .Concat("Tests/SRSL/Regression");
                if (!SR_UTILS_NS::FileSystem::WriteToFile(outputFolder.Concat(regression.file).ConcatExt("wgsl"), code)) {
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }
                auto glsl = SR_SRSL_NS::GLSLCodeGenerator::Instance().GenerateStages(&allocator, shader.Get());
                if (glsl.first.HasErrors() || glsl.second.size() != result.second.size()) {
                    SR_ERROR("SRSLTest: inconsistent stage set: {}", file);
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }
                for (const auto& [stage, source] : glsl.second) {
                    if (result.second.find(stage) == result.second.end()) {
                        return SR_UTILS_NS::TestExecutionResult::Error;
                    }
                    const auto outputFile = outputFolder.Concat(regression.file)
                        .ConcatExt(SR_UTILS_NS::EnumReflector::ToStringAtom(stage).ToString() + ".glsl");
                    if (!SR_UTILS_NS::FileSystem::WriteToFile(outputFile, source)) {
                        return SR_UTILS_NS::TestExecutionResult::Error;
                    }
                }
                auto repeated = SR_SRSL_NS::WGSLCodeGenerator::Instance().GenerateStages(&allocator, shader.Get());
                if (repeated.first.HasErrors() || repeated.second.size() != result.second.size()
                    || repeated.second.empty() || repeated.second.begin()->second != code) {
                    SR_ERROR("SRSLTest: generation is not repeatable: {}", file);
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }
                // Results must remain valid across a subsequent generator invocation.
                if (code.empty()) {
                    return SR_UTILS_NS::TestExecutionResult::Error;
                }
            }
            return SR_UTILS_NS::TestExecutionResult::Success;
        }

        SR_UTILS_NS::MonotonicAllocator m_allocator { 1_MB };

    };
}

#endif //SR_ENGINE_CORE_SRSL_TEST_H
