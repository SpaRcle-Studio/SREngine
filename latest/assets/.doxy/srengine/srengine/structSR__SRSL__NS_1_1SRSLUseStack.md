

# Struct SR\_SRSL\_NS::SRSLUseStack



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLUseStack**](structSR__SRSL__NS_1_1SRSLUseStack.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::shared\_ptr&lt; [**SRSLUseStack**](structSR__SRSL__NS_1_1SRSLUseStack.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::map&lt; std::string, SRSLUseStack::Ptr &gt; | [**functions**](#variable-functions)  <br> |
|  std::set&lt; std::string &gt; | [**variables**](#variable-variables)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Concat**](#function-concat) (const SRSLUseStack::Ptr & pOther) <br> |
|  SR\_NODISCARD SRSLUseStack::Ptr | [**FindFunction**](#function-findfunction) (const std::string & name) const<br> |
|  SR\_NODISCARD bool | [**IsFunctionUsed**](#function-isfunctionused) (const std::string & name) const<br> |
|  SR\_NODISCARD bool | [**IsStructUsed**](#function-isstructused) (const std::string & name) const<br> |
|  SR\_NODISCARD bool | [**IsVariableUsed**](#function-isvariableused) (const std::string & name) const<br> |
|  SR\_NODISCARD bool | [**IsVariableUsedInEntryPoints**](#function-isvariableusedinentrypoints) (const std::string & name) const<br> |
|  SR\_NODISCARD std::set&lt; SR\_GRAPH\_NS::ShaderStage &gt; | [**IsVariableUsedInEntryPointsExt**](#function-isvariableusedinentrypointsext) (const std::string & name) const<br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) (int32\_t deep) const<br> |




























## Public Types Documentation




### typedef Ptr 

```C++
using SR_SRSL_NS::SRSLUseStack::Ptr =  std::shared_ptr<SRSLUseStack>;
```




<hr>
## Public Attributes Documentation




### variable functions 

```C++
std::map<std::string, SRSLUseStack::Ptr> SR_SRSL_NS::SRSLUseStack::functions;
```




<hr>



### variable variables 

```C++
std::set<std::string> SR_SRSL_NS::SRSLUseStack::variables;
```




<hr>
## Public Functions Documentation




### function Concat 

```C++
void SR_SRSL_NS::SRSLUseStack::Concat (
    const SRSLUseStack::Ptr & pOther
) 
```




<hr>



### function FindFunction 

```C++
SR_NODISCARD SRSLUseStack::Ptr SR_SRSL_NS::SRSLUseStack::FindFunction (
    const std::string & name
) const
```




<hr>



### function IsFunctionUsed 

```C++
SR_NODISCARD bool SR_SRSL_NS::SRSLUseStack::IsFunctionUsed (
    const std::string & name
) const
```




<hr>



### function IsStructUsed 

```C++
SR_NODISCARD bool SR_SRSL_NS::SRSLUseStack::IsStructUsed (
    const std::string & name
) const
```




<hr>



### function IsVariableUsed 

```C++
SR_NODISCARD bool SR_SRSL_NS::SRSLUseStack::IsVariableUsed (
    const std::string & name
) const
```




<hr>



### function IsVariableUsedInEntryPoints 

```C++
SR_NODISCARD bool SR_SRSL_NS::SRSLUseStack::IsVariableUsedInEntryPoints (
    const std::string & name
) const
```




<hr>



### function IsVariableUsedInEntryPointsExt 

```C++
SR_NODISCARD std::set< SR_GRAPH_NS::ShaderStage > SR_SRSL_NS::SRSLUseStack::IsVariableUsedInEntryPointsExt (
    const std::string & name
) const
```




<hr>



### function ToString 

```C++
SR_NODISCARD std::string SR_SRSL_NS::SRSLUseStack::ToString (
    int32_t deep
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/RefAnalyzer.h`

