

# Class SR\_GRAPH\_NS::RenderQueue



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md)








Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)


Inherited by the following classes: [SR\_GRAPH\_NS::ColorBufferRenderQueue](classSR__GRAPH__NS_1_1ColorBufferRenderQueue.md)










## Classes

| Type | Name |
| ---: | :--- |
| struct | [**MeshInfo**](structSR__GRAPH__NS_1_1RenderQueue_1_1MeshInfo.md) <br> |
| struct | [**RenderQueueLessPredicate**](structSR__GRAPH__NS_1_1RenderQueue_1_1RenderQueueLessPredicate.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SortedVector**](classSR__HTYPES__NS_1_1SortedVector.md)&lt; [**MeshInfo**](structSR__GRAPH__NS_1_1RenderQueue_1_1MeshInfo.md), [**RenderQueueLessPredicate**](structSR__GRAPH__NS_1_1RenderQueue_1_1RenderQueueLessPredicate.md) &gt; | [**Queue**](#typedef-queue)  <br> |
| enum uint8\_t | [**QueueState**](#enum-queuestate)  <br> |
| typedef uint8\_t | [**QueueStateFlags**](#typedef-queuestateflags)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD const std::vector&lt; std::pair&lt; Layer, Queue &gt; &gt; & | [**GetQueues**](#function-getqueues) () noexcept const<br> |
|  void | [**Init**](#function-init) () <br> |
|  void | [**OnMeshDirty**](#function-onmeshdirty) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh, [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) \* pInfo) <br> |
|  void | [**Register**](#function-register) (const [**MeshRegistrationInfo**](structSR__GRAPH__NS_1_1MeshRegistrationInfo.md) & info) <br> |
|  bool | [**Render**](#function-render-12) () <br> |
|   | [**RenderQueue**](#function-renderqueue) ([**RenderStrategy**](classSR__GRAPH__NS_1_1RenderStrategy.md) \* pStrategy, [**MeshDrawerPass**](classSR__GRAPH__NS_1_1MeshDrawerPass.md) \* pDrawer) <br> |
|  void | [**UnRegister**](#function-unregister) (const [**MeshRegistrationInfo**](structSR__GRAPH__NS_1_1MeshRegistrationInfo.md) & info) <br> |
|  void | [**Update**](#function-update) () <br> |
| virtual  | [**~RenderQueue**](#function-renderqueue) () <br> |


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
















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**m\_customMeshDraw**](#variable-m_custommeshdraw)   = `false`<br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |












































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**CustomDrawMesh**](#function-customdrawmesh) (const [**MeshInfo**](structSR__GRAPH__NS_1_1RenderQueue_1_1MeshInfo.md) & info) <br> |
|  SR\_NODISCARD [**MeshDrawerPass**](classSR__GRAPH__NS_1_1MeshDrawerPass.md) \* | [**GetMeshDrawerPass**](#function-getmeshdrawerpass) () noexcept const<br> |












## Public Types Documentation




### typedef Queue 

```C++
using SR_GRAPH_NS::RenderQueue::Queue =  SR_HTYPES_NS::SortedVector<MeshInfo, RenderQueueLessPredicate>;
```




<hr>



### enum QueueState 

```C++
enum SR_GRAPH_NS::RenderQueue::QueueState {
    QUEUE_STATE_OK = 0,
    QUEUE_STATE_ERROR = 1 << 1,
    QUEUE_STATE_VBO_ERROR = QUEUE_STATE_ERROR | 1 << 2,
    QUEUE_STATE_SHADER_ERROR = QUEUE_STATE_ERROR | 1 << 3,
    QUEUE_STATE_NOT_RENDERED = QUEUE_STATE_ERROR | 1 << 4,
    QUEUE_STATE_WAIT_REGISTER = QUEUE_STATE_ERROR | 1 << 5,
    QUEUE_STATE_MISSING_SHADER = QUEUE_STATE_ERROR | 1 << 6
};
```




<hr>



### typedef QueueStateFlags 

```C++
typedef uint8_t SR_GRAPH_NS::RenderQueue::QueueStateFlags;
```




<hr>
## Public Functions Documentation




### function GetQueues 

```C++
inline SR_NODISCARD const std::vector< std::pair< Layer, Queue > > & SR_GRAPH_NS::RenderQueue::GetQueues () noexcept const
```




<hr>



### function Init 

```C++
void SR_GRAPH_NS::RenderQueue::Init () 
```




<hr>



### function OnMeshDirty 

```C++
void SR_GRAPH_NS::RenderQueue::OnMeshDirty (
    SR_GTYPES_NS::Mesh * pMesh,
    RenderQueueInfo * pInfo
) 
```




<hr>



### function Register 

```C++
void SR_GRAPH_NS::RenderQueue::Register (
    const MeshRegistrationInfo & info
) 
```




<hr>



### function Render [1/2]

```C++
bool SR_GRAPH_NS::RenderQueue::Render () 
```




<hr>



### function RenderQueue 

```C++
SR_GRAPH_NS::RenderQueue::RenderQueue (
    RenderStrategy * pStrategy,
    MeshDrawerPass * pDrawer
) 
```




<hr>



### function UnRegister 

```C++
void SR_GRAPH_NS::RenderQueue::UnRegister (
    const MeshRegistrationInfo & info
) 
```




<hr>



### function Update 

```C++
void SR_GRAPH_NS::RenderQueue::Update () 
```




<hr>



### function ~RenderQueue 

```C++
virtual SR_GRAPH_NS::RenderQueue::~RenderQueue () 
```




<hr>
## Protected Attributes Documentation




### variable m\_customMeshDraw 

```C++
bool SR_GRAPH_NS::RenderQueue::m_customMeshDraw;
```




<hr>
## Protected Functions Documentation




### function CustomDrawMesh 

```C++
inline virtual void SR_GRAPH_NS::RenderQueue::CustomDrawMesh (
    const MeshInfo & info
) 
```




<hr>



### function GetMeshDrawerPass 

```C++
inline SR_NODISCARD MeshDrawerPass * SR_GRAPH_NS::RenderQueue::GetMeshDrawerPass () noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderQueue.h`

