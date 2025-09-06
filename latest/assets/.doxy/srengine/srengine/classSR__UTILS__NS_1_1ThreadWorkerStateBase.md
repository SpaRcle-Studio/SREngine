

# Class SR\_UTILS\_NS::ThreadWorkerStateBase



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ThreadWorkerStateBase**](classSR__UTILS__NS_1_1ThreadWorkerStateBase.md)








Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)


Inherited by the following classes: [SR\_CORE\_NS::ChunkSystemState](classSR__CORE__NS_1_1ChunkSystemState.md),  [SR\_CORE\_NS::DeltaTimeState](classSR__CORE__NS_1_1DeltaTimeState.md),  [SR\_CORE\_NS::DrawState](classSR__CORE__NS_1_1DrawState.md),  [SR\_CORE\_NS::InitializeState](classSR__CORE__NS_1_1InitializeState.md),  [SR\_CORE\_NS::PollEventsState](classSR__CORE__NS_1_1PollEventsState.md),  [SR\_CORE\_NS::PrepareState](classSR__CORE__NS_1_1PrepareState.md),  [SR\_CORE\_NS::SceneUpdateState](classSR__CORE__NS_1_1SceneUpdateState.md),  [SR\_CORE\_NS::StopState](classSR__CORE__NS_1_1StopState.md),  [SR\_CORE\_NS::SubmitState](classSR__CORE__NS_1_1SubmitState.md)














## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddFinishCondition**](#function-addfinishcondition) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, ThreadWorkerState state) <br> |
|  void | [**AddSkipCondition**](#function-addskipcondition) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, ThreadWorkerState state) <br> |
|  void | [**AddStartCondition**](#function-addstartcondition) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, ThreadWorkerState state) <br> |
|  ThreadWorkerResult | [**Execute**](#function-execute) () <br> |
|  void | [**Finalize**](#function-finalize) () <br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) & | [**GetContext**](#function-getcontext) () <br> |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname) () const = 0<br> |
|  SR\_NODISCARD ThreadWorkerState | [**GetState**](#function-getstate) () const<br> |
|  SR\_NODISCARD [**ThreadWorker**](classSR__UTILS__NS_1_1ThreadWorker.md) \* | [**GetThreadWorker**](#function-getthreadworker) () const<br> |
|  SR\_NODISCARD [**ThreadsWorker**](classSR__UTILS__NS_1_1ThreadsWorker.md) \* | [**GetThreadsWorker**](#function-getthreadsworker) () const<br> |
|  void | [**SetThreadWorker**](#function-setthreadworker) ([**ThreadWorker**](classSR__UTILS__NS_1_1ThreadWorker.md) \* pThreadWorker) <br> |
|   | [**ThreadWorkerStateBase**](#function-threadworkerstatebase) () <br> |
| virtual  | [**~ThreadWorkerStateBase**](#function-threadworkerstatebase) () = default<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
|  SR\_NODISCARD const void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-12) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br> |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getthis) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-22) () <br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-incrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**PolymorphicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-polymorphiccast) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-recursivelockifvalid) () noexcept const<br> |
|  U | [**ReinterpretCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reinterpretcast) () <br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reset) () override<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtr.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) override<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-15) () = default<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-25) (const T \* constPtr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-35) (const T \* constPtr, SR\_UTILS\_NS::SharedPtrPolicy policy) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-45) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) const & ptr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-55) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) && ptr) noexcept<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**StaticCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-staticcast) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-tryrecursivelockifvalid) () noexcept const<br> |
|  void | [**Unlock**](classSR__HTYPES__NS_1_1SharedPtr.md#function-unlock) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_2) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_3) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_4) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_5) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|   | [**~SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-decrementpointer) () = 0<br> |
|  const [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-12) () const<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getsrclass) () const = 0<br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-incrementpointer) () = 0<br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-reset) () = 0<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) = 0<br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-12) () <br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-22) ([**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* data) <br> |
| virtual SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-valid) () const = 0<br> |
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |




## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |




















## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |












































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual ThreadWorkerResult | [**ExecuteImpl**](#function-executeimpl) () = 0<br> |
| virtual void | [**FinalizeImpl**](#function-finalizeimpl) () <br> |












## Public Functions Documentation




### function AddFinishCondition 

```C++
void SR_UTILS_NS::ThreadWorkerStateBase::AddFinishCondition (
    SR_UTILS_NS::StringAtom name,
    ThreadWorkerState state
) 
```




<hr>



### function AddSkipCondition 

```C++
void SR_UTILS_NS::ThreadWorkerStateBase::AddSkipCondition (
    SR_UTILS_NS::StringAtom name,
    ThreadWorkerState state
) 
```




<hr>



### function AddStartCondition 

```C++
void SR_UTILS_NS::ThreadWorkerStateBase::AddStartCondition (
    SR_UTILS_NS::StringAtom name,
    ThreadWorkerState state
) 
```




<hr>



### function Execute 

```C++
ThreadWorkerResult SR_UTILS_NS::ThreadWorkerStateBase::Execute () 
```




<hr>



### function Finalize 

```C++
void SR_UTILS_NS::ThreadWorkerStateBase::Finalize () 
```




<hr>



### function GetContext 

```C++
SR_NODISCARD SR_HTYPES_NS::DataStorage & SR_UTILS_NS::ThreadWorkerStateBase::GetContext () 
```




<hr>



### function GetName 

```C++
virtual StringAtom SR_UTILS_NS::ThreadWorkerStateBase::GetName () const = 0
```




<hr>



### function GetState 

```C++
inline SR_NODISCARD ThreadWorkerState SR_UTILS_NS::ThreadWorkerStateBase::GetState () const
```




<hr>



### function GetThreadWorker 

```C++
inline SR_NODISCARD ThreadWorker * SR_UTILS_NS::ThreadWorkerStateBase::GetThreadWorker () const
```




<hr>



### function GetThreadsWorker 

```C++
SR_NODISCARD ThreadsWorker * SR_UTILS_NS::ThreadWorkerStateBase::GetThreadsWorker () const
```




<hr>



### function SetThreadWorker 

```C++
inline void SR_UTILS_NS::ThreadWorkerStateBase::SetThreadWorker (
    ThreadWorker * pThreadWorker
) 
```




<hr>



### function ThreadWorkerStateBase 

```C++
SR_UTILS_NS::ThreadWorkerStateBase::ThreadWorkerStateBase () 
```




<hr>



### function ~ThreadWorkerStateBase 

```C++
virtual SR_UTILS_NS::ThreadWorkerStateBase::~ThreadWorkerStateBase () = default
```




<hr>
## Protected Functions Documentation




### function ExecuteImpl 

```C++
virtual ThreadWorkerResult SR_UTILS_NS::ThreadWorkerStateBase::ExecuteImpl () = 0
```




<hr>



### function FinalizeImpl 

```C++
inline virtual void SR_UTILS_NS::ThreadWorkerStateBase::FinalizeImpl () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/TaskManager/ThreadWorker.h`

