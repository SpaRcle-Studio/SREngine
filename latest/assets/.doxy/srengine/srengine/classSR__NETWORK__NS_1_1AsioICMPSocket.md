

# Class SR\_NETWORK\_NS::AsioICMPSocket



[**ClassList**](annotated.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md) **>** [**AsioICMPSocket**](classSR__NETWORK__NS_1_1AsioICMPSocket.md)








Inherits the following classes: [SR\_NETWORK\_NS::Socket](classSR__NETWORK__NS_1_1Socket.md)


















## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |












































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD uint64\_t | [**AsyncReceive**](#function-asyncreceive) (void \* data, std::function&lt; void(uint64\_t bytesReceived)&gt; callback) override<br> |
|  bool | [**Bind**](#function-bind) (uint16\_t port) <br> |
| virtual bool | [**Close**](#function-close) () override<br> |
| virtual bool | [**Connect**](#function-connect) (const std::string & address, uint16\_t port) override<br> |
| virtual SR\_NODISCARD std::string | [**GetLocalAddress**](#function-getlocaladdress) () override const<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetLocalPort**](#function-getlocalport) () override const<br> |
| virtual SR\_NODISCARD std::string | [**GetRemoteAddress**](#function-getremoteaddress) () override const<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetRemotePort**](#function-getremoteport) () override const<br> |
| virtual SR\_NODISCARD bool | [**IsOpen**](#function-isopen) () override const<br> |
|  bool | [**Listen**](#function-listen) (int32\_t backlog) <br> |
| virtual SR\_NODISCARD uint64\_t | [**Receive**](#function-receive) (void \* data, size\_t size) override<br> |
| virtual bool | [**Send**](#function-send) (const void \* data, size\_t size) override<br> |
| virtual bool | [**SendTo**](#function-sendto) (const void \* data, uint64\_t size, const std::string & address, uint16\_t port) override<br> |
|   | [**~AsioICMPSocket**](#function-asioicmpsocket) () override<br> |


## Public Functions inherited from SR_NETWORK_NS::Socket

See [SR\_NETWORK\_NS::Socket](classSR__NETWORK__NS_1_1Socket.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AsyncReceive**](classSR__NETWORK__NS_1_1Socket.md#function-asyncreceive-12) (uint64\_t size) <br> |
| virtual SR\_NODISCARD uint64\_t | [**AsyncReceive**](classSR__NETWORK__NS_1_1Socket.md#function-asyncreceive-22) (void \* data, std::function&lt; void(uint64\_t bytesReceived)&gt; callback) = 0<br> |
| virtual bool | [**Close**](classSR__NETWORK__NS_1_1Socket.md#function-close) () = 0<br> |
| virtual SR\_NODISCARD bool | [**Connect**](classSR__NETWORK__NS_1_1Socket.md#function-connect) (const std::string & address, uint16\_t port) = 0<br> |
|  SR\_NODISCARD const [**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) & | [**GetContext**](classSR__NETWORK__NS_1_1Socket.md#function-getcontext) () const<br> |
| virtual SR\_NODISCARD std::string | [**GetLocalAddress**](classSR__NETWORK__NS_1_1Socket.md#function-getlocaladdress) () const = 0<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetLocalPort**](classSR__NETWORK__NS_1_1Socket.md#function-getlocalport) () const = 0<br> |
|  SR\_NODISCARD const ReceiveCallback & | [**GetReceiveCallback**](classSR__NETWORK__NS_1_1Socket.md#function-getreceivecallback) () const<br> |
|  SR\_NODISCARD const [**DataPackage::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) & | [**GetReceivedAsyncData**](classSR__NETWORK__NS_1_1Socket.md#function-getreceivedasyncdata) () const<br> |
|  SR\_NODISCARD const [**DataPackage::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) & | [**GetReceivedData**](classSR__NETWORK__NS_1_1Socket.md#function-getreceiveddata) () const<br> |
| virtual SR\_NODISCARD std::string | [**GetRemoteAddress**](classSR__NETWORK__NS_1_1Socket.md#function-getremoteaddress) () const = 0<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetRemotePort**](classSR__NETWORK__NS_1_1Socket.md#function-getremoteport) () const = 0<br> |
|  SR\_NODISCARD SocketType | [**GetType**](classSR__NETWORK__NS_1_1Socket.md#function-gettype) () const<br> |
| virtual SR\_NODISCARD bool | [**IsOpen**](classSR__NETWORK__NS_1_1Socket.md#function-isopen) () const = 0<br> |
|  SR\_NODISCARD bool | [**IsReceiveRepeated**](classSR__NETWORK__NS_1_1Socket.md#function-isreceiverepeated) () const<br> |
|  SR\_NODISCARD [**DataPackage::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**Receive**](classSR__NETWORK__NS_1_1Socket.md#function-receive-12) (uint64\_t size) <br> |
| virtual SR\_NODISCARD uint64\_t | [**Receive**](classSR__NETWORK__NS_1_1Socket.md#function-receive-22) (void \* data, size\_t size) = 0<br> |
| virtual bool | [**Send**](classSR__NETWORK__NS_1_1Socket.md#function-send) (const void \* data, size\_t size) = 0<br> |
| virtual bool | [**SendTo**](classSR__NETWORK__NS_1_1Socket.md#function-sendto) (const void \* data, uint64\_t size, const std::string & address, uint16\_t port) = 0<br> |
|  void | [**SetReceiveCallback**](classSR__NETWORK__NS_1_1Socket.md#function-setreceivecallback) (ReceiveCallback && callback) <br> |
|  void | [**SetWaitingReceive**](classSR__NETWORK__NS_1_1Socket.md#function-setwaitingreceive) (bool isWaiting) <br> |
| virtual  | [**~Socket**](classSR__NETWORK__NS_1_1Socket.md#function-socket) () = default<br> |


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






















## Protected Attributes inherited from SR_NETWORK_NS::Socket

See [SR\_NETWORK\_NS::Socket](classSR__NETWORK__NS_1_1Socket.md)

| Type | Name |
| ---: | :--- |
|  [**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**m\_context**](classSR__NETWORK__NS_1_1Socket.md#variable-m_context)  <br> |
|  bool | [**m\_isReceiveRepeated**](classSR__NETWORK__NS_1_1Socket.md#variable-m_isreceiverepeated)   = `true`<br> |
|  bool | [**m\_isWaitingReceive**](classSR__NETWORK__NS_1_1Socket.md#variable-m_iswaitingreceive)   = `false`<br> |
|  ReceiveCallback | [**m\_receiveCallback**](classSR__NETWORK__NS_1_1Socket.md#variable-m_receivecallback)  <br> |
|  [**DataPackage::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**m\_receivedAsyncData**](classSR__NETWORK__NS_1_1Socket.md#variable-m_receivedasyncdata)  <br> |
|  [**DataPackage::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**m\_receivedData**](classSR__NETWORK__NS_1_1Socket.md#variable-m_receiveddata)  <br> |
|  const SocketType | [**m\_type**](classSR__NETWORK__NS_1_1Socket.md#variable-m_type)   = `SocketType::Unknown`<br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |


























































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**ReceiveAsyncInternal**](#function-receiveasyncinternal) () override<br> |
|  void | [**SetSocket**](#function-setsocket) (asio::ip::icmp::socket && socket) <br> |


## Protected Functions inherited from SR_NETWORK_NS::Socket

See [SR\_NETWORK\_NS::Socket](classSR__NETWORK__NS_1_1Socket.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**ReceiveAsyncInternal**](classSR__NETWORK__NS_1_1Socket.md#function-receiveasyncinternal) () = 0<br> |
|   | [**Socket**](classSR__NETWORK__NS_1_1Socket.md#function-socket) (SocketType type, [**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) context) <br> |














## Public Functions Documentation




### function AsyncReceive 

```C++
virtual SR_NODISCARD uint64_t SR_NETWORK_NS::AsioICMPSocket::AsyncReceive (
    void * data,
    std::function< void(uint64_t bytesReceived)> callback
) override
```



Implements [*SR\_NETWORK\_NS::Socket::AsyncReceive*](classSR__NETWORK__NS_1_1Socket.md#function-asyncreceive-22)


<hr>



### function Bind 

```C++
bool SR_NETWORK_NS::AsioICMPSocket::Bind (
    uint16_t port
) 
```




<hr>



### function Close 

```C++
virtual bool SR_NETWORK_NS::AsioICMPSocket::Close () override
```



Implements [*SR\_NETWORK\_NS::Socket::Close*](classSR__NETWORK__NS_1_1Socket.md#function-close)


<hr>



### function Connect 

```C++
virtual bool SR_NETWORK_NS::AsioICMPSocket::Connect (
    const std::string & address,
    uint16_t port
) override
```



Implements [*SR\_NETWORK\_NS::Socket::Connect*](classSR__NETWORK__NS_1_1Socket.md#function-connect)


<hr>



### function GetLocalAddress 

```C++
virtual SR_NODISCARD std::string SR_NETWORK_NS::AsioICMPSocket::GetLocalAddress () override const
```



Implements [*SR\_NETWORK\_NS::Socket::GetLocalAddress*](classSR__NETWORK__NS_1_1Socket.md#function-getlocaladdress)


<hr>



### function GetLocalPort 

```C++
virtual SR_NODISCARD uint16_t SR_NETWORK_NS::AsioICMPSocket::GetLocalPort () override const
```



Implements [*SR\_NETWORK\_NS::Socket::GetLocalPort*](classSR__NETWORK__NS_1_1Socket.md#function-getlocalport)


<hr>



### function GetRemoteAddress 

```C++
virtual SR_NODISCARD std::string SR_NETWORK_NS::AsioICMPSocket::GetRemoteAddress () override const
```



Implements [*SR\_NETWORK\_NS::Socket::GetRemoteAddress*](classSR__NETWORK__NS_1_1Socket.md#function-getremoteaddress)


<hr>



### function GetRemotePort 

```C++
virtual SR_NODISCARD uint16_t SR_NETWORK_NS::AsioICMPSocket::GetRemotePort () override const
```



Implements [*SR\_NETWORK\_NS::Socket::GetRemotePort*](classSR__NETWORK__NS_1_1Socket.md#function-getremoteport)


<hr>



### function IsOpen 

```C++
virtual SR_NODISCARD bool SR_NETWORK_NS::AsioICMPSocket::IsOpen () override const
```



Implements [*SR\_NETWORK\_NS::Socket::IsOpen*](classSR__NETWORK__NS_1_1Socket.md#function-isopen)


<hr>



### function Listen 

```C++
bool SR_NETWORK_NS::AsioICMPSocket::Listen (
    int32_t backlog
) 
```




<hr>



### function Receive 

```C++
virtual SR_NODISCARD uint64_t SR_NETWORK_NS::AsioICMPSocket::Receive (
    void * data,
    size_t size
) override
```



Implements [*SR\_NETWORK\_NS::Socket::Receive*](classSR__NETWORK__NS_1_1Socket.md#function-receive-22)


<hr>



### function Send 

```C++
virtual bool SR_NETWORK_NS::AsioICMPSocket::Send (
    const void * data,
    size_t size
) override
```



Implements [*SR\_NETWORK\_NS::Socket::Send*](classSR__NETWORK__NS_1_1Socket.md#function-send)


<hr>



### function SendTo 

```C++
virtual bool SR_NETWORK_NS::AsioICMPSocket::SendTo (
    const void * data,
    uint64_t size,
    const std::string & address,
    uint16_t port
) override
```



Implements [*SR\_NETWORK\_NS::Socket::SendTo*](classSR__NETWORK__NS_1_1Socket.md#function-sendto)


<hr>



### function ~AsioICMPSocket 

```C++
SR_NETWORK_NS::AsioICMPSocket::~AsioICMPSocket () override
```




<hr>
## Protected Functions Documentation




### function ReceiveAsyncInternal 

```C++
virtual bool SR_NETWORK_NS::AsioICMPSocket::ReceiveAsyncInternal () override
```



Implements [*SR\_NETWORK\_NS::Socket::ReceiveAsyncInternal*](classSR__NETWORK__NS_1_1Socket.md#function-receiveasyncinternal)


<hr>



### function SetSocket 

```C++
inline void SR_NETWORK_NS::AsioICMPSocket::SetSocket (
    asio::ip::icmp::socket && socket
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Network/Asio/AsioICMPSocket.h`

