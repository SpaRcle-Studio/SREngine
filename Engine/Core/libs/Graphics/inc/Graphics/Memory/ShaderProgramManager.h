//
// Created by Monika on 11.07.2022.
//

#ifndef SRENGINE_SHADERPROGRAMMANAGER_H
#define SRENGINE_SHADERPROGRAMMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Map.h>

#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GRAPH_NS {
    class Pipeline;
}

namespace SR_GRAPH_NS::Memory {
    struct SR_DLL_EXPORT VirtualProgramInfo : public SR_UTILS_NS::NonCopyable {
        using Identifier = uint64_t;
        using ShaderProgram = int32_t;
    public:
        VirtualProgramInfo() {
            m_data.reserve(8);
        }

        ~VirtualProgramInfo() override = default;

        VirtualProgramInfo(VirtualProgramInfo&& ref) noexcept {
            m_data = SR_UTILS_NS::Exchange(ref.m_data, {});
            m_createInfo = SR_UTILS_NS::Exchange(ref.m_createInfo, {});
        }

        VirtualProgramInfo& operator=(VirtualProgramInfo&& ref) noexcept {
            m_data = SR_UTILS_NS::Exchange(ref.m_data, {});
            m_createInfo = SR_UTILS_NS::Exchange(ref.m_createInfo, {});
            return *this;
        }

        struct ShaderProgramInfo {
            ShaderProgram id = SR_ID_INVALID;
            bool depth = false;
            uint8_t samples = 1;

            SR_NODISCARD bool Valid() const { return id != SR_ID_INVALID; }
        };

        ska::flat_hash_map<Identifier, ShaderProgramInfo> m_data;
        SRShaderCreateInfo m_createInfo;

    };

    /**
     * Класс реализует возможность рендера одного объекта в несколько кадровых буферов
    */
    class SR_DLL_EXPORT ShaderProgramManager : public SR_UTILS_NS::Singleton<ShaderProgramManager> {
        SR_REGISTER_SINGLETON(ShaderProgramManager)
    public:
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<Pipeline>;
        using VirtualProgram = int32_t;
        using ShaderProgram = int32_t;
    private:
        ShaderProgramManager();
        ~ShaderProgramManager() override = default;

    public:
        void SetPipeline(PipelinePtr pPipeline) { m_pipeline = std::move(pPipeline); }

        SR_NODISCARD VirtualProgram ReAllocate(VirtualProgram program, const SRShaderCreateInfo& createInfo);
        SR_NODISCARD VirtualProgram Allocate(const SRShaderCreateInfo& createInfo);

        bool FreeProgram(VirtualProgram* program);
        bool FreeProgram(VirtualProgram program);

        void CollectUnusedShaders();

        ShaderBindResult BindProgram(VirtualProgram virtualProgram) noexcept;

        SR_NODISCARD const VirtualProgramInfo* GetInfo(VirtualProgram virtualProgram) const noexcept;
        SR_NODISCARD ShaderProgram GetProgram(VirtualProgram virtualProgram) const noexcept;
        SR_NODISCARD bool IsAvailable(VirtualProgram virtualProgram) const noexcept;
        SR_NODISCARD bool HasProgram(VirtualProgram virtualProgram) const noexcept;

    private:
        SR_NODISCARD VirtualProgramInfo::Identifier GetCurrentIdentifier() const;
        SR_NODISCARD VirtualProgramInfo::ShaderProgramInfo AllocateShaderProgram(const SRShaderCreateInfo& createInfo) const;
        SR_NODISCARD ShaderBindResult BindShaderProgram(VirtualProgramInfo::ShaderProgramInfo& shaderProgramInfo, const SRShaderCreateInfo& createInfo);
        SR_NODISCARD VirtualProgram GenerateUnique() const;

    protected:
        void OnSingletonDestroy() override;

    private:
        ska::flat_hash_map<VirtualProgram, VirtualProgramInfo> m_virtualTable;
        PipelinePtr m_pipeline;

    };
}

#endif //SRENGINE_SHADERPROGRAMMANAGER_H
