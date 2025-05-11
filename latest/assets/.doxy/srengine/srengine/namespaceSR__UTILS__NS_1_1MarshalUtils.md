

# Namespace SR\_UTILS\_NS::MarshalUtils



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**MarshalUtils**](namespaceSR__UTILS__NS_1_1MarshalUtils.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC std::string SR\_FASTCALL | [**LoadShortStr**](#function-loadshortstr) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream) <br> |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC std::string SR\_FASTCALL | [**LoadStr**](#function-loadstr) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream) <br> |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC [**SR\_HTYPES\_NS::UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) SR\_FASTCALL | [**LoadUnicodeString**](#function-loadunicodestring) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream) <br> |
|  SR\_INLINE\_STATIC T SR\_FASTCALL | [**LoadValue**](#function-loadvalue) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream) <br> |
|  SR\_INLINE\_STATIC Vector SR\_FASTCALL | [**LoadVector**](#function-loadvector) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream) <br> |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC void SR\_FASTCALL | [**SaveShortString**](#function-saveshortstring) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream, const std::string & str) <br> |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC void SR\_FASTCALL | [**SaveString**](#function-savestring) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream, const std::string & str) <br> |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC void SR\_FASTCALL | [**SaveUnicodeString**](#function-saveunicodestring) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream, const [**SR\_HTYPES\_NS::UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & str) <br> |
|  SR\_INLINE\_STATIC void SR\_FASTCALL | [**SaveValue**](#function-savevalue) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream, const T & value) <br> |
|  SR\_INLINE\_STATIC void SR\_FASTCALL | [**SaveVector**](#function-savevector) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream, const std::vector&lt; T &gt; & vector) <br> |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC std::string SR\_FASTCALL | [**TryLoadShortStr**](#function-tryloadshortstr) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream) <br> |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC [**SR\_HTYPES\_NS::UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) SR\_FASTCALL | [**TryLoadUnicodeString**](#function-tryloadunicodestring) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**Encode**](#function-encode) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream, const std::string & str, StandardType type) <br> |
|  Any SR\_FASTCALL | [**LoadAny**](#function-loadany) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream) <br> |
|  void SR\_FASTCALL | [**SaveAny**](#function-saveany) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream, const Any & any) <br> |
|  SR\_MAYBE\_UNUSED void SR\_FASTCALL | [**SaveString**](#function-savestring) ([**SR\_HTYPES\_NS::Stream**](classSR__HTYPES__NS_1_1Stream.md) & stream, const std::string\_view & str) <br> |


























## Public Functions Documentation




### function LoadShortStr 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC std::string SR_FASTCALL SR_UTILS_NS::MarshalUtils::LoadShortStr (
    SR_HTYPES_NS::Stream & stream
) 
```




<hr>



### function LoadStr 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC std::string SR_FASTCALL SR_UTILS_NS::MarshalUtils::LoadStr (
    SR_HTYPES_NS::Stream & stream
) 
```




<hr>



### function LoadUnicodeString 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC SR_HTYPES_NS::UnicodeString SR_FASTCALL SR_UTILS_NS::MarshalUtils::LoadUnicodeString (
    SR_HTYPES_NS::Stream & stream
) 
```




<hr>



### function LoadValue 

```C++
template<typename T>
SR_INLINE_STATIC T SR_FASTCALL SR_UTILS_NS::MarshalUtils::LoadValue (
    SR_HTYPES_NS::Stream & stream
) 
```




<hr>



### function LoadVector 

```C++
template<typename Vector>
SR_INLINE_STATIC Vector SR_FASTCALL SR_UTILS_NS::MarshalUtils::LoadVector (
    SR_HTYPES_NS::Stream & stream
) 
```




<hr>



### function SaveShortString 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC void SR_FASTCALL SR_UTILS_NS::MarshalUtils::SaveShortString (
    SR_HTYPES_NS::Stream & stream,
    const std::string & str
) 
```




<hr>



### function SaveString 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC void SR_FASTCALL SR_UTILS_NS::MarshalUtils::SaveString (
    SR_HTYPES_NS::Stream & stream,
    const std::string & str
) 
```




<hr>



### function SaveUnicodeString 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC void SR_FASTCALL SR_UTILS_NS::MarshalUtils::SaveUnicodeString (
    SR_HTYPES_NS::Stream & stream,
    const SR_HTYPES_NS::UnicodeString & str
) 
```




<hr>



### function SaveValue 

```C++
template<typename T>
SR_INLINE_STATIC void SR_FASTCALL SR_UTILS_NS::MarshalUtils::SaveValue (
    SR_HTYPES_NS::Stream & stream,
    const T & value
) 
```




<hr>



### function SaveVector 

```C++
template<typename T>
SR_INLINE_STATIC void SR_FASTCALL SR_UTILS_NS::MarshalUtils::SaveVector (
    SR_HTYPES_NS::Stream & stream,
    const std::vector< T > & vector
) 
```




<hr>



### function TryLoadShortStr 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC std::string SR_FASTCALL SR_UTILS_NS::MarshalUtils::TryLoadShortStr (
    SR_HTYPES_NS::Stream & stream
) 
```




<hr>



### function TryLoadUnicodeString 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC SR_HTYPES_NS::UnicodeString SR_FASTCALL SR_UTILS_NS::MarshalUtils::TryLoadUnicodeString (
    SR_HTYPES_NS::Stream & stream
) 
```




<hr>
## Public Static Functions Documentation




### function Encode 

```C++
static SR_MAYBE_UNUSED void SR_UTILS_NS::MarshalUtils::Encode (
    SR_HTYPES_NS::Stream & stream,
    const std::string & str,
    StandardType type
) 
```




<hr>



### function LoadAny 

```C++
template<typename Any>
static Any SR_FASTCALL SR_UTILS_NS::MarshalUtils::LoadAny (
    SR_HTYPES_NS::Stream & stream
) 
```




<hr>



### function SaveAny 

```C++
template<typename Any>
static void SR_FASTCALL SR_UTILS_NS::MarshalUtils::SaveAny (
    SR_HTYPES_NS::Stream & stream,
    const Any & any
) 
```




<hr>



### function SaveString 

```C++
static SR_MAYBE_UNUSED void SR_FASTCALL SR_UTILS_NS::MarshalUtils::SaveString (
    SR_HTYPES_NS::Stream & stream,
    const std::string_view & str
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/AnyMarshal.h`

