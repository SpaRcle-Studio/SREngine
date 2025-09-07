

# Namespace SR\_GTYPES\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_GTYPES\_NS**](namespaceSR__GTYPES__NS.md)



[More...](#detailed-description)
















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Camera**](classSR__GTYPES__NS_1_1Camera.md) <br> |
| class | [**ComputeShader**](classSR__GTYPES__NS_1_1ComputeShader.md) <br> |
| class | [**DebugLine**](classSR__GTYPES__NS_1_1DebugLine.md) <br> |
| class | [**DebugWireframeMesh**](classSR__GTYPES__NS_1_1DebugWireframeMesh.md) <br> |
| class | [**Font**](classSR__GTYPES__NS_1_1Font.md) <br> |
| class | [**Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) <br> |
| class | [**IRenderComponent**](classSR__GTYPES__NS_1_1IRenderComponent.md) <br> |
| class | [**IndexedMesh**](classSR__GTYPES__NS_1_1IndexedMesh.md) <br> |
| class | [**Mesh**](classSR__GTYPES__NS_1_1Mesh.md) <br> |
| class | [**Mesh3D**](classSR__GTYPES__NS_1_1Mesh3D.md) <br> |
| class | [**ProceduralMesh**](classSR__GTYPES__NS_1_1ProceduralMesh.md) <br> |
| class | [**RenderTechniqueComponent**](classSR__GTYPES__NS_1_1RenderTechniqueComponent.md) <br> |
| class | [**RenderTexture**](classSR__GTYPES__NS_1_1RenderTexture.md) <br> |
| class | [**Shader**](classSR__GTYPES__NS_1_1Shader.md) <br> |
| class | [**SkinnedMesh**](classSR__GTYPES__NS_1_1SkinnedMesh.md) <br> |
| class | [**Skybox**](classSR__GTYPES__NS_1_1Skybox.md) <br> |
| class | [**Sprite**](classSR__GTYPES__NS_1_1Sprite.md) <br> |
| class | [**Text**](classSR__GTYPES__NS_1_1Text.md) <br> |
| class | [**Texture**](classSR__GTYPES__NS_1_1Texture.md) <br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  const std::vector&lt; uint32\_t &gt; | [**SR\_SPRITE\_INDICES**](#variable-sr_sprite_indices)   = `{ 0, 1, 2, 0, 2, 3 }`<br> |
|  const std::vector&lt; Vertices::UIVertex &gt; | [**SR\_SPRITE\_VERTICES**](#variable-sr_sprite_vertices)   = `/* multi line expression */`<br>_NOLINT._  |


## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr size\_t | [**SIZE\_OF\_MESH\_CLASS**](#variable-size_of_mesh_class)   = `sizeof([**Mesh**](classSR__GTYPES__NS_1_1Mesh.md))`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (CameraType, uint8\_t, Main, Offscreen, Editor, EditorPrefab) <br> |




























## Detailed Description



* Layer (Only render)
  * Priority (Only render)
    * [**Shader**](classSR__GTYPES__NS_1_1Shader.md) (Render/Update) OnShaderUse
      * VBO (Render/Update) OnBindVBO
        * [**Mesh**](classSR__GTYPES__NS_1_1Mesh.md)
        * [**Mesh**](classSR__GTYPES__NS_1_1Mesh.md) OnUnBingVBO OnShaderUnUse 












    
## Public Attributes Documentation




### variable SR\_SPRITE\_INDICES 

```C++
const std::vector<uint32_t> SR_GTYPES_NS::SR_SPRITE_INDICES;
```




<hr>



### variable SR\_SPRITE\_VERTICES 

_NOLINT._ 
```C++
const std::vector<Vertices::UIVertex> SR_GTYPES_NS::SR_SPRITE_VERTICES;
```




<hr>
## Public Static Attributes Documentation




### variable SIZE\_OF\_MESH\_CLASS 

```C++
constexpr size_t SR_GTYPES_NS::SIZE_OF_MESH_CLASS;
```




<hr>
## Public Functions Documentation




### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_GTYPES_NS::SR_ENUM_NS_CLASS_T (
    CameraType,
    uint8_t,
    Main,
    Offscreen,
    Editor,
    EditorPrefab
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/Engine.h`

