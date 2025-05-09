

# Struct SR\_AUDIO\_NS::PlayData



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**PlayData**](structSR__AUDIO__NS_1_1PlayData.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**isFailed**](#variable-isfailed)   = `false`<br> |
|  bool | [**isPlaying**](#variable-isplaying)   = `false`<br> |
|  float\_t | [**offset**](#variable-offset)   = `0.f`<br> |
|  [**SoundData**](structSR__AUDIO__NS_1_1SoundData.md) \* | [**pData**](#variable-pdata)   = `nullptr`<br> |
|  [**Sound**](classSR__AUDIO__NS_1_1Sound.md) \* | [**pSound**](#variable-psound)   = `nullptr`<br> |
|  SoundSource | [**pSource**](#variable-psource)   = `nullptr`<br> |
|  [**PlayParams**](structSR__AUDIO__NS_1_1PlayParams.md) | [**params**](#variable-params)  <br> |


































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






## Public Attributes Documentation




### variable isFailed 

```C++
bool SR_AUDIO_NS::PlayData::isFailed;
```




<hr>



### variable isPlaying 

```C++
bool SR_AUDIO_NS::PlayData::isPlaying;
```




<hr>



### variable offset 

```C++
float_t SR_AUDIO_NS::PlayData::offset;
```




<hr>



### variable pData 

```C++
SoundData* SR_AUDIO_NS::PlayData::pData;
```




<hr>



### variable pSound 

```C++
Sound* SR_AUDIO_NS::PlayData::pSound;
```




<hr>



### variable pSource 

```C++
SoundSource SR_AUDIO_NS::PlayData::pSource;
```




<hr>



### variable params 

```C++
PlayParams SR_AUDIO_NS::PlayData::params;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Audio/inc/Audio/SoundManager.h`

