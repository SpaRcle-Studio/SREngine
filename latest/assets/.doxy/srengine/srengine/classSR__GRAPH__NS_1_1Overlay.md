

# Class SR\_GRAPH\_NS::Overlay



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Overlay**](classSR__GRAPH__NS_1_1Overlay.md)



[More...](#detailed-description)

* `#include <Overlay.h>`



Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)


Inherited by the following classes: [SR\_GRAPH\_NS::ImGuiOverlay](classSR__GRAPH__NS_1_1ImGuiOverlay.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](#typedef-pipelineptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Overlay**](classSR__GRAPH__NS_1_1Overlay.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Overlay**](classSR__GRAPH__NS_1_1Overlay.md) &gt; | [**Super**](#typedef-super)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**BeginDraw**](#function-begindraw) () = 0<br> |
| virtual void | [**Destroy**](#function-destroy) () = 0<br> |
| virtual void | [**EndDraw**](#function-enddraw) () = 0<br> |
| virtual SR\_NODISCARD std::string | [**GetName**](#function-getname) () const = 0<br> |
|  SR\_NODISCARD const PipelinePtr & | [**GetPipeline**](#function-getpipeline) () noexcept const<br> |
| virtual SR\_NODISCARD void \* | [**GetTextureDescriptorSet**](#function-gettexturedescriptorset) (uint32\_t textureId) <br> |
| virtual SR\_NODISCARD bool | [**Init**](#function-init) () = 0<br> |
|  SR\_NODISCARD bool | [**IsEnabled**](#function-isenabled) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsSurfaceDirty**](#function-issurfacedirty) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsUndockingActive**](#function-isundockingactive) () const = 0<br> |
|   | [**Overlay**](#function-overlay) (PipelinePtr pPipeline) <br> |
| virtual void | [**Prepare**](#function-prepare) () <br> |
| virtual SR\_NODISCARD bool | [**ReCreate**](#function-recreate) () = 0<br> |
|  void | [**SetEnabled**](#function-setenabled) (bool enabled) <br> |
|  void | [**SetSurfaceDirty**](#function-setsurfacedirty) () <br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
|  SR\_NODISCARD const void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-12) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br>_NOLINT(modernize-use-nodiscard)_  |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getthis) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-22) () <br> |
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
|  const [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-12) () const<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getsrclass) () const = 0<br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-reset) () = 0<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) = 0<br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-12) () = default<br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-22) ([**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* data) <br> |
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () = default<br> |




## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |
















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**m\_enabled**](#variable-m_enabled)   = `true`<br> |
|  bool | [**m\_initialized**](#variable-m_initialized)   = `false`<br> |
|  PipelinePtr | [**m\_pipeline**](#variable-m_pipeline)  <br> |
|  bool | [**m\_surfaceDirty**](#variable-m_surfacedirty)   = `true`<br> |
|  bool | [**m\_tracyEnabled**](#variable-m_tracyenabled)   = `false`<br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |
























































## Detailed Description


## Public Types Documentation




### typedef PipelinePtr 

```C++
using SR_GRAPH_NS::Overlay::PipelinePtr =  SR_HTYPES_NS::SharedPtr<Pipeline>;
```




<hr>



### typedef Ptr 

```C++
using SR_GRAPH_NS::Overlay::Ptr =  SR_HTYPES_NS::SharedPtr<Overlay>;
```




<hr>



### typedef Super 

```C++
using SR_GRAPH_NS::Overlay::Super =  SR_HTYPES_NS::SharedPtr<Overlay>;
```




<hr>
## Public Functions Documentation




### function BeginDraw 

```C++
virtual bool SR_GRAPH_NS::Overlay::BeginDraw () = 0
```




<hr>



### function Destroy 

```C++
virtual void SR_GRAPH_NS::Overlay::Destroy () = 0
```




<hr>



### function EndDraw 

```C++
virtual void SR_GRAPH_NS::Overlay::EndDraw () = 0
```




<hr>



### function GetName 

```C++
virtual SR_NODISCARD std::string SR_GRAPH_NS::Overlay::GetName () const = 0
```




<hr>



### function GetPipeline 

```C++
inline SR_NODISCARD const PipelinePtr & SR_GRAPH_NS::Overlay::GetPipeline () noexcept const
```




<hr>



### function GetTextureDescriptorSet 

```C++
inline virtual SR_NODISCARD void * SR_GRAPH_NS::Overlay::GetTextureDescriptorSet (
    uint32_t textureId
) 
```




<hr>



### function Init 

```C++
virtual SR_NODISCARD bool SR_GRAPH_NS::Overlay::Init () = 0
```




<hr>



### function IsEnabled 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Overlay::IsEnabled () noexcept const
```




<hr>



### function IsSurfaceDirty 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Overlay::IsSurfaceDirty () noexcept const
```




<hr>



### function IsUndockingActive 

```C++
virtual SR_NODISCARD bool SR_GRAPH_NS::Overlay::IsUndockingActive () const = 0
```




<hr>



### function Overlay 

```C++
explicit SR_GRAPH_NS::Overlay::Overlay (
    PipelinePtr pPipeline
) 
```




<hr>



### function Prepare 

```C++
inline virtual void SR_GRAPH_NS::Overlay::Prepare () 
```




<hr>



### function ReCreate 

```C++
virtual SR_NODISCARD bool SR_GRAPH_NS::Overlay::ReCreate () = 0
```




<hr>



### function SetEnabled 

```C++
inline void SR_GRAPH_NS::Overlay::SetEnabled (
    bool enabled
) 
```




<hr>



### function SetSurfaceDirty 

```C++
inline void SR_GRAPH_NS::Overlay::SetSurfaceDirty () 
```




<hr>
## Protected Attributes Documentation




### variable m\_enabled 

```C++
bool SR_GRAPH_NS::Overlay::m_enabled;
```




<hr>



### variable m\_initialized 

```C++
bool SR_GRAPH_NS::Overlay::m_initialized;
```




<hr>



### variable m\_pipeline 

```C++
PipelinePtr SR_GRAPH_NS::Overlay::m_pipeline;
```




<hr>



### variable m\_surfaceDirty 

```C++
bool SR_GRAPH_NS::Overlay::m_surfaceDirty;
```




<hr>



### variable m\_tracyEnabled 

```C++
bool SR_GRAPH_NS::Overlay::m_tracyEnabled;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Overlay/Overlay.h`

