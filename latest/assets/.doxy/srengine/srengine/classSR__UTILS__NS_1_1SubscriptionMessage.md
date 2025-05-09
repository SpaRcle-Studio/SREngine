

# Class SR\_UTILS\_NS::SubscriptionMessage



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**GetBool**](#function-getbool) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const std::optional&lt; bool &gt; & def=std::nullopt) const<br> |
|  SR\_NODISCARD uint64\_t | [**GetInt**](#function-getint) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const std::optional&lt; uint64\_t &gt; & def=std::nullopt) const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetPath**](#function-getpath) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const std::optional&lt; [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) &gt; & def=std::nullopt) const<br> |
|  SR\_NODISCARD const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & | [**GetPathRef**](#function-getpathref) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id) const<br> |
|  SR\_NODISCARD std::string | [**GetString**](#function-getstring) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const std::optional&lt; std::string &gt; & def=std::nullopt) const<br> |
|  void | [**SetBool**](#function-setbool) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, bool value) <br> |
|  void | [**SetInt**](#function-setint) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, uint64\_t value) <br> |
|  void | [**SetPath**](#function-setpath) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & value) <br> |
|  void | [**SetString**](#function-setstring) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const std::string & value) <br> |
|   | [**SubscriptionMessage**](#function-subscriptionmessage) () <br> |
|   | [**~SubscriptionMessage**](#function-subscriptionmessage) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function GetBool 

```C++
SR_NODISCARD bool SR_UTILS_NS::SubscriptionMessage::GetBool (
    StringAtom id,
    const std::optional< bool > & def=std::nullopt
) const
```




<hr>



### function GetInt 

```C++
SR_NODISCARD uint64_t SR_UTILS_NS::SubscriptionMessage::GetInt (
    StringAtom id,
    const std::optional< uint64_t > & def=std::nullopt
) const
```




<hr>



### function GetPath 

```C++
SR_NODISCARD SR_UTILS_NS::Path SR_UTILS_NS::SubscriptionMessage::GetPath (
    StringAtom id,
    const std::optional< SR_UTILS_NS::Path > & def=std::nullopt
) const
```




<hr>



### function GetPathRef 

```C++
SR_NODISCARD const SR_UTILS_NS::Path & SR_UTILS_NS::SubscriptionMessage::GetPathRef (
    StringAtom id
) const
```




<hr>



### function GetString 

```C++
SR_NODISCARD std::string SR_UTILS_NS::SubscriptionMessage::GetString (
    StringAtom id,
    const std::optional< std::string > & def=std::nullopt
) const
```




<hr>



### function SetBool 

```C++
void SR_UTILS_NS::SubscriptionMessage::SetBool (
    StringAtom id,
    bool value
) 
```




<hr>



### function SetInt 

```C++
void SR_UTILS_NS::SubscriptionMessage::SetInt (
    StringAtom id,
    uint64_t value
) 
```




<hr>



### function SetPath 

```C++
void SR_UTILS_NS::SubscriptionMessage::SetPath (
    StringAtom id,
    const SR_UTILS_NS::Path & value
) 
```




<hr>



### function SetString 

```C++
void SR_UTILS_NS::SubscriptionMessage::SetString (
    StringAtom id,
    const std::string & value
) 
```




<hr>



### function SubscriptionMessage 

```C++
SR_UTILS_NS::SubscriptionMessage::SubscriptionMessage () 
```




<hr>



### function ~SubscriptionMessage 

```C++
SR_UTILS_NS::SubscriptionMessage::~SubscriptionMessage () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/SubscriptionHolder.h`

