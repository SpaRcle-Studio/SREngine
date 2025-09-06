

# Class SR\_HTYPES\_NS::ObjectPool

**template &lt;typename T, typename Index&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**ObjectPool**](classSR__HTYPES__NS_1_1ObjectPool.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  Index | [**Add**](#function-add-12) (T && object) <br> |
|  Index | [**Add**](#function-add-22) (const T & object) <br> |
|  T & | [**At**](#function-at-12) (Index index) <br> |
|  const T & | [**At**](#function-at-22) (Index index) const<br> |
|  T &SR\_FASTCALL | [**AtUnchecked**](#function-atunchecked-12) (Index index) <br> |
|  const T &SR\_FASTCALL | [**AtUnchecked**](#function-atunchecked-22) (Index index) const<br> |
|  void | [**Clear**](#function-clear) () <br> |
|  void | [**ForEach**](#function-foreach-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(Index, T &)&gt; & func) <br> |
|  void | [**ForEach**](#function-foreach-22) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(Index, const T &)&gt; & func) const<br> |
|  SR\_NODISCARD uint32\_t | [**GetAliveCount**](#function-getalivecount) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetCapacity**](#function-getcapacity) () const<br> |
|  T \* | [**GetFirstAlive**](#function-getfirstalive) () <br> |
|  SR\_NODISCARD uint32\_t | [**GetFreeCount**](#function-getfreecount) () const<br> |
|  SR\_NODISCARD const std::vector&lt; std::pair&lt; bool, T &gt; &gt; & | [**GetObjects**](#function-getobjects) () const<br> |
|  SR\_NODISCARD bool SR\_FASTCALL | [**IsAlive**](#function-isalive) (Index index) const<br> |
|  SR\_NODISCARD bool | [**IsEmpty**](#function-isempty) () const<br> |
|   | [**ObjectPool**](#function-objectpool-12) () = default<br> |
|   | [**ObjectPool**](#function-objectpool-22) ([**ObjectPool**](classSR__HTYPES__NS_1_1ObjectPool.md) && other) noexcept<br> |
|  T | [**RemoveByIndex**](#function-removebyindex) (Index index) <br> |
|  void | [**RemoveByObject**](#function-removebyobject) (const T & object) <br> |
|  void | [**RemoveIf**](#function-removeif) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool(Index, T &)&gt; & condition, const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T)&gt; & deleter) <br> |
|  void | [**Reserve**](#function-reserve) (uint64\_t size) <br> |
|  void | [**ShrinkToFit**](#function-shrinktofit) () <br> |
|  [**ObjectPool**](classSR__HTYPES__NS_1_1ObjectPool.md) & | [**operator=**](#function-operator) ([**ObjectPool**](classSR__HTYPES__NS_1_1ObjectPool.md) && other) noexcept<br> |


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
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function Add [1/2]

```C++
inline Index SR_HTYPES_NS::ObjectPool::Add (
    T && object
) 
```




<hr>



### function Add [2/2]

```C++
inline Index SR_HTYPES_NS::ObjectPool::Add (
    const T & object
) 
```




<hr>



### function At [1/2]

```C++
inline T & SR_HTYPES_NS::ObjectPool::At (
    Index index
) 
```




<hr>



### function At [2/2]

```C++
inline const T & SR_HTYPES_NS::ObjectPool::At (
    Index index
) const
```




<hr>



### function AtUnchecked [1/2]

```C++
inline T &SR_FASTCALL SR_HTYPES_NS::ObjectPool::AtUnchecked (
    Index index
) 
```




<hr>



### function AtUnchecked [2/2]

```C++
inline const T &SR_FASTCALL SR_HTYPES_NS::ObjectPool::AtUnchecked (
    Index index
) const
```




<hr>



### function Clear 

```C++
inline void SR_HTYPES_NS::ObjectPool::Clear () 
```




<hr>



### function ForEach [1/2]

```C++
inline void SR_HTYPES_NS::ObjectPool::ForEach (
    const SR_HTYPES_NS::Function < void(Index, T &)> & func
) 
```




<hr>



### function ForEach [2/2]

```C++
inline void SR_HTYPES_NS::ObjectPool::ForEach (
    const SR_HTYPES_NS::Function < void(Index, const T &)> & func
) const
```




<hr>



### function GetAliveCount 

```C++
inline SR_NODISCARD uint32_t SR_HTYPES_NS::ObjectPool::GetAliveCount () const
```




<hr>



### function GetCapacity 

```C++
inline SR_NODISCARD uint32_t SR_HTYPES_NS::ObjectPool::GetCapacity () const
```




<hr>



### function GetFirstAlive 

```C++
inline T * SR_HTYPES_NS::ObjectPool::GetFirstAlive () 
```




<hr>



### function GetFreeCount 

```C++
inline SR_NODISCARD uint32_t SR_HTYPES_NS::ObjectPool::GetFreeCount () const
```




<hr>



### function GetObjects 

```C++
inline SR_NODISCARD const std::vector< std::pair< bool, T > > & SR_HTYPES_NS::ObjectPool::GetObjects () const
```




<hr>



### function IsAlive 

```C++
inline SR_NODISCARD bool SR_FASTCALL SR_HTYPES_NS::ObjectPool::IsAlive (
    Index index
) const
```




<hr>



### function IsEmpty 

```C++
inline SR_NODISCARD bool SR_HTYPES_NS::ObjectPool::IsEmpty () const
```




<hr>



### function ObjectPool [1/2]

```C++
SR_HTYPES_NS::ObjectPool::ObjectPool () = default
```




<hr>



### function ObjectPool [2/2]

```C++
inline SR_HTYPES_NS::ObjectPool::ObjectPool (
    ObjectPool && other
) noexcept
```




<hr>



### function RemoveByIndex 

```C++
inline T SR_HTYPES_NS::ObjectPool::RemoveByIndex (
    Index index
) 
```




<hr>



### function RemoveByObject 

```C++
inline void SR_HTYPES_NS::ObjectPool::RemoveByObject (
    const T & object
) 
```




<hr>



### function RemoveIf 

```C++
inline void SR_HTYPES_NS::ObjectPool::RemoveIf (
    const SR_HTYPES_NS::Function < bool(Index, T &)> & condition,
    const SR_HTYPES_NS::Function < void(T)> & deleter
) 
```




<hr>



### function Reserve 

```C++
inline void SR_HTYPES_NS::ObjectPool::Reserve (
    uint64_t size
) 
```




<hr>



### function ShrinkToFit 

```C++
inline void SR_HTYPES_NS::ObjectPool::ShrinkToFit () 
```




<hr>



### function operator= 

```C++
inline ObjectPool & SR_HTYPES_NS::ObjectPool::operator= (
    ObjectPool && other
) noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/ObjectPool.h`

