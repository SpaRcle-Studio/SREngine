

# Class SR\_AUDIO\_NS::SoundManager



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**SoundManager**](classSR__AUDIO__NS_1_1SoundManager.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef void \* | [**Handle**](#typedef-handle)  <br> |
| enum uint8\_t | [**State**](#enum-state)  <br> |
















































































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ApplyParams**](#function-applyparams) (Handle pHandle, const [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) & params) <br> |
|  SR\_NODISCARD [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* | [**CreateListener**](#function-createlistener-12) () <br> |
|  SR\_NODISCARD [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* | [**CreateListener**](#function-createlistener-22) (AudioLibrary library) <br> |
|  void | [**DestroyListener**](#function-destroylistener) ([**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* pListener) <br> |
|  SR\_NODISCARD std::optional&lt; [**ListenerData**](structSR__AUDIO__NS_1_1ListenerData.md) &gt; | [**GetListenerParams**](#function-getlistenerparams) (const [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* pListener) const<br> |
|  SR\_NODISCARD const std::set&lt; [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* &gt; & | [**GetListeners**](#function-getlisteners) () noexcept const<br> |
|  SR\_NODISCARD const std::list&lt; [**PlayData**](structSR__AUDIO__NS_1_1PlayData.md) \* &gt; & | [**GetPlayStack**](#function-getplaystack) () noexcept const<br> |
|  SR\_NODISCARD std::optional&lt; [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) &gt; | [**GetSourceParams**](#function-getsourceparams) (const [**PlayData**](structSR__AUDIO__NS_1_1PlayData.md) \* pPlayData) const<br> |
|  SR\_NODISCARD SR\_HTYPES\_NS::Thread::ThreadId | [**GetThreadId**](#function-getthreadid) () noexcept const<br> |
|  bool | [**IsExists**](#function-isexists) (Handle pHandle) const<br> |
|  bool | [**IsFailed**](#function-isfailed) (Handle pHandle) const<br> |
|  bool | [**IsInitialized**](#function-isinitialized) (Handle pHandle) const<br> |
|  bool | [**IsPlaying**](#function-isplaying) (Handle pHandle) const<br> |
|  Handle | [**Play**](#function-play-13) (const std::string & path) <br> |
|  Handle | [**Play**](#function-play-23) (const std::string & path, const [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) & params) <br> |
|  Handle | [**Play**](#function-play-33) ([**Sound**](classSR__AUDIO__NS_1_1Sound.md) \* pSound, const [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) & params) <br> |
|  [**SoundData**](structSR__AUDIO__NS_1_1SoundData.md) \* | [**Register**](#function-register) ([**Sound**](classSR__AUDIO__NS_1_1Sound.md) \* pSound) <br> |
|  void | [**SetListenerDistanceModel**](#function-setlistenerdistancemodel) ([**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* pListenerContext, ListenerDistanceModel distanceModel) <br> |
|  void | [**SetListenerGain**](#function-setlistenergain) ([**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* pListenerContext, float\_t gain) <br> |
|  void | [**SetListenerTransform**](#function-setlistenertransform) ([**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* pListenerContext, const SR\_MATH\_NS::FVector3 & position, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) <br> |
|  void | [**SetListenerVelocity**](#function-setlistenervelocity) ([**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* pListenerContext, SR\_MATH\_NS::FVector3 velocity) <br> |
|  void | [**Stop**](#function-stop) (Handle pHandle) <br> |
|  void | [**StopAll**](#function-stopall) () <br> |
|  bool | [**Unregister**](#function-unregister) ([**SoundData**](structSR__AUDIO__NS_1_1SoundData.md) \*\* pSoundData) <br> |




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
|  void | [**Destroy**](#function-destroy) () <br> |
|  void | [**DestroyPlayData**](#function-destroyplaydata) ([**PlayData**](structSR__AUDIO__NS_1_1PlayData.md) \* pPlayData) <br> |
|  SR\_NODISCARD AudioLibrary | [**GetRelevantLibrary**](#function-getrelevantlibrary) () noexcept const<br> |
|  SR\_NODISCARD [**SoundContext**](classSR__AUDIO__NS_1_1SoundContext.md) \* | [**GetSoundContext**](#function-getsoundcontext) (const [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) & params) noexcept<br> |
| virtual void | [**InitSingleton**](#function-initsingleton) () override<br> |
| virtual void | [**OnSingletonDestroy**](#function-onsingletondestroy) () override<br> |
|  bool | [**PlayInternal**](#function-playinternal) ([**PlayData**](structSR__AUDIO__NS_1_1PlayData.md) \* pPlayData) <br> |
|  bool | [**PrepareData**](#function-preparedata) ([**PlayData**](structSR__AUDIO__NS_1_1PlayData.md) \* pPlayData) <br> |
|  void | [**Update**](#function-update) () <br> |


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










## Public Types Documentation




### typedef Handle 

```C++
using SR_AUDIO_NS::SoundManager::Handle =  void*;
```




<hr>



### enum State 

```C++
enum SR_AUDIO_NS::SoundManager::State {
    Stopped,
    Active,
    Paused
};
```




<hr>
## Public Functions Documentation




### function ApplyParams 

```C++
void SR_AUDIO_NS::SoundManager::ApplyParams (
    Handle pHandle,
    const PlayParams & params
) 
```




<hr>



### function CreateListener [1/2]

```C++
SR_NODISCARD SoundListener * SR_AUDIO_NS::SoundManager::CreateListener () 
```




<hr>



### function CreateListener [2/2]

```C++
SR_NODISCARD SoundListener * SR_AUDIO_NS::SoundManager::CreateListener (
    AudioLibrary library
) 
```




<hr>



### function DestroyListener 

```C++
void SR_AUDIO_NS::SoundManager::DestroyListener (
    SoundListener * pListener
) 
```




<hr>



### function GetListenerParams 

```C++
SR_NODISCARD std::optional< ListenerData > SR_AUDIO_NS::SoundManager::GetListenerParams (
    const SoundListener * pListener
) const
```




<hr>



### function GetListeners 

```C++
inline SR_NODISCARD const std::set< SoundListener * > & SR_AUDIO_NS::SoundManager::GetListeners () noexcept const
```




<hr>



### function GetPlayStack 

```C++
inline SR_NODISCARD const std::list< PlayData * > & SR_AUDIO_NS::SoundManager::GetPlayStack () noexcept const
```




<hr>



### function GetSourceParams 

```C++
SR_NODISCARD std::optional< PlayParams > SR_AUDIO_NS::SoundManager::GetSourceParams (
    const PlayData * pPlayData
) const
```




<hr>



### function GetThreadId 

```C++
inline SR_NODISCARD SR_HTYPES_NS::Thread::ThreadId SR_AUDIO_NS::SoundManager::GetThreadId () noexcept const
```




<hr>



### function IsExists 

```C++
bool SR_AUDIO_NS::SoundManager::IsExists (
    Handle pHandle
) const
```




<hr>



### function IsFailed 

```C++
bool SR_AUDIO_NS::SoundManager::IsFailed (
    Handle pHandle
) const
```




<hr>



### function IsInitialized 

```C++
bool SR_AUDIO_NS::SoundManager::IsInitialized (
    Handle pHandle
) const
```




<hr>



### function IsPlaying 

```C++
bool SR_AUDIO_NS::SoundManager::IsPlaying (
    Handle pHandle
) const
```




<hr>



### function Play [1/3]

```C++
Handle SR_AUDIO_NS::SoundManager::Play (
    const std::string & path
) 
```




<hr>



### function Play [2/3]

```C++
Handle SR_AUDIO_NS::SoundManager::Play (
    const std::string & path,
    const PlayParams & params
) 
```




<hr>



### function Play [3/3]

```C++
Handle SR_AUDIO_NS::SoundManager::Play (
    Sound * pSound,
    const PlayParams & params
) 
```




<hr>



### function Register 

```C++
SoundData * SR_AUDIO_NS::SoundManager::Register (
    Sound * pSound
) 
```




<hr>



### function SetListenerDistanceModel 

```C++
void SR_AUDIO_NS::SoundManager::SetListenerDistanceModel (
    SoundListener * pListenerContext,
    ListenerDistanceModel distanceModel
) 
```




<hr>



### function SetListenerGain 

```C++
void SR_AUDIO_NS::SoundManager::SetListenerGain (
    SoundListener * pListenerContext,
    float_t gain
) 
```




<hr>



### function SetListenerTransform 

```C++
void SR_AUDIO_NS::SoundManager::SetListenerTransform (
    SoundListener * pListenerContext,
    const SR_MATH_NS::FVector3 & position,
    const SR_MATH_NS::Quaternion & quaternion
) 
```




<hr>



### function SetListenerVelocity 

```C++
void SR_AUDIO_NS::SoundManager::SetListenerVelocity (
    SoundListener * pListenerContext,
    SR_MATH_NS::FVector3 velocity
) 
```




<hr>



### function Stop 

```C++
void SR_AUDIO_NS::SoundManager::Stop (
    Handle pHandle
) 
```




<hr>



### function StopAll 

```C++
void SR_AUDIO_NS::SoundManager::StopAll () 
```




<hr>



### function Unregister 

```C++
bool SR_AUDIO_NS::SoundManager::Unregister (
    SoundData ** pSoundData
) 
```




<hr>
## Protected Functions Documentation




### function Destroy 

```C++
void SR_AUDIO_NS::SoundManager::Destroy () 
```




<hr>



### function DestroyPlayData 

```C++
void SR_AUDIO_NS::SoundManager::DestroyPlayData (
    PlayData * pPlayData
) 
```




<hr>



### function GetRelevantLibrary 

```C++
SR_NODISCARD AudioLibrary SR_AUDIO_NS::SoundManager::GetRelevantLibrary () noexcept const
```




<hr>



### function GetSoundContext 

```C++
SR_NODISCARD SoundContext * SR_AUDIO_NS::SoundManager::GetSoundContext (
    const PlayParams & params
) noexcept
```




<hr>



### function InitSingleton 

```C++
virtual void SR_AUDIO_NS::SoundManager::InitSingleton () override
```



Implements [*SR\_UTILS\_NS::SingletonBase::InitSingleton*](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton)


<hr>



### function OnSingletonDestroy 

```C++
virtual void SR_AUDIO_NS::SoundManager::OnSingletonDestroy () override
```



Implements [*SR\_UTILS\_NS::SingletonBase::OnSingletonDestroy*](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy)


<hr>



### function PlayInternal 

```C++
bool SR_AUDIO_NS::SoundManager::PlayInternal (
    PlayData * pPlayData
) 
```




<hr>



### function PrepareData 

```C++
bool SR_AUDIO_NS::SoundManager::PrepareData (
    PlayData * pPlayData
) 
```




<hr>



### function Update 

```C++
void SR_AUDIO_NS::SoundManager::Update () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Audio/inc/Audio/SoundManager.h`

