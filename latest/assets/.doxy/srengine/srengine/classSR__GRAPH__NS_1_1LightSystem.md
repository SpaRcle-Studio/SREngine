

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
|  std::array&lt; std::set&lt; [**ILightComponent**](classSR__GRAPH__NS_1_1ILightComponent.md) \* &gt;, [**SR\_UTILS\_NS::EnumTraits**](structSR__UTILS__NS_1_1EnumTraits.md)&lt; LightType &gt;::NumItems &gt; | [**m\_lights**](#variable-m_lights)  <br> |
|  RenderScenePtr | [**m\_renderScene**](#variable-m_renderscene)  <br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetDirectionalLightDirection**](#function-getdirectionallightdirection) () noexcept const<br> |
|   | [**LightSystem**](#function-lightsystem) (RenderScenePtr pRenderScene) <br> |
|  void | [**OnLightTransformChanged**](#function-onlighttransformchanged) ([**ILightComponent**](classSR__GRAPH__NS_1_1ILightComponent.md) \* pLightComponent) <br> |
|  void | [**Register**](#function-register) ([**ILightComponent**](classSR__GRAPH__NS_1_1ILightComponent.md) \* pLightComponent) <br> |
|  void | [**Remove**](#function-remove) ([**ILightComponent**](classSR__GRAPH__NS_1_1ILightComponent.md) \* pLightComponent) <br> |
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
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef RenderScenePtr 

```C++
using SR_GRAPH_NS::LightSystem::RenderScenePtr =  SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::RenderScene>;
```




<hr>
## Public Attributes Documentation




### variable m\_lights 

```C++
std::array<std::set<ILightComponent*>, SR_UTILS_NS::EnumTraits<LightType>::NumItems> SR_GRAPH_NS::LightSystem::m_lights;
```




<hr>



### variable m\_renderScene 

```C++
RenderScenePtr SR_GRAPH_NS::LightSystem::m_renderScene;
```




<hr>
## Public Functions Documentation




### function GetDirectionalLightDirection 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_GRAPH_NS::LightSystem::GetDirectionalLightDirection () noexcept const
```




<hr>



### function LightSystem 

```C++
explicit SR_GRAPH_NS::LightSystem::LightSystem (
    RenderScenePtr pRenderScene
) 
```




<hr>



### function OnLightTransformChanged 

```C++
void SR_GRAPH_NS::LightSystem::OnLightTransformChanged (
    ILightComponent * pLightComponent
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



### function ~LightSystem 

```C++
SR_GRAPH_NS::LightSystem::~LightSystem () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Lighting/LightSystem.h`

