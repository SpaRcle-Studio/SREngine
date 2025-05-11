

# Class SR\_NETWORK\_NS::IMessage



[**ClassList**](annotated.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md) **>** [**IMessage**](classSR__NETWORK__NS_1_1IMessage.md)










Inherited by the following classes: [SR\_NETWORK\_NS::Message](classSR__NETWORK__NS_1_1Message.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  T | [**getID**](#function-getid) () const<br> |
|  SR\_NODISCARD bool | [**is**](#function-is) () const<br> |
| virtual  | [**~IMessage**](#function-imessage) () = default<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD int64\_t | [**getRawID**](#function-getrawid) () const = 0<br> |
| virtual SR\_NODISCARD std::size\_t | [**getTypeID**](#function-gettypeid) () const = 0<br> |




## Public Functions Documentation




### function getID 

```C++
template<typename T>
inline T SR_NETWORK_NS::IMessage::getID () const
```




<hr>



### function is 

```C++
template<typename T>
inline SR_NODISCARD bool SR_NETWORK_NS::IMessage::is () const
```




<hr>



### function ~IMessage 

```C++
virtual SR_NETWORK_NS::IMessage::~IMessage () = default
```




<hr>
## Protected Functions Documentation




### function getRawID 

```C++
virtual SR_NODISCARD int64_t SR_NETWORK_NS::IMessage::getRawID () const = 0
```




<hr>



### function getTypeID 

```C++
virtual SR_NODISCARD std::size_t SR_NETWORK_NS::IMessage::getTypeID () const = 0
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Network/Message.h`

