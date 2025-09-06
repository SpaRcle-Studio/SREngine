

# Class SR\_PHYSICS\_NS::PhysicsScene



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**PhysicsScene**](classSR__PHYSICS__NS_1_1PhysicsScene.md)








Inherits the following classes: [SR\_HTYPES\_NS::SafePtr](classSR__HTYPES__NS_1_1SafePtr.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](#typedef-libraryptr)  <br> |
| typedef [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**PhysicsWorldPtr**](#typedef-physicsworldptr)  <br> |
| typedef Super | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_PTYPES\_NS::Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) &gt; | [**RigidbodyPtr**](#typedef-rigidbodyptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**ScenePtr**](#typedef-sceneptr)  <br> |
| typedef SR\_UTILS\_NS::Measurement | [**Space**](#typedef-space)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; [**PhysicsScene**](classSR__PHYSICS__NS_1_1PhysicsScene.md) &gt; | [**Super**](#typedef-super)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**ClearForces**](#function-clearforces) () <br> |
| virtual void | [**FixedUpdate**](#function-fixedupdate) () <br> |
|  SR\_NODISCARD [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**Get2DWorld**](#function-get2dworld) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**Get3DWorld**](#function-get3dworld) () noexcept const<br> |
| virtual bool | [**Init**](#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsDebugEnabled**](#function-isdebugenabled) () noexcept const<br> |
|   | [**PhysicsScene**](#function-physicsscene) (const ScenePtr & scene) <br> |
| virtual void | [**Register**](#function-register) (RigidbodyPtr pRigidbody) <br> |
| virtual void | [**Remove**](#function-remove) (RigidbodyPtr pRigidbody) <br> |
|  void | [**SetIsGameMode**](#function-setisgamemode) (bool enabled) noexcept<br> |
| virtual void | [**Update**](#function-update) (float\_t dt) <br> |
| virtual  | [**~PhysicsScene**](#function-physicsscene) () <br> |


## Public Functions inherited from SR_HTYPES_NS::SafePtr

See [SR\_HTYPES\_NS::SafePtr](classSR__HTYPES__NS_1_1SafePtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SafePtr.md#function-autofree-12) (const std::function&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SafePtr.md#function-autofree-22) () <br> |
|  bool | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-14) (const std::function&lt; void(T \*ptr)&gt; & func) <br> |
|  U | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-24) (const std::function&lt; U(T \*ptr)&gt; & func, U \_default) <br> |
|  bool | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-34) (const std::function&lt; void(T \*)&gt; & func) <br> |
|  U | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-44) (const std::function&lt; U(T \*)&gt; & func, U \_default) <br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SafePtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](classSR__HTYPES__NS_1_1SafePtr.md#function-get) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE [**SafePtrDynamicData**](structSR__HTYPES__NS_1_1SafePtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SafePtr.md#function-getptrdata) () noexcept const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-getrawptr) () const<br> |
|  SR\_NODISCARD [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SafePtr.md#function-getthis) () <br> |
|  SR\_NODISCARD uint32\_t | [**GetUseCount**](classSR__HTYPES__NS_1_1SafePtr.md#function-getusecount) () const<br> |
|  SR\_NODISCARD bool | [**IsLocked**](classSR__HTYPES__NS_1_1SafePtr.md#function-islocked) () const<br> |
|  void | [**Lock**](classSR__HTYPES__NS_1_1SafePtr.md#function-lock) () const<br> |
|  SR\_NODISCARD bool | [**LockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-lockifvalid) () const<br> |
|  void | [**RecursiveLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-recursivelock) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-recursivelockifvalid) () const<br> |
|  void | [**RemoveAllLocks**](classSR__HTYPES__NS_1_1SafePtr.md#function-removealllocks) () <br> |
|  void | [**Replace**](classSR__HTYPES__NS_1_1SafePtr.md#function-replace) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|  void | [**ReplaceAndCopyLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-replaceandcopylock) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|  void | [**ReplaceAndLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-replaceandlock) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|   | [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr-13) (const T \* ptr) <br> |
|   | [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr-23) ([**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) const & ptr) <br> |
|   | [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr-33) () <br> |
|  U | [**TryDo**](classSR__HTYPES__NS_1_1SafePtr.md#function-trydo-12) (const std::function&lt; U(T \*ptr)&gt; & func, U \_default) <br> |
|  U | [**TryDo**](classSR__HTYPES__NS_1_1SafePtr.md#function-trydo-22) (const std::function&lt; U(T \*)&gt; & func, U \_default) <br> |
|  bool | [**TryLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-trylock) () const<br> |
|  SR\_NODISCARD bool | [**TryLockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-trylockifvalid) () const<br> |
|  bool | [**TryRecursiveLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-tryrecursivelock) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-tryrecursivelockifvalid) () const<br> |
|  bool | [**TryUnlock**](classSR__HTYPES__NS_1_1SafePtr.md#function-tryunlock) () const<br> |
|  void | [**Unlock**](classSR__HTYPES__NS_1_1SafePtr.md#function-unlock) () const<br> |
|  SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SafePtr.md#function-valid) () const<br> |
|   | [**operator bool**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator-bool) () noexcept const<br>_не должен быть виртуальным_  |
|  SR\_NODISCARD SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & right) noexcept const<br> |
|  T & | [**operator\***](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_1) () const<br> |
|  T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator-) () const<br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_2) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & ptr) <br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_3) (T \* ptr) <br> |
|  SR\_NODISCARD SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_4) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & right) noexcept const<br> |
|   | [**~SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr) () <br> |






















































## Public Types Documentation




### typedef LibraryPtr 

```C++
using SR_PHYSICS_NS::PhysicsScene::LibraryPtr =  SR_PHYSICS_NS::LibraryImpl*;
```




<hr>



### typedef PhysicsWorldPtr 

```C++
using SR_PHYSICS_NS::PhysicsScene::PhysicsWorldPtr =  SR_PHYSICS_NS::PhysicsWorld*;
```




<hr>



### typedef Ptr 

```C++
using SR_PHYSICS_NS::PhysicsScene::Ptr =  Super;
```




<hr>



### typedef RigidbodyPtr 

```C++
using SR_PHYSICS_NS::PhysicsScene::RigidbodyPtr =  SR_HTYPES_NS::SharedPtr<SR_PTYPES_NS::Rigidbody>;
```




<hr>



### typedef ScenePtr 

```C++
using SR_PHYSICS_NS::PhysicsScene::ScenePtr =  SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;
```




<hr>



### typedef Space 

```C++
using SR_PHYSICS_NS::PhysicsScene::Space =  SR_UTILS_NS::Measurement;
```




<hr>



### typedef Super 

```C++
using SR_PHYSICS_NS::PhysicsScene::Super =  SR_HTYPES_NS::SafePtr<PhysicsScene>;
```




<hr>
## Public Functions Documentation




### function ClearForces 

```C++
virtual void SR_PHYSICS_NS::PhysicsScene::ClearForces () 
```




<hr>



### function FixedUpdate 

```C++
virtual void SR_PHYSICS_NS::PhysicsScene::FixedUpdate () 
```




<hr>



### function Get2DWorld 

```C++
inline SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld * SR_PHYSICS_NS::PhysicsScene::Get2DWorld () noexcept const
```




<hr>



### function Get3DWorld 

```C++
inline SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld * SR_PHYSICS_NS::PhysicsScene::Get3DWorld () noexcept const
```




<hr>



### function Init 

```C++
virtual bool SR_PHYSICS_NS::PhysicsScene::Init () 
```




<hr>



### function IsDebugEnabled 

```C++
SR_NODISCARD bool SR_PHYSICS_NS::PhysicsScene::IsDebugEnabled () noexcept const
```




<hr>



### function PhysicsScene 

```C++
explicit SR_PHYSICS_NS::PhysicsScene::PhysicsScene (
    const ScenePtr & scene
) 
```




<hr>



### function Register 

```C++
virtual void SR_PHYSICS_NS::PhysicsScene::Register (
    RigidbodyPtr pRigidbody
) 
```




<hr>



### function Remove 

```C++
virtual void SR_PHYSICS_NS::PhysicsScene::Remove (
    RigidbodyPtr pRigidbody
) 
```




<hr>



### function SetIsGameMode 

```C++
inline void SR_PHYSICS_NS::PhysicsScene::SetIsGameMode (
    bool enabled
) noexcept
```




<hr>



### function Update 

```C++
virtual void SR_PHYSICS_NS::PhysicsScene::Update (
    float_t dt
) 
```




<hr>



### function ~PhysicsScene 

```C++
virtual SR_PHYSICS_NS::PhysicsScene::~PhysicsScene () 
```




<hr>## Friends Documentation





### friend SafePtr&lt; PhysicsScene &gt; 

```C++
class SR_PHYSICS_NS::PhysicsScene::SafePtr< PhysicsScene > (
    SR_HTYPES_NS::SafePtr < PhysicsScene >
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/PhysicsScene.h`

