//
// Created by Monika on 21.03.2021.
//

#ifndef GAMEENGINE_PHYSENGINE_H
#define GAMEENGINE_PHYSENGINE_H

//#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
//#include <btBulletDynamicsCommon.h>

//#include <btBulletDynamicsCommon.h>

namespace Framework::Physics {
    class PhysEngine {
    public:
        PhysEngine() = default;
    private:
        ~PhysEngine() = default;
    private:
        //btDefaultCollisionConfiguration*        m_collisionConf         = nullptr;
        //btCollisionDispatcher*                  m_dispatcher            = nullptr;
        //btBroadphaseInterface*                  m_overlappingPairCache  = nullptr;
        //btSequentialImpulseConstraintSolver*    m_solver                = nullptr;
        //btDiscreteDynamicsWorld*                m_dynamicWorld          = nullptr;

        bool m_isCreate = false;
        bool m_isInit   = false;
    public:
        bool SetGravity(float x, float y, float z);
    public:
        bool Create();
    };
}

#endif //GAMEENGINE_PHYSENGINE_H
