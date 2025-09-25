

# Class SR\_UTILS\_NS::Subscription



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Subscription**](classSR__UTILS__NS_1_1Subscription.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () noexcept const<br> |
|  void | [**Reset**](#function-reset) () <br> |
|   | [**Subscription**](#function-subscription-13) () <br> |
|   | [**Subscription**](#function-subscription-23) ([**SubscriptionInternalInfo**](classSR__UTILS__NS_1_1SubscriptionInternalInfo.md) \* pInternalInfo) <br> |
|   | [**Subscription**](#function-subscription-33) ([**Subscription**](classSR__UTILS__NS_1_1Subscription.md) && other) noexcept<br> |
|  [**Subscription**](classSR__UTILS__NS_1_1Subscription.md) & | [**operator=**](#function-operator) ([**Subscription**](classSR__UTILS__NS_1_1Subscription.md) && other) noexcept<br> |
|   | [**~Subscription**](#function-subscription) () override<br> |


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




### function IsValid 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Subscription::IsValid () noexcept const
```




<hr>



### function Reset 

```C++
void SR_UTILS_NS::Subscription::Reset () 
```




<hr>



### function Subscription [1/3]

```C++
SR_UTILS_NS::Subscription::Subscription () 
```




<hr>



### function Subscription [2/3]

```C++
explicit SR_UTILS_NS::Subscription::Subscription (
    SubscriptionInternalInfo * pInternalInfo
) 
```




<hr>



### function Subscription [3/3]

```C++
SR_UTILS_NS::Subscription::Subscription (
    Subscription && other
) noexcept
```




<hr>



### function operator= 

```C++
Subscription & SR_UTILS_NS::Subscription::operator= (
    Subscription && other
) noexcept
```




<hr>



### function ~Subscription 

```C++
SR_UTILS_NS::Subscription::~Subscription () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/SubscriptionHolder.h`

