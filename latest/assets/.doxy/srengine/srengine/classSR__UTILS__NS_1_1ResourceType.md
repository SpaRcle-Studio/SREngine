

# Class SR\_UTILS\_NS::ResourceType



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ResourceType**](classSR__UTILS__NS_1_1ResourceType.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Add**](#function-add) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|  void | [**CollectUnused**](#function-collectunused) () <br>_ставит все неиспользуемые ресурсы на очередь уничтожения_  |
|  SR\_NODISCARD [**IResource**](classSR__UTILS__NS_1_1IResource.md) \* | [**Find**](#function-find) (const ResourceId & id) <br> |
|  SR\_NODISCARD const CopiesMap & | [**GetCopiesRef**](#function-getcopiesref) () const<br> |
|  SR\_NODISCARD Info & | [**GetInfo**](#function-getinfo) () <br> |
|  SR\_NODISCARD std::pair&lt; ResourcePath, ResourceInfo::HardPtr &gt; | [**GetInfoByIndex**](#function-getinfobyindex) (uint64\_t index) <br> |
|  SR\_NODISCARD const std::string & | [**GetName**](#function-getname) () const<br> |
|  SR\_NODISCARD [**IResourceReloader**](classSR__UTILS__NS_1_1IResourceReloader.md) \* | [**GetReloader**](#function-getreloader) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsLast**](#function-islast) (const ResourceId & id) <br> |
|  void | [**Remove**](#function-remove) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|   | [**ResourceType**](#function-resourcetype) (std::string name) <br> |
|  void | [**SetReloader**](#function-setreloader) ([**IResourceReloader**](classSR__UTILS__NS_1_1IResourceReloader.md) \* pReloader) <br> |
|   | [**~ResourceType**](#function-resourcetype) () override<br> |


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




### function Add 

```C++
void SR_UTILS_NS::ResourceType::Add (
    IResource * pResource
) 
```




<hr>



### function CollectUnused 

_ставит все неиспользуемые ресурсы на очередь уничтожения_ 
```C++
void SR_UTILS_NS::ResourceType::CollectUnused () 
```




<hr>



### function Find 

```C++
SR_NODISCARD IResource * SR_UTILS_NS::ResourceType::Find (
    const ResourceId & id
) 
```




<hr>



### function GetCopiesRef 

```C++
SR_NODISCARD const CopiesMap & SR_UTILS_NS::ResourceType::GetCopiesRef () const
```




<hr>



### function GetInfo 

```C++
SR_NODISCARD Info & SR_UTILS_NS::ResourceType::GetInfo () 
```




<hr>



### function GetInfoByIndex 

```C++
SR_NODISCARD std::pair< ResourcePath, ResourceInfo::HardPtr > SR_UTILS_NS::ResourceType::GetInfoByIndex (
    uint64_t index
) 
```




<hr>



### function GetName 

```C++
inline SR_NODISCARD const std::string & SR_UTILS_NS::ResourceType::GetName () const
```




<hr>



### function GetReloader 

```C++
inline SR_NODISCARD IResourceReloader * SR_UTILS_NS::ResourceType::GetReloader () noexcept const
```




<hr>



### function IsLast 

```C++
SR_NODISCARD bool SR_UTILS_NS::ResourceType::IsLast (
    const ResourceId & id
) 
```




<hr>



### function Remove 

```C++
void SR_UTILS_NS::ResourceType::Remove (
    IResource * pResource
) 
```




<hr>



### function ResourceType 

```C++
inline explicit SR_UTILS_NS::ResourceType::ResourceType (
    std::string name
) 
```




<hr>



### function SetReloader 

```C++
void SR_UTILS_NS::ResourceType::SetReloader (
    IResourceReloader * pReloader
) 
```




<hr>



### function ~ResourceType 

```C++
SR_UTILS_NS::ResourceType::~ResourceType () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Resources/ResourceInfo.h`

