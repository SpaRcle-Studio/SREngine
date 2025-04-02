

# Class SR\_SCRIPTING\_NS::ScriptHolder



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**ScriptHolder**](classSR__SCRIPTING__NS_1_1ScriptHolder.md)








Inherits the following classes: [SR\_HTYPES\_NS::SafePtr](classSR__HTYPES__NS_1_1SafePtr.md),  [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; [**ScriptHolder**](classSR__SCRIPTING__NS_1_1ScriptHolder.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |




























































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD T \* | [**GetScript**](#function-getscript) () const<br> |
|   | [**ScriptHolder**](#function-scriptholder) (void \* pScriptImpl) <br> |
|  void | [**SetScript**](#function-setscript) (void \* pScriptImpl) <br> |
|   | [**~ScriptHolder**](#function-scriptholder) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SafePtr

See [SR\_HTYPES\_NS::SafePtr](classSR__HTYPES__NS_1_1SafePtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SafePtr.md#function-autofree-12) (const std::function&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SafePtr.md#function-autofree-22) () <br> |
|  bool | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-14) (const std::function&lt; void(T \*ptr)&gt; & func) <br> |
|  U | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-24) (const std::function&lt; U(T \*ptr)&gt; & func, U \_default) <br> |
|  bool | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-34) (const std::function&lt; void(T \*)&gt; & func) <br> |
|  U | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-44) (const std::function&lt; U(T \*)&gt; & func, U \_default) <br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SafePtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](classSR__HTYPES__NS_1_1SafePtr.md#function-get) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE [**SafePtrDynamicData**](structSR__HTYPES__NS_1_1SafePtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SafePtr.md#function-getptrdata) () noexcept const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-getrawptr) () const<br> |
|  SR\_NODISCARD [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SafePtr.md#function-getthis) () <br> |
|  SR\_NODISCARD uint32\_t | [**GetUseCount**](classSR__HTYPES__NS_1_1SafePtr.md#function-getusecount) () const<br> |
|  SR\_NODISCARD bool | [**IsLocked**](classSR__HTYPES__NS_1_1SafePtr.md#function-islocked) () const<br> |
|  void | [**Lock**](classSR__HTYPES__NS_1_1SafePtr.md#function-lock) () const<br> |
|  SR\_NODISCARD bool | [**LockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-lockifvalid) () const<br> |
|  void | [**RecursiveLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-recursivelock) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-recursivelockifvalid) () const<br> |
|  void | [**RemoveAllLocks**](classSR__HTYPES__NS_1_1SafePtr.md#function-removealllocks) () <br> |
|  void | [**Replace**](classSR__HTYPES__NS_1_1SafePtr.md#function-replace) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|  void | [**ReplaceAndCopyLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-replaceandcopylock) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|  void | [**ReplaceAndLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-replaceandlock) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|   | [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr-13) (const T \* ptr) <br> |
|   | [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr-23) ([**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) const & ptr) <br> |
|   | [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr-33) () <br> |
|  U | [**TryDo**](classSR__HTYPES__NS_1_1SafePtr.md#function-trydo-12) (const std::function&lt; U(T \*ptr)&gt; & func, U \_default) <br> |
|  U | [**TryDo**](classSR__HTYPES__NS_1_1SafePtr.md#function-trydo-22) (const std::function&lt; U(T \*)&gt; & func, U \_default) <br> |
|  bool | [**TryLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-trylock) () const<br> |
|  SR\_NODISCARD bool | [**TryLockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-trylockifvalid) () const<br> |
|  bool | [**TryRecursiveLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-tryrecursivelock) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-tryrecursivelockifvalid) () const<br> |
|  bool | [**TryUnlock**](classSR__HTYPES__NS_1_1SafePtr.md#function-tryunlock) () const<br> |
|  void | [**Unlock**](classSR__HTYPES__NS_1_1SafePtr.md#function-unlock) () const<br> |
|  SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SafePtr.md#function-valid) () const<br> |
|   | [**operator bool**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator-bool) () noexcept const<br>_не должен быть виртуальным_  |
|  SR\_NODISCARD SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & right) noexcept const<br> |
|  T & | [**operator\***](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_1) () const<br> |
|  T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_2) () const<br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_3) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & ptr) <br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_4) (T \* ptr) <br> |
|  SR\_NODISCARD SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_5) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & right) noexcept const<br> |
|   | [**~SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr) () <br> |


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








## Public Types Documentation




### typedef Ptr 

```C++
using SR_SCRIPTING_NS::ScriptHolder::Ptr =  SR_HTYPES_NS::SafePtr<ScriptHolder>;
```




<hr>
## Public Functions Documentation




### function GetScript 

```C++
template<typename T>
inline SR_NODISCARD T * SR_SCRIPTING_NS::ScriptHolder::GetScript () const
```




<hr>



### function ScriptHolder 

```C++
inline explicit SR_SCRIPTING_NS::ScriptHolder::ScriptHolder (
    void * pScriptImpl
) 
```




<hr>



### function SetScript 

```C++
inline void SR_SCRIPTING_NS::ScriptHolder::SetScript (
    void * pScriptImpl
) 
```




<hr>



### function ~ScriptHolder 

```C++
inline SR_SCRIPTING_NS::ScriptHolder::~ScriptHolder () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/ScriptHolder.h`

