

# Class SR\_GRAPH\_NS::ISamplersPass



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**ISamplersPass**](classSR__GRAPH__NS_1_1ISamplersPass.md)










Inherited by the following classes: [SR\_GRAPH\_NS::MeshDrawerPass](classSR__GRAPH__NS_1_1MeshDrawerPass.md),  [SR\_GRAPH\_NS::PostProcessPass](classSR__GRAPH__NS_1_1PostProcessPass.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**HasSamplers**](#function-hassamplers) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsSamplersDirty**](#function-issamplersdirty) () noexcept const<br> |
|  void | [**LoadSamplersPass**](#function-loadsamplerspass) (const SR\_XML\_NS::Node & passNode) <br> |
| virtual void | [**UseSamplers**](#function-usesamplers) ([**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) info) <br> |
| virtual  | [**~ISamplersPass**](#function-isamplerspass) () <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**MarkSamplersDirty**](#function-marksamplersdirty) () <br> |
| virtual void | [**OnSamplersChanged**](#function-onsamplerschanged) () <br> |
|  void | [**PrepareSamplers**](#function-preparesamplers) () <br> |
|  void | [**SetISamplerRenderTechnique**](#function-setisamplerrendertechnique) ([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* pTechnique) <br> |




## Public Functions Documentation




### function HasSamplers 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::ISamplersPass::HasSamplers () noexcept const
```




<hr>



### function IsSamplersDirty 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::ISamplersPass::IsSamplersDirty () noexcept const
```




<hr>



### function LoadSamplersPass 

```C++
void SR_GRAPH_NS::ISamplersPass::LoadSamplersPass (
    const SR_XML_NS::Node & passNode
) 
```




<hr>



### function UseSamplers 

```C++
virtual void SR_GRAPH_NS::ISamplersPass::UseSamplers (
    ShaderUseInfo info
) 
```




<hr>



### function ~ISamplersPass 

```C++
virtual SR_GRAPH_NS::ISamplersPass::~ISamplersPass () 
```




<hr>
## Protected Functions Documentation




### function MarkSamplersDirty 

```C++
inline void SR_GRAPH_NS::ISamplersPass::MarkSamplersDirty () 
```




<hr>



### function OnSamplersChanged 

```C++
inline virtual void SR_GRAPH_NS::ISamplersPass::OnSamplersChanged () 
```




<hr>



### function PrepareSamplers 

```C++
void SR_GRAPH_NS::ISamplersPass::PrepareSamplers () 
```




<hr>



### function SetISamplerRenderTechnique 

```C++
inline void SR_GRAPH_NS::ISamplersPass::SetISamplerRenderTechnique (
    IRenderTechnique * pTechnique
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pass/ISamplersPass.h`

