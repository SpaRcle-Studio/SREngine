

# Class EvoScript::Script



[**ClassList**](annotated.md) **>** [**EvoScript**](namespaceEvoScript.md) **>** [**Script**](classEvoScript_1_1Script.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_INLINE Return | [**Call**](#function-call-17) (Fn fn, Args... args) <br> |
|  SR\_INLINE void | [**Call**](#function-call-27) (Fn fn, Args... args) <br> |
|  SR\_INLINE Return | [**Call**](#function-call-37) (Fn fn) <br> |
|  SR\_INLINE Return | [**Call**](#function-call-47) (const std::string & name, Args... args) <br> |
|  SR\_INLINE void | [**Call**](#function-call-57) (const std::string & name, Args... args) <br> |
|  SR\_INLINE Return | [**Call**](#function-call-67) (const std::string & name) <br> |
|  SR\_INLINE void | [**Call**](#function-call-77) (const std::string & name) <br> |
|  SR\_INLINE Fn | [**GetFunction**](#function-getfunction) (const std::string & name) <br> |
|  SR\_NODISCARD std::string | [**GetName**](#function-getname) () const<br> |
|  SR\_NODISCARD std::string | [**GetPath**](#function-getpath) () const<br> |
|  SR\_NODISCARD [**IState**](classEvoScript_1_1IState.md) \* | [**GetState**](#function-getstate) () const<br> |
|  SR\_INLINE bool | [**HasFunction**](#function-hasfunction) (const std::string & name) <br> |
|  SR\_NODISCARD bool | [**IsDebug**](#function-isdebug) () const<br> |
|  SR\_NODISCARD bool | [**IsDirty**](#function-isdirty) () const<br> |
|  bool | [**Load**](#function-load) (const std::string & path, [**Compiler**](classEvoScript_1_1Compiler.md) & compiler, bool compile) <br> |
|   | [**~Script**](#function-script) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Script**](classEvoScript_1_1Script.md) \* | [**Allocate**](#function-allocate) (const std::string & name, [**Compiler**](classEvoScript_1_1Compiler.md) \* pCompiler, MethodPointers methodPointers) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function Call [1/7]

```C++
template<typename Fn, typename Return, typename... Args>
inline SR_INLINE Return EvoScript::Script::Call (
    Fn fn,
    Args... args
) 
```




<hr>



### function Call [2/7]

```C++
template<typename Fn, typename... Args>
inline SR_INLINE void EvoScript::Script::Call (
    Fn fn,
    Args... args
) 
```




<hr>



### function Call [3/7]

```C++
template<typename Fn, typename Return>
inline SR_INLINE Return EvoScript::Script::Call (
    Fn fn
) 
```




<hr>



### function Call [4/7]

```C++
template<typename Fn, typename Return, typename... Args>
inline SR_INLINE Return EvoScript::Script::Call (
    const std::string & name,
    Args... args
) 
```




<hr>



### function Call [5/7]

```C++
template<typename Fn, typename... Args>
inline SR_INLINE void EvoScript::Script::Call (
    const std::string & name,
    Args... args
) 
```




<hr>



### function Call [6/7]

```C++
template<typename Fn, typename Return>
inline SR_INLINE Return EvoScript::Script::Call (
    const std::string & name
) 
```




<hr>



### function Call [7/7]

```C++
template<typename Fn>
inline SR_INLINE void EvoScript::Script::Call (
    const std::string & name
) 
```




<hr>



### function GetFunction 

```C++
template<typename Fn>
inline SR_INLINE Fn EvoScript::Script::GetFunction (
    const std::string & name
) 
```




<hr>



### function GetName 

```C++
inline SR_NODISCARD std::string EvoScript::Script::GetName () const
```




<hr>



### function GetPath 

```C++
inline SR_NODISCARD std::string EvoScript::Script::GetPath () const
```




<hr>



### function GetState 

```C++
inline SR_NODISCARD IState * EvoScript::Script::GetState () const
```




<hr>



### function HasFunction 

```C++
template<typename Fn>
inline SR_INLINE bool EvoScript::Script::HasFunction (
    const std::string & name
) 
```




<hr>



### function IsDebug 

```C++
inline SR_NODISCARD bool EvoScript::Script::IsDebug () const
```




<hr>



### function IsDirty 

```C++
SR_NODISCARD bool EvoScript::Script::IsDirty () const
```




<hr>



### function Load 

```C++
bool EvoScript::Script::Load (
    const std::string & path,
    Compiler & compiler,
    bool compile
) 
```




<hr>



### function ~Script 

```C++
EvoScript::Script::~Script () override
```




<hr>
## Public Static Functions Documentation




### function Allocate 

```C++
static Script * EvoScript::Script::Allocate (
    const std::string & name,
    Compiler * pCompiler,
    MethodPointers methodPointers
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Scripting/inc/Scripting/Old/Script.h`

