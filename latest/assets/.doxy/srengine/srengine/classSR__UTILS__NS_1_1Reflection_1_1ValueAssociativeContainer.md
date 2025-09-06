

# Class SR\_UTILS\_NS::Reflection::ValueAssociativeContainer



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Reflection**](namespaceSR__UTILS__NS_1_1Reflection.md) **>** [**ValueAssociativeContainer**](classSR__UTILS__NS_1_1Reflection_1_1ValueAssociativeContainer.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Clear**](#function-clear) () <br> |
|  SR\_NODISCARD bool | [**Empty**](#function-empty) () const<br> |
|  void | [**Erase**](#function-erase) (const [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & key) <br> |
|  SR\_NODISCARD [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**GetKeyType**](#function-getkeytype) () const<br> |
|  SR\_NODISCARD [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**GetMappedType**](#function-getmappedtype) () const<br> |
|  SR\_NODISCARD [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**GetValueType**](#function-getvaluetype) () const<br> |
|  bool | [**Insert**](#function-insert) (const [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & key, const [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & value) <br> |
|  void | [**Reserve**](#function-reserve) (uint64\_t size) <br> |
|  SR\_NODISCARD uint64\_t | [**Size**](#function-size) () const<br> |
|  SR\_NODISCARD [**ValueAssociativeContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueAssociativeContainerIterator.md) | [**begin**](#function-begin) () <br> |
|  SR\_NODISCARD [**ValueAssociativeContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueAssociativeContainerIterator.md) | [**end**](#function-end) () <br> |




























## Public Functions Documentation




### function Clear 

```C++
void SR_UTILS_NS::Reflection::ValueAssociativeContainer::Clear () 
```




<hr>



### function Empty 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Reflection::ValueAssociativeContainer::Empty () const
```




<hr>



### function Erase 

```C++
void SR_UTILS_NS::Reflection::ValueAssociativeContainer::Erase (
    const Value & key
) 
```




<hr>



### function GetKeyType 

```C++
SR_NODISCARD Value SR_UTILS_NS::Reflection::ValueAssociativeContainer::GetKeyType () const
```




<hr>



### function GetMappedType 

```C++
SR_NODISCARD Value SR_UTILS_NS::Reflection::ValueAssociativeContainer::GetMappedType () const
```




<hr>



### function GetValueType 

```C++
SR_NODISCARD Value SR_UTILS_NS::Reflection::ValueAssociativeContainer::GetValueType () const
```




<hr>



### function Insert 

```C++
bool SR_UTILS_NS::Reflection::ValueAssociativeContainer::Insert (
    const Value & key,
    const Value & value
) 
```




<hr>



### function Reserve 

```C++
void SR_UTILS_NS::Reflection::ValueAssociativeContainer::Reserve (
    uint64_t size
) 
```




<hr>



### function Size 

```C++
inline SR_NODISCARD uint64_t SR_UTILS_NS::Reflection::ValueAssociativeContainer::Size () const
```




<hr>



### function begin 

```C++
inline SR_NODISCARD ValueAssociativeContainerIterator SR_UTILS_NS::Reflection::ValueAssociativeContainer::begin () 
```




<hr>



### function end 

```C++
inline SR_NODISCARD ValueAssociativeContainerIterator SR_UTILS_NS::Reflection::ValueAssociativeContainer::end () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Reflection/Value.h`

