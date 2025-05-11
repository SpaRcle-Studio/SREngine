

# Class SR\_GRAPH\_NS::Memory::CameraManager



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**CameraManager**](classSR__GRAPH__NS_1_1Memory_1_1CameraManager.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)






























































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::list&lt; CameraPtr &gt; | [**GetCameras**](#function-getcameras) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetCountCameras**](#function-getcountcameras) () const<br> |
|  SR\_NODISCARD CameraPtr | [**GetFirstCamera**](#function-getfirstcamera) () const<br> |
|  SR\_NODISCARD CameraPtr | [**GetMainCamera**](#function-getmaincamera) ([**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) \* pRScene) <br> |
|  SR\_NODISCARD std::vector&lt; CameraPtr &gt; | [**GetOffScreenCameras**](#function-getoffscreencameras) ([**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) \* pRScene) <br> |
|  SR\_NODISCARD bool | [**IsDestroyed**](#function-isdestroyed) (const CameraPtr & camera) const<br> |
|  SR\_NODISCARD bool | [**IsRegistered**](#function-isregistered) (const CameraPtr & camera) const<br> |
|  void | [**OnWindowResized**](#function-onwindowresized) ([**Window**](classSR__GRAPH__NS_1_1Window.md) \* pWindow, uint32\_t width, uint32\_t height) <br> |
|  void | [**SetPipeline**](#function-setpipeline) (PipelinePtr pPipeline) <br> |
|  void | [**Update**](#function-update) () <br> |




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




## Public Static Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySingleton**](classSR__UTILS__NS_1_1Singleton.md#function-destroysingleton) () <br> |
|  SR\_MAYBE\_UNUSED std::recursive\_mutex & | [**GetMutex**](classSR__UTILS__NS_1_1Singleton.md#function-getmutex) () noexcept<br> |
|  SR\_MAYBE\_UNUSED T & | [**Instance**](classSR__UTILS__NS_1_1Singleton.md#function-instance) () noexcept<br> |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](classSR__UTILS__NS_1_1Singleton.md#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-unlocksingleton) () noexcept<br> |


























## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |




























































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**OnSingletonDestroy**](#function-onsingletondestroy) () override<br> |
|   | [**~CameraManager**](#function-cameramanager) () override<br> |


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
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |










## Public Functions Documentation




### function GetCameras 

```C++
SR_NODISCARD std::list< CameraPtr > SR_GRAPH_NS::Memory::CameraManager::GetCameras () const
```




<hr>



### function GetCountCameras 

```C++
SR_NODISCARD uint32_t SR_GRAPH_NS::Memory::CameraManager::GetCountCameras () const
```




<hr>



### function GetFirstCamera 

```C++
SR_NODISCARD CameraPtr SR_GRAPH_NS::Memory::CameraManager::GetFirstCamera () const
```




<hr>



### function GetMainCamera 

```C++
SR_NODISCARD CameraPtr SR_GRAPH_NS::Memory::CameraManager::GetMainCamera (
    RenderScene * pRScene
) 
```




<hr>



### function GetOffScreenCameras 

```C++
SR_NODISCARD std::vector< CameraPtr > SR_GRAPH_NS::Memory::CameraManager::GetOffScreenCameras (
    RenderScene * pRScene
) 
```




<hr>



### function IsDestroyed 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Memory::CameraManager::IsDestroyed (
    const CameraPtr & camera
) const
```




<hr>



### function IsRegistered 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Memory::CameraManager::IsRegistered (
    const CameraPtr & camera
) const
```




<hr>



### function OnWindowResized 

```C++
void SR_GRAPH_NS::Memory::CameraManager::OnWindowResized (
    Window * pWindow,
    uint32_t width,
    uint32_t height
) 
```




<hr>



### function SetPipeline 

```C++
inline void SR_GRAPH_NS::Memory::CameraManager::SetPipeline (
    PipelinePtr pPipeline
) 
```




<hr>



### function Update 

```C++
void SR_GRAPH_NS::Memory::CameraManager::Update () 
```




<hr>
## Protected Functions Documentation




### function OnSingletonDestroy 

```C++
virtual void SR_GRAPH_NS::Memory::CameraManager::OnSingletonDestroy () override
```



Implements [*SR\_UTILS\_NS::SingletonBase::OnSingletonDestroy*](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy)


<hr>



### function ~CameraManager 

```C++
SR_GRAPH_NS::Memory::CameraManager::~CameraManager () override
```




<hr>## Friends Documentation





### friend Camera 

```C++
class SR_GRAPH_NS::Memory::CameraManager::Camera (
    SR_GTYPES_NS::Camera
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Memory/CameraManager.h`

