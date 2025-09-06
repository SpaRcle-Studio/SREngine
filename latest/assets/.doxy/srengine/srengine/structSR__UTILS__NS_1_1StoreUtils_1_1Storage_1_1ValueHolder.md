

# Struct SR\_UTILS\_NS::StoreUtils::Storage::ValueHolder



[**ClassList**](annotated.md) **>** [**ValueHolder**](structSR__UTILS__NS_1_1StoreUtils_1_1Storage_1_1ValueHolder.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  ValueType | [**type**](#variable-type)  <br> |
|  Value | [**value**](#variable-value)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ValueHolder**](#function-valueholder-14) () <br> |
|   | [**ValueHolder**](#function-valueholder-24) (Value val, ValueType type) <br> |
|   | [**ValueHolder**](#function-valueholder-34) (const ValueHolder & other) <br> |
|   | [**ValueHolder**](#function-valueholder-44) (ValueHolder && other) noexcept<br> |
|  ValueHolder & | [**operator=**](#function-operator) (const ValueHolder & other) <br> |
|  ValueHolder & | [**operator=**](#function-operator_1) (ValueHolder && other) noexcept<br> |
|   | [**~ValueHolder**](#function-valueholder) () <br> |




























## Public Attributes Documentation




### variable type 

```C++
ValueType SR_UTILS_NS::StoreUtils::Storage::ValueHolder::type;
```




<hr>



### variable value 

```C++
Value SR_UTILS_NS::StoreUtils::Storage::ValueHolder::value;
```




<hr>
## Public Functions Documentation




### function ValueHolder [1/4]

```C++
ValueHolder::ValueHolder () 
```




<hr>



### function ValueHolder [2/4]

```C++
ValueHolder::ValueHolder (
    Value val,
    ValueType type
) 
```




<hr>



### function ValueHolder [3/4]

```C++
ValueHolder::ValueHolder (
    const ValueHolder & other
) 
```




<hr>



### function ValueHolder [4/4]

```C++
ValueHolder::ValueHolder (
    ValueHolder && other
) noexcept
```




<hr>



### function operator= 

```C++
ValueHolder & ValueHolder::operator= (
    const ValueHolder & other
) 
```




<hr>



### function operator= 

```C++
ValueHolder & ValueHolder::operator= (
    ValueHolder && other
) noexcept
```




<hr>



### function ~ValueHolder 

```C++
ValueHolder::~ValueHolder () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/StoreUtils.h`

