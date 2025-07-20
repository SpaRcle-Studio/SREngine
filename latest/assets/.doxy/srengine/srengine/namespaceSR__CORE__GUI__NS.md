

# Namespace SR\_CORE\_GUI\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_CORE\_GUI\_NS**](namespaceSR__CORE__GUI__NS.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**About**](classSR__CORE__GUI__NS_1_1About.md) <br> |
| class | [**AnimatorEditor**](classSR__CORE__GUI__NS_1_1AnimatorEditor.md) <br> |
| class | [**AssetInspector**](classSR__CORE__GUI__NS_1_1AssetInspector.md) <br> |
| class | [**BehaviourNamePropertyDrawer**](classSR__CORE__GUI__NS_1_1BehaviourNamePropertyDrawer.md) <br> |
| class | [**BehaviourPropertyDrawer**](classSR__CORE__GUI__NS_1_1BehaviourPropertyDrawer.md) <br> |
| class | [**BitMapPropertyDrawer**](classSR__CORE__GUI__NS_1_1BitMapPropertyDrawer.md) <br> |
| class | [**BoolPropertyDrawer**](classSR__CORE__GUI__NS_1_1BoolPropertyDrawer.md) <br> |
| struct | [**DrawPropertyContext**](structSR__CORE__GUI__NS_1_1DrawPropertyContext.md) <br> |
| class | [**EditorCamera**](classSR__CORE__GUI__NS_1_1EditorCamera.md) <br> |
| class | [**EditorGUI**](classSR__CORE__GUI__NS_1_1EditorGUI.md) <br> |
| class | [**EditorGizmo**](classSR__CORE__GUI__NS_1_1EditorGizmo.md) <br> |
| class | [**EngineSettings**](classSR__CORE__GUI__NS_1_1EngineSettings.md) <br> |
| class | [**EntityRefPropertyDrawer**](classSR__CORE__GUI__NS_1_1EntityRefPropertyDrawer.md) <br> |
| class | [**EnumPropertyDrawer**](classSR__CORE__GUI__NS_1_1EnumPropertyDrawer.md) <br> |
| class | [**Hierarchy**](classSR__CORE__GUI__NS_1_1Hierarchy.md) <br> |
| class | [**Inspector**](classSR__CORE__GUI__NS_1_1Inspector.md) <br> |
| class | [**MarginPropertyDrawer**](classSR__CORE__GUI__NS_1_1MarginPropertyDrawer.md) <br> |
| class | [**MaterialDataPropertyDrawer**](classSR__CORE__GUI__NS_1_1MaterialDataPropertyDrawer.md) <br> |
| class | [**MaterialEditor**](classSR__CORE__GUI__NS_1_1MaterialEditor.md) <br> |
| class | [**MaterialPropertyDrawer**](classSR__CORE__GUI__NS_1_1MaterialPropertyDrawer.md) <br> |
| class | [**MathSizePropertyDrawer**](classSR__CORE__GUI__NS_1_1MathSizePropertyDrawer.md) <br> |
| class | [**MathVectorPropertyDrawer**](classSR__CORE__GUI__NS_1_1MathVectorPropertyDrawer.md) <br> |
| class | [**NumericPropertyDrawer**](classSR__CORE__GUI__NS_1_1NumericPropertyDrawer.md) <br> |
| class | [**ObjectPropertyDrawer**](classSR__CORE__GUI__NS_1_1ObjectPropertyDrawer.md) <br> |
| class | [**PathPropertyDrawer**](classSR__CORE__GUI__NS_1_1PathPropertyDrawer.md) <br> |
| class | [**PointerPropertyDrawer**](classSR__CORE__GUI__NS_1_1PointerPropertyDrawer.md) <br> |
| class | [**PropertyDrawerBase**](classSR__CORE__GUI__NS_1_1PropertyDrawerBase.md) <br> |
| struct | [**PropertyDrawerContext**](structSR__CORE__GUI__NS_1_1PropertyDrawerContext.md) <br> |
| struct | [**PropertyDrawerFeedback**](structSR__CORE__GUI__NS_1_1PropertyDrawerFeedback.md) <br> |
| class | [**RectPropertyDrawer**](classSR__CORE__GUI__NS_1_1RectPropertyDrawer.md) <br> |
| class | [**RenderTechniqueEditor**](classSR__CORE__GUI__NS_1_1RenderTechniqueEditor.md) <br> |
| class | [**SceneRunner**](classSR__CORE__GUI__NS_1_1SceneRunner.md) <br> |
| class | [**SceneTools**](classSR__CORE__GUI__NS_1_1SceneTools.md) <br> |
| class | [**SceneViewer**](classSR__CORE__GUI__NS_1_1SceneViewer.md) <br> |
| class | [**SoundDebug**](classSR__CORE__GUI__NS_1_1SoundDebug.md) <br> |
| class | [**StringPropertyDrawer**](classSR__CORE__GUI__NS_1_1StringPropertyDrawer.md) <br> |
| class | [**VectorPropertyDrawer**](classSR__CORE__GUI__NS_1_1VectorPropertyDrawer.md) <br> |
| class | [**WorldEdit**](classSR__CORE__GUI__NS_1_1WorldEdit.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED bool | [**DragDropTargetEntityRef**](#function-dragdroptargetentityref) ([**EditorGUI**](classSR__CORE__GUI__NS_1_1EditorGUI.md) \* pContext, [**SR\_UTILS\_NS::EntityRefOld**](classSR__UTILS__NS_1_1EntityRefOld.md) & entityRef, const char \* id, float\_t width=300.f) <br> |
|  SR\_MAYBE\_UNUSED [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetValueInspector**](#function-getvalueinspector) (const [**SR\_UTILS\_NS::Reflection::Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & value) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (EditorSceneViewMode, uint8\_t, FreeAspect, WindowSize) <br> |




























## Public Functions Documentation




### function DragDropTargetEntityRef 

```C++
SR_MAYBE_UNUSED bool SR_CORE_GUI_NS::DragDropTargetEntityRef (
    EditorGUI * pContext,
    SR_UTILS_NS::EntityRefOld & entityRef,
    const char * id,
    float_t width=300.f
) 
```




<hr>



### function GetValueInspector 

```C++
SR_MAYBE_UNUSED SR_UTILS_NS::StringAtom SR_CORE_GUI_NS::GetValueInspector (
    const SR_UTILS_NS::Reflection::Value & value
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_CORE_GUI_NS::SR_ENUM_NS_CLASS_T (
    EditorSceneViewMode,
    uint8_t,
    FreeAspect,
    WindowSize
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/Engine.h`

