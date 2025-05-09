

# Struct SR\_GRAPH\_NS::ISamplersPass::Sampler



[**ClassList**](annotated.md) **>** [**Sampler**](structSR__GRAPH__NS_1_1ISamplersPass_1_1Sampler.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**depth**](#variable-depth)   = `false`<br> |
|  uint32\_t | [**fboId**](#variable-fboid)   = `SR\_ID\_INVALID`<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**fboName**](#variable-fboname)  <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**id**](#variable-id)  <br> |
|  uint64\_t | [**index**](#variable-index)   = `0`<br> |
|  [**SR\_GTYPES\_NS::Texture**](classSR__GTYPES__NS_1_1Texture.md) \* | [**pTexture**](#variable-ptexture)   = `nullptr`<br> |
|  uint32\_t | [**textureId**](#variable-textureid)   = `SR\_ID\_INVALID`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Sampler**](#function-sampler-12) () = default<br> |
|   | [**Sampler**](#function-sampler-22) (Sampler && other) noexcept<br> |
|  Sampler & | [**operator=**](#function-operator) (Sampler && other) noexcept<br> |
|   | [**~Sampler**](#function-sampler) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Attributes Documentation




### variable depth 

```C++
bool SR_GRAPH_NS::ISamplersPass::Sampler::depth;
```




<hr>



### variable fboId 

```C++
uint32_t SR_GRAPH_NS::ISamplersPass::Sampler::fboId;
```




<hr>



### variable fboName 

```C++
SR_UTILS_NS::StringAtom SR_GRAPH_NS::ISamplersPass::Sampler::fboName;
```




<hr>



### variable id 

```C++
SR_UTILS_NS::StringAtom SR_GRAPH_NS::ISamplersPass::Sampler::id;
```




<hr>



### variable index 

```C++
uint64_t SR_GRAPH_NS::ISamplersPass::Sampler::index;
```




<hr>



### variable pTexture 

```C++
SR_GTYPES_NS::Texture* SR_GRAPH_NS::ISamplersPass::Sampler::pTexture;
```




<hr>



### variable textureId 

```C++
uint32_t SR_GRAPH_NS::ISamplersPass::Sampler::textureId;
```




<hr>
## Public Functions Documentation




### function Sampler [1/2]

```C++
Sampler::Sampler () = default
```




<hr>



### function Sampler [2/2]

```C++
Sampler::Sampler (
    Sampler && other
) noexcept
```




<hr>



### function operator= 

```C++
Sampler & Sampler::operator= (
    Sampler && other
) noexcept
```




<hr>



### function ~Sampler 

```C++
Sampler::~Sampler () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Pass/ISamplersPass.h`

