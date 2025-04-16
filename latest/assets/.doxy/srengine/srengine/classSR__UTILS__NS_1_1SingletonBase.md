

# Class SR\_UTILS\_NS::SingletonBase



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**~SingletonBase**](#function-singletonbase) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](#variable-m_mutex)  <br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSingletonName**](#function-getsingletonname) () noexcept const = 0<br> |
| virtual void | [**InitSingleton**](#function-initsingleton) () <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](#function-issingletoncanbedestroyed) () const<br> |
| virtual void | [**OnSingletonDestroy**](#function-onsingletondestroy) () <br> |
|   | [**SingletonBase**](#function-singletonbase) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Functions Documentation




### function ~SingletonBase 

```C++
SR_UTILS_NS::SingletonBase::~SingletonBase () override
```




<hr>
## Protected Attributes Documentation




### variable m\_mutex 

```C++
std::recursive_mutex SR_UTILS_NS::SingletonBase::m_mutex;
```




<hr>
## Protected Functions Documentation




### function GetSingletonName 

```C++
virtual StringAtom SR_UTILS_NS::SingletonBase::GetSingletonName () noexcept const = 0
```




<hr>



### function InitSingleton 

```C++
inline virtual void SR_UTILS_NS::SingletonBase::InitSingleton () 
```




<hr>



### function IsSingletonCanBeDestroyed 

```C++
inline virtual bool SR_UTILS_NS::SingletonBase::IsSingletonCanBeDestroyed () const
```




<hr>



### function OnSingletonDestroy 

```C++
inline virtual void SR_UTILS_NS::SingletonBase::OnSingletonDestroy () 
```




<hr>



### function SingletonBase 

```C++
SR_UTILS_NS::SingletonBase::SingletonBase () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/Singleton.h`

