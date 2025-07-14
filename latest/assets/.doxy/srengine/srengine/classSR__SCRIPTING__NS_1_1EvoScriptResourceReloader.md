

# Class SR\_SCRIPTING\_NS::EvoScriptResourceReloader



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**EvoScriptResourceReloader**](classSR__SCRIPTING__NS_1_1EvoScriptResourceReloader.md)








Inherits the following classes: [SR\_UTILS\_NS::IResourceReloader](classSR__UTILS__NS_1_1IResourceReloader.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**Reload**](#function-reload) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, [**SR\_UTILS\_NS::ResourceInfo**](structSR__UTILS__NS_1_1ResourceInfo.md) \* pResourceInfo) override<br> |


## Public Functions inherited from SR_UTILS_NS::IResourceReloader

See [SR\_UTILS\_NS::IResourceReloader](classSR__UTILS__NS_1_1IResourceReloader.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**IsResourceSuitableForReload**](classSR__UTILS__NS_1_1IResourceReloader.md#function-isresourcesuitableforreload) (const IResource::Ptr & pResource) const<br> |
| virtual SR\_NODISCARD bool | [**Reload**](classSR__UTILS__NS_1_1IResourceReloader.md#function-reload) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, [**ResourceInfo**](structSR__UTILS__NS_1_1ResourceInfo.md) \* pResourceInfo) = 0<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






















## Protected Attributes inherited from SR_UTILS_NS::IResourceReloader

See [SR\_UTILS\_NS::IResourceReloader](classSR__UTILS__NS_1_1IResourceReloader.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1IResourceReloader.md#variable-m_mutex)  <br> |


















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function Reload 

```C++
virtual SR_NODISCARD bool SR_SCRIPTING_NS::EvoScriptResourceReloader::Reload (
    const SR_UTILS_NS::Path & path,
    SR_UTILS_NS::ResourceInfo * pResourceInfo
) override
```



Implements [*SR\_UTILS\_NS::IResourceReloader::Reload*](classSR__UTILS__NS_1_1IResourceReloader.md#function-reload)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Scripting/inc/Scripting/Old/Impl/EvoScriptResourceReloader.h`

