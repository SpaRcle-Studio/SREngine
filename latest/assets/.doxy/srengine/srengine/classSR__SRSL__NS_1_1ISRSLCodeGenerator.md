

# Class SR\_SRSL\_NS::ISRSLCodeGenerator



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**ISRSLCodeGenerator**](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md)










Inherited by the following classes: [SR\_SRSL\_NS::GLSLCodeGenerator](classSR__SRSL__NS_1_1GLSLCodeGenerator.md),  [SR\_SRSL\_NS::SRSLPseudoCodeGenerator](classSR__SRSL__NS_1_1SRSLPseudoCodeGenerator.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::pair&lt; [**SRSLResult**](structSR__SRSL__NS_1_1SRSLResult.md), std::map&lt; ShaderStage, std::string &gt; &gt; | [**SRSLCodeGenRes**](#typedef-srslcodegenres)  <br> |




























## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**SRSLResult**](structSR__SRSL__NS_1_1SRSLResult.md) | [**m\_result**](#variable-m_result)   = `[**SRSLResult**](structSR__SRSL__NS_1_1SRSLResult.md)()`<br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**Clear**](#function-clear) () <br> |
| virtual SR\_NODISCARD SRSLCodeGenRes | [**GenerateStages**](#function-generatestages) (const [**SRSLShader**](classSR__SRSL__NS_1_1SRSLShader.md) \* pShader) = 0<br> |
|   | [**ISRSLCodeGenerator**](#function-isrslcodegenerator) () = default<br> |
| virtual  | [**~ISRSLCodeGenerator**](#function-isrslcodegenerator) () = default<br> |




## Public Types Documentation




### typedef SRSLCodeGenRes 

```C++
using SR_SRSL_NS::ISRSLCodeGenerator::SRSLCodeGenRes =  std::pair<SRSLResult, std::map<ShaderStage, std::string>>;
```




<hr>
## Protected Attributes Documentation




### variable m\_result 

```C++
SRSLResult SR_SRSL_NS::ISRSLCodeGenerator::m_result;
```




<hr>
## Protected Functions Documentation




### function Clear 

```C++
void SR_SRSL_NS::ISRSLCodeGenerator::Clear () 
```




<hr>



### function GenerateStages 

```C++
virtual SR_NODISCARD SRSLCodeGenRes SR_SRSL_NS::ISRSLCodeGenerator::GenerateStages (
    const SRSLShader * pShader
) = 0
```




<hr>



### function ISRSLCodeGenerator 

```C++
SR_SRSL_NS::ISRSLCodeGenerator::ISRSLCodeGenerator () = default
```




<hr>



### function ~ISRSLCodeGenerator 

```C++
virtual SR_SRSL_NS::ISRSLCodeGenerator::~ISRSLCodeGenerator () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/SRSL/ICodeGenerator.h`

