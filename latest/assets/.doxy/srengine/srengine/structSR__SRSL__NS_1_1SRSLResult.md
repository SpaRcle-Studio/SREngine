

# Struct SR\_SRSL\_NS::SRSLResult



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLResult**](structSR__SRSL__NS_1_1SRSLResult.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::list&lt; [**SRSLMessage**](structSR__SRSL__NS_1_1SRSLMessage.md) &gt; | [**errors**](#variable-errors)  <br> |
|  uint64\_t | [**processedLexems**](#variable-processedlexems)   = `0`<br> |
|  std::list&lt; [**SRSLMessage**](structSR__SRSL__NS_1_1SRSLMessage.md) &gt; | [**warnings**](#variable-warnings)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**SRSLMessage**](structSR__SRSL__NS_1_1SRSLMessage.md) & | [**AddError**](#function-adderror) (const [**SRSLMessage**](structSR__SRSL__NS_1_1SRSLMessage.md) & message) <br> |
|  SR\_NODISCARD bool | [**HasAny**](#function-hasany) () const<br> |
|  SR\_NODISCARD bool | [**HasErrors**](#function-haserrors) () const<br> |
|  SR\_NODISCARD bool | [**HasWarnings**](#function-haswarnings) () const<br> |
|   | [**SRSLResult**](#function-srslresult-13) () = default<br> |
|   | [**SRSLResult**](#function-srslresult-23) (SRSLReturnCode code) <br> |
|   | [**SRSLResult**](#function-srslresult-33) (SRSLReturnCode code, const [**Lexem**](structSR__SRSL__NS_1_1Lexem.md) \* pLexem) <br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) (const std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & files, uint8\_t tab=1) const<br> |




























## Public Attributes Documentation




### variable errors 

```C++
std::list<SRSLMessage> SR_SRSL_NS::SRSLResult::errors;
```




<hr>



### variable processedLexems 

```C++
uint64_t SR_SRSL_NS::SRSLResult::processedLexems;
```




<hr>



### variable warnings 

```C++
std::list<SRSLMessage> SR_SRSL_NS::SRSLResult::warnings;
```




<hr>
## Public Functions Documentation




### function AddError 

```C++
inline SRSLMessage & SR_SRSL_NS::SRSLResult::AddError (
    const SRSLMessage & message
) 
```




<hr>



### function HasAny 

```C++
inline SR_NODISCARD bool SR_SRSL_NS::SRSLResult::HasAny () const
```




<hr>



### function HasErrors 

```C++
inline SR_NODISCARD bool SR_SRSL_NS::SRSLResult::HasErrors () const
```




<hr>



### function HasWarnings 

```C++
inline SR_NODISCARD bool SR_SRSL_NS::SRSLResult::HasWarnings () const
```




<hr>



### function SRSLResult [1/3]

```C++
SR_SRSL_NS::SRSLResult::SRSLResult () = default
```




<hr>



### function SRSLResult [2/3]

```C++
inline SR_SRSL_NS::SRSLResult::SRSLResult (
    SRSLReturnCode code
) 
```




<hr>



### function SRSLResult [3/3]

```C++
inline SR_SRSL_NS::SRSLResult::SRSLResult (
    SRSLReturnCode code,
    const Lexem * pLexem
) 
```




<hr>



### function ToString 

```C++
inline SR_NODISCARD std::string SR_SRSL_NS::SRSLResult::ToString (
    const std::vector< SR_UTILS_NS::StringAtom > & files,
    uint8_t tab=1
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexerUtils.h`

