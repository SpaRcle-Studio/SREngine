

# Struct SR\_UTILS\_NS::SerializationId



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_INLINE uint64\_t | [**GetHash**](#function-gethash) () noexcept const<br> |
|  SR\_NODISCARD SR\_INLINE const char \* | [**GetName**](#function-getname) () noexcept const<br> |
|  SR\_CONSTEXPR | [**SerializationId**](#function-serializationid) () noexcept<br> |
|  SR\_NODISCARD SR\_INLINE std::string | [**ToString**](#function-tostring) () noexcept const<br> |
|  SR\_CONSTEXPR | [**~SerializationId**](#function-serializationid) () noexcept<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) | [**Create**](#function-create) (const char(&) text) noexcept<br> |
|  [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) | [**CreateFromCStr**](#function-createfromcstr) (const char \* text) noexcept<br> |
|  [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) | [**CreateFromString**](#function-createfromstring) (const std::string\_view text) noexcept<br> |


























## Public Functions Documentation




### function GetHash 

```C++
inline SR_NODISCARD SR_INLINE uint64_t SR_UTILS_NS::SerializationId::GetHash () noexcept const
```




<hr>



### function GetName 

```C++
inline SR_NODISCARD SR_INLINE const char * SR_UTILS_NS::SerializationId::GetName () noexcept const
```




<hr>



### function SerializationId 

```C++
SR_CONSTEXPR SR_UTILS_NS::SerializationId::SerializationId () noexcept
```




<hr>



### function ToString 

```C++
inline SR_NODISCARD SR_INLINE std::string SR_UTILS_NS::SerializationId::ToString () noexcept const
```




<hr>



### function ~SerializationId 

```C++
SR_CONSTEXPR SR_UTILS_NS::SerializationId::~SerializationId () noexcept
```




<hr>
## Public Static Functions Documentation




### function Create 

```C++
template<uint64_t S>
static inline constexpr SerializationId SR_UTILS_NS::SerializationId::Create (
    const char(&) text
) noexcept
```




<hr>



### function CreateFromCStr 

```C++
static inline SerializationId SR_UTILS_NS::SerializationId::CreateFromCStr (
    const char * text
) noexcept
```




<hr>



### function CreateFromString 

```C++
static inline SerializationId SR_UTILS_NS::SerializationId::CreateFromString (
    const std::string_view text
) noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/TypeTraits/TypeTraits.h`

