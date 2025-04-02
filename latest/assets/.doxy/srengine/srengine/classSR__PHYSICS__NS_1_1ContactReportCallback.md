

# Class SR\_PHYSICS\_NS::ContactReportCallback



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**ContactReportCallback**](classSR__PHYSICS__NS_1_1ContactReportCallback.md)








Inherits the following classes: physx::PxSimulationEventCallback


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**onAdvance**](#function-onadvance) (const physx::PxRigidBody \*const \* bodyBuffer, const physx::PxTransform \* poseBuffer, const physx::PxU32 count) override<br> |
|  void | [**onConstraintBreak**](#function-onconstraintbreak) (physx::PxConstraintInfo \* constraints, physx::PxU32 count) override<br> |
|  void | [**onContact**](#function-oncontact) (const physx::PxContactPairHeader & pairHeader, const physx::PxContactPair \* pairs, physx::PxU32 nbPairs) override<br> |
|  void | [**onSleep**](#function-onsleep) (physx::PxActor \*\* actors, physx::PxU32 count) override<br> |
|  void | [**onTrigger**](#function-ontrigger) (physx::PxTriggerPair \* pairs, physx::PxU32 count) override<br> |
|  void | [**onWake**](#function-onwake) (physx::PxActor \*\* actors, physx::PxU32 count) override<br> |




























## Public Functions Documentation




### function onAdvance 

```C++
inline void SR_PHYSICS_NS::ContactReportCallback::onAdvance (
    const physx::PxRigidBody *const * bodyBuffer,
    const physx::PxTransform * poseBuffer,
    const physx::PxU32 count
) override
```




<hr>



### function onConstraintBreak 

```C++
inline void SR_PHYSICS_NS::ContactReportCallback::onConstraintBreak (
    physx::PxConstraintInfo * constraints,
    physx::PxU32 count
) override
```




<hr>



### function onContact 

```C++
void SR_PHYSICS_NS::ContactReportCallback::onContact (
    const physx::PxContactPairHeader & pairHeader,
    const physx::PxContactPair * pairs,
    physx::PxU32 nbPairs
) override
```




<hr>



### function onSleep 

```C++
inline void SR_PHYSICS_NS::ContactReportCallback::onSleep (
    physx::PxActor ** actors,
    physx::PxU32 count
) override
```




<hr>



### function onTrigger 

```C++
void SR_PHYSICS_NS::ContactReportCallback::onTrigger (
    physx::PxTriggerPair * pairs,
    physx::PxU32 count
) override
```




<hr>



### function onWake 

```C++
inline void SR_PHYSICS_NS::ContactReportCallback::onWake (
    physx::PxActor ** actors,
    physx::PxU32 count
) override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/PhysX/PhysXSimulationCallback.h`

