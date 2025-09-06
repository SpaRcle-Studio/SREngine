

# Class SR\_GRAPH\_NS::ShaderCache



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**ShaderCache**](classSR__GRAPH__NS_1_1ShaderCache.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md),  [SR\_UTILS\_NS::NonMovable](classSR__UTILS__NS_1_1NonMovable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ShaderCache**](#function-shadercache) () = delete<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Functions inherited from SR_UTILS_NS::NonMovable

See [SR\_UTILS\_NS::NonMovable](classSR__UTILS__NS_1_1NonMovable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonMovable**](classSR__UTILS__NS_1_1NonMovable.md#function-nonmovable-22) ([**NonMovable**](classSR__UTILS__NS_1_1NonMovable.md) &&) = delete<br> |
| virtual [**NonMovable**](classSR__UTILS__NS_1_1NonMovable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonMovable.md#function-operator) ([**NonMovable**](classSR__UTILS__NS_1_1NonMovable.md) &&) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**LoadShaderFromCache**](#function-loadshaderfromcache) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & cachePath, [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) <br> |
|  void | [**SaveShaderToCache**](#function-saveshadertocache) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & cachePath, const [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) <br> |




































































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |


## Protected Functions inherited from SR_UTILS_NS::NonMovable

See [SR\_UTILS\_NS::NonMovable](classSR__UTILS__NS_1_1NonMovable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonMovable**](classSR__UTILS__NS_1_1NonMovable.md#function-nonmovable-12) () <br> |
| virtual  | [**~NonMovable**](classSR__UTILS__NS_1_1NonMovable.md#function-nonmovable) () <br> |








## Public Functions Documentation




### function ShaderCache 

```C++
SR_GRAPH_NS::ShaderCache::ShaderCache () = delete
```




<hr>
## Public Static Functions Documentation




### function LoadShaderFromCache 

```C++
static bool SR_GRAPH_NS::ShaderCache::LoadShaderFromCache (
    const SR_UTILS_NS::Path & cachePath,
    SR_GTYPES_NS::Shader * pShader
) 
```




<hr>



### function SaveShaderToCache 

```C++
static void SR_GRAPH_NS::ShaderCache::SaveShaderToCache (
    const SR_UTILS_NS::Path & cachePath,
    const SR_GTYPES_NS::Shader * pShader
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/Cache.h`

