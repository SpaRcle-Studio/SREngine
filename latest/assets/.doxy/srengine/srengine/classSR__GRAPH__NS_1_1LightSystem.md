

# Class SR\_GRAPH\_NS::LightSystem



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**LightSystem**](classSR__GRAPH__NS_1_1LightSystem.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GRAPH\_NS::RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) &gt; | [**RenderScenePtr**](#typedef-rendersceneptr)  <br> |








## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::set&lt; [**AreaLight**](classSR__GRAPH__NS_1_1AreaLight.md) \* &gt; | [**m\_areaLights**](#variable-m_arealights)  <br> |
|  std::set&lt; [**DirectionalLight**](classSR__GRAPH__NS_1_1DirectionalLight.md) \* &gt; | [**m\_directionalLights**](#variable-m_directionallights)  <br> |
|  std::set&lt; [**PointLight**](classSR__GRAPH__NS_1_1PointLight.md) \* &gt; | [**m\_pointLights**](#variable-m_pointlights)  <br> |
|  std::set&lt; [**ProbeLight**](classSR__GRAPH__NS_1_1ProbeLight.md) \* &gt; | [**m\_probeLights**](#variable-m_probelights)  <br> |
|  RenderScenePtr | [**m\_renderScene**](#variable-m_renderscene)  <br> |
|  std::set&lt; [**SpotLight**](classSR__GRAPH__NS_1_1SpotLight.md) \* &gt; | [**m\_spotLights**](#variable-m_spotlights)  <br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD const SR\_MATH\_NS::FVector3 & | [**GetDirectionalLightPosition**](#function-getdirectionallightposition) () noexcept const<br> |
|   | [**LightSystem**](#function-lightsystem) (RenderScenePtr pRenderScene) <br> |
|  void | [**Register**](#function-register) ([**ILightComponent**](classSR__GRAPH__NS_1_1ILightComponent.md) \* pLightComponent) <br> |
|  void | [**Remove**](#function-remove) ([**ILightComponent**](classSR__GRAPH__NS_1_1ILightComponent.md) \* pLightComponent) <br> |
|  void | [**SetDirectionalLightPosition**](#function-setdirectionallightposition) (const SR\_MATH\_NS::FVector3 & position) noexcept<br> |
|   | [**~LightSystem**](#function-lightsystem) () override<br> |


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
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Types Documentation




### typedef RenderScenePtr 

```C++
using SR_GRAPH_NS::LightSystem::RenderScenePtr =  SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::RenderScene>;
```




<hr>
## Public Attributes Documentation




### variable m\_areaLights 

```C++
std::set<AreaLight*> SR_GRAPH_NS::LightSystem::m_areaLights;
```




<hr>



### variable m\_directionalLights 

```C++
std::set<DirectionalLight*> SR_GRAPH_NS::LightSystem::m_directionalLights;
```




<hr>



### variable m\_pointLights 

```C++
std::set<PointLight*> SR_GRAPH_NS::LightSystem::m_pointLights;
```




<hr>



### variable m\_probeLights 

```C++
std::set<ProbeLight*> SR_GRAPH_NS::LightSystem::m_probeLights;
```




<hr>



### variable m\_renderScene 

```C++
RenderScenePtr SR_GRAPH_NS::LightSystem::m_renderScene;
```




<hr>



### variable m\_spotLights 

```C++
std::set<SpotLight*> SR_GRAPH_NS::LightSystem::m_spotLights;
```




<hr>
## Public Functions Documentation




### function GetDirectionalLightPosition 

```C++
inline SR_NODISCARD const SR_MATH_NS::FVector3 & SR_GRAPH_NS::LightSystem::GetDirectionalLightPosition () noexcept const
```




<hr>



### function LightSystem 

```C++
explicit SR_GRAPH_NS::LightSystem::LightSystem (
    RenderScenePtr pRenderScene
) 
```




<hr>



### function Register 

```C++
void SR_GRAPH_NS::LightSystem::Register (
    ILightComponent * pLightComponent
) 
```




<hr>



### function Remove 

```C++
void SR_GRAPH_NS::LightSystem::Remove (
    ILightComponent * pLightComponent
) 
```




<hr>



### function SetDirectionalLightPosition 

```C++
void SR_GRAPH_NS::LightSystem::SetDirectionalLightPosition (
    const SR_MATH_NS::FVector3 & position
) noexcept
```




<hr>



### function ~LightSystem 

```C++
SR_GRAPH_NS::LightSystem::~LightSystem () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Lighting/LightSystem.h`

