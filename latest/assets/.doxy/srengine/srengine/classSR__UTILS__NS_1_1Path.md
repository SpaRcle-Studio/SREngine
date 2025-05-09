

# Class SR\_UTILS\_NS::Path



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Path**](classSR__UTILS__NS_1_1Path.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Type**](#enum-type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD const char \* | [**CStr**](#function-cstr) () const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**Concat**](#function-concat) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**ConcatExt**](#function-concatext-14) (const std::string & ext) const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**ConcatExt**](#function-concatext-24) (const std::string\_view & ext) const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**ConcatExt**](#function-concatext-34) (const char \* ext) const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**ConcatExt**](#function-concatext-44) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) ext) const<br> |
|  SR\_NODISCARD bool | [**Contains**](#function-contains) (const std::string & str) const<br> |
|  SR\_NODISCARD std::string | [**ConvertToFileName**](#function-converttofilename) () const<br> |
|  SR\_NODISCARD bool | [**Copy**](#function-copy) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & destination) const<br> |
|  bool | [**Create**](#function-create) () const<br> |
|  bool | [**CreateIfNotExists**](#function-createifnotexists) () const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**EmplaceFront**](#function-emplacefront) (const std::string & str) const<br> |
|  SR\_NODISCARD bool | [**Exists**](#function-exists-12) () const<br> |
|  SR\_NODISCARD bool | [**Exists**](#function-exists-22) (Type type) const<br> |
|  SR\_NODISCARD std::list&lt; [**Path**](classSR__UTILS__NS_1_1Path.md) &gt; | [**GetAll**](#function-getall) () const<br> |
|  SR\_NODISCARD std::string | [**GetBaseName**](#function-getbasename) () const<br> |
|  SR\_NODISCARD std::string | [**GetBaseNameAndExt**](#function-getbasenameandext) () const<br> |
|  SR\_NODISCARD std::string\_view | [**GetBaseNameView**](#function-getbasenameview) () const<br> |
|  SR\_NODISCARD std::string | [**GetExtension**](#function-getextension) () const<br> |
|  SR\_NODISCARD std::string\_view | [**GetExtensionView**](#function-getextensionview) () const<br> |
|  SR\_NODISCARD uint64\_t | [**GetFileHash**](#function-getfilehash) () const<br> |
|  SR\_NODISCARD std::list&lt; [**Path**](classSR__UTILS__NS_1_1Path.md) &gt; | [**GetFiles**](#function-getfiles) () const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetFolder**](#function-getfolder) () const<br> |
|  SR\_NODISCARD uint64\_t | [**GetFolderHash**](#function-getfolderhash) (uint64\_t deep=SR\_UINT64\_MAX) const<br> |
|  SR\_NODISCARD std::list&lt; [**Path**](classSR__UTILS__NS_1_1Path.md) &gt; | [**GetFolders**](#function-getfolders) () const<br> |
|  SR\_NODISCARD size\_t | [**GetHash**](#function-gethash) () const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetPrevious**](#function-getprevious) () const<br> |
|  SR\_NODISCARD Type | [**GetType**](#function-gettype) () const<br> |
|  SR\_NODISCARD std::string | [**GetWithoutExtension**](#function-getwithoutextension) () const<br> |
|  SR\_NODISCARD bool | [**IsAbs**](#function-isabs) () const<br> |
|  SR\_NODISCARD bool | [**IsDir**](#function-isdir) () const<br> |
|  SR\_NODISCARD bool | [**IsDirEmpty**](#function-isdirempty) () const<br> |
|  SR\_NODISCARD bool | [**IsEmpty**](#function-isempty) () const<br> |
|  SR\_NODISCARD bool | [**IsFile**](#function-isfile) () const<br> |
|  SR\_NODISCARD bool | [**IsHidden**](#function-ishidden) () const<br> |
|  SR\_NODISCARD bool | [**IsSubPath**](#function-issubpath) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & subPath) const<br> |
|  void | [**Load**](#function-load) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |
|  SR\_DEPRECATED bool | [**Make**](#function-make) (Type type=Type::Undefined) const<br> |
|   | [**Path**](#function-path-18) () <br> |
|   | [**Path**](#function-path-28) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|   | [**Path**](#function-path-38) (const char \* path) <br> |
|   | [**Path**](#function-path-48) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) stringAtom) <br> |
|   | [**Path**](#function-path-58) (std::string path) <br> |
|   | [**Path**](#function-path-68) (std::string\_view path) <br> |
|   | [**Path**](#function-path-78) (std::wstring path) <br> |
|   | [**Path**](#function-path-88) ([**Path**](classSR__UTILS__NS_1_1Path.md) && path) noexcept<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**RemoveSubPath**](#function-removesubpath) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & subPath) const<br> |
|  void | [**Save**](#function-save) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**SelfRemoveSubPath**](#function-selfremovesubpath) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & subPath) const<br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |
|  SR\_NODISCARD std::string \* | [**ToStringPtr**](#function-tostringptr) () <br> |
|  SR\_NODISCARD const std::string & | [**ToStringRef**](#function-tostringref) () const<br> |
|  SR\_NODISCARD std::string\_view | [**ToStringView**](#function-tostringview) () const<br> |
|  SR\_NODISCARD std::wstring | [**ToUnicodeString**](#function-tounicodestring) () const<br> |
|  SR\_NODISCARD std::wstring | [**ToWinApiPath**](#function-towinapipath) () const<br> |
|  SR\_NODISCARD bool | [**Valid**](#function-valid) () const<br> |
|  SR\_NODISCARD std::string\_view | [**View**](#function-view) () const<br> |
|  SR\_NODISCARD const char \* | [**c\_str**](#function-c_str) () const<br> |
|  SR\_NODISCARD bool | [**empty**](#function-empty) () const<br> |
|   | [**string &**](#function-string-&) () <br> |
|  bool | [**operator&lt;**](#function-operator) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) noexcept const<br> |
|  [**Path**](classSR__UTILS__NS_1_1Path.md) & | [**operator=**](#function-operator_1) ([**Path**](classSR__UTILS__NS_1_1Path.md) && path) noexcept<br> |
|  [**Path**](classSR__UTILS__NS_1_1Path.md) & | [**operator=**](#function-operator_2) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  bool | [**operator==**](#function-operator_3) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) noexcept const<br> |
|  bool | [**operator&gt;**](#function-operator_4) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) noexcept const<br> |
|  char | [**operator[]**](#function-operator_5) (size\_t index) noexcept const<br> |
|  char & | [**operator[]**](#function-operator_6) (size\_t index) noexcept<br> |
|   | [**~Path**](#function-path) () <br> |




























## Public Types Documentation




### enum Type 

```C++
enum SR_UTILS_NS::Path::Type {
    Undefined,
    File,
    Folder
};
```




<hr>
## Public Functions Documentation




### function CStr 

```C++
SR_NODISCARD const char * SR_UTILS_NS::Path::CStr () const
```




<hr>



### function Concat 

```C++
SR_NODISCARD Path SR_UTILS_NS::Path::Concat (
    const Path & path
) const
```




<hr>



### function ConcatExt [1/4]

```C++
SR_NODISCARD Path SR_UTILS_NS::Path::ConcatExt (
    const std::string & ext
) const
```




<hr>



### function ConcatExt [2/4]

```C++
SR_NODISCARD Path SR_UTILS_NS::Path::ConcatExt (
    const std::string_view & ext
) const
```




<hr>



### function ConcatExt [3/4]

```C++
SR_NODISCARD Path SR_UTILS_NS::Path::ConcatExt (
    const char * ext
) const
```




<hr>



### function ConcatExt [4/4]

```C++
SR_NODISCARD Path SR_UTILS_NS::Path::ConcatExt (
    SR_UTILS_NS::StringAtom ext
) const
```




<hr>



### function Contains 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::Contains (
    const std::string & str
) const
```




<hr>



### function ConvertToFileName 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Path::ConvertToFileName () const
```




<hr>



### function Copy 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::Copy (
    const Path & destination
) const
```




<hr>



### function Create 

```C++
bool SR_UTILS_NS::Path::Create () const
```




<hr>



### function CreateIfNotExists 

```C++
bool SR_UTILS_NS::Path::CreateIfNotExists () const
```




<hr>



### function EmplaceFront 

```C++
SR_NODISCARD Path SR_UTILS_NS::Path::EmplaceFront (
    const std::string & str
) const
```




<hr>



### function Exists [1/2]

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::Exists () const
```




<hr>



### function Exists [2/2]

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::Exists (
    Type type
) const
```




<hr>



### function GetAll 

```C++
SR_NODISCARD std::list< Path > SR_UTILS_NS::Path::GetAll () const
```




<hr>



### function GetBaseName 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Path::GetBaseName () const
```




<hr>



### function GetBaseNameAndExt 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Path::GetBaseNameAndExt () const
```




<hr>



### function GetBaseNameView 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::Path::GetBaseNameView () const
```




<hr>



### function GetExtension 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Path::GetExtension () const
```




<hr>



### function GetExtensionView 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::Path::GetExtensionView () const
```




<hr>



### function GetFileHash 

```C++
SR_NODISCARD uint64_t SR_UTILS_NS::Path::GetFileHash () const
```




<hr>



### function GetFiles 

```C++
SR_NODISCARD std::list< Path > SR_UTILS_NS::Path::GetFiles () const
```




<hr>



### function GetFolder 

```C++
SR_NODISCARD Path SR_UTILS_NS::Path::GetFolder () const
```




<hr>



### function GetFolderHash 

```C++
SR_NODISCARD uint64_t SR_UTILS_NS::Path::GetFolderHash (
    uint64_t deep=SR_UINT64_MAX
) const
```




<hr>



### function GetFolders 

```C++
SR_NODISCARD std::list< Path > SR_UTILS_NS::Path::GetFolders () const
```




<hr>



### function GetHash 

```C++
SR_NODISCARD size_t SR_UTILS_NS::Path::GetHash () const
```




<hr>



### function GetPrevious 

```C++
SR_NODISCARD Path SR_UTILS_NS::Path::GetPrevious () const
```




<hr>



### function GetType 

```C++
SR_NODISCARD Type SR_UTILS_NS::Path::GetType () const
```




<hr>



### function GetWithoutExtension 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Path::GetWithoutExtension () const
```




<hr>



### function IsAbs 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::IsAbs () const
```




<hr>



### function IsDir 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::IsDir () const
```




<hr>



### function IsDirEmpty 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::IsDirEmpty () const
```




<hr>



### function IsEmpty 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::IsEmpty () const
```




<hr>



### function IsFile 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::IsFile () const
```




<hr>



### function IsHidden 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::IsHidden () const
```




<hr>



### function IsSubPath 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::IsSubPath (
    const Path & subPath
) const
```




<hr>



### function Load 

```C++
void SR_UTILS_NS::Path::Load (
    IDeserializer & deserializer,
    const SerializationId & id
) 
```




<hr>



### function Make 

```C++
SR_DEPRECATED bool SR_UTILS_NS::Path::Make (
    Type type=Type::Undefined
) const
```




<hr>



### function Path [1/8]

```C++
SR_UTILS_NS::Path::Path () 
```




<hr>



### function Path [2/8]

```C++
SR_UTILS_NS::Path::Path (
    const Path & path
) 
```




<hr>



### function Path [3/8]

```C++
SR_UTILS_NS::Path::Path (
    const char * path
) 
```




<hr>



### function Path [4/8]

```C++
SR_UTILS_NS::Path::Path (
    SR_UTILS_NS::StringAtom stringAtom
) 
```




<hr>



### function Path [5/8]

```C++
SR_UTILS_NS::Path::Path (
    std::string path
) 
```




<hr>



### function Path [6/8]

```C++
SR_UTILS_NS::Path::Path (
    std::string_view path
) 
```




<hr>



### function Path [7/8]

```C++
SR_UTILS_NS::Path::Path (
    std::wstring path
) 
```




<hr>



### function Path [8/8]

```C++
SR_UTILS_NS::Path::Path (
    Path && path
) noexcept
```




<hr>



### function RemoveSubPath 

```C++
SR_NODISCARD Path SR_UTILS_NS::Path::RemoveSubPath (
    const Path & subPath
) const
```




<hr>



### function Save 

```C++
void SR_UTILS_NS::Path::Save (
    ISerializer & serializer,
    const SerializationId & id
) const
```




<hr>



### function SelfRemoveSubPath 

```C++
SR_NODISCARD Path SR_UTILS_NS::Path::SelfRemoveSubPath (
    const Path & subPath
) const
```




<hr>



### function ToString 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Path::ToString () const
```




<hr>



### function ToStringPtr 

```C++
inline SR_NODISCARD std::string * SR_UTILS_NS::Path::ToStringPtr () 
```




<hr>



### function ToStringRef 

```C++
SR_NODISCARD const std::string & SR_UTILS_NS::Path::ToStringRef () const
```




<hr>



### function ToStringView 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::Path::ToStringView () const
```




<hr>



### function ToUnicodeString 

```C++
SR_NODISCARD std::wstring SR_UTILS_NS::Path::ToUnicodeString () const
```




<hr>



### function ToWinApiPath 

```C++
SR_NODISCARD std::wstring SR_UTILS_NS::Path::ToWinApiPath () const
```




<hr>



### function Valid 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::Valid () const
```




<hr>



### function View 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::Path::View () const
```




<hr>



### function c\_str 

```C++
SR_NODISCARD const char * SR_UTILS_NS::Path::c_str () const
```




<hr>



### function empty 

```C++
SR_NODISCARD bool SR_UTILS_NS::Path::empty () const
```




<hr>



### function string & 

```C++
SR_UTILS_NS::Path::string & () 
```




<hr>



### function operator&lt; 

```C++
bool SR_UTILS_NS::Path::operator< (
    const Path & path
) noexcept const
```




<hr>



### function operator= 

```C++
Path & SR_UTILS_NS::Path::operator= (
    Path && path
) noexcept
```




<hr>



### function operator= 

```C++
Path & SR_UTILS_NS::Path::operator= (
    const Path & path
) 
```



NOLINT 


        

<hr>



### function operator== 

```C++
bool SR_UTILS_NS::Path::operator== (
    const Path & path
) noexcept const
```




<hr>



### function operator&gt; 

```C++
bool SR_UTILS_NS::Path::operator> (
    const Path & path
) noexcept const
```




<hr>



### function operator[] 

```C++
char SR_UTILS_NS::Path::operator[] (
    size_t index
) noexcept const
```




<hr>



### function operator[] 

```C++
char & SR_UTILS_NS::Path::operator[] (
    size_t index
) noexcept
```




<hr>



### function ~Path 

```C++
SR_UTILS_NS::Path::~Path () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/FileSystem/Path.h`

