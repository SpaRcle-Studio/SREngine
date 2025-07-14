

# Class SR\_GTYPES\_NS::RenderTexture



[**ClassList**](annotated.md) **>** [**SR\_GTYPES\_NS**](namespaceSR__GTYPES__NS.md) **>** [**RenderTexture**](classSR__GTYPES__NS_1_1RenderTexture.md)








Inherits the following classes: SR_UTILS_NS::Settings














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**RenderTexture**](classSR__GTYPES__NS_1_1RenderTexture.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RenderTexture**](#function-rendertexture) () <br> |
|   | [**~RenderTexture**](#function-rendertexture) () override<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  RenderTexture::Ptr | [**Load**](#function-load) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |






















## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**ClearSettings**](#function-clearsettings) () override<br> |
|  bool | [**LoadSettings**](#function-loadsettings) (const SR\_XML\_NS::Node & node) override<br> |




## Public Types Documentation




### typedef Ptr 

```C++
using SR_GTYPES_NS::RenderTexture::Ptr =  SR_HTYPES_NS::SharedPtr<RenderTexture>;
```




<hr>
## Public Functions Documentation




### function RenderTexture 

```C++
SR_GTYPES_NS::RenderTexture::RenderTexture () 
```




<hr>



### function ~RenderTexture 

```C++
SR_GTYPES_NS::RenderTexture::~RenderTexture () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static RenderTexture::Ptr SR_GTYPES_NS::RenderTexture::Load (
    const SR_UTILS_NS::Path & path
) 
```




<hr>
## Protected Functions Documentation




### function ClearSettings 

```C++
void SR_GTYPES_NS::RenderTexture::ClearSettings () override
```




<hr>



### function LoadSettings 

```C++
bool SR_GTYPES_NS::RenderTexture::LoadSettings (
    const SR_XML_NS::Node & node
) override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Types/RenderTexture.h`

