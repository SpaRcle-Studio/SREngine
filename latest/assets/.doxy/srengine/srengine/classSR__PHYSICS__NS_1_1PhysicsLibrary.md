

# Class SR\_PHYSICS\_NS::PhysicsLibrary



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**PhysicsLibrary**](classSR__PHYSICS__NS_1_1PhysicsLibrary.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)






























































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**GetActiveLibrary**](#function-getactivelibrary) (Space space) <br> |
|  SR\_NODISCARD [**SR\_PTYPES\_NS::PhysicsMaterial**](classSR__PTYPES__NS_1_1PhysicsMaterial.md) \* | [**GetDefaultMaterial**](#function-getdefaultmaterial) () noexcept const<br> |
|  SR\_NODISCARD [**LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**GetLibrary**](#function-getlibrary) (LibraryType type) <br> |
|  SR\_NODISCARD LibraryTypes | [**GetSupportedLibraries**](#function-getsupportedlibraries) () const<br> |
|   | [**PhysicsLibrary**](#function-physicslibrary) () <br> |
|   | [**~PhysicsLibrary**](#function-physicslibrary) () override<br> |




## Public Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|   | [**~SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |




## Public Static Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySingleton**](classSR__UTILS__NS_1_1Singleton.md#function-destroysingleton) () <br> |
|  SR\_MAYBE\_UNUSED std::recursive\_mutex & | [**GetMutex**](classSR__UTILS__NS_1_1Singleton.md#function-getmutex) () noexcept<br> |
|  SR\_MAYBE\_UNUSED T & | [**Instance**](classSR__UTILS__NS_1_1Singleton.md#function-instance) () noexcept<br> |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](classSR__UTILS__NS_1_1Singleton.md#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-unlocksingleton) () noexcept<br> |


























## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |




























































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**InitSingleton**](#function-initsingleton) () override<br> |
| virtual void | [**OnSingletonDestroy**](#function-onsingletondestroy) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|   | [**Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () <br> |
|   | [**~Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSingletonName**](classSR__UTILS__NS_1_1SingletonBase.md#function-getsingletonname) () noexcept const = 0<br> |
| virtual void | [**InitSingleton**](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton) () <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed) () const<br> |
| virtual void | [**OnSingletonDestroy**](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy) () <br> |
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |










## Public Functions Documentation




### function GetActiveLibrary 

```C++
SR_NODISCARD LibraryImpl * SR_PHYSICS_NS::PhysicsLibrary::GetActiveLibrary (
    Space space
) 
```




<hr>



### function GetDefaultMaterial 

```C++
inline SR_NODISCARD SR_PTYPES_NS::PhysicsMaterial * SR_PHYSICS_NS::PhysicsLibrary::GetDefaultMaterial () noexcept const
```




<hr>



### function GetLibrary 

```C++
SR_NODISCARD LibraryImpl * SR_PHYSICS_NS::PhysicsLibrary::GetLibrary (
    LibraryType type
) 
```




<hr>



### function GetSupportedLibraries 

```C++
SR_NODISCARD LibraryTypes SR_PHYSICS_NS::PhysicsLibrary::GetSupportedLibraries () const
```




<hr>



### function PhysicsLibrary 

```C++
SR_PHYSICS_NS::PhysicsLibrary::PhysicsLibrary () 
```




<hr>



### function ~PhysicsLibrary 

```C++
SR_PHYSICS_NS::PhysicsLibrary::~PhysicsLibrary () override
```




<hr>
## Protected Functions Documentation




### function InitSingleton 

```C++
virtual void SR_PHYSICS_NS::PhysicsLibrary::InitSingleton () override
```



Implements [*SR\_UTILS\_NS::SingletonBase::InitSingleton*](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton)


<hr>



### function OnSingletonDestroy 

```C++
virtual void SR_PHYSICS_NS::PhysicsLibrary::OnSingletonDestroy () override
```



Implements [*SR\_UTILS\_NS::SingletonBase::OnSingletonDestroy*](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/PhysicsLib.h`

