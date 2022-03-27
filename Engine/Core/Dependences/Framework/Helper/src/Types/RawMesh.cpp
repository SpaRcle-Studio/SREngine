//
// Created by Monika on 24.03.2022.
//

#include <Types/RawMesh.h>
#include <FbxLoader/Loader.h>

namespace SR_UTILS_NS::Types {
    RawMesh::RawMesh()
        : IResource(typeid(RawMesh).name(), true /** auto destroy */)
    { }

    RawMesh *RawMesh::Load(const std::string &path) {
        if (auto&& pResource = ResourceManager::Instance().Find<RawMesh>(path)) {
            return pResource;
        }

        auto pMesh = new RawMesh();

        pMesh->SetId(path, false /** auto register */);

        if (!pMesh->Load()) {
            SR_ERROR("RawMesh::Load() : failed to load raw mesh! \n\tPath: " + path);
            delete pMesh;
            return nullptr;
        }

        /// отложенная ручная регистрация
        ResourceManager::Instance().RegisterResource(pMesh);

        return pMesh;
    }

    bool RawMesh::Unload() {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        bool hasErrors = !IResource::Unload();

        hasErrors |= !m_fbx.Valid();
        m_fbx.Clear();

        return !hasErrors;
    }

    bool RawMesh::Load() {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        bool hasErrors = !IResource::Load();

        m_fbx = FbxLoader::Loader::Load(
            ResourceManager::Instance().GetUtilsPath().Concat("FbxFormatConverter.exe"),
            ResourceManager::Instance().GetCachePath(),
            ResourceManager::Instance().GetModelsPath(),
            GetResourceId(),
            true
        );

        hasErrors |= !m_fbx.Valid();

        return !hasErrors;
    }

    bool RawMesh::Access(const RawMesh::CallbackFn &fn) const {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (m_fbx.Valid() && IsLoaded()) {
            return fn(&m_fbx);
        }

        SRAssert2(false, "Resource isn't loaded!");

        return false;
    }

    uint32_t RawMesh::GetModelsCount() const {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        /// TODO: replace to models
        return m_fbx.objects.geometries.size();
    }

    std::string RawMesh::GetGeometryName(uint32_t id) const {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        /// TODO: replace to models
        return m_fbx.objects.geometries[id].name;
    }
}