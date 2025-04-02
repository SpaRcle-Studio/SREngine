

# Class SR\_GRAPH\_NS::AtlasBuilder



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**AtlasBuilder**](classSR__GRAPH__NS_1_1AtlasBuilder.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AtlasBuilder**](#function-atlasbuilder) ([**AtlasBuilderData**](structSR__GRAPH__NS_1_1AtlasBuilderData.md) data) <br> |
|  SR\_NODISCARD bool | [**Generate**](#function-generate) () <br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetLocation**](#function-getlocation) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::UVector2 | [**GetQuantity**](#function-getquantity) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::UVector2 | [**GetStep**](#function-getstep) () const<br> |
|  SR\_NODISCARD bool | [**IsInCache**](#function-isincache) () const<br> |
|  SR\_NODISCARD bool | [**Save**](#function-save) () const<br> |
|  SR\_NODISCARD bool | [**SaveConfig**](#function-saveconfig) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Functions Documentation




### function AtlasBuilder 

```C++
SR_GRAPH_NS::AtlasBuilder::AtlasBuilder (
    AtlasBuilderData data
) 
```




<hr>



### function Generate 

```C++
SR_NODISCARD bool SR_GRAPH_NS::AtlasBuilder::Generate () 
```




<hr>



### function GetLocation 

```C++
inline SR_NODISCARD SR_UTILS_NS::Path SR_GRAPH_NS::AtlasBuilder::GetLocation () const
```




<hr>



### function GetQuantity 

```C++
inline SR_NODISCARD SR_MATH_NS::UVector2 SR_GRAPH_NS::AtlasBuilder::GetQuantity () const
```




<hr>



### function GetStep 

```C++
inline SR_NODISCARD SR_MATH_NS::UVector2 SR_GRAPH_NS::AtlasBuilder::GetStep () const
```




<hr>



### function IsInCache 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::AtlasBuilder::IsInCache () const
```




<hr>



### function Save 

```C++
SR_NODISCARD bool SR_GRAPH_NS::AtlasBuilder::Save () const
```




<hr>



### function SaveConfig 

```C++
SR_NODISCARD bool SR_GRAPH_NS::AtlasBuilder::SaveConfig (
    const SR_UTILS_NS::Path & path
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Utils/AtlasBuilder.h`

