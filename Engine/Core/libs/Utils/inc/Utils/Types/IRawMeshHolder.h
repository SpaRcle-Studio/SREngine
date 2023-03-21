//
// Created by Monika on 20.03.2023.
//

#ifndef SRENGINE_UTILS_IRAWMESHHOLDER_H
#define SRENGINE_UTILS_IRAWMESHHOLDER_H

#include <Utils/stdInclude.h>

namespace SR_HTYPES_NS {
    class RawMesh;

    /// Этот класс предоставляет удобный интерфейс для работы с RwMesh
    class IRawMeshHolder {
    public:
        using RawMeshPtr = SR_HTYPES_NS::RawMesh*;
        using MeshIndex = int32_t;

        virtual ~IRawMeshHolder();

    public:
        SR_NODISCARD uint32_t GetMeshId() const noexcept { return m_meshId; }
        SR_NODISCARD RawMeshPtr GetRawMesh() const noexcept { return m_rawMesh; }
        SR_NODISCARD std::string GetMeshStringPath() const noexcept;
        SR_NODISCARD bool IsValidMeshId() const noexcept;
        SR_NODISCARD std::vector<SR_UTILS_NS::Vertex> GetVertices() const noexcept;

        virtual void SetRawMesh(RawMeshPtr pRawMesh);
        virtual void SetMeshId(MeshIndex meshIndex);

    private:
        RawMeshPtr m_rawMesh = nullptr;
        /// определяет порядок меша в файле, если их там несколько
        /// TODO: переделать в int16_t, но нужно написать миграторы.
        MeshIndex m_meshId = SR_ID_INVALID;

    };
}

#endif //SRENGINE_UTILS_IRAWMESHHOLDER_H
