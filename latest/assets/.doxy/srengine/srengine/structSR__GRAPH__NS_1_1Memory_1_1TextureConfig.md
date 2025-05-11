

# Struct SR\_GRAPH\_NS::Memory::TextureConfig



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**TextureConfig**](structSR__GRAPH__NS_1_1Memory_1_1TextureConfig.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_UTILS\_NS::BoolExt | [**m\_alpha**](#variable-m_alpha)  <br> |
|  TextureCompression | [**m\_compression**](#variable-m_compression)  <br> |
|  bool | [**m\_cpuUsage**](#variable-m_cpuusage)  <br> |
|  TextureFilter | [**m\_filter**](#variable-m_filter)  <br> |
|  ImageFormat | [**m\_format**](#variable-m_format)  <br> |
|  uint32\_t | [**m\_mipLevels**](#variable-m_miplevels)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_UTILS\_NS::BoolExt | [**GetAlpha**](#function-getalpha) () noexcept const<br> |
|  SR\_NODISCARD TextureCompression | [**GetCompression**](#function-getcompression) () noexcept const<br> |
|  SR\_NODISCARD bool | [**GetCpuUsage**](#function-getcpuusage) () noexcept const<br> |
|  SR\_NODISCARD TextureFilter | [**GetFilter**](#function-getfilter) () noexcept const<br> |
|  SR\_NODISCARD ImageFormat | [**GetFormat**](#function-getformat) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetMipLevels**](#function-getmiplevels) () noexcept const<br> |
|   | [**TextureConfig**](#function-textureconfig-12) (ImageFormat format, TextureFilter filter, TextureCompression compression, uint32\_t mipLevels, SR\_UTILS\_NS::BoolExt alpha, bool cpuUsage) <br> |
|   | [**TextureConfig**](#function-textureconfig-22) () <br> |
|  bool | [**operator!=**](#function-operator) (const [**TextureConfig**](structSR__GRAPH__NS_1_1Memory_1_1TextureConfig.md) & lrs) const<br> |
|  bool | [**operator==**](#function-operator_1) (const [**TextureConfig**](structSR__GRAPH__NS_1_1Memory_1_1TextureConfig.md) & lrs) const<br> |




























## Public Attributes Documentation




### variable m\_alpha 

```C++
SR_UTILS_NS::BoolExt SR_GRAPH_NS::Memory::TextureConfig::m_alpha;
```




<hr>



### variable m\_compression 

```C++
TextureCompression SR_GRAPH_NS::Memory::TextureConfig::m_compression;
```




<hr>



### variable m\_cpuUsage 

```C++
bool SR_GRAPH_NS::Memory::TextureConfig::m_cpuUsage;
```




<hr>



### variable m\_filter 

```C++
TextureFilter SR_GRAPH_NS::Memory::TextureConfig::m_filter;
```




<hr>



### variable m\_format 

```C++
ImageFormat SR_GRAPH_NS::Memory::TextureConfig::m_format;
```




<hr>



### variable m\_mipLevels 

```C++
uint32_t SR_GRAPH_NS::Memory::TextureConfig::m_mipLevels;
```




<hr>
## Public Functions Documentation




### function GetAlpha 

```C++
inline SR_NODISCARD SR_UTILS_NS::BoolExt SR_GRAPH_NS::Memory::TextureConfig::GetAlpha () noexcept const
```




<hr>



### function GetCompression 

```C++
inline SR_NODISCARD TextureCompression SR_GRAPH_NS::Memory::TextureConfig::GetCompression () noexcept const
```




<hr>



### function GetCpuUsage 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Memory::TextureConfig::GetCpuUsage () noexcept const
```




<hr>



### function GetFilter 

```C++
inline SR_NODISCARD TextureFilter SR_GRAPH_NS::Memory::TextureConfig::GetFilter () noexcept const
```




<hr>



### function GetFormat 

```C++
inline SR_NODISCARD ImageFormat SR_GRAPH_NS::Memory::TextureConfig::GetFormat () noexcept const
```




<hr>



### function GetMipLevels 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::Memory::TextureConfig::GetMipLevels () noexcept const
```




<hr>



### function TextureConfig [1/2]

```C++
inline SR_GRAPH_NS::Memory::TextureConfig::TextureConfig (
    ImageFormat format,
    TextureFilter filter,
    TextureCompression compression,
    uint32_t mipLevels,
    SR_UTILS_NS::BoolExt alpha,
    bool cpuUsage
) 
```




<hr>



### function TextureConfig [2/2]

```C++
inline SR_GRAPH_NS::Memory::TextureConfig::TextureConfig () 
```




<hr>



### function operator!= 

```C++
inline bool SR_GRAPH_NS::Memory::TextureConfig::operator!= (
    const TextureConfig & lrs
) const
```




<hr>



### function operator== 

```C++
inline bool SR_GRAPH_NS::Memory::TextureConfig::operator== (
    const TextureConfig & lrs
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Memory/TextureConfigs.h`

