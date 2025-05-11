

# Class SR\_NETWORK\_NS::IPV4Header



[**ClassList**](annotated.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md) **>** [**IPV4Header**](classSR__NETWORK__NS_1_1IPV4Header.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**IPV4Header**](#function-ipv4header) () <br>_Refactor, rename to AsioIPV4Header._  |
|  asio::ip::address\_v4 | [**destination\_address**](#function-destination_address) () const<br> |
|  bool | [**dont\_fragment**](#function-dont_fragment) () const<br> |
|  unsigned short | [**fragment\_offset**](#function-fragment_offset) () const<br> |
|  unsigned short | [**header\_checksum**](#function-header_checksum) () const<br> |
|  unsigned short | [**header\_length**](#function-header_length) () const<br> |
|  unsigned short | [**identification**](#function-identification) () const<br> |
|  bool | [**more\_fragments**](#function-more_fragments) () const<br> |
|  unsigned char | [**protocol**](#function-protocol) () const<br> |
|  asio::ip::address\_v4 | [**source\_address**](#function-source_address) () const<br> |
|  unsigned int | [**time\_to\_live**](#function-time_to_live) () const<br> |
|  unsigned short | [**total\_length**](#function-total_length) () const<br> |
|  unsigned char | [**type\_of\_service**](#function-type_of_service) () const<br> |
|  unsigned char | [**version**](#function-version) () const<br> |




























## Public Functions Documentation




### function IPV4Header 

_Refactor, rename to AsioIPV4Header._ 
```C++
inline SR_NETWORK_NS::IPV4Header::IPV4Header () 
```




<hr>



### function destination\_address 

```C++
inline asio::ip::address_v4 SR_NETWORK_NS::IPV4Header::destination_address () const
```




<hr>



### function dont\_fragment 

```C++
inline bool SR_NETWORK_NS::IPV4Header::dont_fragment () const
```




<hr>



### function fragment\_offset 

```C++
inline unsigned short SR_NETWORK_NS::IPV4Header::fragment_offset () const
```




<hr>



### function header\_checksum 

```C++
inline unsigned short SR_NETWORK_NS::IPV4Header::header_checksum () const
```




<hr>



### function header\_length 

```C++
inline unsigned short SR_NETWORK_NS::IPV4Header::header_length () const
```




<hr>



### function identification 

```C++
inline unsigned short SR_NETWORK_NS::IPV4Header::identification () const
```




<hr>



### function more\_fragments 

```C++
inline bool SR_NETWORK_NS::IPV4Header::more_fragments () const
```




<hr>



### function protocol 

```C++
inline unsigned char SR_NETWORK_NS::IPV4Header::protocol () const
```




<hr>



### function source\_address 

```C++
inline asio::ip::address_v4 SR_NETWORK_NS::IPV4Header::source_address () const
```




<hr>



### function time\_to\_live 

```C++
inline unsigned int SR_NETWORK_NS::IPV4Header::time_to_live () const
```




<hr>



### function total\_length 

```C++
inline unsigned short SR_NETWORK_NS::IPV4Header::total_length () const
```




<hr>



### function type\_of\_service 

```C++
inline unsigned char SR_NETWORK_NS::IPV4Header::type_of_service () const
```




<hr>



### function version 

```C++
inline unsigned char SR_NETWORK_NS::IPV4Header::version () const
```




<hr>## Friends Documentation





### friend operator&gt;&gt; 

```C++
inline std::istream & SR_NETWORK_NS::IPV4Header::operator>> (
    std::istream & is,
    IPV4Header & header
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Network/Headers/IPV4Header.h`

