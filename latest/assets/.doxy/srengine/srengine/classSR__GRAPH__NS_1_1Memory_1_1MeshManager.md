

# Class SR\_GRAPH\_NS::Memory::MeshManager



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**MeshManager**](classSR__GRAPH__NS_1_1Memory_1_1MeshManager.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)














## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**FreeResult**](#enum-freeresult)  <br> |
| typedef std::unordered\_map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), [**MeshVidMemInfo**](classSR__GRAPH__NS_1_1Memory_1_1MeshVidMemInfo.md) &gt; | [**VideoResources**](#typedef-videoresources)  <br> |
| typedef std::optional&lt; VideoResources::iterator &gt; | [**VideoResourcesIter**](#typedef-videoresourcesiter)  <br> |
















































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD BakedMesh::Ptr | [**BakeMesh**](#function-bakemesh) ([**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) \* pPipeline, [**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, uint32\_t index, Vertices::VertexType vertexType) <br> |
|  int32\_t | [**CopyIfExists**](#function-copyifexists-12) (const std::string\_view & identifier, Vertices::VertexType vertexType) <br> |
|  int32\_t | [**CopyIfExists**](#function-copyifexists-22) (const std::string\_view & identifier) <br> |
|  FreeResult | [**Free**](#function-free) (int32\_t id) <br> |
|  bool | [**Register**](#function-register-12) (const std::string\_view & identifier, uint32\_t size, uint32\_t id, Vertices::VertexType vertexType) <br> |
|  bool | [**Register**](#function-register-22) (const std::string\_view & identifier, uint32\_t size, uint32\_t id) <br> |
|  uint32\_t | [**Size**](#function-size) (const std::string\_view & identifier) <br> |




## Public Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|   | [**~SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |




## Public Static Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySingleton**](classSR__UTILS__NS_1_1Singleton.md#function-destroysingleton) () <br> |
|  SR\_MAYBE\_UNUSED std::recursive\_mutex & | [**GetMutex**](classSR__UTILS__NS_1_1Singleton.md#function-getmutex) () noexcept<br> |
|  SR\_MAYBE\_UNUSED T & | [**Instance**](classSR__UTILS__NS_1_1Singleton.md#function-instance) () noexcept<br>_TODO: (Multi-threading) Refactor Singleton::Instance()._  |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](classSR__UTILS__NS_1_1Singleton.md#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-unlocksingleton) () noexcept<br> |


























## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |






























































## Protected Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|   | [**Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () <br> |
|   | [**~Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSingletonName**](classSR__UTILS__NS_1_1SingletonBase.md#function-getsingletonname) () noexcept const = 0<br> |
| virtual void | [**InitSingleton**](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton) () <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed) () const<br> |
| virtual void | [**OnSingletonDestroy**](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy) () <br> |
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |










## Public Types Documentation




### enum FreeResult 

```C++
enum SR_GRAPH_NS::Memory::MeshManager::FreeResult {
    Unknown,
    Freed,
    EndUse,
    NotFound,
    UnknownMem
};
```




<hr>



### typedef VideoResources 

```C++
typedef std::unordered_map<SR_UTILS_NS::StringAtom, MeshVidMemInfo> SR_GRAPH_NS::Memory::MeshManager::VideoResources;
```




<hr>



### typedef VideoResourcesIter 

```C++
typedef std::optional<VideoResources::iterator> SR_GRAPH_NS::Memory::MeshManager::VideoResourcesIter;
```




<hr>
## Public Functions Documentation




### function BakeMesh 

```C++
SR_NODISCARD BakedMesh::Ptr SR_GRAPH_NS::Memory::MeshManager::BakeMesh (
    Pipeline * pPipeline,
    SR_HTYPES_NS::RawMesh * pRawMesh,
    uint32_t index,
    Vertices::VertexType vertexType
) 
```




<hr>



### function CopyIfExists [1/2]

```C++
template<MeshMemoryType memType>
int32_t SR_GRAPH_NS::Memory::MeshManager::CopyIfExists (
    const std::string_view & identifier,
    Vertices::VertexType vertexType
) 
```




<hr>



### function CopyIfExists [2/2]

```C++
template<Vertices::VertexType vertexType, MeshMemoryType memType>
int32_t SR_GRAPH_NS::Memory::MeshManager::CopyIfExists (
    const std::string_view & identifier
) 
```




<hr>



### function Free 

```C++
template<MeshMemoryType memType>
FreeResult SR_GRAPH_NS::Memory::MeshManager::Free (
    int32_t id
) 
```




<hr>



### function Register [1/2]

```C++
template<MeshMemoryType memType>
bool SR_GRAPH_NS::Memory::MeshManager::Register (
    const std::string_view & identifier,
    uint32_t size,
    uint32_t id,
    Vertices::VertexType vertexType
) 
```




 


        

<hr>



### function Register [2/2]

```C++
template<Vertices::VertexType vertexType, MeshMemoryType memType>
bool SR_GRAPH_NS::Memory::MeshManager::Register (
    const std::string_view & identifier,
    uint32_t size,
    uint32_t id
) 
```




<hr>



### function Size 

```C++
template<Vertices::VertexType vertexType, MeshMemoryType memType>
uint32_t SR_GRAPH_NS::Memory::MeshManager::Size (
    const std::string_view & identifier
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Memory/MeshManager.h`

