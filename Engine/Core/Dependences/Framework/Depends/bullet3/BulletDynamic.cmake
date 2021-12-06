
set(BULLETDYNAMIC_SRC
        BulletDynamics/Character/btKinematicCharacterController.cpp

        BulletDynamics/ConstraintSolver/btBatchedConstraints.cpp
        BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp
        BulletDynamics/ConstraintSolver/btContactConstraint.cpp
        BulletDynamics/ConstraintSolver/btFixedConstraint.cpp
        BulletDynamics/ConstraintSolver/btGearConstraint.cpp
        BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp
        BulletDynamics/ConstraintSolver/btGeneric6DofSpring2Constraint.cpp
        BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.cpp
        BulletDynamics/ConstraintSolver/btHinge2Constraint.cpp
        BulletDynamics/ConstraintSolver/btHingeConstraint.cpp
        BulletDynamics/ConstraintSolver/btNNCGConstraintSolver.cpp
        BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp
        BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp
        BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolverMt.cpp
        BulletDynamics/ConstraintSolver/btSliderConstraint.cpp
        BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp
        BulletDynamics/ConstraintSolver/btTypedConstraint.cpp
        BulletDynamics/ConstraintSolver/btUniversalConstraint.cpp

        BulletDynamics/Dynamics/btSimulationIslandManagerMt.cpp
        BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp
        BulletDynamics/Dynamics/btDiscreteDynamicsWorldMt.cpp
        BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp
        BulletDynamics/Dynamics/btRigidBody.cpp

        BulletDynamics/MLCPSolvers/btMLCPSolver.cpp
        BulletDynamics/MLCPSolvers/btLemkeAlgorithm.cpp
        BulletDynamics/MLCPSolvers/btDantzigLCP.cpp

        BulletDynamics/Featherstone/btMultiBody.cpp
        BulletDynamics/Featherstone/btMultiBodyConstraint.cpp
        BulletDynamics/Featherstone/btMultiBodyConstraintSolver.cpp
        BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.cpp
        BulletDynamics/Featherstone/btMultiBodyFixedConstraint.cpp
        BulletDynamics/Featherstone/btMultiBodyGearConstraint.cpp
        BulletDynamics/Featherstone/btMultiBodyJointLimitConstraint.cpp
        BulletDynamics/Featherstone/btMultiBodyJointMotor.cpp
        BulletDynamics/Featherstone/btMultiBodyMLCPConstraintSolver.cpp
        BulletDynamics/Featherstone/btMultiBodyPoint2Point.cpp
        BulletDynamics/Featherstone/btMultiBodySliderConstraint.cpp
        BulletDynamics/Featherstone/btMultiBodySphericalJointMotor.cpp

        BulletDynamics/Vehicle/btRaycastVehicle.cpp
        BulletDynamics/Vehicle/btWheelInfo.cpp
        )

set(BULLETDYNAMIC_INC_PUBLIC
        ${BULLET3_ROOT_DIR}
        )

set(BULLETDYNAMIC_INC_PRIVATE

        )

set(BULLETDYNAMIC_INC_INSTANCE

        )
