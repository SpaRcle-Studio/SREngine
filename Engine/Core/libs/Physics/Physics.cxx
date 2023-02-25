//
// Created by Monika on 27.07.2022.
//

#include <Utils/macros.h>

#include "src/Physics/2D/Rigidbody2D.cpp"
#include "src/Physics/3D/Rigidbody3D.cpp"
#include "src/Physics/3D/Raycast3D.cpp"

#include "src/Physics/Rigidbody.cpp"
#include "src/Physics/CollisionShape.cpp"
#include "src/Physics/PhysicsScene.cpp"
#include "src/Physics/PhysicsWorld.cpp"
#include "src/Physics/PhysicsLib.cpp"
#include "src/Physics/LibraryImpl.cpp"

#ifdef SR_PHYSICS_USE_BULLET3
    #include "src/Physics/Bullet3/Bullet3Rigidbody3D.cpp"
    #include "src/Physics/Bullet3/Bullet3LibraryImpl.cpp"
    #include "src/Physics/Bullet3/Bullet3PhysicsWorld.cpp"
    #include "src/Physics/Bullet3/Bullet3CollisionShape.cpp"
#endif

#ifdef SR_PHYSICS_USE_PHYSX
    #include "src/Physics/PhysX/PhysXLibraryImpl.cpp"
    #include "src/Physics/PhysX/PhysXPhysicsWorld.cpp"
    #include "src/Physics/PhysX/PhysXRigidbody3D.cpp"
    #include "src/Physics/PhysX/PhysXRaycast3DImpl.cpp"
    #include "src/Physics/PhysX/PhysXCollisionShape.cpp"
    #include "src/Physics/PhysX/PhysXSimulationCallback.cpp"
#endif

#ifdef SR_PHYSICS_USE_BOX2D
    #include "src/Physics/Box2D/Box2DLibraryImpl.cpp"
#endif