

# Class SR\_AUDIO\_NS::OpenALSoundContext



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**OpenALSoundContext**](classSR__AUDIO__NS_1_1OpenALSoundContext.md)








Inherits the following classes: [SR\_AUDIO\_NS::SoundContext](classSR__AUDIO__NS_1_1SoundContext.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SoundBuffer | [**AllocateBuffer**](#function-allocatebuffer) (void \* data, uint64\_t dataSize, int32\_t sampleRate, SoundFormat format) override<br> |
| virtual SR\_NODISCARD SoundSource | [**AllocateSource**](#function-allocatesource) (SoundBuffer buffer) override<br> |
| virtual void | [**ApplyParamImpl**](#function-applyparamimpl) (SoundSource pSource, PlayParamType paramType, const void \* pValue) override<br> |
| virtual bool | [**FreeBuffer**](#function-freebuffer) (SoundBuffer \* buffer) override<br> |
| virtual bool | [**FreeSource**](#function-freesource) (SoundSource \* pSource) override<br> |
| virtual SR\_NODISCARD [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) | [**GetSourceParams**](#function-getsourceparams) (SoundSource pSource) override const<br> |
| virtual bool | [**Init**](#function-init) () override<br> |
| virtual SR\_NODISCARD bool | [**IsPaused**](#function-ispaused) (SoundSource pSource) override const<br> |
| virtual SR\_NODISCARD bool | [**IsPlaying**](#function-isplaying) (SoundSource pSource) override const<br> |
| virtual SR\_NODISCARD bool | [**IsStopped**](#function-isstopped) (SoundSource pSource) override const<br> |
| virtual bool | [**MakeContextCurrent**](#function-makecontextcurrent) () override<br> |
|   | [**OpenALSoundContext**](#function-openalsoundcontext) ([**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* pDevice) <br> |
| virtual void | [**Play**](#function-play) (SoundSource source) override<br> |
|   | [**~OpenALSoundContext**](#function-openalsoundcontext) () override<br> |


## Public Functions inherited from SR_AUDIO_NS::SoundContext

See [SR\_AUDIO\_NS::SoundContext](classSR__AUDIO__NS_1_1SoundContext.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SoundBuffer | [**AllocateBuffer**](classSR__AUDIO__NS_1_1SoundContext.md#function-allocatebuffer) (void \* data, uint64\_t dataSize, int32\_t sampleRate, SoundFormat format) = 0<br> |
| virtual SR\_NODISCARD [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* | [**AllocateListener**](classSR__AUDIO__NS_1_1SoundContext.md#function-allocatelistener) () <br> |
| virtual SR\_NODISCARD SoundSource | [**AllocateSource**](classSR__AUDIO__NS_1_1SoundContext.md#function-allocatesource) (SoundBuffer buffer) = 0<br> |
|  void | [**ApplyParam**](classSR__AUDIO__NS_1_1SoundContext.md#function-applyparam-12) (SoundSource pSource, const T & newParam, T & currentParam, PlayParamType paramType) <br> |
|  void | [**ApplyParam**](classSR__AUDIO__NS_1_1SoundContext.md#function-applyparam-22) (SoundSource pSource, const T & newParam, PlayParamType paramType) <br> |
| virtual void | [**ApplyParamImpl**](classSR__AUDIO__NS_1_1SoundContext.md#function-applyparamimpl) (SoundSource pSource, PlayParamType paramType, const void \* pValue) = 0<br> |
| virtual void | [**ApplyParams**](classSR__AUDIO__NS_1_1SoundContext.md#function-applyparams) (SoundSource pSource, const [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) & params) <br> |
| virtual bool | [**FreeBuffer**](classSR__AUDIO__NS_1_1SoundContext.md#function-freebuffer) (SoundBuffer \* buffer) = 0<br> |
| virtual bool | [**FreeListener**](classSR__AUDIO__NS_1_1SoundContext.md#function-freelistener) ([**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* pListener) <br> |
| virtual bool | [**FreeSource**](classSR__AUDIO__NS_1_1SoundContext.md#function-freesource) (SoundSource \* pSource) = 0<br> |
|  SR\_NODISCARD [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* | [**GetDevice**](classSR__AUDIO__NS_1_1SoundContext.md#function-getdevice) () const<br> |
| virtual SR\_NODISCARD [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) | [**GetSourceParams**](classSR__AUDIO__NS_1_1SoundContext.md#function-getsourceparams) (SoundSource pSource) const = 0<br> |
| virtual bool | [**Init**](classSR__AUDIO__NS_1_1SoundContext.md#function-init) () = 0<br> |
| virtual SR\_NODISCARD bool | [**IsPaused**](classSR__AUDIO__NS_1_1SoundContext.md#function-ispaused) (SoundSource pSource) const = 0<br> |
| virtual SR\_NODISCARD bool | [**IsPlaying**](classSR__AUDIO__NS_1_1SoundContext.md#function-isplaying) (SoundSource pSource) const = 0<br> |
| virtual SR\_NODISCARD bool | [**IsStopped**](classSR__AUDIO__NS_1_1SoundContext.md#function-isstopped) (SoundSource pSource) const = 0<br> |
| virtual SR\_NODISCARD bool | [**MakeContextCurrent**](classSR__AUDIO__NS_1_1SoundContext.md#function-makecontextcurrent) () = 0<br> |
| virtual void | [**Play**](classSR__AUDIO__NS_1_1SoundContext.md#function-play) (SoundSource source) = 0<br> |
|   | [**~SoundContext**](classSR__AUDIO__NS_1_1SoundContext.md#function-soundcontext) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |




## Public Static Functions inherited from SR_AUDIO_NS::SoundContext

See [SR\_AUDIO\_NS::SoundContext](classSR__AUDIO__NS_1_1SoundContext.md)

| Type | Name |
| ---: | :--- |
|  [**SoundContext**](classSR__AUDIO__NS_1_1SoundContext.md) \* | [**Allocate**](classSR__AUDIO__NS_1_1SoundContext.md#function-allocate) ([**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* pDevice) <br> |


















## Protected Attributes inherited from SR_AUDIO_NS::SoundContext

See [SR\_AUDIO\_NS::SoundContext](classSR__AUDIO__NS_1_1SoundContext.md)

| Type | Name |
| ---: | :--- |
|  [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* | [**m\_device**](classSR__AUDIO__NS_1_1SoundContext.md#variable-m_device)   = `nullptr`<br> |
|  std::list&lt; [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* &gt; | [**m\_listeners**](classSR__AUDIO__NS_1_1SoundContext.md#variable-m_listeners)  <br> |
















































## Protected Functions inherited from SR_AUDIO_NS::SoundContext

See [SR\_AUDIO\_NS::SoundContext](classSR__AUDIO__NS_1_1SoundContext.md)

| Type | Name |
| ---: | :--- |
|   | [**SoundContext**](classSR__AUDIO__NS_1_1SoundContext.md#function-soundcontext) ([**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* pDevice) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |








## Public Functions Documentation




### function AllocateBuffer 

```C++
virtual SR_NODISCARD SoundBuffer SR_AUDIO_NS::OpenALSoundContext::AllocateBuffer (
    void * data,
    uint64_t dataSize,
    int32_t sampleRate,
    SoundFormat format
) override
```



Implements [*SR\_AUDIO\_NS::SoundContext::AllocateBuffer*](classSR__AUDIO__NS_1_1SoundContext.md#function-allocatebuffer)


<hr>



### function AllocateSource 

```C++
virtual SR_NODISCARD SoundSource SR_AUDIO_NS::OpenALSoundContext::AllocateSource (
    SoundBuffer buffer
) override
```



Implements [*SR\_AUDIO\_NS::SoundContext::AllocateSource*](classSR__AUDIO__NS_1_1SoundContext.md#function-allocatesource)


<hr>



### function ApplyParamImpl 

```C++
virtual void SR_AUDIO_NS::OpenALSoundContext::ApplyParamImpl (
    SoundSource pSource,
    PlayParamType paramType,
    const void * pValue
) override
```



Implements [*SR\_AUDIO\_NS::SoundContext::ApplyParamImpl*](classSR__AUDIO__NS_1_1SoundContext.md#function-applyparamimpl)


<hr>



### function FreeBuffer 

```C++
virtual bool SR_AUDIO_NS::OpenALSoundContext::FreeBuffer (
    SoundBuffer * buffer
) override
```



Implements [*SR\_AUDIO\_NS::SoundContext::FreeBuffer*](classSR__AUDIO__NS_1_1SoundContext.md#function-freebuffer)


<hr>



### function FreeSource 

```C++
virtual bool SR_AUDIO_NS::OpenALSoundContext::FreeSource (
    SoundSource * pSource
) override
```



Implements [*SR\_AUDIO\_NS::SoundContext::FreeSource*](classSR__AUDIO__NS_1_1SoundContext.md#function-freesource)


<hr>



### function GetSourceParams 

```C++
virtual SR_NODISCARD PlayParams SR_AUDIO_NS::OpenALSoundContext::GetSourceParams (
    SoundSource pSource
) override const
```



Implements [*SR\_AUDIO\_NS::SoundContext::GetSourceParams*](classSR__AUDIO__NS_1_1SoundContext.md#function-getsourceparams)


<hr>



### function Init 

```C++
virtual bool SR_AUDIO_NS::OpenALSoundContext::Init () override
```



Implements [*SR\_AUDIO\_NS::SoundContext::Init*](classSR__AUDIO__NS_1_1SoundContext.md#function-init)


<hr>



### function IsPaused 

```C++
virtual SR_NODISCARD bool SR_AUDIO_NS::OpenALSoundContext::IsPaused (
    SoundSource pSource
) override const
```



Implements [*SR\_AUDIO\_NS::SoundContext::IsPaused*](classSR__AUDIO__NS_1_1SoundContext.md#function-ispaused)


<hr>



### function IsPlaying 

```C++
virtual SR_NODISCARD bool SR_AUDIO_NS::OpenALSoundContext::IsPlaying (
    SoundSource pSource
) override const
```



Implements [*SR\_AUDIO\_NS::SoundContext::IsPlaying*](classSR__AUDIO__NS_1_1SoundContext.md#function-isplaying)


<hr>



### function IsStopped 

```C++
virtual SR_NODISCARD bool SR_AUDIO_NS::OpenALSoundContext::IsStopped (
    SoundSource pSource
) override const
```



Implements [*SR\_AUDIO\_NS::SoundContext::IsStopped*](classSR__AUDIO__NS_1_1SoundContext.md#function-isstopped)


<hr>



### function MakeContextCurrent 

```C++
virtual bool SR_AUDIO_NS::OpenALSoundContext::MakeContextCurrent () override
```



Implements [*SR\_AUDIO\_NS::SoundContext::MakeContextCurrent*](classSR__AUDIO__NS_1_1SoundContext.md#function-makecontextcurrent)


<hr>



### function OpenALSoundContext 

```C++
explicit SR_AUDIO_NS::OpenALSoundContext::OpenALSoundContext (
    SoundDevice * pDevice
) 
```




<hr>



### function Play 

```C++
virtual void SR_AUDIO_NS::OpenALSoundContext::Play (
    SoundSource source
) override
```



Implements [*SR\_AUDIO\_NS::SoundContext::Play*](classSR__AUDIO__NS_1_1SoundContext.md#function-play)


<hr>



### function ~OpenALSoundContext 

```C++
SR_AUDIO_NS::OpenALSoundContext::~OpenALSoundContext () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Audio/inc/Audio/Impl/OpenALSoundContext.h`

