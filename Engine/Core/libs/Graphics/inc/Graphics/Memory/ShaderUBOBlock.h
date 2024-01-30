//
// Created by Monika on 11.07.2022.
//

#ifndef SR_ENGINE_SHADERUBOBLOCK_H
#define SR_ENGINE_SHADERUBOBLOCK_H

#include <Utils/Types/Map.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GRAPH_NS::Types {
    class Shader;
}

namespace SR_GRAPH_NS::Memory {
    class ShaderUBOBlock : public SR_UTILS_NS::NonCopyable {
        friend class SR_GRAPH_NS::Types::Shader;

        struct SubBlock {
            uint64_t hashId;
            uint64_t size;
            uint64_t offset;
            bool hidden;
        };

    public:
        ~ShaderUBOBlock() override;

        void Append(uint64_t hashId, uint64_t size, bool hidden);
        void Append(uint64_t hashId, uint64_t size, uint64_t alignedSize, bool hidden);

        void Init();
        void DeInit();
        void SR_FASTCALL SetField(uint64_t hashId, const void* data) noexcept;

        SR_NODISCARD uint32_t GetBinding() const { return m_binding; }
        SR_NODISCARD bool Valid() const noexcept { return m_memory && m_binding != SR_ID_INVALID; }

    private:
        SR_NODISCARD uint64_t Align(uint64_t size) const;
        void FreeMemory(char*& pMemory);
        char* AllocMemory(uint64_t size);
        uint32_t OffsetBlock(uint32_t block);
        uint32_t TopAlign(uint32_t block);

    private:
        uint32_t m_alignedBlock = 0;
        uint32_t m_align = 16;

        uint32_t m_binding = SR_ID_INVALID;

        SubBlock* m_data = nullptr;
        uint32_t m_dataCount = 0;

        uint32_t m_size = 0;
        char* m_memory = nullptr;

        bool m_initialized = false;

    };
}

#endif //SR_ENGINE_SHADERUBOBLOCK_H
