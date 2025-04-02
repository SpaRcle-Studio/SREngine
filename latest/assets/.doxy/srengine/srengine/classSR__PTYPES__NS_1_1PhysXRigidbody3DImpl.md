

# Class SR\_PTYPES\_NS::PhysXRigidbody3DImpl



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**PhysXRigidbody3DImpl**](classSR__PTYPES__NS_1_1PhysXRigidbody3DImpl.md)








Inherits the following classes: [SR\_PTYPES\_NS::Rigidbody3DImpl](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md)






























































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**AddAngularVelocity**](#function-addangularvelocity) (const SR\_MATH\_NS::FVector3 & velocity) override<br> |
| virtual void | [**AddLinearVelocity**](#function-addlinearvelocity) (const SR\_MATH\_NS::FVector3 & velocity) override<br> |
| virtual void | [**ClearForces**](#function-clearforces) () override<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetAngularVelocity**](#function-getangularvelocity) () override const<br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () noexcept override const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetLinearVelocity**](#function-getlinearvelocity) () override const<br> |
| virtual bool | [**InitBody**](#function-initbody) () override<br> |
| virtual void | [**SetAngularLock**](#function-setangularlock) (const SR\_MATH\_NS::BVector3 & lock) override<br> |
| virtual void | [**SetAngularVelocity**](#function-setangularvelocity) (const SR\_MATH\_NS::FVector3 & velocity) override<br> |
| virtual void | [**SetLinearLock**](#function-setlinearlock) (const SR\_MATH\_NS::BVector3 & lock) override<br> |
| virtual void | [**SetLinearVelocity**](#function-setlinearvelocity) (const SR\_MATH\_NS::FVector3 & velocity) override<br> |
| virtual void | [**Synchronize**](#function-synchronize) () override<br> |
| virtual void | [**UpdateInertia**](#function-updateinertia) () override<br> |
| virtual bool | [**UpdateMatrix**](#function-updatematrix) (bool force) override<br> |
| virtual bool | [**UpdateShapeInternal**](#function-updateshapeinternal) () override<br> |
|   | [**~PhysXRigidbody3DImpl**](#function-physxrigidbody3dimpl) () override<br> |


## Public Functions inherited from SR_PTYPES_NS::Rigidbody3DImpl

See [SR\_PTYPES\_NS::Rigidbody3DImpl](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**AddAngularVelocity**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-addangularvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |
| virtual void | [**AddLinearVelocity**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-addlinearvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetAngularVelocity**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-getangularvelocity) () const = 0<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetLinearVelocity**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-getlinearvelocity) () const = 0<br> |
| virtual void | [**SetAngularLock**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-setangularlock) (const SR\_MATH\_NS::BVector3 & lock) <br> |
| virtual void | [**SetAngularVelocity**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-setangularvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |
| virtual void | [**SetLinearLock**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-setlinearlock) (const SR\_MATH\_NS::BVector3 & lock) <br> |
| virtual void | [**SetLinearVelocity**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-setlinearvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |


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
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |










## Public Functions Documentation




### function AddAngularVelocity 

```C++
virtual void SR_PTYPES_NS::PhysXRigidbody3DImpl::AddAngularVelocity (
    const SR_MATH_NS::FVector3 & velocity
) override
```



Implements [*SR\_PTYPES\_NS::Rigidbody3DImpl::AddAngularVelocity*](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-addangularvelocity)


<hr>



### function AddLinearVelocity 

```C++
virtual void SR_PTYPES_NS::PhysXRigidbody3DImpl::AddLinearVelocity (
    const SR_MATH_NS::FVector3 & velocity
) override
```



Implements [*SR\_PTYPES\_NS::Rigidbody3DImpl::AddLinearVelocity*](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-addlinearvelocity)


<hr>



### function ClearForces 

```C++
virtual void SR_PTYPES_NS::PhysXRigidbody3DImpl::ClearForces () override
```



Implements [*SR\_PTYPES\_NS::RigidbodyImpl::ClearForces*](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-clearforces)


<hr>



### function GetAngularVelocity 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::PhysXRigidbody3DImpl::GetAngularVelocity () override const
```



Implements [*SR\_PTYPES\_NS::Rigidbody3DImpl::GetAngularVelocity*](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-getangularvelocity)


<hr>



### function GetHandle 

```C++
virtual SR_NODISCARD void * SR_PTYPES_NS::PhysXRigidbody3DImpl::GetHandle () noexcept override const
```



Implements [*SR\_PTYPES\_NS::RigidbodyImpl::GetHandle*](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-gethandle)


<hr>



### function GetLinearVelocity 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::PhysXRigidbody3DImpl::GetLinearVelocity () override const
```



Implements [*SR\_PTYPES\_NS::Rigidbody3DImpl::GetLinearVelocity*](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-getlinearvelocity)


<hr>



### function InitBody 

```C++
virtual bool SR_PTYPES_NS::PhysXRigidbody3DImpl::InitBody () override
```



Implements [*SR\_PTYPES\_NS::RigidbodyImpl::InitBody*](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-initbody)


<hr>



### function SetAngularLock 

```C++
virtual void SR_PTYPES_NS::PhysXRigidbody3DImpl::SetAngularLock (
    const SR_MATH_NS::BVector3 & lock
) override
```



Implements [*SR\_PTYPES\_NS::Rigidbody3DImpl::SetAngularLock*](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-setangularlock)


<hr>



### function SetAngularVelocity 

```C++
virtual void SR_PTYPES_NS::PhysXRigidbody3DImpl::SetAngularVelocity (
    const SR_MATH_NS::FVector3 & velocity
) override
```



Implements [*SR\_PTYPES\_NS::Rigidbody3DImpl::SetAngularVelocity*](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-setangularvelocity)


<hr>



### function SetLinearLock 

```C++
virtual void SR_PTYPES_NS::PhysXRigidbody3DImpl::SetLinearLock (
    const SR_MATH_NS::BVector3 & lock
) override
```



Implements [*SR\_PTYPES\_NS::Rigidbody3DImpl::SetLinearLock*](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-setlinearlock)


<hr>



### function SetLinearVelocity 

```C++
virtual void SR_PTYPES_NS::PhysXRigidbody3DImpl::SetLinearVelocity (
    const SR_MATH_NS::FVector3 & velocity
) override
```



Implements [*SR\_PTYPES\_NS::Rigidbody3DImpl::SetLinearVelocity*](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md#function-setlinearvelocity)


<hr>



### function Synchronize 

```C++
virtual void SR_PTYPES_NS::PhysXRigidbody3DImpl::Synchronize () override
```



Implements [*SR\_PTYPES\_NS::RigidbodyImpl::Synchronize*](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-synchronize)


<hr>



### function UpdateInertia 

```C++
virtual void SR_PTYPES_NS::PhysXRigidbody3DImpl::UpdateInertia () override
```



Implements [*SR\_PTYPES\_NS::RigidbodyImpl::UpdateInertia*](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-updateinertia)


<hr>



### function UpdateMatrix 

```C++
virtual bool SR_PTYPES_NS::PhysXRigidbody3DImpl::UpdateMatrix (
    bool force
) override
```



Implements [*SR\_PTYPES\_NS::RigidbodyImpl::UpdateMatrix*](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-updatematrix)


<hr>



### function UpdateShapeInternal 

```C++
virtual bool SR_PTYPES_NS::PhysXRigidbody3DImpl::UpdateShapeInternal () override
```



Implements [*SR\_PTYPES\_NS::RigidbodyImpl::UpdateShapeInternal*](classSR__PTYPES__NS_1_1RigidbodyImpl.md#function-updateshapeinternal)


<hr>



### function ~PhysXRigidbody3DImpl 

```C++
SR_PTYPES_NS::PhysXRigidbody3DImpl::~PhysXRigidbody3DImpl () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/PhysX/PhysXRigidbody3D.h`

