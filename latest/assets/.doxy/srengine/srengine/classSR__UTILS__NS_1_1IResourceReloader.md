

# Class SR\_UTILS\_NS::IResourceReloader



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**IResourceReloader**](classSR__UTILS__NS_1_1IResourceReloader.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_CORE\_NS::GraphicsResourceReloader](classSR__CORE__NS_1_1GraphicsResourceReloader.md),  [SR\_SCRIPTING\_NS::EvoScriptResourceReloader](classSR__SCRIPTING__NS_1_1EvoScriptResourceReloader.md),  [SR\_UTILS\_NS::DefaultResourceReloader](classSR__UTILS__NS_1_1DefaultResourceReloader.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**IsResourceSuitableForReload**](#function-isresourcesuitableforreload) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) const<br> |
| virtual SR\_NODISCARD bool | [**Reload**](#function-reload) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, [**ResourceInfo**](structSR__UTILS__NS_1_1ResourceInfo.md) \* pResourceInfo) = 0<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](#variable-m_mutex)  <br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function IsResourceSuitableForReload 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IResourceReloader::IsResourceSuitableForReload (
    IResource * pResource
) const
```




<hr>



### function Reload 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IResourceReloader::Reload (
    const SR_UTILS_NS::Path & path,
    ResourceInfo * pResourceInfo
) = 0
```




<hr>
## Protected Attributes Documentation




### variable m\_mutex 

```C++
std::recursive_mutex SR_UTILS_NS::IResourceReloader::m_mutex;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Resources/IResourceReloader.h`

