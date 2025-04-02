

# Class SR\_GRAPH\_NS::Memory::BakedMesh



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**BakedMesh**](classSR__GRAPH__NS_1_1Memory_1_1BakedMesh.md)








Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**BakedMesh**](classSR__GRAPH__NS_1_1Memory_1_1BakedMesh.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddUsePoint**](#function-addusepoint) () <br> |
|   | [**BakedMesh**](#function-bakedmesh) () <br> |
|  void | [**Destroy**](#function-destroy) () <br> |
|  SR\_NODISCARD uint32\_t | [**GetCountIndices**](#function-getcountindices) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetCountVertices**](#function-getcountvertices) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetIBO**](#function-getibo) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetMeshIndex**](#function-getmeshindex) () noexcept const<br> |
|  SR\_NODISCARD [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) \* | [**GetPipeline**](#function-getpipeline) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* | [**GetRawMesh**](#function-getrawmesh) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetUsages**](#function-getusages) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetVBO**](#function-getvbo) () noexcept const<br> |
|  void | [**RemoveUsePoint**](#function-removeusepoint) () <br> |
|   | [**~BakedMesh**](#function-bakedmesh) () override<br> |


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


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  Ptr | [**Bake**](#function-bake-12) ([**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) \* pPipeline, std::string\_view path, uint32\_t index, Vertices::VertexType vertexType) <br> |
|  Ptr | [**Bake**](#function-bake-22) ([**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) \* pPipeline, [**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, uint32\_t index, Vertices::VertexType vertexType) <br> |


## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |




















## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |
























































## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_NS::Memory::BakedMesh::Ptr =  SR_HTYPES_NS::SharedPtr<BakedMesh>;
```




<hr>
## Public Functions Documentation




### function AddUsePoint 

```C++
inline void SR_GRAPH_NS::Memory::BakedMesh::AddUsePoint () 
```




<hr>



### function BakedMesh 

```C++
inline SR_GRAPH_NS::Memory::BakedMesh::BakedMesh () 
```




<hr>



### function Destroy 

```C++
void SR_GRAPH_NS::Memory::BakedMesh::Destroy () 
```




<hr>



### function GetCountIndices 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::Memory::BakedMesh::GetCountIndices () noexcept const
```




<hr>



### function GetCountVertices 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::Memory::BakedMesh::GetCountVertices () noexcept const
```




<hr>



### function GetIBO 

```C++
inline SR_NODISCARD int32_t SR_GRAPH_NS::Memory::BakedMesh::GetIBO () noexcept const
```




<hr>



### function GetMeshIndex 

```C++
inline SR_NODISCARD uint64_t SR_GRAPH_NS::Memory::BakedMesh::GetMeshIndex () noexcept const
```




<hr>



### function GetPipeline 

```C++
inline SR_NODISCARD Pipeline * SR_GRAPH_NS::Memory::BakedMesh::GetPipeline () noexcept const
```




<hr>



### function GetRawMesh 

```C++
inline SR_NODISCARD SR_HTYPES_NS::RawMesh * SR_GRAPH_NS::Memory::BakedMesh::GetRawMesh () noexcept const
```




<hr>



### function GetUsages 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::Memory::BakedMesh::GetUsages () noexcept const
```




<hr>



### function GetVBO 

```C++
inline SR_NODISCARD int32_t SR_GRAPH_NS::Memory::BakedMesh::GetVBO () noexcept const
```




<hr>



### function RemoveUsePoint 

```C++
inline void SR_GRAPH_NS::Memory::BakedMesh::RemoveUsePoint () 
```




<hr>



### function ~BakedMesh 

```C++
SR_GRAPH_NS::Memory::BakedMesh::~BakedMesh () override
```




<hr>
## Public Static Functions Documentation




### function Bake [1/2]

```C++
static Ptr SR_GRAPH_NS::Memory::BakedMesh::Bake (
    Pipeline * pPipeline,
    std::string_view path,
    uint32_t index,
    Vertices::VertexType vertexType
) 
```




<hr>



### function Bake [2/2]

```C++
static Ptr SR_GRAPH_NS::Memory::BakedMesh::Bake (
    Pipeline * pPipeline,
    SR_HTYPES_NS::RawMesh * pRawMesh,
    uint32_t index,
    Vertices::VertexType vertexType
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Memory/MeshManager.h`

