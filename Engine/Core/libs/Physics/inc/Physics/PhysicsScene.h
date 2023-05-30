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
    public:
        using Super = SR_HTYPES_NS::SafePtr<PhysicsScene>;
        using Ptr = Super;
        using RigidbodyPtr = SR_PTYPES_NS::Rigidbody*;
        using PhysicsWorldPtr = SR_PHYSICS_NS::PhysicsWorld*;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
        using Space = SR_UTILS_NS::Measurement;
    public:
        explicit PhysicsScene(const ScenePtr& scene);
        virtual ~PhysicsScene();

    public:
        virtual void FixedUpdate();
        virtual bool Init();

        virtual void Remove(RigidbodyPtr pRigidbody);
        virtual void Register(RigidbodyPtr pRigidbody);

        virtual void ClearForces();

        SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld* Get2DWorld() const noexcept { return m_2DWorld; }
        SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld* Get3DWorld() const noexcept { return m_3DWorld; }
        SR_NODISCARD bool IsDebugEnabled() const noexcept { return m_debugEnabled; };

    private:
        virtual bool Flush();
        virtual bool CreateDynamicWorld();

    private:
        std::list<SR_PTYPES_NS::Rigidbody*> m_rigidbodyToRemove;
        std::list<SR_PTYPES_NS::Rigidbody*> m_rigidbodyToRegister;

        ScenePtr m_scene;

        LibraryPtr m_library2D = nullptr;
        LibraryPtr m_library3D = nullptr;

        PhysicsWorldPtr m_2DWorld = nullptr;
        PhysicsWorldPtr m_3DWorld = nullptr;

        bool m_needClearForces = false;
        bool m_debugEnabled = true;

    };
}

#endif //SRENGINE_PHYSICSSCENE_H
