

# File PhysicsWorld.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**PhysicsWorld.h**](PhysicsWorld_8h.md)

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


