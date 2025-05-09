

# Class SR\_UTILS\_NS::Factory



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Factory**](classSR__UTILS__NS_1_1Factory.md)








Inherits the following classes: [SR\_UTILS\_NS::BaseFactory](classSR__UTILS__NS_1_1BaseFactory.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Create**](#function-create-12) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) noexcept const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Create**](#function-create-22) () noexcept const<br> |
|  SR\_NODISCARD [**SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**CreateBase**](#function-createbase) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) noexcept const<br> |
|  SR\_NODISCARD void | [**ForEachClassInModule**](#function-foreachclassinmodule) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) moduleName, const std::function&lt; void(const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \*)&gt; & func) noexcept const<br> |
|  SR\_NODISCARD std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**GetInheritances**](#function-getinheritances) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) baseClass) noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname-13) (const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* pMeta, bool isMustExists=true) const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname-23) (Y \* pObject, const bool isMustExists=true) const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname-33) () const<br> |
| virtual SR\_NODISCARD const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetType**](#function-gettype) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) noexcept override const<br> |
|  SR\_NODISCARD const TypeInfo \* | [**GetTypeInfo**](#function-gettypeinfo) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsAbstract**](#function-isabstract) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) noexcept const<br> |
|  bool | [**Register**](#function-register) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) moduleName) <br> |
|  bool | [**Unregister**](#function-unregister) () <br> |


## Public Functions inherited from SR_UTILS_NS::BaseFactory

See [SR\_UTILS\_NS::BaseFactory](classSR__UTILS__NS_1_1BaseFactory.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetType**](classSR__UTILS__NS_1_1BaseFactory.md#function-gettype) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const = 0<br> |
|  SR\_NODISCARD bool | [**IsRegistered**](classSR__UTILS__NS_1_1BaseFactory.md#function-isregistered) (const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* pMeta) const<br> |
| virtual  | [**~BaseFactory**](classSR__UTILS__NS_1_1BaseFactory.md#function-basefactory) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**Factory**](classSR__UTILS__NS_1_1Factory.md) & | [**Instance**](#function-instance) () noexcept<br> |




















































## Public Functions Documentation




### function Create [1/2]

```C++
template<typename T>
inline SR_NODISCARD SR_HTYPES_NS::SharedPtr < T > SR_UTILS_NS::Factory::Create (
    SR_UTILS_NS::StringAtom name
) noexcept const
```




<hr>



### function Create [2/2]

```C++
template<typename T>
inline SR_NODISCARD SR_HTYPES_NS::SharedPtr < T > SR_UTILS_NS::Factory::Create () noexcept const
```




<hr>



### function CreateBase 

```C++
SR_NODISCARD SRClass * SR_UTILS_NS::Factory::CreateBase (
    SR_UTILS_NS::StringAtom name
) noexcept const
```




<hr>



### function ForEachClassInModule 

```C++
SR_NODISCARD void SR_UTILS_NS::Factory::ForEachClassInModule (
    SR_UTILS_NS::StringAtom moduleName,
    const std::function< void(const SRClassMeta *)> & func
) noexcept const
```




<hr>



### function GetInheritances 

```C++
SR_NODISCARD std::vector< SR_UTILS_NS::StringAtom > SR_UTILS_NS::Factory::GetInheritances (
    SR_UTILS_NS::StringAtom baseClass
) noexcept const
```




<hr>



### function GetName [1/3]

```C++
SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::Factory::GetName (
    const SRClassMeta * pMeta,
    bool isMustExists=true
) const
```




<hr>



### function GetName [2/3]

```C++
template<class Y>
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::Factory::GetName (
    Y * pObject,
    const bool isMustExists=true
) const
```




<hr>



### function GetName [3/3]

```C++
template<class Y>
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::Factory::GetName () const
```




<hr>



### function GetType 

```C++
virtual SR_NODISCARD const SRClassMeta * SR_UTILS_NS::Factory::GetType (
    SR_UTILS_NS::StringAtom name
) noexcept override const
```



Implements [*SR\_UTILS\_NS::BaseFactory::GetType*](classSR__UTILS__NS_1_1BaseFactory.md#function-gettype)


<hr>



### function GetTypeInfo 

```C++
SR_NODISCARD const TypeInfo * SR_UTILS_NS::Factory::GetTypeInfo (
    SR_UTILS_NS::StringAtom name
) noexcept const
```




<hr>



### function IsAbstract 

```C++
SR_NODISCARD bool SR_UTILS_NS::Factory::IsAbstract (
    SR_UTILS_NS::StringAtom name
) noexcept const
```




<hr>



### function Register 

```C++
template<class T>
bool SR_UTILS_NS::Factory::Register (
    SR_UTILS_NS::StringAtom moduleName
) 
```




<hr>



### function Unregister 

```C++
template<class T>
bool SR_UTILS_NS::Factory::Unregister () 
```




<hr>
## Public Static Functions Documentation




### function Instance 

```C++
static SR_NODISCARD Factory & SR_UTILS_NS::Factory::Instance () noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/Factory.h`

