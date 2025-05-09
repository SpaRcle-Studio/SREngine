

# Class SR\_HTYPES\_NS::SafePtr

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)










Inherited by the following classes: [SR\_GRAPH\_NS::RenderContext](classSR__GRAPH__NS_1_1RenderContext.md),  [SR\_PHYSICS\_NS::PhysicsScene](classSR__PHYSICS__NS_1_1PhysicsScene.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](#function-autofree-12) (const std::function&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](#function-autofree-22) () <br> |
|  bool | [**Do**](#function-do-14) (const std::function&lt; void(T \*ptr)&gt; & func) <br> |
|  U | [**Do**](#function-do-24) (const std::function&lt; U(T \*ptr)&gt; & func, U \_default) <br> |
|  bool | [**Do**](#function-do-34) (const std::function&lt; void(T \*)&gt; & func) <br> |
|  U | [**Do**](#function-do-44) (const std::function&lt; U(T \*)&gt; & func, U \_default) <br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; U &gt; | [**DynamicCast**](#function-dynamiccast) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](#function-get) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE [**SafePtrDynamicData**](structSR__HTYPES__NS_1_1SafePtrDynamicData.md) \* | [**GetPtrData**](#function-getptrdata) () noexcept const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](#function-getrawptr) () const<br> |
|  SR\_NODISCARD [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; | [**GetThis**](#function-getthis) () <br> |
|  SR\_NODISCARD uint32\_t | [**GetUseCount**](#function-getusecount) () const<br> |
|  SR\_NODISCARD bool | [**IsLocked**](#function-islocked) () const<br> |
|  void | [**Lock**](#function-lock) () const<br> |
|  SR\_NODISCARD bool | [**LockIfValid**](#function-lockifvalid) () const<br> |
|  void | [**RecursiveLock**](#function-recursivelock) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](#function-recursivelockifvalid) () const<br> |
|  void | [**RemoveAllLocks**](#function-removealllocks) () <br> |
|  void | [**Replace**](#function-replace) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|  void | [**ReplaceAndCopyLock**](#function-replaceandcopylock) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|  void | [**ReplaceAndLock**](#function-replaceandlock) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|   | [**SafePtr**](#function-safeptr-13) (const T \* ptr) <br> |
|   | [**SafePtr**](#function-safeptr-23) ([**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) const & ptr) <br> |
|   | [**SafePtr**](#function-safeptr-33) () <br> |
|  U | [**TryDo**](#function-trydo-12) (const std::function&lt; U(T \*ptr)&gt; & func, U \_default) <br> |
|  U | [**TryDo**](#function-trydo-22) (const std::function&lt; U(T \*)&gt; & func, U \_default) <br> |
|  bool | [**TryLock**](#function-trylock) () const<br> |
|  SR\_NODISCARD bool | [**TryLockIfValid**](#function-trylockifvalid) () const<br> |
|  bool | [**TryRecursiveLock**](#function-tryrecursivelock) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](#function-tryrecursivelockifvalid) () const<br> |
|  bool | [**TryUnlock**](#function-tryunlock) () const<br> |
|  void | [**Unlock**](#function-unlock) () const<br> |
|  SR\_NODISCARD bool | [**Valid**](#function-valid) () const<br> |
|   | [**operator bool**](#function-operator-bool) () noexcept const<br>_не должен быть виртуальным_  |
|  SR\_NODISCARD SR\_INLINE bool | [**operator!=**](#function-operator) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & right) noexcept const<br> |
|  T & | [**operator\***](#function-operator_1) () const<br> |
|  T \* | [**operator-&gt;**](#function-operator_2) () const<br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & | [**operator=**](#function-operator_3) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & ptr) <br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & | [**operator=**](#function-operator_4) (T \* ptr) <br> |
|  SR\_NODISCARD SR\_INLINE bool | [**operator==**](#function-operator_5) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & right) noexcept const<br> |
|   | [**~SafePtr**](#function-safeptr) () <br> |




























## Public Functions Documentation




### function AutoFree [1/2]

```C++
bool SR_HTYPES_NS::SafePtr::AutoFree (
    const std::function< void(T *ptr)> & freeFun
) 
```




<hr>



### function AutoFree [2/2]

```C++
bool SR_HTYPES_NS::SafePtr::AutoFree () 
```




<hr>



### function Do [1/4]

```C++
bool SR_HTYPES_NS::SafePtr::Do (
    const std::function< void(T *ptr)> & func
) 
```




<hr>



### function Do [2/4]

```C++
template<typename U>
U SR_HTYPES_NS::SafePtr::Do (
    const std::function< U(T *ptr)> & func,
    U _default
) 
```




<hr>



### function Do [3/4]

```C++
template<class T>
bool SR_HTYPES_NS::SafePtr::Do (
    const std::function< void(T *)> & func
) 
```




<hr>



### function Do [4/4]

```C++
template<typename U>
U SR_HTYPES_NS::SafePtr::Do (
    const std::function< U(T *)> & func,
    U _default
) 
```




<hr>



### function DynamicCast 

```C++
template<typename U>
inline SafePtr < U > SR_HTYPES_NS::SafePtr::DynamicCast () const
```




<hr>



### function Get 

```C++
inline SR_NODISCARD T * SR_HTYPES_NS::SafePtr::Get () const
```




<hr>



### function GetPtrData 

```C++
inline SR_NODISCARD SR_FORCE_INLINE SafePtrDynamicData * SR_HTYPES_NS::SafePtr::GetPtrData () noexcept const
```




<hr>



### function GetRawPtr 

```C++
inline SR_NODISCARD void * SR_HTYPES_NS::SafePtr::GetRawPtr () const
```




<hr>



### function GetThis 

```C++
inline SR_NODISCARD SafePtr < T > SR_HTYPES_NS::SafePtr::GetThis () 
```




<hr>



### function GetUseCount 

```C++
SR_NODISCARD uint32_t SR_HTYPES_NS::SafePtr::GetUseCount () const
```




<hr>



### function IsLocked 

```C++
inline SR_NODISCARD bool SR_HTYPES_NS::SafePtr::IsLocked () const
```




<hr>



### function Lock 

```C++
void SR_HTYPES_NS::SafePtr::Lock () const
```




<hr>



### function LockIfValid 

```C++
SR_NODISCARD bool SR_HTYPES_NS::SafePtr::LockIfValid () const
```




<hr>



### function RecursiveLock 

```C++
void SR_HTYPES_NS::SafePtr::RecursiveLock () const
```




<hr>



### function RecursiveLockIfValid 

```C++
SR_NODISCARD bool SR_HTYPES_NS::SafePtr::RecursiveLockIfValid () const
```




<hr>



### function RemoveAllLocks 

```C++
void SR_HTYPES_NS::SafePtr::RemoveAllLocks () 
```




<hr>



### function Replace 

```C++
void SR_HTYPES_NS::SafePtr::Replace (
    const SafePtr & ptr
) 
```




<hr>



### function ReplaceAndCopyLock 

```C++
void SR_HTYPES_NS::SafePtr::ReplaceAndCopyLock (
    const SafePtr & ptr
) 
```




<hr>



### function ReplaceAndLock 

```C++
void SR_HTYPES_NS::SafePtr::ReplaceAndLock (
    const SafePtr & ptr
) 
```




<hr>



### function SafePtr [1/3]

```C++
explicit SR_HTYPES_NS::SafePtr::SafePtr (
    const T * ptr
) 
```




<hr>



### function SafePtr [2/3]

```C++
SR_HTYPES_NS::SafePtr::SafePtr (
    SafePtr const & ptr
) 
```




<hr>



### function SafePtr [3/3]

```C++
SR_HTYPES_NS::SafePtr::SafePtr () 
```




<hr>



### function TryDo [1/2]

```C++
template<typename U>
U SR_HTYPES_NS::SafePtr::TryDo (
    const std::function< U(T *ptr)> & func,
    U _default
) 
```




<hr>



### function TryDo [2/2]

```C++
template<typename U>
U SR_HTYPES_NS::SafePtr::TryDo (
    const std::function< U(T *)> & func,
    U _default
) 
```




<hr>



### function TryLock 

```C++
bool SR_HTYPES_NS::SafePtr::TryLock () const
```




<hr>



### function TryLockIfValid 

```C++
SR_NODISCARD bool SR_HTYPES_NS::SafePtr::TryLockIfValid () const
```




<hr>



### function TryRecursiveLock 

```C++
bool SR_HTYPES_NS::SafePtr::TryRecursiveLock () const
```




<hr>



### function TryRecursiveLockIfValid 

```C++
SR_NODISCARD bool SR_HTYPES_NS::SafePtr::TryRecursiveLockIfValid () const
```




<hr>



### function TryUnlock 

```C++
bool SR_HTYPES_NS::SafePtr::TryUnlock () const
```




<hr>



### function Unlock 

```C++
void SR_HTYPES_NS::SafePtr::Unlock () const
```




<hr>



### function Valid 

```C++
inline SR_NODISCARD bool SR_HTYPES_NS::SafePtr::Valid () const
```




<hr>



### function operator bool 

_не должен быть виртуальным_ 
```C++
inline SR_HTYPES_NS::SafePtr::operator bool () noexcept const
```




<hr>



### function operator!= 

```C++
inline SR_NODISCARD SR_INLINE bool SR_HTYPES_NS::SafePtr::operator!= (
    const SafePtr < T > & right
) noexcept const
```




<hr>



### function operator\* 

```C++
inline T & SR_HTYPES_NS::SafePtr::operator* () const
```




<hr>



### function operator-&gt; 

```C++
inline T * SR_HTYPES_NS::SafePtr::operator-> () const
```




<hr>



### function operator= 

```C++
SafePtr < T > & SR_HTYPES_NS::SafePtr::operator= (
    const SafePtr < T > & ptr
) 
```




<hr>



### function operator= 

```C++
SafePtr < T > & SR_HTYPES_NS::SafePtr::operator= (
    T * ptr
) 
```




<hr>



### function operator== 

```C++
inline SR_NODISCARD SR_INLINE bool SR_HTYPES_NS::SafePtr::operator== (
    const SafePtr < T > & right
) noexcept const
```




<hr>



### function ~SafePtr 

```C++
SR_HTYPES_NS::SafePtr::~SafePtr () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/SafePointer.h`

