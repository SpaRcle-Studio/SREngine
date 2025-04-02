

# Class SR\_CORE\_GUI\_NS::EditorGUI



[**ClassList**](annotated.md) **>** [**SR\_CORE\_GUI\_NS**](namespaceSR__CORE__GUI__NS.md) **>** [**EditorGUI**](classSR__CORE__GUI__NS_1_1EditorGUI.md)








Inherits the following classes: SR_GRAPH_GUI_NS::WidgetManager


































## Public Functions

| Type | Name |
| ---: | :--- |
|  T & | [**AddWidget**](#function-addwidget) (T \* pWidget) <br> |
|  SR\_DEPRECATED void | [**AddWindow**](#function-addwindow) (T \* widget) <br> |
|  void | [**CacheScenePath**](#function-cachescenepath) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & scenePath) <br> |
|  void | [**CloseAllWidgets**](#function-closeallwidgets) () <br> |
|  void | [**DeInit**](#function-deinit) () <br> |
|  void | [**Draw**](#function-draw) () override<br> |
|   | [**EditorGUI**](#function-editorgui) (const EnginePtr & pEngine) <br> |
|  void | [**Enable**](#function-enable) (bool value) <br> |
|  SR\_NODISCARD bool | [**Enabled**](#function-enabled) () const<br> |
|  void | [**FixedUpdate**](#function-fixedupdate) () <br> |
|  SR\_NODISCARD const EnginePtr & | [**GetEngine**](#function-getengine) () const<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Texture**](classSR__GTYPES__NS_1_1Texture.md) \* | [**GetIcon**](#function-geticon) (EditorIcon icon) const<br> |
|  SR\_NODISCARD void \* | [**GetIconDescriptor**](#function-geticondescriptor) (EditorIcon icon) const<br> |
|  SR\_NODISCARD [**SR\_GRAPH\_GUI\_NS::Widget**](classSR__GRAPH__GUI__NS_1_1Widget.md) \* | [**GetWidget**](#function-getwidget-12) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  T \* | [**GetWidget**](#function-getwidget-22) () <br> |
|  SR\_DEPRECATED T \* | [**GetWindow**](#function-getwindow) () <br> |
|  bool | [**Init**](#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsDockingEnabled**](#function-isdockingenabled) () const<br> |
|  SR\_NODISCARD bool | [**IsInitialized**](#function-isinitialized) () const<br> |
|  bool | [**LoadSceneFromCachedPath**](#function-loadscenefromcachedpath) () <br> |
|  T \* | [**OpenWidget**](#function-openwidget) () <br> |
|  void | [**ReloadWindows**](#function-reloadwindows) () <br> |
|  void | [**ResetToDefault**](#function-resettodefault) () <br> |
|  void | [**Save**](#function-save) () <br> |
|  void | [**SetDockingEnabled**](#function-setdockingenabled) (bool value) <br> |
|  void | [**Update**](#function-update) (float\_t dt) <br> |
|   | [**~EditorGUI**](#function-editorgui) () override<br> |




























## Public Functions Documentation




### function AddWidget 

```C++
template<typename T>
inline T & SR_CORE_GUI_NS::EditorGUI::AddWidget (
    T * pWidget
) 
```




<hr>



### function AddWindow 

```C++
template<typename T>
inline SR_DEPRECATED void SR_CORE_GUI_NS::EditorGUI::AddWindow (
    T * widget
) 
```




<hr>



### function CacheScenePath 

```C++
void SR_CORE_GUI_NS::EditorGUI::CacheScenePath (
    const SR_UTILS_NS::Path & scenePath
) 
```




<hr>



### function CloseAllWidgets 

```C++
void SR_CORE_GUI_NS::EditorGUI::CloseAllWidgets () 
```




<hr>



### function DeInit 

```C++
void SR_CORE_GUI_NS::EditorGUI::DeInit () 
```




<hr>



### function Draw 

```C++
void SR_CORE_GUI_NS::EditorGUI::Draw () override
```




<hr>



### function EditorGUI 

```C++
explicit SR_CORE_GUI_NS::EditorGUI::EditorGUI (
    const EnginePtr & pEngine
) 
```




<hr>



### function Enable 

```C++
void SR_CORE_GUI_NS::EditorGUI::Enable (
    bool value
) 
```




<hr>



### function Enabled 

```C++
inline SR_NODISCARD bool SR_CORE_GUI_NS::EditorGUI::Enabled () const
```




<hr>



### function FixedUpdate 

```C++
void SR_CORE_GUI_NS::EditorGUI::FixedUpdate () 
```




<hr>



### function GetEngine 

```C++
inline SR_NODISCARD const EnginePtr & SR_CORE_GUI_NS::EditorGUI::GetEngine () const
```




<hr>



### function GetIcon 

```C++
SR_NODISCARD SR_GTYPES_NS::Texture * SR_CORE_GUI_NS::EditorGUI::GetIcon (
    EditorIcon icon
) const
```




<hr>



### function GetIconDescriptor 

```C++
SR_NODISCARD void * SR_CORE_GUI_NS::EditorGUI::GetIconDescriptor (
    EditorIcon icon
) const
```




<hr>



### function GetWidget [1/2]

```C++
SR_NODISCARD SR_GRAPH_GUI_NS::Widget * SR_CORE_GUI_NS::EditorGUI::GetWidget (
    const SR_UTILS_NS::StringAtom & name
) const
```




<hr>



### function GetWidget [2/2]

```C++
template<typename T>
inline T * SR_CORE_GUI_NS::EditorGUI::GetWidget () 
```




<hr>



### function GetWindow 

```C++
template<typename T>
inline SR_DEPRECATED T * SR_CORE_GUI_NS::EditorGUI::GetWindow () 
```




<hr>



### function Init 

```C++
bool SR_CORE_GUI_NS::EditorGUI::Init () 
```




<hr>



### function IsDockingEnabled 

```C++
inline SR_NODISCARD bool SR_CORE_GUI_NS::EditorGUI::IsDockingEnabled () const
```




<hr>



### function IsInitialized 

```C++
inline SR_NODISCARD bool SR_CORE_GUI_NS::EditorGUI::IsInitialized () const
```




<hr>



### function LoadSceneFromCachedPath 

```C++
bool SR_CORE_GUI_NS::EditorGUI::LoadSceneFromCachedPath () 
```




<hr>



### function OpenWidget 

```C++
template<typename T>
inline T * SR_CORE_GUI_NS::EditorGUI::OpenWidget () 
```




<hr>



### function ReloadWindows 

```C++
void SR_CORE_GUI_NS::EditorGUI::ReloadWindows () 
```




<hr>



### function ResetToDefault 

```C++
void SR_CORE_GUI_NS::EditorGUI::ResetToDefault () 
```




<hr>



### function Save 

```C++
void SR_CORE_GUI_NS::EditorGUI::Save () 
```




<hr>



### function SetDockingEnabled 

```C++
inline void SR_CORE_GUI_NS::EditorGUI::SetDockingEnabled (
    bool value
) 
```




<hr>



### function Update 

```C++
void SR_CORE_GUI_NS::EditorGUI::Update (
    float_t dt
) 
```




<hr>



### function ~EditorGUI 

```C++
SR_CORE_GUI_NS::EditorGUI::~EditorGUI () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/inc/Core/GUI/EditorGUI.h`

