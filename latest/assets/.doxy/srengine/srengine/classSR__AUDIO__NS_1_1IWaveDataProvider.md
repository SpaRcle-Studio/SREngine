

# Class SR\_AUDIO\_NS::IWaveDataProvider



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**IWaveDataProvider**](classSR__AUDIO__NS_1_1IWaveDataProvider.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_AUDIO\_NS::MP3DataProvider](classSR__AUDIO__NS_1_1MP3DataProvider.md),  [SR\_AUDIO\_NS::ModPlugDataProvider](classSR__AUDIO__NS_1_1ModPlugDataProvider.md),  [SR\_AUDIO\_NS::WAVDataProvider](classSR__AUDIO__NS_1_1WAVDataProvider.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::shared\_ptr&lt; [**IWaveDataProvider**](classSR__AUDIO__NS_1_1IWaveDataProvider.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD const uint8\_t \* | [**GetWaveData**](#function-getwavedata) () const = 0<br> |
| virtual SR\_NODISCARD const [**WaveDataFormat**](classSR__AUDIO__NS_1_1WaveDataFormat.md) & | [**GetWaveDataFormat**](#function-getwavedataformat) () const = 0<br> |
| virtual SR\_NODISCARD size\_t | [**GetWaveDataSize**](#function-getwavedatasize) () const = 0<br> |
| virtual SR\_NODISCARD bool | [**IsEndOfStream**](#function-isendofstream) () const<br> |
| virtual SR\_NODISCARD bool | [**IsStreaming**](#function-isstreaming) () const<br> |
|  SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () const<br> |
| virtual void | [**Seek**](#function-seek) (float\_t seconds) <br> |
| virtual size\_t | [**StreamWaveData**](#function-streamwavedata) (size\_t size) <br> |
|   | [**~IWaveDataProvider**](#function-iwavedataprovider) () override<br> |


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






## Public Types Documentation




### typedef Ptr 

```C++
using SR_AUDIO_NS::IWaveDataProvider::Ptr =  std::shared_ptr<IWaveDataProvider>;
```




<hr>
## Public Functions Documentation




### function GetWaveData 

```C++
virtual SR_NODISCARD const uint8_t * SR_AUDIO_NS::IWaveDataProvider::GetWaveData () const = 0
```




<hr>



### function GetWaveDataFormat 

```C++
virtual SR_NODISCARD const WaveDataFormat & SR_AUDIO_NS::IWaveDataProvider::GetWaveDataFormat () const = 0
```




<hr>



### function GetWaveDataSize 

```C++
virtual SR_NODISCARD size_t SR_AUDIO_NS::IWaveDataProvider::GetWaveDataSize () const = 0
```




<hr>



### function IsEndOfStream 

```C++
inline virtual SR_NODISCARD bool SR_AUDIO_NS::IWaveDataProvider::IsEndOfStream () const
```




<hr>



### function IsStreaming 

```C++
inline virtual SR_NODISCARD bool SR_AUDIO_NS::IWaveDataProvider::IsStreaming () const
```




<hr>



### function IsValid 

```C++
inline SR_NODISCARD bool SR_AUDIO_NS::IWaveDataProvider::IsValid () const
```




<hr>



### function Seek 

```C++
inline virtual void SR_AUDIO_NS::IWaveDataProvider::Seek (
    float_t seconds
) 
```




<hr>



### function StreamWaveData 

```C++
inline virtual size_t SR_AUDIO_NS::IWaveDataProvider::StreamWaveData (
    size_t size
) 
```




<hr>



### function ~IWaveDataProvider 

```C++
SR_AUDIO_NS::IWaveDataProvider::~IWaveDataProvider () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Audio/inc/Audio/Decoders/IWaveDataProvider.h`

