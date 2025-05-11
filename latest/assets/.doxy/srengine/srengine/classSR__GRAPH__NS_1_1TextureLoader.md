

# Class SR\_GRAPH\_NS::TextureLoader



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**TextureLoader**](classSR__GRAPH__NS_1_1TextureLoader.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TextureLoader**](#function-textureloader-13) () = delete<br> |
|   | [**TextureLoader**](#function-textureloader-23) (const [**TextureLoader**](classSR__GRAPH__NS_1_1TextureLoader.md) &) = delete<br> |
|   | [**TextureLoader**](#function-textureloader-33) ([**TextureLoader**](classSR__GRAPH__NS_1_1TextureLoader.md) &&) = delete<br> |
|   | [**~TextureLoader**](#function-textureloader) () = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Free**](#function-free) (unsigned char \* data) <br> |
|  [**TextureData::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**Load**](#function-load) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  [**TextureData::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**LoadFromMemory**](#function-loadfrommemory) (const std::string & data, const [**Memory::TextureConfig**](structSR__GRAPH__NS_1_1Memory_1_1TextureConfig.md) & config) <br> |


























## Public Functions Documentation




### function TextureLoader [1/3]

```C++
SR_GRAPH_NS::TextureLoader::TextureLoader () = delete
```




<hr>



### function TextureLoader [2/3]

```C++
SR_GRAPH_NS::TextureLoader::TextureLoader (
    const TextureLoader &
) = delete
```




<hr>



### function TextureLoader [3/3]

```C++
SR_GRAPH_NS::TextureLoader::TextureLoader (
    TextureLoader &&
) = delete
```




<hr>



### function ~TextureLoader 

```C++
SR_GRAPH_NS::TextureLoader::~TextureLoader () = delete
```




<hr>
## Public Static Functions Documentation




### function Free 

```C++
static bool SR_GRAPH_NS::TextureLoader::Free (
    unsigned char * data
) 
```




<hr>



### function Load 

```C++
static TextureData::Ptr SR_GRAPH_NS::TextureLoader::Load (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function LoadFromMemory 

```C++
static TextureData::Ptr SR_GRAPH_NS::TextureLoader::LoadFromMemory (
    const std::string & data,
    const Memory::TextureConfig & config
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Loaders/TextureLoader.h`

