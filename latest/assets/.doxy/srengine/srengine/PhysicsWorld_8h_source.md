

# File PhysicsWorld.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysicsWorld.h**](PhysicsWorld_8h.md)

[Go to the documentation of this file](PhysicsWorld_8h.md)


```C++
//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_PHYSICSWORLD_H
#define SR_ENGINE_PHYSICSWORLD_H

#include <Physics/macros.h>

#include <Physics/Utils/Utils.h>

namespace SR_PHYSICS_NS {
    class LibraryImpl;
    class Raycast3DImpl;

    class PhysicsWorld : public SR_UTILS_NS::NonCopyable {
    public:
        using Super = SR_UTILS_NS::NonCopyable;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using RigidbodyPtr = SR_HTYPES_NS::SharedPtr<SR_PTYPES_NS::Rigidbody>;
        using Space = SR_UTILS_NS::Measurement;
    public:
        explicit PhysicsWorld(LibraryPtr pLibrary, Space space);
        ~PhysicsWorld() override;

    public:
        virtual bool StepSimulation(float_t step) { return false; }
        virtual bool Initialize() { return false; }
        virtual bool ClearForces() { return false; }
        virtual bool Synchronize() { return false; }

        virtual void Flush() { }

        virtual bool AddRigidbody(RigidbodyPtr pRigidbody) { return false; }
        virtual bool RemoveRigidbody(RigidbodyPtr pRigidbody) { return false; }

        virtual void ForEachRigidbody3D(const SR_HTYPES_NS::Function<void(SR_PTYPES_NS::Rigidbody3D *)> &fun) { }

        bool ReAddRigidbody(RigidbodyPtr pRigidbody) {
            return RemoveRigidbody(pRigidbody) && AddRigidbody(pRigidbody);
        }

        SR_NODISCARD Raycast3DImpl* GetRaycast3DImpl() const noexcept { return m_raycast3dImpl; }

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
        Raycast3DImpl* m_raycast3dImpl = nullptr;

    };
}

#endif //SR_ENGINE_PHYSICSWORLD_H
```


