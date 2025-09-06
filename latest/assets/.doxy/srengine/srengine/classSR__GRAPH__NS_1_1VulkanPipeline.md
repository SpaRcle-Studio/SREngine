

# Class SR\_GRAPH\_NS::VulkanPipeline



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**VulkanPipeline**](classSR__GRAPH__NS_1_1VulkanPipeline.md)








Inherits the following classes: [SR\_GRAPH\_NS::Pipeline](classSR__GRAPH__NS_1_1Pipeline.md)
















## Public Types inherited from SR_GRAPH_NS::Pipeline

See [SR\_GRAPH\_NS::Pipeline](classSR__GRAPH__NS_1_1Pipeline.md)

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) &gt; | [**ClearColors**](classSR__GRAPH__NS_1_1Pipeline.md#typedef-clearcolors)  <br> |
| typedef [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* | [**FramebufferPtr**](classSR__GRAPH__NS_1_1Pipeline.md#typedef-framebufferptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**Ptr**](classSR__GRAPH__NS_1_1Pipeline.md#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; [**SR\_GRAPH\_NS::RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) &gt; | [**RenderContextPtr**](classSR__GRAPH__NS_1_1Pipeline.md#typedef-rendercontextptr)  <br> |
| typedef int32\_t | [**ShaderProgram**](classSR__GRAPH__NS_1_1Pipeline.md#typedef-shaderprogram)  <br> |
| typedef [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**ShaderPtr**](classSR__GRAPH__NS_1_1Pipeline.md#typedef-shaderptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**Super**](classSR__GRAPH__NS_1_1Pipeline.md#typedef-super)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Window**](classSR__GRAPH__NS_1_1Window.md) &gt; | [**WindowPtr**](classSR__GRAPH__NS_1_1Pipeline.md#typedef-windowptr)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |












































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD int32\_t | [**AllocDescriptorSet**](#function-allocdescriptorset) (const std::vector&lt; DescriptorType &gt; & types) override<br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateCubeMap**](#function-allocatecubemap) (const [**SRCubeMapCreateInfo**](structSR__GRAPH__NS_1_1SRCubeMapCreateInfo.md) & createInfo) override<br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateFrameBuffer**](#function-allocateframebuffer) (const [**SRFrameBufferCreateInfo**](structSR__GRAPH__NS_1_1SRFrameBufferCreateInfo.md) & createInfo) override<br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateIBO**](#function-allocateibo) (const void \* pIndices, uint32\_t indexSize, size\_t count, int32\_t VBO) override<br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateSSBO**](#function-allocatessbo) (uint32\_t size, SSBOUsage usage) override<br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateShaderProgram**](#function-allocateshaderprogram) (const [**SRShaderCreateInfo**](structSR__GRAPH__NS_1_1SRShaderCreateInfo.md) & createInfo, int32\_t fbo) override<br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateTexture**](#function-allocatetexture) (const [**SRTextureCreateInfo**](structSR__GRAPH__NS_1_1SRTextureCreateInfo.md) & createInfo) override<br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateUBO**](#function-allocateubo) (uint32\_t uboSize) override<br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateVBO**](#function-allocatevbo) (const void \* pVertices, Vertices::VertexType type, size\_t count) override<br>_---------------------------------------_  _Работа с памятью ---------------------------------------------_ __ |
| virtual bool | [**BeginCmdBuffer**](#function-begincmdbuffer) () override<br>_Начало записи в буфер команд. Разделение необходимо некоторым графическим API._  |
| virtual bool | [**BeginCompute**](#function-begincompute) () override<br>_Начало вычислений в Compute Shader._  |
| virtual bool | [**BeginRender**](#function-beginrender) () override<br>_Начало рендера в кадровый буфер или в SwapChain._  |
| virtual void | [**BindAttachment**](#function-bindattachment) (uint8\_t activeTexture, uint32\_t textureId) override<br> |
| virtual bool | [**BindDescriptorSet**](#function-binddescriptorset) (uint32\_t descriptorSet) override<br>_Привязка UBO к набору дескрипторов. Поддерживается не всеми API._  |
| virtual void | [**BindFrameBuffer**](#function-bindframebuffer) (FramebufferPtr pFBO) override<br> |
| virtual void | [**BindIBO**](#function-bindibo) (uint32\_t IBO) override<br>_Index Buffer Object - биндим для рендера вершин по индексам_  |
| virtual void | [**BindSSBO**](#function-bindssbo) (uint32\_t SSBO) override<br>_Shader Storage Buffer Object - обеспечивает привязку для передачм данных в шейдеры_  |
| virtual void | [**BindTexture**](#function-bindtexture) (uint8\_t activeTexture, uint32\_t textureId) override<br> |
| virtual void | [**BindUBO**](#function-bindubo) (uint32\_t UBO) override<br>[_**Uniform**_](structSR__GRAPH__NS_1_1Uniform.md) _Buffer Object - обеспечивает привязку для передачм данных в шейдеры_ |
| virtual void | [**BindVBO**](#function-bindvbo) (uint32\_t VBO) override<br>_Vertex Buffer Object - биндими для рендера вершин_  |
| virtual void | [**ClearBuffers**](#function-clearbuffers-13) () override<br> |
| virtual void | [**ClearBuffers**](#function-clearbuffers-23) (float\_t r, float\_t g, float\_t b, float\_t a, float\_t depth, uint8\_t colorCount) override<br> |
| virtual void | [**ClearBuffers**](#function-clearbuffers-33) (const ClearColors & clearColors, std::optional&lt; float\_t &gt; depth) override<br> |
| virtual void | [**ClearColorBuffer**](#function-clearcolorbuffer) (const ClearColors & clearColors) override<br> |
| virtual void | [**ClearDepthBuffer**](#function-cleardepthbuffer) (float\_t depth) override<br> |
| virtual bool | [**Destroy**](#function-destroy) () override<br>_Чистим все данные графического конфейера и де-инициализируем его_  |
| virtual void | [**Dispatch**](#function-dispatch) (uint32\_t groupCountX, uint32\_t groupCountY, uint32\_t groupCountZ) override<br>_-----------------------------------------_  _Вычисления -------------------------------------------------_ __ |
| virtual void | [**Draw**](#function-draw) (uint32\_t count) override<br>_Обычная отрисовка вершин_  |
| virtual void | [**DrawFrame**](#function-drawframe) () override<br> |
| virtual void | [**DrawIndices**](#function-drawindices) (uint32\_t count) override<br>_---------------------------------------_  _Вызовы отрисовки ---------------------------------------------_ __ |
| virtual void | [**EndCmdBuffer**](#function-endcmdbuffer) () override<br>_Конец записи в буфер команд. Разделение необходимо некоторым графическим API._  |
| virtual void | [**EndCompute**](#function-endcompute) () override<br>_Конец вычислений в Compute Shader._  |
| virtual void | [**EndRender**](#function-endrender) () override<br>_Обязательно нужно вызвать после успешного вызова BeginRender._  |
| virtual void | [**FlushSSBO**](#function-flushssbo) (uint32\_t SSBO, uint64\_t offset, uint64\_t size) override<br> |
| virtual bool | [**FreeCubeMap**](#function-freecubemap) (int32\_t \* id) override<br> |
| virtual bool | [**FreeDescriptorSet**](#function-freedescriptorset) (int32\_t \* id) override<br> |
| virtual bool | [**FreeFBO**](#function-freefbo) (int32\_t \* id) override<br> |
| virtual bool | [**FreeIBO**](#function-freeibo) (int32\_t \* id) override<br> |
| virtual bool | [**FreeSSBO**](#function-freessbo) (int32\_t \* id) override<br> |
| virtual bool | [**FreeShader**](#function-freeshader) (int32\_t \* id) override<br> |
| virtual bool | [**FreeTexture**](#function-freetexture) (int32\_t \* id) override<br> |
| virtual bool | [**FreeUBO**](#function-freeubo) (int32\_t \* id) override<br> |
| virtual bool | [**FreeVBO**](#function-freevbo) (int32\_t \* id) override<br> |
| virtual SR\_NODISCARD uint8\_t | [**GetBuildIterationsCount**](#function-getbuilditerationscount) () noexcept override const<br> |
| virtual SR\_NODISCARD void \* | [**GetCurrentFBOHandle**](#function-getcurrentfbohandle) () override const<br> |
| virtual SR\_NODISCARD uint8\_t | [**GetCurrentFrameIndex**](#function-getcurrentframeindex) () override const<br> |
| virtual SR\_NODISCARD void \* | [**GetCurrentShaderHandle**](#function-getcurrentshaderhandle) () override const<br> |
| virtual SR\_NODISCARD std::set&lt; void \* &gt; | [**GetFBOHandles**](#function-getfbohandles) () override const<br> |
| virtual SR\_NODISCARD uint8\_t | [**GetFrameBufferSampleCount**](#function-getframebuffersamplecount) () override const<br> |
|  SR\_NODISCARD EvoVulkan::Core::VulkanKernel \* | [**GetKernel**](#function-getkernel) () noexcept const<br> |
|  SR\_NODISCARD [**VulkanTools::MemoryManager**](classSR__GRAPH__NS_1_1VulkanTools_1_1MemoryManager.md) \* | [**GetMemoryManager**](#function-getmemorymanager) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**GetPixelColor**](#function-getpixelcolor) (uint32\_t textureId, uint32\_t x, uint32\_t y) override<br> |
| virtual SR\_NODISCARD std::string | [**GetRenderer**](#function-getrenderer) () override const<br> |
| virtual SR\_NODISCARD std::set&lt; void \* &gt; | [**GetShaderHandles**](#function-getshaderhandles) () override const<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetSwapchainImagesCount**](#function-getswapchainimagescount) () override const<br> |
| virtual SR\_NODISCARD PipelineType | [**GetType**](#function-gettype) () noexcept override const<br> |
| virtual SR\_NODISCARD uint64\_t | [**GetUsedMemory**](#function-getusedmemory) () override const<br> |
| virtual SR\_NODISCARD std::string | [**GetVendor**](#function-getvendor) () override const<br>_------------------------------------_  _Вспомогательные методы ------------------------------------------_ __ |
| virtual SR\_NODISCARD std::string | [**GetVersion**](#function-getversion) () override const<br> |
| virtual bool | [**Init**](#function-init) () override<br>_Подключаем окно и настраиваем взаимодействие рендера с ним_  |
| virtual bool | [**InitOverlay**](#function-initoverlay) () override<br>_---------------------------------------_  _Работа с_[_**Overlay**_](classSR__GRAPH__NS_1_1Overlay.md) _---------------------------------------------_ __ |
| virtual bool | [**IsSamplerValid**](#function-issamplervalid) (int32\_t id) override const<br> |
| virtual SR\_NODISCARD bool | [**IsShaderConstantSupport**](#function-isshaderconstantsupport) () noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**IsVSyncEnabled**](#function-isvsyncenabled) () override const<br> |
| virtual bool | [**MapSSBO**](#function-mapssbo) (uint32\_t SSBO, void \*\* ppData) override<br> |
| virtual void | [**OnMultiSampleChanged**](#function-onmultisamplechanged) () override<br>_-------------------------------------_  _Мультисемплинг и VSync -----------------------------------------_ __ |
| virtual void | [**OnResize**](#function-onresize) (const SR\_MATH\_NS::UVector2 & size) override<br> |
| virtual bool | [**PostInit**](#function-postinit) () override<br>_Профайлинг и прочие пост-штучки_  |
| virtual bool | [**PreInit**](#function-preinit) (const [**PipelinePreInitInfo**](structSR__GRAPH__NS_1_1PipelinePreInitInfo.md) & info) override<br>_-------------------------------------_  _Инициализация рендера ------------------------------------------_ __ |
| virtual void | [**PrepareFrame**](#function-prepareframe) () override<br>_------------------------------------_  _Главные методы рендера ------------------------------------------_ __ |
| virtual void | [**PushConstants**](#function-pushconstants) (void \* pData, uint64\_t size) override<br> |
| virtual void | [**ReadSSBO**](#function-readssbo) (uint32\_t SSBO, void \* pData, uint64\_t size) override<br>_Читает данные из SSBO в память_  |
| virtual void | [**ResetLastShader**](#function-resetlastshader) () override<br> |
| virtual void | [**ResetSubmitQueue**](#function-resetsubmitqueue) () override<br> |
| virtual void | [**SetCurrentFrameBuffer**](#function-setcurrentframebuffer) (FramebufferPtr pFrameBuffer) override<br> |
| virtual void | [**SetDirty**](#function-setdirty) (bool dirty) override<br> |
| virtual void | [**SetOverlayEnabled**](#function-setoverlayenabled) (OverlayType overlayType, bool enabled) override<br> |
| virtual void | [**SetScissor**](#function-setscissor) (int32\_t width, int32\_t height) override<br> |
| virtual void | [**SetSwapchainImagesCount**](#function-setswapchainimagescount) (uint16\_t count) override<br> |
| virtual void | [**SetVSyncEnabled**](#function-setvsyncenabled) (bool enabled) override<br> |
| virtual void | [**SetViewport**](#function-setviewport) (int32\_t width, int32\_t height) override<br> |
| virtual void | [**UnMapSSBO**](#function-unmapssbo) (uint32\_t SSBO) override<br> |
| virtual void | [**UnUseShader**](#function-unuseshader) () override<br> |
| virtual void | [**UpdateDescriptorSets**](#function-updatedescriptorsets) (uint32\_t descriptorSet, const SRDescriptorUpdateInfos & updateInfo) override<br>_Привязываем к дескриптору юниформы. Работает не во всех API._  |
| virtual void | [**UpdateSSBO**](#function-updatessbo) (uint32\_t SSBO, void \* pData, uint64\_t size) override<br>_Обеспечивает обновление данных в шейдере_  |
| virtual void | [**UpdateUBO**](#function-updateubo) (uint32\_t UBO, void \* pData, uint64\_t size) override<br>_Обеспечивает обновление данных в шейдере_  |
| virtual void | [**UseShader**](#function-useshader) (uint32\_t shaderProgram) override<br>_------------------------------------------_  _Биндинги --------------------------------------------------_ __ |
|   | [**VulkanPipeline**](#function-vulkanpipeline) (const RenderContextPtr & pContext) <br> |
| virtual void | [**WaitComputeIdle**](#function-waitcomputeidle) () override<br> |
| virtual void | [**WaitRenderIdle**](#function-waitrenderidle) () override<br> |
|   | [**~VulkanPipeline**](#function-vulkanpipeline) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::Pipeline

See [SR\_GRAPH\_NS::Pipeline](classSR__GRAPH__NS_1_1Pipeline.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD int32\_t | [**AllocDescriptorSet**](classSR__GRAPH__NS_1_1Pipeline.md#function-allocdescriptorset) (const std::vector&lt; DescriptorType &gt; & types) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateCubeMap**](classSR__GRAPH__NS_1_1Pipeline.md#function-allocatecubemap) (const [**SRCubeMapCreateInfo**](structSR__GRAPH__NS_1_1SRCubeMapCreateInfo.md) & createInfo) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateFrameBuffer**](classSR__GRAPH__NS_1_1Pipeline.md#function-allocateframebuffer) (const [**SRFrameBufferCreateInfo**](structSR__GRAPH__NS_1_1SRFrameBufferCreateInfo.md) & createInfo) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateIBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-allocateibo) (const void \* pIndices, uint32\_t indexSize, size\_t count, int32\_t VBO) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateSSBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-allocatessbo) (uint32\_t ssboSize, SSBOUsage usage) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateShaderProgram**](classSR__GRAPH__NS_1_1Pipeline.md#function-allocateshaderprogram) (const [**SRShaderCreateInfo**](structSR__GRAPH__NS_1_1SRShaderCreateInfo.md) & createInfo, int32\_t fbo) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateTexture**](classSR__GRAPH__NS_1_1Pipeline.md#function-allocatetexture) (const [**SRTextureCreateInfo**](structSR__GRAPH__NS_1_1SRTextureCreateInfo.md) & createInfo) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateUBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-allocateubo) (uint32\_t uboSize) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateVBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-allocatevbo-12) (const void \* pVertices, Vertices::VertexType type, size\_t count) <br>_---------------------------------------_  _Работа с памятью ---------------------------------------------_ __ |
| virtual SR\_NODISCARD int32\_t | [**AllocateVBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-allocatevbo-22) (const [**SR\_UTILS\_NS::Vertex**](structSR__UTILS__NS_1_1Vertex.md) \* pVertices, Vertices::VertexType type, size\_t count) <br>_Продвинутая версия AllocateVBO, может сама выполнить преобразование типа памяти базовых вершин к нужному выравниванию._  |
| virtual bool | [**BeginCmdBuffer**](classSR__GRAPH__NS_1_1Pipeline.md#function-begincmdbuffer) () <br>_Начало записи в буфер команд. Разделение необходимо некоторым графическим API._  |
| virtual bool | [**BeginCompute**](classSR__GRAPH__NS_1_1Pipeline.md#function-begincompute) () <br>_Начало вычислений в Compute Shader._  |
| virtual bool | [**BeginDrawOverlay**](classSR__GRAPH__NS_1_1Pipeline.md#function-begindrawoverlay) (OverlayType overlayType) <br> |
| virtual bool | [**BeginRender**](classSR__GRAPH__NS_1_1Pipeline.md#function-beginrender) () <br>_Начало рендера в кадровый буфер или в SwapChain._  |
| virtual void | [**BindAttachment**](classSR__GRAPH__NS_1_1Pipeline.md#function-bindattachment) (uint8\_t activeTexture, uint32\_t textureId) <br> |
| virtual bool | [**BindDescriptorSet**](classSR__GRAPH__NS_1_1Pipeline.md#function-binddescriptorset) (uint32\_t descriptorSet) <br>_Привязка UBO к набору дескрипторов. Поддерживается не всеми API._  |
| virtual void | [**BindFrameBuffer**](classSR__GRAPH__NS_1_1Pipeline.md#function-bindframebuffer) (FramebufferPtr pFBO) <br> |
| virtual void | [**BindIBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-bindibo) (uint32\_t IBO) <br>_Index Buffer Object - биндим для рендера вершин по индексам_  |
| virtual void | [**BindSSBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-bindssbo) (uint32\_t SSBO) <br>_Shader Storage Buffer Object - обеспечивает привязку для передачм данных в шейдеры_  |
| virtual void | [**BindTexture**](classSR__GRAPH__NS_1_1Pipeline.md#function-bindtexture) (uint8\_t activeTexture, uint32\_t textureId) <br> |
| virtual void | [**BindUBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-bindubo) (uint32\_t UBO) <br>[_**Uniform**_](structSR__GRAPH__NS_1_1Uniform.md) _Buffer Object - обеспечивает привязку для передачм данных в шейдеры_ |
| virtual void | [**BindVBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-bindvbo) (uint32\_t VBO) <br>_Vertex Buffer Object - биндими для рендера вершин_  |
| virtual void | [**ClearBuffers**](classSR__GRAPH__NS_1_1Pipeline.md#function-clearbuffers-13) () <br> |
| virtual void | [**ClearBuffers**](classSR__GRAPH__NS_1_1Pipeline.md#function-clearbuffers-23) (float\_t r, float\_t g, float\_t b, float\_t a, float\_t depth, uint8\_t colorCount) <br> |
| virtual void | [**ClearBuffers**](classSR__GRAPH__NS_1_1Pipeline.md#function-clearbuffers-33) (const ClearColors & clearColors, std::optional&lt; float\_t &gt; depth) <br> |
| virtual void | [**ClearColorBuffer**](classSR__GRAPH__NS_1_1Pipeline.md#function-clearcolorbuffer) (const ClearColors & clearColors) <br> |
| virtual void | [**ClearDepthBuffer**](classSR__GRAPH__NS_1_1Pipeline.md#function-cleardepthbuffer) (float\_t depth) <br> |
| virtual void | [**ClearFrameBuffersQueue**](classSR__GRAPH__NS_1_1Pipeline.md#function-clearframebuffersqueue) () <br>_Вызывается в начале построения сцены рендера, чистит очередь рендера._  |
| virtual bool | [**Destroy**](classSR__GRAPH__NS_1_1Pipeline.md#function-destroy) () <br>_Чистим все данные графического конфейера и де-инициализируем его_  |
| virtual void | [**DestroyOverlay**](classSR__GRAPH__NS_1_1Pipeline.md#function-destroyoverlay) () <br> |
| virtual void | [**Dispatch**](classSR__GRAPH__NS_1_1Pipeline.md#function-dispatch) (uint32\_t groupCountX, uint32\_t groupCountY, uint32\_t groupCountZ) <br>_-----------------------------------------_  _Вычисления -------------------------------------------------_ __ |
| virtual void | [**Draw**](classSR__GRAPH__NS_1_1Pipeline.md#function-draw) (uint32\_t count) <br>_Обычная отрисовка вершин_  |
| virtual void | [**DrawFrame**](classSR__GRAPH__NS_1_1Pipeline.md#function-drawframe) () <br> |
| virtual void | [**DrawIndices**](classSR__GRAPH__NS_1_1Pipeline.md#function-drawindices) (uint32\_t count) <br>_---------------------------------------_  _Вызовы отрисовки ---------------------------------------------_ __ |
| virtual void | [**EndCmdBuffer**](classSR__GRAPH__NS_1_1Pipeline.md#function-endcmdbuffer) () <br>_Конец записи в буфер команд. Разделение необходимо некоторым графическим API._  |
| virtual void | [**EndCompute**](classSR__GRAPH__NS_1_1Pipeline.md#function-endcompute) () <br>_Конец вычислений в Compute Shader._  |
| virtual void | [**EndDrawOverlay**](classSR__GRAPH__NS_1_1Pipeline.md#function-enddrawoverlay) (OverlayType overlayType) <br> |
| virtual void | [**EndRender**](classSR__GRAPH__NS_1_1Pipeline.md#function-endrender) () <br>_Обязательно нужно вызвать после успешного вызова BeginRender._  |
| virtual void | [**FlushSSBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-flushssbo) (uint32\_t SSBO, uint64\_t offset, uint64\_t size) <br> |
| virtual bool | [**FreeCubeMap**](classSR__GRAPH__NS_1_1Pipeline.md#function-freecubemap) (int32\_t \* id) <br> |
| virtual bool | [**FreeDescriptorSet**](classSR__GRAPH__NS_1_1Pipeline.md#function-freedescriptorset) (int32\_t \* id) <br> |
| virtual bool | [**FreeFBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-freefbo) (int32\_t \* id) <br> |
| virtual bool | [**FreeIBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-freeibo) (int32\_t \* id) <br> |
| virtual bool | [**FreeSSBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-freessbo) (int32\_t \* id) <br> |
| virtual bool | [**FreeShader**](classSR__GRAPH__NS_1_1Pipeline.md#function-freeshader) (int32\_t \* id) <br> |
| virtual bool | [**FreeTexture**](classSR__GRAPH__NS_1_1Pipeline.md#function-freetexture) (int32\_t \* id) <br> |
| virtual bool | [**FreeUBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-freeubo) (int32\_t \* id) <br> |
| virtual bool | [**FreeVBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-freevbo) (int32\_t \* id) <br> |
| virtual SR\_NODISCARD uint8\_t | [**GetBuildIterationsCount**](classSR__GRAPH__NS_1_1Pipeline.md#function-getbuilditerationscount) () noexcept const<br> |
|  SR\_NODISCARD const [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) & | [**GetBuildState**](classSR__GRAPH__NS_1_1Pipeline.md#function-getbuildstate) (uint8\_t frameIndex) const<br> |
|  SR\_NODISCARD int32\_t | [**GetCurrentDescriptorSet**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentdescriptorset) () noexcept const<br> |
| virtual SR\_NODISCARD void \* | [**GetCurrentFBOHandle**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentfbohandle) () const<br> |
|  SR\_NODISCARD FramebufferPtr | [**GetCurrentFrameBuffer**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentframebuffer) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetCurrentFrameBufferId**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentframebufferid) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetCurrentFrameBufferLayer**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentframebufferlayer) () noexcept const<br> |
| virtual SR\_NODISCARD uint8\_t | [**GetCurrentFrameIndex**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentframeindex) () const<br> |
|  SR\_NODISCARD [**RenderStrategy**](classSR__GRAPH__NS_1_1RenderStrategy.md) \* | [**GetCurrentRenderStrategy**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentrenderstrategy) () noexcept const<br> |
|  SR\_NODISCARD ShaderPtr | [**GetCurrentShader**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentshader) () const<br> |
| virtual SR\_NODISCARD void \* | [**GetCurrentShaderHandle**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentshaderhandle) () const<br> |
|  SR\_NODISCARD int32\_t | [**GetCurrentShaderId**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentshaderid) () const<br> |
|  SR\_NODISCARD int32\_t | [**GetCurrentUBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentubo) () const<br> |
| virtual SR\_NODISCARD std::set&lt; void \* &gt; | [**GetFBOHandles**](classSR__GRAPH__NS_1_1Pipeline.md#function-getfbohandles) () const<br> |
| virtual SR\_NODISCARD uint8\_t | [**GetFrameBufferSampleCount**](classSR__GRAPH__NS_1_1Pipeline.md#function-getframebuffersamplecount) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetFramesPerSecond**](classSR__GRAPH__NS_1_1Pipeline.md#function-getframespersecond) () noexcept const<br> |
| virtual const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Overlay**](classSR__GRAPH__NS_1_1Overlay.md) &gt; & | [**GetOverlay**](classSR__GRAPH__NS_1_1Pipeline.md#function-getoverlay) (OverlayType overlayType) const<br> |
| virtual void \* | [**GetOverlayTextureDescriptorSet**](classSR__GRAPH__NS_1_1Pipeline.md#function-getoverlaytexturedescriptorset) (uint32\_t textureId, OverlayType overlayType) const<br> |
| virtual SR\_NODISCARD [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**GetPixelColor**](classSR__GRAPH__NS_1_1Pipeline.md#function-getpixelcolor) (uint32\_t textureId, uint32\_t x, uint32\_t y) <br> |
|  SR\_NODISCARD const [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) & | [**GetPreviousState**](classSR__GRAPH__NS_1_1Pipeline.md#function-getpreviousstate) () const<br> |
|  SR\_NODISCARD [**FrameBufferQueue**](classSR__GRAPH__NS_1_1FrameBufferQueue.md) & | [**GetQueue**](classSR__GRAPH__NS_1_1Pipeline.md#function-getqueue) () noexcept<br> |
|  SR\_NODISCARD RenderContextPtr | [**GetRenderContext**](classSR__GRAPH__NS_1_1Pipeline.md#function-getrendercontext) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetRenderStageId**](classSR__GRAPH__NS_1_1Pipeline.md#function-getrenderstageid) () const<br> |
| virtual SR\_NODISCARD std::string | [**GetRenderer**](classSR__GRAPH__NS_1_1Pipeline.md#function-getrenderer) () const<br> |
|  SR\_NODISCARD uint8\_t | [**GetSamplesCount**](classSR__GRAPH__NS_1_1Pipeline.md#function-getsamplescount) () const<br> |
| virtual SR\_NODISCARD std::set&lt; void \* &gt; | [**GetShaderHandles**](classSR__GRAPH__NS_1_1Pipeline.md#function-getshaderhandles) () const<br> |
|  SR\_NODISCARD const [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) & | [**GetState**](classSR__GRAPH__NS_1_1Pipeline.md#function-getstate) () const<br> |
| virtual SR\_NODISCARD uint8\_t | [**GetSupportedSamples**](classSR__GRAPH__NS_1_1Pipeline.md#function-getsupportedsamples) () noexcept const<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetSwapchainImagesCount**](classSR__GRAPH__NS_1_1Pipeline.md#function-getswapchainimagescount) () const<br> |
| virtual SR\_NODISCARD PipelineType | [**GetType**](classSR__GRAPH__NS_1_1Pipeline.md#function-gettype) () noexcept const = 0<br> |
| virtual uint64\_t | [**GetUsedMemory**](classSR__GRAPH__NS_1_1Pipeline.md#function-getusedmemory) () const<br> |
| virtual SR\_NODISCARD std::string | [**GetVendor**](classSR__GRAPH__NS_1_1Pipeline.md#function-getvendor) () const<br>_------------------------------------_  _Вспомогательные методы ------------------------------------------_ __ |
| virtual SR\_NODISCARD std::string | [**GetVersion**](classSR__GRAPH__NS_1_1Pipeline.md#function-getversion) () const<br> |
|  SR\_NODISCARD WindowPtr | [**GetWindow**](classSR__GRAPH__NS_1_1Pipeline.md#function-getwindow) () const<br> |
| virtual bool | [**HasActiveOverlay**](classSR__GRAPH__NS_1_1Pipeline.md#function-hasactiveoverlay) () const<br> |
| virtual bool | [**Init**](classSR__GRAPH__NS_1_1Pipeline.md#function-init) () <br>_Подключаем окно и настраиваем взаимодействие рендера с ним_  |
| virtual bool | [**InitOverlay**](classSR__GRAPH__NS_1_1Pipeline.md#function-initoverlay) () <br>_---------------------------------------_  _Работа с_[_**Overlay**_](classSR__GRAPH__NS_1_1Overlay.md) _---------------------------------------------_ __ |
|  SR\_NODISCARD bool | [**IsDirty**](classSR__GRAPH__NS_1_1Pipeline.md#function-isdirty) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsFBOQueueValid**](classSR__GRAPH__NS_1_1Pipeline.md#function-isfboqueuevalid) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsMultiSamplingSupported**](classSR__GRAPH__NS_1_1Pipeline.md#function-ismultisamplingsupported) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsRenderState**](classSR__GRAPH__NS_1_1Pipeline.md#function-isrenderstate) () noexcept const<br> |
| virtual bool | [**IsSamplerValid**](classSR__GRAPH__NS_1_1Pipeline.md#function-issamplervalid) (int32\_t id) const<br> |
|  SR\_NODISCARD bool | [**IsShaderChanged**](classSR__GRAPH__NS_1_1Pipeline.md#function-isshaderchanged) () noexcept const<br>_Изменился ли текущий шейдер после UseShader. Даже если был вызван UnUseShader. Низкоуровневая проверка._  |
| virtual SR\_NODISCARD bool | [**IsShaderConstantSupport**](classSR__GRAPH__NS_1_1Pipeline.md#function-isshaderconstantsupport) () const<br> |
| virtual SR\_NODISCARD bool | [**IsVSyncEnabled**](classSR__GRAPH__NS_1_1Pipeline.md#function-isvsyncenabled) () const<br> |
| virtual bool | [**MapSSBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-mapssbo) (uint32\_t SSBO, void \*\* ppData) <br> |
|  void | [**OnFrameBuildEnd**](classSR__GRAPH__NS_1_1Pipeline.md#function-onframebuildend) () <br> |
| virtual void | [**OnMultiSampleChanged**](classSR__GRAPH__NS_1_1Pipeline.md#function-onmultisamplechanged) () <br>_-------------------------------------_  _Мультисемплинг и VSync -----------------------------------------_ __ |
| virtual void | [**OnResize**](classSR__GRAPH__NS_1_1Pipeline.md#function-onresize) (const SR\_MATH\_NS::UVector2 & size) <br> |
|   | [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md#function-pipeline) (const RenderContextPtr & pContext) <br> |
| virtual void | [**PipelineError**](classSR__GRAPH__NS_1_1Pipeline.md#function-pipelineerror) (const std::string & msg) const<br> |
| virtual bool | [**PostInit**](classSR__GRAPH__NS_1_1Pipeline.md#function-postinit) () <br>_Профайлинг и прочие пост-штучки_  |
| virtual bool | [**PreInit**](classSR__GRAPH__NS_1_1Pipeline.md#function-preinit) (const [**PipelinePreInitInfo**](structSR__GRAPH__NS_1_1PipelinePreInitInfo.md) & info) <br>_-------------------------------------_  _Инициализация рендера ------------------------------------------_ __ |
| virtual void | [**PrepareFrame**](classSR__GRAPH__NS_1_1Pipeline.md#function-prepareframe) () <br>_------------------------------------_  _Главные методы рендера ------------------------------------------_ __ |
| virtual void | [**PrepareOverlay**](classSR__GRAPH__NS_1_1Pipeline.md#function-prepareoverlay) (OverlayType overlayType) <br> |
| virtual void | [**PushConstants**](classSR__GRAPH__NS_1_1Pipeline.md#function-pushconstants) (void \* pData, uint64\_t size) <br> |
| virtual void | [**ReCreateOverlay**](classSR__GRAPH__NS_1_1Pipeline.md#function-recreateoverlay) () <br> |
| virtual void | [**ReadSSBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-readssbo) (uint32\_t SSBO, void \* pData, uint64\_t size) <br>_Читает данные из SSBO в память_  |
| virtual void | [**ResetLastShader**](classSR__GRAPH__NS_1_1Pipeline.md#function-resetlastshader) () <br> |
| virtual void | [**ResetSubmitQueue**](classSR__GRAPH__NS_1_1Pipeline.md#function-resetsubmitqueue) () <br> |
| virtual void | [**SetCurrentFrameBuffer**](classSR__GRAPH__NS_1_1Pipeline.md#function-setcurrentframebuffer) (FramebufferPtr pFrameBuffer) <br> |
| virtual void | [**SetCurrentFrameBufferLayer**](classSR__GRAPH__NS_1_1Pipeline.md#function-setcurrentframebufferlayer) (uint32\_t layer) <br> |
| virtual void | [**SetCurrentRenderStrategy**](classSR__GRAPH__NS_1_1Pipeline.md#function-setcurrentrenderstrategy) ([**RenderStrategy**](classSR__GRAPH__NS_1_1RenderStrategy.md) \* pStrategy) <br> |
| virtual void | [**SetCurrentShader**](classSR__GRAPH__NS_1_1Pipeline.md#function-setcurrentshader) (ShaderPtr pShader) <br> |
| virtual void | [**SetCurrentShaderId**](classSR__GRAPH__NS_1_1Pipeline.md#function-setcurrentshaderid) (int32\_t id) <br> |
| virtual void | [**SetDirty**](classSR__GRAPH__NS_1_1Pipeline.md#function-setdirty) (bool dirty) <br> |
| virtual void | [**SetOverlayEnabled**](classSR__GRAPH__NS_1_1Pipeline.md#function-setoverlayenabled) (OverlayType overlayType, bool enabled) <br> |
| virtual void | [**SetOverlaySurfaceDirty**](classSR__GRAPH__NS_1_1Pipeline.md#function-setoverlaysurfacedirty) () <br> |
| virtual void | [**SetRenderStageId**](classSR__GRAPH__NS_1_1Pipeline.md#function-setrenderstageid) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id) <br> |
| virtual void | [**SetSampleCount**](classSR__GRAPH__NS_1_1Pipeline.md#function-setsamplecount) (uint8\_t count) <br> |
| virtual void | [**SetScissor**](classSR__GRAPH__NS_1_1Pipeline.md#function-setscissor) (int32\_t width=-1, int32\_t height=-1) <br> |
| virtual void | [**SetSwapchainImagesCount**](classSR__GRAPH__NS_1_1Pipeline.md#function-setswapchainimagescount) (uint16\_t count) <br> |
| virtual void | [**SetVSyncEnabled**](classSR__GRAPH__NS_1_1Pipeline.md#function-setvsyncenabled) (bool enabled) <br> |
| virtual void | [**SetViewport**](classSR__GRAPH__NS_1_1Pipeline.md#function-setviewport) (int32\_t width=-1, int32\_t height=-1) <br> |
| virtual void | [**SwitchWindow**](classSR__GRAPH__NS_1_1Pipeline.md#function-switchwindow) (const WindowPtr & pWindow) <br> |
| virtual void | [**UnMapSSBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-unmapssbo) (uint32\_t SSBO) <br> |
| virtual void | [**UnUseShader**](classSR__GRAPH__NS_1_1Pipeline.md#function-unuseshader) () <br> |
| virtual void | [**UpdateDescriptorSets**](classSR__GRAPH__NS_1_1Pipeline.md#function-updatedescriptorsets) (uint32\_t descriptorSet, const SRDescriptorUpdateInfos & updateInfo) <br>_Привязываем к дескриптору юниформы. Работает не во всех API._  |
| virtual void | [**UpdateMultiSampling**](classSR__GRAPH__NS_1_1Pipeline.md#function-updatemultisampling) () <br> |
| virtual void | [**UpdateSSBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-updatessbo) (uint32\_t SSBO, void \* pData, uint64\_t size) <br>_Обеспечивает обновление данных в шейдере_  |
| virtual void | [**UpdateUBO**](classSR__GRAPH__NS_1_1Pipeline.md#function-updateubo) (uint32\_t UBO, void \* pData, uint64\_t size) <br>_Обеспечивает обновление данных в шейдере_  |
| virtual void | [**UseShader**](classSR__GRAPH__NS_1_1Pipeline.md#function-useshader) (uint32\_t shaderProgram) <br>_------------------------------------------_  _Биндинги --------------------------------------------------_ __ |
| virtual void | [**WaitComputeIdle**](classSR__GRAPH__NS_1_1Pipeline.md#function-waitcomputeidle) () <br> |
| virtual void | [**WaitRenderIdle**](classSR__GRAPH__NS_1_1Pipeline.md#function-waitrenderidle) () <br> |
| virtual  | [**~Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md#function-pipeline) () <br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
|  SR\_NODISCARD const void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-12) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br> |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getthis) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-22) () <br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-incrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**PolymorphicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-polymorphiccast) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-recursivelockifvalid) () noexcept const<br> |
|  U | [**ReinterpretCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reinterpretcast) () <br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reset) () override<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtr.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) override<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-15) () = default<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-25) (const T \* constPtr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-35) (const T \* constPtr, SR\_UTILS\_NS::SharedPtrPolicy policy) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-45) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) const & ptr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-55) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) && ptr) noexcept<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**StaticCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-staticcast) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-tryrecursivelockifvalid) () noexcept const<br> |
|  void | [**Unlock**](classSR__HTYPES__NS_1_1SharedPtr.md#function-unlock) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_2) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_3) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_4) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_5) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|   | [**~SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-decrementpointer) () = 0<br> |
|  const [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-12) () const<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getsrclass) () const = 0<br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-incrementpointer) () = 0<br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-reset) () = 0<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) = 0<br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-12) () <br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-22) ([**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* data) <br> |
| virtual SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-valid) () const = 0<br> |
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |






## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |






















## Protected Attributes inherited from SR_GRAPH_NS::Pipeline

See [SR\_GRAPH\_NS::Pipeline](classSR__GRAPH__NS_1_1Pipeline.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_HTYPES\_NS::PoolSet**](classSR__HTYPES__NS_1_1PoolSet.md)&lt; bool &gt; | [**m\_bindedDescriptors**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_bindeddescriptors)  <br> |
|  std::vector&lt; [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) &gt; | [**m\_buildStates**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_buildstates)  <br>_Состояние, которое было на момент постоения сцены рендера_  |
|  uint8\_t | [**m\_currentSampleCount**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_currentsamplecount)   = `0`<br> |
|  std::atomic&lt; bool &gt; | [**m\_dirty**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_dirty)   = `false`<br> |
|  bool | [**m\_enableValidationLayers**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_enablevalidationlayers)   = `false`<br> |
|  uint64\_t | [**m\_errorsCount**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_errorscount)   = `0`<br> |
|  [**FrameBufferQueue**](classSR__GRAPH__NS_1_1FrameBufferQueue.md) | [**m\_fboQueue**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_fboqueue)  <br> |
|  uint32\_t | [**m\_frames**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_frames)   = `0`<br> |
|  uint32\_t | [**m\_framesPerSecond**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_framespersecond)   = `0`<br> |
|  bool | [**m\_isCmdState**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_iscmdstate)   = `false`<br> |
|  bool | [**m\_isComputeState**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_iscomputestate)   = `false`<br> |
|  bool | [**m\_isMultiSampleSupported**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_ismultisamplesupported)   = `false`<br> |
|  bool | [**m\_isRenderState**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_isrenderstate)   = `false`<br> |
|  bool | [**m\_isShaderChanged**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_isshaderchanged)   = `true`<br> |
|  std::optional&lt; SR\_UTILS\_NS::TimePointType &gt; | [**m\_lastSecond**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_lastsecond)  <br> |
|  std::optional&lt; uint8\_t &gt; | [**m\_newSampleCount**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_newsamplecount)  <br>_Все параметры, относящиется к мультисемплингу_  |
|  std::map&lt; OverlayType, [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Overlay**](classSR__GRAPH__NS_1_1Overlay.md) &gt; &gt; | [**m\_overlays**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_overlays)  <br> |
|  [**PipelinePreInitInfo**](structSR__GRAPH__NS_1_1PipelinePreInitInfo.md) | [**m\_preInitInfo**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_preinitinfo)  <br> |
|  [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) | [**m\_previousState**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_previousstate)  <br> |
|  RenderContextPtr | [**m\_renderContext**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_rendercontext)  <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**m\_renderStageId**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_renderstageid)  <br> |
|  uint8\_t | [**m\_requiredSampleCount**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_requiredsamplecount)   = `0`<br> |
|  [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) | [**m\_state**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_state)  <br> |
|  uint8\_t | [**m\_supportedSampleCount**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_supportedsamplecount)   = `0`<br> |
|  WindowPtr | [**m\_window**](classSR__GRAPH__NS_1_1Pipeline.md#variable-m_window)  <br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |










































































## Public Functions Documentation




### function AllocDescriptorSet 

```C++
virtual SR_NODISCARD int32_t SR_GRAPH_NS::VulkanPipeline::AllocDescriptorSet (
    const std::vector< DescriptorType > & types
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::AllocDescriptorSet*](classSR__GRAPH__NS_1_1Pipeline.md#function-allocdescriptorset)


<hr>



### function AllocateCubeMap 

```C++
virtual SR_NODISCARD int32_t SR_GRAPH_NS::VulkanPipeline::AllocateCubeMap (
    const SRCubeMapCreateInfo & createInfo
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::AllocateCubeMap*](classSR__GRAPH__NS_1_1Pipeline.md#function-allocatecubemap)


<hr>



### function AllocateFrameBuffer 

```C++
virtual SR_NODISCARD int32_t SR_GRAPH_NS::VulkanPipeline::AllocateFrameBuffer (
    const SRFrameBufferCreateInfo & createInfo
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::AllocateFrameBuffer*](classSR__GRAPH__NS_1_1Pipeline.md#function-allocateframebuffer)


<hr>



### function AllocateIBO 

```C++
virtual SR_NODISCARD int32_t SR_GRAPH_NS::VulkanPipeline::AllocateIBO (
    const void * pIndices,
    uint32_t indexSize,
    size_t count,
    int32_t VBO
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::AllocateIBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-allocateibo)


<hr>



### function AllocateSSBO 

```C++
virtual SR_NODISCARD int32_t SR_GRAPH_NS::VulkanPipeline::AllocateSSBO (
    uint32_t size,
    SSBOUsage usage
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::AllocateSSBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-allocatessbo)


<hr>



### function AllocateShaderProgram 

```C++
virtual SR_NODISCARD int32_t SR_GRAPH_NS::VulkanPipeline::AllocateShaderProgram (
    const SRShaderCreateInfo & createInfo,
    int32_t fbo
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::AllocateShaderProgram*](classSR__GRAPH__NS_1_1Pipeline.md#function-allocateshaderprogram)


<hr>



### function AllocateTexture 

```C++
virtual SR_NODISCARD int32_t SR_GRAPH_NS::VulkanPipeline::AllocateTexture (
    const SRTextureCreateInfo & createInfo
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::AllocateTexture*](classSR__GRAPH__NS_1_1Pipeline.md#function-allocatetexture)


<hr>



### function AllocateUBO 

```C++
virtual SR_NODISCARD int32_t SR_GRAPH_NS::VulkanPipeline::AllocateUBO (
    uint32_t uboSize
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::AllocateUBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-allocateubo)


<hr>



### function AllocateVBO 

_---------------------------------------_  _Работа с памятью ---------------------------------------------_ __
```C++
virtual SR_NODISCARD int32_t SR_GRAPH_NS::VulkanPipeline::AllocateVBO (
    const void * pVertices,
    Vertices::VertexType type,
    size_t count
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::AllocateVBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-allocatevbo-12)


<hr>



### function BeginCmdBuffer 

_Начало записи в буфер команд. Разделение необходимо некоторым графическим API._ 
```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::BeginCmdBuffer () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BeginCmdBuffer*](classSR__GRAPH__NS_1_1Pipeline.md#function-begincmdbuffer)


<hr>



### function BeginCompute 

_Начало вычислений в Compute Shader._ 
```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::BeginCompute () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BeginCompute*](classSR__GRAPH__NS_1_1Pipeline.md#function-begincompute)


<hr>



### function BeginRender 

_Начало рендера в кадровый буфер или в SwapChain._ 
```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::BeginRender () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BeginRender*](classSR__GRAPH__NS_1_1Pipeline.md#function-beginrender)


<hr>



### function BindAttachment 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::BindAttachment (
    uint8_t activeTexture,
    uint32_t textureId
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BindAttachment*](classSR__GRAPH__NS_1_1Pipeline.md#function-bindattachment)


<hr>



### function BindDescriptorSet 

_Привязка UBO к набору дескрипторов. Поддерживается не всеми API._ 
```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::BindDescriptorSet (
    uint32_t descriptorSet
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BindDescriptorSet*](classSR__GRAPH__NS_1_1Pipeline.md#function-binddescriptorset)


<hr>



### function BindFrameBuffer 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::BindFrameBuffer (
    FramebufferPtr pFBO
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BindFrameBuffer*](classSR__GRAPH__NS_1_1Pipeline.md#function-bindframebuffer)


<hr>



### function BindIBO 

_Index Buffer Object - биндим для рендера вершин по индексам_ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::BindIBO (
    uint32_t IBO
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BindIBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-bindibo)


<hr>



### function BindSSBO 

_Shader Storage Buffer Object - обеспечивает привязку для передачм данных в шейдеры_ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::BindSSBO (
    uint32_t SSBO
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BindSSBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-bindssbo)


<hr>



### function BindTexture 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::BindTexture (
    uint8_t activeTexture,
    uint32_t textureId
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BindTexture*](classSR__GRAPH__NS_1_1Pipeline.md#function-bindtexture)


<hr>



### function BindUBO 

[_**Uniform**_](structSR__GRAPH__NS_1_1Uniform.md) _Buffer Object - обеспечивает привязку для передачм данных в шейдеры_
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::BindUBO (
    uint32_t UBO
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BindUBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-bindubo)


<hr>



### function BindVBO 

_Vertex Buffer Object - биндими для рендера вершин_ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::BindVBO (
    uint32_t VBO
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::BindVBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-bindvbo)


<hr>



### function ClearBuffers [1/3]

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::ClearBuffers () override
```



Очистка кадрового буфера цветом. Если у буфера несколько attachment'ов, то в colorCount нужно задать их количество 


        
Implements [*SR\_GRAPH\_NS::Pipeline::ClearBuffers*](classSR__GRAPH__NS_1_1Pipeline.md#function-clearbuffers-13)


<hr>



### function ClearBuffers [2/3]

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::ClearBuffers (
    float_t r,
    float_t g,
    float_t b,
    float_t a,
    float_t depth,
    uint8_t colorCount
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::ClearBuffers*](classSR__GRAPH__NS_1_1Pipeline.md#function-clearbuffers-23)


<hr>



### function ClearBuffers [3/3]

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::ClearBuffers (
    const ClearColors & clearColors,
    std::optional< float_t > depth
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::ClearBuffers*](classSR__GRAPH__NS_1_1Pipeline.md#function-clearbuffers-33)


<hr>



### function ClearColorBuffer 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::ClearColorBuffer (
    const ClearColors & clearColors
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::ClearColorBuffer*](classSR__GRAPH__NS_1_1Pipeline.md#function-clearcolorbuffer)


<hr>



### function ClearDepthBuffer 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::ClearDepthBuffer (
    float_t depth
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::ClearDepthBuffer*](classSR__GRAPH__NS_1_1Pipeline.md#function-cleardepthbuffer)


<hr>



### function Destroy 

_Чистим все данные графического конфейера и де-инициализируем его_ 
```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::Destroy () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::Destroy*](classSR__GRAPH__NS_1_1Pipeline.md#function-destroy)


<hr>



### function Dispatch 

_-----------------------------------------_  _Вычисления -------------------------------------------------_ __
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::Dispatch (
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::Dispatch*](classSR__GRAPH__NS_1_1Pipeline.md#function-dispatch)


<hr>



### function Draw 

_Обычная отрисовка вершин_ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::Draw (
    uint32_t count
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::Draw*](classSR__GRAPH__NS_1_1Pipeline.md#function-draw)


<hr>



### function DrawFrame 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::DrawFrame () override
```



Отрисовка кадра на экран После вызова функции кадр считается законченным и [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) очищается 


        
Implements [*SR\_GRAPH\_NS::Pipeline::DrawFrame*](classSR__GRAPH__NS_1_1Pipeline.md#function-drawframe)


<hr>



### function DrawIndices 

_---------------------------------------_  _Вызовы отрисовки ---------------------------------------------_ __
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::DrawIndices (
    uint32_t count
) override
```



Отрисовка вершин по индексам 


        
Implements [*SR\_GRAPH\_NS::Pipeline::DrawIndices*](classSR__GRAPH__NS_1_1Pipeline.md#function-drawindices)


<hr>



### function EndCmdBuffer 

_Конец записи в буфер команд. Разделение необходимо некоторым графическим API._ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::EndCmdBuffer () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::EndCmdBuffer*](classSR__GRAPH__NS_1_1Pipeline.md#function-endcmdbuffer)


<hr>



### function EndCompute 

_Конец вычислений в Compute Shader._ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::EndCompute () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::EndCompute*](classSR__GRAPH__NS_1_1Pipeline.md#function-endcompute)


<hr>



### function EndRender 

_Обязательно нужно вызвать после успешного вызова BeginRender._ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::EndRender () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::EndRender*](classSR__GRAPH__NS_1_1Pipeline.md#function-endrender)


<hr>



### function FlushSSBO 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::FlushSSBO (
    uint32_t SSBO,
    uint64_t offset,
    uint64_t size
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::FlushSSBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-flushssbo)


<hr>



### function FreeCubeMap 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::FreeCubeMap (
    int32_t * id
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::FreeCubeMap*](classSR__GRAPH__NS_1_1Pipeline.md#function-freecubemap)


<hr>



### function FreeDescriptorSet 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::FreeDescriptorSet (
    int32_t * id
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::FreeDescriptorSet*](classSR__GRAPH__NS_1_1Pipeline.md#function-freedescriptorset)


<hr>



### function FreeFBO 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::FreeFBO (
    int32_t * id
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::FreeFBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-freefbo)


<hr>



### function FreeIBO 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::FreeIBO (
    int32_t * id
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::FreeIBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-freeibo)


<hr>



### function FreeSSBO 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::FreeSSBO (
    int32_t * id
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::FreeSSBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-freessbo)


<hr>



### function FreeShader 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::FreeShader (
    int32_t * id
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::FreeShader*](classSR__GRAPH__NS_1_1Pipeline.md#function-freeshader)


<hr>



### function FreeTexture 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::FreeTexture (
    int32_t * id
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::FreeTexture*](classSR__GRAPH__NS_1_1Pipeline.md#function-freetexture)


<hr>



### function FreeUBO 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::FreeUBO (
    int32_t * id
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::FreeUBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-freeubo)


<hr>



### function FreeVBO 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::FreeVBO (
    int32_t * id
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::FreeVBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-freevbo)


<hr>



### function GetBuildIterationsCount 

```C++
virtual SR_NODISCARD uint8_t SR_GRAPH_NS::VulkanPipeline::GetBuildIterationsCount () noexcept override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetBuildIterationsCount*](classSR__GRAPH__NS_1_1Pipeline.md#function-getbuilditerationscount)


<hr>



### function GetCurrentFBOHandle 

```C++
virtual SR_NODISCARD void * SR_GRAPH_NS::VulkanPipeline::GetCurrentFBOHandle () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetCurrentFBOHandle*](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentfbohandle)


<hr>



### function GetCurrentFrameIndex 

```C++
virtual SR_NODISCARD uint8_t SR_GRAPH_NS::VulkanPipeline::GetCurrentFrameIndex () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetCurrentFrameIndex*](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentframeindex)


<hr>



### function GetCurrentShaderHandle 

```C++
virtual SR_NODISCARD void * SR_GRAPH_NS::VulkanPipeline::GetCurrentShaderHandle () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetCurrentShaderHandle*](classSR__GRAPH__NS_1_1Pipeline.md#function-getcurrentshaderhandle)


<hr>



### function GetFBOHandles 

```C++
virtual SR_NODISCARD std::set< void * > SR_GRAPH_NS::VulkanPipeline::GetFBOHandles () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetFBOHandles*](classSR__GRAPH__NS_1_1Pipeline.md#function-getfbohandles)


<hr>



### function GetFrameBufferSampleCount 

```C++
virtual SR_NODISCARD uint8_t SR_GRAPH_NS::VulkanPipeline::GetFrameBufferSampleCount () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetFrameBufferSampleCount*](classSR__GRAPH__NS_1_1Pipeline.md#function-getframebuffersamplecount)


<hr>



### function GetKernel 

```C++
inline SR_NODISCARD EvoVulkan::Core::VulkanKernel * SR_GRAPH_NS::VulkanPipeline::GetKernel () noexcept const
```




<hr>



### function GetMemoryManager 

```C++
inline SR_NODISCARD VulkanTools::MemoryManager * SR_GRAPH_NS::VulkanPipeline::GetMemoryManager () noexcept const
```




<hr>



### function GetPixelColor 

```C++
virtual SR_NODISCARD SR_MATH_NS::FColor SR_GRAPH_NS::VulkanPipeline::GetPixelColor (
    uint32_t textureId,
    uint32_t x,
    uint32_t y
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetPixelColor*](classSR__GRAPH__NS_1_1Pipeline.md#function-getpixelcolor)


<hr>



### function GetRenderer 

```C++
inline virtual SR_NODISCARD std::string SR_GRAPH_NS::VulkanPipeline::GetRenderer () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetRenderer*](classSR__GRAPH__NS_1_1Pipeline.md#function-getrenderer)


<hr>



### function GetShaderHandles 

```C++
virtual SR_NODISCARD std::set< void * > SR_GRAPH_NS::VulkanPipeline::GetShaderHandles () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetShaderHandles*](classSR__GRAPH__NS_1_1Pipeline.md#function-getshaderhandles)


<hr>



### function GetSwapchainImagesCount 

```C++
virtual SR_NODISCARD uint16_t SR_GRAPH_NS::VulkanPipeline::GetSwapchainImagesCount () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetSwapchainImagesCount*](classSR__GRAPH__NS_1_1Pipeline.md#function-getswapchainimagescount)


<hr>



### function GetType 

```C++
inline virtual SR_NODISCARD PipelineType SR_GRAPH_NS::VulkanPipeline::GetType () noexcept override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetType*](classSR__GRAPH__NS_1_1Pipeline.md#function-gettype)


<hr>



### function GetUsedMemory 

```C++
virtual SR_NODISCARD uint64_t SR_GRAPH_NS::VulkanPipeline::GetUsedMemory () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetUsedMemory*](classSR__GRAPH__NS_1_1Pipeline.md#function-getusedmemory)


<hr>



### function GetVendor 

_------------------------------------_  _Вспомогательные методы ------------------------------------------_ __
```C++
virtual SR_NODISCARD std::string SR_GRAPH_NS::VulkanPipeline::GetVendor () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetVendor*](classSR__GRAPH__NS_1_1Pipeline.md#function-getvendor)


<hr>



### function GetVersion 

```C++
inline virtual SR_NODISCARD std::string SR_GRAPH_NS::VulkanPipeline::GetVersion () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::GetVersion*](classSR__GRAPH__NS_1_1Pipeline.md#function-getversion)


<hr>



### function Init 

_Подключаем окно и настраиваем взаимодействие рендера с ним_ 
```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::Init () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::Init*](classSR__GRAPH__NS_1_1Pipeline.md#function-init)


<hr>



### function InitOverlay 

_---------------------------------------_  _Работа с_[_**Overlay**_](classSR__GRAPH__NS_1_1Overlay.md) _---------------------------------------------_ __
```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::InitOverlay () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::InitOverlay*](classSR__GRAPH__NS_1_1Pipeline.md#function-initoverlay)


<hr>



### function IsSamplerValid 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::IsSamplerValid (
    int32_t id
) override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::IsSamplerValid*](classSR__GRAPH__NS_1_1Pipeline.md#function-issamplervalid)


<hr>



### function IsShaderConstantSupport 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::VulkanPipeline::IsShaderConstantSupport () noexcept override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::IsShaderConstantSupport*](classSR__GRAPH__NS_1_1Pipeline.md#function-isshaderconstantsupport)


<hr>



### function IsVSyncEnabled 

```C++
virtual SR_NODISCARD bool SR_GRAPH_NS::VulkanPipeline::IsVSyncEnabled () override const
```



Implements [*SR\_GRAPH\_NS::Pipeline::IsVSyncEnabled*](classSR__GRAPH__NS_1_1Pipeline.md#function-isvsyncenabled)


<hr>



### function MapSSBO 

```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::MapSSBO (
    uint32_t SSBO,
    void ** ppData
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::MapSSBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-mapssbo)


<hr>



### function OnMultiSampleChanged 

_-------------------------------------_  _Мультисемплинг и VSync -----------------------------------------_ __
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::OnMultiSampleChanged () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::OnMultiSampleChanged*](classSR__GRAPH__NS_1_1Pipeline.md#function-onmultisamplechanged)


<hr>



### function OnResize 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::OnResize (
    const SR_MATH_NS::UVector2 & size
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::OnResize*](classSR__GRAPH__NS_1_1Pipeline.md#function-onresize)


<hr>



### function PostInit 

_Профайлинг и прочие пост-штучки_ 
```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::PostInit () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::PostInit*](classSR__GRAPH__NS_1_1Pipeline.md#function-postinit)


<hr>



### function PreInit 

_-------------------------------------_  _Инициализация рендера ------------------------------------------_ __
```C++
virtual bool SR_GRAPH_NS::VulkanPipeline::PreInit (
    const PipelinePreInitInfo & info
) override
```



Предназначено для инициализации всех структур и классов 


        
Implements [*SR\_GRAPH\_NS::Pipeline::PreInit*](classSR__GRAPH__NS_1_1Pipeline.md#function-preinit)


<hr>



### function PrepareFrame 

_------------------------------------_  _Главные методы рендера ------------------------------------------_ __
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::PrepareFrame () override
```



Вызывается перед началом рендера, подготовка к рендеру 


        
Implements [*SR\_GRAPH\_NS::Pipeline::PrepareFrame*](classSR__GRAPH__NS_1_1Pipeline.md#function-prepareframe)


<hr>



### function PushConstants 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::PushConstants (
    void * pData,
    uint64_t size
) override
```



Передает данные в шейдер, которые не будут обновляться до следующего перерисовывания сцены. Поддерживается не всеми API 


        
Implements [*SR\_GRAPH\_NS::Pipeline::PushConstants*](classSR__GRAPH__NS_1_1Pipeline.md#function-pushconstants)


<hr>



### function ReadSSBO 

_Читает данные из SSBO в память_ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::ReadSSBO (
    uint32_t SSBO,
    void * pData,
    uint64_t size
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::ReadSSBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-readssbo)


<hr>



### function ResetLastShader 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::ResetLastShader () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::ResetLastShader*](classSR__GRAPH__NS_1_1Pipeline.md#function-resetlastshader)


<hr>



### function ResetSubmitQueue 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::ResetSubmitQueue () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::ResetSubmitQueue*](classSR__GRAPH__NS_1_1Pipeline.md#function-resetsubmitqueue)


<hr>



### function SetCurrentFrameBuffer 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::SetCurrentFrameBuffer (
    FramebufferPtr pFrameBuffer
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::SetCurrentFrameBuffer*](classSR__GRAPH__NS_1_1Pipeline.md#function-setcurrentframebuffer)


<hr>



### function SetDirty 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::SetDirty (
    bool dirty
) override
```



Устанавливает состояние графического конвейера. Если грязный, то будет перестроена сцена Если чистый, то считаем, что постороение сцены завершено 


        
Implements [*SR\_GRAPH\_NS::Pipeline::SetDirty*](classSR__GRAPH__NS_1_1Pipeline.md#function-setdirty)


<hr>



### function SetOverlayEnabled 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::SetOverlayEnabled (
    OverlayType overlayType,
    bool enabled
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::SetOverlayEnabled*](classSR__GRAPH__NS_1_1Pipeline.md#function-setoverlayenabled)


<hr>



### function SetScissor 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::SetScissor (
    int32_t width,
    int32_t height
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::SetScissor*](classSR__GRAPH__NS_1_1Pipeline.md#function-setscissor)


<hr>



### function SetSwapchainImagesCount 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::SetSwapchainImagesCount (
    uint16_t count
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::SetSwapchainImagesCount*](classSR__GRAPH__NS_1_1Pipeline.md#function-setswapchainimagescount)


<hr>



### function SetVSyncEnabled 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::SetVSyncEnabled (
    bool enabled
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::SetVSyncEnabled*](classSR__GRAPH__NS_1_1Pipeline.md#function-setvsyncenabled)


<hr>



### function SetViewport 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::SetViewport (
    int32_t width,
    int32_t height
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::SetViewport*](classSR__GRAPH__NS_1_1Pipeline.md#function-setviewport)


<hr>



### function UnMapSSBO 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::UnMapSSBO (
    uint32_t SSBO
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::UnMapSSBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-unmapssbo)


<hr>



### function UnUseShader 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::UnUseShader () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::UnUseShader*](classSR__GRAPH__NS_1_1Pipeline.md#function-unuseshader)


<hr>



### function UpdateDescriptorSets 

_Привязываем к дескриптору юниформы. Работает не во всех API._ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::UpdateDescriptorSets (
    uint32_t descriptorSet,
    const SRDescriptorUpdateInfos & updateInfo
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::UpdateDescriptorSets*](classSR__GRAPH__NS_1_1Pipeline.md#function-updatedescriptorsets)


<hr>



### function UpdateSSBO 

_Обеспечивает обновление данных в шейдере_ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::UpdateSSBO (
    uint32_t SSBO,
    void * pData,
    uint64_t size
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::UpdateSSBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-updatessbo)


<hr>



### function UpdateUBO 

_Обеспечивает обновление данных в шейдере_ 
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::UpdateUBO (
    uint32_t UBO,
    void * pData,
    uint64_t size
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::UpdateUBO*](classSR__GRAPH__NS_1_1Pipeline.md#function-updateubo)


<hr>



### function UseShader 

_------------------------------------------_  _Биндинги --------------------------------------------------_ __
```C++
virtual void SR_GRAPH_NS::VulkanPipeline::UseShader (
    uint32_t shaderProgram
) override
```



Implements [*SR\_GRAPH\_NS::Pipeline::UseShader*](classSR__GRAPH__NS_1_1Pipeline.md#function-useshader)


<hr>



### function VulkanPipeline 

```C++
inline explicit SR_GRAPH_NS::VulkanPipeline::VulkanPipeline (
    const RenderContextPtr & pContext
) 
```




<hr>



### function WaitComputeIdle 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::WaitComputeIdle () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::WaitComputeIdle*](classSR__GRAPH__NS_1_1Pipeline.md#function-waitcomputeidle)


<hr>



### function WaitRenderIdle 

```C++
virtual void SR_GRAPH_NS::VulkanPipeline::WaitRenderIdle () override
```



Implements [*SR\_GRAPH\_NS::Pipeline::WaitRenderIdle*](classSR__GRAPH__NS_1_1Pipeline.md#function-waitrenderidle)


<hr>



### function ~VulkanPipeline 

```C++
SR_GRAPH_NS::VulkanPipeline::~VulkanPipeline () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/Vulkan/VulkanPipeline.h`

