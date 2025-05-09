

# Namespace SR\_NETWORK\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Acceptor**](classSR__NETWORK__NS_1_1Acceptor.md) <br> |
| class | [**AsioContext**](classSR__NETWORK__NS_1_1AsioContext.md) <br> |
| class | [**AsioICMPSocket**](classSR__NETWORK__NS_1_1AsioICMPSocket.md) <br> |
| class | [**AsioPinger**](classSR__NETWORK__NS_1_1AsioPinger.md) <br> |
| class | [**AsioTCPAcceptor**](classSR__NETWORK__NS_1_1AsioTCPAcceptor.md) <br> |
| class | [**AsioTCPSocket**](classSR__NETWORK__NS_1_1AsioTCPSocket.md) <br> |
| class | [**Client**](classSR__NETWORK__NS_1_1Client.md) <br> |
| class | [**Context**](classSR__NETWORK__NS_1_1Context.md) <br> |
| class | [**DataPackage**](classSR__NETWORK__NS_1_1DataPackage.md) <br> |
| class | [**FileDownloader**](classSR__NETWORK__NS_1_1FileDownloader.md) <br> |
| class | [**ICMPHeader**](classSR__NETWORK__NS_1_1ICMPHeader.md) <br> |
| class | [**IMessage**](classSR__NETWORK__NS_1_1IMessage.md) <br> |
| class | [**IMessageData**](classSR__NETWORK__NS_1_1IMessageData.md) <br> |
| class | [**IMessageHandler**](classSR__NETWORK__NS_1_1IMessageHandler.md) <br> |
| class | [**IPV4Header**](classSR__NETWORK__NS_1_1IPV4Header.md) <br> |
| class | [**Message**](classSR__NETWORK__NS_1_1Message.md) &lt;typename T, typename DataT&gt;<br> |
| struct | [**P2PAnnounceHeader**](structSR__NETWORK__NS_1_1P2PAnnounceHeader.md) <br> |
| struct | [**P2PConnectionHeader**](structSR__NETWORK__NS_1_1P2PConnectionHeader.md) <br> |
| struct | [**P2PDisconnectionHeader**](structSR__NETWORK__NS_1_1P2PDisconnectionHeader.md) <br> |
| struct | [**P2PKnownHostHeader**](structSR__NETWORK__NS_1_1P2PKnownHostHeader.md) <br> |
| struct | [**P2PKnownHostsListInfoHeader**](structSR__NETWORK__NS_1_1P2PKnownHostsListInfoHeader.md) <br> |
| class | [**PeerToPeer**](classSR__NETWORK__NS_1_1PeerToPeer.md) <br> |
| class | [**Pinger**](classSR__NETWORK__NS_1_1Pinger.md) <br> |
| class | [**Server**](classSR__NETWORK__NS_1_1Server.md) <br> |
| class | [**Socket**](classSR__NETWORK__NS_1_1Socket.md) <br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|   | [**TCP**](#variable-tcp)  <br> |
|   | [**UDP**](#variable-udp)  <br> |
|   | [**Unknown**](#variable-unknown)  <br> |
|   | [**uint8\_t**](#variable-uint8_t)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ComputeChecksum**](#function-computechecksum) ([**ICMPHeader**](classSR__NETWORK__NS_1_1ICMPHeader.md) & header, Iterator body\_begin, Iterator body\_end) <br> |
|  SR\_MAYBE\_UNUSED SR\_CONSTEXPR SR\_INLINE\_STATIC size\_t | [**GetMaxP2PHeaderSize**](#function-getmaxp2pheadersize) () <br>_write constexpr code that be return max header size from sizeof_  |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC std::string | [**IPv4ToString**](#function-ipv4tostring) (uint32\_t address) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (NetworkLib, uint8\_t, Unknown, Asio) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (ICMPType, uint8\_t, EchoReply=0, DestinationUnreachable=3, SourceQuench=4, Redirect=5, EchoRequest=8, TimeExceeded=11, ParameterProblem=12, TimestampRequest=13, TimestampReply=14, InfoRequest=15, InfoReply=16, AddressRequest=17, AddressReply=18) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (P2PMessageType, uint8\_t, Unknown, PeerConnection, PeerDisconnection, KnownHostsListInfo, KnownHost, Announce) <br> |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC uint32\_t | [**StringToIPv4**](#function-stringtoipv4) (const std::string & address) <br> |




























## Public Attributes Documentation




### variable TCP 

```C++
SR_NETWORK_NS::TCP;
```




<hr>



### variable UDP 

```C++
SR_NETWORK_NS::UDP;
```




<hr>



### variable Unknown 

```C++
SR_NETWORK_NS::Unknown;
```




<hr>



### variable uint8\_t 

```C++
SR_NETWORK_NS::uint8_t;
```




<hr>
## Public Functions Documentation




### function ComputeChecksum 

```C++
template<typename Iterator>
void SR_NETWORK_NS::ComputeChecksum (
    ICMPHeader & header,
    Iterator body_begin,
    Iterator body_end
) 
```




<hr>



### function GetMaxP2PHeaderSize 

_write constexpr code that be return max header size from sizeof_ 
```C++
SR_MAYBE_UNUSED SR_CONSTEXPR SR_INLINE_STATIC size_t SR_NETWORK_NS::GetMaxP2PHeaderSize () 
```




<hr>



### function IPv4ToString 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC std::string SR_NETWORK_NS::IPv4ToString (
    uint32_t address
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_NETWORK_NS::SR_ENUM_NS_CLASS_T (
    NetworkLib,
    uint8_t,
    Unknown,
    Asio
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_NETWORK_NS::SR_ENUM_NS_CLASS_T (
    ICMPType,
    uint8_t,
    EchoReply=0,
    DestinationUnreachable=3,
    SourceQuench=4,
    Redirect=5,
    EchoRequest=8,
    TimeExceeded=11,
    ParameterProblem=12,
    TimestampRequest=13,
    TimestampReply=14,
    InfoRequest=15,
    InfoReply=16,
    AddressRequest=17,
    AddressReply=18
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_NETWORK_NS::SR_ENUM_NS_CLASS_T (
    P2PMessageType,
    uint8_t,
    Unknown,
    PeerConnection,
    PeerDisconnection,
    KnownHostsListInfo,
    KnownHost,
    Announce
) 
```




<hr>



### function StringToIPv4 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC uint32_t SR_NETWORK_NS::StringToIPv4 (
    const std::string & address
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Network/Acceptor.h`

