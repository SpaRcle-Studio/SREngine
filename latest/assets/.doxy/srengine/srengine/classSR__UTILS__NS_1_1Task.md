

# Class SR\_UTILS\_NS::Task



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Task**](classSR__UTILS__NS_1_1Task.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**State**](#enum-state)  <br> |
| typedef std::atomic&lt; State &gt; \* | [**StatePtr**](#typedef-stateptr)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(StatePtr)&gt; | [**TaskFn**](#typedef-taskfn)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD uint64\_t | [**GetId**](#function-getid) () const<br> |
|  SR\_NODISCARD State | [**GetResult**](#function-getresult) () const<br> |
|  SR\_NODISCARD bool | [**IsCompleted**](#function-iscompleted) () const<br> |
|  SR\_NODISCARD bool | [**IsWaiting**](#function-iswaiting) () const<br> |
|  bool | [**Run**](#function-run) () <br> |
|  void | [**SetId**](#function-setid) (uint64\_t id) <br> |
|  bool | [**Stop**](#function-stop) () <br> |
|   | [**Task**](#function-task-12) (TaskFn fn, bool createThread) <br> |
|   | [**Task**](#function-task-22) ([**Task**](classSR__UTILS__NS_1_1Task.md) && task) noexcept<br> |
|  [**Task**](classSR__UTILS__NS_1_1Task.md) & | [**operator=**](#function-operator) ([**Task**](classSR__UTILS__NS_1_1Task.md) && task) noexcept<br> |
|   | [**~Task**](#function-task) () override<br> |


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






## Public Types Documentation




### enum State 

```C++
enum SR_UTILS_NS::Task::State {
    Unknown,
    Waiting,
    Launched,
    Stopped,
    Completed,
    Failed
};
```




<hr>



### typedef StatePtr 

```C++
using SR_UTILS_NS::Task::StatePtr =  std::atomic<State>*;
```




<hr>



### typedef TaskFn 

```C++
using SR_UTILS_NS::Task::TaskFn =  SR_HTYPES_NS::Function<void(StatePtr)>;
```




<hr>
## Public Functions Documentation




### function GetId 

```C++
SR_NODISCARD uint64_t SR_UTILS_NS::Task::GetId () const
```




<hr>



### function GetResult 

```C++
SR_NODISCARD State SR_UTILS_NS::Task::GetResult () const
```




<hr>



### function IsCompleted 

```C++
SR_NODISCARD bool SR_UTILS_NS::Task::IsCompleted () const
```




<hr>



### function IsWaiting 

```C++
SR_NODISCARD bool SR_UTILS_NS::Task::IsWaiting () const
```




<hr>



### function Run 

```C++
bool SR_UTILS_NS::Task::Run () 
```




<hr>



### function SetId 

```C++
void SR_UTILS_NS::Task::SetId (
    uint64_t id
) 
```




<hr>



### function Stop 

```C++
bool SR_UTILS_NS::Task::Stop () 
```




<hr>



### function Task [1/2]

```C++
explicit SR_UTILS_NS::Task::Task (
    TaskFn fn,
    bool createThread
) 
```




<hr>



### function Task [2/2]

```C++
SR_UTILS_NS::Task::Task (
    Task && task
) noexcept
```




<hr>



### function operator= 

```C++
Task & SR_UTILS_NS::Task::operator= (
    Task && task
) noexcept
```




<hr>



### function ~Task 

```C++
SR_UTILS_NS::Task::~Task () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/TaskManager/TaskManager.h`

