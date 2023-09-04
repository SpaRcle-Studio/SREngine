//
// Created by innerviewer on 3/4/2023.
//

#include <Physics/PhysicsMaterial.h>
#include <Physics/PhysicsMaterialImpl.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_PTYPES_NS {
    PhysicsMaterial::PhysicsMaterial()
        : Super(SR_COMPILE_TIME_CRC32_TYPE_NAME(PhysicsMaterial))
    { }

    PhysicsMaterial::~PhysicsMaterial() {
        for (auto&& [libraryType, physicsMaterial] : m_implementations) {
            delete physicsMaterial;
        }

        m_implementations.clear();
    }

    SR_UTILS_NS::IResource* PhysicsMaterial::CopyResource(Super *destination) const {
        SRHalt("Materials are not copyable!");
        return nullptr;
    }

    PhysicsMaterial* PhysicsMaterial::Load(const SR_UTILS_NS::Path& rawPath) {
        if (rawPath.Empty()) {
            SRHalt("PhysicsMaterial::Load() : path is empty!");
            return nullptr;
        }

        static auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        PhysicsMaterial* pMaterial = nullptr;

        resourceManager.Execute([&](){
            auto&& path = rawPath.SelfRemoveSubPath(resourceManager.GetResPathRef());

            if ((pMaterial = resourceManager.Find<PhysicsMaterial>(path))) {
                return;
            }

            pMaterial = new PhysicsMaterial();

            pMaterial->SetId(path, false);

            if (!pMaterial->Reload()) {
                delete pMaterial;
                pMaterial = nullptr;
                return;
            }

            resourceManager.RegisterResource(pMaterial);
        });

        return pMaterial;
    }

    bool PhysicsMaterial::Load() {
        SR_TRACY_ZONE;

        const auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(GetResourcePath());

        SR_LOG("PhysicsMaterial::Load() : the physics material is loading. \n\tPath: " + path.ToString());

        auto&& document = SR_XML_NS::Document::Load(path);
        if (!document.Valid()) {
            SR_ERROR("PhysicsMaterial::Load() : file is not found! \n\tPath: " + path.ToString());
            return false;
        }

        auto&& matXml = document.Root().GetNode("PhysicsMaterial");
        if (!matXml) {
            SR_ERROR("PhysicsMaterial::Load() : \"PhysicsMaterial\" node is not found! \n\tPath: " + path.ToString());
            return false;
        }

        SetDynamicFriction(matXml.TryGetNode("DynamicFriction").TryGetAttribute<float_t>(0.6f));
        SetStaticFriction(matXml.TryGetNode("StaticFriction").TryGetAttribute<float_t>(0.6f));
        SetBounciness(matXml.TryGetNode("Bounciness").TryGetAttribute<float_t>(0.6f));
        SetFrictionCombine(SR_UTILS_NS::EnumReflector::FromString<Combine>(matXml.TryGetNode("FrictionCombine").TryGetAttribute<std::string>("Average")));
        SetBounceCombine(SR_UTILS_NS::EnumReflector::FromString<Combine>(matXml.TryGetNode("BounceCombine").TryGetAttribute<std::string>("Average")));

        for (auto&& libraryType : SR_PHYSICS_NS::PhysicsLibrary::Instance().GetSupportedLibraries())
        {
            auto&& pLibrary = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetLibrary(libraryType);

            if (auto&& pMaterial = pLibrary->CreatePhysicsMaterial()) {
                m_implementations[libraryType] = pMaterial;
                pMaterial->Init(this);
            }
        }

        return IResource::Load();
    }

    bool PhysicsMaterial::Unload() {
        for (auto&& [libraryType, physicsMaterial] : m_implementations) {
            delete physicsMaterial;
        }

        m_implementations.clear();

        return IResource::Unload();
    }

    bool PhysicsMaterial::Save(const SR_UTILS_NS::Path& path, const PhysicsMaterialData& materialData) {
        auto&& document = SR_XML_NS::Document::New();

        auto&& matXml = document.Root().AppendNode("PhysicsMaterial");

        matXml.AppendNode("DynamicFriction").AppendAttribute(materialData.dynamicFriction);
        matXml.AppendNode("StaticFriction").AppendAttribute(materialData.staticFriction);
        matXml.AppendNode("Bounciness").AppendAttribute(materialData.bounciness);
        matXml.AppendNode("FrictionCombine").AppendAttribute(SR_UTILS_NS::EnumReflector::ToString(materialData.frictionCombine));
        matXml.AppendNode("BounceCombine").AppendAttribute(SR_UTILS_NS::EnumReflector::ToString(materialData.bounceCombine));

        if (!document.Save(path)) {
            SR_ERROR("PhysicsMaterial::Save() : Failed to save the document! \n\tPath: " + path.ToString());
            return false;
        }

        return true;
    }

    PhysicsMaterialImpl* PhysicsMaterial::GetMaterialImpl(LibraryType libraryType) const {
        if (auto&& pIt = m_implementations.find(libraryType); pIt != m_implementations.end()) {
            return pIt->second;
        }
        return nullptr;
    }
}
