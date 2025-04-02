

# Struct SR\_UTILS\_NS::Web::CSSDirection



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md) **>** [**CSSDirection**](structSR__UTILS__NS_1_1Web_1_1CSSDirection.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**DirectionType**](#enum-directiontype)  <br> |
| enum uint8\_t | [**Type**](#enum-type)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_UTILS\_NS::Web::CSSDirection**](structSR__UTILS__NS_1_1Web_1_1CSSDirection.md) | [**CSSDirection**](#variable-cssdirection)  <br> |
|  float\_t | [**degree**](#variable-degree)  <br> |
|  Type | [**direction**](#variable-direction)   = `Type::Bottom`<br> |
|  enum SR\_UTILS\_NS::Web::CSSDirection::DirectionType | [**type**](#variable-type)   = `DirectionType::To`<br> |












































## Public Types Documentation




### enum DirectionType 

```C++
enum SR_UTILS_NS::Web::CSSDirection::DirectionType {
    To,
    Degree
};
```




<hr>



### enum Type 

```C++
enum SR_UTILS_NS::Web::CSSDirection::Type {
    Top,
    Right,
    Bottom,
    Left,
    TopRight,
    BottomRight,
    BottomLeft,
    TopLeft
};
```




<hr>
## Public Attributes Documentation




### variable CSSDirection 

```C++
union SR_UTILS_NS::Web::CSSDirection SR_UTILS_NS::Web::CSSDirection;
```




<hr>



### variable degree 

```C++
float_t SR_UTILS_NS::Web::CSSDirection::degree;
```




<hr>



### variable direction 

```C++
Type SR_UTILS_NS::Web::CSSDirection::direction;
```




<hr>



### variable type 

```C++
enum SR_UTILS_NS::Web::CSSDirection::DirectionType SR_UTILS_NS::Web::CSSDirection::type;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Web/CSS/CSSColor.h`

