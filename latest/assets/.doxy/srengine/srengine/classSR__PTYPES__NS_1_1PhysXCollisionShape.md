

# Class SR\_PTYPES\_NS::PhysXCollisionShape



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**PhysXCollisionShape**](classSR__PTYPES__NS_1_1PhysXCollisionShape.md)








Inherits the following classes: [SR\_PTYPES\_NS::CollisionShapeImpl](classSR__PTYPES__NS_1_1CollisionShapeImpl.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD physx::PxConvexMesh \* | [**CreateConvexMesh**](#function-createconvexmesh) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh) <br> |
|  SR\_NODISCARD physx::PxTriangleMesh \* | [**CreateTriangleMesh**](#function-createtrianglemesh) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh) <br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () noexcept override const<br> |
|  SR\_NODISCARD physx::PxMaterial \* | [**GetMaterial**](#function-getmaterial) () const<br> |
| virtual bool | [**UpdateMatrix**](#function-updatematrix) () override<br> |
| virtual bool | [**UpdateShape**](#function-updateshape) () override<br> |
|   | [**~PhysXCollisionShape**](#function-physxcollisionshape) () override<br> |


## Public Functions inherited from SR_PTYPES_NS::CollisionShapeImpl

See [SR\_PTYPES\_NS::CollisionShapeImpl](classSR__PTYPES__NS_1_1CollisionShapeImpl.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**CalculateLocalInertia**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md#function-calculatelocalinertia) (float\_t mass) const<br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md#function-gethandle) () noexcept const<br> |
|  SR\_NODISCARD [**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md) \* | [**GetShape**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md#function-getshape) () noexcept const<br> |
|  void | [**SetShape**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md#function-setshape) ([**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md) \* pShape) <br> |
| virtual void | [**Update**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md#function-update) (float\_t dt) <br> |
| virtual bool | [**UpdateMatrix**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md#function-updatematrix) () <br> |
| virtual bool | [**UpdateShape**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md#function-updateshape) () <br> |


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




### function CreateConvexMesh 

```C++
SR_NODISCARD physx::PxConvexMesh * SR_PTYPES_NS::PhysXCollisionShape::CreateConvexMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh
) 
```




<hr>



### function CreateTriangleMesh 

```C++
SR_NODISCARD physx::PxTriangleMesh * SR_PTYPES_NS::PhysXCollisionShape::CreateTriangleMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh
) 
```




<hr>



### function GetHandle 

```C++
inline virtual SR_NODISCARD void * SR_PTYPES_NS::PhysXCollisionShape::GetHandle () noexcept override const
```



Implements [*SR\_PTYPES\_NS::CollisionShapeImpl::GetHandle*](classSR__PTYPES__NS_1_1CollisionShapeImpl.md#function-gethandle)


<hr>



### function GetMaterial 

```C++
SR_NODISCARD physx::PxMaterial * SR_PTYPES_NS::PhysXCollisionShape::GetMaterial () const
```




<hr>



### function UpdateMatrix 

```C++
virtual bool SR_PTYPES_NS::PhysXCollisionShape::UpdateMatrix () override
```



Implements [*SR\_PTYPES\_NS::CollisionShapeImpl::UpdateMatrix*](classSR__PTYPES__NS_1_1CollisionShapeImpl.md#function-updatematrix)


<hr>



### function UpdateShape 

```C++
virtual bool SR_PTYPES_NS::PhysXCollisionShape::UpdateShape () override
```



Implements [*SR\_PTYPES\_NS::CollisionShapeImpl::UpdateShape*](classSR__PTYPES__NS_1_1CollisionShapeImpl.md#function-updateshape)


<hr>



### function ~PhysXCollisionShape 

```C++
SR_PTYPES_NS::PhysXCollisionShape::~PhysXCollisionShape () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/PhysX/PhysXCollisionShape.h`

