

# Struct SR\_UTILS\_NS::GlobalStringRegistry



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**GlobalStringRegistry**](structSR__UTILS__NS_1_1GlobalStringRegistry.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  uint64\_t | [**count**](#variable-count)  <br> |
|  std::array&lt; [**ConstexprStringHashEntry**](structSR__UTILS__NS_1_1ConstexprStringHashEntry.md), ConstexprStringsMaxEntries &gt; | [**entries**](#variable-entries)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD constexpr std::optional&lt; std::string\_view &gt; | [**FindConstexprStringByHash**](#function-findconstexprstringbyhash) (uint64\_t hash) const<br> |
|  constexpr | [**GlobalStringRegistry**](#function-globalstringregistry) () <br> |
|  uint64\_t | [**Register**](#function-register) (std::string\_view str, uint64\_t hash) const<br> |




























## Public Attributes Documentation




### variable count 

```C++
uint64_t SR_UTILS_NS::GlobalStringRegistry::count;
```




<hr>



### variable entries 

```C++
std::array<ConstexprStringHashEntry, ConstexprStringsMaxEntries> SR_UTILS_NS::GlobalStringRegistry::entries;
```




<hr>
## Public Functions Documentation




### function FindConstexprStringByHash 

```C++
inline SR_NODISCARD constexpr std::optional< std::string_view > SR_UTILS_NS::GlobalStringRegistry::FindConstexprStringByHash (
    uint64_t hash
) const
```




<hr>



### function GlobalStringRegistry 

```C++
inline constexpr SR_UTILS_NS::GlobalStringRegistry::GlobalStringRegistry () 
```




<hr>



### function Register 

```C++
inline uint64_t SR_UTILS_NS::GlobalStringRegistry::Register (
    std::string_view str,
    uint64_t hash
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/HashManager.h`

