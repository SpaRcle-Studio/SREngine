

# Class SR\_NETWORK\_NS::Acceptor



[**ClassList**](annotated.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md) **>** [**Acceptor**](classSR__NETWORK__NS_1_1Acceptor.md)








Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)


Inherited by the following classes: [SR\_NETWORK\_NS::AsioTCPAcceptor](classSR__NETWORK__NS_1_1AsioTCPAcceptor.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::function&lt; void([**Socket::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md))&gt; | [**Callback**](#typedef-callback)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Close**](#function-close) () <br> |
| virtual SR\_NODISCARD std::string | [**GetLocalAddress**](#function-getlocaladdress) () const = 0<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetLocalPort**](#function-getlocalport) () const = 0<br> |
| virtual SR\_NODISCARD std::string | [**GetRemoteAddress**](#function-getremoteaddress) () const = 0<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetRemotePort**](#function-getremoteport) () const = 0<br> |
| virtual SR\_NODISCARD bool | [**Init**](#function-init) () = 0<br> |
|  SR\_NODISCARD bool | [**IsOpen**](#function-isopen) () const<br> |
|  SR\_NODISCARD bool | [**IsRepeated**](#function-isrepeated) () const<br> |
|  SR\_NODISCARD bool | [**IsWaitingAccept**](#function-iswaitingaccept) () const<br> |
|  void | [**SetCallback**](#function-setcallback) (Callback && callback) <br> |
|  void | [**SetRepeated**](#function-setrepeated) (bool isRepeated) <br> |
|  bool | [**Start**](#function-start) () <br> |
|  bool | [**StartAsync**](#function-startasync) () <br> |
| virtual  | [**~Acceptor**](#function-acceptor) () = default<br> |


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
















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::string | [**m\_address**](#variable-m_address)  <br> |
|  Callback | [**m\_callback**](#variable-m_callback)  <br> |
|  [**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**m\_context**](#variable-m_context)  <br> |
|  bool | [**m\_isOpen**](#variable-m_isopen)   = `false`<br> |
|  bool | [**m\_isRepeated**](#variable-m_isrepeated)   = `true`<br> |
|  bool | [**m\_isWaitingAccept**](#variable-m_iswaitingaccept)   = `false`<br> |
|  uint16\_t | [**m\_port**](#variable-m_port)   = `0`<br> |
|  const SocketType | [**m\_type**](#variable-m_type)   = `SocketType::Unknown`<br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |












































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**Acceptor**](#function-acceptor) (SocketType type, [**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) pContext, std::string address, uint16\_t port) <br> |
| virtual bool | [**StartInternal**](#function-startinternal) (bool async) = 0<br> |












## Public Types Documentation




### typedef Callback 

```C++
using SR_NETWORK_NS::Acceptor::Callback =  std::function<void(Socket::Ptr)>;
```




<hr>
## Public Functions Documentation




### function Close 

```C++
inline virtual void SR_NETWORK_NS::Acceptor::Close () 
```




<hr>



### function GetLocalAddress 

```C++
virtual SR_NODISCARD std::string SR_NETWORK_NS::Acceptor::GetLocalAddress () const = 0
```




<hr>



### function GetLocalPort 

```C++
virtual SR_NODISCARD uint16_t SR_NETWORK_NS::Acceptor::GetLocalPort () const = 0
```




<hr>



### function GetRemoteAddress 

```C++
virtual SR_NODISCARD std::string SR_NETWORK_NS::Acceptor::GetRemoteAddress () const = 0
```




<hr>



### function GetRemotePort 

```C++
virtual SR_NODISCARD uint16_t SR_NETWORK_NS::Acceptor::GetRemotePort () const = 0
```




<hr>



### function Init 

```C++
virtual SR_NODISCARD bool SR_NETWORK_NS::Acceptor::Init () = 0
```




<hr>



### function IsOpen 

```C++
inline SR_NODISCARD bool SR_NETWORK_NS::Acceptor::IsOpen () const
```




<hr>



### function IsRepeated 

```C++
inline SR_NODISCARD bool SR_NETWORK_NS::Acceptor::IsRepeated () const
```




<hr>



### function IsWaitingAccept 

```C++
inline SR_NODISCARD bool SR_NETWORK_NS::Acceptor::IsWaitingAccept () const
```




<hr>



### function SetCallback 

```C++
inline void SR_NETWORK_NS::Acceptor::SetCallback (
    Callback && callback
) 
```




<hr>



### function SetRepeated 

```C++
inline void SR_NETWORK_NS::Acceptor::SetRepeated (
    bool isRepeated
) 
```




<hr>



### function Start 

```C++
bool SR_NETWORK_NS::Acceptor::Start () 
```




<hr>



### function StartAsync 

```C++
bool SR_NETWORK_NS::Acceptor::StartAsync () 
```




<hr>



### function ~Acceptor 

```C++
virtual SR_NETWORK_NS::Acceptor::~Acceptor () = default
```




<hr>
## Protected Attributes Documentation




### variable m\_address 

```C++
std::string SR_NETWORK_NS::Acceptor::m_address;
```




<hr>



### variable m\_callback 

```C++
Callback SR_NETWORK_NS::Acceptor::m_callback;
```




<hr>



### variable m\_context 

```C++
Context::Ptr SR_NETWORK_NS::Acceptor::m_context;
```




<hr>



### variable m\_isOpen 

```C++
bool SR_NETWORK_NS::Acceptor::m_isOpen;
```




<hr>



### variable m\_isRepeated 

```C++
bool SR_NETWORK_NS::Acceptor::m_isRepeated;
```



Нужно ли повторять прослушивание новых соединений. Работает только для асинхронного режима. 


        

<hr>



### variable m\_isWaitingAccept 

```C++
bool SR_NETWORK_NS::Acceptor::m_isWaitingAccept;
```




<hr>



### variable m\_port 

```C++
uint16_t SR_NETWORK_NS::Acceptor::m_port;
```




<hr>



### variable m\_type 

```C++
const SocketType SR_NETWORK_NS::Acceptor::m_type;
```




<hr>
## Protected Functions Documentation




### function Acceptor 

```C++
inline explicit SR_NETWORK_NS::Acceptor::Acceptor (
    SocketType type,
    Context::Ptr pContext,
    std::string address,
    uint16_t port
) 
```




<hr>



### function StartInternal 

```C++
virtual bool SR_NETWORK_NS::Acceptor::StartInternal (
    bool async
) = 0
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Network/Acceptor.h`

