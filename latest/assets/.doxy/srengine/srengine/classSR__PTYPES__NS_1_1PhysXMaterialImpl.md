

# Class SR\_PTYPES\_NS::PhysXMaterialImpl



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**PhysXMaterialImpl**](classSR__PTYPES__NS_1_1PhysXMaterialImpl.md)








Inherits the following classes: [SR\_PTYPES\_NS::PhysicsMaterialImpl](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**DeInit**](#function-deinit) () override<br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () override<br> |
| virtual bool | [**Init**](#function-init) () override<br> |
|   | [**PhysXMaterialImpl**](#function-physxmaterialimpl) (LibraryPtr pLibrary) <br> |
|  bool | [**ReInit**](#function-reinit) () <br> |
| virtual void | [**SetMaterial**](#function-setmaterial) ([**PhysicsMaterial**](classSR__PTYPES__NS_1_1PhysicsMaterial.md) \* pMaterial) override<br> |
|   | [**~PhysXMaterialImpl**](#function-physxmaterialimpl) () override<br> |


## Public Functions inherited from SR_PTYPES_NS::PhysicsMaterialImpl

See [SR\_PTYPES\_NS::PhysicsMaterialImpl](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**DeInit**](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md#function-deinit) () = 0<br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md#function-gethandle) () = 0<br> |
|  SR\_NODISCARD T \* | [**GetLibrary**](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md#function-getlibrary) () const<br> |
| virtual bool | [**Init**](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md#function-init) () = 0<br> |
| virtual void | [**SetMaterial**](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md#function-setmaterial) ([**PhysicsMaterial**](classSR__PTYPES__NS_1_1PhysicsMaterial.md) \* pMaterial) = 0<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






































































## Protected Functions inherited from SR_PTYPES_NS::PhysicsMaterialImpl

See [SR\_PTYPES\_NS::PhysicsMaterialImpl](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md)

| Type | Name |
| ---: | :--- |
|   | [**PhysicsMaterialImpl**](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md#function-physicsmaterialimpl) (LibraryPtr pLibrary) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function DeInit 

```C++
virtual void SR_PTYPES_NS::PhysXMaterialImpl::DeInit () override
```



Implements [*SR\_PTYPES\_NS::PhysicsMaterialImpl::DeInit*](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md#function-deinit)


<hr>



### function GetHandle 

```C++
inline virtual SR_NODISCARD void * SR_PTYPES_NS::PhysXMaterialImpl::GetHandle () override
```



Implements [*SR\_PTYPES\_NS::PhysicsMaterialImpl::GetHandle*](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md#function-gethandle)


<hr>



### function Init 

```C++
virtual bool SR_PTYPES_NS::PhysXMaterialImpl::Init () override
```



Implements [*SR\_PTYPES\_NS::PhysicsMaterialImpl::Init*](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md#function-init)


<hr>



### function PhysXMaterialImpl 

```C++
explicit SR_PTYPES_NS::PhysXMaterialImpl::PhysXMaterialImpl (
    LibraryPtr pLibrary
) 
```




<hr>



### function ReInit 

```C++
bool SR_PTYPES_NS::PhysXMaterialImpl::ReInit () 
```




<hr>



### function SetMaterial 

```C++
inline virtual void SR_PTYPES_NS::PhysXMaterialImpl::SetMaterial (
    PhysicsMaterial * pMaterial
) override
```



Implements [*SR\_PTYPES\_NS::PhysicsMaterialImpl::SetMaterial*](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md#function-setmaterial)


<hr>



### function ~PhysXMaterialImpl 

```C++
SR_PTYPES_NS::PhysXMaterialImpl::~PhysXMaterialImpl () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/PhysX/PhysXMaterialImpl.h`

