

# Namespace SR\_UTILS\_NS::Xml



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Xml**](namespaceSR__UTILS__NS_1_1Xml.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Attribute**](classSR__UTILS__NS_1_1Xml_1_1Attribute.md) <br> |
| class | [**Document**](classSR__UTILS__NS_1_1Xml_1_1Document.md) <br> |
| class | [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) <br> |








## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  int32\_t | [**g\_xml\_last\_error**](#variable-g_xml_last_error)   = `0`<br> |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**AppendColorNode**](#function-appendcolornode) ([**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) & node, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**NodeToColor**](#function-nodetocolor) (const [**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) & node) <br> |


























## Public Static Attributes Documentation




### variable g\_xml\_last\_error 

```C++
int32_t SR_UTILS_NS::Xml::g_xml_last_error;
```




<hr>
## Public Static Functions Documentation




### function AppendColorNode 

```C++
static SR_MAYBE_UNUSED void SR_UTILS_NS::Xml::AppendColorNode (
    Xml::Node & node,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function NodeToColor 

```C++
template<bool NeedConvert>
static SR_MATH_NS::FColor SR_UTILS_NS::Xml::NodeToColor (
    const Xml::Node & node
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Resources/Xml.h`

