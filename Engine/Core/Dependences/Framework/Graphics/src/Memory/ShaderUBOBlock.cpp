//
// Created by Monika on 11.07.2022.
//

#include <Memory/ShaderUBOBlock.h>

namespace SR_GRAPH_NS::Memory {
    void ShaderUBOBlock::Append(uint64_t hashId, ShaderVarType type, bool hidden) {
        auto&& size = GetShaderVarSize(type);

        ++m_dataCount;

        auto&& data = new SubBlock[m_dataCount];

        data[m_dataCount - 1] = SubBlock {
            .hashId = hashId,
            .type = type,
            .size = size,
            .offset = m_size,
            .hidden = hidden,
        };

        if (m_data) {
            memcpy(data, m_data, (m_dataCount - 1) * sizeof(SubBlock));
            delete[] m_data;
        }

        m_data = data;

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
        m_dataCount = 0;

        if (m_data) {
            delete[] m_data;
            m_data = nullptr;
        }

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

        for (uint32_t i = 0; i < m_dataCount; ++i) {
            if (m_data[i].hashId == hashId) {
                memcpy(m_memory + m_data[i].offset, data, m_data[i].size);
            }
        }
    }
}