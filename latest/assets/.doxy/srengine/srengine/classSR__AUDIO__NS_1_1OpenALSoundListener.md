

# Class SR\_AUDIO\_NS::OpenALSoundListener



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**OpenALSoundListener**](classSR__AUDIO__NS_1_1OpenALSoundListener.md)








Inherits the following classes: [SR\_AUDIO\_NS::SoundListener](classSR__AUDIO__NS_1_1SoundListener.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD ListenerDistanceModel | [**GetDistanceModel**](#function-getdistancemodel) () noexcept override const<br> |
| virtual SR\_NODISCARD float\_t | [**GetGain**](#function-getgain) () noexcept override const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector6 | [**GetOrientation**](#function-getorientation) () noexcept override const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetPosition**](#function-getposition) () noexcept override const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetVelocity**](#function-getvelocity) () noexcept override const<br> |
| virtual bool | [**Init**](#function-init) () override<br> |
|   | [**OpenALSoundListener**](#function-openalsoundlistener) ([**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* pDevice) <br> |
| virtual void | [**SetDistanceModel**](#function-setdistancemodel) (ListenerDistanceModel distanceModel) override<br> |
| virtual void | [**SetGain**](#function-setgain) (float\_t gain) override<br> |
| virtual void | [**SetVelocity**](#function-setvelocity) (SR\_MATH\_NS::FVector3 velocity) override<br> |
| virtual bool | [**Update**](#function-update) (const SR\_MATH\_NS::FVector3 & position, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) override<br> |


## Public Functions inherited from SR_AUDIO_NS::SoundListener

See [SR\_AUDIO\_NS::SoundListener](classSR__AUDIO__NS_1_1SoundListener.md)

| Type | Name |
| ---: | :--- |
|  [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* | [**Allocate**](classSR__AUDIO__NS_1_1SoundListener.md#function-allocate) ([**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* pDevice) <br> |
|  SR\_NODISCARD const [**ListenerData**](structSR__AUDIO__NS_1_1ListenerData.md) & | [**GetData**](classSR__AUDIO__NS_1_1SoundListener.md#function-getdata-12) () noexcept const<br> |
|  SR\_NODISCARD [**ListenerData**](structSR__AUDIO__NS_1_1ListenerData.md) & | [**GetData**](classSR__AUDIO__NS_1_1SoundListener.md#function-getdata-22) () noexcept<br> |
|  SR\_NODISCARD [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* | [**GetDevice**](classSR__AUDIO__NS_1_1SoundListener.md#function-getdevice) () noexcept const<br> |
| virtual SR\_NODISCARD ListenerDistanceModel | [**GetDistanceModel**](classSR__AUDIO__NS_1_1SoundListener.md#function-getdistancemodel) () noexcept const<br> |
| virtual SR\_NODISCARD float\_t | [**GetGain**](classSR__AUDIO__NS_1_1SoundListener.md#function-getgain) () noexcept const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector6 | [**GetOrientation**](classSR__AUDIO__NS_1_1SoundListener.md#function-getorientation) () noexcept const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetPosition**](classSR__AUDIO__NS_1_1SoundListener.md#function-getposition) () noexcept const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetVelocity**](classSR__AUDIO__NS_1_1SoundListener.md#function-getvelocity) () noexcept const<br> |
| virtual bool | [**Init**](classSR__AUDIO__NS_1_1SoundListener.md#function-init) () <br> |
|  void | [**SetData**](classSR__AUDIO__NS_1_1SoundListener.md#function-setdata) (const [**ListenerData**](structSR__AUDIO__NS_1_1ListenerData.md) & data) <br> |
| virtual void | [**SetDistanceModel**](classSR__AUDIO__NS_1_1SoundListener.md#function-setdistancemodel) (ListenerDistanceModel distanceModel) <br> |
| virtual void | [**SetGain**](classSR__AUDIO__NS_1_1SoundListener.md#function-setgain) (float\_t gain) <br> |
| virtual void | [**SetVelocity**](classSR__AUDIO__NS_1_1SoundListener.md#function-setvelocity) (SR\_MATH\_NS::FVector3 velocity) <br> |
|   | [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md#function-soundlistener) ([**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* pDevice) <br> |
| virtual bool | [**Update**](classSR__AUDIO__NS_1_1SoundListener.md#function-update) (const SR\_MATH\_NS::FVector3 & position, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






















## Protected Attributes inherited from SR_AUDIO_NS::SoundListener

See [SR\_AUDIO\_NS::SoundListener](classSR__AUDIO__NS_1_1SoundListener.md)

| Type | Name |
| ---: | :--- |
|  [**ListenerData**](structSR__AUDIO__NS_1_1ListenerData.md) | [**m\_data**](classSR__AUDIO__NS_1_1SoundListener.md#variable-m_data)  <br> |


















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function GetDistanceModel 

```C++
virtual SR_NODISCARD ListenerDistanceModel SR_AUDIO_NS::OpenALSoundListener::GetDistanceModel () noexcept override const
```



Implements [*SR\_AUDIO\_NS::SoundListener::GetDistanceModel*](classSR__AUDIO__NS_1_1SoundListener.md#function-getdistancemodel)


<hr>



### function GetGain 

```C++
virtual SR_NODISCARD float_t SR_AUDIO_NS::OpenALSoundListener::GetGain () noexcept override const
```



Implements [*SR\_AUDIO\_NS::SoundListener::GetGain*](classSR__AUDIO__NS_1_1SoundListener.md#function-getgain)


<hr>



### function GetOrientation 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector6 SR_AUDIO_NS::OpenALSoundListener::GetOrientation () noexcept override const
```



Implements [*SR\_AUDIO\_NS::SoundListener::GetOrientation*](classSR__AUDIO__NS_1_1SoundListener.md#function-getorientation)


<hr>



### function GetPosition 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_AUDIO_NS::OpenALSoundListener::GetPosition () noexcept override const
```



Implements [*SR\_AUDIO\_NS::SoundListener::GetPosition*](classSR__AUDIO__NS_1_1SoundListener.md#function-getposition)


<hr>



### function GetVelocity 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_AUDIO_NS::OpenALSoundListener::GetVelocity () noexcept override const
```



Implements [*SR\_AUDIO\_NS::SoundListener::GetVelocity*](classSR__AUDIO__NS_1_1SoundListener.md#function-getvelocity)


<hr>



### function Init 

```C++
virtual bool SR_AUDIO_NS::OpenALSoundListener::Init () override
```



Implements [*SR\_AUDIO\_NS::SoundListener::Init*](classSR__AUDIO__NS_1_1SoundListener.md#function-init)


<hr>



### function OpenALSoundListener 

```C++
inline explicit SR_AUDIO_NS::OpenALSoundListener::OpenALSoundListener (
    SoundDevice * pDevice
) 
```




<hr>



### function SetDistanceModel 

```C++
virtual void SR_AUDIO_NS::OpenALSoundListener::SetDistanceModel (
    ListenerDistanceModel distanceModel
) override
```



Implements [*SR\_AUDIO\_NS::SoundListener::SetDistanceModel*](classSR__AUDIO__NS_1_1SoundListener.md#function-setdistancemodel)


<hr>



### function SetGain 

```C++
virtual void SR_AUDIO_NS::OpenALSoundListener::SetGain (
    float_t gain
) override
```



Implements [*SR\_AUDIO\_NS::SoundListener::SetGain*](classSR__AUDIO__NS_1_1SoundListener.md#function-setgain)


<hr>



### function SetVelocity 

```C++
virtual void SR_AUDIO_NS::OpenALSoundListener::SetVelocity (
    SR_MATH_NS::FVector3 velocity
) override
```



Implements [*SR\_AUDIO\_NS::SoundListener::SetVelocity*](classSR__AUDIO__NS_1_1SoundListener.md#function-setvelocity)


<hr>



### function Update 

```C++
virtual bool SR_AUDIO_NS::OpenALSoundListener::Update (
    const SR_MATH_NS::FVector3 & position,
    const SR_MATH_NS::Quaternion & quaternion
) override
```



Implements [*SR\_AUDIO\_NS::SoundListener::Update*](classSR__AUDIO__NS_1_1SoundListener.md#function-update)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Audio/inc/Audio/Impl/OpenALSoundListener.h`

