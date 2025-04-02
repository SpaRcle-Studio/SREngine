

# Class SR\_UTILS\_NS::Reflection::ValueSequenceContainerIterator



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Reflection**](namespaceSR__UTILS__NS_1_1Reflection.md) **>** [**ValueSequenceContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainerIterator.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD | [**operator bool**](#function-operator-bool) () noexcept const<br> |
|  SR\_NODISCARD bool | [**operator!=**](#function-operator) (const [**ValueSequenceContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainerIterator.md) & other) noexcept const<br> |
|  SR\_NODISCARD [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**operator\***](#function-operator_1) () const<br> |
|  [**ValueSequenceContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainerIterator.md) & | [**operator++**](#function-operator_2) () noexcept<br> |
|  [**ValueSequenceContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainerIterator.md) | [**operator++**](#function-operator_3) (int32\_t value) noexcept<br> |
|  [**ValueSequenceContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainerIterator.md) & | [**operator--**](#function-operator_4) () noexcept<br> |
|  [**ValueSequenceContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainerIterator.md) | [**operator--**](#function-operator_5) (int32\_t value) noexcept<br> |
|  SR\_NODISCARD [**InputIteratorPointer**](structSR__UTILS__NS_1_1InputIteratorPointer.md)&lt; [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) &gt; | [**operator-&gt;**](#function-operator_6) () const<br> |
|  SR\_NODISCARD bool | [**operator==**](#function-operator_7) (const [**ValueSequenceContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainerIterator.md) & other) noexcept const<br>_NOLINT._  |




























## Public Functions Documentation




### function operator bool 

```C++
inline SR_NODISCARD SR_UTILS_NS::Reflection::ValueSequenceContainerIterator::operator bool () noexcept const
```




<hr>



### function operator!= 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Reflection::ValueSequenceContainerIterator::operator!= (
    const ValueSequenceContainerIterator & other
) noexcept const
```




<hr>



### function operator\* 

```C++
SR_NODISCARD Value SR_UTILS_NS::Reflection::ValueSequenceContainerIterator::operator* () const
```




<hr>



### function operator++ 

```C++
inline ValueSequenceContainerIterator & SR_UTILS_NS::Reflection::ValueSequenceContainerIterator::operator++ () noexcept
```




<hr>



### function operator++ 

```C++
inline ValueSequenceContainerIterator SR_UTILS_NS::Reflection::ValueSequenceContainerIterator::operator++ (
    int32_t value
) noexcept
```




<hr>



### function operator-- 

```C++
inline ValueSequenceContainerIterator & SR_UTILS_NS::Reflection::ValueSequenceContainerIterator::operator-- () noexcept
```




<hr>



### function operator-- 

```C++
inline ValueSequenceContainerIterator SR_UTILS_NS::Reflection::ValueSequenceContainerIterator::operator-- (
    int32_t value
) noexcept
```




<hr>



### function operator-&gt; 

```C++
SR_NODISCARD InputIteratorPointer < Value > SR_UTILS_NS::Reflection::ValueSequenceContainerIterator::operator-> () const
```




<hr>



### function operator== 

_NOLINT._ 
```C++
inline SR_NODISCARD bool SR_UTILS_NS::Reflection::ValueSequenceContainerIterator::operator== (
    const ValueSequenceContainerIterator & other
) noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Reflection/Value.h`

