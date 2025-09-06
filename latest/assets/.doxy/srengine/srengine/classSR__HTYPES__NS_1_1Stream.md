

# Class SR\_HTYPES\_NS::Stream



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**Stream**](classSR__HTYPES__NS_1_1Stream.md)










Inherited by the following classes: [SR\_HTYPES\_NS::Marshal](classSR__HTYPES__NS_1_1Marshal.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD uint64\_t | [**GetCapacity**](#function-getcapacity) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetPosition**](#function-getposition) () noexcept const<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**Read**](#function-read) (void \* pDst, uint64\_t count) noexcept<br> |
|  void SR\_FASTCALL | [**Reserve**](#function-reserve) (uint64\_t capacity) <br> |
|  void | [**SetData**](#function-setdata) (const char \* pData, uint64\_t size) <br> |
|  void | [**SetPosition**](#function-setposition) (uint64\_t position) <br> |
|  SR\_NODISCARD uint64\_t | [**Size**](#function-size) () noexcept const<br> |
|  void | [**Skip**](#function-skip) (uint64\_t count) <br> |
|   | [**Stream**](#function-stream-16) () <br> |
|   | [**Stream**](#function-stream-26) (std::ifstream & ifs) <br> |
|   | [**Stream**](#function-stream-36) (const std::string & str) <br> |
|   | [**Stream**](#function-stream-46) (const char \* pData, uint64\_t size, bool copy=true) <br> |
|   | [**Stream**](#function-stream-56) (const [**Stream**](classSR__HTYPES__NS_1_1Stream.md) & other) noexcept<br> |
|   | [**Stream**](#function-stream-66) ([**Stream**](classSR__HTYPES__NS_1_1Stream.md) && other) noexcept<br> |
|  SR\_NODISCARD std::string | [**ToBase64**](#function-tobase64) () noexcept const<br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () noexcept const<br> |
|  SR\_NODISCARD std::string\_view | [**ToStringView**](#function-tostringview) () noexcept const<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**TryRead**](#function-tryread) (void \* pDst, uint64\_t count) noexcept<br> |
|  SR\_NODISCARD bool | [**Valid**](#function-valid) () noexcept const<br> |
|  SR\_NODISCARD const char \* | [**View**](#function-view) () noexcept const<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**Write**](#function-write) (const void \* pSrc, uint64\_t count) noexcept<br> |
|   | [**operator bool**](#function-operator-bool) () noexcept const<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**operator=**](#function-operator) (const [**Stream**](classSR__HTYPES__NS_1_1Stream.md) & other) noexcept<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**operator=**](#function-operator_1) ([**Stream**](classSR__HTYPES__NS_1_1Stream.md) && other) noexcept<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**read**](#function-read) (void \* pDst, uint64\_t count) noexcept<br> |
|  [**Stream**](classSR__HTYPES__NS_1_1Stream.md) &SR\_FASTCALL | [**write**](#function-write) (const void \* pSrc, uint64\_t count) noexcept<br> |
|   | [**~Stream**](#function-stream) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  char \* | [**Allocate**](#function-allocate) (uint64\_t size) <br> |
|  void | [**Free**](#function-free) (char \* pData) <br> |


























## Public Functions Documentation




### function GetCapacity 

```C++
SR_NODISCARD uint64_t SR_HTYPES_NS::Stream::GetCapacity () noexcept const
```




<hr>



### function GetPosition 

```C++
SR_NODISCARD uint64_t SR_HTYPES_NS::Stream::GetPosition () noexcept const
```




<hr>



### function Read 

```C++
Stream &SR_FASTCALL SR_HTYPES_NS::Stream::Read (
    void * pDst,
    uint64_t count
) noexcept
```




<hr>



### function Reserve 

```C++
void SR_FASTCALL SR_HTYPES_NS::Stream::Reserve (
    uint64_t capacity
) 
```




<hr>



### function SetData 

```C++
void SR_HTYPES_NS::Stream::SetData (
    const char * pData,
    uint64_t size
) 
```




<hr>



### function SetPosition 

```C++
void SR_HTYPES_NS::Stream::SetPosition (
    uint64_t position
) 
```




<hr>



### function Size 

```C++
SR_NODISCARD uint64_t SR_HTYPES_NS::Stream::Size () noexcept const
```




<hr>



### function Skip 

```C++
void SR_HTYPES_NS::Stream::Skip (
    uint64_t count
) 
```




<hr>



### function Stream [1/6]

```C++
SR_HTYPES_NS::Stream::Stream () 
```




<hr>



### function Stream [2/6]

```C++
SR_HTYPES_NS::Stream::Stream (
    std::ifstream & ifs
) 
```




<hr>



### function Stream [3/6]

```C++
SR_HTYPES_NS::Stream::Stream (
    const std::string & str
) 
```



NOLINT 


        

<hr>



### function Stream [4/6]

```C++
SR_HTYPES_NS::Stream::Stream (
    const char * pData,
    uint64_t size,
    bool copy=true
) 
```



NOLINT 


        

<hr>



### function Stream [5/6]

```C++
SR_HTYPES_NS::Stream::Stream (
    const Stream & other
) noexcept
```




<hr>



### function Stream [6/6]

```C++
SR_HTYPES_NS::Stream::Stream (
    Stream && other
) noexcept
```




<hr>



### function ToBase64 

```C++
SR_NODISCARD std::string SR_HTYPES_NS::Stream::ToBase64 () noexcept const
```




<hr>



### function ToString 

```C++
SR_NODISCARD std::string SR_HTYPES_NS::Stream::ToString () noexcept const
```




<hr>



### function ToStringView 

```C++
SR_NODISCARD std::string_view SR_HTYPES_NS::Stream::ToStringView () noexcept const
```




<hr>



### function TryRead 

```C++
Stream &SR_FASTCALL SR_HTYPES_NS::Stream::TryRead (
    void * pDst,
    uint64_t count
) noexcept
```




<hr>



### function Valid 

```C++
SR_NODISCARD bool SR_HTYPES_NS::Stream::Valid () noexcept const
```



NOLINT 


        

<hr>



### function View 

```C++
SR_NODISCARD const char * SR_HTYPES_NS::Stream::View () noexcept const
```




<hr>



### function Write 

```C++
Stream &SR_FASTCALL SR_HTYPES_NS::Stream::Write (
    const void * pSrc,
    uint64_t count
) noexcept
```




<hr>



### function operator bool 

```C++
SR_HTYPES_NS::Stream::operator bool () noexcept const
```




<hr>



### function operator= 

```C++
Stream &SR_FASTCALL SR_HTYPES_NS::Stream::operator= (
    const Stream & other
) noexcept
```




<hr>



### function operator= 

```C++
Stream &SR_FASTCALL SR_HTYPES_NS::Stream::operator= (
    Stream && other
) noexcept
```




<hr>



### function read 

```C++
Stream &SR_FASTCALL SR_HTYPES_NS::Stream::read (
    void * pDst,
    uint64_t count
) noexcept
```




<hr>



### function write 

```C++
Stream &SR_FASTCALL SR_HTYPES_NS::Stream::write (
    const void * pSrc,
    uint64_t count
) noexcept
```




<hr>



### function ~Stream 

```C++
SR_HTYPES_NS::Stream::~Stream () 
```




<hr>
## Public Static Functions Documentation




### function Allocate 

```C++
static char * SR_HTYPES_NS::Stream::Allocate (
    uint64_t size
) 
```




<hr>



### function Free 

```C++
static void SR_HTYPES_NS::Stream::Free (
    char * pData
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/Stream.h`

