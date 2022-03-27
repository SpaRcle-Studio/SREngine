//
// Created by Monika on 24.03.2022.
//

#ifndef SRENGINE_RAWMESH_H
#define SRENGINE_RAWMESH_H

#include <ResourceManager/IResource.h>
#include <FbxLoader/Fbx.h>

#include <mutex>

namespace SR_UTILS_NS::Types {
    class RawMesh : public IResource {
        using CallbackFn = std::function<bool(const FbxLoader::Fbx*)>;
    private:
        RawMesh();
        ~RawMesh() override = default;

    public:
        static RawMesh *Load(const std::string &path);

    public:
        bool Access(const CallbackFn& fn) const;
        uint32_t GetModelsCount() const;
        std::string GetGeometryName(uint32_t id) const;

        const std::vector<FbxLoader::Vertex>& GetVertices(uint32_t id) const {
            return m_fbx.objects.geometries.at(id).vertices;
        }

        const std::vector<uint32_t>& GetIndices(uint32_t id) const {
            SRAssert(id != SR_UINT32_MAX);
            return m_fbx.objects.geometries.at(id).indices;
        }

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        FbxLoader::Fbx m_fbx;

        /// блокировка на случай выгрузки ресурса
        /// во время работы у указателем на его данные
        mutable std::recursive_mutex m_mutex;

    };
}

#endif //SRENGINE_RAWMESH_H
