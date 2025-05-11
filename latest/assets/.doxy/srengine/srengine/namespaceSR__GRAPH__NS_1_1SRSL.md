

# Namespace SR\_GRAPH\_NS::SRSL



[**Namespace List**](namespaces.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**SRSL**](namespaceSR__GRAPH__NS_1_1SRSL.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**SRSLFunc**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLFunc.md) <br> |
| class | [**SRSLLoader**](classSR__GRAPH__NS_1_1SRSL_1_1SRSLLoader.md) <br> |
| struct | [**SRSLParseData**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLParseData.md) <br> |
| struct | [**SRSLStage**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLStage.md) <br> |
| struct | [**SRSLStruct**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLStruct.md) <br> |
| struct | [**SRSLUnit**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLUnit.md) <br> |
| struct | [**SRSLVariable**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLVariable.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; std::string &gt;::const\_iterator | [**CodeIter**](#typedef-codeiter)  <br> |
| typedef uint32\_t | [**RequireBits**](#typedef-requirebits)  <br> |
| typedef std::vector&lt; std::string &gt; | [**SRSLCode**](#typedef-srslcode)  <br> |
| typedef std::list&lt; [**SRSLFunc**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLFunc.md) &gt; | [**SRSLFunctions**](#typedef-srslfunctions)  <br> |
| typedef std::map&lt; ShaderStage, [**SRSLStage**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLStage.md) &gt; | [**SRSLStages**](#typedef-srslstages)  <br> |
| typedef std::list&lt; [**SRSLStruct**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLStruct.md) &gt; | [**SRSLStructs**](#typedef-srslstructs)  <br> |
| typedef std::map&lt; std::string, [**SRSLVariable**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLVariable.md) &gt; | [**SRSLVariables**](#typedef-srslvariables)  <br> |
| typedef std::list&lt; std::string &gt; | [**SRSLVars**](#typedef-srslvars)  <br> |
| typedef uint32\_t | [**VertexAttributeBits**](#typedef-vertexattributebits)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**GenerateFunctions**](#function-generatefunctions) (const SRSLFunctions & functions, const std::string & callFrom) <br> |
|  std::optional&lt; [**SRSLParseData**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLParseData.md) &gt; | [**Parse**](#function-parse) (SRSLCode & code) <br> |
|  bool | [**PreProcess**](#function-preprocess) (SRSLCode & code, std::map&lt; std::string, std::string &gt; defines) <br> |
|  bool | [**RemoveComments**](#function-removecomments) (SRSLCode & code) <br> |




























## Public Types Documentation




### typedef CodeIter 

```C++
typedef std::vector<std::string>::const_iterator SR_GRAPH_NS::SRSL::CodeIter;
```




<hr>



### typedef RequireBits 

```C++
typedef uint32_t SR_GRAPH_NS::SRSL::RequireBits;
```




<hr>



### typedef SRSLCode 

```C++
typedef std::vector<std::string> SR_GRAPH_NS::SRSL::SRSLCode;
```




<hr>



### typedef SRSLFunctions 

```C++
typedef std::list<SRSLFunc> SR_GRAPH_NS::SRSL::SRSLFunctions;
```




<hr>



### typedef SRSLStages 

```C++
typedef std::map<ShaderStage, SRSLStage> SR_GRAPH_NS::SRSL::SRSLStages;
```




<hr>



### typedef SRSLStructs 

```C++
typedef std::list<SRSLStruct> SR_GRAPH_NS::SRSL::SRSLStructs;
```




<hr>



### typedef SRSLVariables 

```C++
typedef std::map<std::string, SRSLVariable> SR_GRAPH_NS::SRSL::SRSLVariables;
```




<hr>



### typedef SRSLVars 

```C++
typedef std::list<std::string> SR_GRAPH_NS::SRSL::SRSLVars;
```




<hr>



### typedef VertexAttributeBits 

```C++
typedef uint32_t SR_GRAPH_NS::SRSL::VertexAttributeBits;
```




<hr>
## Public Functions Documentation




### function GenerateFunctions 

```C++
std::string SR_GRAPH_NS::SRSL::GenerateFunctions (
    const SRSLFunctions & functions,
    const std::string & callFrom
) 
```




<hr>



### function Parse 

```C++
std::optional< SRSLParseData > SR_GRAPH_NS::SRSL::Parse (
    SRSLCode & code
) 
```




<hr>



### function PreProcess 

```C++
bool SR_GRAPH_NS::SRSL::PreProcess (
    SRSLCode & code,
    std::map< std::string, std::string > defines
) 
```




<hr>



### function RemoveComments 

```C++
bool SR_GRAPH_NS::SRSL::RemoveComments (
    SRSLCode & code
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Loaders/SRSL.h`

