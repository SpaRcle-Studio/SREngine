

# Class EvoScript::Compiler



[**ClassList**](annotated.md) **>** [**EvoScript**](namespaceEvoScript.md) **>** [**Compiler**](classEvoScript_1_1Compiler.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_SCRIPTING\_NS::EvoCompiler](classSR__SCRIPTING__NS_1_1EvoCompiler.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddIncludePath**](#function-addincludepath) (const std::string & path) <br> |
|  [**IState**](classEvoScript_1_1IState.md) \* | [**AllocateState**](#function-allocatestate) (const std::string & path) <br> |
|  bool | [**Compile**](#function-compile) ([**Script**](classEvoScript_1_1Script.md) \* script) <br> |
|   | [**Compiler**](#function-compiler) (std::string cachePath) <br> |
|  SR\_NODISCARD std::string | [**GetAPIVersion**](#function-getapiversion) () const<br> |
|  SR\_NODISCARD std::string | [**GetCachePath**](#function-getcachepath) () const<br> |
|  SR\_NODISCARD std::string | [**GetCompilerPath**](#function-getcompilerpath) () const<br> |
|  bool | [**Load**](#function-load) ([**Script**](classEvoScript_1_1Script.md) \* script) <br> |
|  bool | [**LoadState**](#function-loadstate) ([**IState**](classEvoScript_1_1IState.md) \* state) <br> |
|  void | [**SetApiVersion**](#function-setapiversion) (std::string version) <br> |
|  void | [**SetCompilePDB**](#function-setcompilepdb) (bool value) <br> |
|  void | [**SetCompilerPath**](#function-setcompilerpath) (const std::string & compilerPath) <br> |
|  void | [**SetMultiInstances**](#function-setmultiinstances) (bool enabled) <br> |
|  bool | [**TryLoad**](#function-tryload) ([**Script**](classEvoScript_1_1Script.md) \* script) <br> |
|   | [**~Compiler**](#function-compiler) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function AddIncludePath 

```C++
void EvoScript::Compiler::AddIncludePath (
    const std::string & path
) 
```




<hr>



### function AllocateState 

```C++
IState * EvoScript::Compiler::AllocateState (
    const std::string & path
) 
```




<hr>



### function Compile 

```C++
bool EvoScript::Compiler::Compile (
    Script * script
) 
```




<hr>



### function Compiler 

```C++
explicit EvoScript::Compiler::Compiler (
    std::string cachePath
) 
```




<hr>



### function GetAPIVersion 

```C++
inline SR_NODISCARD std::string EvoScript::Compiler::GetAPIVersion () const
```




<hr>



### function GetCachePath 

```C++
inline SR_NODISCARD std::string EvoScript::Compiler::GetCachePath () const
```




<hr>



### function GetCompilerPath 

```C++
inline SR_NODISCARD std::string EvoScript::Compiler::GetCompilerPath () const
```




<hr>



### function Load 

```C++
bool EvoScript::Compiler::Load (
    Script * script
) 
```




<hr>



### function LoadState 

```C++
bool EvoScript::Compiler::LoadState (
    IState * state
) 
```




<hr>



### function SetApiVersion 

```C++
void EvoScript::Compiler::SetApiVersion (
    std::string version
) 
```




<hr>



### function SetCompilePDB 

```C++
inline void EvoScript::Compiler::SetCompilePDB (
    bool value
) 
```




<hr>



### function SetCompilerPath 

```C++
inline void EvoScript::Compiler::SetCompilerPath (
    const std::string & compilerPath
) 
```




<hr>



### function SetMultiInstances 

```C++
inline void EvoScript::Compiler::SetMultiInstances (
    bool enabled
) 
```




<hr>



### function TryLoad 

```C++
bool EvoScript::Compiler::TryLoad (
    Script * script
) 
```




<hr>



### function ~Compiler 

```C++
EvoScript::Compiler::~Compiler () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Scripting/inc/Scripting/Old/Compilation/Compiler.h`

