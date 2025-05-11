

# Struct SR\_HTYPES\_NS::SharedPtrDynamicData



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**deallocated**](#variable-deallocated)   = `false`<br> |
|  SR\_UTILS\_NS::SharedPtrPolicy | [**policy**](#variable-policy)   = `SR\_UTILS\_NS::SharedPtrPolicy::Automatic`<br> |
|  uint16\_t | [**strongCount**](#variable-strongcount)   = `0`<br> |
|  bool | [**valid**](#variable-valid)   = `false`<br> |
|  uint16\_t | [**weakCount**](#variable-weakcount)   = `0`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**DecrementStrong**](#function-decrementstrong) () <br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetDebugTrace**](#function-getdebugtrace) () const<br> |
|  SR\_NODISCARD uint16\_t | [**GetStrongCount**](#function-getstrongcount) () const<br> |
|  void | [**IncrementStrong**](#function-incrementstrong) () <br> |
|   | [**SharedPtrDynamicData**](#function-sharedptrdynamicdata) (uint16\_t strongCount, uint16\_t weakCount, bool valid, SR\_UTILS\_NS::SharedPtrPolicy policy) <br> |
|   | [**~SharedPtrDynamicData**](#function-sharedptrdynamicdata) () <br> |




























## Public Attributes Documentation




### variable deallocated 

```C++
bool SR_HTYPES_NS::SharedPtrDynamicData::deallocated;
```




<hr>



### variable policy 

```C++
SR_UTILS_NS::SharedPtrPolicy SR_HTYPES_NS::SharedPtrDynamicData::policy;
```




<hr>



### variable strongCount 

```C++
uint16_t SR_HTYPES_NS::SharedPtrDynamicData::strongCount;
```




<hr>



### variable valid 

```C++
bool SR_HTYPES_NS::SharedPtrDynamicData::valid;
```




<hr>



### variable weakCount 

```C++
uint16_t SR_HTYPES_NS::SharedPtrDynamicData::weakCount;
```




<hr>
## Public Functions Documentation




### function DecrementStrong 

```C++
inline void SR_HTYPES_NS::SharedPtrDynamicData::DecrementStrong () 
```




<hr>



### function GetDebugTrace 

```C++
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_HTYPES_NS::SharedPtrDynamicData::GetDebugTrace () const
```




<hr>



### function GetStrongCount 

```C++
inline SR_NODISCARD uint16_t SR_HTYPES_NS::SharedPtrDynamicData::GetStrongCount () const
```




<hr>



### function IncrementStrong 

```C++
inline void SR_HTYPES_NS::SharedPtrDynamicData::IncrementStrong () 
```




<hr>



### function SharedPtrDynamicData 

```C++
inline SR_HTYPES_NS::SharedPtrDynamicData::SharedPtrDynamicData (
    uint16_t strongCount,
    uint16_t weakCount,
    bool valid,
    SR_UTILS_NS::SharedPtrPolicy policy
) 
```




<hr>



### function ~SharedPtrDynamicData 

```C++
inline SR_HTYPES_NS::SharedPtrDynamicData::~SharedPtrDynamicData () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/SharedPtr.h`

