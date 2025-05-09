

# Class SR\_SCRIPTING\_NS::CppBehaviourInstance



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**CppBehaviourInstance**](classSR__SCRIPTING__NS_1_1CppBehaviourInstance.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Awake**](#function-awake) () <br> |
|  SR\_NODISCARD bool | [**ExecuteInEditMode**](#function-executeineditmode) () const<br> |
|  void | [**FixedUpdate**](#function-fixedupdate) () <br> |
|  SR\_NODISCARD CppBehaviour::Ptr & | [**GetBehaviour**](#function-getbehaviour-12) () <br> |
|  SR\_NODISCARD const CppBehaviour::Ptr & | [**GetBehaviour**](#function-getbehaviour-22) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetBehaviourName**](#function-getbehaviourname) () const<br> |
|  SR\_NODISCARD const LoadedCallback & | [**GetLoadedCallback**](#function-getloadedcallback) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetModuleName**](#function-getmodulename) () const<br> |
|  SR\_NODISCARD const PreReloadCalback & | [**GetPreReloadCallback**](#function-getprereloadcallback) () const<br> |
|  SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () const<br> |
|  void | [**OnAttached**](#function-onattached) () <br> |
|  void | [**OnBehaviourUnloaded**](#function-onbehaviourunloaded) (ManagerPasskey) <br> |
|  void | [**OnDestroy**](#function-ondestroy) () <br> |
|  void | [**OnDetached**](#function-ondetached) () <br> |
|  void | [**OnDisable**](#function-ondisable) () <br> |
|  void | [**OnEnable**](#function-onenable) () <br> |
|  void | [**SetBehaviourName**](#function-setbehaviourname) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, ManagerPasskey) <br> |
|  void | [**SetInstance**](#function-setinstance) (const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**CppBehaviour**](classSR__SCRIPTING__NS_1_1CppBehaviour.md) &gt; & pBehaviour, ManagerPasskey) <br> |
|  void | [**SetLoadedCallback**](#function-setloadedcallback) (const LoadedCallback & callback) <br> |
|  void | [**SetModuleName**](#function-setmodulename) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, ManagerPasskey) <br> |
|  void | [**SetPreReloadCallback**](#function-setprereloadcallback) (const PreReloadCalback & callback) <br> |
|  void | [**SetSceneObject**](#function-setsceneobject) (const SR\_UTILS\_NS::SceneObject::Ptr & pSceneObject) <br> |
|  void | [**Start**](#function-start) () <br> |
|  void | [**Update**](#function-update) (float\_t dt) <br> |




























## Public Functions Documentation




### function Awake 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::Awake () 
```




<hr>



### function ExecuteInEditMode 

```C++
SR_NODISCARD bool SR_SCRIPTING_NS::CppBehaviourInstance::ExecuteInEditMode () const
```




<hr>



### function FixedUpdate 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::FixedUpdate () 
```




<hr>



### function GetBehaviour [1/2]

```C++
inline SR_NODISCARD CppBehaviour::Ptr & SR_SCRIPTING_NS::CppBehaviourInstance::GetBehaviour () 
```




<hr>



### function GetBehaviour [2/2]

```C++
inline SR_NODISCARD const CppBehaviour::Ptr & SR_SCRIPTING_NS::CppBehaviourInstance::GetBehaviour () const
```




<hr>



### function GetBehaviourName 

```C++
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_SCRIPTING_NS::CppBehaviourInstance::GetBehaviourName () const
```




<hr>



### function GetLoadedCallback 

```C++
inline SR_NODISCARD const LoadedCallback & SR_SCRIPTING_NS::CppBehaviourInstance::GetLoadedCallback () const
```




<hr>



### function GetModuleName 

```C++
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_SCRIPTING_NS::CppBehaviourInstance::GetModuleName () const
```




<hr>



### function GetPreReloadCallback 

```C++
inline SR_NODISCARD const PreReloadCalback & SR_SCRIPTING_NS::CppBehaviourInstance::GetPreReloadCallback () const
```




<hr>



### function IsValid 

```C++
inline SR_NODISCARD bool SR_SCRIPTING_NS::CppBehaviourInstance::IsValid () const
```




<hr>



### function OnAttached 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::OnAttached () 
```




<hr>



### function OnBehaviourUnloaded 

```C++
void SR_SCRIPTING_NS::CppBehaviourInstance::OnBehaviourUnloaded (
    ManagerPasskey
) 
```




<hr>



### function OnDestroy 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::OnDestroy () 
```




<hr>



### function OnDetached 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::OnDetached () 
```




<hr>



### function OnDisable 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::OnDisable () 
```




<hr>



### function OnEnable 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::OnEnable () 
```




<hr>



### function SetBehaviourName 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::SetBehaviourName (
    SR_UTILS_NS::StringAtom name,
    ManagerPasskey
) 
```




<hr>



### function SetInstance 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::SetInstance (
    const SR_HTYPES_NS::SharedPtr < CppBehaviour > & pBehaviour,
    ManagerPasskey
) 
```




<hr>



### function SetLoadedCallback 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::SetLoadedCallback (
    const LoadedCallback & callback
) 
```




<hr>



### function SetModuleName 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::SetModuleName (
    SR_UTILS_NS::StringAtom name,
    ManagerPasskey
) 
```




<hr>



### function SetPreReloadCallback 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::SetPreReloadCallback (
    const PreReloadCalback & callback
) 
```




<hr>



### function SetSceneObject 

```C++
void SR_SCRIPTING_NS::CppBehaviourInstance::SetSceneObject (
    const SR_UTILS_NS::SceneObject::Ptr & pSceneObject
) 
```




<hr>



### function Start 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::Start () 
```




<hr>



### function Update 

```C++
inline void SR_SCRIPTING_NS::CppBehaviourInstance::Update (
    float_t dt
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Cpp/ModuleManager.h`

