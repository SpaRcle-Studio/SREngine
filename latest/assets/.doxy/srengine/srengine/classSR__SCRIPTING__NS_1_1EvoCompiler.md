

# Class SR\_SCRIPTING\_NS::EvoCompiler



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**EvoCompiler**](classSR__SCRIPTING__NS_1_1EvoCompiler.md)








Inherits the following classes: [SR\_SCRIPTING\_NS::Compiler](classSR__SCRIPTING__NS_1_1Compiler.md),  EvoScript::Compiler


Inherited by the following classes: [SR\_SCRIPTING\_NS::GlobalEvoCompiler](classSR__SCRIPTING__NS_1_1GlobalEvoCompiler.md)








































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EvoCompiler**](#function-evocompiler) (std::string cachePath) <br> |
|  SR\_NODISCARD EvoScript::CastingGen \* | [**GetCasting**](#function-getcasting) () const<br> |
|  SR\_NODISCARD EvoScript::AddressTableGen \* | [**GetGenerator**](#function-getgenerator) () const<br> |
| virtual bool | [**Init**](#function-init) () override<br> |
|   | [**~EvoCompiler**](#function-evocompiler) () override<br> |


## Public Functions inherited from SR_SCRIPTING_NS::Compiler

See [SR\_SCRIPTING\_NS::Compiler](classSR__SCRIPTING__NS_1_1Compiler.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**Init**](classSR__SCRIPTING__NS_1_1Compiler.md#function-init) () = 0<br> |
|   | [**~Compiler**](classSR__SCRIPTING__NS_1_1Compiler.md#function-compiler) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






















## Protected Attributes inherited from SR_SCRIPTING_NS::Compiler

See [SR\_SCRIPTING\_NS::Compiler](classSR__SCRIPTING__NS_1_1Compiler.md)

| Type | Name |
| ---: | :--- |
|  Mutex | [**m\_mutex**](classSR__SCRIPTING__NS_1_1Compiler.md#variable-m_mutex)   = `Mutex()`<br> |
















































## Protected Functions inherited from SR_SCRIPTING_NS::Compiler

See [SR\_SCRIPTING\_NS::Compiler](classSR__SCRIPTING__NS_1_1Compiler.md)

| Type | Name |
| ---: | :--- |
|   | [**Compiler**](classSR__SCRIPTING__NS_1_1Compiler.md#function-compiler) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |








## Public Functions Documentation




### function EvoCompiler 

```C++
explicit SR_SCRIPTING_NS::EvoCompiler::EvoCompiler (
    std::string cachePath
) 
```




<hr>



### function GetCasting 

```C++
inline SR_NODISCARD EvoScript::CastingGen * SR_SCRIPTING_NS::EvoCompiler::GetCasting () const
```




<hr>



### function GetGenerator 

```C++
SR_NODISCARD EvoScript::AddressTableGen * SR_SCRIPTING_NS::EvoCompiler::GetGenerator () const
```




<hr>



### function Init 

```C++
virtual bool SR_SCRIPTING_NS::EvoCompiler::Init () override
```



Implements [*SR\_SCRIPTING\_NS::Compiler::Init*](classSR__SCRIPTING__NS_1_1Compiler.md#function-init)


<hr>



### function ~EvoCompiler 

```C++
SR_SCRIPTING_NS::EvoCompiler::~EvoCompiler () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Impl/EvoCompiler.h`

