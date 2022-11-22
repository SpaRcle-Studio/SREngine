//
// Created by Monika on 22.11.2022.
//

#include <Physics/PhysicsLib.h>

#include <Physics/Bullet3/Bullet3LibraryImpl.h>

namespace SR_PHYSICS_NS {
    PhysicsLibrary::PhysicsLibrary()
        : Super()
    {
        m_libraries.resize(SR_UTILS_NS::EnumReflector::Count<LibraryType>());
    }

    PhysicsLibrary::~PhysicsLibrary() = default;

    LibraryImpl *PhysicsLibrary::GetLibrary(LibraryType type) {
        const auto index = static_cast<int32_t>(type);

        if (index >= m_libraries.size()) {
            SRHalt("Out of range!");
            return nullptr;
        }

        if (auto&& pLibrary = m_libraries[index]) {
            return pLibrary;
        }

        switch (type) {
            case LibraryType::Bullet3:
                return (m_libraries[index] = new Bullet3LibraryImpl());
            default:
                SRHalt("Unsupported library!");
                return nullptr;
        }
    }

    LibraryImpl *PhysicsLibrary::GetActiveLibrary() {
        return GetLibrary(LibraryType::Bullet3);
    }
}