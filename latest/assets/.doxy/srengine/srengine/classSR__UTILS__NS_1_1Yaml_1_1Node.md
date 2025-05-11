

# Class SR\_UTILS\_NS::Yaml::Node



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Yaml**](namespaceSR__UTILS__NS_1_1Yaml.md) **>** [**Node**](classSR__UTILS__NS_1_1Yaml_1_1Node.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**Node**](classSR__UTILS__NS_1_1Yaml_1_1Node.md) | [**AppendChild**](#function-appendchild) (const std::string\_view & name) <br> |
|  SR\_NODISCARD [**Node**](classSR__UTILS__NS_1_1Yaml_1_1Node.md) | [**GetChild**](#function-getchild) (const std::string\_view & name) const<br> |
|  SR\_NODISCARD std::vector&lt; [**Node**](classSR__UTILS__NS_1_1Yaml_1_1Node.md) &gt; | [**GetChildren**](#function-getchildren) () const<br> |
|  SR\_NODISCARD uint16\_t | [**GetId**](#function-getid) () const<br> |
|  SR\_NODISCARD std::string | [**GetKey**](#function-getkey) () const<br> |
|  SR\_NODISCARD std::string\_view | [**GetKeyView**](#function-getkeyview) () const<br> |
|  SR\_NODISCARD std::string | [**GetValue**](#function-getvalue) () const<br> |
|  SR\_NODISCARD std::string\_view | [**GetValueView**](#function-getvalueview) () const<br> |
|  SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () const<br> |
|  SR\_NODISCARD std::string | [**Name**](#function-name) () const<br> |
|  SR\_NODISCARD std::string\_view | [**NameView**](#function-nameview) () const<br> |
|   | [**Node**](#function-node-13) () = default<br> |
|   | [**Node**](#function-node-23) (void const \* pTreeImpl, const size\_t id) <br> |
|   | [**Node**](#function-node-33) (void \* pTreeImpl, const size\_t id) <br> |
|  SR\_NODISCARD void | [**SetValue**](#function-setvalue) (const std::string\_view & value) <br> |
|   | [**operator bool**](#function-operator-bool) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Node**](classSR__UTILS__NS_1_1Yaml_1_1Node.md) | [**Empty**](#function-empty) () <br> |


























## Public Functions Documentation




### function AppendChild 

```C++
SR_NODISCARD Node SR_UTILS_NS::Yaml::Node::AppendChild (
    const std::string_view & name
) 
```




<hr>



### function GetChild 

```C++
SR_NODISCARD Node SR_UTILS_NS::Yaml::Node::GetChild (
    const std::string_view & name
) const
```




<hr>



### function GetChildren 

```C++
SR_NODISCARD std::vector< Node > SR_UTILS_NS::Yaml::Node::GetChildren () const
```




<hr>



### function GetId 

```C++
SR_NODISCARD uint16_t SR_UTILS_NS::Yaml::Node::GetId () const
```




<hr>



### function GetKey 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Yaml::Node::GetKey () const
```




<hr>



### function GetKeyView 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::Yaml::Node::GetKeyView () const
```




<hr>



### function GetValue 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Yaml::Node::GetValue () const
```




<hr>



### function GetValueView 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::Yaml::Node::GetValueView () const
```




<hr>



### function IsValid 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Yaml::Node::IsValid () const
```




<hr>



### function Name 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Yaml::Node::Name () const
```




<hr>



### function NameView 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::Yaml::Node::NameView () const
```




<hr>



### function Node [1/3]

```C++
SR_UTILS_NS::Yaml::Node::Node () = default
```




<hr>



### function Node [2/3]

```C++
inline explicit SR_UTILS_NS::Yaml::Node::Node (
    void const * pTreeImpl,
    const size_t id
) 
```




<hr>



### function Node [3/3]

```C++
inline explicit SR_UTILS_NS::Yaml::Node::Node (
    void * pTreeImpl,
    const size_t id
) 
```




<hr>



### function SetValue 

```C++
SR_NODISCARD void SR_UTILS_NS::Yaml::Node::SetValue (
    const std::string_view & value
) 
```




<hr>



### function operator bool 

```C++
inline explicit SR_UTILS_NS::Yaml::Node::operator bool () const
```




<hr>
## Public Static Functions Documentation




### function Empty 

```C++
static inline Node SR_UTILS_NS::Yaml::Node::Empty () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Resources/Yaml.h`

