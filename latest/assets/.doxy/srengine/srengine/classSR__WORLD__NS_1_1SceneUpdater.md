

# Class SR\_WORLD\_NS::SceneUpdater



[**ClassList**](annotated.md) **>** [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) **>** [**SceneUpdater**](classSR__WORLD__NS_1_1SceneUpdater.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Build**](#function-build) (bool isPaused) <br> |
|  void | [**FixedUpdate**](#function-fixedupdate) (bool isPaused) <br> |
|  SR\_NODISCARD SR\_UTILS\_NS::TimePointType | [**GetLastBuildTime**](#function-getlastbuildtime) () const<br> |
|  void | [**LateUpdate**](#function-lateupdate) (bool isPaused) <br> |
|  void | [**RegisterComponent**](#function-registercomponent) ([**SR\_UTILS\_NS::Component**](classSR__UTILS__NS_1_1Component.md) \* pComponent) <br> |
|   | [**SceneUpdater**](#function-sceneupdater) ([**Scene**](classSR__WORLD__NS_1_1Scene.md) \* pScene) <br> |
|  void | [**SetDirty**](#function-setdirty) () <br> |
|  void | [**UnRegisterComponent**](#function-unregistercomponent) ([**SR\_UTILS\_NS::Component**](classSR__UTILS__NS_1_1Component.md) \* pComponent) <br> |
|  void | [**Update**](#function-update) (float\_t dt, bool isPaused) <br> |


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




### function Build 

```C++
void SR_WORLD_NS::SceneUpdater::Build (
    bool isPaused
) 
```




<hr>



### function FixedUpdate 

```C++
void SR_WORLD_NS::SceneUpdater::FixedUpdate (
    bool isPaused
) 
```




<hr>



### function GetLastBuildTime 

```C++
inline SR_NODISCARD SR_UTILS_NS::TimePointType SR_WORLD_NS::SceneUpdater::GetLastBuildTime () const
```




<hr>



### function LateUpdate 

```C++
void SR_WORLD_NS::SceneUpdater::LateUpdate (
    bool isPaused
) 
```




<hr>



### function RegisterComponent 

```C++
void SR_WORLD_NS::SceneUpdater::RegisterComponent (
    SR_UTILS_NS::Component * pComponent
) 
```




<hr>



### function SceneUpdater 

```C++
explicit SR_WORLD_NS::SceneUpdater::SceneUpdater (
    Scene * pScene
) 
```




<hr>



### function SetDirty 

```C++
void SR_WORLD_NS::SceneUpdater::SetDirty () 
```




<hr>



### function UnRegisterComponent 

```C++
void SR_WORLD_NS::SceneUpdater::UnRegisterComponent (
    SR_UTILS_NS::Component * pComponent
) 
```




<hr>



### function Update 

```C++
void SR_WORLD_NS::SceneUpdater::Update (
    float_t dt,
    bool isPaused
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/World/SceneUpdater.h`

