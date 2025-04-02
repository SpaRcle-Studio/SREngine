

# Class SR\_SRLM\_NS::DataOperator



[**ClassList**](annotated.md) **>** [**SR\_SRLM\_NS**](namespaceSR__SRLM__NS.md) **>** [**DataOperator**](classSR__SRLM__NS_1_1DataOperator.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_SRLM\_NS::DataOperatorAddition](classSR__SRLM__NS_1_1DataOperatorAddition.md),  [SR\_SRLM\_NS::DataOperatorDivision](classSR__SRLM__NS_1_1DataOperatorDivision.md),  [SR\_SRLM\_NS::DataOperatorIsEqual](classSR__SRLM__NS_1_1DataOperatorIsEqual.md),  [SR\_SRLM\_NS::DataOperatorIsGreater](classSR__SRLM__NS_1_1DataOperatorIsGreater.md),  [SR\_SRLM\_NS::DataOperatorModulo](classSR__SRLM__NS_1_1DataOperatorModulo.md),  [SR\_SRLM\_NS::DataOperatorMultiplication](classSR__SRLM__NS_1_1DataOperatorMultiplication.md),  [SR\_SRLM\_NS::DataOperatorSubtraction](classSR__SRLM__NS_1_1DataOperatorSubtraction.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**Calculate**](#function-calculate) ([**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pFirst, [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pSecond) = 0<br> |


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






## Public Functions Documentation




### function Calculate 

```C++
virtual SR_NODISCARD DataType * SR_SRLM_NS::DataOperator::Calculate (
    DataType * pFirst,
    DataType * pSecond
) = 0
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/SRLM/DataOperators.h`

