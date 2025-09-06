

# Class SR\_SRSL\_NS::SRSLShaderCache



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLShaderCache**](classSR__SRSL__NS_1_1SRSLShaderCache.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md),  [SR\_UTILS\_NS::NonMovable](classSR__UTILS__NS_1_1NonMovable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SRSLShaderCache**](#function-srslshadercache) () = delete<br> |


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
|  bool | [**LoadShaderFromCache**](#function-loadshaderfromcache) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & cachePath, [**SR\_SRSL\_NS::SRSLShader**](classSR__SRSL__NS_1_1SRSLShader.md) \* pShader) <br> |
|  void | [**SaveShaderToCache**](#function-saveshadertocache) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & cachePath, const [**SR\_SRSL\_NS::SRSLShader**](classSR__SRSL__NS_1_1SRSLShader.md) \* pShader) <br> |




































































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




### function SRSLShaderCache 

```C++
SR_SRSL_NS::SRSLShaderCache::SRSLShaderCache () = delete
```




<hr>
## Public Static Functions Documentation




### function LoadShaderFromCache 

```C++
static bool SR_SRSL_NS::SRSLShaderCache::LoadShaderFromCache (
    const SR_UTILS_NS::Path & cachePath,
    SR_SRSL_NS::SRSLShader * pShader
) 
```




<hr>



### function SaveShaderToCache 

```C++
static void SR_SRSL_NS::SRSLShaderCache::SaveShaderToCache (
    const SR_UTILS_NS::Path & cachePath,
    const SR_SRSL_NS::SRSLShader * pShader
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/Cache.h`

