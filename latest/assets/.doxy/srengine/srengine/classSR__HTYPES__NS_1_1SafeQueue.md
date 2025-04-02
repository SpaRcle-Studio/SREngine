

# Class SR\_HTYPES\_NS::SafeQueue

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**SafeQueue**](classSR__HTYPES__NS_1_1SafeQueue.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**Empty**](#function-empty) () noexcept const<br> |
|  void | [**Flush**](#function-flush) (const std::function&lt; void(T &)&gt; & callBack) <br> |
|  void | [**Push**](#function-push) (const T & value) noexcept<br> |
|  SR\_NODISCARD std::shared\_lock&lt; std::shared\_mutex &gt; | [**ReadLock**](#function-readlock) () const<br> |
|  SR\_NODISCARD uint64\_t | [**Size**](#function-size) () noexcept const<br> |
|  SR\_NODISCARD std::lock\_guard&lt; std::shared\_mutex &gt; | [**WriteLock**](#function-writelock) () const<br> |


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




### function Empty 

```C++
SR_NODISCARD bool SR_HTYPES_NS::SafeQueue::Empty () noexcept const
```




<hr>



### function Flush 

```C++
void SR_HTYPES_NS::SafeQueue::Flush (
    const std::function< void(T &)> & callBack
) 
```




<hr>



### function Push 

```C++
void SR_HTYPES_NS::SafeQueue::Push (
    const T & value
) noexcept
```




<hr>



### function ReadLock 

```C++
inline SR_NODISCARD std::shared_lock< std::shared_mutex > SR_HTYPES_NS::SafeQueue::ReadLock () const
```




<hr>



### function Size 

```C++
SR_NODISCARD uint64_t SR_HTYPES_NS::SafeQueue::Size () noexcept const
```




<hr>



### function WriteLock 

```C++
inline SR_NODISCARD std::lock_guard< std::shared_mutex > SR_HTYPES_NS::SafeQueue::WriteLock () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/SafeQueue.h`

