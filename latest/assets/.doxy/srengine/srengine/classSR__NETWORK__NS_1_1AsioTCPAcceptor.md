

# Class SR\_NETWORK\_NS::AsioTCPAcceptor



[**ClassList**](annotated.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md) **>** [**AsioTCPAcceptor**](classSR__NETWORK__NS_1_1AsioTCPAcceptor.md)








Inherits the following classes: [SR\_NETWORK\_NS::Acceptor](classSR__NETWORK__NS_1_1Acceptor.md)
















## Public Types inherited from SR_NETWORK_NS::Acceptor

See [SR\_NETWORK\_NS::Acceptor](classSR__NETWORK__NS_1_1Acceptor.md)

| Type | Name |
| ---: | :--- |
| typedef std::function&lt; void([**Socket::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md))&gt; | [**Callback**](classSR__NETWORK__NS_1_1Acceptor.md#typedef-callback)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |












































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Close**](#function-close) () override<br> |
| virtual SR\_NODISCARD std::string | [**GetLocalAddress**](#function-getlocaladdress) () override const<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetLocalPort**](#function-getlocalport) () override const<br> |
| virtual SR\_NODISCARD std::string | [**GetRemoteAddress**](#function-getremoteaddress) () override const<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetRemotePort**](#function-getremoteport) () override const<br> |
|   | [**~AsioTCPAcceptor**](#function-asiotcpacceptor) () override<br> |


## Public Functions inherited from SR_NETWORK_NS::Acceptor

See [SR\_NETWORK\_NS::Acceptor](classSR__NETWORK__NS_1_1Acceptor.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Close**](classSR__NETWORK__NS_1_1Acceptor.md#function-close) () <br> |
| virtual SR\_NODISCARD std::string | [**GetLocalAddress**](classSR__NETWORK__NS_1_1Acceptor.md#function-getlocaladdress) () const = 0<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetLocalPort**](classSR__NETWORK__NS_1_1Acceptor.md#function-getlocalport) () const = 0<br> |
| virtual SR\_NODISCARD std::string | [**GetRemoteAddress**](classSR__NETWORK__NS_1_1Acceptor.md#function-getremoteaddress) () const = 0<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetRemotePort**](classSR__NETWORK__NS_1_1Acceptor.md#function-getremoteport) () const = 0<br> |
| virtual SR\_NODISCARD bool | [**Init**](classSR__NETWORK__NS_1_1Acceptor.md#function-init) () = 0<br> |
|  SR\_NODISCARD bool | [**IsOpen**](classSR__NETWORK__NS_1_1Acceptor.md#function-isopen) () const<br> |
|  SR\_NODISCARD bool | [**IsRepeated**](classSR__NETWORK__NS_1_1Acceptor.md#function-isrepeated) () const<br> |
|  SR\_NODISCARD bool | [**IsWaitingAccept**](classSR__NETWORK__NS_1_1Acceptor.md#function-iswaitingaccept) () const<br> |
|  void | [**SetCallback**](classSR__NETWORK__NS_1_1Acceptor.md#function-setcallback) (Callback && callback) <br> |
|  void | [**SetRepeated**](classSR__NETWORK__NS_1_1Acceptor.md#function-setrepeated) (bool isRepeated) <br> |
|  bool | [**Start**](classSR__NETWORK__NS_1_1Acceptor.md#function-start) () <br> |
|  bool | [**StartAsync**](classSR__NETWORK__NS_1_1Acceptor.md#function-startasync) () <br> |
| virtual  | [**~Acceptor**](classSR__NETWORK__NS_1_1Acceptor.md#function-acceptor) () = default<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
|  SR\_NODISCARD const void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-12) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br>_NOLINT(modernize-use-nodiscard)_  |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getthis) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-22) () <br> |
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
|  const [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-12) () const<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getsrclass) () const = 0<br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-reset) () = 0<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) = 0<br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-12) () = default<br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-22) ([**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* data) <br> |
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () = default<br> |






## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |






















## Protected Attributes inherited from SR_NETWORK_NS::Acceptor

See [SR\_NETWORK\_NS::Acceptor](classSR__NETWORK__NS_1_1Acceptor.md)

| Type | Name |
| ---: | :--- |
|  std::string | [**m\_address**](classSR__NETWORK__NS_1_1Acceptor.md#variable-m_address)  <br> |
|  Callback | [**m\_callback**](classSR__NETWORK__NS_1_1Acceptor.md#variable-m_callback)  <br> |
|  [**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**m\_context**](classSR__NETWORK__NS_1_1Acceptor.md#variable-m_context)  <br> |
|  bool | [**m\_isOpen**](classSR__NETWORK__NS_1_1Acceptor.md#variable-m_isopen)   = `false`<br> |
|  bool | [**m\_isRepeated**](classSR__NETWORK__NS_1_1Acceptor.md#variable-m_isrepeated)   = `true`<br> |
|  bool | [**m\_isWaitingAccept**](classSR__NETWORK__NS_1_1Acceptor.md#variable-m_iswaitingaccept)   = `false`<br> |
|  uint16\_t | [**m\_port**](classSR__NETWORK__NS_1_1Acceptor.md#variable-m_port)   = `0`<br> |
|  const SocketType | [**m\_type**](classSR__NETWORK__NS_1_1Acceptor.md#variable-m_type)   = `SocketType::Unknown`<br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |




























































## Protected Functions inherited from SR_NETWORK_NS::Acceptor

See [SR\_NETWORK\_NS::Acceptor](classSR__NETWORK__NS_1_1Acceptor.md)

| Type | Name |
| ---: | :--- |
|   | [**Acceptor**](classSR__NETWORK__NS_1_1Acceptor.md#function-acceptor) (SocketType type, [**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) pContext, std::string address, uint16\_t port) <br> |
| virtual bool | [**StartInternal**](classSR__NETWORK__NS_1_1Acceptor.md#function-startinternal) (bool async) = 0<br> |














## Public Functions Documentation




### function Close 

```C++
virtual void SR_NETWORK_NS::AsioTCPAcceptor::Close () override
```



Implements [*SR\_NETWORK\_NS::Acceptor::Close*](classSR__NETWORK__NS_1_1Acceptor.md#function-close)


<hr>



### function GetLocalAddress 

```C++
virtual SR_NODISCARD std::string SR_NETWORK_NS::AsioTCPAcceptor::GetLocalAddress () override const
```



Implements [*SR\_NETWORK\_NS::Acceptor::GetLocalAddress*](classSR__NETWORK__NS_1_1Acceptor.md#function-getlocaladdress)


<hr>



### function GetLocalPort 

```C++
virtual SR_NODISCARD uint16_t SR_NETWORK_NS::AsioTCPAcceptor::GetLocalPort () override const
```



Implements [*SR\_NETWORK\_NS::Acceptor::GetLocalPort*](classSR__NETWORK__NS_1_1Acceptor.md#function-getlocalport)


<hr>



### function GetRemoteAddress 

```C++
virtual SR_NODISCARD std::string SR_NETWORK_NS::AsioTCPAcceptor::GetRemoteAddress () override const
```



Implements [*SR\_NETWORK\_NS::Acceptor::GetRemoteAddress*](classSR__NETWORK__NS_1_1Acceptor.md#function-getremoteaddress)


<hr>



### function GetRemotePort 

```C++
virtual SR_NODISCARD uint16_t SR_NETWORK_NS::AsioTCPAcceptor::GetRemotePort () override const
```



Implements [*SR\_NETWORK\_NS::Acceptor::GetRemotePort*](classSR__NETWORK__NS_1_1Acceptor.md#function-getremoteport)


<hr>



### function ~AsioTCPAcceptor 

```C++
SR_NETWORK_NS::AsioTCPAcceptor::~AsioTCPAcceptor () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Network/Asio/AsioTCPAcceptor.h`

