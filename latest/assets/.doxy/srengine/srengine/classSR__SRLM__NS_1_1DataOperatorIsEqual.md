

# Class SR\_SRLM\_NS::DataOperatorIsEqual



[**ClassList**](annotated.md) **>** [**SR\_SRLM\_NS**](namespaceSR__SRLM__NS.md) **>** [**DataOperatorIsEqual**](classSR__SRLM__NS_1_1DataOperatorIsEqual.md)








Inherits the following classes: [SR\_SRLM\_NS::DataOperator](classSR__SRLM__NS_1_1DataOperator.md)


Inherited by the following classes: [SR\_SRLM\_NS::DataOperatorIsGreaterOrEqual](classSR__SRLM__NS_1_1DataOperatorIsGreaterOrEqual.md),  [SR\_SRLM\_NS::DataOperatorIsLessOrEqual](classSR__SRLM__NS_1_1DataOperatorIsLessOrEqual.md),  [SR\_SRLM\_NS::DataOperatorIsNotEqual](classSR__SRLM__NS_1_1DataOperatorIsNotEqual.md)










































































## Public Functions inherited from SR_SRLM_NS::DataOperator

See [SR\_SRLM\_NS::DataOperator](classSR__SRLM__NS_1_1DataOperator.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**Calculate**](classSR__SRLM__NS_1_1DataOperator.md#function-calculate) ([**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pFirst, [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pSecond) = 0<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |




































































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**Calculate**](#function-calculate) ([**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pFirst, [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pSecond) override<br> |




## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |








## Protected Functions Documentation




### function Calculate 

```C++
virtual SR_NODISCARD DataType * SR_SRLM_NS::DataOperatorIsEqual::Calculate (
    DataType * pFirst,
    DataType * pSecond
) override
```



Implements [*SR\_SRLM\_NS::DataOperator::Calculate*](classSR__SRLM__NS_1_1DataOperator.md#function-calculate)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/SRLM/DataOperators.h`

