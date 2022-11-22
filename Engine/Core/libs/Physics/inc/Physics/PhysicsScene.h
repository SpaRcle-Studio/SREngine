//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_PHYSICSSCENE_H
#define SRENGINE_PHYSICSSCENE_H

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
        using Super = SR_HTYPES_NS::SafePtr<PhysicsScene>;
        using Ptr = Super;
        using RigidbodyPtr = SR_PTYPES_NS::Rigidbody*;
        using PhysicsWorldPtr = SR_PHYSICS_NS::PhysicsWorld*;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
    public:
        explicit PhysicsScene(const ScenePtr& scene);
        ~PhysicsScene();

    public:
        void FixedUpdate();
        bool Init();

        void Remove(RigidbodyPtr pRigidbody);
        void Register(RigidbodyPtr pRigidbody);

        void ClearForces();

    private:
        bool CreateDynamicWorld();

    private:
        ScenePtr m_scene;

        LibraryPtr m_library = nullptr;

        PhysicsWorldPtr m_2DWorld = nullptr;
        PhysicsWorldPtr m_3DWorld = nullptr;

        bool m_needClearForces = false;

    };
}

#endif //SRENGINE_PHYSICSSCENE_H
