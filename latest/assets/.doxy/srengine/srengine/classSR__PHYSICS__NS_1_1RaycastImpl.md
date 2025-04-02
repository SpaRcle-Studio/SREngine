

# Class SR\_PHYSICS\_NS::RaycastImpl



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**RaycastImpl**](classSR__PHYSICS__NS_1_1RaycastImpl.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_PHYSICS\_NS::Raycast3DImpl](classSR__PHYSICS__NS_1_1Raycast3DImpl.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**SR\_UTILS\_NS::RaycastHit**](structSR__UTILS__NS_1_1RaycastHit.md) &gt; | [**RaycastHits**](#typedef-raycasthits)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RaycastImpl**](#function-raycastimpl) ([**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* world) <br> |
|   | [**~RaycastImpl**](#function-raycastimpl) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**m\_world**](#variable-m_world)   = `nullptr`<br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Types Documentation




### typedef RaycastHits 

```C++
using SR_PHYSICS_NS::RaycastImpl::RaycastHits =  std::vector<SR_UTILS_NS::RaycastHit>;
```




<hr>
## Public Functions Documentation




### function RaycastImpl 

```C++
inline explicit SR_PHYSICS_NS::RaycastImpl::RaycastImpl (
    SR_PHYSICS_NS::PhysicsWorld * world
) 
```




<hr>



### function ~RaycastImpl 

```C++
SR_PHYSICS_NS::RaycastImpl::~RaycastImpl () override
```




<hr>
## Protected Attributes Documentation




### variable m\_world 

```C++
SR_PHYSICS_NS::PhysicsWorld* SR_PHYSICS_NS::RaycastImpl::m_world;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/RaycastImpl.h`

