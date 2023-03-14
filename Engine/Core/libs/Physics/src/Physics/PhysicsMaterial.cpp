//
// Created by innerviewer on 3/4/2023.
//

#include <Physics/PhysicsMaterial.h>
#include <Physics/PhysicsMaterialImpl.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_PTYPES_NS {
    PhysicsMaterial::PhysicsMaterial()
        : Super(SR_COMPILE_TIME_CRC32_TYPE_NAME(PhysicsMaterial), true /** auto remove */)
    { }

    PhysicsMaterial::~PhysicsMaterial() {
        SetReadOnly(false);

        for (auto&& [libraryType, physicsMaterial] : m_implementations) {
            delete physicsMaterial;
        }

        m_implementations.clear();
    }

    SR_UTILS_NS::IResource* PhysicsMaterial::CopyResource(Super *destination) const {
        SRHalt("Materials are not copyable!");
        return nullptr;
    }

    PhysicsMaterial* PhysicsMaterial::Load(SR_UTILS_NS::Path rawPath) {
        if (rawPath.Empty()) {
            SR_ERROR("PhysicsMaterial::Load : path is empty!");
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
        const auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(GetResourcePath());

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

        SetDynamicFriction(matXml.TryGetNode("DynamicFriction").TryGetAttribute("Value").ToFloat(0.6f));
        SetStaticFriction(matXml.TryGetNode("StaticFriction").TryGetAttribute("Value").ToFloat(0.6f));
        SetBounciness(matXml.TryGetNode("Bounciness").TryGetAttribute("Value").ToFloat(0.0f));
        SetFrictionCombine(SR_UTILS_NS::EnumReflector::FromString<Combine>(matXml.TryGetNode("FrictionCombine").TryGetAttribute("Value").ToString("Average")));
        SetBounceCombine(SR_UTILS_NS::EnumReflector::FromString<Combine>(matXml.TryGetNode("BounceCombine").TryGetAttribute("Value").ToString("Average")));

        SetReadOnly(matXml.TryGetAttribute("ReadOnly").ToBool(false));

        for (auto&& libraryType : SR_PHYSICS_NS::PhysicsLibrary::Instance().GetSupportedLibraries()) {
            auto&& pLibrary = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetLibrary(libraryType);
            m_implementations[libraryType] = pLibrary->CreatePhysicsMaterial();
        }

        return IResource::Load();
    }

    bool PhysicsMaterial::Unload() {
        SetReadOnly(false);

        for (auto&& [libraryType, physicsMaterial] : m_implementations) {
            delete physicsMaterial;
        }

        m_implementations.clear();

        return IResource::Unload();
    }
}