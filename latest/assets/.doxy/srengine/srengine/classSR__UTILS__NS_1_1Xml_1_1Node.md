

# Class SR\_UTILS\_NS::Xml::Node



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Xml**](namespaceSR__UTILS__NS_1_1Xml.md) **>** [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**AppendAttribute**](#function-appendattribute-12) (const T & value) <br> |
|  bool | [**AppendAttribute**](#function-appendattribute-22) (const std::string & name, const T & value) <br> |
|  bool | [**AppendAttributeDef**](#function-appendattributedef) (const std::string & name, const T & value, const U & def) <br> |
|  [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**AppendChild**](#function-appendchild-12) (const std::string & name) <br> |
|  [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**AppendChild**](#function-appendchild-22) (const [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) & node) <br> |
|  [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**AppendNode**](#function-appendnode-12) (const std::string & name) <br> |
|  [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**AppendNode**](#function-appendnode-22) (const [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) & node) <br> |
|  SR\_NODISCARD [**Attribute**](classSR__UTILS__NS_1_1Xml_1_1Attribute.md) | [**GetAttribute**](#function-getattribute-12) (const std::string & name) const<br> |
|  T | [**GetAttribute**](#function-getattribute-22) () const<br> |
|  SR\_NODISCARD [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**GetNode**](#function-getnode) (const std::string & name) const<br> |
|  SR\_NODISCARD std::vector&lt; [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) &gt; | [**GetNodes**](#function-getnodes-12) (const std::string & name) const<br> |
|  SR\_NODISCARD std::vector&lt; [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) &gt; | [**GetNodes**](#function-getnodes-22) () const<br> |
|  SR\_NODISCARD bool | [**HasAttribute**](#function-hasattribute) (const std::string & name) const<br> |
|  [**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**NAppendAttribute**](#function-nappendattribute) (const std::string & name, const T & value) <br> |
|  [**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**NAppendAttributeDef**](#function-nappendattributedef) (const std::string & name, const T & value, const U & def) <br> |
|  SR\_NODISCARD std::string | [**Name**](#function-name) () const<br> |
|  SR\_NODISCARD std::string\_view | [**NameView**](#function-nameview) () const<br> |
|   | [**Node**](#function-node-12) () <br> |
|   | [**Node**](#function-node-22) (pugi::xml\_node node) <br> |
|  SR\_NODISCARD [**Document**](classSR__UTILS__NS_1_1Xml_1_1Document.md) | [**ToDocument**](#function-todocument) () const<br> |
|  SR\_NODISCARD [**Attribute**](classSR__UTILS__NS_1_1Xml_1_1Attribute.md) | [**TryGetAttribute**](#function-trygetattribute-12) (const std::string & name) const<br> |
|  SR\_NODISCARD T | [**TryGetAttribute**](#function-trygetattribute-22) (const T & def) const<br> |
|  SR\_NODISCARD [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**TryGetNode**](#function-trygetnode) (const std::string & name) const<br> |
|  SR\_NODISCARD std::vector&lt; [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) &gt; | [**TryGetNodes**](#function-trygetnodes-12) () const<br> |
|  SR\_NODISCARD std::vector&lt; [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) &gt; | [**TryGetNodes**](#function-trygetnodes-22) (const std::string & name) const<br> |
|  SR\_NODISCARD bool | [**Valid**](#function-valid) () const<br> |
|   | [**operator bool**](#function-operator-bool) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**Empty**](#function-empty) () <br> |


























## Public Functions Documentation




### function AppendAttribute [1/2]

```C++
template<typename T>
inline bool SR_UTILS_NS::Xml::Node::AppendAttribute (
    const T & value
) 
```




<hr>



### function AppendAttribute [2/2]

```C++
template<typename T>
inline bool SR_UTILS_NS::Xml::Node::AppendAttribute (
    const std::string & name,
    const T & value
) 
```




<hr>



### function AppendAttributeDef 

```C++
template<typename T, typename U>
inline bool SR_UTILS_NS::Xml::Node::AppendAttributeDef (
    const std::string & name,
    const T & value,
    const U & def
) 
```




<hr>



### function AppendChild [1/2]

```C++
Node SR_UTILS_NS::Xml::Node::AppendChild (
    const std::string & name
) 
```




<hr>



### function AppendChild [2/2]

```C++
Node SR_UTILS_NS::Xml::Node::AppendChild (
    const Node & node
) 
```




<hr>



### function AppendNode [1/2]

```C++
inline Node SR_UTILS_NS::Xml::Node::AppendNode (
    const std::string & name
) 
```




<hr>



### function AppendNode [2/2]

```C++
inline Node SR_UTILS_NS::Xml::Node::AppendNode (
    const Node & node
) 
```




<hr>



### function GetAttribute [1/2]

```C++
inline SR_NODISCARD Attribute SR_UTILS_NS::Xml::Node::GetAttribute (
    const std::string & name
) const
```




<hr>



### function GetAttribute [2/2]

```C++
template<typename T>
inline T SR_UTILS_NS::Xml::Node::GetAttribute () const
```




<hr>



### function GetNode 

```C++
inline SR_NODISCARD Node SR_UTILS_NS::Xml::Node::GetNode (
    const std::string & name
) const
```




<hr>



### function GetNodes [1/2]

```C++
SR_NODISCARD std::vector< Node > SR_UTILS_NS::Xml::Node::GetNodes (
    const std::string & name
) const
```




<hr>



### function GetNodes [2/2]

```C++
SR_NODISCARD std::vector< Node > SR_UTILS_NS::Xml::Node::GetNodes () const
```




<hr>



### function HasAttribute 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Xml::Node::HasAttribute (
    const std::string & name
) const
```




<hr>



### function NAppendAttribute 

```C++
template<typename T>
inline Xml::Node SR_UTILS_NS::Xml::Node::NAppendAttribute (
    const std::string & name,
    const T & value
) 
```




<hr>



### function NAppendAttributeDef 

```C++
template<typename T, typename U>
inline Xml::Node SR_UTILS_NS::Xml::Node::NAppendAttributeDef (
    const std::string & name,
    const T & value,
    const U & def
) 
```




<hr>



### function Name 

```C++
inline SR_NODISCARD std::string SR_UTILS_NS::Xml::Node::Name () const
```




<hr>



### function NameView 

```C++
inline SR_NODISCARD std::string_view SR_UTILS_NS::Xml::Node::NameView () const
```




<hr>



### function Node [1/2]

```C++
SR_UTILS_NS::Xml::Node::Node () 
```




<hr>



### function Node [2/2]

```C++
inline explicit SR_UTILS_NS::Xml::Node::Node (
    pugi::xml_node node
) 
```




<hr>



### function ToDocument 

```C++
SR_NODISCARD Document SR_UTILS_NS::Xml::Node::ToDocument () const
```




<hr>



### function TryGetAttribute [1/2]

```C++
inline SR_NODISCARD Attribute SR_UTILS_NS::Xml::Node::TryGetAttribute (
    const std::string & name
) const
```




<hr>



### function TryGetAttribute [2/2]

```C++
template<typename T>
inline SR_NODISCARD T SR_UTILS_NS::Xml::Node::TryGetAttribute (
    const T & def
) const
```




<hr>



### function TryGetNode 

```C++
inline SR_NODISCARD Node SR_UTILS_NS::Xml::Node::TryGetNode (
    const std::string & name
) const
```




<hr>



### function TryGetNodes [1/2]

```C++
SR_NODISCARD std::vector< Node > SR_UTILS_NS::Xml::Node::TryGetNodes () const
```




<hr>



### function TryGetNodes [2/2]

```C++
SR_NODISCARD std::vector< Node > SR_UTILS_NS::Xml::Node::TryGetNodes (
    const std::string & name
) const
```




<hr>



### function Valid 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Xml::Node::Valid () const
```




<hr>



### function operator bool 

```C++
inline explicit SR_UTILS_NS::Xml::Node::operator bool () const
```




<hr>
## Public Static Functions Documentation




### function Empty 

```C++
static inline Node SR_UTILS_NS::Xml::Node::Empty () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Resources/Xml.h`

