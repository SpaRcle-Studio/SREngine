

# Class SR\_UTILS\_NS::StoreUtils::Template

**template &lt;Storage::StorageType storeType&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**StoreUtils**](namespaceSR__UTILS__NS_1_1StoreUtils.md) **>** [**Template**](classSR__UTILS__NS_1_1StoreUtils_1_1Template.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Template**](#function-template) () = delete<br> |
|   | [**~Template**](#function-template) () = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**GetBool**](#function-getbool) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, const std::optional&lt; bool &gt; & def=std::nullopt) <br> |
|  SR\_NODISCARD float\_t | [**GetFloat**](#function-getfloat) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, const std::optional&lt; float\_t &gt; & def=std::nullopt) <br> |
|  SR\_NODISCARD int64\_t | [**GetInt**](#function-getint) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, const std::optional&lt; int64\_t &gt; & def=std::nullopt) <br> |
|  SR\_NODISCARD std::string | [**GetString**](#function-getstring) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, const std::optional&lt; std::string &gt; & def=std::nullopt) <br> |
|  SR\_NODISCARD bool | [**Has**](#function-has) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, Storage::ValueType type=Storage::ValueType::AnyType) <br> |
|  SR\_NODISCARD bool | [**HasBool**](#function-hasbool) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key) <br>_================= Bool =================_  |
|  SR\_NODISCARD bool | [**HasFloat**](#function-hasfloat) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key) <br>_================= Float =================_  |
|  SR\_NODISCARD bool | [**HasInt**](#function-hasint) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key) <br>_================= Int =================_  |
|  SR\_NODISCARD bool | [**HasString**](#function-hasstring) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key) <br>_================= String =================_  |
|  void | [**SetBool**](#function-setbool) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, bool value) <br> |
|  void | [**SetFloat**](#function-setfloat) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, float\_t value) <br> |
|  void | [**SetInt**](#function-setint) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, int64\_t value) <br> |
|  void | [**SetString**](#function-setstring) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, const std::string & value) <br> |


























## Public Functions Documentation




### function Template 

```C++
SR_UTILS_NS::StoreUtils::Template::Template () = delete
```




<hr>



### function ~Template 

```C++
SR_UTILS_NS::StoreUtils::Template::~Template () = delete
```




<hr>
## Public Static Functions Documentation




### function GetBool 

```C++
static inline SR_NODISCARD bool SR_UTILS_NS::StoreUtils::Template::GetBool (
    SR_UTILS_NS::StringAtom key,
    const std::optional< bool > & def=std::nullopt
) 
```




<hr>



### function GetFloat 

```C++
static inline SR_NODISCARD float_t SR_UTILS_NS::StoreUtils::Template::GetFloat (
    SR_UTILS_NS::StringAtom key,
    const std::optional< float_t > & def=std::nullopt
) 
```




<hr>



### function GetInt 

```C++
static inline SR_NODISCARD int64_t SR_UTILS_NS::StoreUtils::Template::GetInt (
    SR_UTILS_NS::StringAtom key,
    const std::optional< int64_t > & def=std::nullopt
) 
```




<hr>



### function GetString 

```C++
static inline SR_NODISCARD std::string SR_UTILS_NS::StoreUtils::Template::GetString (
    SR_UTILS_NS::StringAtom key,
    const std::optional< std::string > & def=std::nullopt
) 
```




<hr>



### function Has 

```C++
static inline SR_NODISCARD bool SR_UTILS_NS::StoreUtils::Template::Has (
    SR_UTILS_NS::StringAtom key,
    Storage::ValueType type=Storage::ValueType::AnyType
) 
```




<hr>



### function HasBool 

_================= Bool =================_ 
```C++
static inline SR_NODISCARD bool SR_UTILS_NS::StoreUtils::Template::HasBool (
    SR_UTILS_NS::StringAtom key
) 
```




<hr>



### function HasFloat 

_================= Float =================_ 
```C++
static inline SR_NODISCARD bool SR_UTILS_NS::StoreUtils::Template::HasFloat (
    SR_UTILS_NS::StringAtom key
) 
```




<hr>



### function HasInt 

_================= Int =================_ 
```C++
static inline SR_NODISCARD bool SR_UTILS_NS::StoreUtils::Template::HasInt (
    SR_UTILS_NS::StringAtom key
) 
```




<hr>



### function HasString 

_================= String =================_ 
```C++
static inline SR_NODISCARD bool SR_UTILS_NS::StoreUtils::Template::HasString (
    SR_UTILS_NS::StringAtom key
) 
```




<hr>



### function SetBool 

```C++
static inline void SR_UTILS_NS::StoreUtils::Template::SetBool (
    SR_UTILS_NS::StringAtom key,
    bool value
) 
```




<hr>



### function SetFloat 

```C++
static inline void SR_UTILS_NS::StoreUtils::Template::SetFloat (
    SR_UTILS_NS::StringAtom key,
    float_t value
) 
```




<hr>



### function SetInt 

```C++
static inline void SR_UTILS_NS::StoreUtils::Template::SetInt (
    SR_UTILS_NS::StringAtom key,
    int64_t value
) 
```




<hr>



### function SetString 

```C++
static inline void SR_UTILS_NS::StoreUtils::Template::SetString (
    SR_UTILS_NS::StringAtom key,
    const std::string & value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/StoreUtils.h`

