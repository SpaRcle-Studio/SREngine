//
// Created by Monika on 22.11.2022.
//

#include <Physics/PhysicsWorld.h>
#include <Physics/3D/Raycast3DImpl.h>

namespace SR_PHYSICS_NS {
    PhysicsWorld::PhysicsWorld(LibraryPtr pLibrary, Space space)
        : Super()
        , m_library(pLibrary)
        , m_space(space)
    {
        SRAssert(space != Space::Unknown);
    }

    PhysicsWorld::~PhysicsWorld() {
        if (m_raycast3dImpl) {
            delete m_raycast3dImpl;
            m_raycast3dImpl = nullptr;
        }
    }
}
