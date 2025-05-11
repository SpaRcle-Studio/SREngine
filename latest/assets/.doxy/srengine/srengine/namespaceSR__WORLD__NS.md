

# Namespace SR\_WORLD\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**CameraData**](classSR__WORLD__NS_1_1CameraData.md) <br> |
| class | [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) <br> |
| class | [**Observer**](classSR__WORLD__NS_1_1Observer.md) <br> |
| struct | [**Offset**](structSR__WORLD__NS_1_1Offset.md) <br> |
| class | [**Region**](classSR__WORLD__NS_1_1Region.md) <br> |
| class | [**Scene**](classSR__WORLD__NS_1_1Scene.md) <br> |
| class | [**SceneAllocator**](classSR__WORLD__NS_1_1SceneAllocator.md) <br> |
| class | [**SceneAssetLogic**](classSR__WORLD__NS_1_1SceneAssetLogic.md) <br> |
| class | [**SceneCubeChunkLogic**](classSR__WORLD__NS_1_1SceneCubeChunkLogic.md) <br> |
| class | [**SceneLogic**](classSR__WORLD__NS_1_1SceneLogic.md) <br> |
| class | [**ScenePrefabLogic**](classSR__WORLD__NS_1_1ScenePrefabLogic.md) <br> |
| class | [**SceneUpdater**](classSR__WORLD__NS_1_1SceneUpdater.md) <br> |
| struct | [**TensorKey**](structSR__WORLD__NS_1_1TensorKey.md) <br> |
| class | [**WorldGen**](classSR__WORLD__NS_1_1WorldGen.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::unordered\_map&lt; Math::IVector3, SR\_HTYPES\_NS::Marshal::Ptr &gt; | [**CachedChunks**](#typedef-cachedchunks)  <br> |
| typedef std::unordered\_map&lt; Math::IVector3, [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* &gt; | [**Chunks**](#typedef-chunks)  <br> |
| typedef std::list&lt; [**Region**](classSR__WORLD__NS_1_1Region.md) \* &gt; | [**Regions**](#typedef-regions)  <br> |
| typedef std::unordered\_map&lt; [**TensorKey**](structSR__WORLD__NS_1_1TensorKey.md), std::vector&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; SceneObject &gt; &gt; &gt; | [**Tensor**](#typedef-tensor)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_COMMON\_DLL\_API Math::Unit | [**AddOffset**](#function-addoffset) (const Math::Unit & value, const Math::Unit & offset) <br> |
|  SR\_COMMON\_DLL\_API Math::FVector3 | [**AddOffset**](#function-addoffset) (const Math::FVector3 & chunk, const Math::FVector3 & offset) <br> |
|  SR\_COMMON\_DLL\_API Math::IVector3 | [**AddOffset**](#function-addoffset) (const Math::IVector3 & chunk, const Math::IVector3 & offset) <br> |
|  SR\_COMMON\_DLL\_API Math::FVector3 | [**AddOffset**](#function-addoffset) (const Math::FVector3 & region, const Math::IVector3 & offset) <br> |
|  SR\_COMMON\_DLL\_API Math::IVector3 | [**MakeChunk**](#function-makechunk) (const Math::IVector3 & rawChunkPos, int32\_t width) <br> |




























## Public Types Documentation




### typedef CachedChunks 

```C++
typedef std::unordered_map<Math::IVector3, SR_HTYPES_NS::Marshal::Ptr> SR_WORLD_NS::CachedChunks;
```




<hr>



### typedef Chunks 

```C++
typedef std::unordered_map<Math::IVector3, Chunk*> SR_WORLD_NS::Chunks;
```




<hr>



### typedef Regions 

```C++
typedef std::list<Region*> SR_WORLD_NS::Regions;
```




<hr>



### typedef Tensor 

```C++
typedef std::unordered_map<TensorKey, std::vector<SR_HTYPES_NS::SharedPtr<SceneObject> > > SR_WORLD_NS::Tensor;
```




<hr>
## Public Functions Documentation




### function AddOffset 

```C++
SR_COMMON_DLL_API Math::Unit SR_WORLD_NS::AddOffset (
    const Math::Unit & value,
    const Math::Unit & offset
) 
```




<hr>



### function AddOffset 

```C++
SR_COMMON_DLL_API Math::FVector3 SR_WORLD_NS::AddOffset (
    const Math::FVector3 & chunk,
    const Math::FVector3 & offset
) 
```




<hr>



### function AddOffset 

```C++
SR_COMMON_DLL_API Math::IVector3 SR_WORLD_NS::AddOffset (
    const Math::IVector3 & chunk,
    const Math::IVector3 & offset
) 
```




<hr>



### function AddOffset 

```C++
SR_COMMON_DLL_API Math::FVector3 SR_WORLD_NS::AddOffset (
    const Math::FVector3 & region,
    const Math::IVector3 & offset
) 
```




<hr>



### function MakeChunk 

```C++
SR_COMMON_DLL_API Math::IVector3 SR_WORLD_NS::MakeChunk (
    const Math::IVector3 & rawChunkPos,
    int32_t width
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/Engine.h`

