

# File PhysicsScene.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysicsScene.h**](PhysicsScene_8h.md)

[Go to the documentation of this file](PhysicsScene_8h.md)


```C++
//
// Created by Monika on 28.07.2022.
//

#ifndef SR_ENGINE_PHYSICSSCENE_H
#define SR_ENGINE_PHYSICSSCENE_H

#include <Physics/macros.h>

#include <Physics/PhysicsLib.h>
#include <Utils/Types/SafePointer.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_PHYSICS_NS::Types {
    class Rigidbody;
}

namespace SR_PHYSICS_NS {
    class PhysicsWorld;

    class PhysicsScene : public SR_HTYPES_NS::SafePtr<PhysicsScene> {
        friend class SR_HTYPES_NS::SafePtr<PhysicsScene>;
    public:
        using Super = SR_HTYPES_NS::SafePtr<PhysicsScene>;
        using Ptr = Super;
        using RigidbodyPtr = SR_HTYPES_NS::SharedPtr<SR_PTYPES_NS::Rigidbody>;
        using PhysicsWorldPtr = SR_PHYSICS_NS::PhysicsWorld*;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using ScenePtr = SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;
        using Space = SR_UTILS_NS::Measurement;
    public:
        explicit PhysicsScene(const ScenePtr& scene);
        virtual ~PhysicsScene();

    public:
        virtual void Update(float_t dt);
        virtual void FixedUpdate();
        virtual bool Init();

        virtual void Remove(RigidbodyPtr pRigidbody);
        virtual void Register(RigidbodyPtr pRigidbody);

        virtual void ClearForces();

        SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld* Get2DWorld() const noexcept { return m_2DWorld; }
        SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld* Get3DWorld() const noexcept { return m_3DWorld; }
        SR_NODISCARD bool IsDebugEnabled() const noexcept;

        void SetIsGameMode(bool enabled) noexcept { m_isGameMode = enabled; }

    private:
        virtual bool Flush();
        virtual bool CreateDynamicWorld();

    private:
        std::list<RigidbodyPtr> m_rigidbodyToRemove;
        std::list<RigidbodyPtr> m_rigidbodyToRegister;

        ScenePtr m_scene;

        LibraryPtr m_library2D = nullptr;
        LibraryPtr m_library3D = nullptr;

        PhysicsWorldPtr m_2DWorld = nullptr;
        PhysicsWorldPtr m_3DWorld = nullptr;

        bool m_needClearForces = false;
        bool m_debugEnabled = true;
        bool m_isGameMode = false;

    };
}

#endif //SR_ENGINE_PHYSICSSCENE_H
```


