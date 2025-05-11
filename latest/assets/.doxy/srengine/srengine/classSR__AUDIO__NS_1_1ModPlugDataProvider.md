

# Class SR\_AUDIO\_NS::ModPlugDataProvider



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**ModPlugDataProvider**](classSR__AUDIO__NS_1_1ModPlugDataProvider.md)



_ModPlug decoder._ 

* `#include <ModPlugDataProvider.h>`



Inherits the following classes: [SR\_AUDIO\_NS::IWaveDataProvider](classSR__AUDIO__NS_1_1IWaveDataProvider.md)
















## Public Types inherited from SR_AUDIO_NS::IWaveDataProvider

See [SR\_AUDIO\_NS::IWaveDataProvider](classSR__AUDIO__NS_1_1IWaveDataProvider.md)

| Type | Name |
| ---: | :--- |
| typedef std::shared\_ptr&lt; [**IWaveDataProvider**](classSR__AUDIO__NS_1_1IWaveDataProvider.md) &gt; | [**Ptr**](classSR__AUDIO__NS_1_1IWaveDataProvider.md#typedef-ptr)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual const uint8\_t \* | [**GetWaveData**](#function-getwavedata) () override const<br> |
| virtual SR\_NODISCARD const [**WaveDataFormat**](classSR__AUDIO__NS_1_1WaveDataFormat.md) & | [**GetWaveDataFormat**](#function-getwavedataformat) () override const<br> |
| virtual size\_t | [**GetWaveDataSize**](#function-getwavedatasize) () override const<br> |
| virtual bool | [**IsEndOfStream**](#function-isendofstream) () override const<br> |
| virtual bool | [**IsStreaming**](#function-isstreaming) () override const<br> |
|   | [**ModPlugDataProvider**](#function-modplugdataprovider) (const RawSoundDataPtr & data) <br> |
| virtual void | [**Seek**](#function-seek) (float\_t seconds) override<br> |
| virtual size\_t | [**StreamWaveData**](#function-streamwavedata) (size\_t size) override<br> |
|   | [**~ModPlugDataProvider**](#function-modplugdataprovider) () override<br> |


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
virtual const uint8_t * SR_AUDIO_NS::ModPlugDataProvider::GetWaveData () override const
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::GetWaveData*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-getwavedata)


<hr>



### function GetWaveDataFormat 

```C++
inline virtual SR_NODISCARD const WaveDataFormat & SR_AUDIO_NS::ModPlugDataProvider::GetWaveDataFormat () override const
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::GetWaveDataFormat*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-getwavedataformat)


<hr>



### function GetWaveDataSize 

```C++
virtual size_t SR_AUDIO_NS::ModPlugDataProvider::GetWaveDataSize () override const
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::GetWaveDataSize*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-getwavedatasize)


<hr>



### function IsEndOfStream 

```C++
inline virtual bool SR_AUDIO_NS::ModPlugDataProvider::IsEndOfStream () override const
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::IsEndOfStream*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-isendofstream)


<hr>



### function IsStreaming 

```C++
inline virtual bool SR_AUDIO_NS::ModPlugDataProvider::IsStreaming () override const
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::IsStreaming*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-isstreaming)


<hr>



### function ModPlugDataProvider 

```C++
explicit SR_AUDIO_NS::ModPlugDataProvider::ModPlugDataProvider (
    const RawSoundDataPtr & data
) 
```




<hr>



### function Seek 

```C++
virtual void SR_AUDIO_NS::ModPlugDataProvider::Seek (
    float_t seconds
) override
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::Seek*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-seek)


<hr>



### function StreamWaveData 

```C++
virtual size_t SR_AUDIO_NS::ModPlugDataProvider::StreamWaveData (
    size_t size
) override
```



Implements [*SR\_AUDIO\_NS::IWaveDataProvider::StreamWaveData*](classSR__AUDIO__NS_1_1IWaveDataProvider.md#function-streamwavedata)


<hr>



### function ~ModPlugDataProvider 

```C++
SR_AUDIO_NS::ModPlugDataProvider::~ModPlugDataProvider () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Audio/inc/Audio/Decoders/ModPlugDataProvider.h`

