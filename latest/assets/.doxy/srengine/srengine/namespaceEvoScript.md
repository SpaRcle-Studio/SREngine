

# Namespace EvoScript



[**Namespace List**](namespaces.md) **>** [**EvoScript**](namespaceEvoScript.md)


















## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**Tools**](namespaceEvoScript_1_1Tools.md) <br> |
| namespace | [**Typedefs**](namespaceEvoScript_1_1Typedefs.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**AddressTableGen**](classEvoScript_1_1AddressTableGen.md) <br> |
| class | [**CMakeCodeGen**](classEvoScript_1_1CMakeCodeGen.md) <br> |
| class | [**CastingGen**](classEvoScript_1_1CastingGen.md) <br> |
| struct | [**Class**](structEvoScript_1_1Class.md) <br> |
| class | [**Compiler**](classEvoScript_1_1Compiler.md) <br> |
| struct | [**EvoEnum**](structEvoScript_1_1EvoEnum.md) <br> |
| struct | [**Header**](structEvoScript_1_1Header.md) <br> |
| class | [**IState**](classEvoScript_1_1IState.md) <br> |
| struct | [**InheritClass**](structEvoScript_1_1InheritClass.md) <br> |
| struct | [**Method**](structEvoScript_1_1Method.md) <br> |
| struct | [**Property**](structEvoScript_1_1Property.md) <br> |
| class | [**Script**](classEvoScript_1_1Script.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**CastingType**](#enum-castingtype)  <br> |
| enum  | [**MethodType**](#enum-methodtype)  <br> |
| typedef std::unordered\_map&lt; std::string, std::vector&lt; uint32\_t &gt; &gt; | [**ModuleCopies**](#typedef-modulecopies)  <br> |
| enum  | [**Publicity**](#enum-publicity)  <br> |






















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**CastingTypeToString**](#function-castingtypetostring) (CastingType type) <br> |
|  void \* | [**ESAllocateMemory**](#function-esallocatememory) (size\_t sz) <br> |
|  void | [**ESFreeMemory**](#function-esfreememory) (void \* ptr) <br> |
|  std::string | [**PublicityToString**](#function-publicitytostring) (Publicity publicity, bool colon=true) <br> |


























## Public Types Documentation




### enum CastingType 

```C++
enum EvoScript::CastingType {
    Unknown,
    Dynamic,
    Static,
    Reinterpret
};
```




<hr>



### enum MethodType 

```C++
enum EvoScript::MethodType {
    Normal,
    Virtual,
    Override,
    Static,
    VirtualOverride
};
```




<hr>



### typedef ModuleCopies 

```C++
typedef std::unordered_map<std::string, std::vector<uint32_t> > EvoScript::ModuleCopies;
```




<hr>



### enum Publicity 

```C++
enum EvoScript::Publicity {
    Unknown,
    Public,
    Private,
    Protected
};
```




<hr>
## Public Static Functions Documentation




### function CastingTypeToString 

```C++
static std::string EvoScript::CastingTypeToString (
    CastingType type
) 
```




<hr>



### function ESAllocateMemory 

```C++
static void * EvoScript::ESAllocateMemory (
    size_t sz
) 
```




<hr>



### function ESFreeMemory 

```C++
static void EvoScript::ESFreeMemory (
    void * ptr
) 
```




<hr>



### function PublicityToString 

```C++
static std::string EvoScript::PublicityToString (
    Publicity publicity,
    bool colon=true
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/EvoScriptAPI.h`

