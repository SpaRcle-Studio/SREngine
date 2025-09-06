

# Class SR\_HTYPES\_NS::Marshal



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**Marshal**](classSR__HTYPES__NS_1_1Marshal.md)








Inherits the following classes: [SR\_HTYPES\_NS::Stream](classSR__HTYPES__NS_1_1Stream.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**Marshal**](classSR__HTYPES__NS_1_1Marshal.md) \* | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**Stream**](classSR__HTYPES__NS_1_1Stream.md) | [**Super**](#typedef-super)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Append**](#function-append-13) ([**Marshal**](classSR__HTYPES__NS_1_1Marshal.md) && marshal) <br> |
|  void | [**Append**](#function-append-23) (std::unique\_ptr&lt; [**Marshal**](classSR__HTYPES__NS_1_1Marshal.md) &gt; && pMarshal) <br> |
|  void | [**Append**](#function-append-33) ([**Marshal::Ptr**](classSR__HTYPES__NS_1_1Marshal.md) & pMarshal) <br> |
|  SR\_NODISCARD [**Marshal**](classSR__HTYPES__NS_1_1Marshal.md) | [**Copy**](#function-copy) () const<br> |
|  SR\_NODISCARD [**Marshal::Ptr**](classSR__HTYPES__NS_1_1Marshal.md) | [**CopyPtr**](#function-copyptr) () const<br> |
|  SR\_NODISCARD [**Marshal**](classSR__HTYPES__NS_1_1Marshal.md) | [**FullCopy**](#function-fullcopy) () const<br> |
|   | [**Marshal**](#function-marshal-14) () <br> |
|   | [**Marshal**](#function-marshal-24) (std::ifstream & ifs) <br> |
|   | [**Marshal**](#function-marshal-34) (const std::string & str) <br> |
|   | [**Marshal**](#function-marshal-44) (const char \* pData, uint64\_t size, bool copy=true) <br> |
|  T | [**Read**](#function-read-12) () <br> |
|  T | [**Read**](#function-read-22) (const T & def) <br> |
|  void | [**ReadBlock**](#function-readblock) (void \* pDestination) <br> |
|  SR\_NODISCARD [**Marshal**](classSR__HTYPES__NS_1_1Marshal.md) | [**ReadBytes**](#function-readbytes) (uint64\_t count) noexcept<br> |
|  SR\_NODISCARD [**Marshal::Ptr**](classSR__HTYPES__NS_1_1Marshal.md) | [**ReadBytesPtr**](#function-readbytesptr) (uint64\_t count) noexcept<br> |
|  bool | [**Save**](#function-save) (const Path & path) const<br> |
|  T | [**TryRead**](#function-tryread) () <br> |
|  T | [**View**](#function-view) (uint64\_t offset) const<br> |
|  void | [**Write**](#function-write-12) (const T & value) <br> |
|  void | [**Write**](#function-write-22) (const T & value, const T & def) <br> |
|  void | [**WriteBlock**](#function-writeblock) (void \* pData, uint64\_t size) <br> |
|   | [**~Marshal**](#function-marshal) () <br> |


## Public Functions inherited from SR_HTYPES_NS::Stream

See [SR\_HTYPES\_NS::Stream](classSR__HTYPES__NS_1_1Stream.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD uint64\_t | [**GetCapacity**](classSR__HTYPES__NS_1_1Stream.md#function-getcapacity) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetPosition**](classSR__HTYPES__NS_1_1Stream.md#function-getposition) () noexcept const<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**Read**](classSR__HTYPES__NS_1_1Stream.md#function-read) (void \* pDst, uint64\_t count) noexcept<br> |
|  void SR\_FASTCALL | [**Reserve**](classSR__HTYPES__NS_1_1Stream.md#function-reserve) (uint64\_t capacity) <br> |
|  void | [**SetData**](classSR__HTYPES__NS_1_1Stream.md#function-setdata) (const char \* pData, uint64\_t size) <br> |
|  void | [**SetPosition**](classSR__HTYPES__NS_1_1Stream.md#function-setposition) (uint64\_t position) <br> |
|  SR\_NODISCARD uint64\_t | [**Size**](classSR__HTYPES__NS_1_1Stream.md#function-size) () noexcept const<br> |
|  void | [**Skip**](classSR__HTYPES__NS_1_1Stream.md#function-skip) (uint64\_t count) <br> |
|   | [**Stream**](classSR__HTYPES__NS_1_1Stream.md#function-stream-16) () <br> |
|   | [**Stream**](classSR__HTYPES__NS_1_1Stream.md#function-stream-26) (std::ifstream & ifs) <br> |
|   | [**Stream**](classSR__HTYPES__NS_1_1Stream.md#function-stream-36) (const std::string & str) <br> |
|   | [**Stream**](classSR__HTYPES__NS_1_1Stream.md#function-stream-46) (const char \* pData, uint64\_t size, bool copy=true) <br> |
|   | [**Stream**](classSR__HTYPES__NS_1_1Stream.md#function-stream-56) (const [**Stream**](classSR__HTYPES__NS_1_1Stream.md) & other) noexcept<br> |
|   | [**Stream**](classSR__HTYPES__NS_1_1Stream.md#function-stream-66) ([**Stream**](classSR__HTYPES__NS_1_1Stream.md) && other) noexcept<br> |
|  SR\_NODISCARD std::string | [**ToBase64**](classSR__HTYPES__NS_1_1Stream.md#function-tobase64) () noexcept const<br> |
|  SR\_NODISCARD std::string | [**ToString**](classSR__HTYPES__NS_1_1Stream.md#function-tostring) () noexcept const<br> |
|  SR\_NODISCARD std::string\_view | [**ToStringView**](classSR__HTYPES__NS_1_1Stream.md#function-tostringview) () noexcept const<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**TryRead**](classSR__HTYPES__NS_1_1Stream.md#function-tryread) (void \* pDst, uint64\_t count) noexcept<br> |
|  SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1Stream.md#function-valid) () noexcept const<br> |
|  SR\_NODISCARD const char \* | [**View**](classSR__HTYPES__NS_1_1Stream.md#function-view) () noexcept const<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**Write**](classSR__HTYPES__NS_1_1Stream.md#function-write) (const void \* pSrc, uint64\_t count) noexcept<br> |
|   | [**operator bool**](classSR__HTYPES__NS_1_1Stream.md#function-operator-bool) () noexcept const<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**operator=**](classSR__HTYPES__NS_1_1Stream.md#function-operator) (const [**Stream**](classSR__HTYPES__NS_1_1Stream.md) & other) noexcept<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**operator=**](classSR__HTYPES__NS_1_1Stream.md#function-operator_1) ([**Stream**](classSR__HTYPES__NS_1_1Stream.md) && other) noexcept<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**read**](classSR__HTYPES__NS_1_1Stream.md#function-read) (void \* pDst, uint64\_t count) noexcept<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**write**](classSR__HTYPES__NS_1_1Stream.md#function-write) (const void \* pSrc, uint64\_t count) noexcept<br> |
|   | [**~Stream**](classSR__HTYPES__NS_1_1Stream.md#function-stream) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Marshal**](classSR__HTYPES__NS_1_1Marshal.md) | [**Load**](#function-load) (const Path & path) <br> |
|  [**Marshal**](classSR__HTYPES__NS_1_1Marshal.md) | [**LoadFromBase64**](#function-loadfrombase64) (const std::string & base64) <br> |
|  [**Marshal**](classSR__HTYPES__NS_1_1Marshal.md) | [**LoadFromMemory**](#function-loadfrommemory) (const std::string & data) <br> |
|  [**Marshal::Ptr**](classSR__HTYPES__NS_1_1Marshal.md) | [**LoadPtr**](#function-loadptr) (const Path & path) <br> |


## Public Static Functions inherited from SR_HTYPES_NS::Stream

See [SR\_HTYPES\_NS::Stream](classSR__HTYPES__NS_1_1Stream.md)

| Type | Name |
| ---: | :--- |
|  char \* | [**Allocate**](classSR__HTYPES__NS_1_1Stream.md#function-allocate) (uint64\_t size) <br> |
|  void | [**Free**](classSR__HTYPES__NS_1_1Stream.md#function-free) (char \* pData) <br> |


















































## Public Types Documentation




### typedef Ptr 

```C++
using SR_HTYPES_NS::Marshal::Ptr =  Marshal*;
```




<hr>



### typedef Super 

```C++
using SR_HTYPES_NS::Marshal::Super =  Stream;
```




<hr>
## Public Functions Documentation




### function Append [1/3]

```C++
void SR_HTYPES_NS::Marshal::Append (
    Marshal && marshal
) 
```




<hr>



### function Append [2/3]

```C++
void SR_HTYPES_NS::Marshal::Append (
    std::unique_ptr< Marshal > && pMarshal
) 
```




<hr>



### function Append [3/3]

```C++
void SR_HTYPES_NS::Marshal::Append (
    Marshal::Ptr & pMarshal
) 
```




<hr>



### function Copy 

```C++
SR_NODISCARD Marshal SR_HTYPES_NS::Marshal::Copy () const
```



NOLINT 


        

<hr>



### function CopyPtr 

```C++
SR_NODISCARD Marshal::Ptr SR_HTYPES_NS::Marshal::CopyPtr () const
```




<hr>



### function FullCopy 

```C++
SR_NODISCARD Marshal SR_HTYPES_NS::Marshal::FullCopy () const
```




<hr>



### function Marshal [1/4]

```C++
SR_HTYPES_NS::Marshal::Marshal () 
```




<hr>



### function Marshal [2/4]

```C++
SR_HTYPES_NS::Marshal::Marshal (
    std::ifstream & ifs
) 
```




<hr>



### function Marshal [3/4]

```C++
SR_HTYPES_NS::Marshal::Marshal (
    const std::string & str
) 
```



NOLINT 


        

<hr>



### function Marshal [4/4]

```C++
SR_HTYPES_NS::Marshal::Marshal (
    const char * pData,
    uint64_t size,
    bool copy=true
) 
```



NOLINT 


        

<hr>



### function Read [1/2]

```C++
template<typename T>
T SR_HTYPES_NS::Marshal::Read () 
```




<hr>



### function Read [2/2]

```C++
template<typename T>
T SR_HTYPES_NS::Marshal::Read (
    const T & def
) 
```




<hr>



### function ReadBlock 

```C++
void SR_HTYPES_NS::Marshal::ReadBlock (
    void * pDestination
) 
```




<hr>



### function ReadBytes 

```C++
SR_NODISCARD Marshal SR_HTYPES_NS::Marshal::ReadBytes (
    uint64_t count
) noexcept
```




<hr>



### function ReadBytesPtr 

```C++
SR_NODISCARD Marshal::Ptr SR_HTYPES_NS::Marshal::ReadBytesPtr (
    uint64_t count
) noexcept
```




<hr>



### function Save 

```C++
bool SR_HTYPES_NS::Marshal::Save (
    const Path & path
) const
```




<hr>



### function TryRead 

```C++
template<typename T>
T SR_HTYPES_NS::Marshal::TryRead () 
```




<hr>



### function View 

```C++
template<typename T>
T SR_HTYPES_NS::Marshal::View (
    uint64_t offset
) const
```




<hr>



### function Write [1/2]

```C++
template<typename T>
void SR_HTYPES_NS::Marshal::Write (
    const T & value
) 
```




<hr>



### function Write [2/2]

```C++
template<typename T>
void SR_HTYPES_NS::Marshal::Write (
    const T & value,
    const T & def
) 
```




<hr>



### function WriteBlock 

```C++
void SR_HTYPES_NS::Marshal::WriteBlock (
    void * pData,
    uint64_t size
) 
```




<hr>



### function ~Marshal 

```C++
SR_HTYPES_NS::Marshal::~Marshal () 
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static Marshal SR_HTYPES_NS::Marshal::Load (
    const Path & path
) 
```




<hr>



### function LoadFromBase64 

```C++
static Marshal SR_HTYPES_NS::Marshal::LoadFromBase64 (
    const std::string & base64
) 
```




<hr>



### function LoadFromMemory 

```C++
static Marshal SR_HTYPES_NS::Marshal::LoadFromMemory (
    const std::string & data
) 
```




<hr>



### function LoadPtr 

```C++
static Marshal::Ptr SR_HTYPES_NS::Marshal::LoadPtr (
    const Path & path
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/Marshal.h`

