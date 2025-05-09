

# Class SR\_UTILS\_NS::ResourcesHolder



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ResourcesHolder**](classSR__UTILS__NS_1_1ResourcesHolder.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Add**](#function-add) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|  void | [**Release**](#function-release) () <br> |
|  bool | [**Remove**](#function-remove) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|   | [**~ResourcesHolder**](#function-resourcesholder) () override<br> |


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
bool SR_UTILS_NS::ResourcesHolder::Add (
    IResource * pResource
) 
```




<hr>



### function Release 

```C++
void SR_UTILS_NS::ResourcesHolder::Release () 
```




<hr>



### function Remove 

```C++
bool SR_UTILS_NS::ResourcesHolder::Remove (
    IResource * pResource
) 
```




<hr>



### function ~ResourcesHolder 

```C++
SR_UTILS_NS::ResourcesHolder::~ResourcesHolder () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Resources/ResourcesHolder.h`

