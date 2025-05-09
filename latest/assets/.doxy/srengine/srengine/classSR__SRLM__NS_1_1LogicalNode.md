

# Class SR\_SRLM\_NS::LogicalNode



[**ClassList**](annotated.md) **>** [**SR\_SRLM\_NS**](namespaceSR__SRLM__NS.md) **>** [**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_SRLM\_NS::ConnectorNode](classSR__SRLM__NS_1_1ConnectorNode.md),  [SR\_SRLM\_NS::EndResetNode](classSR__SRLM__NS_1_1EndResetNode.md),  [SR\_SRLM\_NS::IComputeNode](classSR__SRLM__NS_1_1IComputeNode.md),  [SR\_SRLM\_NS::IExecutableNode](classSR__SRLM__NS_1_1IExecutableNode.md),  [SR\_SRLM\_NS::StartResetNode](classSR__SRLM__NS_1_1StartResetNode.md)










## Classes

| Type | Name |
| ---: | :--- |
| struct | [**NodeConnect**](structSR__SRLM__NS_1_1LogicalNode_1_1NodeConnect.md) <br> |
| struct | [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef uint64\_t | [**Hash**](#typedef-hash)  <br> |
| typedef std::vector&lt; [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) &gt; | [**Pins**](#typedef-pins)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddInputConnection**](#function-addinputconnection) ([**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* pNode, uint32\_t nodePinIndex, uint32\_t pinIndex) <br> |
|  [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) & | [**AddInputData**](#function-addinputdata-12) ([**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pData, uint64\_t hashName=SR\_UINT64\_MAX) <br> |
|  [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) & | [**AddInputData**](#function-addinputdata-22) (uint64\_t hashName=SR\_UINT64\_MAX) <br> |
|  void | [**AddOutputConnection**](#function-addoutputconnection) ([**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* pNode, uint32\_t nodePinIndex, uint32\_t pinIndex) <br> |
|  [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) & | [**AddOutputData**](#function-addoutputdata-12) ([**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pData, uint64\_t hashName=SR\_UINT64\_MAX) <br> |
|  [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) & | [**AddOutputData**](#function-addoutputdata-22) (uint64\_t hashName=SR\_UINT64\_MAX) <br> |
|  SR\_NODISCARD const [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**CalcInput**](#function-calcinput) (uint32\_t index) <br> |
|  void | [**ClearLogicalNode**](#function-clearlogicalnode) () <br> |
| virtual void | [**Execute**](#function-execute) (float\_t dt) <br> |
|  SR\_NODISCARD [**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* | [**GetBaseLogicalNode**](#function-getbaselogicalnode) () noexcept<br> |
|  SR\_NODISCARD Pins & | [**GetInputs**](#function-getinputs) () <br> |
| virtual SR\_NODISCARD uint64\_t | [**GetNodeHashName**](#function-getnodehashname) () noexcept const = 0<br> |
|  SR\_NODISCARD uint32\_t | [**GetNodeIndex**](#function-getnodeindex) () noexcept const<br> |
| virtual SR\_NODISCARD std::string | [**GetNodeName**](#function-getnodename) () noexcept const = 0<br> |
| virtual SR\_NODISCARD const [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**GetOutput**](#function-getoutput) (uint32\_t index) <br> |
|  SR\_NODISCARD Pins & | [**GetOutputs**](#function-getoutputs) () <br> |
|  SR\_NODISCARD LogicalNodeStatus | [**GetStatus**](#function-getstatus) () noexcept const<br> |
| virtual SR\_NODISCARD LogicalNodeType | [**GetType**](#function-gettype) () noexcept const = 0<br> |
|  SR\_NODISCARD bool | [**HasErrors**](#function-haserrors) () const<br> |
| virtual void | [**InitNode**](#function-initnode) () <br> |
| virtual void | [**InitValues**](#function-initvalues) () <br> |
| virtual SR\_NODISCARD bool | [**IsDirty**](#function-isdirty) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsEntryPoint**](#function-isentrypoint) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsNeedPostRepeat**](#function-isneedpostrepeat) () const<br> |
| virtual SR\_NODISCARD bool | [**IsNeedRepeat**](#function-isneedrepeat) () const<br> |
|  SR\_NODISCARD bool | [**IsSuccessfullyCompleted**](#function-issuccessfullycompleted) () noexcept const<br> |
| virtual void | [**MarkDirty**](#function-markdirty) () <br> |
|  void | [**RemoveInput**](#function-removeinput) (uint32\_t index) <br> |
|  void | [**RemoveInputConnection**](#function-removeinputconnection) ([**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* pNode, uint32\_t pinIndex) <br> |
|  void | [**RemoveOutput**](#function-removeoutput) (uint32\_t index) <br> |
|  void | [**RemoveOutputConnection**](#function-removeoutputconnection) ([**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* pNode, uint32\_t pinIndex) <br> |
| virtual void | [**Reset**](#function-reset) () <br> |
|  void | [**ResetInputFlows**](#function-resetinputflows) () <br> |
|  void | [**ResetOutputFlows**](#function-resetoutputflows) () <br> |
|  void | [**ResetStatus**](#function-resetstatus) () <br> |
| virtual void | [**SaveXml**](#function-savexml) (SR\_XML\_NS::Node & xmlNode) <br> |
| virtual void | [**SetInput**](#function-setinput) (const [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pInput, uint32\_t index) <br> |
|  void | [**SetMachine**](#function-setmachine) ([**LogicalMachine**](classSR__SRLM__NS_1_1LogicalMachine.md) \* pMachine) <br> |
|  void | [**SetNodeIndex**](#function-setnodeindex) (uint32\_t index) <br> |
|   | [**~LogicalNode**](#function-logicalnode) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* | [**LoadXml**](#function-loadxml) (const SR\_XML\_NS::Node & xmlNode) <br> |












## Protected Attributes

| Type | Name |
| ---: | :--- |
|  Pins | [**m\_inputs**](#variable-m_inputs)  <br> |
|  [**LogicalMachine**](classSR__SRLM__NS_1_1LogicalMachine.md) \* | [**m\_machine**](#variable-m_machine)   = `nullptr`<br> |
|  uint32\_t | [**m\_nodeIndex**](#variable-m_nodeindex)   = `SR\_UINT32\_MAX`<br> |
|  Pins | [**m\_outputs**](#variable-m_outputs)  <br> |
|  LogicalNodeStatus | [**m\_status**](#variable-m_status)   = `LogicalNodeStatus::None`<br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef Hash 

```C++
using SR_SRLM_NS::LogicalNode::Hash =  uint64_t;
```




<hr>



### typedef Pins 

```C++
using SR_SRLM_NS::LogicalNode::Pins =  std::vector<NodePin>;
```




<hr>
## Public Functions Documentation




### function AddInputConnection 

```C++
void SR_SRLM_NS::LogicalNode::AddInputConnection (
    LogicalNode * pNode,
    uint32_t nodePinIndex,
    uint32_t pinIndex
) 
```




<hr>



### function AddInputData [1/2]

```C++
NodePin & SR_SRLM_NS::LogicalNode::AddInputData (
    DataType * pData,
    uint64_t hashName=SR_UINT64_MAX
) 
```




<hr>



### function AddInputData [2/2]

```C++
template<typename T>
inline NodePin & SR_SRLM_NS::LogicalNode::AddInputData (
    uint64_t hashName=SR_UINT64_MAX
) 
```




<hr>



### function AddOutputConnection 

```C++
void SR_SRLM_NS::LogicalNode::AddOutputConnection (
    LogicalNode * pNode,
    uint32_t nodePinIndex,
    uint32_t pinIndex
) 
```




<hr>



### function AddOutputData [1/2]

```C++
NodePin & SR_SRLM_NS::LogicalNode::AddOutputData (
    DataType * pData,
    uint64_t hashName=SR_UINT64_MAX
) 
```




<hr>



### function AddOutputData [2/2]

```C++
template<typename T>
inline NodePin & SR_SRLM_NS::LogicalNode::AddOutputData (
    uint64_t hashName=SR_UINT64_MAX
) 
```




<hr>



### function CalcInput 

```C++
SR_NODISCARD const DataType * SR_SRLM_NS::LogicalNode::CalcInput (
    uint32_t index
) 
```




<hr>



### function ClearLogicalNode 

```C++
void SR_SRLM_NS::LogicalNode::ClearLogicalNode () 
```




<hr>



### function Execute 

```C++
inline virtual void SR_SRLM_NS::LogicalNode::Execute (
    float_t dt
) 
```




<hr>



### function GetBaseLogicalNode 

```C++
inline SR_NODISCARD LogicalNode * SR_SRLM_NS::LogicalNode::GetBaseLogicalNode () noexcept
```




<hr>



### function GetInputs 

```C++
inline SR_NODISCARD Pins & SR_SRLM_NS::LogicalNode::GetInputs () 
```




<hr>



### function GetNodeHashName 

```C++
virtual SR_NODISCARD uint64_t SR_SRLM_NS::LogicalNode::GetNodeHashName () noexcept const = 0
```




<hr>



### function GetNodeIndex 

```C++
inline SR_NODISCARD uint32_t SR_SRLM_NS::LogicalNode::GetNodeIndex () noexcept const
```




<hr>



### function GetNodeName 

```C++
virtual SR_NODISCARD std::string SR_SRLM_NS::LogicalNode::GetNodeName () noexcept const = 0
```




<hr>



### function GetOutput 

```C++
virtual SR_NODISCARD const DataType * SR_SRLM_NS::LogicalNode::GetOutput (
    uint32_t index
) 
```




<hr>



### function GetOutputs 

```C++
inline SR_NODISCARD Pins & SR_SRLM_NS::LogicalNode::GetOutputs () 
```




<hr>



### function GetStatus 

```C++
inline SR_NODISCARD LogicalNodeStatus SR_SRLM_NS::LogicalNode::GetStatus () noexcept const
```




<hr>



### function GetType 

```C++
virtual SR_NODISCARD LogicalNodeType SR_SRLM_NS::LogicalNode::GetType () noexcept const = 0
```




<hr>



### function HasErrors 

```C++
inline SR_NODISCARD bool SR_SRLM_NS::LogicalNode::HasErrors () const
```




<hr>



### function InitNode 

```C++
inline virtual void SR_SRLM_NS::LogicalNode::InitNode () 
```




<hr>



### function InitValues 

```C++
inline virtual void SR_SRLM_NS::LogicalNode::InitValues () 
```




<hr>



### function IsDirty 

```C++
inline virtual SR_NODISCARD bool SR_SRLM_NS::LogicalNode::IsDirty () noexcept const
```




<hr>



### function IsEntryPoint 

```C++
inline virtual SR_NODISCARD bool SR_SRLM_NS::LogicalNode::IsEntryPoint () noexcept const
```




<hr>



### function IsNeedPostRepeat 

```C++
inline virtual SR_NODISCARD bool SR_SRLM_NS::LogicalNode::IsNeedPostRepeat () const
```




<hr>



### function IsNeedRepeat 

```C++
inline virtual SR_NODISCARD bool SR_SRLM_NS::LogicalNode::IsNeedRepeat () const
```




<hr>



### function IsSuccessfullyCompleted 

```C++
SR_NODISCARD bool SR_SRLM_NS::LogicalNode::IsSuccessfullyCompleted () noexcept const
```




<hr>



### function MarkDirty 

```C++
virtual void SR_SRLM_NS::LogicalNode::MarkDirty () 
```




<hr>



### function RemoveInput 

```C++
void SR_SRLM_NS::LogicalNode::RemoveInput (
    uint32_t index
) 
```




<hr>



### function RemoveInputConnection 

```C++
void SR_SRLM_NS::LogicalNode::RemoveInputConnection (
    LogicalNode * pNode,
    uint32_t pinIndex
) 
```




<hr>



### function RemoveOutput 

```C++
void SR_SRLM_NS::LogicalNode::RemoveOutput (
    uint32_t index
) 
```




<hr>



### function RemoveOutputConnection 

```C++
void SR_SRLM_NS::LogicalNode::RemoveOutputConnection (
    LogicalNode * pNode,
    uint32_t pinIndex
) 
```




<hr>



### function Reset 

```C++
virtual void SR_SRLM_NS::LogicalNode::Reset () 
```




<hr>



### function ResetInputFlows 

```C++
void SR_SRLM_NS::LogicalNode::ResetInputFlows () 
```




<hr>



### function ResetOutputFlows 

```C++
void SR_SRLM_NS::LogicalNode::ResetOutputFlows () 
```




<hr>



### function ResetStatus 

```C++
void SR_SRLM_NS::LogicalNode::ResetStatus () 
```




<hr>



### function SaveXml 

```C++
virtual void SR_SRLM_NS::LogicalNode::SaveXml (
    SR_XML_NS::Node & xmlNode
) 
```




<hr>



### function SetInput 

```C++
virtual void SR_SRLM_NS::LogicalNode::SetInput (
    const DataType * pInput,
    uint32_t index
) 
```




<hr>



### function SetMachine 

```C++
inline void SR_SRLM_NS::LogicalNode::SetMachine (
    LogicalMachine * pMachine
) 
```




<hr>



### function SetNodeIndex 

```C++
inline void SR_SRLM_NS::LogicalNode::SetNodeIndex (
    uint32_t index
) 
```




<hr>



### function ~LogicalNode 

```C++
SR_SRLM_NS::LogicalNode::~LogicalNode () override
```




<hr>
## Public Static Functions Documentation




### function LoadXml 

```C++
static SR_NODISCARD LogicalNode * SR_SRLM_NS::LogicalNode::LoadXml (
    const SR_XML_NS::Node & xmlNode
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_inputs 

```C++
Pins SR_SRLM_NS::LogicalNode::m_inputs;
```




<hr>



### variable m\_machine 

```C++
LogicalMachine* SR_SRLM_NS::LogicalNode::m_machine;
```




<hr>



### variable m\_nodeIndex 

```C++
uint32_t SR_SRLM_NS::LogicalNode::m_nodeIndex;
```




<hr>



### variable m\_outputs 

```C++
Pins SR_SRLM_NS::LogicalNode::m_outputs;
```




<hr>



### variable m\_status 

```C++
LogicalNodeStatus SR_SRLM_NS::LogicalNode::m_status;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/SRLM/LogicalNode.h`

