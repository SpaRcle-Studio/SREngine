//
// Created by Monika on 11.07.2022.
//

#ifndef SRENGINE_SHADERUBOBLOCK_H
#define SRENGINE_SHADERUBOBLOCK_H

#include <Utils/Types/Map.h>
#include <Environment/Basic/IShaderProgram.h>

namespace SR_GRAPH_NS::Types {
    class Shader;
}

namespace SR_GRAPH_NS::Memory {
    class ShaderUBOBlock {
        friend class SR_GRAPH_NS::Types::Shader;

        struct SubBlock {
            ShaderVarType type;
            uint32_t size;
            uint32_t offset;
            bool hidden;
        };

    public:
        ShaderUBOBlock();

    public:
        void Append(uint64_t hashId, ShaderVarType type, bool hidden);
        void Init();
        void DeInit();
        void SR_FASTCALL SetField(uint64_t hashId, const void* data) noexcept;

        SR_NODISCARD uint32_t GetBinding() const { return m_binding; }
        SR_NODISCARD bool Valid() const { return m_memory && m_binding != SR_ID_INVALID; }

    private:
        uint32_t m_binding = SR_ID_INVALID;
        ska::flat_hash_map<uint64_t, SubBlock> m_data;
        uint32_t m_size = 0;
        char* m_memory = nullptr;

    };
}

#endif //SRENGINE_SHADERUBOBLOCK_H