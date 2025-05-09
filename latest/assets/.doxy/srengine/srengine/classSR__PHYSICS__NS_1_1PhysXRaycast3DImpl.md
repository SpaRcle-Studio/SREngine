

# Class SR\_PHYSICS\_NS::PhysXRaycast3DImpl



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**PhysXRaycast3DImpl**](classSR__PHYSICS__NS_1_1PhysXRaycast3DImpl.md)








Inherits the following classes: [SR\_PHYSICS\_NS::Raycast3DImpl](classSR__PHYSICS__NS_1_1Raycast3DImpl.md)


















## Public Types inherited from SR_PHYSICS_NS::RaycastImpl

See [SR\_PHYSICS\_NS::RaycastImpl](classSR__PHYSICS__NS_1_1RaycastImpl.md)

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**SR\_UTILS\_NS::RaycastHit**](structSR__UTILS__NS_1_1RaycastHit.md) &gt; | [**RaycastHits**](classSR__PHYSICS__NS_1_1RaycastImpl.md#typedef-raycasthits)  <br> |












































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual RaycastHits | [**Cast**](#function-cast) (const SR\_MATH\_NS::FVector3 & origin, const SR\_MATH\_NS::FVector3 & direction, float\_t maxDistance, uint32\_t maxHits) override<br> |
|   | [**PhysXRaycast3DImpl**](#function-physxraycast3dimpl) ([**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* world) <br> |


## Public Functions inherited from SR_PHYSICS_NS::Raycast3DImpl

See [SR\_PHYSICS\_NS::Raycast3DImpl](classSR__PHYSICS__NS_1_1Raycast3DImpl.md)

| Type | Name |
| ---: | :--- |
| virtual RaycastHits | [**Cast**](classSR__PHYSICS__NS_1_1Raycast3DImpl.md#function-cast) (const SR\_MATH\_NS::FVector3 & origin, const SR\_MATH\_NS::FVector3 & direction, float\_t maxDistance, uint32\_t maxHits) = 0<br> |
|   | [**Raycast3DImpl**](classSR__PHYSICS__NS_1_1Raycast3DImpl.md#function-raycast3dimpl) ([**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* world) <br> |


## Public Functions inherited from SR_PHYSICS_NS::RaycastImpl

See [SR\_PHYSICS\_NS::RaycastImpl](classSR__PHYSICS__NS_1_1RaycastImpl.md)

| Type | Name |
| ---: | :--- |
|   | [**RaycastImpl**](classSR__PHYSICS__NS_1_1RaycastImpl.md#function-raycastimpl) ([**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* world) <br> |
|   | [**~RaycastImpl**](classSR__PHYSICS__NS_1_1RaycastImpl.md#function-raycastimpl) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






























## Protected Attributes inherited from SR_PHYSICS_NS::RaycastImpl

See [SR\_PHYSICS\_NS::RaycastImpl](classSR__PHYSICS__NS_1_1RaycastImpl.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**m\_world**](classSR__PHYSICS__NS_1_1RaycastImpl.md#variable-m_world)   = `nullptr`<br> |


































































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |










## Public Functions Documentation




### function Cast 

```C++
virtual RaycastHits SR_PHYSICS_NS::PhysXRaycast3DImpl::Cast (
    const SR_MATH_NS::FVector3 & origin,
    const SR_MATH_NS::FVector3 & direction,
    float_t maxDistance,
    uint32_t maxHits
) override
```



Implements [*SR\_PHYSICS\_NS::Raycast3DImpl::Cast*](classSR__PHYSICS__NS_1_1Raycast3DImpl.md#function-cast)


<hr>



### function PhysXRaycast3DImpl 

```C++
inline explicit SR_PHYSICS_NS::PhysXRaycast3DImpl::PhysXRaycast3DImpl (
    SR_PHYSICS_NS::PhysicsWorld * world
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/PhysX/PhysXRaycast3DImpl.h`

