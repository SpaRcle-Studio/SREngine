

# Struct EvoScript::Header



[**ClassList**](annotated.md) **>** [**EvoScript**](namespaceEvoScript.md) **>** [**Header**](structEvoScript_1_1Header.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**Class**](structEvoScript_1_1Class.md) &gt; | [**m\_classes**](#variable-m_classes)  <br> |
|  std::vector&lt; [**EvoEnum**](structEvoScript_1_1EvoEnum.md) &gt; | [**m\_enums**](#variable-m_enums)  <br> |
|  std::vector&lt; [**Method**](structEvoScript_1_1Method.md) &gt; | [**m\_functions**](#variable-m_functions)  <br> |
|  std::set&lt; std::string &gt; | [**m\_includes**](#variable-m_includes)  <br> |
|  std::vector&lt; std::string &gt; | [**m\_incompleteTypes**](#variable-m_incompletetypes)  <br> |
|  std::string | [**m\_name**](#variable-m_name)  <br> |
|  std::vector&lt; std::string &gt; | [**m\_typedefs**](#variable-m_typedefs)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**Class**](structEvoScript_1_1Class.md) \* | [**FindClass**](#function-findclass) (const std::string & name) <br> |
|  std::string | [**GetIncludes**](#function-getincludes) () const<br> |
|  std::string | [**ToString**](#function-tostring) () const<br> |




























## Public Attributes Documentation




### variable m\_classes 

```C++
std::vector<Class> EvoScript::Header::m_classes;
```




<hr>



### variable m\_enums 

```C++
std::vector<EvoEnum> EvoScript::Header::m_enums;
```




<hr>



### variable m\_functions 

```C++
std::vector<Method> EvoScript::Header::m_functions;
```




<hr>



### variable m\_includes 

```C++
std::set<std::string> EvoScript::Header::m_includes;
```




<hr>



### variable m\_incompleteTypes 

```C++
std::vector<std::string> EvoScript::Header::m_incompleteTypes;
```




<hr>



### variable m\_name 

```C++
std::string EvoScript::Header::m_name;
```




<hr>



### variable m\_typedefs 

```C++
std::vector<std::string> EvoScript::Header::m_typedefs;
```




<hr>
## Public Functions Documentation




### function FindClass 

```C++
inline Class * EvoScript::Header::FindClass (
    const std::string & name
) 
```




<hr>



### function GetIncludes 

```C++
inline std::string EvoScript::Header::GetIncludes () const
```




<hr>



### function ToString 

```C++
inline std::string EvoScript::Header::ToString () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Scripting/inc/Scripting/Old/Compilation/AddressTableGen.h`

