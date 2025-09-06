

# Class SR\_HTYPES\_NS::MultiThreadPtr

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**MultiThreadPtr**](classSR__HTYPES__NS_1_1MultiThreadPtr.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](#function-autofree) (const std::function&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  U | [**DynamicCast**](#function-dynamiccast) () <br> |
|  SR\_NODISCARD T \* | [**Get**](#function-get) () const<br> |
|  SR\_NODISCARD std::recursive\_mutex & | [**GetMutex**](#function-getmutex) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](#function-getrawptr) () const<br> |
|  SR\_NODISCARD [**MultiThreadPtr**](classSR__HTYPES__NS_1_1MultiThreadPtr.md)&lt; T &gt; | [**GetThis**](#function-getthis) () <br> |
|  SR\_NODISCARD uint32\_t | [**GetUseCount**](#function-getusecount) () const<br> |
|  bool | [**Lock**](#function-lock) () const<br> |
|   | [**MultiThreadPtr**](#function-multithreadptr-13) (T \* ptr) <br> |
|   | [**MultiThreadPtr**](#function-multithreadptr-23) ([**MultiThreadPtr**](classSR__HTYPES__NS_1_1MultiThreadPtr.md) const & ptr) <br> |
|   | [**MultiThreadPtr**](#function-multithreadptr-33) () = default<br> |
|  void | [**Unlock**](#function-unlock) () const<br> |
|  SR\_NODISCARD bool | [**Valid**](#function-valid) () const<br> |
|   | [**operator bool**](#function-operator-bool) () noexcept const<br> |
|  SR\_NODISCARD SR\_INLINE bool | [**operator!=**](#function-operator) (const [**MultiThreadPtr**](classSR__HTYPES__NS_1_1MultiThreadPtr.md)&lt; T &gt; & right) noexcept const<br> |
|  T & | [**operator\***](#function-operator_1) () const<br> |
|  T \* | [**operator-&gt;**](#function-operator-) () const<br> |
|  [**MultiThreadPtr**](classSR__HTYPES__NS_1_1MultiThreadPtr.md)&lt; T &gt; & | [**operator=**](#function-operator_2) (const [**MultiThreadPtr**](classSR__HTYPES__NS_1_1MultiThreadPtr.md)&lt; T &gt; & ptr) <br>_не должен быть виртуальным_  |
|  [**MultiThreadPtr**](classSR__HTYPES__NS_1_1MultiThreadPtr.md)&lt; T &gt; & | [**operator=**](#function-operator_3) (T \* ptr) <br> |
|  SR\_NODISCARD SR\_INLINE bool | [**operator==**](#function-operator_4) (const [**MultiThreadPtr**](classSR__HTYPES__NS_1_1MultiThreadPtr.md)&lt; T &gt; & right) noexcept const<br> |
|   | [**~MultiThreadPtr**](#function-multithreadptr) () <br> |




























## Public Functions Documentation




### function AutoFree 

```C++
bool SR_HTYPES_NS::MultiThreadPtr::AutoFree (
    const std::function< void(T *ptr)> & freeFun
) 
```




<hr>



### function DynamicCast 

```C++
template<typename U>
inline U SR_HTYPES_NS::MultiThreadPtr::DynamicCast () 
```




<hr>



### function Get 

```C++
inline SR_NODISCARD T * SR_HTYPES_NS::MultiThreadPtr::Get () const
```




<hr>



### function GetMutex 

```C++
inline SR_NODISCARD std::recursive_mutex & SR_HTYPES_NS::MultiThreadPtr::GetMutex () const
```




<hr>



### function GetRawPtr 

```C++
inline SR_NODISCARD void * SR_HTYPES_NS::MultiThreadPtr::GetRawPtr () const
```




<hr>



### function GetThis 

```C++
inline SR_NODISCARD MultiThreadPtr < T > SR_HTYPES_NS::MultiThreadPtr::GetThis () 
```




<hr>



### function GetUseCount 

```C++
inline SR_NODISCARD uint32_t SR_HTYPES_NS::MultiThreadPtr::GetUseCount () const
```




<hr>



### function Lock 

```C++
bool SR_HTYPES_NS::MultiThreadPtr::Lock () const
```




<hr>



### function MultiThreadPtr [1/3]

```C++
explicit SR_HTYPES_NS::MultiThreadPtr::MultiThreadPtr (
    T * ptr
) 
```




 


        

<hr>



### function MultiThreadPtr [2/3]

```C++
SR_HTYPES_NS::MultiThreadPtr::MultiThreadPtr (
    MultiThreadPtr const & ptr
) 
```




<hr>



### function MultiThreadPtr [3/3]

```C++
SR_HTYPES_NS::MultiThreadPtr::MultiThreadPtr () = default
```




<hr>



### function Unlock 

```C++
void SR_HTYPES_NS::MultiThreadPtr::Unlock () const
```




<hr>



### function Valid 

```C++
inline SR_NODISCARD bool SR_HTYPES_NS::MultiThreadPtr::Valid () const
```




<hr>



### function operator bool 

```C++
inline SR_HTYPES_NS::MultiThreadPtr::operator bool () noexcept const
```




<hr>



### function operator!= 

```C++
inline SR_NODISCARD SR_INLINE bool SR_HTYPES_NS::MultiThreadPtr::operator!= (
    const MultiThreadPtr < T > & right
) noexcept const
```




<hr>



### function operator\* 

```C++
inline T & SR_HTYPES_NS::MultiThreadPtr::operator* () const
```



NOLINT 


        

<hr>



### function operator-&gt; 

```C++
inline T * SR_HTYPES_NS::MultiThreadPtr::operator-> () const
```




<hr>



### function operator= 

_не должен быть виртуальным_ 
```C++
MultiThreadPtr < T > & SR_HTYPES_NS::MultiThreadPtr::operator= (
    const MultiThreadPtr < T > & ptr
) 
```




<hr>



### function operator= 

```C++
MultiThreadPtr < T > & SR_HTYPES_NS::MultiThreadPtr::operator= (
    T * ptr
) 
```




<hr>



### function operator== 

```C++
inline SR_NODISCARD SR_INLINE bool SR_HTYPES_NS::MultiThreadPtr::operator== (
    const MultiThreadPtr < T > & right
) noexcept const
```




<hr>



### function ~MultiThreadPtr 

```C++
SR_HTYPES_NS::MultiThreadPtr::~MultiThreadPtr () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/MultiThreadPtr.h`

