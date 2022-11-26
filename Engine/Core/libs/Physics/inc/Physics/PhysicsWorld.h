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
        using Space = SR_UTILS_NS::Measurement;
    public:
        explicit PhysicsWorld(LibraryPtr pLibrary, Space space);
        ~PhysicsWorld() override = default;

    public:
        virtual bool StepSimulation(float_t step) { return false; }
        virtual bool Initialize() { return false; }
        virtual bool ClearForces() { return false; }
        virtual bool Synchronize() { return false; }

        virtual bool AddRigidbody(RigidbodyPtr pRigidbody) { return false; }
        virtual bool RemoveRigidbody(RigidbodyPtr pRigidbody) { return false; }

        bool ReAddRigidbody(RigidbodyPtr pRigidbody) {
            return RemoveRigidbody(pRigidbody) && AddRigidbody(pRigidbody);
        }

        template<typename T> SR_NODISCARD T* GetLibrary() const {
            if (auto&& pLibrary = dynamic_cast<T*>(m_library)) {
                return pLibrary;
            }

            SRHalt("Failed to cast library!");

            return nullptr;
        }

    protected:
        LibraryPtr m_library = nullptr;
        Space m_space = Space::Unknown;

    };
}

#endif //SRENGINE_PHYSICSWORLD_H
