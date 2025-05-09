

# Class SR\_SCRIPTING\_NS::EvoCompiler



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**EvoCompiler**](classSR__SCRIPTING__NS_1_1EvoCompiler.md)








Inherits the following classes: [SR\_SCRIPTING\_NS::Compiler](classSR__SCRIPTING__NS_1_1Compiler.md),  [EvoScript::Compiler](classEvoScript_1_1Compiler.md)


Inherited by the following classes: [SR\_SCRIPTING\_NS::GlobalEvoCompiler](classSR__SCRIPTING__NS_1_1GlobalEvoCompiler.md)
















































































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EvoCompiler**](#function-evocompiler) (std::string cachePath) <br> |
|  SR\_NODISCARD [**EvoScript::CastingGen**](classEvoScript_1_1CastingGen.md) \* | [**GetCasting**](#function-getcasting) () const<br> |
|  SR\_NODISCARD [**EvoScript::AddressTableGen**](classEvoScript_1_1AddressTableGen.md) \* | [**GetGenerator**](#function-getgenerator) () const<br> |
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


## Public Functions inherited from EvoScript::Compiler

See [EvoScript::Compiler](classEvoScript_1_1Compiler.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddIncludePath**](classEvoScript_1_1Compiler.md#function-addincludepath) (const std::string & path) <br> |
|  [**IState**](classEvoScript_1_1IState.md) \* | [**AllocateState**](classEvoScript_1_1Compiler.md#function-allocatestate) (const std::string & path) <br> |
|  bool | [**Compile**](classEvoScript_1_1Compiler.md#function-compile) ([**Script**](classEvoScript_1_1Script.md) \* script) <br> |
|   | [**Compiler**](classEvoScript_1_1Compiler.md#function-compiler) (std::string cachePath) <br> |
|  SR\_NODISCARD std::string | [**GetAPIVersion**](classEvoScript_1_1Compiler.md#function-getapiversion) () const<br> |
|  SR\_NODISCARD std::string | [**GetCachePath**](classEvoScript_1_1Compiler.md#function-getcachepath) () const<br> |
|  SR\_NODISCARD std::string | [**GetCompilerPath**](classEvoScript_1_1Compiler.md#function-getcompilerpath) () const<br> |
|  bool | [**Load**](classEvoScript_1_1Compiler.md#function-load) ([**Script**](classEvoScript_1_1Script.md) \* script) <br> |
|  bool | [**LoadState**](classEvoScript_1_1Compiler.md#function-loadstate) ([**IState**](classEvoScript_1_1IState.md) \* state) <br> |
|  void | [**SetApiVersion**](classEvoScript_1_1Compiler.md#function-setapiversion) (std::string version) <br> |
|  void | [**SetCompilePDB**](classEvoScript_1_1Compiler.md#function-setcompilepdb) (bool value) <br> |
|  void | [**SetCompilerPath**](classEvoScript_1_1Compiler.md#function-setcompilerpath) (const std::string & compilerPath) <br> |
|  void | [**SetMultiInstances**](classEvoScript_1_1Compiler.md#function-setmultiinstances) (bool enabled) <br> |
|  bool | [**TryLoad**](classEvoScript_1_1Compiler.md#function-tryload) ([**Script**](classEvoScript_1_1Script.md) \* script) <br> |
|   | [**~Compiler**](classEvoScript_1_1Compiler.md#function-compiler) () override<br> |


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
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |




## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |












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
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Old/Impl/EvoCompiler.h`

