

# Class SR\_NETWORK\_NS::Message

**template &lt;typename T, typename DataT&gt;**



[**ClassList**](annotated.md) **>** [**SR\_NETWORK\_NS**](namespaceSR__NETWORK__NS.md) **>** [**Message**](classSR__NETWORK__NS_1_1Message.md)








Inherits the following classes: [SR\_NETWORK\_NS::IMessage](classSR__NETWORK__NS_1_1IMessage.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Message**](#function-message-12) (T id) <br> |
|   | [**Message**](#function-message-22) (T id, DataT data) <br> |
|  std::enable\_if\_t&lt;!std::is\_same\_v&lt; U, void &gt;, const U & &gt; | [**getData**](#function-getdata) () const<br> |
| virtual SR\_NODISCARD int64\_t | [**getRawID**](#function-getrawid) () override const<br> |
| virtual SR\_NODISCARD std::size\_t | [**getTypeID**](#function-gettypeid) () override const<br> |
|  SR\_NODISCARD bool | [**hasData**](#function-hasdata) () const<br> |


## Public Functions inherited from SR_NETWORK_NS::IMessage

See [SR\_NETWORK\_NS::IMessage](classSR__NETWORK__NS_1_1IMessage.md)

| Type | Name |
| ---: | :--- |
|  T | [**getID**](classSR__NETWORK__NS_1_1IMessage.md#function-getid) () const<br> |
|  SR\_NODISCARD bool | [**is**](classSR__NETWORK__NS_1_1IMessage.md#function-is) () const<br> |
| virtual  | [**~IMessage**](classSR__NETWORK__NS_1_1IMessage.md#function-imessage) () = default<br> |
















































## Protected Functions inherited from SR_NETWORK_NS::IMessage

See [SR\_NETWORK\_NS::IMessage](classSR__NETWORK__NS_1_1IMessage.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD int64\_t | [**getRawID**](classSR__NETWORK__NS_1_1IMessage.md#function-getrawid) () const = 0<br> |
| virtual SR\_NODISCARD std::size\_t | [**getTypeID**](classSR__NETWORK__NS_1_1IMessage.md#function-gettypeid) () const = 0<br> |






## Public Functions Documentation




### function Message [1/2]

```C++
inline explicit SR_NETWORK_NS::Message::Message (
    T id
) 
```




<hr>



### function Message [2/2]

```C++
inline SR_NETWORK_NS::Message::Message (
    T id,
    DataT data
) 
```




<hr>



### function getData 

```C++
template<typename U>
inline std::enable_if_t<!std::is_same_v< U, void >, const U & > SR_NETWORK_NS::Message::getData () const
```




<hr>



### function getRawID 

```C++
inline virtual SR_NODISCARD int64_t SR_NETWORK_NS::Message::getRawID () override const
```



Implements [*SR\_NETWORK\_NS::IMessage::getRawID*](classSR__NETWORK__NS_1_1IMessage.md#function-getrawid)


<hr>



### function getTypeID 

```C++
inline virtual SR_NODISCARD std::size_t SR_NETWORK_NS::Message::getTypeID () override const
```



Implements [*SR\_NETWORK\_NS::IMessage::getTypeID*](classSR__NETWORK__NS_1_1IMessage.md#function-gettypeid)


<hr>



### function hasData 

```C++
inline SR_NODISCARD bool SR_NETWORK_NS::Message::hasData () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Network/Message.h`

