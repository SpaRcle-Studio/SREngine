

# Class EvoScript::IState



[**ClassList**](annotated.md) **>** [**EvoScript**](namespaceEvoScript.md) **>** [**IState**](classEvoScript_1_1IState.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const std::string | [**Extension**](#variable-extension)   = `".UNKNOWN"`<br> |




























## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**Exists**](#function-exists) () = 0<br> |
|  Fn | [**GetFunction**](#function-getfunction) (const char \* name) <br> |
|  SR\_NODISCARD std::string | [**GetPath**](#function-getpath) () const<br> |
| virtual bool | [**Load**](#function-load) () = 0<br> |
| virtual bool | [**Unload**](#function-unload) () = 0<br> |
|   | [**~IState**](#function-istate) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**IState**](classEvoScript_1_1IState.md) \* | [**Allocate**](#function-allocate) (const std::string & path) <br> |












## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::string | [**m\_path**](#variable-m_path)  <br>_path to local module copy_  |
































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void \* | [**GetFunctionImpl**](#function-getfunctionimpl) (const char \* name) = 0<br> |
|   | [**IState**](#function-istate) (std::string path) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Static Attributes Documentation




### variable Extension 

```C++
const std::string EvoScript::IState::Extension;
```




<hr>
## Public Functions Documentation




### function Exists 

```C++
virtual bool EvoScript::IState::Exists () = 0
```




<hr>



### function GetFunction 

```C++
template<typename Fn>
inline Fn EvoScript::IState::GetFunction (
    const char * name
) 
```




<hr>



### function GetPath 

```C++
inline SR_NODISCARD std::string EvoScript::IState::GetPath () const
```




<hr>



### function Load 

```C++
virtual bool EvoScript::IState::Load () = 0
```




<hr>



### function Unload 

```C++
virtual bool EvoScript::IState::Unload () = 0
```




<hr>



### function ~IState 

```C++
EvoScript::IState::~IState () override
```




<hr>
## Public Static Functions Documentation




### function Allocate 

```C++
static IState * EvoScript::IState::Allocate (
    const std::string & path
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_path 

_path to local module copy_ 
```C++
std::string EvoScript::IState::m_path;
```




<hr>
## Protected Functions Documentation




### function GetFunctionImpl 

```C++
virtual void * EvoScript::IState::GetFunctionImpl (
    const char * name
) = 0
```




<hr>



### function IState 

```C++
inline explicit EvoScript::IState::IState (
    std::string path
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Scripting/inc/Scripting/Old/IState.h`

