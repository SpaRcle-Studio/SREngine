

# Class SR\_GRAPH\_NS::VulkanImGuiOverlay



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**VulkanImGuiOverlay**](classSR__GRAPH__NS_1_1VulkanImGuiOverlay.md)








Inherits the following classes: [SR\_GRAPH\_NS::ImGuiOverlay](classSR__GRAPH__NS_1_1ImGuiOverlay.md)


















## Public Types inherited from SR_GRAPH_NS::Overlay

See [SR\_GRAPH\_NS::Overlay](classSR__GRAPH__NS_1_1Overlay.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](classSR__GRAPH__NS_1_1Overlay.md#typedef-pipelineptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Overlay**](classSR__GRAPH__NS_1_1Overlay.md) &gt; | [**Ptr**](classSR__GRAPH__NS_1_1Overlay.md#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Overlay**](classSR__GRAPH__NS_1_1Overlay.md) &gt; | [**Super**](classSR__GRAPH__NS_1_1Overlay.md#typedef-super)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |






























































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**BeginDraw**](#function-begindraw) () override<br> |
| virtual void | [**Destroy**](#function-destroy) () override<br> |
| virtual void | [**EndDraw**](#function-enddraw) () override<br> |
| virtual SR\_NODISCARD std::string | [**GetName**](#function-getname) () override const<br> |
|  SR\_NODISCARD VkSemaphore | [**GetSemaphore**](#function-getsemaphore) () <br> |
|  SR\_NODISCARD EvoVulkan::SubmitInfo & | [**GetSubmitInfo**](#function-getsubmitinfo) () <br> |
| virtual SR\_NODISCARD void \* | [**GetTextureDescriptorSet**](#function-gettexturedescriptorset) (uint32\_t textureId) override<br> |
| virtual SR\_NODISCARD bool | [**Init**](#function-init) () override<br> |
| virtual SR\_NODISCARD bool | [**ReCreate**](#function-recreate) () override<br> |
| virtual void | [**ReloadFonts**](#function-reloadfonts) () override<br> |
|  SR\_NODISCARD EvoVulkan::SubmitInfo & | [**Render**](#function-render) (uint32\_t frame) <br> |
|  void | [**ResetSubmitInfo**](#function-resetsubmitinfo) () <br> |
|   | [**VulkanImGuiOverlay**](#function-vulkanimguioverlay) (PipelinePtr pPipeline) <br> |
|   | [**~VulkanImGuiOverlay**](#function-vulkanimguioverlay) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::ImGuiOverlay

See [SR\_GRAPH\_NS::ImGuiOverlay](classSR__GRAPH__NS_1_1ImGuiOverlay.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Destroy**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-destroy) () override<br> |
|  SR\_NODISCARD void \* | [**GetIconFont**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-geticonfont) () const<br> |
|  SR\_NODISCARD void \* | [**GetMainFont**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-getmainfont) () const<br> |
|   | [**ImGuiOverlay**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-imguioverlay) (PipelinePtr pPipeline) <br> |
| virtual SR\_NODISCARD bool | [**Init**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-init) () override<br> |
| virtual SR\_NODISCARD bool | [**IsUndockingActive**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-isundockingactive) () override const<br> |
|  SR\_NODISCARD bool | [**IsViewportsEnabled**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-isviewportsenabled) () const<br> |
| virtual void | [**Prepare**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-prepare) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::Overlay

See [SR\_GRAPH\_NS::Overlay](classSR__GRAPH__NS_1_1Overlay.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**BeginDraw**](classSR__GRAPH__NS_1_1Overlay.md#function-begindraw) () = 0<br> |
| virtual void | [**Destroy**](classSR__GRAPH__NS_1_1Overlay.md#function-destroy) () = 0<br> |
| virtual void | [**EndDraw**](classSR__GRAPH__NS_1_1Overlay.md#function-enddraw) () = 0<br> |
| virtual SR\_NODISCARD std::string | [**GetName**](classSR__GRAPH__NS_1_1Overlay.md#function-getname) () const = 0<br> |
|  SR\_NODISCARD const PipelinePtr & | [**GetPipeline**](classSR__GRAPH__NS_1_1Overlay.md#function-getpipeline) () noexcept const<br> |
| virtual SR\_NODISCARD void \* | [**GetTextureDescriptorSet**](classSR__GRAPH__NS_1_1Overlay.md#function-gettexturedescriptorset) (uint32\_t textureId) <br> |
| virtual SR\_NODISCARD bool | [**Init**](classSR__GRAPH__NS_1_1Overlay.md#function-init) () = 0<br> |
|  SR\_NODISCARD bool | [**IsEnabled**](classSR__GRAPH__NS_1_1Overlay.md#function-isenabled) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsSurfaceDirty**](classSR__GRAPH__NS_1_1Overlay.md#function-issurfacedirty) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsUndockingActive**](classSR__GRAPH__NS_1_1Overlay.md#function-isundockingactive) () const = 0<br> |
|   | [**Overlay**](classSR__GRAPH__NS_1_1Overlay.md#function-overlay) (PipelinePtr pPipeline) <br> |
| virtual void | [**Prepare**](classSR__GRAPH__NS_1_1Overlay.md#function-prepare) () <br> |
| virtual SR\_NODISCARD bool | [**ReCreate**](classSR__GRAPH__NS_1_1Overlay.md#function-recreate) () = 0<br> |
|  void | [**SetEnabled**](classSR__GRAPH__NS_1_1Overlay.md#function-setenabled) (bool enabled) <br> |
|  void | [**SetSurfaceDirty**](classSR__GRAPH__NS_1_1Overlay.md#function-setsurfacedirty) () <br> |


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


























## Protected Attributes inherited from SR_GRAPH_NS::ImGuiOverlay

See [SR\_GRAPH\_NS::ImGuiOverlay](classSR__GRAPH__NS_1_1ImGuiOverlay.md)

| Type | Name |
| ---: | :--- |
|  void \* | [**m\_context**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#variable-m_context)   = `nullptr`<br> |
|  float\_t | [**m\_fontSize**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#variable-m_fontsize)   = `12.0f`<br> |
|  void \* | [**m\_iconFont**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#variable-m_iconfont)   = `nullptr`<br> |
|  float\_t | [**m\_iconFontSize**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#variable-m_iconfontsize)   = `40.0f`<br> |
|  [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**m\_iniPathEditor**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#variable-m_inipatheditor)  <br> |
|  [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**m\_iniPathWidgets**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#variable-m_inipathwidgets)  <br> |
|  void \* | [**m\_mainFont**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#variable-m_mainfont)   = `nullptr`<br> |


## Protected Attributes inherited from SR_GRAPH_NS::Overlay

See [SR\_GRAPH\_NS::Overlay](classSR__GRAPH__NS_1_1Overlay.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_enabled**](classSR__GRAPH__NS_1_1Overlay.md#variable-m_enabled)   = `true`<br> |
|  bool | [**m\_initialized**](classSR__GRAPH__NS_1_1Overlay.md#variable-m_initialized)   = `false`<br> |
|  PipelinePtr | [**m\_pipeline**](classSR__GRAPH__NS_1_1Overlay.md#variable-m_pipeline)  <br> |
|  bool | [**m\_surfaceDirty**](classSR__GRAPH__NS_1_1Overlay.md#variable-m_surfacedirty)   = `true`<br> |
|  bool | [**m\_tracyEnabled**](classSR__GRAPH__NS_1_1Overlay.md#variable-m_tracyenabled)   = `false`<br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |










































































## Protected Functions inherited from SR_GRAPH_NS::ImGuiOverlay

See [SR\_GRAPH\_NS::ImGuiOverlay](classSR__GRAPH__NS_1_1ImGuiOverlay.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**ReloadFonts**](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-reloadfonts) () <br> |


















## Public Functions Documentation




### function BeginDraw 

```C++
virtual bool SR_GRAPH_NS::VulkanImGuiOverlay::BeginDraw () override
```



Implements [*SR\_GRAPH\_NS::Overlay::BeginDraw*](classSR__GRAPH__NS_1_1Overlay.md#function-begindraw)


<hr>



### function Destroy 

```C++
virtual void SR_GRAPH_NS::VulkanImGuiOverlay::Destroy () override
```



Implements [*SR\_GRAPH\_NS::ImGuiOverlay::Destroy*](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-destroy)


<hr>



### function EndDraw 

```C++
virtual void SR_GRAPH_NS::VulkanImGuiOverlay::EndDraw () override
```



Implements [*SR\_GRAPH\_NS::Overlay::EndDraw*](classSR__GRAPH__NS_1_1Overlay.md#function-enddraw)


<hr>



### function GetName 

```C++
inline virtual SR_NODISCARD std::string SR_GRAPH_NS::VulkanImGuiOverlay::GetName () override const
```



Implements [*SR\_GRAPH\_NS::Overlay::GetName*](classSR__GRAPH__NS_1_1Overlay.md#function-getname)


<hr>



### function GetSemaphore 

```C++
inline SR_NODISCARD VkSemaphore SR_GRAPH_NS::VulkanImGuiOverlay::GetSemaphore () 
```




<hr>



### function GetSubmitInfo 

```C++
inline SR_NODISCARD EvoVulkan::SubmitInfo & SR_GRAPH_NS::VulkanImGuiOverlay::GetSubmitInfo () 
```




<hr>



### function GetTextureDescriptorSet 

```C++
virtual SR_NODISCARD void * SR_GRAPH_NS::VulkanImGuiOverlay::GetTextureDescriptorSet (
    uint32_t textureId
) override
```



Implements [*SR\_GRAPH\_NS::Overlay::GetTextureDescriptorSet*](classSR__GRAPH__NS_1_1Overlay.md#function-gettexturedescriptorset)


<hr>



### function Init 

```C++
virtual SR_NODISCARD bool SR_GRAPH_NS::VulkanImGuiOverlay::Init () override
```



Implements [*SR\_GRAPH\_NS::ImGuiOverlay::Init*](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-init)


<hr>



### function ReCreate 

```C++
virtual SR_NODISCARD bool SR_GRAPH_NS::VulkanImGuiOverlay::ReCreate () override
```



Implements [*SR\_GRAPH\_NS::Overlay::ReCreate*](classSR__GRAPH__NS_1_1Overlay.md#function-recreate)


<hr>



### function ReloadFonts 

```C++
virtual void SR_GRAPH_NS::VulkanImGuiOverlay::ReloadFonts () override
```



Implements [*SR\_GRAPH\_NS::ImGuiOverlay::ReloadFonts*](classSR__GRAPH__NS_1_1ImGuiOverlay.md#function-reloadfonts)


<hr>



### function Render 

```C++
SR_NODISCARD EvoVulkan::SubmitInfo & SR_GRAPH_NS::VulkanImGuiOverlay::Render (
    uint32_t frame
) 
```




<hr>



### function ResetSubmitInfo 

```C++
void SR_GRAPH_NS::VulkanImGuiOverlay::ResetSubmitInfo () 
```




<hr>



### function VulkanImGuiOverlay 

```C++
inline explicit SR_GRAPH_NS::VulkanImGuiOverlay::VulkanImGuiOverlay (
    PipelinePtr pPipeline
) 
```




<hr>



### function ~VulkanImGuiOverlay 

```C++
inline SR_GRAPH_NS::VulkanImGuiOverlay::~VulkanImGuiOverlay () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Overlay/VulkanImGuiOverlay.h`

