

# Class SR\_UTILS\_NS::Yaml::Document



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Yaml**](namespaceSR__UTILS__NS_1_1Yaml.md) **>** [**Document**](classSR__UTILS__NS_1_1Yaml_1_1Document.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**Node**](classSR__UTILS__NS_1_1Yaml_1_1Node.md) | [**AppendChild**](#function-appendchild) (const std::string\_view & name) <br> |
|   | [**Document**](#function-document-12) () = default<br> |
|   | [**Document**](#function-document-22) ([**Document**](classSR__UTILS__NS_1_1Yaml_1_1Document.md) && document) noexcept<br> |
|  SR\_NODISCARD std::string | [**Dump**](#function-dump) () const<br> |
|  SR\_NODISCARD [**Node**](classSR__UTILS__NS_1_1Yaml_1_1Node.md) | [**GetRoot**](#function-getroot-12) () const<br> |
|  SR\_NODISCARD [**Node**](classSR__UTILS__NS_1_1Yaml_1_1Node.md) | [**GetRoot**](#function-getroot-22) () <br> |
|  SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () const<br> |
|  SR\_NODISCARD bool | [**Save**](#function-save) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |
|   | [**operator bool**](#function-operator-bool) () const<br> |
|  [**Document**](classSR__UTILS__NS_1_1Yaml_1_1Document.md) & | [**operator=**](#function-operator) ([**Document**](classSR__UTILS__NS_1_1Yaml_1_1Document.md) && document) noexcept<br> |
|   | [**~Document**](#function-document) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Document**](classSR__UTILS__NS_1_1Yaml_1_1Document.md) | [**Empty**](#function-empty) () <br> |
|  [**Document**](classSR__UTILS__NS_1_1Yaml_1_1Document.md) | [**Load**](#function-load) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  [**Document**](classSR__UTILS__NS_1_1Yaml_1_1Document.md) | [**New**](#function-new) () <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function AppendChild 

```C++
Node SR_UTILS_NS::Yaml::Document::AppendChild (
    const std::string_view & name
) 
```




<hr>



### function Document [1/2]

```C++
SR_UTILS_NS::Yaml::Document::Document () = default
```




<hr>



### function Document [2/2]

```C++
SR_UTILS_NS::Yaml::Document::Document (
    Document && document
) noexcept
```




<hr>



### function Dump 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Yaml::Document::Dump () const
```




<hr>



### function GetRoot [1/2]

```C++
SR_NODISCARD Node SR_UTILS_NS::Yaml::Document::GetRoot () const
```




<hr>



### function GetRoot [2/2]

```C++
SR_NODISCARD Node SR_UTILS_NS::Yaml::Document::GetRoot () 
```




<hr>



### function IsValid 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Yaml::Document::IsValid () const
```




<hr>



### function Save 

```C++
SR_NODISCARD bool SR_UTILS_NS::Yaml::Document::Save (
    const SR_UTILS_NS::Path & path
) const
```




<hr>



### function operator bool 

```C++
inline explicit SR_UTILS_NS::Yaml::Document::operator bool () const
```




<hr>



### function operator= 

```C++
Document & SR_UTILS_NS::Yaml::Document::operator= (
    Document && document
) noexcept
```




<hr>



### function ~Document 

```C++
SR_UTILS_NS::Yaml::Document::~Document () override
```




<hr>
## Public Static Functions Documentation




### function Empty 

```C++
static Document SR_UTILS_NS::Yaml::Document::Empty () 
```




<hr>



### function Load 

```C++
static Document SR_UTILS_NS::Yaml::Document::Load (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function New 

```C++
static Document SR_UTILS_NS::Yaml::Document::New () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Resources/Yaml.h`

