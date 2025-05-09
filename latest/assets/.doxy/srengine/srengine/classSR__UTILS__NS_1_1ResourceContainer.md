

# Class SR\_UTILS\_NS::ResourceContainer



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_GRAPH\_NS::BasePass](classSR__GRAPH__NS_1_1BasePass.md),  [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddDependency**](#function-adddependency) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer) <br> |
|  SR\_NODISCARD const std::unordered\_set&lt; [**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* &gt; & | [**GetContainerParents**](#function-getcontainerparents) () const<br> |
|  void | [**RemoveDependency**](#function-removedependency) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**OnResourceUpdated**](#function-onresourceupdated) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer, int32\_t depth) <br> |
|  void | [**UpdateResources**](#function-updateresources) (int32\_t depth=0) <br> |
|   | [**~ResourceContainer**](#function-resourcecontainer) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function AddDependency 

```C++
void SR_UTILS_NS::ResourceContainer::AddDependency (
    ResourceContainer * pContainer
) 
```




<hr>



### function GetContainerParents 

```C++
inline SR_NODISCARD const std::unordered_set< ResourceContainer * > & SR_UTILS_NS::ResourceContainer::GetContainerParents () const
```




<hr>



### function RemoveDependency 

```C++
void SR_UTILS_NS::ResourceContainer::RemoveDependency (
    ResourceContainer * pContainer
) 
```




<hr>
## Protected Functions Documentation




### function OnResourceUpdated 

```C++
virtual void SR_UTILS_NS::ResourceContainer::OnResourceUpdated (
    ResourceContainer * pContainer,
    int32_t depth
) 
```




<hr>



### function UpdateResources 

```C++
void SR_UTILS_NS::ResourceContainer::UpdateResources (
    int32_t depth=0
) 
```




<hr>



### function ~ResourceContainer 

```C++
SR_UTILS_NS::ResourceContainer::~ResourceContainer () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Resources/ResourceContainer.h`

