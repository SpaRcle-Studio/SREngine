

# Class SR\_PHYSICS\_NS::Raycast3D



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**Raycast3D**](classSR__PHYSICS__NS_1_1Raycast3D.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_PHYSICS\_NS::Raycast](classSR__PHYSICS__NS_1_1Raycast.md)






















## Public Types inherited from SR_PHYSICS_NS::Raycast

See [SR\_PHYSICS\_NS::Raycast](classSR__PHYSICS__NS_1_1Raycast.md)

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**SR\_UTILS\_NS::RaycastHit**](structSR__UTILS__NS_1_1RaycastHit.md) &gt; | [**RaycastHits**](classSR__PHYSICS__NS_1_1Raycast.md#typedef-raycasthits)  <br> |




























































































## Public Functions

| Type | Name |
| ---: | :--- |
|  RaycastHits | [**Cast**](#function-cast-12) (const SR\_MATH\_NS::FVector3 & origin, const SR\_MATH\_NS::FVector3 & direction, float\_t maxDistance, uint32\_t maxHits) <br> |
|  RaycastHits | [**Cast**](#function-cast-22) (const SR\_MATH\_NS::FVector3 & origin, const SR\_MATH\_NS::FVector3 & direction, float\_t maxDistance) <br> |




## Public Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|   | [**~SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Functions inherited from SR_PHYSICS_NS::Raycast

See [SR\_PHYSICS\_NS::Raycast](classSR__PHYSICS__NS_1_1Raycast.md)

| Type | Name |
| ---: | :--- |
|  void | [**SwitchPhysics**](classSR__PHYSICS__NS_1_1Raycast.md#function-switchphysics) ([**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* pWorld) <br> |
| virtual  | [**~Raycast**](classSR__PHYSICS__NS_1_1Raycast.md#function-raycast) () = default<br> |




## Public Static Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySingleton**](classSR__UTILS__NS_1_1Singleton.md#function-destroysingleton) () <br> |
|  SR\_MAYBE\_UNUSED std::recursive\_mutex & | [**GetMutex**](classSR__UTILS__NS_1_1Singleton.md#function-getmutex) () noexcept<br> |
|  SR\_MAYBE\_UNUSED T & | [**Instance**](classSR__UTILS__NS_1_1Singleton.md#function-instance) () noexcept<br>_TODO: (Multi-threading) Refactor Singleton::Instance()._  |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](classSR__UTILS__NS_1_1Singleton.md#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-unlocksingleton) () noexcept<br> |
































## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |




## Protected Attributes inherited from SR_PHYSICS_NS::Raycast

See [SR\_PHYSICS\_NS::Raycast](classSR__PHYSICS__NS_1_1Raycast.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**m\_world**](classSR__PHYSICS__NS_1_1Raycast.md#variable-m_world)   = `nullptr`<br> |










































































## Protected Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|   | [**Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () <br> |
|   | [**~Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSingletonName**](classSR__UTILS__NS_1_1SingletonBase.md#function-getsingletonname) () noexcept const = 0<br> |
| virtual void | [**InitSingleton**](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton) () <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed) () const<br> |
| virtual void | [**OnSingletonDestroy**](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy) () <br> |
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |














## Public Functions Documentation




### function Cast [1/2]

```C++
RaycastHits SR_PHYSICS_NS::Raycast3D::Cast (
    const SR_MATH_NS::FVector3 & origin,
    const SR_MATH_NS::FVector3 & direction,
    float_t maxDistance,
    uint32_t maxHits
) 
```




<hr>



### function Cast [2/2]

```C++
RaycastHits SR_PHYSICS_NS::Raycast3D::Cast (
    const SR_MATH_NS::FVector3 & origin,
    const SR_MATH_NS::FVector3 & direction,
    float_t maxDistance
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/3D/Raycast3D.h`

