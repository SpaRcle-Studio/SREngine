

# Class SR\_AUDIO\_NS::SoundListener



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_AUDIO\_NS::OpenALSoundListener](classSR__AUDIO__NS_1_1OpenALSoundListener.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) \* | [**Allocate**](#function-allocate) ([**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* pDevice) <br> |
|  SR\_NODISCARD const [**ListenerData**](structSR__AUDIO__NS_1_1ListenerData.md) & | [**GetData**](#function-getdata-12) () noexcept const<br> |
|  SR\_NODISCARD [**ListenerData**](structSR__AUDIO__NS_1_1ListenerData.md) & | [**GetData**](#function-getdata-22) () noexcept<br> |
|  SR\_NODISCARD [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* | [**GetDevice**](#function-getdevice) () noexcept const<br> |
| virtual SR\_NODISCARD ListenerDistanceModel | [**GetDistanceModel**](#function-getdistancemodel) () noexcept const<br> |
| virtual SR\_NODISCARD float\_t | [**GetGain**](#function-getgain) () noexcept const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector6 | [**GetOrientation**](#function-getorientation) () noexcept const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetPosition**](#function-getposition) () noexcept const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetVelocity**](#function-getvelocity) () noexcept const<br> |
| virtual bool | [**Init**](#function-init) () <br> |
|  void | [**SetData**](#function-setdata) (const [**ListenerData**](structSR__AUDIO__NS_1_1ListenerData.md) & data) <br> |
| virtual void | [**SetDistanceModel**](#function-setdistancemodel) (ListenerDistanceModel distanceModel) <br> |
| virtual void | [**SetGain**](#function-setgain) (float\_t gain) <br> |
| virtual void | [**SetVelocity**](#function-setvelocity) (SR\_MATH\_NS::FVector3 velocity) <br> |
|   | [**SoundListener**](#function-soundlistener) ([**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* pDevice) <br> |
| virtual bool | [**Update**](#function-update) (const SR\_MATH\_NS::FVector3 & position, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**ListenerData**](structSR__AUDIO__NS_1_1ListenerData.md) | [**m\_data**](#variable-m_data)  <br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function Allocate 

```C++
SoundListener * SR_AUDIO_NS::SoundListener::Allocate (
    SoundDevice * pDevice
) 
```




<hr>



### function GetData [1/2]

```C++
inline SR_NODISCARD const ListenerData & SR_AUDIO_NS::SoundListener::GetData () noexcept const
```




<hr>



### function GetData [2/2]

```C++
inline SR_NODISCARD ListenerData & SR_AUDIO_NS::SoundListener::GetData () noexcept
```




<hr>



### function GetDevice 

```C++
inline SR_NODISCARD SoundDevice * SR_AUDIO_NS::SoundListener::GetDevice () noexcept const
```




<hr>



### function GetDistanceModel 

```C++
inline virtual SR_NODISCARD ListenerDistanceModel SR_AUDIO_NS::SoundListener::GetDistanceModel () noexcept const
```




<hr>



### function GetGain 

```C++
inline virtual SR_NODISCARD float_t SR_AUDIO_NS::SoundListener::GetGain () noexcept const
```




<hr>



### function GetOrientation 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::FVector6 SR_AUDIO_NS::SoundListener::GetOrientation () noexcept const
```




<hr>



### function GetPosition 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_AUDIO_NS::SoundListener::GetPosition () noexcept const
```




<hr>



### function GetVelocity 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_AUDIO_NS::SoundListener::GetVelocity () noexcept const
```




<hr>



### function Init 

```C++
inline virtual bool SR_AUDIO_NS::SoundListener::Init () 
```




<hr>



### function SetData 

```C++
inline void SR_AUDIO_NS::SoundListener::SetData (
    const ListenerData & data
) 
```




<hr>



### function SetDistanceModel 

```C++
inline virtual void SR_AUDIO_NS::SoundListener::SetDistanceModel (
    ListenerDistanceModel distanceModel
) 
```




<hr>



### function SetGain 

```C++
inline virtual void SR_AUDIO_NS::SoundListener::SetGain (
    float_t gain
) 
```




<hr>



### function SetVelocity 

```C++
inline virtual void SR_AUDIO_NS::SoundListener::SetVelocity (
    SR_MATH_NS::FVector3 velocity
) 
```




<hr>



### function SoundListener 

```C++
inline explicit SR_AUDIO_NS::SoundListener::SoundListener (
    SoundDevice * pDevice
) 
```




<hr>



### function Update 

```C++
inline virtual bool SR_AUDIO_NS::SoundListener::Update (
    const SR_MATH_NS::FVector3 & position,
    const SR_MATH_NS::Quaternion & quaternion
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_data 

```C++
ListenerData SR_AUDIO_NS::SoundListener::m_data;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Audio/inc/Audio/SoundListener.h`

