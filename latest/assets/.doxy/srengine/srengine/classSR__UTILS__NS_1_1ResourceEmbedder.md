

# Class SR\_UTILS\_NS::ResourceEmbedder



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ResourceEmbedder**](classSR__UTILS__NS_1_1ResourceEmbedder.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**ExportAllResources**](#function-exportallresources-12) () <br> |
|  bool | [**ExportAllResources**](#function-exportallresources-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & newDirectory) <br> |
|  bool | [**ExportToFile**](#function-exporttofile-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  bool | [**RegisterResource**](#function-registerresource) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**ExportToFile**](#function-exporttofile-12) (std::string\_view path, const Resource & resource, const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & newDirectory) <br> |
|  bool | [**ExportToMemory**](#function-exporttomemory) (std::string\_view data) <br> |
|  [**ResourceEmbedder**](classSR__UTILS__NS_1_1ResourceEmbedder.md) & | [**Instance**](#function-instance) () <br> |


























## Public Functions Documentation




### function ExportAllResources [1/2]

```C++
bool SR_UTILS_NS::ResourceEmbedder::ExportAllResources () 
```




<hr>



### function ExportAllResources [2/2]

```C++
bool SR_UTILS_NS::ResourceEmbedder::ExportAllResources (
    const SR_UTILS_NS::Path & newDirectory
) 
```




<hr>



### function ExportToFile [2/2]

```C++
bool SR_UTILS_NS::ResourceEmbedder::ExportToFile (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function RegisterResource 

```C++
template<class T>
inline bool SR_UTILS_NS::ResourceEmbedder::RegisterResource () 
```




<hr>
## Public Static Functions Documentation




### function ExportToFile [1/2]

```C++
static bool SR_UTILS_NS::ResourceEmbedder::ExportToFile (
    std::string_view path,
    const Resource & resource,
    const SR_UTILS_NS::Path & newDirectory
) 
```




<hr>



### function ExportToMemory 

```C++
static bool SR_UTILS_NS::ResourceEmbedder::ExportToMemory (
    std::string_view data
) 
```




<hr>



### function Instance 

```C++
static inline ResourceEmbedder & SR_UTILS_NS::ResourceEmbedder::Instance () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Resources/ResourceEmbedder.h`

