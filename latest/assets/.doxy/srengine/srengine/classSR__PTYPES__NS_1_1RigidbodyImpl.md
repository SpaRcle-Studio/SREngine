

# Class SR\_PTYPES\_NS::RigidbodyImpl



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**RigidbodyImpl**](classSR__PTYPES__NS_1_1RigidbodyImpl.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_PTYPES\_NS::Rigidbody2DImpl](classSR__PTYPES__NS_1_1Rigidbody2DImpl.md),  [SR\_PTYPES\_NS::Rigidbody3DImpl](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**ClearForces**](#function-clearforces) () <br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () noexcept const = 0<br> |
| virtual bool | [**InitBody**](#function-initbody) () <br> |
|  void | [**SetRigidbody**](#function-setrigidbody) ([**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* pRigidbody) <br> |
|  void | [**SetSyncAllowed**](#function-setsyncallowed) (bool allowed) <br> |
| virtual void | [**Synchronize**](#function-synchronize) () <br> |
| virtual void | [**UpdateInertia**](#function-updateinertia) () <br> |
| virtual bool | [**UpdateMatrix**](#function-updatematrix) (bool force) <br> |
| virtual bool | [**UpdateShapeInternal**](#function-updateshapeinternal) () <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






## Protected Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](#typedef-libraryptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; PhysicsScene &gt; | [**PhysicsScenePtr**](#typedef-physicssceneptr)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](#typedef-super)  <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**m\_isSyncAllowed**](#variable-m_issyncallowed)   = `true`<br> |
|  [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* | [**m\_rigidbody**](#variable-m_rigidbody)   = `nullptr`<br> |
|  [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**m\_rigidbodyRotation**](#variable-m_rigidbodyrotation)   = `SR\_MATH\_NS::InfinityQuaternion`<br> |
|  SR\_MATH\_NS::FVector3 | [**m\_rigidbodyTranslation**](#variable-m_rigidbodytranslation)   = `SR\_MATH\_NS::InfinityFV3`<br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD T \* | [**GetRigidbody**](#function-getrigidbody) () noexcept const<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function ClearForces 

```C++
inline virtual void SR_PTYPES_NS::RigidbodyImpl::ClearForces () 
```




<hr>



### function GetHandle 

```C++
virtual SR_NODISCARD void * SR_PTYPES_NS::RigidbodyImpl::GetHandle () noexcept const = 0
```




<hr>



### function InitBody 

```C++
inline virtual bool SR_PTYPES_NS::RigidbodyImpl::InitBody () 
```




<hr>



### function SetRigidbody 

```C++
inline void SR_PTYPES_NS::RigidbodyImpl::SetRigidbody (
    Rigidbody * pRigidbody
) 
```




<hr>



### function SetSyncAllowed 

```C++
inline void SR_PTYPES_NS::RigidbodyImpl::SetSyncAllowed (
    bool allowed
) 
```




<hr>



### function Synchronize 

```C++
inline virtual void SR_PTYPES_NS::RigidbodyImpl::Synchronize () 
```




<hr>



### function UpdateInertia 

```C++
inline virtual void SR_PTYPES_NS::RigidbodyImpl::UpdateInertia () 
```




<hr>



### function UpdateMatrix 

```C++
inline virtual bool SR_PTYPES_NS::RigidbodyImpl::UpdateMatrix (
    bool force
) 
```




<hr>



### function UpdateShapeInternal 

```C++
inline virtual bool SR_PTYPES_NS::RigidbodyImpl::UpdateShapeInternal () 
```




<hr>
## Protected Types Documentation




### typedef LibraryPtr 

```C++
using SR_PTYPES_NS::RigidbodyImpl::LibraryPtr =  SR_PHYSICS_NS::LibraryImpl*;
```




<hr>



### typedef PhysicsScenePtr 

```C++
using SR_PTYPES_NS::RigidbodyImpl::PhysicsScenePtr =  SR_HTYPES_NS::SafePtr<PhysicsScene>;
```




<hr>



### typedef Super 

```C++
using SR_PTYPES_NS::RigidbodyImpl::Super =  SR_UTILS_NS::NonCopyable;
```




<hr>
## Protected Attributes Documentation




### variable m\_isSyncAllowed 

```C++
bool SR_PTYPES_NS::RigidbodyImpl::m_isSyncAllowed;
```




<hr>



### variable m\_rigidbody 

```C++
Rigidbody* SR_PTYPES_NS::RigidbodyImpl::m_rigidbody;
```




<hr>



### variable m\_rigidbodyRotation 

```C++
SR_MATH_NS::Quaternion SR_PTYPES_NS::RigidbodyImpl::m_rigidbodyRotation;
```




<hr>



### variable m\_rigidbodyTranslation 

```C++
SR_MATH_NS::FVector3 SR_PTYPES_NS::RigidbodyImpl::m_rigidbodyTranslation;
```




<hr>
## Protected Functions Documentation




### function GetRigidbody 

```C++
template<typename T>
inline SR_NODISCARD T * SR_PTYPES_NS::RigidbodyImpl::GetRigidbody () noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/Rigidbody.h`

