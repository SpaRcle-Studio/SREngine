

# Struct SR\_SCRIPTING\_NS::CppCodegenModule



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**CppCodegenModule**](structSR__SCRIPTING__NS_1_1CppCodegenModule.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::set&lt; [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) &gt; | [**codeFiles**](#variable-codefiles)  <br> |
|  uint64\_t | [**hash**](#variable-hash)   = `0`<br> |
|  bool | [**isCompiled**](#variable-iscompiled)   = `true`<br> |
|  bool | [**isNeedCodegen**](#variable-isneedcodegen)   = `false`<br> |
|  [**CppScriptModuleInfo**](structSR__SCRIPTING__NS_1_1CppScriptModuleInfo.md) | [**moduleInfo**](#variable-moduleinfo)  <br> |
|  [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**path**](#variable-path)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**CalculateHash**](#function-calculatehash) () <br> |
|  uint64\_t | [**GetCacheHash**](#function-getcachehash) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & cacheFolder) const<br> |
|  bool | [**IsCacheExpired**](#function-iscacheexpired) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & cacheFolder) const<br> |
|  void | [**SaveHash**](#function-savehash) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & cacheFolder) <br> |




























## Public Attributes Documentation




### variable codeFiles 

```C++
std::set<SR_UTILS_NS::Path> SR_SCRIPTING_NS::CppCodegenModule::codeFiles;
```




<hr>



### variable hash 

```C++
uint64_t SR_SCRIPTING_NS::CppCodegenModule::hash;
```




<hr>



### variable isCompiled 

```C++
bool SR_SCRIPTING_NS::CppCodegenModule::isCompiled;
```




<hr>



### variable isNeedCodegen 

```C++
bool SR_SCRIPTING_NS::CppCodegenModule::isNeedCodegen;
```




<hr>



### variable moduleInfo 

```C++
CppScriptModuleInfo SR_SCRIPTING_NS::CppCodegenModule::moduleInfo;
```




<hr>



### variable path 

```C++
SR_UTILS_NS::Path SR_SCRIPTING_NS::CppCodegenModule::path;
```




<hr>
## Public Functions Documentation




### function CalculateHash 

```C++
void SR_SCRIPTING_NS::CppCodegenModule::CalculateHash () 
```




<hr>



### function GetCacheHash 

```C++
uint64_t SR_SCRIPTING_NS::CppCodegenModule::GetCacheHash (
    const SR_UTILS_NS::Path & cacheFolder
) const
```




<hr>



### function IsCacheExpired 

```C++
inline bool SR_SCRIPTING_NS::CppCodegenModule::IsCacheExpired (
    const SR_UTILS_NS::Path & cacheFolder
) const
```




<hr>



### function SaveHash 

```C++
void SR_SCRIPTING_NS::CppCodegenModule::SaveHash (
    const SR_UTILS_NS::Path & cacheFolder
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Scripting/inc/Scripting/Cpp/CodeGenerator.h`

