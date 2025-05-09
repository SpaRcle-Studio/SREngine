

# Class SR\_HTYPES\_NS::SharedPtr

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)



_SR\_COMMON\_DLL\_API._ 

* `#include <SharedPtr.h>`



Inherits the following classes: [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)


Inherited by the following classes: [SR\_ANIMATIONS\_NS::Bone](structSR__ANIMATIONS__NS_1_1Bone.md),  [SR\_CORE\_GUI\_NS::PropertyDrawerBase](classSR__CORE__GUI__NS_1_1PropertyDrawerBase.md),  [SR\_CORE\_NS::Application](classSR__CORE__NS_1_1Application.md),  [SR\_CORE\_NS::Engine](classSR__CORE__NS_1_1Engine.md),  [SR\_GRAPH\_GUI\_NS::WidgetContainerElement](classSR__GRAPH__GUI__NS_1_1WidgetContainerElement.md),  [SR\_GRAPH\_NS::BaseMaterial](classSR__GRAPH__NS_1_1BaseMaterial.md),  [SR\_GRAPH\_NS::FrameBufferController](classSR__GRAPH__NS_1_1FrameBufferController.md),  [SR\_GRAPH\_NS::IRenderer](classSR__GRAPH__NS_1_1IRenderer.md),  [SR\_GRAPH\_NS::MaterialData](classSR__GRAPH__NS_1_1MaterialData.md),  [SR\_GRAPH\_NS::Memory::BakedMesh](classSR__GRAPH__NS_1_1Memory_1_1BakedMesh.md),  [SR\_GRAPH\_NS::Overlay](classSR__GRAPH__NS_1_1Overlay.md),  [SR\_GRAPH\_NS::Pipeline](classSR__GRAPH__NS_1_1Pipeline.md),  [SR\_GRAPH\_NS::RenderQueue](classSR__GRAPH__NS_1_1RenderQueue.md),  [SR\_GRAPH\_NS::RenderScene](classSR__GRAPH__NS_1_1RenderScene.md),  [SR\_GRAPH\_NS::TextureData](classSR__GRAPH__NS_1_1TextureData.md),  [SR\_GRAPH\_NS::Window](classSR__GRAPH__NS_1_1Window.md),  [SR\_NETWORK\_NS::Acceptor](classSR__NETWORK__NS_1_1Acceptor.md),  [SR\_NETWORK\_NS::Client](classSR__NETWORK__NS_1_1Client.md),  [SR\_NETWORK\_NS::Context](classSR__NETWORK__NS_1_1Context.md),  [SR\_NETWORK\_NS::DataPackage](classSR__NETWORK__NS_1_1DataPackage.md),  [SR\_NETWORK\_NS::PeerToPeer](classSR__NETWORK__NS_1_1PeerToPeer.md),  [SR\_NETWORK\_NS::Server](classSR__NETWORK__NS_1_1Server.md),  [SR\_NETWORK\_NS::Socket](classSR__NETWORK__NS_1_1Socket.md),  [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md),  [SR\_SCRIPTING\_NS::CppBehaviour](classSR__SCRIPTING__NS_1_1CppBehaviour.md),  [SR\_SCRIPTING\_NS::CppCodeGenerator](classSR__SCRIPTING__NS_1_1CppCodeGenerator.md),  [SR\_SCRIPTING\_NS::CppCompiler](classSR__SCRIPTING__NS_1_1CppCompiler.md),  [SR\_SCRIPTING\_NS::ModuleManager](classSR__SCRIPTING__NS_1_1ModuleManager.md),  [SR\_SCRIPTING\_NS::ScriptHolder](classSR__SCRIPTING__NS_1_1ScriptHolder.md),  [SR\_UTILS\_NS::AutoTests::AutomaticallySharedPtrTestClass](classSR__UTILS__NS_1_1AutoTests_1_1AutomaticallySharedPtrTestClass.md),  [SR\_UTILS\_NS::AutoTests::ManuallySharedPtrTestClass](classSR__UTILS__NS_1_1AutoTests_1_1ManuallySharedPtrTestClass.md),  [SR\_UTILS\_NS::EntityController](classSR__UTILS__NS_1_1EntityController.md),  [SR\_UTILS\_NS::FileSystemWatcher](classSR__UTILS__NS_1_1FileSystemWatcher.md),  [SR\_UTILS\_NS::FileWatcher](classSR__UTILS__NS_1_1FileWatcher.md),  [SR\_UTILS\_NS::IMigrator](classSR__UTILS__NS_1_1IMigrator.md),  [SR\_UTILS\_NS::Tests::ReflectionTestComponentLogicBase](classSR__UTILS__NS_1_1Tests_1_1ReflectionTestComponentLogicBase.md),  [SR\_UTILS\_NS::ThreadWorker](classSR__UTILS__NS_1_1ThreadWorker.md),  [SR\_UTILS\_NS::ThreadWorkerStateBase](classSR__UTILS__NS_1_1ThreadWorkerStateBase.md),  [SR\_UTILS\_NS::ThreadsWorker](classSR__UTILS__NS_1_1ThreadsWorker.md),  [SR\_UTILS\_NS::Transform](classSR__UTILS__NS_1_1Transform.md),  [SR\_UTILS\_NS::Web::CSS](classSR__UTILS__NS_1_1Web_1_1CSS.md),  [SR\_UTILS\_NS::Web::HTMLContainerInterface](classSR__UTILS__NS_1_1Web_1_1HTMLContainerInterface.md),  [SR\_UTILS\_NS::Web::HTMLPage](classSR__UTILS__NS_1_1Web_1_1HTMLPage.md),  [SR\_WORLD\_NS::SceneLogic](classSR__WORLD__NS_1_1SceneLogic.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](#typedef-sharedpointertype)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](#function-dynamiccast) () const<br> |
|  SR\_NODISCARD const T \* | [**Get**](#function-get-12) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](#function-get-22) () <br> |
|  SR\_NODISCARD const void \* | [**GetRawPtr**](#function-getrawptr-12) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](#function-getrawptr-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](#function-getsrclass) () override const<br>_NOLINT(modernize-use-nodiscard)_  |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetThis**](#function-getthis) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T &SR\_FASTCALL | [**GetUncheckedRef**](#function-getuncheckedref-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T &SR\_FASTCALL | [**GetUncheckedRef**](#function-getuncheckedref-22) () <br> |
| virtual void | [**IncrementPointer**](#function-incrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**PolymorphicCast**](#function-polymorphiccast) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](#function-recursivelockifvalid) () noexcept const<br> |
|  U | [**ReinterpretCast**](#function-reinterpretcast) () <br> |
| virtual void | [**Reset**](#function-reset) () override<br> |
| virtual void | [**SetPointerFromBase**](#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) override<br> |
|   | [**SharedPtr**](#function-sharedptr-15) () = default<br> |
|   | [**SharedPtr**](#function-sharedptr-25) (const T \* constPtr) <br> |
|   | [**SharedPtr**](#function-sharedptr-35) (const T \* constPtr, SR\_UTILS\_NS::SharedPtrPolicy policy) <br> |
|   | [**SharedPtr**](#function-sharedptr-45) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) const & ptr) <br> |
|   | [**SharedPtr**](#function-sharedptr-55) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) && ptr) noexcept<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**StaticCast**](#function-staticcast) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](#function-tryrecursivelockifvalid) () noexcept const<br> |
|  void | [**Unlock**](#function-unlock) () noexcept const<br> |
|  bool | [**Valid**](#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](#function-operator_2) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](#function-operator_3) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](#function-operator_4) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](#function-operator_5) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](#function-operator_6) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|   | [**~SharedPtr**](#function-sharedptr) () override<br> |


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
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](#function-makeshared) (Args &&... args) <br> |














## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |






































## Public Types Documentation




### typedef Ptr 

```C++
using SR_HTYPES_NS::SharedPtr< T >::Ptr =  SharedPtr<T>;
```




<hr>



### typedef SharedPointerType 

```C++
using SR_HTYPES_NS::SharedPtr< T >::SharedPointerType =  T;
```




<hr>
## Public Functions Documentation




### function AutoFree [1/2]

```C++
bool SR_HTYPES_NS::SharedPtr::AutoFree (
    const SR_HTYPES_NS::Function < void(T *ptr)> & freeFun
) 
```




<hr>



### function AutoFree [2/2]

```C++
bool SR_HTYPES_NS::SharedPtr::AutoFree () 
```




<hr>



### function DecrementPointer 

```C++
inline virtual void SR_HTYPES_NS::SharedPtr::DecrementPointer () override
```



Implements [*SR\_HTYPES\_NS::SharedPtrBase::DecrementPointer*](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-decrementpointer)


<hr>



### function DynamicCast 

```C++
template<typename U>
inline SharedPtr < U > SR_HTYPES_NS::SharedPtr::DynamicCast () const
```




<hr>



### function Get [1/2]

```C++
inline SR_NODISCARD const T * SR_HTYPES_NS::SharedPtr::Get () const
```




<hr>



### function Get [2/2]

```C++
inline SR_NODISCARD T * SR_HTYPES_NS::SharedPtr::Get () 
```




<hr>



### function GetRawPtr [1/2]

```C++
inline SR_NODISCARD const void * SR_HTYPES_NS::SharedPtr::GetRawPtr () const
```




<hr>



### function GetRawPtr [2/2]

_NOLINT(modernize-use-nodiscard)_ 
```C++
inline SR_NODISCARD void * SR_HTYPES_NS::SharedPtr::GetRawPtr () 
```




<hr>



### function GetSRClass 

_NOLINT(modernize-use-nodiscard)_ 
```C++
inline virtual SR_NODISCARD SRClass * SR_HTYPES_NS::SharedPtr::GetSRClass () override const
```



Implements [*SR\_HTYPES\_NS::SharedPtrBase::GetSRClass*](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getsrclass)


<hr>



### function GetThis 

```C++
inline SR_NODISCARD SharedPtr < T > SR_HTYPES_NS::SharedPtr::GetThis () const
```




<hr>



### function GetUncheckedRef [1/2]

```C++
inline SR_NODISCARD SR_FORCE_INLINE const T &SR_FASTCALL SR_HTYPES_NS::SharedPtr::GetUncheckedRef () const
```




<hr>



### function GetUncheckedRef [2/2]

```C++
inline SR_NODISCARD SR_FORCE_INLINE T &SR_FASTCALL SR_HTYPES_NS::SharedPtr::GetUncheckedRef () 
```




<hr>



### function IncrementPointer 

```C++
inline virtual void SR_HTYPES_NS::SharedPtr::IncrementPointer () override
```



Implements [*SR\_HTYPES\_NS::SharedPtrBase::IncrementPointer*](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-incrementpointer)


<hr>



### function PolymorphicCast 

```C++
template<typename U>
inline SharedPtr < U > SR_HTYPES_NS::SharedPtr::PolymorphicCast () const
```




<hr>



### function RecursiveLockIfValid 

```C++
SR_NODISCARD bool SR_HTYPES_NS::SharedPtr::RecursiveLockIfValid () noexcept const
```




<hr>



### function ReinterpretCast 

```C++
template<typename U>
inline U SR_HTYPES_NS::SharedPtr::ReinterpretCast () 
```




<hr>



### function Reset 

```C++
virtual void SR_HTYPES_NS::SharedPtr::Reset () override
```



Implements [*SR\_HTYPES\_NS::SharedPtrBase::Reset*](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-reset)


<hr>



### function SetPointerFromBase 

```C++
inline virtual void SR_HTYPES_NS::SharedPtr::SetPointerFromBase (
    SharedPtrBase * pBase
) override
```



Implements [*SR\_HTYPES\_NS::SharedPtrBase::SetPointerFromBase*](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-setpointerfrombase)


<hr>



### function SharedPtr [1/5]

```C++
SR_HTYPES_NS::SharedPtr::SharedPtr () = default
```




<hr>



### function SharedPtr [2/5]

```C++
SR_HTYPES_NS::SharedPtr::SharedPtr (
    const T * constPtr
) 
```




<hr>



### function SharedPtr [3/5]

```C++
SR_HTYPES_NS::SharedPtr::SharedPtr (
    const T * constPtr,
    SR_UTILS_NS::SharedPtrPolicy policy
) 
```



NOLINT(google-explicit-constructor) 


        

<hr>



### function SharedPtr [4/5]

```C++
SR_HTYPES_NS::SharedPtr::SharedPtr (
    SharedPtr const & ptr
) 
```




<hr>



### function SharedPtr [5/5]

```C++
inline SR_HTYPES_NS::SharedPtr::SharedPtr (
    SharedPtr && ptr
) noexcept
```




<hr>



### function StaticCast 

```C++
template<typename U>
inline SharedPtr < U > SR_HTYPES_NS::SharedPtr::StaticCast () const
```




<hr>



### function TryRecursiveLockIfValid 

```C++
SR_NODISCARD bool SR_HTYPES_NS::SharedPtr::TryRecursiveLockIfValid () noexcept const
```




<hr>



### function Unlock 

```C++
inline void SR_HTYPES_NS::SharedPtr::Unlock () noexcept const
```




<hr>



### function Valid 

```C++
inline bool SR_HTYPES_NS::SharedPtr::Valid () const
```




<hr>



### function operator bool 

```C++
inline SR_NODISCARD SR_FORCE_INLINE SR_HTYPES_NS::SharedPtr::operator bool () noexcept const
```




<hr>



### function operator!= 

```C++
inline SR_INLINE bool SR_HTYPES_NS::SharedPtr::operator!= (
    const SharedPtr < T > & right
) const
```




<hr>



### function operator\* 

```C++
inline SR_FORCE_INLINE T & SR_HTYPES_NS::SharedPtr::operator* () const
```




<hr>



### function operator-&gt; 

```C++
inline SR_FORCE_INLINE T * SR_HTYPES_NS::SharedPtr::operator-> () const
```




<hr>



### function operator= 

```C++
SharedPtr < T > & SR_HTYPES_NS::SharedPtr::operator= (
    const SharedPtr < T > & ptr
) 
```



NOLINT 


        

<hr>



### function operator= 

```C++
SharedPtr < T > & SR_HTYPES_NS::SharedPtr::operator= (
    T * ptr
) 
```




<hr>



### function operator= 

```C++
inline SharedPtr < T > & SR_HTYPES_NS::SharedPtr::operator= (
    SharedPtr < T > && ptr
) noexcept
```




<hr>



### function operator== 

```C++
inline SR_INLINE bool SR_HTYPES_NS::SharedPtr::operator== (
    const SharedPtr < T > & right
) const
```




<hr>



### function ~SharedPtr 

```C++
SR_HTYPES_NS::SharedPtr::~SharedPtr () override
```




<hr>
## Public Static Functions Documentation




### function MakeShared 

```C++
template<typename U, typename R, typename... Args>
static inline SR_NODISCARD SharedPtr < R > SR_HTYPES_NS::SharedPtr::MakeShared (
    Args &&... args
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/SharedPtr.h`

