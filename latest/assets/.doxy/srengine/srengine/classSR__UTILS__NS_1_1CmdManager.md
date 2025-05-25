

# Class SR\_UTILS\_NS::CmdManager



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**CmdManager**](classSR__UTILS__NS_1_1CmdManager.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Cancel**](#function-cancel) () <br> |
|  void | [**Clear**](#function-clear) () <br> |
|   | [**CmdManager**](#function-cmdmanager) () = default<br> |
|  bool | [**Execute**](#function-execute-13) ([**ReversibleCommand**](classSR__UTILS__NS_1_1ReversibleCommand.md) \* cmd, SyncType sync) <br> |
|  bool | [**Execute**](#function-execute-23) (SyncType sync, Args &&... args) <br> |
|  SR\_NODISCARD uint32\_t | [**GetHistoryPC**](#function-gethistorypc) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetHistorySize**](#function-gethistorysize) () const<br> |
|  SR\_NODISCARD std::string | [**GetLastCmdName**](#function-getlastcmdname) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetMaxHistorySize**](#function-getmaxhistorysize) () const<br> |
|  bool | [**Redo**](#function-redo) () <br> |
|  void | [**SetMaxHistorySize**](#function-setmaxhistorysize) (uint32\_t size) <br> |
|  void | [**Store**](#function-store) ([**ReversibleCommand**](classSR__UTILS__NS_1_1ReversibleCommand.md) \* cmd) <br> |
|  void | [**Update**](#function-update) () <br> |
|   | [**~CmdManager**](#function-cmdmanager) () override<br> |


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




### function Cancel 

```C++
bool SR_UTILS_NS::CmdManager::Cancel () 
```




<hr>



### function Clear 

```C++
void SR_UTILS_NS::CmdManager::Clear () 
```




<hr>



### function CmdManager 

```C++
SR_UTILS_NS::CmdManager::CmdManager () = default
```




<hr>



### function Execute [1/3]

```C++
bool SR_UTILS_NS::CmdManager::Execute (
    ReversibleCommand * cmd,
    SyncType sync
) 
```




<hr>



### function Execute [2/3]

```C++
template<typename T, typename... Args>
inline bool SR_UTILS_NS::CmdManager::Execute (
    SyncType sync,
    Args &&... args
) 
```




<hr>



### function GetHistoryPC 

```C++
SR_NODISCARD uint32_t SR_UTILS_NS::CmdManager::GetHistoryPC () const
```




<hr>



### function GetHistorySize 

```C++
SR_NODISCARD uint32_t SR_UTILS_NS::CmdManager::GetHistorySize () const
```




<hr>



### function GetLastCmdName 

```C++
SR_NODISCARD std::string SR_UTILS_NS::CmdManager::GetLastCmdName () const
```




<hr>



### function GetMaxHistorySize 

```C++
SR_NODISCARD uint32_t SR_UTILS_NS::CmdManager::GetMaxHistorySize () const
```




<hr>



### function Redo 

```C++
bool SR_UTILS_NS::CmdManager::Redo () 
```




<hr>



### function SetMaxHistorySize 

```C++
void SR_UTILS_NS::CmdManager::SetMaxHistorySize (
    uint32_t size
) 
```




<hr>



### function Store 

```C++
void SR_UTILS_NS::CmdManager::Store (
    ReversibleCommand * cmd
) 
```




<hr>



### function Update 

```C++
void SR_UTILS_NS::CmdManager::Update () 
```




<hr>



### function ~CmdManager 

```C++
SR_UTILS_NS::CmdManager::~CmdManager () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/CommandManager/CmdManager.h`

