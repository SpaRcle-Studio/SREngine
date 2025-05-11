

# Class SR\_PTYPES\_NS::PhysicsMaterialImpl



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**PhysicsMaterialImpl**](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_PTYPES\_NS::PhysXMaterialImpl](classSR__PTYPES__NS_1_1PhysXMaterialImpl.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**DeInit**](#function-deinit) () = 0<br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () = 0<br> |
|  SR\_NODISCARD T \* | [**GetLibrary**](#function-getlibrary) () const<br> |
| virtual bool | [**Init**](#function-init) () = 0<br> |
| virtual void | [**SetMaterial**](#function-setmaterial) ([**PhysicsMaterial**](classSR__PTYPES__NS_1_1PhysicsMaterial.md) \* pMaterial) = 0<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**PhysicsMaterialImpl**](#function-physicsmaterialimpl) (LibraryPtr pLibrary) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function DeInit 

```C++
virtual void SR_PTYPES_NS::PhysicsMaterialImpl::DeInit () = 0
```




<hr>



### function GetHandle 

```C++
virtual SR_NODISCARD void * SR_PTYPES_NS::PhysicsMaterialImpl::GetHandle () = 0
```




<hr>



### function GetLibrary 

```C++
template<typename T>
inline SR_NODISCARD T * SR_PTYPES_NS::PhysicsMaterialImpl::GetLibrary () const
```




<hr>



### function Init 

```C++
virtual bool SR_PTYPES_NS::PhysicsMaterialImpl::Init () = 0
```




<hr>



### function SetMaterial 

```C++
virtual void SR_PTYPES_NS::PhysicsMaterialImpl::SetMaterial (
    PhysicsMaterial * pMaterial
) = 0
```




<hr>
## Protected Functions Documentation




### function PhysicsMaterialImpl 

```C++
inline explicit SR_PTYPES_NS::PhysicsMaterialImpl::PhysicsMaterialImpl (
    LibraryPtr pLibrary
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/PhysicsMaterialImpl.h`

