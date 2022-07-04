//
// Created by Monika on 10.06.2022.
//

#ifndef SRENGINE_UBOMANAGER_H
#define SRENGINE_UBOMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Map.h>

namespace SR_GRAPH_NS {
    class Camera;
}

namespace SR_GRAPH_NS::Memory {
    struct VirtualUBOInfo : public SR_UTILS_NS::NonCopyable {
        using Descriptor = int32_t;
        using UBO = int32_t;

        VirtualUBOInfo() {
            m_data.reserve(8);
        }

        ~VirtualUBOInfo() override = default;

        VirtualUBOInfo(VirtualUBOInfo&& ref)  noexcept {
            m_data = std::exchange(ref.m_data, {});
            m_samples = std::exchange(ref.m_samples, {});
            m_uboSize = std::exchange(ref.m_uboSize, {});
            m_shaderProgram = std::exchange(ref.m_shaderProgram, {});
        }

        VirtualUBOInfo& operator=(VirtualUBOInfo&& ref) noexcept {
            m_data = std::exchange(ref.m_data, {});
            m_samples = std::exchange(ref.m_samples, {});
            m_uboSize = std::exchange(ref.m_uboSize, {});
            m_shaderProgram = std::exchange(ref.m_shaderProgram, {});
            return *this;
        }

        ska::flat_hash_map<Camera*, std::pair<UBO, Descriptor>> m_data;
        uint32_t m_samples = 0;
        uint32_t m_uboSize = 0;
        int32_t m_shaderProgram = SR_ID_INVALID;

    };

    /**
     * Класс реализует возможность рендера в несколько камер с нескольких ракурсов
    */
    class UBOManager : public SR_UTILS_NS::Singleton<UBOManager> {
        friend class SR_UTILS_NS::Singleton<UBOManager>;
        using VirtualUBO = int32_t;
        using Descriptor = int32_t;
        using UBO = int32_t;
    public:
        enum class BindResult : uint8_t {
            Success,
            Duplicated,
            Failed
        };
    private:
        UBOManager();
        ~UBOManager() override = default;

    public:
        void SetCurrentCamera(Camera* pCamera);

    public:
        SR_NODISCARD VirtualUBO ReAllocateUBO(VirtualUBO virtualUbo, uint32_t uboSize, uint32_t samples);
        SR_NODISCARD VirtualUBO AllocateUBO(uint32_t uboSize, uint32_t samples);
        bool FreeUBO(VirtualUBO* ubo);
        BindResult BindUBO(VirtualUBO ubo);

    private:
        SR_NODISCARD bool AllocMemory(UBO* ubo, Descriptor* descriptor, uint32_t uboSize, uint32_t samples, int32_t shader);
        void FreeMemory(UBO* ubo, Descriptor* descriptor);

        SR_NODISCARD VirtualUBO GenerateUnique() const;

    private:
        ska::flat_hash_map<VirtualUBO, VirtualUBOInfo> m_virtualTable;
        Camera* m_camera = nullptr;
        bool m_singleCameraMode = false;

    };
}

#endif //SRENGINE_UBOMANAGER_H
