

# Class SR\_UTILS\_NS::SubscriptionHolder



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md)










Inherited by the following classes: [SR\_GRAPH\_NS::MaterialData](classSR__GRAPH__NS_1_1MaterialData.md),  [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md),  [SR\_UTILS\_NS::Input](classSR__UTILS__NS_1_1Input.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Broadcast**](#function-broadcast-12) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id) <br> |
|  void | [**Broadcast**](#function-broadcast-22) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) & message) <br> |
|  SR\_NODISCARD bool | [**HasSubscriptions**](#function-hassubscriptions) () noexcept const<br> |
|  SR\_NODISCARD [**Subscription**](classSR__UTILS__NS_1_1Subscription.md) | [**Subscribe**](#function-subscribe) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) &)&gt; && callback) <br> |
|  void | [**Unsubscribe**](#function-unsubscribe) (const [**SubscriptionInternalInfo**](classSR__UTILS__NS_1_1SubscriptionInternalInfo.md) \* pSubscription) <br> |
| virtual  | [**~SubscriptionHolder**](#function-subscriptionholder) () <br> |




























## Public Functions Documentation




### function Broadcast [1/2]

```C++
inline void SR_UTILS_NS::SubscriptionHolder::Broadcast (
    const StringAtom id
) 
```




<hr>



### function Broadcast [2/2]

```C++
inline void SR_UTILS_NS::SubscriptionHolder::Broadcast (
    const StringAtom id,
    const SubscriptionMessage & message
) 
```




<hr>



### function HasSubscriptions 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::SubscriptionHolder::HasSubscriptions () noexcept const
```




<hr>



### function Subscribe 

```C++
SR_NODISCARD Subscription SR_UTILS_NS::SubscriptionHolder::Subscribe (
    StringAtom id,
    SR_HTYPES_NS::Function < void(const SubscriptionMessage &)> && callback
) 
```




<hr>



### function Unsubscribe 

```C++
inline void SR_UTILS_NS::SubscriptionHolder::Unsubscribe (
    const SubscriptionInternalInfo * pSubscription
) 
```




<hr>



### function ~SubscriptionHolder 

```C++
virtual SR_UTILS_NS::SubscriptionHolder::~SubscriptionHolder () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/SubscriptionHolder.h`

