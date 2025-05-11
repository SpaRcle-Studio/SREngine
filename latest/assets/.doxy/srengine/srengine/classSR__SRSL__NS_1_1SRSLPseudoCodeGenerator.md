

# Class SR\_SRSL\_NS::SRSLPseudoCodeGenerator



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLPseudoCodeGenerator**](classSR__SRSL__NS_1_1SRSLPseudoCodeGenerator.md)








Inherits the following classes: [SR\_SRSL\_NS::ISRSLCodeGenerator](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)
















## Public Types inherited from SR_SRSL_NS::ISRSLCodeGenerator

See [SR\_SRSL\_NS::ISRSLCodeGenerator](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md)

| Type | Name |
| ---: | :--- |
| typedef std::pair&lt; [**SRSLResult**](structSR__SRSL__NS_1_1SRSLResult.md), std::map&lt; ShaderStage, std::string &gt; &gt; | [**SRSLCodeGenRes**](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md#typedef-srslcodegenres)  <br> |


































































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SRSLCodeGenRes | [**GenerateStages**](#function-generatestages) (const [**SRSLShader**](classSR__SRSL__NS_1_1SRSLShader.md) \* pShader) override<br> |






## Public Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|   | [**~SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






## Public Static Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySingleton**](classSR__UTILS__NS_1_1Singleton.md#function-destroysingleton) () <br> |
|  SR\_MAYBE\_UNUSED std::recursive\_mutex & | [**GetMutex**](classSR__UTILS__NS_1_1Singleton.md#function-getmutex) () noexcept<br> |
|  SR\_MAYBE\_UNUSED T & | [**Instance**](classSR__UTILS__NS_1_1Singleton.md#function-instance) () noexcept<br> |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](classSR__UTILS__NS_1_1Singleton.md#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-unlocksingleton) () noexcept<br> |




























## Protected Attributes inherited from SR_SRSL_NS::ISRSLCodeGenerator

See [SR\_SRSL\_NS::ISRSLCodeGenerator](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md)

| Type | Name |
| ---: | :--- |
|  [**SRSLResult**](structSR__SRSL__NS_1_1SRSLResult.md) | [**m\_result**](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md#variable-m_result)   = `[**SRSLResult**](structSR__SRSL__NS_1_1SRSLResult.md)()`<br> |




## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |










































































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD std::string | [**GenerateDecorators**](#function-generatedecorators) ([**SRSLDecorators**](classSR__SRSL__NS_1_1SRSLDecorators.md) \* pDecorators, int32\_t deep) const<br> |
| virtual SR\_NODISCARD std::string | [**GenerateExpression**](#function-generateexpression) ([**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pExpr, int32\_t deep) const<br> |
| virtual SR\_NODISCARD std::string | [**GenerateFunction**](#function-generatefunction) ([**SRSLFunction**](classSR__SRSL__NS_1_1SRSLFunction.md) \* pFunction, int32\_t deep) const<br> |
| virtual SR\_NODISCARD std::string | [**GenerateLexicalTree**](#function-generatelexicaltree) ([**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md) \* pLexicalTree, int32\_t deep) const<br> |
| virtual SR\_NODISCARD std::string | [**GenerateName**](#function-generatename) ([**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pExpr, int32\_t deep) const<br> |
| virtual SR\_NODISCARD std::string | [**GenerateTab**](#function-generatetab) (int32\_t deep) const<br> |
| virtual SR\_NODISCARD std::string | [**GenerateType**](#function-generatetype) ([**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pExpr, int32\_t deep) const<br> |
| virtual SR\_NODISCARD std::string | [**GenerateVariable**](#function-generatevariable) ([**SRSLVariable**](classSR__SRSL__NS_1_1SRSLVariable.md) \* pVariable, int32\_t deep) const<br> |
|   | [**SRSLPseudoCodeGenerator**](#function-srslpseudocodegenerator) () = default<br> |
|   | [**~SRSLPseudoCodeGenerator**](#function-srslpseudocodegenerator) () override<br> |


## Protected Functions inherited from SR_SRSL_NS::ISRSLCodeGenerator

See [SR\_SRSL\_NS::ISRSLCodeGenerator](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md)

| Type | Name |
| ---: | :--- |
|  void | [**Clear**](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md#function-clear) () <br> |
| virtual SR\_NODISCARD SRSLCodeGenRes | [**GenerateStages**](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md#function-generatestages) (const [**SRSLShader**](classSR__SRSL__NS_1_1SRSLShader.md) \* pShader) = 0<br> |
|   | [**ISRSLCodeGenerator**](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md#function-isrslcodegenerator) () = default<br> |
| virtual  | [**~ISRSLCodeGenerator**](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md#function-isrslcodegenerator) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|   | [**Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () <br> |
|   | [**~Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSingletonName**](classSR__UTILS__NS_1_1SingletonBase.md#function-getsingletonname) () noexcept const = 0<br> |
| virtual void | [**InitSingleton**](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton) () <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed) () const<br> |
| virtual void | [**OnSingletonDestroy**](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy) () <br> |
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |












## Public Functions Documentation




### function GenerateStages 

```C++
virtual SR_NODISCARD SRSLCodeGenRes SR_SRSL_NS::SRSLPseudoCodeGenerator::GenerateStages (
    const SRSLShader * pShader
) override
```



Implements [*SR\_SRSL\_NS::ISRSLCodeGenerator::GenerateStages*](classSR__SRSL__NS_1_1ISRSLCodeGenerator.md#function-generatestages)


<hr>
## Protected Functions Documentation




### function GenerateDecorators 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLPseudoCodeGenerator::GenerateDecorators (
    SRSLDecorators * pDecorators,
    int32_t deep
) const
```




<hr>



### function GenerateExpression 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLPseudoCodeGenerator::GenerateExpression (
    SRSLExpr * pExpr,
    int32_t deep
) const
```




<hr>



### function GenerateFunction 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLPseudoCodeGenerator::GenerateFunction (
    SRSLFunction * pFunction,
    int32_t deep
) const
```




<hr>



### function GenerateLexicalTree 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLPseudoCodeGenerator::GenerateLexicalTree (
    SRSLLexicalTree * pLexicalTree,
    int32_t deep
) const
```




<hr>



### function GenerateName 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLPseudoCodeGenerator::GenerateName (
    SRSLExpr * pExpr,
    int32_t deep
) const
```




<hr>



### function GenerateTab 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLPseudoCodeGenerator::GenerateTab (
    int32_t deep
) const
```




<hr>



### function GenerateType 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLPseudoCodeGenerator::GenerateType (
    SRSLExpr * pExpr,
    int32_t deep
) const
```




<hr>



### function GenerateVariable 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLPseudoCodeGenerator::GenerateVariable (
    SRSLVariable * pVariable,
    int32_t deep
) const
```




<hr>



### function SRSLPseudoCodeGenerator 

```C++
SR_SRSL_NS::SRSLPseudoCodeGenerator::SRSLPseudoCodeGenerator () = default
```




<hr>



### function ~SRSLPseudoCodeGenerator 

```C++
SR_SRSL_NS::SRSLPseudoCodeGenerator::~SRSLPseudoCodeGenerator () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/PseudoCodeGenerator.h`

