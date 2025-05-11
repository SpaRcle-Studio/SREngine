

# Class SR\_PHYSICS\_NS::PhysicsWorld



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_PHYSICS\_NS::Bullet3PhysicsWorld](classSR__PHYSICS__NS_1_1Bullet3PhysicsWorld.md),  [SR\_PHYSICS\_NS::PhysXPhysicsWorld](classSR__PHYSICS__NS_1_1PhysXPhysicsWorld.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](#typedef-libraryptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_PTYPES\_NS::Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) &gt; | [**RigidbodyPtr**](#typedef-rigidbodyptr)  <br> |
| typedef SR\_UTILS\_NS::Measurement | [**Space**](#typedef-space)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](#typedef-super)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**AddRigidbody**](#function-addrigidbody) (RigidbodyPtr pRigidbody) <br> |
| virtual bool | [**ClearForces**](#function-clearforces) () <br> |
| virtual void | [**Flush**](#function-flush) () <br> |
| virtual void | [**ForEachRigidbody3D**](#function-foreachrigidbody3d) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**SR\_PTYPES\_NS::Rigidbody3D**](classSR__PTYPES__NS_1_1Rigidbody3D.md) \*)&gt; & fun) <br> |
|  SR\_NODISCARD T \* | [**GetLibrary**](#function-getlibrary) () const<br> |
|  SR\_NODISCARD [**Raycast3DImpl**](classSR__PHYSICS__NS_1_1Raycast3DImpl.md) \* | [**GetRaycast3DImpl**](#function-getraycast3dimpl) () noexcept const<br> |
| virtual bool | [**Initialize**](#function-initialize) () <br> |
|   | [**PhysicsWorld**](#function-physicsworld) (LibraryPtr pLibrary, Space space) <br> |
|  bool | [**ReAddRigidbody**](#function-readdrigidbody) (RigidbodyPtr pRigidbody) <br> |
| virtual bool | [**RemoveRigidbody**](#function-removerigidbody) (RigidbodyPtr pRigidbody) <br> |
| virtual bool | [**StepSimulation**](#function-stepsimulation) (float\_t step) <br> |
| virtual bool | [**Synchronize**](#function-synchronize) () <br> |
|   | [**~PhysicsWorld**](#function-physicsworld) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  LibraryPtr | [**m\_library**](#variable-m_library)   = `nullptr`<br> |
|  [**Raycast3DImpl**](classSR__PHYSICS__NS_1_1Raycast3DImpl.md) \* | [**m\_raycast3dImpl**](#variable-m_raycast3dimpl)   = `nullptr`<br> |
|  Space | [**m\_space**](#variable-m_space)   = `Space::Unknown`<br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef LibraryPtr 

```C++
using SR_PHYSICS_NS::PhysicsWorld::LibraryPtr =  SR_PHYSICS_NS::LibraryImpl*;
```




<hr>



### typedef RigidbodyPtr 

```C++
using SR_PHYSICS_NS::PhysicsWorld::RigidbodyPtr =  SR_HTYPES_NS::SharedPtr<SR_PTYPES_NS::Rigidbody>;
```




<hr>



### typedef Space 

```C++
using SR_PHYSICS_NS::PhysicsWorld::Space =  SR_UTILS_NS::Measurement;
```




<hr>



### typedef Super 

```C++
using SR_PHYSICS_NS::PhysicsWorld::Super =  SR_UTILS_NS::NonCopyable;
```




<hr>
## Public Functions Documentation




### function AddRigidbody 

```C++
inline virtual bool SR_PHYSICS_NS::PhysicsWorld::AddRigidbody (
    RigidbodyPtr pRigidbody
) 
```




<hr>



### function ClearForces 

```C++
inline virtual bool SR_PHYSICS_NS::PhysicsWorld::ClearForces () 
```




<hr>



### function Flush 

```C++
inline virtual void SR_PHYSICS_NS::PhysicsWorld::Flush () 
```




<hr>



### function ForEachRigidbody3D 

```C++
inline virtual void SR_PHYSICS_NS::PhysicsWorld::ForEachRigidbody3D (
    const SR_HTYPES_NS::Function < void( SR_PTYPES_NS::Rigidbody3D *)> & fun
) 
```




<hr>



### function GetLibrary 

```C++
template<typename T>
inline SR_NODISCARD T * SR_PHYSICS_NS::PhysicsWorld::GetLibrary () const
```




<hr>



### function GetRaycast3DImpl 

```C++
inline SR_NODISCARD Raycast3DImpl * SR_PHYSICS_NS::PhysicsWorld::GetRaycast3DImpl () noexcept const
```




<hr>



### function Initialize 

```C++
inline virtual bool SR_PHYSICS_NS::PhysicsWorld::Initialize () 
```




<hr>



### function PhysicsWorld 

```C++
explicit SR_PHYSICS_NS::PhysicsWorld::PhysicsWorld (
    LibraryPtr pLibrary,
    Space space
) 
```




<hr>



### function ReAddRigidbody 

```C++
inline bool SR_PHYSICS_NS::PhysicsWorld::ReAddRigidbody (
    RigidbodyPtr pRigidbody
) 
```




<hr>



### function RemoveRigidbody 

```C++
inline virtual bool SR_PHYSICS_NS::PhysicsWorld::RemoveRigidbody (
    RigidbodyPtr pRigidbody
) 
```




<hr>



### function StepSimulation 

```C++
inline virtual bool SR_PHYSICS_NS::PhysicsWorld::StepSimulation (
    float_t step
) 
```




<hr>



### function Synchronize 

```C++
inline virtual bool SR_PHYSICS_NS::PhysicsWorld::Synchronize () 
```




<hr>



### function ~PhysicsWorld 

```C++
SR_PHYSICS_NS::PhysicsWorld::~PhysicsWorld () override
```




<hr>
## Protected Attributes Documentation




### variable m\_library 

```C++
LibraryPtr SR_PHYSICS_NS::PhysicsWorld::m_library;
```




<hr>



### variable m\_raycast3dImpl 

```C++
Raycast3DImpl* SR_PHYSICS_NS::PhysicsWorld::m_raycast3dImpl;
```




<hr>



### variable m\_space 

```C++
Space SR_PHYSICS_NS::PhysicsWorld::m_space;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/PhysicsWorld.h`

