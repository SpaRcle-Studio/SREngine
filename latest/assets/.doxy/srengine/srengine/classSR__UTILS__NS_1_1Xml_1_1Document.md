

# Class SR\_UTILS\_NS::Xml::Document



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Xml**](namespaceSR__UTILS__NS_1_1Xml.md) **>** [**Document**](classSR__UTILS__NS_1_1Xml_1_1Document.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**AppendChild**](#function-appendchild) (const std::string & name) <br> |
|   | [**Document**](#function-document-12) () <br> |
|   | [**Document**](#function-document-22) ([**Document**](classSR__UTILS__NS_1_1Xml_1_1Document.md) && document) noexcept<br> |
|  SR\_NODISCARD [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**DocumentElement**](#function-documentelement) () const<br> |
|  SR\_NODISCARD std::string | [**Dump**](#function-dump) () const<br>_NOLINT._  |
|  SR\_NODISCARD [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**Root**](#function-root) () const<br> |
|  bool | [**Save**](#function-save) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |
|  SR\_NODISCARD [**Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**TryRoot**](#function-tryroot) () const<br> |
|  SR\_NODISCARD bool | [**Valid**](#function-valid) () const<br> |
|   | [**operator bool**](#function-operator-bool) () const<br> |
|  [**Document**](classSR__UTILS__NS_1_1Xml_1_1Document.md) & | [**operator=**](#function-operator) ([**Document**](classSR__UTILS__NS_1_1Xml_1_1Document.md) && document) noexcept<br> |
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
|  [**Document**](classSR__UTILS__NS_1_1Xml_1_1Document.md) | [**Empty**](#function-empty) () <br> |
|  int32\_t | [**GetLastError**](#function-getlasterror) () <br> |
|  [**Document**](classSR__UTILS__NS_1_1Xml_1_1Document.md) | [**Load**](#function-load) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  [**Document**](classSR__UTILS__NS_1_1Xml_1_1Document.md) | [**New**](#function-new) () <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function AppendChild 

```C++
Xml::Node SR_UTILS_NS::Xml::Document::AppendChild (
    const std::string & name
) 
```




<hr>



### function Document [1/2]

```C++
SR_UTILS_NS::Xml::Document::Document () 
```




<hr>



### function Document [2/2]

```C++
SR_UTILS_NS::Xml::Document::Document (
    Document && document
) noexcept
```




<hr>



### function DocumentElement 

```C++
SR_NODISCARD Node SR_UTILS_NS::Xml::Document::DocumentElement () const
```




<hr>



### function Dump 

_NOLINT._ 
```C++
SR_NODISCARD std::string SR_UTILS_NS::Xml::Document::Dump () const
```




<hr>



### function Root 

```C++
SR_NODISCARD Node SR_UTILS_NS::Xml::Document::Root () const
```




<hr>



### function Save 

```C++
bool SR_UTILS_NS::Xml::Document::Save (
    const SR_UTILS_NS::Path & path
) const
```




<hr>



### function TryRoot 

```C++
SR_NODISCARD Node SR_UTILS_NS::Xml::Document::TryRoot () const
```




<hr>



### function Valid 

```C++
SR_NODISCARD bool SR_UTILS_NS::Xml::Document::Valid () const
```




<hr>



### function operator bool 

```C++
SR_UTILS_NS::Xml::Document::operator bool () const
```




<hr>



### function operator= 

```C++
Document & SR_UTILS_NS::Xml::Document::operator= (
    Document && document
) noexcept
```




<hr>



### function ~Document 

```C++
SR_UTILS_NS::Xml::Document::~Document () override
```




<hr>
## Public Static Functions Documentation




### function Empty 

```C++
static Document SR_UTILS_NS::Xml::Document::Empty () 
```




<hr>



### function GetLastError 

```C++
static int32_t SR_UTILS_NS::Xml::Document::GetLastError () 
```




<hr>



### function Load 

```C++
static Document SR_UTILS_NS::Xml::Document::Load (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function New 

```C++
static Document SR_UTILS_NS::Xml::Document::New () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Resources/Xml.h`

