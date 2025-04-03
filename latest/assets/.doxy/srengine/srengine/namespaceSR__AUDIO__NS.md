

# Namespace SR\_AUDIO\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**ALfVec3**](structSR__AUDIO__NS_1_1ALfVec3.md) <br> |
| struct | [**ALfVec6**](structSR__AUDIO__NS_1_1ALfVec6.md) <br> |
| class | [**AudioListener**](classSR__AUDIO__NS_1_1AudioListener.md) <br> |
| class | [**AudioSource**](classSR__AUDIO__NS_1_1AudioSource.md) <br> |
| class | [**IWaveDataProvider**](classSR__AUDIO__NS_1_1IWaveDataProvider.md) <br> |
| struct | [**ListenerData**](structSR__AUDIO__NS_1_1ListenerData.md) <br> |
| class | [**MP3DataProvider**](classSR__AUDIO__NS_1_1MP3DataProvider.md) <br>_MPEG Layer-III decoder._  |
| class | [**ModPlugDataProvider**](classSR__AUDIO__NS_1_1ModPlugDataProvider.md) <br>_ModPlug decoder._  |
| class | [**OpenALDevice**](classSR__AUDIO__NS_1_1OpenALDevice.md) <br> |
| class | [**OpenALSoundContext**](classSR__AUDIO__NS_1_1OpenALSoundContext.md) <br> |
| class | [**OpenALSoundListener**](classSR__AUDIO__NS_1_1OpenALSoundListener.md) <br> |
| struct | [**PlayData**](structSR__AUDIO__NS_1_1PlayData.md) <br> |
| class | [**PlayParamChangeChecker**](classSR__AUDIO__NS_1_1PlayParamChangeChecker.md) &lt;typename T&gt;<br> |
| struct | [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) <br> |
| class | [**RawSound**](classSR__AUDIO__NS_1_1RawSound.md) <br> |
| class | [**Sound**](classSR__AUDIO__NS_1_1Sound.md) <br> |
| class | [**SoundContext**](classSR__AUDIO__NS_1_1SoundContext.md) <br> |
| struct | [**SoundData**](structSR__AUDIO__NS_1_1SoundData.md) <br> |
| class | [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) <br> |
| class | [**SoundListener**](classSR__AUDIO__NS_1_1SoundListener.md) <br> |
| class | [**SoundManager**](classSR__AUDIO__NS_1_1SoundManager.md) <br> |
| class | [**WAVDataProvider**](classSR__AUDIO__NS_1_1WAVDataProvider.md) <br>_a Microsoft WAVE decoder_  |
| class | [**WaveDataFormat**](classSR__AUDIO__NS_1_1WaveDataFormat.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef struct [**SR\_AUDIO\_NS::ALfVec3**](structSR__AUDIO__NS_1_1ALfVec3.md) | [**ALfVec3**](#typedef-alfvec3)  <br> |
| typedef struct [**SR\_AUDIO\_NS::ALfVec6**](structSR__AUDIO__NS_1_1ALfVec6.md) | [**ALfVec6**](#typedef-alfvec6)  <br> |
| typedef std::string | [**AudioDeviceName**](#typedef-audiodevicename)  <br> |
| typedef std::vector&lt; uint8\_t &gt; | [**RawSoundData**](#typedef-rawsounddata)  <br> |
| typedef std::shared\_ptr&lt; RawSoundData &gt; | [**RawSoundDataPtr**](#typedef-rawsounddataptr)  <br> |
| typedef void \* | [**SoundBuffer**](#typedef-soundbuffer)  <br> |
| enum uint8\_t | [**SoundFormat**](#enum-soundformat)  <br> |
| typedef void \* | [**SoundSource**](#typedef-soundsource)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_INLINE\_STATIC [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**SR\_SUPPORTED\_AUDIO\_FORMATS**](#variable-sr_supported_audio_formats)   = `"wav,mp3,ogg"`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  ListenerDistanceModel | [**ALDistanceModelToDistanceModel**](#function-aldistancemodeltodistancemodel) (ALenum distanceModel) <br> |
|  void | [**CheckThreadId**](#function-checkthreadid) (const char \* filename, const std::uint\_fast32\_t line) <br> |
|  IWaveDataProvider::Ptr | [**CreateWaveDataProvider**](#function-createwavedataprovider) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, const RawSoundDataPtr & data) <br> |
|  ALenum | [**DistanceModelToALDistanceModel**](#function-distancemodeltoaldistancemodel) (ListenerDistanceModel distanceModel) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (AudioLibrary, uint8\_t, Unknown, OpenAL, FMOD, Wwise, Allegro, SoLoud) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (ListenerDistanceModel, uint8\_t, None, Inverse, InverseClamped, Linear, LinearClamped, Exponent, ExponentClamped) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (PlayParamType, uint8\_t, Async, Loop, Library, Relative, Gain, MinGain, Pitch, ConeInnerAngle, ConeOuterAngle, UniqueId, Position, Direction, Velocity, ConeOuterGain, Orientation, Device, MaxGain, MaxDistance, RolloffFactor, ReferenceDistance, Spatialize) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (SpatializeMode, uint8\_t, Off, On, Auto) <br> |
|  RawSoundDataPtr | [**TryMP3InsideWAV**](#function-trymp3insidewav) (const RawSoundDataPtr & data) <br> |
|  auto | [**alCallImpl**](#function-alcallimpl) (const char \* filename, const std::uint\_fast32\_t line, alFunction function, Params... params) <br> |
|  auto | [**alcCallImpl**](#function-alccallimpl) (const char \* filename, const std::uint\_fast32\_t line, alcFunction function, ALCdevice \* device, Params... params) <br> |
|  auto | [**alcCallImpl**](#function-alccallimpl) (const char \* filename, const std::uint\_fast32\_t line, alcFunction function, ReturnType & returnValue, ALCdevice \* device, Params... params) <br> |
|  bool | [**check\_al\_errors**](#function-check_al_errors) (const std::string & filename, const std::uint\_fast32\_t line) <br> |
|  bool | [**check\_alc\_errors**](#function-check_alc_errors) (const std::string & filename, const std::uint\_fast32\_t line, ALCdevice \* device) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SoundFormat | [**CalculateSoundFormat**](#function-calculatesoundformat) (uint8\_t channels, uint8\_t bitsPerSample) <br> |
|  SR\_MAYBE\_UNUSED [**ALfVec3**](structSR__AUDIO__NS_1_1ALfVec3.md) | [**FV3ToALV3**](#function-fv3toalv3) (const SR\_MATH\_NS::FVector3 & vector3) <br> |
|  SR\_MAYBE\_UNUSED [**ALfVec6**](structSR__AUDIO__NS_1_1ALfVec6.md) | [**FV6ToALV6**](#function-fv6toalv6) (const SR\_MATH\_NS::FVector6 & vector6) <br> |


























## Public Types Documentation




### typedef ALfVec3 

```C++
typedef struct SR_AUDIO_NS::ALfVec3 SR_AUDIO_NS::ALfVec3;
```




<hr>



### typedef ALfVec6 

```C++
typedef struct SR_AUDIO_NS::ALfVec6 SR_AUDIO_NS::ALfVec6;
```




<hr>



### typedef AudioDeviceName 

```C++
using SR_AUDIO_NS::AudioDeviceName = typedef std::string;
```




<hr>



### typedef RawSoundData 

```C++
typedef std::vector<uint8_t> SR_AUDIO_NS::RawSoundData;
```




<hr>



### typedef RawSoundDataPtr 

```C++
typedef std::shared_ptr<RawSoundData> SR_AUDIO_NS::RawSoundDataPtr;
```




<hr>



### typedef SoundBuffer 

```C++
using SR_AUDIO_NS::SoundBuffer = typedef void*;
```




<hr>



### enum SoundFormat 

```C++
enum SR_AUDIO_NS::SoundFormat {
    SR_SOUND_FORMAT_UNKNOWN,
    SR_SOUND_FORMAT_MONO_8,
    SR_SOUND_FORMAT_MONO_16,
    SR_SOUND_FORMAT_STEREO_8,
    SR_SOUND_FORMAT_STEREO_16
};
```




<hr>



### typedef SoundSource 

```C++
using SR_AUDIO_NS::SoundSource = typedef void*;
```




<hr>
## Public Attributes Documentation




### variable SR\_SUPPORTED\_AUDIO\_FORMATS 

```C++
SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_AUDIO_NS::SR_SUPPORTED_AUDIO_FORMATS;
```




<hr>
## Public Functions Documentation




### function ALDistanceModelToDistanceModel 

```C++
ListenerDistanceModel SR_AUDIO_NS::ALDistanceModelToDistanceModel (
    ALenum distanceModel
) 
```




<hr>



### function CheckThreadId 

```C++
void SR_AUDIO_NS::CheckThreadId (
    const char * filename,
    const std::uint_fast32_t line
) 
```




<hr>



### function CreateWaveDataProvider 

```C++
IWaveDataProvider::Ptr SR_AUDIO_NS::CreateWaveDataProvider (
    const SR_UTILS_NS::Path & path,
    const RawSoundDataPtr & data
) 
```




<hr>



### function DistanceModelToALDistanceModel 

```C++
ALenum SR_AUDIO_NS::DistanceModelToALDistanceModel (
    ListenerDistanceModel distanceModel
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_AUDIO_NS::SR_ENUM_NS_CLASS_T (
    AudioLibrary,
    uint8_t,
    Unknown,
    OpenAL,
    FMOD,
    Wwise,
    Allegro,
    SoLoud
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_AUDIO_NS::SR_ENUM_NS_CLASS_T (
    ListenerDistanceModel,
    uint8_t,
    None,
    Inverse,
    InverseClamped,
    Linear,
    LinearClamped,
    Exponent,
    ExponentClamped
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_AUDIO_NS::SR_ENUM_NS_CLASS_T (
    PlayParamType,
    uint8_t,
    Async,
    Loop,
    Library,
    Relative,
    Gain,
    MinGain,
    Pitch,
    ConeInnerAngle,
    ConeOuterAngle,
    UniqueId,
    Position,
    Direction,
    Velocity,
    ConeOuterGain,
    Orientation,
    Device,
    MaxGain,
    MaxDistance,
    RolloffFactor,
    ReferenceDistance,
    Spatialize
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_AUDIO_NS::SR_ENUM_NS_CLASS_T (
    SpatializeMode,
    uint8_t,
    Off,
    On,
    Auto
) 
```




<hr>



### function TryMP3InsideWAV 

```C++
RawSoundDataPtr SR_AUDIO_NS::TryMP3InsideWAV (
    const RawSoundDataPtr & data
) 
```




<hr>



### function alCallImpl 

```C++
template<typename alFunction, typename... Params>
auto SR_AUDIO_NS::alCallImpl (
    const char * filename,
    const std::uint_fast32_t line,
    alFunction function,
    Params... params
) 
```




<hr>



### function alcCallImpl 

```C++
template<typename alcFunction, typename... Params>
auto SR_AUDIO_NS::alcCallImpl (
    const char * filename,
    const std::uint_fast32_t line,
    alcFunction function,
    ALCdevice * device,
    Params... params
) 
```




<hr>



### function alcCallImpl 

```C++
template<typename alcFunction, typename ReturnType, typename... Params>
auto SR_AUDIO_NS::alcCallImpl (
    const char * filename,
    const std::uint_fast32_t line,
    alcFunction function,
    ReturnType & returnValue,
    ALCdevice * device,
    Params... params
) 
```




<hr>



### function check\_al\_errors 

```C++
bool SR_AUDIO_NS::check_al_errors (
    const std::string & filename,
    const std::uint_fast32_t line
) 
```




<hr>



### function check\_alc\_errors 

```C++
bool SR_AUDIO_NS::check_alc_errors (
    const std::string & filename,
    const std::uint_fast32_t line,
    ALCdevice * device
) 
```




<hr>
## Public Static Functions Documentation




### function CalculateSoundFormat 

```C++
static SoundFormat SR_AUDIO_NS::CalculateSoundFormat (
    uint8_t channels,
    uint8_t bitsPerSample
) 
```




<hr>



### function FV3ToALV3 

```C++
static SR_MAYBE_UNUSED ALfVec3 SR_AUDIO_NS::FV3ToALV3 (
    const SR_MATH_NS::FVector3 & vector3
) 
```




<hr>



### function FV6ToALV6 

```C++
static SR_MAYBE_UNUSED ALfVec6 SR_AUDIO_NS::FV6ToALV6 (
    const SR_MATH_NS::FVector6 & vector6
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Audio/inc/Audio/AudioLibrary.h`

