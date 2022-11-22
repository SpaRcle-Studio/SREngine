//
// Created by Monika on 22.11.2022.
//

#ifndef SRENGINE_PHYSICSWORLD_H
#define SRENGINE_PHYSICSWORLD_H

#include <Physics/Utils/Utils.h>

namespace SR_PHYSICS_NS {
    class LibraryImpl;

    class PhysicsWorld : public SR_UTILS_NS::NonCopyable {
    public:
        using Super = SR_UTILS_NS::NonCopyable;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using RigidbodyPtr = SR_PTYPES_NS::Rigidbody*;
    public:
        explicit PhysicsWorld(LibraryPtr pLibrary);
        ~PhysicsWorld() override = default;

    public:
        virtual bool StepSimulation(float_t step) { return false; }
        virtual bool CreateDynamicWorld() { return false; }
        virtual bool ClearForces() { return false; }
        virtual bool Update() { return false; }

        virtual bool AddRigidbody(RigidbodyPtr pRigidbody) { return false; }
        virtual bool RemoveRigidbody(RigidbodyPtr pRigidbody) { return false; }

    protected:
        LibraryPtr m_library = nullptr;

    };
}

#endif //SRENGINE_PHYSICSWORLD_H
