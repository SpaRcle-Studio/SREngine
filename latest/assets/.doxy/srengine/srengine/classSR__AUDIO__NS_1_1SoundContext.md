

# Class SR\_AUDIO\_NS::SoundContext



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**SoundContext**](classSR__AUDIO__NS_1_1SoundContext.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_AUDIO\_NS::OpenALSoundContext](classSR__AUDIO__NS_1_1OpenALSoundContext.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SoundBuffer | [**AllocateBuffer**](#function-allocatebuffer) (void \* data, uint64\_t dataSize, int32\_t sampleRate, SoundFormat format) = 0<br> |
| virtual SR\_NODISCARD [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* | [**AllocateListener**](#function-allocatelistener) () <br> |
| virtual SR\_NODISCARD SoundSource | [**AllocateSource**](#function-allocatesource) (SoundBuffer buffer) = 0<br> |
|  void | [**ApplyParam**](#function-applyparam-12) (SoundSource pSource, const T & newParam, T & currentParam, PlayParamType paramType) <br> |
|  void | [**ApplyParam**](#function-applyparam-22) (SoundSource pSource, const T & newParam, PlayParamType paramType) <br> |
| virtual void | [**ApplyParamImpl**](#function-applyparamimpl) (SoundSource pSource, PlayParamType paramType, const void \* pValue) = 0<br> |
| virtual void | [**ApplyParams**](#function-applyparams) (SoundSource pSource, const [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) & params) <br> |
| virtual bool | [**FreeBuffer**](#function-freebuffer) (SoundBuffer \* buffer) = 0<br> |
| virtual bool | [**FreeListener**](#function-freelistener) ([**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* pListener) <br> |
| virtual bool | [**FreeSource**](#function-freesource) (SoundSource \* pSource) = 0<br> |
|  SR\_NODISCARD [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* | [**GetDevice**](#function-getdevice) () const<br> |
| virtual SR\_NODISCARD [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) | [**GetSourceParams**](#function-getsourceparams) (SoundSource pSource) const = 0<br> |
| virtual bool | [**Init**](#function-init) () = 0<br> |
| virtual SR\_NODISCARD bool | [**IsPaused**](#function-ispaused) (SoundSource pSource) const = 0<br> |
| virtual SR\_NODISCARD bool | [**IsPlaying**](#function-isplaying) (SoundSource pSource) const = 0<br> |
| virtual SR\_NODISCARD bool | [**IsStopped**](#function-isstopped) (SoundSource pSource) const = 0<br> |
| virtual SR\_NODISCARD bool | [**MakeContextCurrent**](#function-makecontextcurrent) () = 0<br> |
| virtual void | [**Play**](#function-play) (SoundSource source) = 0<br> |
|   | [**~SoundContext**](#function-soundcontext) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**SoundContext**](classSR__AUDIO__NS_1_1SoundContext.md) \* | [**Allocate**](#function-allocate) ([**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* pDevice) <br> |












## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* | [**m\_device**](#variable-m_device)   = `nullptr`<br> |
|  std::list&lt; [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* &gt; | [**m\_listeners**](#variable-m_listeners)  <br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**SoundContext**](#function-soundcontext) ([**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* pDevice) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function AllocateBuffer 

```C++
virtual SR_NODISCARD SoundBuffer SR_AUDIO_NS::SoundContext::AllocateBuffer (
    void * data,
    uint64_t dataSize,
    int32_t sampleRate,
    SoundFormat format
) = 0
```




<hr>



### function AllocateListener 

```C++
virtual SR_NODISCARD SoundListener * SR_AUDIO_NS::SoundContext::AllocateListener () 
```




<hr>



### function AllocateSource 

```C++
virtual SR_NODISCARD SoundSource SR_AUDIO_NS::SoundContext::AllocateSource (
    SoundBuffer buffer
) = 0
```




<hr>



### function ApplyParam [1/2]

```C++
template<typename T>
inline void SR_AUDIO_NS::SoundContext::ApplyParam (
    SoundSource pSource,
    const T & newParam,
    T & currentParam,
    PlayParamType paramType
) 
```




<hr>



### function ApplyParam [2/2]

```C++
template<typename T>
inline void SR_AUDIO_NS::SoundContext::ApplyParam (
    SoundSource pSource,
    const T & newParam,
    PlayParamType paramType
) 
```




<hr>



### function ApplyParamImpl 

```C++
virtual void SR_AUDIO_NS::SoundContext::ApplyParamImpl (
    SoundSource pSource,
    PlayParamType paramType,
    const void * pValue
) = 0
```




<hr>



### function ApplyParams 

```C++
virtual void SR_AUDIO_NS::SoundContext::ApplyParams (
    SoundSource pSource,
    const PlayParams & params
) 
```




<hr>



### function FreeBuffer 

```C++
virtual bool SR_AUDIO_NS::SoundContext::FreeBuffer (
    SoundBuffer * buffer
) = 0
```




<hr>



### function FreeListener 

```C++
virtual bool SR_AUDIO_NS::SoundContext::FreeListener (
    SoundListener * pListener
) 
```




<hr>



### function FreeSource 

```C++
virtual bool SR_AUDIO_NS::SoundContext::FreeSource (
    SoundSource * pSource
) = 0
```




<hr>



### function GetDevice 

```C++
SR_NODISCARD SoundDevice * SR_AUDIO_NS::SoundContext::GetDevice () const
```




<hr>



### function GetSourceParams 

```C++
virtual SR_NODISCARD PlayParams SR_AUDIO_NS::SoundContext::GetSourceParams (
    SoundSource pSource
) const = 0
```




<hr>



### function Init 

```C++
virtual bool SR_AUDIO_NS::SoundContext::Init () = 0
```




<hr>



### function IsPaused 

```C++
virtual SR_NODISCARD bool SR_AUDIO_NS::SoundContext::IsPaused (
    SoundSource pSource
) const = 0
```




<hr>



### function IsPlaying 

```C++
virtual SR_NODISCARD bool SR_AUDIO_NS::SoundContext::IsPlaying (
    SoundSource pSource
) const = 0
```




<hr>



### function IsStopped 

```C++
virtual SR_NODISCARD bool SR_AUDIO_NS::SoundContext::IsStopped (
    SoundSource pSource
) const = 0
```




<hr>



### function MakeContextCurrent 

```C++
virtual SR_NODISCARD bool SR_AUDIO_NS::SoundContext::MakeContextCurrent () = 0
```




<hr>



### function Play 

```C++
virtual void SR_AUDIO_NS::SoundContext::Play (
    SoundSource source
) = 0
```




<hr>



### function ~SoundContext 

```C++
SR_AUDIO_NS::SoundContext::~SoundContext () override
```




<hr>
## Public Static Functions Documentation




### function Allocate 

```C++
static SoundContext * SR_AUDIO_NS::SoundContext::Allocate (
    SoundDevice * pDevice
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_device 

```C++
SoundDevice* SR_AUDIO_NS::SoundContext::m_device;
```




<hr>



### variable m\_listeners 

```C++
std::list<SoundListener*> SR_AUDIO_NS::SoundContext::m_listeners;
```




<hr>
## Protected Functions Documentation




### function SoundContext 

```C++
explicit SR_AUDIO_NS::SoundContext::SoundContext (
    SoundDevice * pDevice
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Audio/inc/Audio/SoundContext.h`

