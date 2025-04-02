

# Class SR\_UTILS\_NS::EntityIdList



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**EntityIdList**](classSR__UTILS__NS_1_1EntityIdList.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::optional&lt; [**EntityIdList**](classSR__UTILS__NS_1_1EntityIdList.md) &gt; | [**Optional**](#typedef-optional)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Add**](#function-add-13) (EntityId id) <br> |
|  void | [**Add**](#function-add-23) (const [**EntityIdList**](classSR__UTILS__NS_1_1EntityIdList.md) & list) <br> |
|  void | [**Add**](#function-add-33) (const std::vector&lt; EntityId &gt; & list) <br> |
|  void | [**Clear**](#function-clear) () <br> |
|   | [**EntityIdList**](#function-entityidlist-12) (EntityController::Ptr pController) <br> |
|   | [**EntityIdList**](#function-entityidlist-22) ([**EntityIdList**](classSR__UTILS__NS_1_1EntityIdList.md) && other) noexcept<br> |
|  SR\_NODISCARD bool | [**IsReserved**](#function-isreserved) () const<br> |
|  void | [**Reserve**](#function-reserve) (const uint64\_t size) <br> |
|  void | [**ReserveIds**](#function-reserveids) () <br> |
|  void | [**UnReserveIds**](#function-unreserveids) () <br> |
|  [**EntityIdList**](classSR__UTILS__NS_1_1EntityIdList.md) & | [**operator=**](#function-operator) ([**EntityIdList**](classSR__UTILS__NS_1_1EntityIdList.md) && other) noexcept<br> |
|   | [**~EntityIdList**](#function-entityidlist) () override<br> |


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
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Types Documentation




### typedef Optional 

```C++
using SR_UTILS_NS::EntityIdList::Optional =  std::optional<EntityIdList>;
```




<hr>
## Public Functions Documentation




### function Add [1/3]

```C++
void SR_UTILS_NS::EntityIdList::Add (
    EntityId id
) 
```




<hr>



### function Add [2/3]

```C++
void SR_UTILS_NS::EntityIdList::Add (
    const EntityIdList & list
) 
```




<hr>



### function Add [3/3]

```C++
void SR_UTILS_NS::EntityIdList::Add (
    const std::vector< EntityId > & list
) 
```




<hr>



### function Clear 

```C++
void SR_UTILS_NS::EntityIdList::Clear () 
```




<hr>



### function EntityIdList [1/2]

```C++
inline explicit SR_UTILS_NS::EntityIdList::EntityIdList (
    EntityController::Ptr pController
) 
```




<hr>



### function EntityIdList [2/2]

```C++
inline SR_UTILS_NS::EntityIdList::EntityIdList (
    EntityIdList && other
) noexcept
```




<hr>



### function IsReserved 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::EntityIdList::IsReserved () const
```




<hr>



### function Reserve 

```C++
inline void SR_UTILS_NS::EntityIdList::Reserve (
    const uint64_t size
) 
```




<hr>



### function ReserveIds 

```C++
void SR_UTILS_NS::EntityIdList::ReserveIds () 
```




<hr>



### function UnReserveIds 

```C++
void SR_UTILS_NS::EntityIdList::UnReserveIds () 
```




<hr>



### function operator= 

```C++
inline EntityIdList & SR_UTILS_NS::EntityIdList::operator= (
    EntityIdList && other
) noexcept
```




<hr>



### function ~EntityIdList 

```C++
inline SR_UTILS_NS::EntityIdList::~EntityIdList () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/ECS/EntityController.h`

