

# Class SR\_UTILS\_NS::BaseFactory



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**BaseFactory**](classSR__UTILS__NS_1_1BaseFactory.md)










Inherited by the following classes: [SR\_UTILS\_NS::Factory](classSR__UTILS__NS_1_1Factory.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetType**](#function-gettype) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const = 0<br> |
|  SR\_NODISCARD bool | [**IsRegistered**](#function-isregistered) (const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* pMeta) const<br> |
| virtual  | [**~BaseFactory**](#function-basefactory) () = default<br> |




























## Public Functions Documentation




### function GetType 

```C++
virtual SR_NODISCARD const SRClassMeta * SR_UTILS_NS::BaseFactory::GetType (
    SR_UTILS_NS::StringAtom name
) const = 0
```




<hr>



### function IsRegistered 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::BaseFactory::IsRegistered (
    const SRClassMeta * pMeta
) const
```




<hr>



### function ~BaseFactory 

```C++
virtual SR_UTILS_NS::BaseFactory::~BaseFactory () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/TypeTraits/Factory.h`

