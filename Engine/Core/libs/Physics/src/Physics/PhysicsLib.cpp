//
// Created by Monika on 22.11.2022.
//

#include <Physics/PhysicsLib.h>
#include <Utils/ResourceManager/ResourceManager.h>

#ifdef SR_PHYSICS_USE_BULLET3
    #include <Physics/Bullet3/Bullet3LibraryImpl.h>
#endif

#ifdef SR_PHYSICS_USE_PHYSX
    #include <Physics/PhysX/PhysXLibraryImpl.h>
#endif

#ifdef SR_PHYSICS_USE_BOX2D
    #include <Physics/Box2D/Box2DLibraryImpl.h>
#endif

namespace SR_PHYSICS_NS {
    PhysicsLibrary::PhysicsLibrary()
        : Super()
    {
        m_libraries.resize(SR_UTILS_NS::EnumReflector::Count<LibraryType>());
    }

    PhysicsLibrary::~PhysicsLibrary() {
        for (auto&& pLibrary : m_libraries) {
            SR_SAFE_DELETE_PTR(pLibrary);
        }
        m_libraries.clear();
    }

    void PhysicsLibrary::InitSingleton() {
        auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Configs/Physics.xml");
        auto&& document = SR_XML_NS::Document::Load(path);
        if (!document.Valid()) {
            SR_ERROR("PhysicsLibrary::InitSingleton() : failed to load xml document! \n\tPath: " + path.ToString());
            return Super::InitSingleton();
        }

        auto&& defaultLibraries = document.Root().GetNode("Physics").TryGetNode("DefaultLibraries");

        for (auto&& node : defaultLibraries.TryGetNodes()) {
            auto&& space = SR_UTILS_NS::EnumReflector::FromString<Space>(node.Name());
            auto&& library = SR_UTILS_NS::EnumReflector::FromString<LibraryType>(node.GetAttribute("Library").ToString());
            m_activeLibs[space] = library;
        }

        auto&& supportedLibraries = document.Root().GetNode("Physics").TryGetNode("SupportedLibraries");

        for (auto&& node : supportedLibraries.TryGetNodes()) {
            auto&& library = SR_UTILS_NS::EnumReflector::FromString<LibraryType>(node.Name());
            m_supportedLibs.insert(library);
        }
    }

    LibraryImpl *PhysicsLibrary::GetLibrary(LibraryType type) {
        const auto index = static_cast<int32_t>(type);

        if (index >= m_libraries.size()) {
            SRHalt("Out of range!");
            return nullptr;
        }

        if (auto&& pLibrary = m_libraries[index]) {
            return pLibrary;
        }

        SR_INFO("PhysicsLibrary::GetLibrary() : initializing \"" + SR_UTILS_NS::EnumReflector::ToString(type) +
                "\" physics library...");

        switch (type) {
        #ifdef SR_PHYSICS_USE_PHYSX
            case LibraryType::PhysX:
                m_libraries[index] = new PhysXLibraryImpl();
                break;
        #endif
        #ifdef SR_PHYSICS_USE_BULLET3
            case LibraryType::Bullet3:
                m_libraries[index] = new Bullet3LibraryImpl();
                break;
        #endif
        #ifdef SR_PHYSICS_USE_BOX2D
            case LibraryType::Box2D:
                m_libraries[index] = new Box2DLibraryImpl();
                break;
        #endif
            default:
                SRHalt("Unsupported library!");
                return nullptr;
        }

        if (!m_libraries[index]->Initialize()) {
            SR_ERROR("PhysicsLibrary::GetLibrary() : failed to initialize physics library!\n\tType: "
                 + SR_UTILS_NS::EnumReflector::ToString(type)
            );
            delete m_libraries[index];
            m_libraries[index] = nullptr;
            return nullptr;
        }

        return m_libraries[index];
    }

    LibraryImpl* PhysicsLibrary::GetActiveLibrary(Space space) {
        if (auto&& pIt = m_activeLibs.find(space); pIt != m_activeLibs.end()) {
            return GetLibrary(pIt->second);
        }

        SR_WARN("PhysicsLibrary::GetActiveLibrary() : not found active library for \"" +
            SR_UTILS_NS::EnumReflector::ToString(space) + "\", use default...");

        switch (space) {
            case Space::Space2D:
            case Space::Space3D:
                return GetLibrary(LibraryType::Bullet3);
            default:
                break;
        }

        SRHalt("PhysicsLibrary::GetActiveLibrary() : unsupported measurement!");

        return nullptr;
    }

    PhysicsLibrary::LibraryTypes PhysicsLibrary::GetSupportedLibraries() const {
        LibraryTypes types;

    #ifdef SR_PHYSICS_USE_PHYSX
        if (m_supportedLibs.count(LibraryType::PhysX)){
            types.emplace_back(LibraryType::PhysX);
        }
    #endif
    #ifdef SR_PHYSICS_USE_BULLET3
        if (m_supportedLibs.count(LibraryType::Bullet3)){
            types.emplace_back(LibraryType::Bullet3);
        }
    #endif
    #ifdef SR_PHYSICS_USE_BOX2D
        if (m_supportedLibs.count(LibraryType::Box2D)){
            types.emplace_back(LibraryType::Box2D);
        }
    #endif

        return types;
    }
}