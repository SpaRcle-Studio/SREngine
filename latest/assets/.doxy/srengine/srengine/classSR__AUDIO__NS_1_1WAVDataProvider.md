

# Class SR\_AUDIO\_NS::WAVDataProvider



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**WAVDataProvider**](classSR__AUDIO__NS_1_1WAVDataProvider.md)



_a Microsoft WAVE decoder_ 

* `#include <WAVDataProvider.h>`



Inherits the following classes: [SR\_AUDIO\_NS::IWaveDataProvider](classSR__AUDIO__NS_1_1IWaveDataProvider.md)
















## Public Types inherited from SR_AUDIO_NS::IWaveDataProvider

See [SR\_AUDIO\_NS::IWaveDataProvider](classSR__AUDIO__NS_1_1IWaveDataProvider.md)

| Type | Name |
| ---: | :--- |
| typedef std::shared\_ptr&lt; [**IWaveDataProvider**](classSR__AUDIO__NS_1_1IWaveDataProvider.md) &gt; | [**Ptr**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#typedef-ptr)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD const uint8\_t \* | [**GetWaveData**](#function-getwavedata) () override const<br> |
| virtual SR\_NODISCARD const [**WaveDataFormat**](classSR__AUDIO__NS_1_1WaveDataFormat.md) & | [**GetWaveDataFormat**](#function-getwavedataformat) () override const<br> |
| virtual SR\_NODISCARD size\_t | [**GetWaveDataSize**](#function-getwavedatasize) () override const<br> |
|  void | [**Seek**](#function-seek) (float Seconds) override<br> |
| virtual SR\_NODISCARD size\_t | [**StreamWaveData**](#function-streamwavedata) (size\_t Size) override<br> |
|   | [**WAVDataProvider**](#function-wavdataprovider) (const RawSoundDataPtr & data) <br> |


## Public Functions inherited from SR_AUDIO_NS::IWaveDataProvider

See [SR\_AUDIO\_NS::IWaveDataProvider](classSR__AUDIO__NS_1_1IWaveDataProvider.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD const uint8\_t \* | [**GetWaveData**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-getwavedata) () const = 0<br> |
| virtual SR\_NODISCARD const [**WaveDataFormat**](classSR__AUDIO__NS_1_1WaveDataFormat.md) & | [**GetWaveDataFormat**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-getwavedataformat) () const = 0<br> |
| virtual SR\_NODISCARD size\_t | [**GetWaveDataSize**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-getwavedatasize) () const = 0<br> |
| virtual SR\_NODISCARD bool | [**IsEndOfStream**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-isendofstream) () const<br> |
| virtual SR\_NODISCARD bool | [**IsStreaming**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-isstreaming) () const<br> |
|  SR\_NODISCARD bool | [**IsValid**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-isvalid) () const<br> |
| virtual void | [**Seek**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-seek) (float\_t seconds) <br> |
| virtual size\_t | [**StreamWaveData**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-streamwavedata) (size\_t size) <br> |
|   | [**~IWaveDataProvider**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-iwavedataprovider) () override<br> |


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




### function GetWaveData 

```C++
virtual SR_NODISCARD const uint8_t * SR_AUDIO_NS::WAVDataProvider::GetWaveData () override const
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::GetWaveData*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-getwavedata)


<hr>



### function GetWaveDataFormat 

```C++
inline virtual SR_NODISCARD const WaveDataFormat & SR_AUDIO_NS::WAVDataProvider::GetWaveDataFormat () override const
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::GetWaveDataFormat*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-getwavedataformat)


<hr>



### function GetWaveDataSize 

```C++
virtual SR_NODISCARD size_t SR_AUDIO_NS::WAVDataProvider::GetWaveDataSize () override const
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::GetWaveDataSize*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-getwavedatasize)


<hr>



### function Seek 

```C++
void SR_AUDIO_NS::WAVDataProvider::Seek (
    float Seconds
) override
```




<hr>



### function StreamWaveData 

```C++
virtual SR_NODISCARD size_t SR_AUDIO_NS::WAVDataProvider::StreamWaveData (
    size_t Size
) override
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::StreamWaveData*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-streamwavedata)


<hr>



### function WAVDataProvider 

```C++
explicit SR_AUDIO_NS::WAVDataProvider::WAVDataProvider (
    const RawSoundDataPtr & data
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Audio/inc/Audio/Decoders/WAVDataProvider.h`

