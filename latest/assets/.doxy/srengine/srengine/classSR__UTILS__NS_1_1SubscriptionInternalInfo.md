

# Class SR\_UTILS\_NS::SubscriptionInternalInfo



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SubscriptionInternalInfo**](classSR__UTILS__NS_1_1SubscriptionInternalInfo.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) &)&gt; | [**callback**](#variable-callback)  <br> |
|  [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**id**](#variable-id)  <br> |
|  uint32\_t | [**index**](#variable-index)   = `SR\_ID\_INVALID`<br> |
|  [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) \* | [**pHolder**](#variable-pholder)   = `nullptr`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SubscriptionInternalInfo**](#function-subscriptioninternalinfo) ([**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) &)&gt; && callback, [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) \* pHolder) <br> |


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






## Public Attributes Documentation




### variable callback 

```C++
SR_HTYPES_NS::Function<void(const SubscriptionMessage&)> SR_UTILS_NS::SubscriptionInternalInfo::callback;
```




<hr>



### variable id 

```C++
StringAtom SR_UTILS_NS::SubscriptionInternalInfo::id;
```




<hr>



### variable index 

```C++
uint32_t SR_UTILS_NS::SubscriptionInternalInfo::index;
```




<hr>



### variable pHolder 

```C++
SubscriptionHolder* SR_UTILS_NS::SubscriptionInternalInfo::pHolder;
```




<hr>
## Public Functions Documentation




### function SubscriptionInternalInfo 

```C++
explicit SR_UTILS_NS::SubscriptionInternalInfo::SubscriptionInternalInfo (
    SR_HTYPES_NS::Function < void(const SubscriptionMessage &)> && callback,
    SubscriptionHolder * pHolder
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/SubscriptionHolder.h`

