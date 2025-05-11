

# Struct SR\_UTILS\_NS::EnumTraits

**template &lt;typename EnumType&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**EnumTraits**](structSR__UTILS__NS_1_1EnumTraits.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef typename std::conditional\_t&lt; std::is\_enum\_v&lt; EnumType &gt;, EnumType, void &gt; | [**EnumResultType**](#typedef-enumresulttype)  <br> |
| typedef typename std::conditional\_t&lt; IsDeclaredInNamespace, const EnumResultType \*, [**Codegen::EnumSelector**](structCodegen_1_1EnumSelector.md)&lt; EnumType &gt; &gt; | [**EnumSelectorType**](#typedef-enumselectortype)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**IsDeclaredInNamespace**](#variable-isdeclaredinnamespace)   = `(Codegen::GetEnumVariant(static\_cast&lt;const EnumResultType\*&gt;(nullptr)) != EnumVariant::Undefined)`<br> |
|  constexpr bool | [**IsEnum**](#variable-isenum)   = `Codegen::GetEnumVariant(EnumSelectorType{}) != EnumVariant::Undefined`<br> |
|  constexpr bool | [**IsFlags**](#variable-isflags)   = `Codegen::GetEnumVariant(EnumSelectorType{}) == EnumVariant::Flags`<br> |
|  constexpr size\_t | [**NumItems**](#variable-numitems)   = `Codegen::GetEnumItemsCount(EnumSelectorType{})`<br> |










































## Public Types Documentation




### typedef EnumResultType 

```C++
using SR_UTILS_NS::EnumTraits< EnumType >::EnumResultType =  typename std::conditional_t<std::is_enum_v<EnumType>, EnumType, void>;
```




<hr>



### typedef EnumSelectorType 

```C++
using SR_UTILS_NS::EnumTraits< EnumType >::EnumSelectorType =  typename std::conditional_t<IsDeclaredInNamespace, const EnumResultType*, Codegen::EnumSelector<EnumType> >;
```




<hr>
## Public Static Attributes Documentation




### variable IsDeclaredInNamespace 

```C++
constexpr bool SR_UTILS_NS::EnumTraits< EnumType >::IsDeclaredInNamespace;
```




<hr>



### variable IsEnum 

```C++
constexpr bool SR_UTILS_NS::EnumTraits< EnumType >::IsEnum;
```




<hr>



### variable IsFlags 

```C++
constexpr bool SR_UTILS_NS::EnumTraits< EnumType >::IsFlags;
```




<hr>



### variable NumItems 

```C++
constexpr size_t SR_UTILS_NS::EnumTraits< EnumType >::NumItems;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/EnumReflector.h`

