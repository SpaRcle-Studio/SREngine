

# Class SR\_GRAPH\_NS::Pipeline



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md)








Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)


Inherited by the following classes: [SR\_GRAPH\_NS::VulkanPipeline](classSR__GRAPH__NS_1_1VulkanPipeline.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) &gt; | [**ClearColors**](#typedef-clearcolors)  <br> |
| typedef [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* | [**FramebufferPtr**](#typedef-framebufferptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; [**SR\_GRAPH\_NS::RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) &gt; | [**RenderContextPtr**](#typedef-rendercontextptr)  <br> |
| typedef int32\_t | [**ShaderProgram**](#typedef-shaderprogram)  <br> |
| typedef [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**ShaderPtr**](#typedef-shaderptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**Super**](#typedef-super)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Window**](classSR__GRAPH__NS_1_1Window.md) &gt; | [**WindowPtr**](#typedef-windowptr)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD int32\_t | [**AllocDescriptorSet**](#function-allocdescriptorset) (const std::vector&lt; DescriptorType &gt; & types) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateCubeMap**](#function-allocatecubemap) (const [**SRCubeMapCreateInfo**](structSR__GRAPH__NS_1_1SRCubeMapCreateInfo.md) & createInfo) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateFrameBuffer**](#function-allocateframebuffer) (const [**SRFrameBufferCreateInfo**](structSR__GRAPH__NS_1_1SRFrameBufferCreateInfo.md) & createInfo) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateIBO**](#function-allocateibo) (const void \* pIndices, uint32\_t indexSize, size\_t count, int32\_t VBO) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateSSBO**](#function-allocatessbo) (uint32\_t ssboSize, SSBOUsage usage) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateShaderProgram**](#function-allocateshaderprogram) (const [**SRShaderCreateInfo**](structSR__GRAPH__NS_1_1SRShaderCreateInfo.md) & createInfo, int32\_t fbo) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateTexture**](#function-allocatetexture) (const [**SRTextureCreateInfo**](structSR__GRAPH__NS_1_1SRTextureCreateInfo.md) & createInfo) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateUBO**](#function-allocateubo) (uint32\_t uboSize) <br> |
| virtual SR\_NODISCARD int32\_t | [**AllocateVBO**](#function-allocatevbo-12) (const void \* pVertices, Vertices::VertexType type, size\_t count) <br>_---------------------------------------_  _Работа с памятью ---------------------------------------------_ __ |
| virtual SR\_NODISCARD int32\_t | [**AllocateVBO**](#function-allocatevbo-22) (const [**SR\_UTILS\_NS::Vertex**](structSR__UTILS__NS_1_1Vertex.md) \* pVertices, Vertices::VertexType type, size\_t count) <br>_Продвинутая версия AllocateVBO, может сама выполнить преобразование типа памяти базовых вершин к нужному выравниванию._  |
| virtual bool | [**BeginCmdBuffer**](#function-begincmdbuffer) () <br>_Начало записи в буфер команд. Разделение необходимо некоторым графическим API._  |
| virtual bool | [**BeginCompute**](#function-begincompute) () <br>_Начало вычислений в Compute Shader._  |
| virtual bool | [**BeginDrawOverlay**](#function-begindrawoverlay) (OverlayType overlayType) <br> |
| virtual bool | [**BeginRender**](#function-beginrender) () <br>_Начало рендера в кадровый буфер или в SwapChain._  |
| virtual void | [**BindAttachment**](#function-bindattachment) (uint8\_t activeTexture, uint32\_t textureId) <br> |
| virtual bool | [**BindDescriptorSet**](#function-binddescriptorset) (uint32\_t descriptorSet) <br>_Привязка UBO к набору дескрипторов. Поддерживается не всеми API._  |
| virtual void | [**BindFrameBuffer**](#function-bindframebuffer) (FramebufferPtr pFBO) <br> |
| virtual void | [**BindIBO**](#function-bindibo) (uint32\_t IBO) <br>_Index Buffer Object - биндим для рендера вершин по индексам_  |
| virtual void | [**BindSSBO**](#function-bindssbo) (uint32\_t SSBO) <br>_Shader Storage Buffer Object - обеспечивает привязку для передачм данных в шейдеры_  |
| virtual void | [**BindTexture**](#function-bindtexture) (uint8\_t activeTexture, uint32\_t textureId) <br> |
| virtual void | [**BindUBO**](#function-bindubo) (uint32\_t UBO) <br>[_**Uniform**_](structSR__GRAPH__NS_1_1Uniform.md) _Buffer Object - обеспечивает привязку для передачм данных в шейдеры_ |
| virtual void | [**BindVBO**](#function-bindvbo) (uint32\_t VBO) <br>_Vertex Buffer Object - биндими для рендера вершин_  |
| virtual void | [**ClearBuffers**](#function-clearbuffers-13) () <br> |
| virtual void | [**ClearBuffers**](#function-clearbuffers-23) (float\_t r, float\_t g, float\_t b, float\_t a, float\_t depth, uint8\_t colorCount) <br> |
| virtual void | [**ClearBuffers**](#function-clearbuffers-33) (const ClearColors & clearColors, std::optional&lt; float\_t &gt; depth) <br> |
| virtual void | [**ClearColorBuffer**](#function-clearcolorbuffer) (const ClearColors & clearColors) <br> |
| virtual void | [**ClearDepthBuffer**](#function-cleardepthbuffer) (float\_t depth) <br> |
| virtual void | [**ClearFrameBuffersQueue**](#function-clearframebuffersqueue) () <br>_Вызывается в начале построения сцены рендера, чистит очередь рендера._  |
| virtual bool | [**Destroy**](#function-destroy) () <br>_Чистим все данные графического конфейера и де-инициализируем его_  |
| virtual void | [**DestroyOverlay**](#function-destroyoverlay) () <br> |
| virtual void | [**Dispatch**](#function-dispatch) (uint32\_t groupCountX, uint32\_t groupCountY, uint32\_t groupCountZ) <br>_-----------------------------------------_  _Вычисления -------------------------------------------------_ __ |
| virtual void | [**Draw**](#function-draw) (uint32\_t count) <br>_Обычная отрисовка вершин_  |
| virtual void | [**DrawFrame**](#function-drawframe) () <br> |
| virtual void | [**DrawIndices**](#function-drawindices) (uint32\_t count) <br>_---------------------------------------_  _Вызовы отрисовки ---------------------------------------------_ __ |
| virtual void | [**EndCmdBuffer**](#function-endcmdbuffer) () <br>_Конец записи в буфер команд. Разделение необходимо некоторым графическим API._  |
| virtual void | [**EndCompute**](#function-endcompute) () <br>_Конец вычислений в Compute Shader._  |
| virtual void | [**EndDrawOverlay**](#function-enddrawoverlay) (OverlayType overlayType) <br> |
| virtual void | [**EndRender**](#function-endrender) () <br>_Обязательно нужно вызвать после успешного вызова BeginRender._  |
| virtual bool | [**FreeCubeMap**](#function-freecubemap) (int32\_t \* id) <br> |
| virtual bool | [**FreeDescriptorSet**](#function-freedescriptorset) (int32\_t \* id) <br> |
| virtual bool | [**FreeFBO**](#function-freefbo) (int32\_t \* id) <br> |
| virtual bool | [**FreeIBO**](#function-freeibo) (int32\_t \* id) <br> |
| virtual bool | [**FreeSSBO**](#function-freessbo) (int32\_t \* id) <br> |
| virtual bool | [**FreeShader**](#function-freeshader) (int32\_t \* id) <br> |
| virtual bool | [**FreeTexture**](#function-freetexture) (int32\_t \* id) <br> |
| virtual bool | [**FreeUBO**](#function-freeubo) (int32\_t \* id) <br> |
| virtual bool | [**FreeVBO**](#function-freevbo) (int32\_t \* id) <br> |
| virtual SR\_NODISCARD uint8\_t | [**GetBuildIterationsCount**](#function-getbuilditerationscount) () noexcept const<br> |
|  SR\_NODISCARD const [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) & | [**GetBuildState**](#function-getbuildstate) () const<br> |
|  SR\_NODISCARD uint8\_t | [**GetCurrentBuildIteration**](#function-getcurrentbuilditeration) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetCurrentDescriptorSet**](#function-getcurrentdescriptorset) () noexcept const<br> |
| virtual SR\_NODISCARD void \* | [**GetCurrentFBOHandle**](#function-getcurrentfbohandle) () const<br> |
|  SR\_NODISCARD FramebufferPtr | [**GetCurrentFrameBuffer**](#function-getcurrentframebuffer) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetCurrentFrameBufferId**](#function-getcurrentframebufferid) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetCurrentFrameBufferLayer**](#function-getcurrentframebufferlayer) () noexcept const<br> |
|  SR\_NODISCARD [**RenderStrategy**](classSR__GRAPH__NS_1_1RenderStrategy.md) \* | [**GetCurrentRenderStrategy**](#function-getcurrentrenderstrategy) () noexcept const<br> |
|  SR\_NODISCARD ShaderPtr | [**GetCurrentShader**](#function-getcurrentshader) () const<br> |
| virtual SR\_NODISCARD void \* | [**GetCurrentShaderHandle**](#function-getcurrentshaderhandle) () const<br> |
|  SR\_NODISCARD int32\_t | [**GetCurrentShaderId**](#function-getcurrentshaderid) () const<br> |
|  SR\_NODISCARD int32\_t | [**GetCurrentUBO**](#function-getcurrentubo) () const<br> |
| virtual SR\_NODISCARD std::set&lt; void \* &gt; | [**GetFBOHandles**](#function-getfbohandles) () const<br> |
| virtual SR\_NODISCARD uint8\_t | [**GetFrameBufferSampleCount**](#function-getframebuffersamplecount) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetFramesPerSecond**](#function-getframespersecond) () noexcept const<br> |
| virtual const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Overlay**](classSR__GRAPH__NS_1_1Overlay.md) &gt; & | [**GetOverlay**](#function-getoverlay) (OverlayType overlayType) const<br> |
| virtual void \* | [**GetOverlayTextureDescriptorSet**](#function-getoverlaytexturedescriptorset) (uint32\_t textureId, OverlayType overlayType) const<br> |
| virtual SR\_NODISCARD [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**GetPixelColor**](#function-getpixelcolor) (uint32\_t textureId, uint32\_t x, uint32\_t y) <br> |
|  SR\_NODISCARD const [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) & | [**GetPreviousState**](#function-getpreviousstate) () const<br> |
|  SR\_NODISCARD [**FrameBufferQueue**](classSR__GRAPH__NS_1_1FrameBufferQueue.md) & | [**GetQueue**](#function-getqueue) () noexcept<br> |
|  SR\_NODISCARD RenderContextPtr | [**GetRenderContext**](#function-getrendercontext) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetRenderStageId**](#function-getrenderstageid) () const<br> |
| virtual SR\_NODISCARD std::string | [**GetRenderer**](#function-getrenderer) () const<br> |
|  SR\_NODISCARD uint8\_t | [**GetSamplesCount**](#function-getsamplescount) () const<br> |
| virtual SR\_NODISCARD std::set&lt; void \* &gt; | [**GetShaderHandles**](#function-getshaderhandles) () const<br> |
|  SR\_NODISCARD const [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) & | [**GetState**](#function-getstate) () const<br> |
| virtual SR\_NODISCARD uint8\_t | [**GetSupportedSamples**](#function-getsupportedsamples) () noexcept const<br> |
| virtual SR\_NODISCARD PipelineType | [**GetType**](#function-gettype) () noexcept const = 0<br> |
| virtual uint64\_t | [**GetUsedMemory**](#function-getusedmemory) () const<br> |
| virtual SR\_NODISCARD std::string | [**GetVendor**](#function-getvendor) () const<br>_------------------------------------_  _Вспомогательные методы ------------------------------------------_ __ |
| virtual SR\_NODISCARD std::string | [**GetVersion**](#function-getversion) () const<br> |
|  SR\_NODISCARD WindowPtr | [**GetWindow**](#function-getwindow) () const<br> |
| virtual bool | [**Init**](#function-init) () <br>_Подключаем окно и настраиваем взаимодействие рендера с ним_  |
| virtual bool | [**InitOverlay**](#function-initoverlay) () <br>_---------------------------------------_  _Работа с_[_**Overlay**_](classSR__GRAPH__NS_1_1Overlay.md) _---------------------------------------------_ __ |
|  SR\_NODISCARD bool | [**IsDirty**](#function-isdirty) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsFBOQueueValid**](#function-isfboqueuevalid) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsMultiSamplingSupported**](#function-ismultisamplingsupported) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsRenderState**](#function-isrenderstate) () noexcept const<br> |
| virtual bool | [**IsSamplerValid**](#function-issamplervalid) (int32\_t id) const<br> |
|  SR\_NODISCARD bool | [**IsShaderChanged**](#function-isshaderchanged) () noexcept const<br>_Изменился ли текущий шейдер после UseShader. Даже если был вызван UnUseShader. Низкоуровневая проверка._  |
| virtual SR\_NODISCARD bool | [**IsShaderConstantSupport**](#function-isshaderconstantsupport) () const<br> |
| virtual SR\_NODISCARD bool | [**IsVSyncEnabled**](#function-isvsyncenabled) () const<br> |
| virtual bool | [**MapSSBO**](#function-mapssbo) (uint32\_t SSBO, void \*\* ppData) <br> |
| virtual void | [**OnMultiSampleChanged**](#function-onmultisamplechanged) () <br>_-------------------------------------_  _Мультисемплинг и VSync -----------------------------------------_ __ |
| virtual void | [**OnResize**](#function-onresize) (const SR\_MATH\_NS::UVector2 & size) <br> |
|   | [**Pipeline**](#function-pipeline) (const RenderContextPtr & pContext) <br> |
| virtual void | [**PipelineError**](#function-pipelineerror) (const std::string & msg) const<br> |
| virtual bool | [**PostInit**](#function-postinit) () <br>_Профайлинг и прочие пост-штучки_  |
| virtual bool | [**PreInit**](#function-preinit) (const [**PipelinePreInitInfo**](structSR__GRAPH__NS_1_1PipelinePreInitInfo.md) & info) <br>_-------------------------------------_  _Инициализация рендера ------------------------------------------_ __ |
| virtual void | [**PrepareFrame**](#function-prepareframe) () <br>_------------------------------------_  _Главные методы рендера ------------------------------------------_ __ |
| virtual void | [**PrepareOverlay**](#function-prepareoverlay) (OverlayType overlayType) <br> |
| virtual void | [**PushConstants**](#function-pushconstants) (void \* pData, uint64\_t size) <br> |
| virtual void | [**ReCreateOverlay**](#function-recreateoverlay) () <br> |
| virtual void | [**ReadSSBO**](#function-readssbo) (uint32\_t SSBO, void \* pData, uint64\_t size) <br>_Читает данные из SSBO в память_  |
| virtual void | [**ResetLastShader**](#function-resetlastshader) () <br> |
| virtual void | [**ResetSubmitQueue**](#function-resetsubmitqueue) () <br> |
| virtual void | [**SetBuildIteration**](#function-setbuilditeration) (uint8\_t iteration) <br> |
| virtual void | [**SetCurrentFrameBuffer**](#function-setcurrentframebuffer) (FramebufferPtr pFrameBuffer) <br> |
| virtual void | [**SetCurrentFrameBufferLayer**](#function-setcurrentframebufferlayer) (uint32\_t layer) <br> |
| virtual void | [**SetCurrentRenderStrategy**](#function-setcurrentrenderstrategy) ([**RenderStrategy**](classSR__GRAPH__NS_1_1RenderStrategy.md) \* pStrategy) <br> |
| virtual void | [**SetCurrentShader**](#function-setcurrentshader) (ShaderPtr pShader) <br> |
| virtual void | [**SetCurrentShaderId**](#function-setcurrentshaderid) (int32\_t id) <br> |
| virtual void | [**SetDirty**](#function-setdirty) (bool dirty) <br> |
| virtual void | [**SetOverlayEnabled**](#function-setoverlayenabled) (OverlayType overlayType, bool enabled) <br> |
| virtual void | [**SetOverlaySurfaceDirty**](#function-setoverlaysurfacedirty) () <br> |
| virtual void | [**SetSampleCount**](#function-setsamplecount) (uint8\_t count) <br> |
| virtual void | [**SetScissor**](#function-setscissor) (int32\_t width=-1, int32\_t height=-1) <br> |
| virtual void | [**SetVSyncEnabled**](#function-setvsyncenabled) (bool enabled) <br> |
| virtual void | [**SetViewport**](#function-setviewport) (int32\_t width=-1, int32\_t height=-1) <br> |
| virtual void | [**SwitchWindow**](#function-switchwindow) (const WindowPtr & pWindow) <br> |
| virtual void | [**UnMapSSBO**](#function-unmapssbo) (uint32\_t SSBO) <br> |
| virtual void | [**UnUseShader**](#function-unuseshader) () <br> |
| virtual void | [**UpdateDescriptorSets**](#function-updatedescriptorsets) (uint32\_t descriptorSet, const SRDescriptorUpdateInfos & updateInfo) <br>_Привязываем к дескриптору юниформы. Работает не во всех API._  |
| virtual void | [**UpdateMultiSampling**](#function-updatemultisampling) () <br> |
| virtual void | [**UpdateSSBO**](#function-updatessbo) (uint32\_t SSBO, void \* pData, uint64\_t size) <br>_Обеспечивает обновление данных в шейдере_  |
| virtual void | [**UpdateUBO**](#function-updateubo) (uint32\_t UBO, void \* pData, uint64\_t size) <br>_Обеспечивает обновление данных в шейдере_  |
| virtual void | [**UseShader**](#function-useshader) (uint32\_t shaderProgram) <br>_------------------------------------------_  _Биндинги --------------------------------------------------_ __ |
| virtual void | [**WaitComputeIdle**](#function-waitcomputeidle) () <br> |
| virtual  | [**~Pipeline**](#function-pipeline) () <br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
|  SR\_NODISCARD const void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-12) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br>_NOLINT(modernize-use-nodiscard)_  |
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
|  bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_2) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_3) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_4) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_5) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_6) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
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
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |




## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |
















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**SR\_HTYPES\_NS::PoolSet**](classSR__HTYPES__NS_1_1PoolSet.md)&lt; bool &gt; | [**m\_bindedDescriptors**](#variable-m_bindeddescriptors)  <br> |
|  [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) | [**m\_buildState**](#variable-m_buildstate)  <br>_Состояние, которое было на момент постоения сцены рендера_  |
|  uint8\_t | [**m\_currentSampleCount**](#variable-m_currentsamplecount)   = `0`<br> |
|  std::atomic&lt; bool &gt; | [**m\_dirty**](#variable-m_dirty)   = `false`<br> |
|  bool | [**m\_enableValidationLayers**](#variable-m_enablevalidationlayers)   = `false`<br> |
|  uint64\_t | [**m\_errorsCount**](#variable-m_errorscount)   = `0`<br> |
|  [**FrameBufferQueue**](classSR__GRAPH__NS_1_1FrameBufferQueue.md) | [**m\_fboQueue**](#variable-m_fboqueue)  <br> |
|  uint32\_t | [**m\_frames**](#variable-m_frames)   = `0`<br> |
|  uint32\_t | [**m\_framesPerSecond**](#variable-m_framespersecond)   = `0`<br> |
|  bool | [**m\_isCmdState**](#variable-m_iscmdstate)   = `false`<br> |
|  bool | [**m\_isComputeState**](#variable-m_iscomputestate)   = `false`<br> |
|  bool | [**m\_isMultiSampleSupported**](#variable-m_ismultisamplesupported)   = `false`<br> |
|  bool | [**m\_isRenderState**](#variable-m_isrenderstate)   = `false`<br> |
|  bool | [**m\_isShaderChanged**](#variable-m_isshaderchanged)   = `true`<br> |
|  std::optional&lt; SR\_UTILS\_NS::TimePointType &gt; | [**m\_lastSecond**](#variable-m_lastsecond)  <br> |
|  std::optional&lt; uint8\_t &gt; | [**m\_newSampleCount**](#variable-m_newsamplecount)  <br>_Все параметры, относящиется к мультисемплингу_  |
|  std::map&lt; OverlayType, [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Overlay**](classSR__GRAPH__NS_1_1Overlay.md) &gt; &gt; | [**m\_overlays**](#variable-m_overlays)  <br> |
|  [**PipelinePreInitInfo**](structSR__GRAPH__NS_1_1PipelinePreInitInfo.md) | [**m\_preInitInfo**](#variable-m_preinitinfo)  <br> |
|  [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) | [**m\_previousState**](#variable-m_previousstate)  <br> |
|  RenderContextPtr | [**m\_renderContext**](#variable-m_rendercontext)  <br> |
|  uint8\_t | [**m\_requiredSampleCount**](#variable-m_requiredsamplecount)   = `0`<br> |
|  [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) | [**m\_state**](#variable-m_state)  <br> |
|  uint8\_t | [**m\_supportedSampleCount**](#variable-m_supportedsamplecount)   = `0`<br> |
|  WindowPtr | [**m\_window**](#variable-m_window)  <br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |
























































## Public Types Documentation




### typedef ClearColors 

```C++
using SR_GRAPH_NS::Pipeline::ClearColors =  std::vector<SR_MATH_NS::FColor>;
```




<hr>



### typedef FramebufferPtr 

```C++
using SR_GRAPH_NS::Pipeline::FramebufferPtr =  SR_GTYPES_NS::Framebuffer*;
```




<hr>



### typedef Ptr 

```C++
using SR_GRAPH_NS::Pipeline::Ptr =  SR_HTYPES_NS::SharedPtr<Pipeline>;
```




<hr>



### typedef RenderContextPtr 

```C++
using SR_GRAPH_NS::Pipeline::RenderContextPtr =  SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
```




<hr>



### typedef ShaderProgram 

```C++
using SR_GRAPH_NS::Pipeline::ShaderProgram =  int32_t;
```




<hr>



### typedef ShaderPtr 

```C++
using SR_GRAPH_NS::Pipeline::ShaderPtr =  SR_GTYPES_NS::Shader*;
```




<hr>



### typedef Super 

```C++
using SR_GRAPH_NS::Pipeline::Super =  SR_HTYPES_NS::SharedPtr<Pipeline>;
```




<hr>



### typedef WindowPtr 

```C++
using SR_GRAPH_NS::Pipeline::WindowPtr =  SR_HTYPES_NS::SharedPtr<Window>;
```




<hr>
## Public Functions Documentation




### function AllocDescriptorSet 

```C++
inline virtual SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::AllocDescriptorSet (
    const std::vector< DescriptorType > & types
) 
```




<hr>



### function AllocateCubeMap 

```C++
inline virtual SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::AllocateCubeMap (
    const SRCubeMapCreateInfo & createInfo
) 
```




<hr>



### function AllocateFrameBuffer 

```C++
inline virtual SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::AllocateFrameBuffer (
    const SRFrameBufferCreateInfo & createInfo
) 
```




<hr>



### function AllocateIBO 

```C++
inline virtual SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::AllocateIBO (
    const void * pIndices,
    uint32_t indexSize,
    size_t count,
    int32_t VBO
) 
```




<hr>



### function AllocateSSBO 

```C++
inline virtual SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::AllocateSSBO (
    uint32_t ssboSize,
    SSBOUsage usage
) 
```




<hr>



### function AllocateShaderProgram 

```C++
inline virtual SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::AllocateShaderProgram (
    const SRShaderCreateInfo & createInfo,
    int32_t fbo
) 
```




<hr>



### function AllocateTexture 

```C++
inline virtual SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::AllocateTexture (
    const SRTextureCreateInfo & createInfo
) 
```




<hr>



### function AllocateUBO 

```C++
inline virtual SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::AllocateUBO (
    uint32_t uboSize
) 
```




<hr>



### function AllocateVBO [1/2]

_---------------------------------------_  _Работа с памятью ---------------------------------------------_ __
```C++
inline virtual SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::AllocateVBO (
    const void * pVertices,
    Vertices::VertexType type,
    size_t count
) 
```




<hr>



### function AllocateVBO [2/2]

_Продвинутая версия AllocateVBO, может сама выполнить преобразование типа памяти базовых вершин к нужному выравниванию._ 
```C++
virtual SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::AllocateVBO (
    const SR_UTILS_NS::Vertex * pVertices,
    Vertices::VertexType type,
    size_t count
) 
```




<hr>



### function BeginCmdBuffer 

_Начало записи в буфер команд. Разделение необходимо некоторым графическим API._ 
```C++
virtual bool SR_GRAPH_NS::Pipeline::BeginCmdBuffer () 
```




<hr>



### function BeginCompute 

_Начало вычислений в Compute Shader._ 
```C++
virtual bool SR_GRAPH_NS::Pipeline::BeginCompute () 
```




<hr>



### function BeginDrawOverlay 

```C++
virtual bool SR_GRAPH_NS::Pipeline::BeginDrawOverlay (
    OverlayType overlayType
) 
```




<hr>



### function BeginRender 

_Начало рендера в кадровый буфер или в SwapChain._ 
```C++
virtual bool SR_GRAPH_NS::Pipeline::BeginRender () 
```




<hr>



### function BindAttachment 

```C++
virtual void SR_GRAPH_NS::Pipeline::BindAttachment (
    uint8_t activeTexture,
    uint32_t textureId
) 
```




<hr>



### function BindDescriptorSet 

_Привязка UBO к набору дескрипторов. Поддерживается не всеми API._ 
```C++
virtual bool SR_GRAPH_NS::Pipeline::BindDescriptorSet (
    uint32_t descriptorSet
) 
```




<hr>



### function BindFrameBuffer 

```C++
virtual void SR_GRAPH_NS::Pipeline::BindFrameBuffer (
    FramebufferPtr pFBO
) 
```




<hr>



### function BindIBO 

_Index Buffer Object - биндим для рендера вершин по индексам_ 
```C++
virtual void SR_GRAPH_NS::Pipeline::BindIBO (
    uint32_t IBO
) 
```




<hr>



### function BindSSBO 

_Shader Storage Buffer Object - обеспечивает привязку для передачм данных в шейдеры_ 
```C++
virtual void SR_GRAPH_NS::Pipeline::BindSSBO (
    uint32_t SSBO
) 
```




<hr>



### function BindTexture 

```C++
virtual void SR_GRAPH_NS::Pipeline::BindTexture (
    uint8_t activeTexture,
    uint32_t textureId
) 
```




<hr>



### function BindUBO 

[_**Uniform**_](structSR__GRAPH__NS_1_1Uniform.md) _Buffer Object - обеспечивает привязку для передачм данных в шейдеры_
```C++
virtual void SR_GRAPH_NS::Pipeline::BindUBO (
    uint32_t UBO
) 
```




<hr>



### function BindVBO 

_Vertex Buffer Object - биндими для рендера вершин_ 
```C++
virtual void SR_GRAPH_NS::Pipeline::BindVBO (
    uint32_t VBO
) 
```




<hr>



### function ClearBuffers [1/3]

```C++
virtual void SR_GRAPH_NS::Pipeline::ClearBuffers () 
```



Очистка кадрового буфера цветом. Если у буфера несколько attachment'ов, то в colorCount нужно задать их количество 


        

<hr>



### function ClearBuffers [2/3]

```C++
virtual void SR_GRAPH_NS::Pipeline::ClearBuffers (
    float_t r,
    float_t g,
    float_t b,
    float_t a,
    float_t depth,
    uint8_t colorCount
) 
```




<hr>



### function ClearBuffers [3/3]

```C++
virtual void SR_GRAPH_NS::Pipeline::ClearBuffers (
    const ClearColors & clearColors,
    std::optional< float_t > depth
) 
```




<hr>



### function ClearColorBuffer 

```C++
virtual void SR_GRAPH_NS::Pipeline::ClearColorBuffer (
    const ClearColors & clearColors
) 
```




<hr>



### function ClearDepthBuffer 

```C++
virtual void SR_GRAPH_NS::Pipeline::ClearDepthBuffer (
    float_t depth
) 
```




<hr>



### function ClearFrameBuffersQueue 

_Вызывается в начале построения сцены рендера, чистит очередь рендера._ 
```C++
virtual void SR_GRAPH_NS::Pipeline::ClearFrameBuffersQueue () 
```




<hr>



### function Destroy 

_Чистим все данные графического конфейера и де-инициализируем его_ 
```C++
inline virtual bool SR_GRAPH_NS::Pipeline::Destroy () 
```




<hr>



### function DestroyOverlay 

```C++
virtual void SR_GRAPH_NS::Pipeline::DestroyOverlay () 
```




<hr>



### function Dispatch 

_-----------------------------------------_  _Вычисления -------------------------------------------------_ __
```C++
virtual void SR_GRAPH_NS::Pipeline::Dispatch (
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ
) 
```




<hr>



### function Draw 

_Обычная отрисовка вершин_ 
```C++
virtual void SR_GRAPH_NS::Pipeline::Draw (
    uint32_t count
) 
```




<hr>



### function DrawFrame 

```C++
virtual void SR_GRAPH_NS::Pipeline::DrawFrame () 
```



Отрисовка кадра на экран После вызова функции кадр считается законченным и [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md) очищается 


        

<hr>



### function DrawIndices 

_---------------------------------------_  _Вызовы отрисовки ---------------------------------------------_ __
```C++
virtual void SR_GRAPH_NS::Pipeline::DrawIndices (
    uint32_t count
) 
```



Отрисовка вершин по индексам 


        

<hr>



### function EndCmdBuffer 

_Конец записи в буфер команд. Разделение необходимо некоторым графическим API._ 
```C++
virtual void SR_GRAPH_NS::Pipeline::EndCmdBuffer () 
```




<hr>



### function EndCompute 

_Конец вычислений в Compute Shader._ 
```C++
virtual void SR_GRAPH_NS::Pipeline::EndCompute () 
```




<hr>



### function EndDrawOverlay 

```C++
virtual void SR_GRAPH_NS::Pipeline::EndDrawOverlay (
    OverlayType overlayType
) 
```




<hr>



### function EndRender 

_Обязательно нужно вызвать после успешного вызова BeginRender._ 
```C++
virtual void SR_GRAPH_NS::Pipeline::EndRender () 
```




<hr>



### function FreeCubeMap 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::FreeCubeMap (
    int32_t * id
) 
```




<hr>



### function FreeDescriptorSet 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::FreeDescriptorSet (
    int32_t * id
) 
```




<hr>



### function FreeFBO 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::FreeFBO (
    int32_t * id
) 
```




<hr>



### function FreeIBO 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::FreeIBO (
    int32_t * id
) 
```




<hr>



### function FreeSSBO 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::FreeSSBO (
    int32_t * id
) 
```




<hr>



### function FreeShader 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::FreeShader (
    int32_t * id
) 
```




<hr>



### function FreeTexture 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::FreeTexture (
    int32_t * id
) 
```




<hr>



### function FreeUBO 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::FreeUBO (
    int32_t * id
) 
```




<hr>



### function FreeVBO 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::FreeVBO (
    int32_t * id
) 
```




<hr>



### function GetBuildIterationsCount 

```C++
inline virtual SR_NODISCARD uint8_t SR_GRAPH_NS::Pipeline::GetBuildIterationsCount () noexcept const
```




<hr>



### function GetBuildState 

```C++
inline SR_NODISCARD const PipelineState & SR_GRAPH_NS::Pipeline::GetBuildState () const
```




<hr>



### function GetCurrentBuildIteration 

```C++
inline SR_NODISCARD uint8_t SR_GRAPH_NS::Pipeline::GetCurrentBuildIteration () noexcept const
```




<hr>



### function GetCurrentDescriptorSet 

```C++
inline SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::GetCurrentDescriptorSet () noexcept const
```




<hr>



### function GetCurrentFBOHandle 

```C++
inline virtual SR_NODISCARD void * SR_GRAPH_NS::Pipeline::GetCurrentFBOHandle () const
```




<hr>



### function GetCurrentFrameBuffer 

```C++
inline SR_NODISCARD FramebufferPtr SR_GRAPH_NS::Pipeline::GetCurrentFrameBuffer () noexcept const
```




<hr>



### function GetCurrentFrameBufferId 

```C++
inline SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::GetCurrentFrameBufferId () noexcept const
```




<hr>



### function GetCurrentFrameBufferLayer 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::Pipeline::GetCurrentFrameBufferLayer () noexcept const
```




<hr>



### function GetCurrentRenderStrategy 

```C++
inline SR_NODISCARD RenderStrategy * SR_GRAPH_NS::Pipeline::GetCurrentRenderStrategy () noexcept const
```




<hr>



### function GetCurrentShader 

```C++
inline SR_NODISCARD ShaderPtr SR_GRAPH_NS::Pipeline::GetCurrentShader () const
```




<hr>



### function GetCurrentShaderHandle 

```C++
inline virtual SR_NODISCARD void * SR_GRAPH_NS::Pipeline::GetCurrentShaderHandle () const
```




<hr>



### function GetCurrentShaderId 

```C++
inline SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::GetCurrentShaderId () const
```




<hr>



### function GetCurrentUBO 

```C++
inline SR_NODISCARD int32_t SR_GRAPH_NS::Pipeline::GetCurrentUBO () const
```




<hr>



### function GetFBOHandles 

```C++
inline virtual SR_NODISCARD std::set< void * > SR_GRAPH_NS::Pipeline::GetFBOHandles () const
```




<hr>



### function GetFrameBufferSampleCount 

```C++
inline virtual SR_NODISCARD uint8_t SR_GRAPH_NS::Pipeline::GetFrameBufferSampleCount () const
```




<hr>



### function GetFramesPerSecond 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::Pipeline::GetFramesPerSecond () noexcept const
```




<hr>



### function GetOverlay 

```C++
virtual const SR_HTYPES_NS::SharedPtr < Overlay > & SR_GRAPH_NS::Pipeline::GetOverlay (
    OverlayType overlayType
) const
```




<hr>



### function GetOverlayTextureDescriptorSet 

```C++
virtual void * SR_GRAPH_NS::Pipeline::GetOverlayTextureDescriptorSet (
    uint32_t textureId,
    OverlayType overlayType
) const
```




<hr>



### function GetPixelColor 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::FColor SR_GRAPH_NS::Pipeline::GetPixelColor (
    uint32_t textureId,
    uint32_t x,
    uint32_t y
) 
```




<hr>



### function GetPreviousState 

```C++
inline SR_NODISCARD const PipelineState & SR_GRAPH_NS::Pipeline::GetPreviousState () const
```




<hr>



### function GetQueue 

```C++
inline SR_NODISCARD FrameBufferQueue & SR_GRAPH_NS::Pipeline::GetQueue () noexcept
```




<hr>



### function GetRenderContext 

```C++
inline SR_NODISCARD RenderContextPtr SR_GRAPH_NS::Pipeline::GetRenderContext () noexcept const
```




<hr>



### function GetRenderStageId 

```C++
inline virtual SR_NODISCARD SR_UTILS_NS::StringAtom SR_GRAPH_NS::Pipeline::GetRenderStageId () const
```




<hr>



### function GetRenderer 

```C++
inline virtual SR_NODISCARD std::string SR_GRAPH_NS::Pipeline::GetRenderer () const
```




<hr>



### function GetSamplesCount 

```C++
SR_NODISCARD uint8_t SR_GRAPH_NS::Pipeline::GetSamplesCount () const
```




<hr>



### function GetShaderHandles 

```C++
inline virtual SR_NODISCARD std::set< void * > SR_GRAPH_NS::Pipeline::GetShaderHandles () const
```




<hr>



### function GetState 

```C++
inline SR_NODISCARD const PipelineState & SR_GRAPH_NS::Pipeline::GetState () const
```




<hr>



### function GetSupportedSamples 

```C++
inline virtual SR_NODISCARD uint8_t SR_GRAPH_NS::Pipeline::GetSupportedSamples () noexcept const
```




<hr>



### function GetType 

```C++
virtual SR_NODISCARD PipelineType SR_GRAPH_NS::Pipeline::GetType () noexcept const = 0
```




<hr>



### function GetUsedMemory 

```C++
inline virtual uint64_t SR_GRAPH_NS::Pipeline::GetUsedMemory () const
```




<hr>



### function GetVendor 

_------------------------------------_  _Вспомогательные методы ------------------------------------------_ __
```C++
inline virtual SR_NODISCARD std::string SR_GRAPH_NS::Pipeline::GetVendor () const
```




<hr>



### function GetVersion 

```C++
inline virtual SR_NODISCARD std::string SR_GRAPH_NS::Pipeline::GetVersion () const
```




<hr>



### function GetWindow 

```C++
inline SR_NODISCARD WindowPtr SR_GRAPH_NS::Pipeline::GetWindow () const
```




<hr>



### function Init 

_Подключаем окно и настраиваем взаимодействие рендера с ним_ 
```C++
virtual bool SR_GRAPH_NS::Pipeline::Init () 
```




<hr>



### function InitOverlay 

_---------------------------------------_  _Работа с_[_**Overlay**_](classSR__GRAPH__NS_1_1Overlay.md) _---------------------------------------------_ __
```C++
virtual bool SR_GRAPH_NS::Pipeline::InitOverlay () 
```




<hr>



### function IsDirty 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Pipeline::IsDirty () noexcept const
```




<hr>



### function IsFBOQueueValid 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Pipeline::IsFBOQueueValid () noexcept const
```




<hr>



### function IsMultiSamplingSupported 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Pipeline::IsMultiSamplingSupported () noexcept const
```




<hr>



### function IsRenderState 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Pipeline::IsRenderState () noexcept const
```




<hr>



### function IsSamplerValid 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::IsSamplerValid (
    int32_t id
) const
```




<hr>



### function IsShaderChanged 

_Изменился ли текущий шейдер после UseShader. Даже если был вызван UnUseShader. Низкоуровневая проверка._ 
```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Pipeline::IsShaderChanged () noexcept const
```




<hr>



### function IsShaderConstantSupport 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::Pipeline::IsShaderConstantSupport () const
```




<hr>



### function IsVSyncEnabled 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::Pipeline::IsVSyncEnabled () const
```




<hr>



### function MapSSBO 

```C++
inline virtual bool SR_GRAPH_NS::Pipeline::MapSSBO (
    uint32_t SSBO,
    void ** ppData
) 
```




<hr>



### function OnMultiSampleChanged 

_-------------------------------------_  _Мультисемплинг и VSync -----------------------------------------_ __
```C++
virtual void SR_GRAPH_NS::Pipeline::OnMultiSampleChanged () 
```




<hr>



### function OnResize 

```C++
virtual void SR_GRAPH_NS::Pipeline::OnResize (
    const SR_MATH_NS::UVector2 & size
) 
```




<hr>



### function Pipeline 

```C++
explicit SR_GRAPH_NS::Pipeline::Pipeline (
    const RenderContextPtr & pContext
) 
```




<hr>



### function PipelineError 

```C++
virtual void SR_GRAPH_NS::Pipeline::PipelineError (
    const std::string & msg
) const
```




<hr>



### function PostInit 

_Профайлинг и прочие пост-штучки_ 
```C++
inline virtual bool SR_GRAPH_NS::Pipeline::PostInit () 
```




<hr>



### function PreInit 

_-------------------------------------_  _Инициализация рендера ------------------------------------------_ __
```C++
virtual bool SR_GRAPH_NS::Pipeline::PreInit (
    const PipelinePreInitInfo & info
) 
```



Предназначено для инициализации всех структур и классов 


        

<hr>



### function PrepareFrame 

_------------------------------------_  _Главные методы рендера ------------------------------------------_ __
```C++
virtual void SR_GRAPH_NS::Pipeline::PrepareFrame () 
```



Вызывается перед началом рендера, подготовка к рендеру 


        

<hr>



### function PrepareOverlay 

```C++
virtual void SR_GRAPH_NS::Pipeline::PrepareOverlay (
    OverlayType overlayType
) 
```




<hr>



### function PushConstants 

```C++
virtual void SR_GRAPH_NS::Pipeline::PushConstants (
    void * pData,
    uint64_t size
) 
```



Передает данные в шейдер, которые не будут обновляться до следующего перерисовывания сцены. Поддерживается не всеми API 


        

<hr>



### function ReCreateOverlay 

```C++
virtual void SR_GRAPH_NS::Pipeline::ReCreateOverlay () 
```




<hr>



### function ReadSSBO 

_Читает данные из SSBO в память_ 
```C++
virtual void SR_GRAPH_NS::Pipeline::ReadSSBO (
    uint32_t SSBO,
    void * pData,
    uint64_t size
) 
```




<hr>



### function ResetLastShader 

```C++
virtual void SR_GRAPH_NS::Pipeline::ResetLastShader () 
```




<hr>



### function ResetSubmitQueue 

```C++
virtual void SR_GRAPH_NS::Pipeline::ResetSubmitQueue () 
```




<hr>



### function SetBuildIteration 

```C++
virtual void SR_GRAPH_NS::Pipeline::SetBuildIteration (
    uint8_t iteration
) 
```




<hr>



### function SetCurrentFrameBuffer 

```C++
virtual void SR_GRAPH_NS::Pipeline::SetCurrentFrameBuffer (
    FramebufferPtr pFrameBuffer
) 
```




<hr>



### function SetCurrentFrameBufferLayer 

```C++
inline virtual void SR_GRAPH_NS::Pipeline::SetCurrentFrameBufferLayer (
    uint32_t layer
) 
```




<hr>



### function SetCurrentRenderStrategy 

```C++
inline virtual void SR_GRAPH_NS::Pipeline::SetCurrentRenderStrategy (
    RenderStrategy * pStrategy
) 
```




<hr>



### function SetCurrentShader 

```C++
inline virtual void SR_GRAPH_NS::Pipeline::SetCurrentShader (
    ShaderPtr pShader
) 
```




<hr>



### function SetCurrentShaderId 

```C++
inline virtual void SR_GRAPH_NS::Pipeline::SetCurrentShaderId (
    int32_t id
) 
```




<hr>



### function SetDirty 

```C++
virtual void SR_GRAPH_NS::Pipeline::SetDirty (
    bool dirty
) 
```



Устанавливает состояние графического конвейера. Если грязный, то будет перестроена сцена Если чистый, то считаем, что постороение сцены завершено 


        

<hr>



### function SetOverlayEnabled 

```C++
virtual void SR_GRAPH_NS::Pipeline::SetOverlayEnabled (
    OverlayType overlayType,
    bool enabled
) 
```




<hr>



### function SetOverlaySurfaceDirty 

```C++
virtual void SR_GRAPH_NS::Pipeline::SetOverlaySurfaceDirty () 
```




<hr>



### function SetSampleCount 

```C++
virtual void SR_GRAPH_NS::Pipeline::SetSampleCount (
    uint8_t count
) 
```




<hr>



### function SetScissor 

```C++
inline virtual void SR_GRAPH_NS::Pipeline::SetScissor (
    int32_t width=-1,
    int32_t height=-1
) 
```




<hr>



### function SetVSyncEnabled 

```C++
inline virtual void SR_GRAPH_NS::Pipeline::SetVSyncEnabled (
    bool enabled
) 
```




<hr>



### function SetViewport 

```C++
inline virtual void SR_GRAPH_NS::Pipeline::SetViewport (
    int32_t width=-1,
    int32_t height=-1
) 
```




<hr>



### function SwitchWindow 

```C++
virtual void SR_GRAPH_NS::Pipeline::SwitchWindow (
    const WindowPtr & pWindow
) 
```




<hr>



### function UnMapSSBO 

```C++
inline virtual void SR_GRAPH_NS::Pipeline::UnMapSSBO (
    uint32_t SSBO
) 
```




<hr>



### function UnUseShader 

```C++
virtual void SR_GRAPH_NS::Pipeline::UnUseShader () 
```




<hr>



### function UpdateDescriptorSets 

_Привязываем к дескриптору юниформы. Работает не во всех API._ 
```C++
virtual void SR_GRAPH_NS::Pipeline::UpdateDescriptorSets (
    uint32_t descriptorSet,
    const SRDescriptorUpdateInfos & updateInfo
) 
```




<hr>



### function UpdateMultiSampling 

```C++
virtual void SR_GRAPH_NS::Pipeline::UpdateMultiSampling () 
```




<hr>



### function UpdateSSBO 

_Обеспечивает обновление данных в шейдере_ 
```C++
virtual void SR_GRAPH_NS::Pipeline::UpdateSSBO (
    uint32_t SSBO,
    void * pData,
    uint64_t size
) 
```




<hr>



### function UpdateUBO 

_Обеспечивает обновление данных в шейдере_ 
```C++
virtual void SR_GRAPH_NS::Pipeline::UpdateUBO (
    uint32_t UBO,
    void * pData,
    uint64_t size
) 
```




<hr>



### function UseShader 

_------------------------------------------_  _Биндинги --------------------------------------------------_ __
```C++
virtual void SR_GRAPH_NS::Pipeline::UseShader (
    uint32_t shaderProgram
) 
```




<hr>



### function WaitComputeIdle 

```C++
virtual void SR_GRAPH_NS::Pipeline::WaitComputeIdle () 
```




<hr>



### function ~Pipeline 

```C++
virtual SR_GRAPH_NS::Pipeline::~Pipeline () 
```




<hr>
## Protected Attributes Documentation




### variable m\_bindedDescriptors 

```C++
SR_HTYPES_NS::PoolSet<bool> SR_GRAPH_NS::Pipeline::m_bindedDescriptors;
```




<hr>



### variable m\_buildState 

_Состояние, которое было на момент постоения сцены рендера_ 
```C++
PipelineState SR_GRAPH_NS::Pipeline::m_buildState;
```




<hr>



### variable m\_currentSampleCount 

```C++
uint8_t SR_GRAPH_NS::Pipeline::m_currentSampleCount;
```




<hr>



### variable m\_dirty 

```C++
std::atomic<bool> SR_GRAPH_NS::Pipeline::m_dirty;
```




<hr>



### variable m\_enableValidationLayers 

```C++
bool SR_GRAPH_NS::Pipeline::m_enableValidationLayers;
```




<hr>



### variable m\_errorsCount 

```C++
uint64_t SR_GRAPH_NS::Pipeline::m_errorsCount;
```




<hr>



### variable m\_fboQueue 

```C++
FrameBufferQueue SR_GRAPH_NS::Pipeline::m_fboQueue;
```




<hr>



### variable m\_frames 

```C++
uint32_t SR_GRAPH_NS::Pipeline::m_frames;
```




<hr>



### variable m\_framesPerSecond 

```C++
uint32_t SR_GRAPH_NS::Pipeline::m_framesPerSecond;
```




<hr>



### variable m\_isCmdState 

```C++
bool SR_GRAPH_NS::Pipeline::m_isCmdState;
```




<hr>



### variable m\_isComputeState 

```C++
bool SR_GRAPH_NS::Pipeline::m_isComputeState;
```




<hr>



### variable m\_isMultiSampleSupported 

```C++
bool SR_GRAPH_NS::Pipeline::m_isMultiSampleSupported;
```




<hr>



### variable m\_isRenderState 

```C++
bool SR_GRAPH_NS::Pipeline::m_isRenderState;
```




<hr>



### variable m\_isShaderChanged 

```C++
bool SR_GRAPH_NS::Pipeline::m_isShaderChanged;
```




<hr>



### variable m\_lastSecond 

```C++
std::optional<SR_UTILS_NS::TimePointType> SR_GRAPH_NS::Pipeline::m_lastSecond;
```




<hr>



### variable m\_newSampleCount 

_Все параметры, относящиется к мультисемплингу_ 
```C++
std::optional<uint8_t> SR_GRAPH_NS::Pipeline::m_newSampleCount;
```




<hr>



### variable m\_overlays 

```C++
std::map<OverlayType, SR_HTYPES_NS::SharedPtr<Overlay> > SR_GRAPH_NS::Pipeline::m_overlays;
```




<hr>



### variable m\_preInitInfo 

```C++
PipelinePreInitInfo SR_GRAPH_NS::Pipeline::m_preInitInfo;
```




<hr>



### variable m\_previousState 

```C++
PipelineState SR_GRAPH_NS::Pipeline::m_previousState;
```




<hr>



### variable m\_renderContext 

```C++
RenderContextPtr SR_GRAPH_NS::Pipeline::m_renderContext;
```




<hr>



### variable m\_requiredSampleCount 

```C++
uint8_t SR_GRAPH_NS::Pipeline::m_requiredSampleCount;
```




<hr>



### variable m\_state 

```C++
PipelineState SR_GRAPH_NS::Pipeline::m_state;
```




<hr>



### variable m\_supportedSampleCount 

```C++
uint8_t SR_GRAPH_NS::Pipeline::m_supportedSampleCount;
```




<hr>



### variable m\_window 

```C++
WindowPtr SR_GRAPH_NS::Pipeline::m_window;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/Pipeline.h`

