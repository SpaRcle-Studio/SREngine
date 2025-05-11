

# Class SR\_NETWORK\_NS::ICMPHeader



[**ClassList**](annotated.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md) **>** [**ICMPHeader**](classSR__NETWORK__NS_1_1ICMPHeader.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  uint16\_t | [**Checksum**](#function-checksum-12) () const<br> |
|  void | [**Checksum**](#function-checksum-22) (uint16\_t type) <br> |
|  uint8\_t | [**Code**](#function-code-12) () const<br> |
|  void | [**Code**](#function-code-22) (ICMPType type) <br> |
|   | [**ICMPHeader**](#function-icmpheader) () <br> |
|  uint16\_t | [**Identifier**](#function-identifier-12) () const<br> |
|  void | [**Identifier**](#function-identifier-22) (uint16\_t type) <br> |
|  uint16\_t | [**SequenceNumber**](#function-sequencenumber-12) () const<br> |
|  void | [**SequenceNumber**](#function-sequencenumber-22) (uint16\_t type) <br> |
|  uint8\_t | [**Type**](#function-type-12) () const<br> |
|  void | [**Type**](#function-type-22) (ICMPType type) <br> |




























## Public Functions Documentation




### function Checksum [1/2]

```C++
inline uint16_t SR_NETWORK_NS::ICMPHeader::Checksum () const
```




<hr>



### function Checksum [2/2]

```C++
inline void SR_NETWORK_NS::ICMPHeader::Checksum (
    uint16_t type
) 
```




<hr>



### function Code [1/2]

```C++
inline uint8_t SR_NETWORK_NS::ICMPHeader::Code () const
```




<hr>



### function Code [2/2]

```C++
inline void SR_NETWORK_NS::ICMPHeader::Code (
    ICMPType type
) 
```




<hr>



### function ICMPHeader 

```C++
inline SR_NETWORK_NS::ICMPHeader::ICMPHeader () 
```




<hr>



### function Identifier [1/2]

```C++
inline uint16_t SR_NETWORK_NS::ICMPHeader::Identifier () const
```




<hr>



### function Identifier [2/2]

```C++
inline void SR_NETWORK_NS::ICMPHeader::Identifier (
    uint16_t type
) 
```




<hr>



### function SequenceNumber [1/2]

```C++
inline uint16_t SR_NETWORK_NS::ICMPHeader::SequenceNumber () const
```




<hr>



### function SequenceNumber [2/2]

```C++
inline void SR_NETWORK_NS::ICMPHeader::SequenceNumber (
    uint16_t type
) 
```




<hr>



### function Type [1/2]

```C++
inline uint8_t SR_NETWORK_NS::ICMPHeader::Type () const
```




<hr>



### function Type [2/2]

```C++
inline void SR_NETWORK_NS::ICMPHeader::Type (
    ICMPType type
) 
```




<hr>## Friends Documentation





### friend operator&lt;&lt; 

```C++
inline std::ostream & SR_NETWORK_NS::ICMPHeader::operator<< (
    std::ostream & os,
    const ICMPHeader & header
) 
```




<hr>



### friend operator&gt;&gt; 

```C++
inline std::istream & SR_NETWORK_NS::ICMPHeader::operator>> (
    std::istream & is,
    ICMPHeader & header
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Network/Headers/ICMPHeader.h`

