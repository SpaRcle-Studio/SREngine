

# Struct SR\_SRSL\_NS::SRSLMessage



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLMessage**](structSR__SRSL__NS_1_1SRSLMessage.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  SRSLReturnCode | [**code**](#variable-code)   = `SRSLReturnCode::Unknown`<br> |
|  std::string | [**description**](#variable-description)  <br> |
|  uint16\_t | [**fileIndex**](#variable-fileindex)   = `SR\_UINT16\_MAX`<br> |
|  LexemKind | [**lexemKind**](#variable-lexemkind)   = `LexemKind::Unknown`<br> |
|  uint64\_t | [**position**](#variable-position)   = `SR\_UINT64\_MAX`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SRSLMessage**](#function-srslmessage-13) (SRSLReturnCode code) <br> |
|   | [**SRSLMessage**](#function-srslmessage-23) (SRSLReturnCode code, const [**Lexem**](structSR__SRSL__NS_1_1Lexem.md) & lexem) <br> |
|   | [**SRSLMessage**](#function-srslmessage-33) (SRSLReturnCode code, const [**Lexem**](structSR__SRSL__NS_1_1Lexem.md) \* pLexem) <br> |
|  [**SRSLMessage**](structSR__SRSL__NS_1_1SRSLMessage.md) & | [**SetDescription**](#function-setdescription) (const std::string & text) <br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) (const std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & files, uint8\_t tab) const<br> |




























## Public Attributes Documentation




### variable code 

```C++
SRSLReturnCode SR_SRSL_NS::SRSLMessage::code;
```




<hr>



### variable description 

```C++
std::string SR_SRSL_NS::SRSLMessage::description;
```




<hr>



### variable fileIndex 

```C++
uint16_t SR_SRSL_NS::SRSLMessage::fileIndex;
```




<hr>



### variable lexemKind 

```C++
LexemKind SR_SRSL_NS::SRSLMessage::lexemKind;
```




<hr>



### variable position 

```C++
uint64_t SR_SRSL_NS::SRSLMessage::position;
```




<hr>
## Public Functions Documentation




### function SRSLMessage [1/3]

```C++
inline SR_SRSL_NS::SRSLMessage::SRSLMessage (
    SRSLReturnCode code
) 
```



NOLINT 


        

<hr>



### function SRSLMessage [2/3]

```C++
inline SR_SRSL_NS::SRSLMessage::SRSLMessage (
    SRSLReturnCode code,
    const Lexem & lexem
) 
```




<hr>



### function SRSLMessage [3/3]

```C++
inline SR_SRSL_NS::SRSLMessage::SRSLMessage (
    SRSLReturnCode code,
    const Lexem * pLexem
) 
```




<hr>



### function SetDescription 

```C++
inline SRSLMessage & SR_SRSL_NS::SRSLMessage::SetDescription (
    const std::string & text
) 
```




<hr>



### function ToString 

```C++
inline SR_NODISCARD std::string SR_SRSL_NS::SRSLMessage::ToString (
    const std::vector< SR_UTILS_NS::StringAtom > & files,
    uint8_t tab
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/SRSL/LexerUtils.h`

