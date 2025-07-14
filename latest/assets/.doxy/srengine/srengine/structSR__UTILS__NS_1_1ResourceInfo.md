

# Struct SR\_UTILS\_NS::ResourceInfo



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ResourceInfo**](structSR__UTILS__NS_1_1ResourceInfo.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::shared\_ptr&lt; [**ResourceInfo**](structSR__UTILS__NS_1_1ResourceInfo.md) &gt; | [**HardPtr**](#typedef-hardptr)  <br> |
| typedef std::weak\_ptr&lt; [**ResourceInfo**](structSR__UTILS__NS_1_1ResourceInfo.md) &gt; | [**WeakPtr**](#typedef-weakptr)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  ResourcesSet | [**m\_loaded**](#variable-m_loaded)  <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**m\_path**](#variable-m_path)  <br>_путь ресурса_  |
|  uint64\_t | [**m\_resourceHash**](#variable-m_resourcehash)   = `0`<br>_текущий хеш самого ресурса (параметры и тд, не файл!)_  |
|  [**ResourceType**](classSR__UTILS__NS_1_1ResourceType.md) \* | [**m\_resourceType**](#variable-m_resourcetype)   = `nullptr`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD IResource::Ptr | [**GetFirstResource**](#function-getfirstresource) () const<br> |
|  SR\_NODISCARD [**IResourceReloader**](classSR__UTILS__NS_1_1IResourceReloader.md) \* | [**GetReloader**](#function-getreloader) () const<br> |
|  SR\_NODISCARD IResource::Ptr | [**GetResource**](#function-getresource) () const<br> |
|   | [**ResourceInfo**](#function-resourceinfo) (uint64\_t resourceHash, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) path, [**ResourceType**](classSR__UTILS__NS_1_1ResourceType.md) \* pResourceType) <br> |




























## Public Types Documentation




### typedef HardPtr 

```C++
using SR_UTILS_NS::ResourceInfo::HardPtr =  std::shared_ptr<ResourceInfo>;
```




<hr>



### typedef WeakPtr 

```C++
using SR_UTILS_NS::ResourceInfo::WeakPtr =  std::weak_ptr<ResourceInfo>;
```




<hr>
## Public Attributes Documentation




### variable m\_loaded 

```C++
ResourcesSet SR_UTILS_NS::ResourceInfo::m_loaded;
```




<hr>



### variable m\_path 

_путь ресурса_ 
```C++
SR_UTILS_NS::StringAtom SR_UTILS_NS::ResourceInfo::m_path;
```




<hr>



### variable m\_resourceHash 

_текущий хеш самого ресурса (параметры и тд, не файл!)_ 
```C++
uint64_t SR_UTILS_NS::ResourceInfo::m_resourceHash;
```




<hr>



### variable m\_resourceType 

```C++
ResourceType* SR_UTILS_NS::ResourceInfo::m_resourceType;
```




<hr>
## Public Functions Documentation




### function GetFirstResource 

```C++
SR_NODISCARD IResource::Ptr SR_UTILS_NS::ResourceInfo::GetFirstResource () const
```




<hr>



### function GetReloader 

```C++
SR_NODISCARD IResourceReloader * SR_UTILS_NS::ResourceInfo::GetReloader () const
```




<hr>



### function GetResource 

```C++
SR_NODISCARD IResource::Ptr SR_UTILS_NS::ResourceInfo::GetResource () const
```




<hr>



### function ResourceInfo 

```C++
inline SR_UTILS_NS::ResourceInfo::ResourceInfo (
    uint64_t resourceHash,
    SR_UTILS_NS::StringAtom path,
    ResourceType * pResourceType
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Resources/ResourceInfo.h`

