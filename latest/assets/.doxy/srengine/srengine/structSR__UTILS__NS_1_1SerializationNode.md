

# Struct SR\_UTILS\_NS::SerializationNode



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) &gt; | [**children**](#variable-children)  <br> |
|  [**SerializationTrivialDataType**](unionSR__UTILS__NS_1_1SerializationTrivialDataType.md) | [**data**](#variable-data)   = `{}`<br> |
|  [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) | [**id**](#variable-id)  <br> |
|  std::string | [**string**](#variable-string)  <br> |
|  SerializationDataType | [**type**](#variable-type)   = `SerializationDataType::Unknown`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SerializationNode**](#function-serializationnode-14) () = default<br> |
|   | [**SerializationNode**](#function-serializationnode-24) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id, SerializationDataType type) <br> |
|   | [**SerializationNode**](#function-serializationnode-34) ([**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) && other) noexcept<br> |
|   | [**SerializationNode**](#function-serializationnode-44) (const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & other) <br> |
|  [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**operator=**](#function-operator) ([**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) && other) noexcept<br> |
|  [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**operator=**](#function-operator_1) (const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & other) <br> |




























## Public Attributes Documentation




### variable children 

```C++
std::vector<SerializationNode> SR_UTILS_NS::SerializationNode::children;
```




<hr>



### variable data 

```C++
SerializationTrivialDataType SR_UTILS_NS::SerializationNode::data;
```




<hr>



### variable id 

```C++
SerializationId SR_UTILS_NS::SerializationNode::id;
```




<hr>



### variable string 

```C++
std::string SR_UTILS_NS::SerializationNode::string;
```




<hr>



### variable type 

```C++
SerializationDataType SR_UTILS_NS::SerializationNode::type;
```




<hr>
## Public Functions Documentation




### function SerializationNode [1/4]

```C++
SR_UTILS_NS::SerializationNode::SerializationNode () = default
```




<hr>



### function SerializationNode [2/4]

```C++
inline SR_UTILS_NS::SerializationNode::SerializationNode (
    const SerializationId & id,
    SerializationDataType type
) 
```




<hr>



### function SerializationNode [3/4]

```C++
inline SR_UTILS_NS::SerializationNode::SerializationNode (
    SerializationNode && other
) noexcept
```




<hr>



### function SerializationNode [4/4]

```C++
inline SR_UTILS_NS::SerializationNode::SerializationNode (
    const SerializationNode & other
) 
```




<hr>



### function operator= 

```C++
inline SerializationNode & SR_UTILS_NS::SerializationNode::operator= (
    SerializationNode && other
) noexcept
```




<hr>



### function operator= 

```C++
inline SerializationNode & SR_UTILS_NS::SerializationNode::operator= (
    const SerializationNode & other
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/BaseSerialization.h`

