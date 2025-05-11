

# Struct SR\_SRLM\_NS::LogicalNode::NodePin



[**ClassList**](annotated.md) **>** [**SR\_SRLM\_NS**](namespaceSR__SRLM__NS.md) **>** [**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) **>** [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**NodeConnect**](structSR__SRLM__NS_1_1LogicalNode_1_1NodeConnect.md) &gt; | [**connections**](#variable-connections)  <br> |
|  Hash | [**hashName**](#variable-hashname)   = `SR\_UINT64\_MAX`<br> |
|  [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**pData**](#variable-pdata)   = `nullptr`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* | [**GetFirstNode**](#function-getfirstnode) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetFirstNodePin**](#function-getfirstnodepin) () const<br> |




























## Public Attributes Documentation




### variable connections 

```C++
std::vector<NodeConnect> SR_SRLM_NS::LogicalNode::NodePin::connections;
```




<hr>



### variable hashName 

```C++
Hash SR_SRLM_NS::LogicalNode::NodePin::hashName;
```




<hr>



### variable pData 

```C++
DataType* SR_SRLM_NS::LogicalNode::NodePin::pData;
```




<hr>
## Public Functions Documentation




### function GetFirstNode 

```C++
inline SR_NODISCARD LogicalNode * SR_SRLM_NS::LogicalNode::NodePin::GetFirstNode () const
```




<hr>



### function GetFirstNodePin 

```C++
inline SR_NODISCARD uint32_t SR_SRLM_NS::LogicalNode::NodePin::GetFirstNodePin () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/SRLM/LogicalNode.h`

