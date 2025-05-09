

# Class SR\_GRAPH\_GUI\_NS::Theme



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_GUI\_NS**](namespaceSR__GRAPH__GUI__NS.md) **>** [**Theme**](classSR__GRAPH__GUI__NS_1_1Theme.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Apply**](#function-apply) (ImGuiStyle & style) const<br> |
|  bool | [**Save**](#function-save-12) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**SetBool**](#function-setbool) (const std::string & id, bool value) <br> |
|  void | [**SetColor**](#function-setcolor) (const std::string & id, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  void | [**SetFloat**](#function-setfloat) (const std::string & id, float\_t value) <br> |
|  void | [**SetSize**](#function-setsize) (const std::string & id, const SR\_MATH\_NS::FVector2 & size) <br> |
|   | [**~Theme**](#function-theme) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FVector2 | [**ImVec2ToFVector2**](#function-imvec2tofvector2) (ImVec2 imVec2) <br> |
|  [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**ImVec4ToColor**](#function-imvec4tocolor) (ImVec4 imVec4) <br> |
|  [**Theme**](classSR__GRAPH__GUI__NS_1_1Theme.md) \* | [**Load**](#function-load) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  bool | [**Save**](#function-save-22) (const std::string & path, const ImGuiStyle & style) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function Apply 

```C++
bool SR_GRAPH_GUI_NS::Theme::Apply (
    ImGuiStyle & style
) const
```




<hr>



### function Save [1/2]

```C++
bool SR_GRAPH_GUI_NS::Theme::Save (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function SetBool 

```C++
void SR_GRAPH_GUI_NS::Theme::SetBool (
    const std::string & id,
    bool value
) 
```




<hr>



### function SetColor 

```C++
void SR_GRAPH_GUI_NS::Theme::SetColor (
    const std::string & id,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function SetFloat 

```C++
void SR_GRAPH_GUI_NS::Theme::SetFloat (
    const std::string & id,
    float_t value
) 
```




<hr>



### function SetSize 

```C++
void SR_GRAPH_GUI_NS::Theme::SetSize (
    const std::string & id,
    const SR_MATH_NS::FVector2 & size
) 
```




<hr>



### function ~Theme 

```C++
SR_GRAPH_GUI_NS::Theme::~Theme () override
```




<hr>
## Public Static Functions Documentation




### function ImVec2ToFVector2 

```C++
static SR_MATH_NS::FVector2 SR_GRAPH_GUI_NS::Theme::ImVec2ToFVector2 (
    ImVec2 imVec2
) 
```




<hr>



### function ImVec4ToColor 

```C++
static SR_MATH_NS::FColor SR_GRAPH_GUI_NS::Theme::ImVec4ToColor (
    ImVec4 imVec4
) 
```




<hr>



### function Load 

```C++
static Theme * SR_GRAPH_GUI_NS::Theme::Load (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function Save [2/2]

```C++
static bool SR_GRAPH_GUI_NS::Theme::Save (
    const std::string & path,
    const ImGuiStyle & style
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/Editor/Theme.h`

