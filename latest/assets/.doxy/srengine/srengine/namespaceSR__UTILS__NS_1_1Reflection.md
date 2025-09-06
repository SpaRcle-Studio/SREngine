

# Namespace SR\_UTILS\_NS::Reflection



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Reflection**](namespaceSR__UTILS__NS_1_1Reflection.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) <br> |
| class | [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) <br> |
| class | [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) <br> |
| class | [**ValueAssociativeContainer**](classSR__UTILS__NS_1_1Reflection_1_1ValueAssociativeContainer.md) <br> |
| class | [**ValueAssociativeContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueAssociativeContainerIterator.md) <br> |
| class | [**ValueSequenceContainer**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainer.md) <br> |
| class | [**ValueSequenceContainerIterator**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainerIterator.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**PropertySRClassContainsMode**](#enum-propertysrclasscontainsmode)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**ContainsSRClassV**](#variable-containssrclassv)   = `IsSRClassV&lt;InnerTypeT&lt;T&gt;&gt;`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_INLINE void | [**CloneTo**](#function-cloneto) (const T & from, T & to) <br> |
|  SR\_INLINE void | [**ForEachSRClass**](#function-foreachsrclass) (T && object, const auto & func) <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetPropertyInspector**](#function-getpropertyinspector) () <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**MakeDisplayName**](#function-makedisplayname) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  std::string\_view | [**MakeSerializePropertyName**](#function-makeserializepropertyname) (std::string\_view name) <br> |




























## Public Types Documentation




### enum PropertySRClassContainsMode 

```C++
enum SR_UTILS_NS::Reflection::PropertySRClassContainsMode {
    NotContains,
    SharedPointer,
    Contains,
    Inner
};
```




<hr>
## Public Attributes Documentation




### variable ContainsSRClassV 

```C++
constexpr bool SR_UTILS_NS::Reflection::ContainsSRClassV;
```




<hr>
## Public Functions Documentation




### function CloneTo 

```C++
template<typename T>
SR_INLINE void SR_UTILS_NS::Reflection::CloneTo (
    const T & from,
    T & to
) 
```




<hr>



### function ForEachSRClass 

```C++
template<typename T>
SR_INLINE void SR_UTILS_NS::Reflection::ForEachSRClass (
    T && object,
    const auto & func
) 
```




<hr>



### function GetPropertyInspector 

```C++
template<typename T>
SR_UTILS_NS::StringAtom SR_UTILS_NS::Reflection::GetPropertyInspector () 
```




<hr>



### function MakeDisplayName 

```C++
SR_UTILS_NS::StringAtom SR_UTILS_NS::Reflection::MakeDisplayName (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function MakeSerializePropertyName 

```C++
std::string_view SR_UTILS_NS::Reflection::MakeSerializePropertyName (
    std::string_view name
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Reflection/Property.h`

