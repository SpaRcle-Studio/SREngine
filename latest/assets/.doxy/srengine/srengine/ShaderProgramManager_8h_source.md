

# File ShaderProgramManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Memory**](dir_cc5176abae198c1d3b7945975349bd99.md) **>** [**ShaderProgramManager.h**](ShaderProgramManager_8h.md)

[Go to the documentation of this file](ShaderProgramManager_8h.md)


```C++
//
// Created by Monika on 11.07.2022.
//

#ifndef SR_ENGINE_SHADERPROGRAMMANAGER_H
#define SR_ENGINE_SHADERPROGRAMMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Map.h>
#include <Utils/Types/ObjectPool.h>

#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GRAPH_NS {
    class Pipeline;
}

namespace SR_GRAPH_NS::Memory {
    struct SR_RENDERER_DLL_API VirtualProgramInfo : public SR_UTILS_NS::NonCopyable {
        using Identifier = uint64_t;
        using ShaderProgram = int32_t;
    public:
        VirtualProgramInfo() = default;
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

        SR_NODISCARD bool Valid() const { return m_createInfo.Validate(); }

        ShaderProgramInfo* SetProgramInfo(Identifier identifier, const ShaderProgramInfo& info) {
            for (auto&& [id, data] : m_data) {
                if (id == identifier) SR_UNLIKELY_ATTRIBUTE {
                    data = info;
                    return &data;
                }
            }

            return &m_data.emplace_back(identifier, info).second;
        }

        SR_NODISCARD bool HasProgram(Identifier identifier) const {
            const auto* pBegin = m_data.data();
            const auto* pEnd = pBegin + m_data.size();

            while (pBegin != pEnd) {
                if (pBegin->first == identifier) SR_LIKELY_ATTRIBUTE {
                    return true;
                }
                ++pBegin;
            }
            return false;
        }

        SR_NODISCARD ShaderProgramInfo* GetProgramInfo(Identifier identifier) {
            for (auto&& [id, data] : m_data) {
                if (id == identifier) SR_LIKELY_ATTRIBUTE {
                    return &data;
                }
            }

            return nullptr;
        }

        SR_NODISCARD const ShaderProgramInfo* GetProgramInfo(Identifier identifier) const noexcept {
            for (auto&& iter : m_data) {
                if (iter.first == identifier) SR_LIKELY_ATTRIBUTE {
                    return &iter.second;
                }
            }

            return nullptr;
        }

        SR_NODISCARD int32_t GetProgramId(Identifier identifier) const noexcept {
            for (auto&& iter : m_data) {
                if (iter.first == identifier) SR_LIKELY_ATTRIBUTE {
                    return iter.second.id;
                }
            }

            return SR_ID_INVALID;
        }

        std::vector<std::pair<Identifier, ShaderProgramInfo>> m_data;
        SRShaderCreateInfo m_createInfo;

    };

    class SR_RENDERER_DLL_API ShaderProgramManager : public SR_UTILS_NS::Singleton<ShaderProgramManager> {
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

        void CollectUnused();

        ShaderBindResult BindProgram(VirtualProgram virtualProgram) noexcept;

        SR_NODISCARD const VirtualProgramInfo* GetInfo(VirtualProgram virtualProgram) const noexcept;
        SR_NODISCARD ShaderProgram GetProgram(VirtualProgram virtualProgram) const noexcept;
        SR_NODISCARD bool IsAvailable(VirtualProgram virtualProgram) const noexcept;
        SR_NODISCARD bool HasProgram(VirtualProgram virtualProgram) const noexcept;

    private:
        SR_NODISCARD VirtualProgramInfo::Identifier GetCurrentIdentifier() const;
        SR_NODISCARD VirtualProgramInfo::ShaderProgramInfo AllocateShaderProgram(const SRShaderCreateInfo& createInfo) const;
        SR_NODISCARD ShaderBindResult BindShaderProgram(VirtualProgramInfo::ShaderProgramInfo& shaderProgramInfo, const SRShaderCreateInfo& createInfo);

    protected:
        void OnSingletonDestroy() override;

    private:
        SR_HTYPES_NS::ObjectPool<VirtualProgramInfo, VirtualProgram> m_programPool;
        PipelinePtr m_pipeline;

    };
}

#endif //SR_ENGINE_SHADERPROGRAMMANAGER_H
```


