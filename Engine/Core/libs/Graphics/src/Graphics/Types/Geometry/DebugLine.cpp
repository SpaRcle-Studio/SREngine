//
// Created by Monika on 19.09.2022.
//

#include <Graphics/Types/Geometry/DebugLine.h>

namespace SR_GTYPES_NS {
    DebugLine::DebugLine()
        : Super(MeshType::Line)
    { }

    DebugLine::DebugLine(SR_MATH_NS::FVector3 startPoint, SR_MATH_NS::FVector3 endPoint, SR_MATH_NS::FVector4 color)
        : Super(MeshType::Line)
        , m_startPoint(startPoint)
        , m_endPoint(endPoint)
        , m_color(color)
    { }

    void DebugLine::Draw() {
        if (IsDestroyed()) {
            return;
        }

        if ((!m_isCalculated && !Calculate()) || m_hasErrors)
            return;

        auto &&shader = m_material->GetShader();

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = m_uboManager.ReAllocateUBO(m_virtualUBO, shader->GetUBOBlockSize(), shader->GetSamplersCount());

            if (m_virtualUBO != SR_ID_INVALID) {
                m_uboManager.BindUBO(m_virtualUBO);
            }
            else {
                m_pipeline->ResetDescriptorSet();
                m_hasErrors = true;
                return;
            }

            shader->InitUBOBlock();
            shader->Flush();
        }

        switch (m_uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                shader->InitUBOBlock();
                shader->Flush();
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Success:
                m_pipeline->DrawIndices(2);
                break;
            case Memory::UBOManager::BindResult::Failed:
            default:
                break;
        }
    }

    Helper::IResource *DebugLine::Copy(Helper::IResource *destination) const {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        auto* pCopy = dynamic_cast<DebugLine *>(destination ? destination : new DebugLine());
        pCopy = dynamic_cast<DebugLine *>(Mesh::Copy(pCopy));

        return pCopy;
    }

    bool DebugLine::Calculate() {
        return Mesh::Calculate();
    }

    void DebugLine::FreeVideoMemory() {
        Mesh::FreeVideoMemory();
    }

    void DebugLine::UseMaterial() {
        if (auto&& pShader = GetShader()) {
            pShader->SetValue(SHADER_LINE_START_POINT, m_startPoint.Cast<float_t>());
            pShader->SetValue(SHADER_LINE_END_POINT, m_endPoint.Cast<float_t>());
            pShader->SetValue(SHADER_LINE_COLOR, m_color.Cast<float_t>());
        }

        Mesh::UseMaterial();
    }
}