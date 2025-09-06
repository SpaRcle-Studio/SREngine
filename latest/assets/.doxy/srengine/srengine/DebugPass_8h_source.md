

# File DebugPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**DebugPass.h**](DebugPass_8h.md)

[Go to the documentation of this file](DebugPass_8h.md)


```C++
//
// Created by Monika on 19.09.2022.
//

#ifndef SR_ENGINE_GRAPHICS_DEBUG_PASS_H
#define SR_ENGINE_GRAPHICS_DEBUG_PASS_H

#include <Graphics/Pass/IMesh3DClusterPass.h>
#include <Graphics/Render/DebugRenderer.h>

namespace SR_GRAPH_NS {
    struct DebugPassShaderInfo : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        DebugPassShaderInfo() = default;
        ~DebugPassShaderInfo() override;

        void SetShader(const SR_UTILS_NS::Path& path);
        void LoadShader();

        struct MemInfo {
            Memory::UBOManager::VirtualUBO virtualUBO;
            DescriptorManager::VirtualDescriptorSet virtualDescriptor;
            bool isDirty = true;
        };

        SR_GTYPES_NS::Shader::Ptr pShader;
        uint32_t uboUsed = 0;
        std::vector<MemInfo> UBOs;
        std::vector<std::vector<DebugRenderer::DrawInfo>> drawQueues;

        SR_UTILS_NS::Path shaderPath;
    };

    class DebugPass : public BasePass {
        SR_CLASS()
        using Super = BasePass;
    protected:
        void Prepare() override;
        bool Render() override;
        void Update() override;

        bool Init() override;
        void DeInit() override;

        void OnResize(const SR_MATH_NS::UVector2& size) override;

        void BuildQueues();
        void DrawQueue(Pipeline& pipeline, const std::vector<DebugRenderer::DrawInfo>& queue, DebugPassShaderInfo& shaderInfo, uint32_t indicesCount);
        void UpdateUBO(DebugPassShaderInfo& shaderInfo, DebugRenderer::DrawType type);

    private:
        std::pair<uint32_t, uint32_t> m_linesCountCache;
        std::vector<std::pair<uint32_t, uint32_t>> m_meshesCountCache;
        bool m_hasRendered = false;
        bool m_isNeedUpdate = false;
        bool m_isValid = false;
        bool m_updateMeshesOnDemand = false;

        std::map<SR_UTILS_NS::StringAtom, DebugPassShaderInfo> m_shaders;

    };
}

#endif //SR_ENGINE_GRAPHICS_DEBUG_PASS_H
```


