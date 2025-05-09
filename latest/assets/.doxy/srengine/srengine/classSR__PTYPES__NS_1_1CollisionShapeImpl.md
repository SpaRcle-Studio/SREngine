

# Class SR\_PTYPES\_NS::CollisionShapeImpl



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**CollisionShapeImpl**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_PTYPES\_NS::PhysXCollisionShape](classSR__PTYPES__NS_1_1PhysXCollisionShape.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**CalculateLocalInertia**](#function-calculatelocalinertia) (float\_t mass) const<br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () noexcept const<br> |
|  SR\_NODISCARD [**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md) \* | [**GetShape**](#function-getshape) () noexcept const<br> |
|  void | [**SetShape**](#function-setshape) ([**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md) \* pShape) <br> |
| virtual void | [**Update**](#function-update) (float\_t dt) <br> |
| virtual bool | [**UpdateMatrix**](#function-updatematrix) () <br> |
| virtual bool | [**UpdateShape**](#function-updateshape) () <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function CalculateLocalInertia 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShapeImpl::CalculateLocalInertia (
    float_t mass
) const
```




<hr>



### function GetHandle 

```C++
inline virtual SR_NODISCARD void * SR_PTYPES_NS::CollisionShapeImpl::GetHandle () noexcept const
```




<hr>



### function GetShape 

```C++
inline SR_NODISCARD CollisionShape * SR_PTYPES_NS::CollisionShapeImpl::GetShape () noexcept const
```




<hr>



### function SetShape 

```C++
inline void SR_PTYPES_NS::CollisionShapeImpl::SetShape (
    CollisionShape * pShape
) 
```




<hr>



### function Update 

```C++
inline virtual void SR_PTYPES_NS::CollisionShapeImpl::Update (
    float_t dt
) 
```




<hr>



### function UpdateMatrix 

```C++
inline virtual bool SR_PTYPES_NS::CollisionShapeImpl::UpdateMatrix () 
```




<hr>



### function UpdateShape 

```C++
inline virtual bool SR_PTYPES_NS::CollisionShapeImpl::UpdateShape () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/CollisionShape.h`

