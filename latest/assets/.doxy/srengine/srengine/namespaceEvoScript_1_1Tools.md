

# Namespace EvoScript::Tools



[**Namespace List**](namespaces.md) **>** [**EvoScript**](namespaceEvoScript.md) **>** [**Tools**](namespaceEvoScript_1_1Tools.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**MD5**](classEvoScript_1_1Tools_1_1MD5.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef unsigned char | [**MD5\_BYTE**](#typedef-md5_byte)  <br> |
| typedef unsigned char \* | [**MD5\_POINTER**](#typedef-md5_pointer)  <br> |
| typedef unsigned short int | [**MD5\_UINT2**](#typedef-md5_uint2)  <br> |
| typedef unsigned long int | [**MD5\_UINT4**](#typedef-md5_uint4)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  unsigned char | [**MD5\_PADDING**](#variable-md5_padding)   = `/* multi line expression */`<br> |
|  const std::vector&lt; std::string &gt; | [**VS\_PATHS**](#variable-vs_paths)   = `/* multi line expression */`<br> |
|  const std::vector&lt; std::string &gt; | [**VS\_TYPES**](#variable-vs_types)   = `/* multi line expression */`<br> |
|  const std::vector&lt; std::string &gt; | [**VS\_YEARS**](#variable-vs_years)   = `/* multi line expression */`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  std::set&lt; T &gt; | [**Merge**](#function-merge) (const std::set&lt; T &gt; & s1, const std::set&lt; T &gt; & s2) <br> |
|  void | [**PrintSet**](#function-printset) (const std::set&lt; T &gt; & s) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**BackReadTo**](#function-backreadto) (const std::string & str, const char c) <br> |
|  std::string | [**DeleteSymbolsInStr**](#function-deletesymbolsinstr) (std::string str, const std::string & symbols) <br> |
|  std::string | [**FindMSVC**](#function-findmsvc) () <br> |
|  std::string | [**FindMSVCCompiler**](#function-findmsvccompiler) () <br> |
|  std::string | [**FindMSVCInclude**](#function-findmsvcinclude) () <br> |
|  std::string | [**FindMSVCVars64**](#function-findmsvcvars64) (const std::string & compilerPath) <br> |
|  std::string | [**FindMSVCVars64**](#function-findmsvcvars64) () <br> |
|  std::string | [**FixPath**](#function-fixpath) (const std::string & path) <br> |
|  std::vector&lt; std::string &gt; | [**GetArgs**](#function-getargs) (const std::string & str) <br> |
|  std::string | [**GetDate**](#function-getdate) () <br> |
|  std::string | [**GetFileHash**](#function-getfilehash) (const std::string & file) <br> |
|  std::vector&lt; std::string &gt; | [**GetHashAllFilesInDir**](#function-gethashallfilesindir) (const std::string & dir) <br> |
|  bool | [**HashEquals**](#function-hashequals) (const std::pair&lt; bool, std::vector&lt; std::string &gt; &gt; & a, const std::pair&lt; bool, std::vector&lt; std::string &gt; &gt; & b) <br> |
|  std::pair&lt; bool, std::vector&lt; std::string &gt; &gt; | [**LoadHashInfo**](#function-loadhashinfo) (const std::string & pathToHashInfo) <br> |
|  std::string | [**Read**](#function-read) (const std::string & str, uint32\_t count) <br> |
|  std::string | [**ReadTo**](#function-readto) (const std::string & str, char c) <br> |
|  std::string | [**ReadToLast**](#function-readtolast) (const std::string & str, char c) <br> |
|  std::vector&lt; std::string &gt; | [**RemoveFirstSpaces**](#function-removefirstspaces) (std::vector&lt; std::string &gt; strings) <br> |
|  std::string | [**Replace**](#function-replace) (std::string str, const std::string & from, const std::string & to) <br> |
|  bool | [**SaveHashInfo**](#function-savehashinfo) (const std::string & path, const std::pair&lt; bool, std::vector&lt; std::string &gt; &gt; & hashInfo) <br> |
|  std::vector&lt; std::string &gt; | [**Split**](#function-split) (const std::string & s) <br> |
|  std::string | [**TabString**](#function-tabstring) (std::string str) <br> |
|  std::string | [**ToUpper**](#function-toupper) (std::string str) <br> |


























## Public Types Documentation




### typedef MD5\_BYTE 

```C++
typedef unsigned char EvoScript::Tools::MD5_BYTE;
```




<hr>



### typedef MD5\_POINTER 

```C++
typedef unsigned char* EvoScript::Tools::MD5_POINTER;
```




<hr>



### typedef MD5\_UINT2 

```C++
typedef unsigned short int EvoScript::Tools::MD5_UINT2;
```




<hr>



### typedef MD5\_UINT4 

```C++
typedef unsigned long int EvoScript::Tools::MD5_UINT4;
```




<hr>
## Public Static Attributes Documentation




### variable MD5\_PADDING 

```C++
unsigned char EvoScript::Tools::MD5_PADDING[64];
```




<hr>



### variable VS\_PATHS 

```C++
const std::vector<std::string> EvoScript::Tools::VS_PATHS;
```




<hr>



### variable VS\_TYPES 

```C++
const std::vector<std::string> EvoScript::Tools::VS_TYPES;
```




<hr>



### variable VS\_YEARS 

```C++
const std::vector<std::string> EvoScript::Tools::VS_YEARS;
```




<hr>
## Public Functions Documentation




### function Merge 

```C++
template<typename T>
std::set< T > EvoScript::Tools::Merge (
    const std::set< T > & s1,
    const std::set< T > & s2
) 
```




<hr>



### function PrintSet 

```C++
template<typename T>
void EvoScript::Tools::PrintSet (
    const std::set< T > & s
) 
```




<hr>
## Public Static Functions Documentation




### function BackReadTo 

```C++
static std::string EvoScript::Tools::BackReadTo (
    const std::string & str,
    const char c
) 
```




<hr>



### function DeleteSymbolsInStr 

```C++
static std::string EvoScript::Tools::DeleteSymbolsInStr (
    std::string str,
    const std::string & symbols
) 
```




<hr>



### function FindMSVC 

```C++
static std::string EvoScript::Tools::FindMSVC () 
```




<hr>



### function FindMSVCCompiler 

```C++
static std::string EvoScript::Tools::FindMSVCCompiler () 
```




<hr>



### function FindMSVCInclude 

```C++
static std::string EvoScript::Tools::FindMSVCInclude () 
```




<hr>



### function FindMSVCVars64 

```C++
static std::string EvoScript::Tools::FindMSVCVars64 (
    const std::string & compilerPath
) 
```




<hr>



### function FindMSVCVars64 

```C++
static std::string EvoScript::Tools::FindMSVCVars64 () 
```




<hr>



### function FixPath 

```C++
static std::string EvoScript::Tools::FixPath (
    const std::string & path
) 
```




<hr>



### function GetArgs 

```C++
static std::vector< std::string > EvoScript::Tools::GetArgs (
    const std::string & str
) 
```




<hr>



### function GetDate 

```C++
static std::string EvoScript::Tools::GetDate () 
```




<hr>



### function GetFileHash 

```C++
static std::string EvoScript::Tools::GetFileHash (
    const std::string & file
) 
```




<hr>



### function GetHashAllFilesInDir 

```C++
static std::vector< std::string > EvoScript::Tools::GetHashAllFilesInDir (
    const std::string & dir
) 
```




<hr>



### function HashEquals 

```C++
static bool EvoScript::Tools::HashEquals (
    const std::pair< bool, std::vector< std::string > > & a,
    const std::pair< bool, std::vector< std::string > > & b
) 
```




<hr>



### function LoadHashInfo 

```C++
static std::pair< bool, std::vector< std::string > > EvoScript::Tools::LoadHashInfo (
    const std::string & pathToHashInfo
) 
```




<hr>



### function Read 

```C++
static inline std::string EvoScript::Tools::Read (
    const std::string & str,
    uint32_t count
) 
```




<hr>



### function ReadTo 

```C++
static inline std::string EvoScript::Tools::ReadTo (
    const std::string & str,
    char c
) 
```




<hr>



### function ReadToLast 

```C++
static inline std::string EvoScript::Tools::ReadToLast (
    const std::string & str,
    char c
) 
```




<hr>



### function RemoveFirstSpaces 

```C++
static std::vector< std::string > EvoScript::Tools::RemoveFirstSpaces (
    std::vector< std::string > strings
) 
```




<hr>



### function Replace 

```C++
static std::string EvoScript::Tools::Replace (
    std::string str,
    const std::string & from,
    const std::string & to
) 
```




<hr>



### function SaveHashInfo 

```C++
static bool EvoScript::Tools::SaveHashInfo (
    const std::string & path,
    const std::pair< bool, std::vector< std::string > > & hashInfo
) 
```




<hr>



### function Split 

```C++
static std::vector< std::string > EvoScript::Tools::Split (
    const std::string & s
) 
```




<hr>



### function TabString 

```C++
static std::string EvoScript::Tools::TabString (
    std::string str
) 
```




<hr>



### function ToUpper 

```C++
static std::string EvoScript::Tools::ToUpper (
    std::string str
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Old/Tools/Finder.h`

