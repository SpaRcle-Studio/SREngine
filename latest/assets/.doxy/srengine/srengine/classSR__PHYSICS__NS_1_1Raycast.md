

# Class SR\_PHYSICS\_NS::Raycast



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**Raycast**](classSR__PHYSICS__NS_1_1Raycast.md)










Inherited by the following classes: [SR\_PHYSICS\_NS::Raycast3D](classSR__PHYSICS__NS_1_1Raycast3D.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**SR\_UTILS\_NS::RaycastHit**](structSR__UTILS__NS_1_1RaycastHit.md) &gt; | [**RaycastHits**](#typedef-raycasthits)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**SwitchPhysics**](#function-switchphysics) ([**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* pWorld) <br> |
| virtual  | [**~Raycast**](#function-raycast) () = default<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**m\_world**](#variable-m_world)   = `nullptr`<br> |




















## Public Types Documentation




### typedef RaycastHits 

```C++
using SR_PHYSICS_NS::Raycast::RaycastHits =  std::vector<SR_UTILS_NS::RaycastHit>;
```




<hr>
## Public Functions Documentation




### function SwitchPhysics 

```C++
inline void SR_PHYSICS_NS::Raycast::SwitchPhysics (
    SR_PHYSICS_NS::PhysicsWorld * pWorld
) 
```




<hr>



### function ~Raycast 

```C++
virtual SR_PHYSICS_NS::Raycast::~Raycast () = default
```




<hr>
## Protected Attributes Documentation




### variable m\_world 

```C++
SR_PHYSICS_NS::PhysicsWorld* SR_PHYSICS_NS::Raycast::m_world;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/Raycast.h`

