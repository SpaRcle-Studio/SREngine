

# Class SR\_UTILS\_NS::SubscriptionMessage



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**GetBool**](#function-getbool) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const std::optional&lt; bool &gt; def=std::nullopt) const<br> |
|  SR\_NODISCARD uint64\_t | [**GetInt**](#function-getint) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const std::optional&lt; uint64\_t &gt; def=std::nullopt) const<br> |
|  void | [**SetBool**](#function-setbool) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const bool value) <br> |
|  void | [**SetInt**](#function-setint) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const uint64\_t value) <br> |


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
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Functions Documentation




### function GetBool 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::SubscriptionMessage::GetBool (
    const StringAtom id,
    const std::optional< bool > def=std::nullopt
) const
```




<hr>



### function GetInt 

```C++
inline SR_NODISCARD uint64_t SR_UTILS_NS::SubscriptionMessage::GetInt (
    const StringAtom id,
    const std::optional< uint64_t > def=std::nullopt
) const
```




<hr>



### function SetBool 

```C++
inline void SR_UTILS_NS::SubscriptionMessage::SetBool (
    const StringAtom id,
    const bool value
) 
```




<hr>



### function SetInt 

```C++
inline void SR_UTILS_NS::SubscriptionMessage::SetInt (
    const StringAtom id,
    const uint64_t value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/SubscriptionHolder.h`

