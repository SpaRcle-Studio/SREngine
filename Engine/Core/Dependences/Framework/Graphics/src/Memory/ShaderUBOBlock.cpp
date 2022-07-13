//
// Created by Monika on 11.07.2022.
//

#include <Memory/ShaderUBOBlock.h>

namespace SR_GRAPH_NS::Memory {
    ShaderUBOBlock::ShaderUBOBlock() {
        m_data.reserve(10);
        m_data.max_load_factor(0.9f);
    }

    void ShaderUBOBlock::Append(uint64_t hashId, ShaderVarType type, bool hidden) {
        auto &&size = GetShaderVarSize(type);

        m_data.insert(std::make_pair(hashId, SubBlock{
                .type = type,
                .size = size,
                .offset = m_size,
                .hidden = hidden,
        }));

        m_size += size;
    }

    void ShaderUBOBlock::Init() {
        if (m_memory) {
            delete m_memory;
            m_memory = nullptr;
        }

        m_memory = new char[m_size];
    }

    void ShaderUBOBlock::DeInit() {
        m_data.clear();
        m_size = 0;
        m_binding = SR_ID_INVALID;

        if (m_memory) {
            delete m_memory;
            m_memory = nullptr;
        }
    }

    void ShaderUBOBlock::SetField(uint64_t hashId, const void *data) noexcept {
        if (!m_memory) {
            return;
        }

        if (auto &&pIt = m_data.find(hashId); pIt != m_data.end()) {
            memcpy(m_memory + pIt->second.offset, data, pIt->second.size);
        }
    }
}