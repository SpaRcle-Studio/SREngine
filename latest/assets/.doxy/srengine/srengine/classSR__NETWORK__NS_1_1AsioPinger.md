

# Class SR\_NETWORK\_NS::AsioPinger



[**ClassList**](annotated.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md) **>** [**AsioPinger**](classSR__NETWORK__NS_1_1AsioPinger.md)








Inherits the following classes: [SR\_NETWORK\_NS::Pinger](classSR__NETWORK__NS_1_1Pinger.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Ping**](#function-ping) (const std::string & address) override<br> |
|   | [**~AsioPinger**](#function-asiopinger) () <br> |


## Public Functions inherited from SR_NETWORK_NS::Pinger

See [SR\_NETWORK\_NS::Pinger](classSR__NETWORK__NS_1_1Pinger.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Ping**](classSR__NETWORK__NS_1_1Pinger.md#function-ping) (const std::string & address) = 0<br> |
|   | [**Pinger**](classSR__NETWORK__NS_1_1Pinger.md#function-pinger) () = default<br> |
|  void | [**SetContext**](classSR__NETWORK__NS_1_1Pinger.md#function-setcontext) ([**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) context) <br> |
|  void | [**SetSocket**](classSR__NETWORK__NS_1_1Pinger.md#function-setsocket) ([**Socket::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) socket) <br> |
















## Protected Attributes inherited from SR_NETWORK_NS::Pinger

See [SR\_NETWORK\_NS::Pinger](classSR__NETWORK__NS_1_1Pinger.md)

| Type | Name |
| ---: | :--- |
|  [**Context::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**m\_context**](classSR__NETWORK__NS_1_1Pinger.md#variable-m_context)  <br> |
|  [**Socket::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**m\_socket**](classSR__NETWORK__NS_1_1Pinger.md#variable-m_socket)  <br> |






































## Public Functions Documentation




### function Ping 

```C++
virtual void SR_NETWORK_NS::AsioPinger::Ping (
    const std::string & address
) override
```



Implements [*SR\_NETWORK\_NS::Pinger::Ping*](classSR__NETWORK__NS_1_1Pinger.md#function-ping)


<hr>



### function ~AsioPinger 

```C++
SR_NETWORK_NS::AsioPinger::~AsioPinger () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Network/Asio/AsioPinger.h`

