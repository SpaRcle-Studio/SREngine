

# Namespace SR\_UTILS\_NS::Base64



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Base64**](namespaceSR__UTILS__NS_1_1Base64.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**FixedString**](structSR__UTILS__NS_1_1Base64_1_1FixedString.md) &lt;N&gt;<br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr std::array&lt; char,((((N-1) &gt; &gt; 2) \*3)+1)&gt; | [**CompileTimeDecode**](#function-compiletimedecode) (const char(&) input) <br> |




























## Public Functions Documentation




### function CompileTimeDecode 

```C++
template<size_t N>
constexpr std::array< char,((((N-1) > > 2) *3)+1)> SR_UTILS_NS::Base64::CompileTimeDecode (
    const char(&) input
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/Base64.h`

