//
// Created by Monika on 11.07.2022.
//

#ifndef SRENGINE_SHADERPROGRAMMANAGER_H
#define SRENGINE_SHADERPROGRAMMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Environment/Basic/IShaderProgram.h>
#include <Utils/Types/Map.h>

namespace SR_GRAPH_NS::Memory {
    struct SR_DLL_EXPORT VirtualProgramInfo : public SR_UTILS_NS::NonCopyable {
        using Framebuffer = int32_t;
        using ShaderProgram = int32_t;
    public:
        VirtualProgramInfo() {
            m_data.reserve(8);
        }

        ~VirtualProgramInfo() override = default;

        VirtualProgramInfo(VirtualProgramInfo&& ref) noexcept {
            m_data = std::exchange(ref.m_data, {});
            m_createInfo = std::exchange(ref.m_createInfo, {});
        }

        VirtualProgramInfo& operator=(VirtualProgramInfo&& ref) noexcept {
            m_data = std::exchange(ref.m_data, {});
            m_createInfo = std::exchange(ref.m_createInfo, {});
            return *this;
        }

        ska::flat_hash_map<Framebuffer, ShaderProgram> m_data;
        SRShaderCreateInfo m_createInfo;

    };

    /**
     * Класс реализует возможность рендера одного объекта в несколько кадровых буферов
    */
    class SR_DLL_EXPORT ShaderProgramManager : public SR_UTILS_NS::Singleton<ShaderProgramManager> {
        friend class SR_UTILS_NS::Singleton<ShaderProgramManager>;
    public:
        using VirtualProgram = int32_t;
        using ShaderProgram = int32_t;
        enum class BindResult : uint8_t {
            Success,
            Duplicated,
            Failed
        };
    private:
        ShaderProgramManager();
        ~ShaderProgramManager() override;

    public:
        SR_NODISCARD VirtualProgram ReAllocate(VirtualProgram program, const SRShaderCreateInfo& createInfo);
        SR_NODISCARD VirtualProgram Allocate(const SRShaderCreateInfo& createInfo);

        bool FreeProgram(VirtualProgram* program);

        BindResult BindProgram(VirtualProgram virtualProgram) noexcept;

        SR_NODISCARD ShaderProgram GetProgram(VirtualProgram virtualProgram) const noexcept;

    private:
        SR_NODISCARD VirtualProgram GenerateUnique() const;

    protected:
        void OnSingletonDestroy() override;

    private:
        ska::flat_hash_map<VirtualProgram, VirtualProgramInfo> m_virtualTable;

    };
}

#endif //SRENGINE_SHADERPROGRAMMANAGER_H
