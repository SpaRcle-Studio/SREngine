

# Class SR\_HTYPES\_NS::SharedPtrDynamicDataCounter



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**SharedPtrDynamicDataCounter**](classSR__HTYPES__NS_1_1SharedPtrDynamicDataCounter.md)








Inherits the following classes: Singleton< SharedPtrDynamicDataCounter >


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Decrement**](#function-decrement) ([**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* pData) <br> |
|  SR\_NODISCARD uint64\_t | [**GetCount**](#function-getcount) () const<br> |
|  SR\_NODISCARD const std::unordered\_set&lt; [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* &gt; & | [**GetData**](#function-getdata) () const<br> |
|  void | [**Increment**](#function-increment) ([**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* pData) <br> |
|  SR\_NODISCARD bool | [**IsSingletonCanBeDestroyed**](#function-issingletoncanbedestroyed) () override const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED bool | [**CheckMemoryLeaks**](#function-checkmemoryleaks) () <br> |


























## Public Functions Documentation




### function Decrement 

```C++
inline void SR_HTYPES_NS::SharedPtrDynamicDataCounter::Decrement (
    SharedPtrDynamicData * pData
) 
```




<hr>



### function GetCount 

```C++
inline SR_NODISCARD uint64_t SR_HTYPES_NS::SharedPtrDynamicDataCounter::GetCount () const
```




<hr>



### function GetData 

```C++
inline SR_NODISCARD const std::unordered_set< SharedPtrDynamicData * > & SR_HTYPES_NS::SharedPtrDynamicDataCounter::GetData () const
```




<hr>



### function Increment 

```C++
inline void SR_HTYPES_NS::SharedPtrDynamicDataCounter::Increment (
    SharedPtrDynamicData * pData
) 
```




<hr>



### function IsSingletonCanBeDestroyed 

```C++
inline SR_NODISCARD bool SR_HTYPES_NS::SharedPtrDynamicDataCounter::IsSingletonCanBeDestroyed () override const
```




<hr>
## Public Static Functions Documentation




### function CheckMemoryLeaks 

```C++
static SR_MAYBE_UNUSED bool SR_HTYPES_NS::SharedPtrDynamicDataCounter::CheckMemoryLeaks () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/SharedPtr.h`

