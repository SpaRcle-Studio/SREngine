

# Namespace SR\_PHYSICS\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md)


















## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**Types**](namespaceSR__PHYSICS__NS_1_1Types.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**Box2DLibraryImpl**](classSR__PHYSICS__NS_1_1Box2DLibraryImpl.md) <br> |
| class | [**Bullet3LibraryImpl**](classSR__PHYSICS__NS_1_1Bullet3LibraryImpl.md) <br> |
| class | [**Bullet3PhysicsWorld**](classSR__PHYSICS__NS_1_1Bullet3PhysicsWorld.md) <br> |
| class | [**ContactReportCallback**](classSR__PHYSICS__NS_1_1ContactReportCallback.md) <br> |
| class | [**LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) <br> |
| class | [**PhysXLibraryImpl**](classSR__PHYSICS__NS_1_1PhysXLibraryImpl.md) <br> |
| class | [**PhysXPhysicsWorld**](classSR__PHYSICS__NS_1_1PhysXPhysicsWorld.md) <br> |
| class | [**PhysXRaycast3DImpl**](classSR__PHYSICS__NS_1_1PhysXRaycast3DImpl.md) <br> |
| class | [**PhysicsLibrary**](classSR__PHYSICS__NS_1_1PhysicsLibrary.md) <br> |
| class | [**PhysicsScene**](classSR__PHYSICS__NS_1_1PhysicsScene.md) <br> |
| class | [**PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) <br> |
| class | [**Raycast**](classSR__PHYSICS__NS_1_1Raycast.md) <br> |
| class | [**Raycast3D**](classSR__PHYSICS__NS_1_1Raycast3D.md) <br> |
| class | [**Raycast3DImpl**](classSR__PHYSICS__NS_1_1Raycast3DImpl.md) <br> |
| class | [**RaycastImpl**](classSR__PHYSICS__NS_1_1RaycastImpl.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef debugger::comm::PvdConnection | [**PhysXPvdConnection**](#typedef-physxpvdconnection)  <br> |
| enum uint8\_t | [**RBUpdShapeRes**](#enum-rbupdshaperes)  <br>_Rigidbody Update Shape Result._  |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SR\_ENUM\_NS\_CLASS**](#function-sr_enum_ns_class) (LibraryType, Unknown=0, Bullet3=1, Newton=2, PhysX=3, Havok=4, Volt=5, Shark=6, Box2D=7) <br> |




























## Public Types Documentation




### typedef PhysXPvdConnection 

```C++
typedef debugger::comm::PvdConnection SR_PHYSICS_NS::PhysXPvdConnection;
```




<hr>



### enum RBUpdShapeRes 

_Rigidbody Update Shape Result._ 
```C++
enum SR_PHYSICS_NS::RBUpdShapeRes {
    Updated = 0,
    Error = 1,
    Nothing = 2
};
```




<hr>
## Public Functions Documentation




### function SR\_ENUM\_NS\_CLASS 

```C++
SR_PHYSICS_NS::SR_ENUM_NS_CLASS (
    LibraryType,
    Unknown=0,
    Bullet3=1,
    Newton=2,
    PhysX=3,
    Havok=4,
    Volt=5,
    Shark=6,
    Box2D=7
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/inc/Core/Engine.h`

