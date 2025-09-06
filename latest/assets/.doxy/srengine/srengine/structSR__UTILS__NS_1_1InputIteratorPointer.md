

# Struct SR\_UTILS\_NS::InputIteratorPointer

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**InputIteratorPointer**](structSR__UTILS__NS_1_1InputIteratorPointer.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef T \* | [**Pointer**](#typedef-pointer)  <br> |
| typedef T & | [**Reference**](#typedef-reference)  <br> |
| typedef T | [**ValueType**](#typedef-valuetype)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**InputIteratorPointer**](#function-inputiteratorpointer) (ValueType && value) noexcept<br>_NOLINT(google-explicit-constructor)_  |
|  SR\_NODISCARD constexpr Reference | [**operator\***](#function-operator) () noexcept<br> |
|  SR\_NODISCARD constexpr Pointer | [**operator-&gt;**](#function-operator-) () noexcept<br> |




























## Public Types Documentation




### typedef Pointer 

```C++
using SR_UTILS_NS::InputIteratorPointer< T >::Pointer =  T*;
```




<hr>



### typedef Reference 

```C++
using SR_UTILS_NS::InputIteratorPointer< T >::Reference =  T&;
```




<hr>



### typedef ValueType 

```C++
using SR_UTILS_NS::InputIteratorPointer< T >::ValueType =  T;
```




<hr>
## Public Functions Documentation




### function InputIteratorPointer 

_NOLINT(google-explicit-constructor)_ 
```C++
inline constexpr SR_UTILS_NS::InputIteratorPointer::InputIteratorPointer (
    ValueType && value
) noexcept
```




<hr>



### function operator\* 

```C++
inline SR_NODISCARD constexpr Reference SR_UTILS_NS::InputIteratorPointer::operator* () noexcept
```




<hr>



### function operator-&gt; 

```C++
inline SR_NODISCARD constexpr Pointer SR_UTILS_NS::InputIteratorPointer::operator-> () noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/stdInclude.h`

