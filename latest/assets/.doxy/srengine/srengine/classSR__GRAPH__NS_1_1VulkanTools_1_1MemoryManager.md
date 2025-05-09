

# Class SR\_GRAPH\_NS::VulkanTools::MemoryManager



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**VulkanTools**](namespaceSR__GRAPH__NS_1_1VulkanTools.md) **>** [**MemoryManager**](classSR__GRAPH__NS_1_1VulkanTools_1_1MemoryManager.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD int32\_t | [**AllocateDescriptorSet**](#function-allocatedescriptorset) (uint32\_t shaderProgram, const std::vector&lt; uint64\_t &gt; & types) <br> |
|  SR\_NODISCARD int32\_t | [**AllocateFBO**](#function-allocatefbo) (const [**VulkanFrameBufferAllocInfo**](structSR__GRAPH__NS_1_1VulkanTools_1_1VulkanFrameBufferAllocInfo.md) & info) <br> |
|  SR\_NODISCARD int32\_t | [**AllocateIBO**](#function-allocateibo) (uint32\_t buffSize, const void \* data) <br> |
|  SR\_NODISCARD int32\_t | [**AllocateSSBO**](#function-allocatessbo) (uint32\_t size, SSBOUsage usage) <br> |
|  SR\_NODISCARD int32\_t | [**AllocateShaderProgram**](#function-allocateshaderprogram) (EvoVulkan::Types::RenderPass renderPass) <br> |
|  SR\_NODISCARD int32\_t | [**AllocateTexture**](#function-allocatetexture-12) (const uint8\_t \* pixels, uint32\_t w, uint32\_t h, VkFormat format, VkFilter filter, TextureCompression compression, uint8\_t mipLevels, bool cpuUsage) <br> |
|  SR\_NODISCARD int32\_t | [**AllocateTexture**](#function-allocatetexture-22) (std::array&lt; const uint8\_t \*, 6 &gt; pixels, uint32\_t w, uint32\_t h, VkFormat format, VkFilter filter, uint8\_t mipLevels, bool cpuUsage) <br> |
|  SR\_NODISCARD int32\_t | [**AllocateUBO**](#function-allocateubo) (uint32\_t UBOSize) <br> |
|  SR\_NODISCARD int32\_t | [**AllocateVBO**](#function-allocatevbo) (uint32\_t buffSize, const void \* data) <br> |
|  void | [**ForEachFBO**](#function-foreachfbo) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(int32\_t, EvoVulkan::Complexes::FrameBuffer \*)&gt; & func) const<br> |
|  void | [**ForEachShader**](#function-foreachshader) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(int32\_t, EvoVulkan::Complexes::Shader \*)&gt; & func) const<br> |
|  void | [**Free**](#function-free) () <br> |
|  SR\_NODISCARD bool | [**FreeDescriptorSet**](#function-freedescriptorset) (uint32\_t id) <br> |
|  SR\_NODISCARD bool | [**FreeFBO**](#function-freefbo) (uint32\_t id) <br> |
|  SR\_NODISCARD bool | [**FreeIBO**](#function-freeibo) (uint32\_t id) <br> |
|  SR\_NODISCARD bool | [**FreeSSBO**](#function-freessbo) (uint32\_t id) <br> |
|  SR\_NODISCARD bool | [**FreeShaderProgram**](#function-freeshaderprogram) (uint32\_t id) <br> |
|  SR\_NODISCARD bool | [**FreeTexture**](#function-freetexture) (uint32\_t id) <br> |
|  SR\_NODISCARD bool | [**FreeUBO**](#function-freeubo) (uint32\_t id) <br> |
|  SR\_NODISCARD bool | [**FreeVBO**](#function-freevbo) (uint32\_t id) <br> |
|  SR\_NODISCARD const EvoVulkan::Types::DescriptorSet & | [**GetDescriptorSet**](#function-getdescriptorset-12) (uint32\_t id) const<br> |
|  SR\_NODISCARD EvoVulkan::Types::DescriptorSet & | [**GetDescriptorSet**](#function-getdescriptorset-22) (uint32\_t id) <br> |
|  SR\_NODISCARD uint32\_t | [**GetDescriptorSetsCount**](#function-getdescriptorsetscount) () const<br> |
|  SR\_NODISCARD const EvoVulkan::Complexes::FrameBuffer \* | [**GetFBO**](#function-getfbo-12) (uint32\_t id) const<br> |
|  SR\_NODISCARD EvoVulkan::Complexes::FrameBuffer \* | [**GetFBO**](#function-getfbo-22) (uint32\_t id) <br> |
|  SR\_NODISCARD uint32\_t | [**GetFBOsCount**](#function-getfboscount) () const<br> |
|  SR\_NODISCARD const EvoVulkan::Types::VmaBuffer \* | [**GetIBO**](#function-getibo-12) (uint32\_t id) const<br> |
|  SR\_NODISCARD EvoVulkan::Types::VmaBuffer \* | [**GetIBO**](#function-getibo-22) (uint32\_t id) <br> |
|  SR\_NODISCARD uint32\_t | [**GetIBOsCount**](#function-getiboscount) () const<br> |
|  SR\_NODISCARD const EvoVulkan::Types::VmaBuffer \* | [**GetSSBO**](#function-getssbo-12) (uint32\_t id) const<br> |
|  SR\_NODISCARD EvoVulkan::Types::VmaBuffer \* | [**GetSSBO**](#function-getssbo-22) (uint32\_t id) <br> |
|  SR\_NODISCARD uint32\_t | [**GetSSBOsCount**](#function-getssboscount) () const<br> |
|  SR\_NODISCARD const EvoVulkan::Complexes::Shader \* | [**GetShaderProgram**](#function-getshaderprogram-12) (uint32\_t id) const<br> |
|  SR\_NODISCARD EvoVulkan::Complexes::Shader \* | [**GetShaderProgram**](#function-getshaderprogram-22) (uint32\_t id) <br> |
|  SR\_NODISCARD uint32\_t | [**GetShaderProgramsCount**](#function-getshaderprogramscount) () const<br> |
|  SR\_NODISCARD const EvoVulkan::Types::Texture \* | [**GetTexture**](#function-gettexture-12) (uint32\_t id) const<br> |
|  SR\_NODISCARD EvoVulkan::Types::Texture \* | [**GetTexture**](#function-gettexture-22) (uint32\_t id) <br> |
|  SR\_NODISCARD uint32\_t | [**GetTexturesCount**](#function-gettexturescount) () const<br> |
|  SR\_NODISCARD const EvoVulkan::Types::VmaBuffer \* | [**GetUBO**](#function-getubo-12) (uint32\_t id) const<br> |
|  SR\_NODISCARD EvoVulkan::Types::VmaBuffer \* | [**GetUBO**](#function-getubo-22) (uint32\_t id) <br> |
|  SR\_NODISCARD uint32\_t | [**GetUBOsCount**](#function-getuboscount) () const<br> |
|  SR\_NODISCARD const EvoVulkan::Types::VmaBuffer \* | [**GetVBO**](#function-getvbo-12) (uint32\_t id) const<br> |
|  SR\_NODISCARD EvoVulkan::Types::VmaBuffer \* | [**GetVBO**](#function-getvbo-22) (uint32\_t id) <br> |
|  SR\_NODISCARD uint32\_t | [**GetVBOsCount**](#function-getvboscount) () const<br> |
|  SR\_NODISCARD bool | [**IsTextureValid**](#function-istexturevalid) (uint32\_t id) const<br> |
|  SR\_NODISCARD bool | [**ReAllocateFBO**](#function-reallocatefbo) (const [**VulkanFrameBufferAllocInfo**](structSR__GRAPH__NS_1_1VulkanTools_1_1VulkanFrameBufferAllocInfo.md) & info) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**MemoryManager**](classSR__GRAPH__NS_1_1VulkanTools_1_1MemoryManager.md) \* | [**Create**](#function-create) (EvoVulkan::Core::VulkanKernel \* kernel) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function AllocateDescriptorSet 

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateDescriptorSet (
    uint32_t shaderProgram,
    const std::vector< uint64_t > & types
) 
```




<hr>



### function AllocateFBO 

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateFBO (
    const VulkanFrameBufferAllocInfo & info
) 
```




<hr>



### function AllocateIBO 

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateIBO (
    uint32_t buffSize,
    const void * data
) 
```




<hr>



### function AllocateSSBO 

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateSSBO (
    uint32_t size,
    SSBOUsage usage
) 
```




<hr>



### function AllocateShaderProgram 

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateShaderProgram (
    EvoVulkan::Types::RenderPass renderPass
) 
```




<hr>



### function AllocateTexture [1/2]

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateTexture (
    const uint8_t * pixels,
    uint32_t w,
    uint32_t h,
    VkFormat format,
    VkFilter filter,
    TextureCompression compression,
    uint8_t mipLevels,
    bool cpuUsage
) 
```




<hr>



### function AllocateTexture [2/2]

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateTexture (
    std::array< const uint8_t *, 6 > pixels,
    uint32_t w,
    uint32_t h,
    VkFormat format,
    VkFilter filter,
    uint8_t mipLevels,
    bool cpuUsage
) 
```




<hr>



### function AllocateUBO 

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateUBO (
    uint32_t UBOSize
) 
```




<hr>



### function AllocateVBO 

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::VulkanTools::MemoryManager::AllocateVBO (
    uint32_t buffSize,
    const void * data
) 
```




<hr>



### function ForEachFBO 

```C++
inline void SR_GRAPH_NS::VulkanTools::MemoryManager::ForEachFBO (
    const SR_HTYPES_NS::Function < void(int32_t, EvoVulkan::Complexes::FrameBuffer *)> & func
) const
```




<hr>



### function ForEachShader 

```C++
inline void SR_GRAPH_NS::VulkanTools::MemoryManager::ForEachShader (
    const SR_HTYPES_NS::Function < void(int32_t, EvoVulkan::Complexes::Shader *)> & func
) const
```




<hr>



### function Free 

```C++
void SR_GRAPH_NS::VulkanTools::MemoryManager::Free () 
```




<hr>



### function FreeDescriptorSet 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeDescriptorSet (
    uint32_t id
) 
```




<hr>



### function FreeFBO 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeFBO (
    uint32_t id
) 
```




<hr>



### function FreeIBO 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeIBO (
    uint32_t id
) 
```




<hr>



### function FreeSSBO 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeSSBO (
    uint32_t id
) 
```




<hr>



### function FreeShaderProgram 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeShaderProgram (
    uint32_t id
) 
```




<hr>



### function FreeTexture 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeTexture (
    uint32_t id
) 
```




<hr>



### function FreeUBO 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeUBO (
    uint32_t id
) 
```




<hr>



### function FreeVBO 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanTools::MemoryManager::FreeVBO (
    uint32_t id
) 
```




<hr>



### function GetDescriptorSet [1/2]

```C++
inline SR_NODISCARD const EvoVulkan::Types::DescriptorSet & SR_GRAPH_NS::VulkanTools::MemoryManager::GetDescriptorSet (
    uint32_t id
) const
```




<hr>



### function GetDescriptorSet [2/2]

```C++
inline SR_NODISCARD EvoVulkan::Types::DescriptorSet & SR_GRAPH_NS::VulkanTools::MemoryManager::GetDescriptorSet (
    uint32_t id
) 
```




<hr>



### function GetDescriptorSetsCount 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::VulkanTools::MemoryManager::GetDescriptorSetsCount () const
```




<hr>



### function GetFBO [1/2]

```C++
inline SR_NODISCARD const EvoVulkan::Complexes::FrameBuffer * SR_GRAPH_NS::VulkanTools::MemoryManager::GetFBO (
    uint32_t id
) const
```




<hr>



### function GetFBO [2/2]

```C++
inline SR_NODISCARD EvoVulkan::Complexes::FrameBuffer * SR_GRAPH_NS::VulkanTools::MemoryManager::GetFBO (
    uint32_t id
) 
```




<hr>



### function GetFBOsCount 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::VulkanTools::MemoryManager::GetFBOsCount () const
```




<hr>



### function GetIBO [1/2]

```C++
inline SR_NODISCARD const EvoVulkan::Types::VmaBuffer * SR_GRAPH_NS::VulkanTools::MemoryManager::GetIBO (
    uint32_t id
) const
```




<hr>



### function GetIBO [2/2]

```C++
inline SR_NODISCARD EvoVulkan::Types::VmaBuffer * SR_GRAPH_NS::VulkanTools::MemoryManager::GetIBO (
    uint32_t id
) 
```




<hr>



### function GetIBOsCount 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::VulkanTools::MemoryManager::GetIBOsCount () const
```




<hr>



### function GetSSBO [1/2]

```C++
inline SR_NODISCARD const EvoVulkan::Types::VmaBuffer * SR_GRAPH_NS::VulkanTools::MemoryManager::GetSSBO (
    uint32_t id
) const
```




<hr>



### function GetSSBO [2/2]

```C++
inline SR_NODISCARD EvoVulkan::Types::VmaBuffer * SR_GRAPH_NS::VulkanTools::MemoryManager::GetSSBO (
    uint32_t id
) 
```




<hr>



### function GetSSBOsCount 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::VulkanTools::MemoryManager::GetSSBOsCount () const
```




<hr>



### function GetShaderProgram [1/2]

```C++
inline SR_NODISCARD const EvoVulkan::Complexes::Shader * SR_GRAPH_NS::VulkanTools::MemoryManager::GetShaderProgram (
    uint32_t id
) const
```




<hr>



### function GetShaderProgram [2/2]

```C++
inline SR_NODISCARD EvoVulkan::Complexes::Shader * SR_GRAPH_NS::VulkanTools::MemoryManager::GetShaderProgram (
    uint32_t id
) 
```




<hr>



### function GetShaderProgramsCount 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::VulkanTools::MemoryManager::GetShaderProgramsCount () const
```




<hr>



### function GetTexture [1/2]

```C++
inline SR_NODISCARD const EvoVulkan::Types::Texture * SR_GRAPH_NS::VulkanTools::MemoryManager::GetTexture (
    uint32_t id
) const
```




<hr>



### function GetTexture [2/2]

```C++
inline SR_NODISCARD EvoVulkan::Types::Texture * SR_GRAPH_NS::VulkanTools::MemoryManager::GetTexture (
    uint32_t id
) 
```




<hr>



### function GetTexturesCount 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::VulkanTools::MemoryManager::GetTexturesCount () const
```




<hr>



### function GetUBO [1/2]

```C++
inline SR_NODISCARD const EvoVulkan::Types::VmaBuffer * SR_GRAPH_NS::VulkanTools::MemoryManager::GetUBO (
    uint32_t id
) const
```




<hr>



### function GetUBO [2/2]

```C++
inline SR_NODISCARD EvoVulkan::Types::VmaBuffer * SR_GRAPH_NS::VulkanTools::MemoryManager::GetUBO (
    uint32_t id
) 
```




<hr>



### function GetUBOsCount 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::VulkanTools::MemoryManager::GetUBOsCount () const
```




<hr>



### function GetVBO [1/2]

```C++
inline SR_NODISCARD const EvoVulkan::Types::VmaBuffer * SR_GRAPH_NS::VulkanTools::MemoryManager::GetVBO (
    uint32_t id
) const
```




<hr>



### function GetVBO [2/2]

```C++
inline SR_NODISCARD EvoVulkan::Types::VmaBuffer * SR_GRAPH_NS::VulkanTools::MemoryManager::GetVBO (
    uint32_t id
) 
```




<hr>



### function GetVBOsCount 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::VulkanTools::MemoryManager::GetVBOsCount () const
```




<hr>



### function IsTextureValid 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::VulkanTools::MemoryManager::IsTextureValid (
    uint32_t id
) const
```




<hr>



### function ReAllocateFBO 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanTools::MemoryManager::ReAllocateFBO (
    const VulkanFrameBufferAllocInfo & info
) 
```




<hr>
## Public Static Functions Documentation




### function Create 

```C++
static inline MemoryManager * SR_GRAPH_NS::VulkanTools::MemoryManager::Create (
    EvoVulkan::Core::VulkanKernel * kernel
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Pipeline/Vulkan/VulkanMemory.h`

