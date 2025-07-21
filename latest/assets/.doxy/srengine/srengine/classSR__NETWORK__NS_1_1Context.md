

# Class SR\_NETWORK\_NS::Context



[**ClassList**](annotated.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md) **>** [**Context**](classSR__NETWORK__NS_1_1Context.md)








Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)


Inherited by the following classes: [SR\_NETWORK\_NS::AsioContext](classSR__NETWORK__NS_1_1AsioContext.md)














## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddAsyncAcceptor**](#function-addasyncacceptor) (const AcceptorPtr & pAcceptor) <br> |
|  void | [**AddAsyncReceiveSocket**](#function-addasyncreceivesocket) (const SocketPtr & pSocket) <br> |
|  void | [**AddAsyncSendKnownHostsSocket**](#function-addasyncsendknownhostssocket) (const PeerToPeerPtr & pP2P, const SocketPtr & pSocket) <br> |
| virtual SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Acceptor**](classSR__NETWORK__NS_1_1Acceptor.md) &gt; | [**CreateAcceptor**](#function-createacceptor) (SocketType type, const std::string & address, uint16\_t port) = 0<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**PeerToPeer**](classSR__NETWORK__NS_1_1PeerToPeer.md) &gt; | [**CreateP2P**](#function-createp2p) (SocketType type, const std::string & address, uint16\_t port) <br> |
| virtual SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pinger**](classSR__NETWORK__NS_1_1Pinger.md) &gt; | [**CreatePinger**](#function-createpinger) () = 0<br> |
| virtual SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Socket**](classSR__NETWORK__NS_1_1Socket.md) &gt; | [**CreateSocket**](#function-createsocket) (SocketType type) = 0<br> |
| virtual bool | [**Poll**](#function-poll) () <br> |
| virtual bool | [**Run**](#function-run) () = 0<br> |
| virtual void | [**Stop**](#function-stop) () = 0<br> |
| virtual  | [**~Context**](#function-context) () = default<br> |


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
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br>_NOLINT(modernize-use-nodiscard)_  |
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
|  bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_2) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_3) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_4) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_5) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_6) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
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
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Context**](classSR__NETWORK__NS_1_1Context.md) &gt; | [**Create**](#function-create) () <br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Context**](classSR__NETWORK__NS_1_1Context.md) &gt; | [**CreateAndRun**](#function-createandrun) () <br> |


## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |
















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::list&lt; AcceptorPtr &gt; | [**m\_asyncAcceptors**](#variable-m_asyncacceptors)  <br> |
|  std::list&lt; SocketPtr &gt; | [**m\_asyncReceiveSockets**](#variable-m_asyncreceivesockets)  <br> |
|  std::list&lt; std::pair&lt; PeerToPeerPtr, SocketPtr &gt; &gt; | [**m\_asyncSendKnownHostsSockets**](#variable-m_asyncsendknownhostssockets)  <br> |
|  bool | [**m\_isRunning**](#variable-m_isrunning)   = `false`<br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |












































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**Context**](#function-context) () <br> |












## Public Functions Documentation




### function AddAsyncAcceptor 

```C++
void SR_NETWORK_NS::Context::AddAsyncAcceptor (
    const AcceptorPtr & pAcceptor
) 
```




<hr>



### function AddAsyncReceiveSocket 

```C++
void SR_NETWORK_NS::Context::AddAsyncReceiveSocket (
    const SocketPtr & pSocket
) 
```




<hr>



### function AddAsyncSendKnownHostsSocket 

```C++
void SR_NETWORK_NS::Context::AddAsyncSendKnownHostsSocket (
    const PeerToPeerPtr & pP2P,
    const SocketPtr & pSocket
) 
```




<hr>



### function CreateAcceptor 

```C++
virtual SR_NODISCARD SR_HTYPES_NS::SharedPtr < Acceptor > SR_NETWORK_NS::Context::CreateAcceptor (
    SocketType type,
    const std::string & address,
    uint16_t port
) = 0
```




<hr>



### function CreateP2P 

```C++
SR_NODISCARD SR_HTYPES_NS::SharedPtr < PeerToPeer > SR_NETWORK_NS::Context::CreateP2P (
    SocketType type,
    const std::string & address,
    uint16_t port
) 
```




<hr>



### function CreatePinger 

```C++
virtual SR_NODISCARD SR_HTYPES_NS::SharedPtr < Pinger > SR_NETWORK_NS::Context::CreatePinger () = 0
```




<hr>



### function CreateSocket 

```C++
virtual SR_NODISCARD SR_HTYPES_NS::SharedPtr < Socket > SR_NETWORK_NS::Context::CreateSocket (
    SocketType type
) = 0
```




<hr>



### function Poll 

```C++
virtual bool SR_NETWORK_NS::Context::Poll () 
```




<hr>



### function Run 

```C++
virtual bool SR_NETWORK_NS::Context::Run () = 0
```




<hr>



### function Stop 

```C++
virtual void SR_NETWORK_NS::Context::Stop () = 0
```




<hr>



### function ~Context 

```C++
virtual SR_NETWORK_NS::Context::~Context () = default
```




<hr>
## Public Static Functions Documentation




### function Create 

```C++
static SR_NODISCARD SR_HTYPES_NS::SharedPtr < Context > SR_NETWORK_NS::Context::Create () 
```




<hr>



### function CreateAndRun 

```C++
static SR_NODISCARD SR_HTYPES_NS::SharedPtr < Context > SR_NETWORK_NS::Context::CreateAndRun () 
```




<hr>
## Protected Attributes Documentation




### variable m\_asyncAcceptors 

```C++
std::list<AcceptorPtr> SR_NETWORK_NS::Context::m_asyncAcceptors;
```




<hr>



### variable m\_asyncReceiveSockets 

```C++
std::list<SocketPtr> SR_NETWORK_NS::Context::m_asyncReceiveSockets;
```




<hr>



### variable m\_asyncSendKnownHostsSockets 

```C++
std::list<std::pair<PeerToPeerPtr, SocketPtr> > SR_NETWORK_NS::Context::m_asyncSendKnownHostsSockets;
```




<hr>



### variable m\_isRunning 

```C++
bool SR_NETWORK_NS::Context::m_isRunning;
```




<hr>
## Protected Functions Documentation




### function Context 

```C++
SR_NETWORK_NS::Context::Context () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Network/Context.h`

