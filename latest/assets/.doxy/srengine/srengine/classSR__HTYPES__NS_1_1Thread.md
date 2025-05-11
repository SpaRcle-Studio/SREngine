

# Class SR\_HTYPES\_NS::Thread



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**Thread**](classSR__HTYPES__NS_1_1Thread.md)








Inherits the following classes: NonCopyable












## Classes

| Type | Name |
| ---: | :--- |
| class | [**Factory**](classSR__HTYPES__NS_1_1Thread_1_1Factory.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**Thread**](classSR__HTYPES__NS_1_1Thread.md) \* | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**ThreadId**](#typedef-threadid)  <br> |
| typedef std::unordered\_map&lt; ThreadId, [**Thread::Ptr**](classSR__HTYPES__NS_1_1Thread.md) &gt; | [**ThreadsMap**](#typedef-threadsmap)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Detach**](#function-detach) () <br> |
|  bool | [**Execute**](#function-execute) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool()&gt; & function) const<br> |
|  void | [**Free**](#function-free) () <br> |
|  SR\_NODISCARD [**DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) \* | [**GetContext**](#function-getcontext) () <br> |
|  SR\_NODISCARD ThreadId | [**GetId**](#function-getid) () const<br> |
|  bool | [**HasId**](#function-hasid) () const<br> |
|  void | [**Join**](#function-join) () <br> |
|  SR\_NODISCARD bool | [**Joinable**](#function-joinable) () const<br> |
|  SR\_NODISCARD bool | [**Run**](#function-run-12) (Functor && fn) <br> |
|  bool | [**Run**](#function-run-22) (Functor && fn) <br> |
|  void | [**SetName**](#function-setname) (const std::string & name) <br> |
|  void | [**SetPriority**](#function-setpriority) (ThreadPriority priority) <br> |
|  void | [**Synchronize**](#function-synchronize) () <br> |
|  bool | [**TryJoin**](#function-tryjoin) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD ThreadId | [**EmptyThreadId**](#function-emptythreadid) () <br> |
|  void | [**Sleep**](#function-sleep) (uint64\_t milliseconds) <br> |


























## Public Types Documentation




### typedef Ptr 

```C++
using SR_HTYPES_NS::Thread::Ptr =  Thread*;
```




<hr>



### typedef ThreadId 

```C++
using SR_HTYPES_NS::Thread::ThreadId =  SR_UTILS_NS::StringAtom;
```




<hr>



### typedef ThreadsMap 

```C++
using SR_HTYPES_NS::Thread::ThreadsMap =  std::unordered_map<ThreadId, Thread::Ptr>;
```




<hr>
## Public Functions Documentation




### function Detach 

```C++
void SR_HTYPES_NS::Thread::Detach () 
```




<hr>



### function Execute 

```C++
bool SR_HTYPES_NS::Thread::Execute (
    const SR_HTYPES_NS::Function < bool()> & function
) const
```




<hr>



### function Free 

```C++
void SR_HTYPES_NS::Thread::Free () 
```




<hr>



### function GetContext 

```C++
SR_NODISCARD DataStorage * SR_HTYPES_NS::Thread::GetContext () 
```




<hr>



### function GetId 

```C++
SR_NODISCARD ThreadId SR_HTYPES_NS::Thread::GetId () const
```




<hr>



### function HasId 

```C++
bool SR_HTYPES_NS::Thread::HasId () const
```




<hr>



### function Join 

```C++
void SR_HTYPES_NS::Thread::Join () 
```




<hr>



### function Joinable 

```C++
SR_NODISCARD bool SR_HTYPES_NS::Thread::Joinable () const
```




<hr>



### function Run [1/2]

```C++
template<class Functor, typename... Args>
SR_NODISCARD bool SR_HTYPES_NS::Thread::Run (
    Functor && fn
) 
```




<hr>



### function Run [2/2]

```C++
template<class Functor, typename... Args>
bool SR_HTYPES_NS::Thread::Run (
    Functor && fn
) 
```




<hr>



### function SetName 

```C++
void SR_HTYPES_NS::Thread::SetName (
    const std::string & name
) 
```




<hr>



### function SetPriority 

```C++
void SR_HTYPES_NS::Thread::SetPriority (
    ThreadPriority priority
) 
```




<hr>



### function Synchronize 

```C++
void SR_HTYPES_NS::Thread::Synchronize () 
```




<hr>



### function TryJoin 

```C++
bool SR_HTYPES_NS::Thread::TryJoin () 
```




<hr>
## Public Static Functions Documentation




### function EmptyThreadId 

```C++
static SR_NODISCARD ThreadId SR_HTYPES_NS::Thread::EmptyThreadId () 
```




<hr>



### function Sleep 

```C++
static void SR_HTYPES_NS::Thread::Sleep (
    uint64_t milliseconds
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/Thread.h`

