

# Class SR\_SCRIPTING\_NS::GlobalEvoCompiler



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**GlobalEvoCompiler**](classSR__SCRIPTING__NS_1_1GlobalEvoCompiler.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_SCRIPTING\_NS::EvoCompiler](classSR__SCRIPTING__NS_1_1EvoCompiler.md)






























































































































































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


## Public Functions inherited from SR_SCRIPTING_NS::EvoCompiler

See [SR\_SCRIPTING\_NS::EvoCompiler](classSR__SCRIPTING__NS_1_1EvoCompiler.md)

| Type | Name |
| ---: | :--- |
|   | [**EvoCompiler**](classSR__SCRIPTING__NS_1_1EvoCompiler.md#function-evocompiler) (std::string cachePath) <br> |
|  SR\_NODISCARD EvoScript::CastingGen \* | [**GetCasting**](classSR__SCRIPTING__NS_1_1EvoCompiler.md#function-getcasting) () const<br> |
|  SR\_NODISCARD EvoScript::AddressTableGen \* | [**GetGenerator**](classSR__SCRIPTING__NS_1_1EvoCompiler.md#function-getgenerator) () const<br> |
| virtual bool | [**Init**](classSR__SCRIPTING__NS_1_1EvoCompiler.md#function-init) () override<br> |
|   | [**~EvoCompiler**](classSR__SCRIPTING__NS_1_1EvoCompiler.md#function-evocompiler) () override<br> |


## Public Functions inherited from SR_SCRIPTING_NS::Compiler

See [SR\_SCRIPTING\_NS::Compiler](classSR__SCRIPTING__NS_1_1Compiler.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**Init**](classSR__SCRIPTING__NS_1_1Compiler.md#function-init) () = 0<br> |
|   | [**~Compiler**](classSR__SCRIPTING__NS_1_1Compiler.md#function-compiler) () override<br> |


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
|  SR\_MAYBE\_UNUSED T & | [**Instance**](classSR__UTILS__NS_1_1Singleton.md#function-instance) () noexcept<br>_TODO: (Multi-threading) Refactor Singleton::Instance()._  |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](classSR__UTILS__NS_1_1Singleton.md#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-unlocksingleton) () noexcept<br> |












































## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |






## Protected Attributes inherited from SR_SCRIPTING_NS::Compiler

See [SR\_SCRIPTING\_NS::Compiler](classSR__SCRIPTING__NS_1_1Compiler.md)

| Type | Name |
| ---: | :--- |
|  Mutex | [**m\_mutex**](classSR__SCRIPTING__NS_1_1Compiler.md#variable-m_mutex)   = `Mutex()`<br> |






































































































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**GlobalEvoCompiler**](#function-globalevocompiler) () <br> |
| virtual void | [**OnSingletonDestroy**](#function-onsingletondestroy) () override<br> |
|   | [**~GlobalEvoCompiler**](#function-globalevocompiler) () override<br> |


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
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |




## Protected Functions inherited from SR_SCRIPTING_NS::Compiler

See [SR\_SCRIPTING\_NS::Compiler](classSR__SCRIPTING__NS_1_1Compiler.md)

| Type | Name |
| ---: | :--- |
|   | [**Compiler**](classSR__SCRIPTING__NS_1_1Compiler.md#function-compiler) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |
















## Protected Functions Documentation




### function GlobalEvoCompiler 

```C++
SR_SCRIPTING_NS::GlobalEvoCompiler::GlobalEvoCompiler () 
```




<hr>



### function OnSingletonDestroy 

```C++
inline virtual void SR_SCRIPTING_NS::GlobalEvoCompiler::OnSingletonDestroy () override
```



Implements [*SR\_UTILS\_NS::SingletonBase::OnSingletonDestroy*](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy)


<hr>



### function ~GlobalEvoCompiler 

```C++
SR_SCRIPTING_NS::GlobalEvoCompiler::~GlobalEvoCompiler () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Impl/EvoCompiler.h`

