

# Class SR\_PTYPES\_NS::Rigidbody3DImpl



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**Rigidbody3DImpl**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md)








Inherits the following classes: [SR\_PTYPES\_NS::RigidbodyImpl](classSR__PTYPES__NS_1_1RigidbodyImpl.md)


Inherited by the following classes: [SR\_PTYPES\_NS::PhysXRigidbody3DImpl](classSR__PTYPES__NS_1_1PhysXRigidbody3DImpl.md)








































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**AddAngularVelocity**](#function-addangularvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |
| virtual void | [**AddLinearVelocity**](#function-addlinearvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetAngularVelocity**](#function-getangularvelocity) () const = 0<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetLinearVelocity**](#function-getlinearvelocity) () const = 0<br> |
| virtual void | [**SetAngularLock**](#function-setangularlock) (const SR\_MATH\_NS::BVector3 & lock) <br> |
| virtual void | [**SetAngularVelocity**](#function-setangularvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |
| virtual void | [**SetLinearLock**](#function-setlinearlock) (const SR\_MATH\_NS::BVector3 & lock) <br> |
| virtual void | [**SetLinearVelocity**](#function-setlinearvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |


## Public Functions inherited from SR_PTYPES_NS::RigidbodyImpl

See [SR\_PTYPES\_NS::RigidbodyImpl](classSR__PTYPES__NS_1_1RigidbodyImpl.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**ClearForces**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-clearforces) () <br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-gethandle) () noexcept const = 0<br> |
| virtual bool | [**InitBody**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-initbody) () <br> |
|  void | [**SetRigidbody**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-setrigidbody) ([**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* pRigidbody) <br> |
| virtual void | [**Synchronize**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-synchronize) () <br> |
| virtual void | [**UpdateInertia**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-updateinertia) () <br> |
| virtual bool | [**UpdateMatrix**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-updatematrix) (bool force) <br> |
| virtual bool | [**UpdateShapeInternal**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-updateshapeinternal) () <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |










## Protected Types inherited from SR_PTYPES_NS::RigidbodyImpl

See [SR\_PTYPES\_NS::RigidbodyImpl](classSR__PTYPES__NS_1_1RigidbodyImpl.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#typedef-libraryptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; PhysicsScene &gt; | [**PhysicsScenePtr**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#typedef-physicssceneptr)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#typedef-super)  <br> |












## Protected Attributes inherited from SR_PTYPES_NS::RigidbodyImpl

See [SR\_PTYPES\_NS::RigidbodyImpl](classSR__PTYPES__NS_1_1RigidbodyImpl.md)

| Type | Name |
| ---: | :--- |
|  [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* | [**m\_rigidbody**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#variable-m_rigidbody)   = `nullptr`<br> |
|  [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**m\_rigidbodyRotation**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#variable-m_rigidbodyrotation)   = `SR\_MATH\_NS::InfinityQuaternion`<br> |
|  SR\_MATH\_NS::FVector3 | [**m\_rigidbodyTranslation**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#variable-m_rigidbodytranslation)   = `SR\_MATH\_NS::InfinityFV3`<br> |
















































## Protected Functions inherited from SR_PTYPES_NS::RigidbodyImpl

See [SR\_PTYPES\_NS::RigidbodyImpl](classSR__PTYPES__NS_1_1RigidbodyImpl.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD T \* | [**GetRigidbody**](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-getrigidbody) () noexcept const<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function AddAngularVelocity 

```C++
inline virtual void SR_PTYPES_NS::Rigidbody3DImpl::AddAngularVelocity (
    const SR_MATH_NS::FVector3 & velocity
) 
```




<hr>



### function AddLinearVelocity 

```C++
inline virtual void SR_PTYPES_NS::Rigidbody3DImpl::AddLinearVelocity (
    const SR_MATH_NS::FVector3 & velocity
) 
```




<hr>



### function GetAngularVelocity 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody3DImpl::GetAngularVelocity () const = 0
```




<hr>



### function GetLinearVelocity 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody3DImpl::GetLinearVelocity () const = 0
```




<hr>



### function SetAngularLock 

```C++
inline virtual void SR_PTYPES_NS::Rigidbody3DImpl::SetAngularLock (
    const SR_MATH_NS::BVector3 & lock
) 
```




<hr>



### function SetAngularVelocity 

```C++
inline virtual void SR_PTYPES_NS::Rigidbody3DImpl::SetAngularVelocity (
    const SR_MATH_NS::FVector3 & velocity
) 
```




<hr>



### function SetLinearLock 

```C++
inline virtual void SR_PTYPES_NS::Rigidbody3DImpl::SetLinearLock (
    const SR_MATH_NS::BVector3 & lock
) 
```




<hr>



### function SetLinearVelocity 

```C++
inline virtual void SR_PTYPES_NS::Rigidbody3DImpl::SetLinearVelocity (
    const SR_MATH_NS::FVector3 & velocity
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/3D/Rigidbody3D.h`

