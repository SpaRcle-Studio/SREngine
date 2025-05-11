

# Class SR\_PHYSICS\_NS::PhysXPhysicsWorld



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**PhysXPhysicsWorld**](classSR__PHYSICS__NS_1_1PhysXPhysicsWorld.md)








Inherits the following classes: [SR\_PHYSICS\_NS::PhysicsWorld](classSR__PHYSICS__NS_1_1PhysicsWorld.md)
















## Public Types inherited from SR_PHYSICS_NS::PhysicsWorld

See [SR\_PHYSICS\_NS::PhysicsWorld](classSR__PHYSICS__NS_1_1PhysicsWorld.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#typedef-libraryptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_PTYPES\_NS::Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) &gt; | [**RigidbodyPtr**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#typedef-rigidbodyptr)  <br> |
| typedef SR\_UTILS\_NS::Measurement | [**Space**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#typedef-space)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#typedef-super)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**AddRigidbody**](#function-addrigidbody) (RigidbodyPtr pRigidbody) override<br> |
| virtual bool | [**ClearForces**](#function-clearforces) () override<br> |
| virtual void | [**Flush**](#function-flush) () override<br> |
| virtual void | [**ForEachRigidbody3D**](#function-foreachrigidbody3d) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**SR\_PTYPES\_NS::Rigidbody3D**](classSR__PTYPES__NS_1_1Rigidbody3D.md) \*)&gt; & fun) override<br> |
| virtual bool | [**Initialize**](#function-initialize) () override<br> |
|   | [**PhysXPhysicsWorld**](#function-physxphysicsworld) (LibraryPtr pLibrary, Space space) <br> |
| virtual bool | [**RemoveRigidbody**](#function-removerigidbody) (RigidbodyPtr pRigidbody) override<br> |
| virtual bool | [**StepSimulation**](#function-stepsimulation) (float\_t step) override<br> |
| virtual bool | [**Synchronize**](#function-synchronize) () override<br> |
|   | [**~PhysXPhysicsWorld**](#function-physxphysicsworld) () override<br> |


## Public Functions inherited from SR_PHYSICS_NS::PhysicsWorld

See [SR\_PHYSICS\_NS::PhysicsWorld](classSR__PHYSICS__NS_1_1PhysicsWorld.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**AddRigidbody**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-addrigidbody) (RigidbodyPtr pRigidbody) <br> |
| virtual bool | [**ClearForces**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-clearforces) () <br> |
| virtual void | [**Flush**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-flush) () <br> |
| virtual void | [**ForEachRigidbody3D**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-foreachrigidbody3d) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**SR\_PTYPES\_NS::Rigidbody3D**](classSR__PTYPES__NS_1_1Rigidbody3D.md) \*)&gt; & fun) <br> |
|  SR\_NODISCARD T \* | [**GetLibrary**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-getlibrary) () const<br> |
|  SR\_NODISCARD [**Raycast3DImpl**](classSR__PHYSICS__NS_1_1Raycast3DImpl.md) \* | [**GetRaycast3DImpl**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-getraycast3dimpl) () noexcept const<br> |
| virtual bool | [**Initialize**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-initialize) () <br> |
|   | [**PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-physicsworld) (LibraryPtr pLibrary, Space space) <br> |
|  bool | [**ReAddRigidbody**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-readdrigidbody) (RigidbodyPtr pRigidbody) <br> |
| virtual bool | [**RemoveRigidbody**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-removerigidbody) (RigidbodyPtr pRigidbody) <br> |
| virtual bool | [**StepSimulation**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-stepsimulation) (float\_t step) <br> |
| virtual bool | [**Synchronize**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-synchronize) () <br> |
|   | [**~PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-physicsworld) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






















## Protected Attributes inherited from SR_PHYSICS_NS::PhysicsWorld

See [SR\_PHYSICS\_NS::PhysicsWorld](classSR__PHYSICS__NS_1_1PhysicsWorld.md)

| Type | Name |
| ---: | :--- |
|  LibraryPtr | [**m\_library**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#variable-m_library)   = `nullptr`<br> |
|  [**Raycast3DImpl**](classSR__PHYSICS__NS_1_1Raycast3DImpl.md) \* | [**m\_raycast3dImpl**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#variable-m_raycast3dimpl)   = `nullptr`<br> |
|  Space | [**m\_space**](classSR__PHYSICS__NS_1_1PhysicsWorld.md#variable-m_space)   = `Space::Unknown`<br> |


















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function AddRigidbody 

```C++
virtual bool SR_PHYSICS_NS::PhysXPhysicsWorld::AddRigidbody (
    RigidbodyPtr pRigidbody
) override
```



Implements [*SR\_PHYSICS\_NS::PhysicsWorld::AddRigidbody*](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-addrigidbody)


<hr>



### function ClearForces 

```C++
virtual bool SR_PHYSICS_NS::PhysXPhysicsWorld::ClearForces () override
```



Implements [*SR\_PHYSICS\_NS::PhysicsWorld::ClearForces*](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-clearforces)


<hr>



### function Flush 

```C++
virtual void SR_PHYSICS_NS::PhysXPhysicsWorld::Flush () override
```



Implements [*SR\_PHYSICS\_NS::PhysicsWorld::Flush*](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-flush)


<hr>



### function ForEachRigidbody3D 

```C++
virtual void SR_PHYSICS_NS::PhysXPhysicsWorld::ForEachRigidbody3D (
    const SR_HTYPES_NS::Function < void( SR_PTYPES_NS::Rigidbody3D *)> & fun
) override
```



Implements [*SR\_PHYSICS\_NS::PhysicsWorld::ForEachRigidbody3D*](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-foreachrigidbody3d)


<hr>



### function Initialize 

```C++
virtual bool SR_PHYSICS_NS::PhysXPhysicsWorld::Initialize () override
```



Implements [*SR\_PHYSICS\_NS::PhysicsWorld::Initialize*](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-initialize)


<hr>



### function PhysXPhysicsWorld 

```C++
explicit SR_PHYSICS_NS::PhysXPhysicsWorld::PhysXPhysicsWorld (
    LibraryPtr pLibrary,
    Space space
) 
```




<hr>



### function RemoveRigidbody 

```C++
virtual bool SR_PHYSICS_NS::PhysXPhysicsWorld::RemoveRigidbody (
    RigidbodyPtr pRigidbody
) override
```



Implements [*SR\_PHYSICS\_NS::PhysicsWorld::RemoveRigidbody*](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-removerigidbody)


<hr>



### function StepSimulation 

```C++
virtual bool SR_PHYSICS_NS::PhysXPhysicsWorld::StepSimulation (
    float_t step
) override
```



Implements [*SR\_PHYSICS\_NS::PhysicsWorld::StepSimulation*](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-stepsimulation)


<hr>



### function Synchronize 

```C++
virtual bool SR_PHYSICS_NS::PhysXPhysicsWorld::Synchronize () override
```



Implements [*SR\_PHYSICS\_NS::PhysicsWorld::Synchronize*](classSR__PHYSICS__NS_1_1PhysicsWorld.md#function-synchronize)


<hr>



### function ~PhysXPhysicsWorld 

```C++
SR_PHYSICS_NS::PhysXPhysicsWorld::~PhysXPhysicsWorld () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/PhysX/PhysXPhysicsWorld.h`

