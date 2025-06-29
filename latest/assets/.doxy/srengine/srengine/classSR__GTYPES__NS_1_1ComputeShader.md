

# Class SR\_GTYPES\_NS::ComputeShader



[**ClassList**](annotated.md) **>** [**SR\_GTYPES\_NS**](namespaceSR__GTYPES__NS.md) **>** [**ComputeShader**](classSR__GTYPES__NS_1_1ComputeShader.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::unique\_ptr&lt; [**ComputeShader**](classSR__GTYPES__NS_1_1ComputeShader.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**BeginCompute**](#function-begincompute) () <br> |
|  void | [**Dispatch**](#function-dispatch-12) (uint32\_t x, uint32\_t y, uint32\_t z) <br> |
|  void | [**Dispatch**](#function-dispatch-22) () <br> |
|  void | [**EndCompute**](#function-endcompute) () <br> |
|  SR\_NODISCARD const SR\_GRAPH\_NS::Pipeline::Ptr & | [**GetPipeline**](#function-getpipeline) () const<br> |
|  SR\_NODISCARD const SR\_GTYPES\_NS::Shader::Ptr & | [**GetShader**](#function-getshader) () noexcept const<br> |
|   | [**~ComputeShader**](#function-computeshader) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD ComputeShader::Ptr | [**Load**](#function-load) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef Ptr 

```C++
using SR_GTYPES_NS::ComputeShader::Ptr =  std::unique_ptr<ComputeShader>;
```




<hr>
## Public Functions Documentation




### function BeginCompute 

```C++
bool SR_GTYPES_NS::ComputeShader::BeginCompute () 
```




<hr>



### function Dispatch [1/2]

```C++
void SR_GTYPES_NS::ComputeShader::Dispatch (
    uint32_t x,
    uint32_t y,
    uint32_t z
) 
```




<hr>



### function Dispatch [2/2]

```C++
void SR_GTYPES_NS::ComputeShader::Dispatch () 
```




<hr>



### function EndCompute 

```C++
void SR_GTYPES_NS::ComputeShader::EndCompute () 
```




<hr>



### function GetPipeline 

```C++
SR_NODISCARD const SR_GRAPH_NS::Pipeline::Ptr & SR_GTYPES_NS::ComputeShader::GetPipeline () const
```




<hr>



### function GetShader 

```C++
SR_NODISCARD const SR_GTYPES_NS::Shader::Ptr & SR_GTYPES_NS::ComputeShader::GetShader () noexcept const
```




<hr>



### function ~ComputeShader 

```C++
SR_GTYPES_NS::ComputeShader::~ComputeShader () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD ComputeShader::Ptr SR_GTYPES_NS::ComputeShader::Load (
    const SR_UTILS_NS::Path & path
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Types/ComputeShader.h`

