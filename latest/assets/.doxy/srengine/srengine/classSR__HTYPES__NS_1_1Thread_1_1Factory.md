

# Class SR\_HTYPES\_NS::Thread::Factory



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**Thread**](classSR__HTYPES__NS_1_1Thread.md) **>** [**Factory**](classSR__HTYPES__NS_1_1Thread_1_1Factory.md)








Inherits the following classes: Singleton< Factory >


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_DEPRECATED\_EX("Not safe, use Create([**Ptr**](classSR__HTYPES__NS_1_1Thread.md)& pThread, Functor&& fn, Args&&... args)") SR\_NODISCARD [**Ptr**](classSR__HTYPES__NS_1_1Thread.md) Create(std SR\_DEPRECATED\_EX("Not safe, use Create([**Ptr**](classSR__HTYPES__NS_1_1Thread.md)& pThread, Functor&& fn, Args&&... args)") SR\_NODISCARD [**Ptr**](classSR__HTYPES__NS_1_1Thread.md) Create(const std SR\_NODISCARD uint32\_t | [**GetThreadsCount**](#variable-getthreadscount)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Create**](#function-create) ([**Ptr**](classSR__HTYPES__NS_1_1Thread.md) & pThread, Functor && fn, Args &&... args) <br> |
|  SR\_NODISCARD [**Ptr**](classSR__HTYPES__NS_1_1Thread.md) | [**CreateEmpty**](#function-createempty) () <br> |
|  void | [**DeInitialize**](#function-deinitialize) () <br> |
|  SR\_NODISCARD [**Ptr**](classSR__HTYPES__NS_1_1Thread.md) | [**GetMainThread**](#function-getmainthread) () <br> |
|  SR\_NODISCARD [**Ptr**](classSR__HTYPES__NS_1_1Thread.md) | [**GetThisThread**](#function-getthisthread) () <br> |
|  bool | [**IsSingletonCanBeDestroyed**](#function-issingletoncanbedestroyed) () override const<br> |
|  void | [**PrintThreads**](#function-printthreads) () <br> |
|  void | [**SetMainThread**](#function-setmainthread) () <br> |
|  SR\_NODISCARD [**Ptr**](classSR__HTYPES__NS_1_1Thread.md) | [**TryGetThisThread**](#function-trygetthisthread) () <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**Factory**](#function-factory) () <br> |
|   | [**~Factory**](#function-factory) () override<br> |




## Public Attributes Documentation




### variable GetThreadsCount 

```C++
SR_DEPRECATED_EX("Not safe, use Create(Ptr& pThread, Functor&& fn, Args&&... args)") SR_NODISCARD Ptr Create(std SR_DEPRECATED_EX("Not safe, use Create(Ptr& pThread, Functor&& fn, Args&&... args)") SR_NODISCARD Ptr Create(const std SR_NODISCARD uint32_t SR_HTYPES_NS::Thread::Factory::GetThreadsCount();
```




<hr>
## Public Functions Documentation




### function Create 

```C++
template<class Functor, typename... Args>
bool SR_HTYPES_NS::Thread::Factory::Create (
    Ptr & pThread,
    Functor && fn,
    Args &&... args
) 
```




<hr>



### function CreateEmpty 

```C++
SR_NODISCARD Ptr SR_HTYPES_NS::Thread::Factory::CreateEmpty () 
```




<hr>



### function DeInitialize 

```C++
void SR_HTYPES_NS::Thread::Factory::DeInitialize () 
```




<hr>



### function GetMainThread 

```C++
SR_NODISCARD Ptr SR_HTYPES_NS::Thread::Factory::GetMainThread () 
```




<hr>



### function GetThisThread 

```C++
SR_NODISCARD Ptr SR_HTYPES_NS::Thread::Factory::GetThisThread () 
```




<hr>



### function IsSingletonCanBeDestroyed 

```C++
inline bool SR_HTYPES_NS::Thread::Factory::IsSingletonCanBeDestroyed () override const
```




<hr>



### function PrintThreads 

```C++
void SR_HTYPES_NS::Thread::Factory::PrintThreads () 
```




<hr>



### function SetMainThread 

```C++
void SR_HTYPES_NS::Thread::Factory::SetMainThread () 
```




<hr>



### function TryGetThisThread 

```C++
SR_NODISCARD Ptr SR_HTYPES_NS::Thread::Factory::TryGetThisThread () 
```




<hr>
## Protected Functions Documentation




### function Factory 

```C++
SR_HTYPES_NS::Thread::Factory::Factory () 
```




<hr>



### function ~Factory 

```C++
SR_HTYPES_NS::Thread::Factory::~Factory () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/Thread.h`

