

# Namespace SR\_SRSL\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**GLSLCodeGenerator**](classSR__SRSL__NS_1_1GLSLCodeGenerator.md) <br> |
| class | [**ISRSLCodeGenerator**](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md) <br> |
| struct | [**Lexem**](structSR__SRSL__NS_1_1Lexem.md) <br> |
| struct | [**LocationEntity**](structSR__SRSL__NS_1_1LocationEntity.md) <br> |
| class | [**SRSLAnalyzedTree**](classSR__SRSL__NS_1_1SRSLAnalyzedTree.md) <br> |
| class | [**SRSLAssignExpander**](classSR__SRSL__NS_1_1SRSLAssignExpander.md) <br> |
| class | [**SRSLDecorator**](classSR__SRSL__NS_1_1SRSLDecorator.md) <br> |
| class | [**SRSLDecorators**](classSR__SRSL__NS_1_1SRSLDecorators.md) <br> |
| class | [**SRSLEvaluator**](classSR__SRSL__NS_1_1SRSLEvaluator.md) <br> |
| class | [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) <br> |
| class | [**SRSLForStatement**](classSR__SRSL__NS_1_1SRSLForStatement.md) <br> |
| class | [**SRSLFunction**](classSR__SRSL__NS_1_1SRSLFunction.md) <br> |
| class | [**SRSLIfStatement**](classSR__SRSL__NS_1_1SRSLIfStatement.md) <br> |
| class | [**SRSLLexer**](classSR__SRSL__NS_1_1SRSLLexer.md) <br> |
| class | [**SRSLLexicalAnalyzer**](classSR__SRSL__NS_1_1SRSLLexicalAnalyzer.md) <br> |
| class | [**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md) <br> |
| class | [**SRSLLexicalUnit**](classSR__SRSL__NS_1_1SRSLLexicalUnit.md) <br>_минимальная лексическая единица_  |
| class | [**SRSLMathExpression**](classSR__SRSL__NS_1_1SRSLMathExpression.md) <br> |
| struct | [**SRSLMessage**](structSR__SRSL__NS_1_1SRSLMessage.md) <br> |
| class | [**SRSLPreProcessor**](classSR__SRSL__NS_1_1SRSLPreProcessor.md) <br> |
| class | [**SRSLPseudoCodeGenerator**](classSR__SRSL__NS_1_1SRSLPseudoCodeGenerator.md) <br> |
| class | [**SRSLRefAnalyzer**](classSR__SRSL__NS_1_1SRSLRefAnalyzer.md) <br> |
| struct | [**SRSLResult**](structSR__SRSL__NS_1_1SRSLResult.md) <br> |
| class | [**SRSLReturn**](classSR__SRSL__NS_1_1SRSLReturn.md) <br> |
| struct | [**SRSLSampler**](structSR__SRSL__NS_1_1SRSLSampler.md) <br> |
| class | [**SRSLShader**](classSR__SRSL__NS_1_1SRSLShader.md) <br> |
| class | [**SRSLStructureStatement**](classSR__SRSL__NS_1_1SRSLStructureStatement.md) <br> |
| class | [**SRSLTypeInfo**](classSR__SRSL__NS_1_1SRSLTypeInfo.md) <br> |
| struct | [**SRSLUniformBlock**](structSR__SRSL__NS_1_1SRSLUniformBlock.md) <br> |
| struct | [**SRSLUseStack**](structSR__SRSL__NS_1_1SRSLUseStack.md) <br> |
| class | [**SRSLVariable**](classSR__SRSL__NS_1_1SRSLVariable.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), [**SRSLSampler**](structSR__SRSL__NS_1_1SRSLSampler.md) &gt; | [**SRSLSamplers**](#typedef-srslsamplers)  <br> |
| enum  | [**VertexAttribute**](#enum-vertexattribute)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_INLINE\_STATIC const std::set&lt; std::string &gt; | [**SR\_SRSL\_DEFAULT\_OUT\_LAYERS**](#variable-sr_srsl_default_out_layers)   = `/* multi line expression */`<br> |
|  SR\_INLINE\_STATIC const std::map&lt; std::string, std::string &gt; | [**SR\_SRSL\_DEFAULT\_PUSH\_CONSTANTS**](#variable-sr_srsl_default_push_constants)   = `/* multi line expression */`<br> |
|  SR\_INLINE\_STATIC const std::map&lt; std::string, std::string &gt; | [**SR\_SRSL\_DEFAULT\_SAMPLERS**](#variable-sr_srsl_default_samplers)   = `/* multi line expression */`<br> |
|  SR\_INLINE\_STATIC const std::map&lt; std::string, std::string &gt; | [**SR\_SRSL\_DEFAULT\_SHARED\_UNIFORMS**](#variable-sr_srsl_default_shared_uniforms)   = `/* multi line expression */`<br> |
|  SR\_INLINE\_STATIC const std::map&lt; std::string, std::string &gt; | [**SR\_SRSL\_DEFAULT\_UNIFORMS**](#variable-sr_srsl_default_uniforms)   = `/* multi line expression */`<br> |
|  SR\_INLINE\_STATIC const std::map&lt; ShaderStage, std::string &gt; | [**SR\_SRSL\_ENTRY\_POINTS**](#variable-sr_srsl_entry_points)   = `/* multi line expression */`<br> |
|  SR\_INLINE\_STATIC const std::string | [**SR\_SRSL\_MAIN\_OUT\_LAYER**](#variable-sr_srsl_main_out_layer)   = `"COLOR\_INDEX\_0"`<br> |
|  SR\_INLINE\_STATIC const std::map&lt; ShaderStage, std::string &gt; | [**SR\_SRSL\_STAGE\_EXTENSIONS**](#variable-sr_srsl_stage_extensions)   = `/* multi line expression */`<br> |


## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  SR\_INLINE constexpr char | [**SRSL\_IDENTIFIER\_CHARS**](#variable-srsl_identifier_chars)   = `/* multi line expression */`<br> |
|  SR\_INLINE constexpr char | [**SRSL\_SPACE\_CHARS**](#variable-srsl_space_chars)   = `{ ' ', '\n', '\r', '\t' }`<br> |
|  std::map&lt; std::string, uint64\_t &gt; | [**SR\_SRSL\_TYPE\_SIZE\_TABLE**](#variable-sr_srsl_type_size_table)   = `/* multi line expression */`<br> |
|  std::map&lt; std::string, ShaderVarType &gt; | [**SR\_SRSL\_TYPE\_STRINGS**](#variable-sr_srsl_type_strings)   = `/* multi line expression */`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_INLINE\_STATIC uint64\_t | [**GetTypeSize**](#function-gettypesize) (const std::string & type) <br> |
|  SR\_INLINE\_STATIC bool | [**IsSampler**](#function-issampler) (const std::string & type) <br> |
|  SR\_INLINE\_STATIC bool | [**IsShaderEntryPoint**](#function-isshaderentrypoint) (const std::string & name) <br> |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC std::string | [**LexemsToString**](#function-lexemstostring) (const std::vector&lt; [**Lexem**](structSR__SRSL__NS_1_1Lexem.md) &gt; & lexems) <br> |
|   | [**SR\_ENUM\_NS\_CLASS**](#function-sr_enum_ns_class) (ShaderType, Unknown, Spatial, SpatialCustom, Skinned, PostProcessing, Skybox, Simple, Canvas, Particles, Compute, Line, Text, TextUI, Custom, RayTrace) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (LexemKind, uint16\_t, Unknown, OpeningSquareBracket, ClosingSquareBracket, OpeningAngleBracket, ClosingAngleBracket, OpeningCurlyBracket, ClosingCurlyBracket, OpeningBracket, ClosingBracket, Plus, Minus, Multiply, Divide, Percent, Assign, Semicolon, Dot, Comma, Negation, And, Or, Question, Colon, Tilda, Exponentiation, Integer, Macro, String, Identifier) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (SRSLReturnCode, uint16\_t, Unknown, Success, OutOfBounds, InvalidLexicalTree, UnknownLexem, UnexceptedLexem, UnexceptedDot, InvalidExpression, InvalidComplexExpression, InvalidDecorator, IncompleteExpression, EmptyExpression, InvalidScope, InvalidCall, InvalidIfStatement, UnknownShaderLanguage, InvalidAngleBracket, InvalidAssign, InvalidMathToken, InvalidNumericToken, EmptyToken, InvalidIncrementOrDecrement, InvalidListEnd, WrongMacroName, IncludeNotExists, UnexceptedError, IncludeError, InvalidFunction, InvalidString) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (ShaderLanguage, uint8\_t, PseudoCode, GLSL, HLSL, Metal) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED bool | [**IsIdentifier**](#function-isidentifier) (const std::string & token) noexcept<br> |
|  SR\_MAYBE\_UNUSED bool | [**IsOperator**](#function-isoperator) (const std::string & operation) noexcept<br> |
|  std::string | [**LexemKindToString**](#function-lexemkindtostring) (LexemKind lexem) <br> |


























## Public Types Documentation




### typedef SRSLSamplers 

```C++
typedef std::map<SR_UTILS_NS::StringAtom, SRSLSampler> SR_SRSL_NS::SRSLSamplers;
```




<hr>



### enum VertexAttribute 

```C++
enum SR_SRSL_NS::VertexAttribute {
    SRSL_VERTEX_ATTRIBUTE_AUTO = 0,
    SRSL_VERTEX_ATTRIBUTE_POSITION = 1 << 0,
    SRSL_VERTEX_ATTRIBUTE_UV = 1 << 1,
    SRSL_VERTEX_ATTRIBUTE_NORMAL = 1 << 2,
    SRSL_VERTEX_ATTRIBUTE_TANGENT = 1 << 3,
    SRSL_VERTEX_ATTRIBUTE_BITANGENT = 1 << 4
};
```




<hr>
## Public Attributes Documentation




### variable SR\_SRSL\_DEFAULT\_OUT\_LAYERS 

```C++
SR_INLINE_STATIC const std::set<std::string> SR_SRSL_NS::SR_SRSL_DEFAULT_OUT_LAYERS;
```



NOLINT 


        

<hr>



### variable SR\_SRSL\_DEFAULT\_PUSH\_CONSTANTS 

```C++
SR_INLINE_STATIC const std::map<std::string, std::string> SR_SRSL_NS::SR_SRSL_DEFAULT_PUSH_CONSTANTS;
```




<hr>



### variable SR\_SRSL\_DEFAULT\_SAMPLERS 

```C++
SR_INLINE_STATIC const std::map<std::string, std::string> SR_SRSL_NS::SR_SRSL_DEFAULT_SAMPLERS;
```




<hr>



### variable SR\_SRSL\_DEFAULT\_SHARED\_UNIFORMS 

```C++
SR_INLINE_STATIC const std::map<std::string, std::string> SR_SRSL_NS::SR_SRSL_DEFAULT_SHARED_UNIFORMS;
```




<hr>



### variable SR\_SRSL\_DEFAULT\_UNIFORMS 

```C++
SR_INLINE_STATIC const std::map<std::string, std::string> SR_SRSL_NS::SR_SRSL_DEFAULT_UNIFORMS;
```




<hr>



### variable SR\_SRSL\_ENTRY\_POINTS 

```C++
SR_INLINE_STATIC const std::map<ShaderStage, std::string> SR_SRSL_NS::SR_SRSL_ENTRY_POINTS;
```




<hr>



### variable SR\_SRSL\_MAIN\_OUT\_LAYER 

```C++
SR_INLINE_STATIC const std::string SR_SRSL_NS::SR_SRSL_MAIN_OUT_LAYER;
```




<hr>



### variable SR\_SRSL\_STAGE\_EXTENSIONS 

```C++
SR_INLINE_STATIC const std::map<ShaderStage, std::string> SR_SRSL_NS::SR_SRSL_STAGE_EXTENSIONS;
```




<hr>
## Public Static Attributes Documentation




### variable SRSL\_IDENTIFIER\_CHARS 

```C++
SR_INLINE constexpr char SR_SRSL_NS::SRSL_IDENTIFIER_CHARS[];
```




<hr>



### variable SRSL\_SPACE\_CHARS 

```C++
SR_INLINE constexpr char SR_SRSL_NS::SRSL_SPACE_CHARS[];
```




<hr>



### variable SR\_SRSL\_TYPE\_SIZE\_TABLE 

```C++
std::map<std::string, uint64_t> SR_SRSL_NS::SR_SRSL_TYPE_SIZE_TABLE;
```




<hr>



### variable SR\_SRSL\_TYPE\_STRINGS 

```C++
std::map<std::string, ShaderVarType> SR_SRSL_NS::SR_SRSL_TYPE_STRINGS;
```




<hr>
## Public Functions Documentation




### function GetTypeSize 

```C++
SR_INLINE_STATIC uint64_t SR_SRSL_NS::GetTypeSize (
    const std::string & type
) 
```




<hr>



### function IsSampler 

```C++
SR_INLINE_STATIC bool SR_SRSL_NS::IsSampler (
    const std::string & type
) 
```




<hr>



### function IsShaderEntryPoint 

```C++
SR_INLINE_STATIC bool SR_SRSL_NS::IsShaderEntryPoint (
    const std::string & name
) 
```




<hr>



### function LexemsToString 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC std::string SR_SRSL_NS::LexemsToString (
    const std::vector< Lexem > & lexems
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS 

```C++
SR_SRSL_NS::SR_ENUM_NS_CLASS (
    ShaderType,
    Unknown,
    Spatial,
    SpatialCustom,
    Skinned,
    PostProcessing,
    Skybox,
    Simple,
    Canvas,
    Particles,
    Compute,
    Line,
    Text,
    TextUI,
    Custom,
    RayTrace
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_SRSL_NS::SR_ENUM_NS_CLASS_T (
    LexemKind,
    uint16_t,
    Unknown,
    OpeningSquareBracket,
    ClosingSquareBracket,
    OpeningAngleBracket,
    ClosingAngleBracket,
    OpeningCurlyBracket,
    ClosingCurlyBracket,
    OpeningBracket,
    ClosingBracket,
    Plus,
    Minus,
    Multiply,
    Divide,
    Percent,
    Assign,
    Semicolon,
    Dot,
    Comma,
    Negation,
    And,
    Or,
    Question,
    Colon,
    Tilda,
    Exponentiation,
    Integer,
    Macro,
    String,
    Identifier
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_SRSL_NS::SR_ENUM_NS_CLASS_T (
    SRSLReturnCode,
    uint16_t,
    Unknown,
    Success,
    OutOfBounds,
    InvalidLexicalTree,
    UnknownLexem,
    UnexceptedLexem,
    UnexceptedDot,
    InvalidExpression,
    InvalidComplexExpression,
    InvalidDecorator,
    IncompleteExpression,
    EmptyExpression,
    InvalidScope,
    InvalidCall,
    InvalidIfStatement,
    UnknownShaderLanguage,
    InvalidAngleBracket,
    InvalidAssign,
    InvalidMathToken,
    InvalidNumericToken,
    EmptyToken,
    InvalidIncrementOrDecrement,
    InvalidListEnd,
    WrongMacroName,
    IncludeNotExists,
    UnexceptedError,
    IncludeError,
    InvalidFunction,
    InvalidString
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_SRSL_NS::SR_ENUM_NS_CLASS_T (
    ShaderLanguage,
    uint8_t,
    PseudoCode,
    GLSL,
    HLSL,
    Metal
) 
```




<hr>
## Public Static Functions Documentation




### function IsIdentifier 

```C++
static SR_MAYBE_UNUSED bool SR_SRSL_NS::IsIdentifier (
    const std::string & token
) noexcept
```




<hr>



### function IsOperator 

```C++
static SR_MAYBE_UNUSED bool SR_SRSL_NS::IsOperator (
    const std::string & operation
) noexcept
```




<hr>



### function LexemKindToString 

```C++
static std::string SR_SRSL_NS::LexemKindToString (
    LexemKind lexem
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/MeshCluster.h`

