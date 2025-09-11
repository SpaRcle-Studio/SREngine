

# Struct SR\_GRAPH\_UI\_NS::UILayout



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_UI\_NS**](namespaceSR__GRAPH__UI__NS.md) **>** [**UILayout**](structSR__GRAPH__UI__NS_1_1UILayout.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)
















## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |










## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FVector2 | [**absolutePosition**](#variable-absoluteposition)   = `{ 0.f, 0.f }`<br> |
|  UIAlign | [**align**](#variable-align)   = `UIAlign::Auto`<br> |
|  float\_t | [**aspectRatio**](#variable-aspectratio)   = `0.0f`<br> |
|  float\_t | [**height**](#variable-height)   = `0.0f`<br> |
|  UISizePolicy | [**heightPolicy**](#variable-heightpolicy)   = `UISizePolicy::Auto`<br> |
|  SR\_MATH\_NS::FRect | [**margin**](#variable-margin)  <br> |
|  SR\_MATH\_NS::FVector2 | [**offset**](#variable-offset)   = `{ 0.f, 0.f }`<br> |
|  SR\_MATH\_NS::FRect | [**padding**](#variable-padding)  <br> |
|  UIPositionType | [**positionType**](#variable-positiontype)   = `UIPositionType::Relative`<br> |
|  float\_t | [**width**](#variable-width)   = `0.0f`<br> |
|  UISizePolicy | [**widthPolicy**](#variable-widthpolicy)   = `UISizePolicy::Auto`<br> |


















































## Public Functions inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-addserializationflags) (SerializationFlags flags) noexcept<br> |
|  SR\_NODISCARD bool | [**HasSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-hasserializationflags) (SerializationFlags flags) noexcept const<br> |
| virtual bool | [**Load**](classSR__UTILS__NS_1_1Serializable.md#function-load) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer) <br> |
| virtual void | [**OnPostLoad**](classSR__UTILS__NS_1_1Serializable.md#function-onpostload) () <br> |
| virtual void | [**OnPostSave**](classSR__UTILS__NS_1_1Serializable.md#function-onpostsave) () <br> |
| virtual void | [**OnPreLoad**](classSR__UTILS__NS_1_1Serializable.md#function-onpreload) () <br> |
| virtual void | [**OnPreSave**](classSR__UTILS__NS_1_1Serializable.md#function-onpresave) () <br> |
|  void | [**RemoveSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-removeserializationflags) (SerializationFlags flags) noexcept<br> |
| virtual void | [**Save**](classSR__UTILS__NS_1_1Serializable.md#function-save) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer) const<br> |
| virtual void | [**VerifyAfterLoad**](classSR__UTILS__NS_1_1Serializable.md#function-verifyafterload) (SerializableVerifyContext & context) noexcept const<br> |


## Public Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**CloneTo**](classSR__UTILS__NS_1_1SRClass.md#function-cloneto) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) & clone) const<br> |
| virtual SR\_NODISCARD const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMeta**](classSR__UTILS__NS_1_1SRClass.md#function-getmeta) () noexcept const = 0<br> |
| virtual  | [**~SRClass**](classSR__UTILS__NS_1_1SRClass.md#function-srclass) () = default<br> |






## Public Static Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**AllocateStatic**](classSR__UTILS__NS_1_1SRClass.md#function-allocatestatic) () noexcept<br> |
|  SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](classSR__UTILS__NS_1_1SRClass.md#function-getbasemetas) () noexcept<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetClassStaticName**](classSR__UTILS__NS_1_1SRClass.md#function-getclassstaticname) () noexcept<br> |
|  const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMetaStatic**](classSR__UTILS__NS_1_1SRClass.md#function-getmetastatic) () noexcept<br> |
|  bool | [**RegisterPropertiesCodegen**](classSR__UTILS__NS_1_1SRClass.md#function-registerpropertiescodegen) () <br> |










































































## Public Attributes Documentation




### variable absolutePosition 

```C++
SR_MATH_NS::FVector2 SR_GRAPH_UI_NS::UILayout::absolutePosition;
```




<hr>



### variable align 

```C++
UIAlign SR_GRAPH_UI_NS::UILayout::align;
```




<hr>



### variable aspectRatio 

```C++
float_t SR_GRAPH_UI_NS::UILayout::aspectRatio;
```




<hr>



### variable height 

```C++
float_t SR_GRAPH_UI_NS::UILayout::height;
```




<hr>



### variable heightPolicy 

```C++
UISizePolicy SR_GRAPH_UI_NS::UILayout::heightPolicy;
```




<hr>



### variable margin 

```C++
SR_MATH_NS::FRect SR_GRAPH_UI_NS::UILayout::margin;
```




<hr>



### variable offset 

```C++
SR_MATH_NS::FVector2 SR_GRAPH_UI_NS::UILayout::offset;
```




<hr>



### variable padding 

```C++
SR_MATH_NS::FRect SR_GRAPH_UI_NS::UILayout::padding;
```




<hr>



### variable positionType 

```C++
UIPositionType SR_GRAPH_UI_NS::UILayout::positionType;
```




<hr>



### variable width 

```C++
float_t SR_GRAPH_UI_NS::UILayout::width;
```




<hr>



### variable widthPolicy 

```C++
UISizePolicy SR_GRAPH_UI_NS::UILayout::widthPolicy;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/UI/UIControlNode.h`

