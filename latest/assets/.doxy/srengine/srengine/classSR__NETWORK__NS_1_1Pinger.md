

# Class SR\_NETWORK\_NS::Pinger



[**ClassList**](annotated.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md) **>** [**Pinger**](classSR__NETWORK__NS_1_1Pinger.md)










Inherited by the following classes: [SR\_NETWORK\_NS::AsioPinger](classSR__NETWORK__NS_1_1AsioPinger.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Ping**](#function-ping) (const std::string & address) = 0<br> |
|   | [**Pinger**](#function-pinger) () = default<br> |
|  void | [**SetContext**](#function-setcontext) ([**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) context) <br> |
|  void | [**SetSocket**](#function-setsocket) ([**Socket::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) socket) <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**m\_context**](#variable-m_context)  <br> |
|  [**Socket::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**m\_socket**](#variable-m_socket)  <br> |




















## Public Functions Documentation




### function Ping 

```C++
virtual void SR_NETWORK_NS::Pinger::Ping (
    const std::string & address
) = 0
```




<hr>



### function Pinger 

```C++
SR_NETWORK_NS::Pinger::Pinger () = default
```




<hr>



### function SetContext 

```C++
inline void SR_NETWORK_NS::Pinger::SetContext (
    Context::Ptr context
) 
```




<hr>



### function SetSocket 

```C++
inline void SR_NETWORK_NS::Pinger::SetSocket (
    Socket::Ptr socket
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_context 

```C++
Context::Ptr SR_NETWORK_NS::Pinger::m_context;
```




<hr>



### variable m\_socket 

```C++
Socket::Ptr SR_NETWORK_NS::Pinger::m_socket;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Network/Pinger.h`

