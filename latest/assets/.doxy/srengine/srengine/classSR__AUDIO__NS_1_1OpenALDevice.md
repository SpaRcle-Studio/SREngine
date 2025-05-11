

# Class SR\_AUDIO\_NS::OpenALDevice



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**OpenALDevice**](classSR__AUDIO__NS_1_1OpenALDevice.md)








Inherits the following classes: [SR\_AUDIO\_NS::SoundDevice](classSR__AUDIO__NS_1_1SoundDevice.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD ALCdevice \* | [**GetALDevice**](#function-getaldevice) () const<br> |
| virtual bool | [**Init**](#function-init) () override<br> |
|   | [**OpenALDevice**](#function-openaldevice) (AudioLibrary library, const std::string & name) <br> |
|   | [**~OpenALDevice**](#function-openaldevice) () override<br> |


## Public Functions inherited from SR_AUDIO_NS::SoundDevice

See [SR\_AUDIO\_NS::SoundDevice](classSR__AUDIO__NS_1_1SoundDevice.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD AudioLibrary | [**GetLibrary**](classSR__AUDIO__NS_1_1SoundDevice.md#function-getlibrary) () const<br> |
|  SR\_NODISCARD std::string | [**GetName**](classSR__AUDIO__NS_1_1SoundDevice.md#function-getname) () const<br> |
| virtual bool | [**Init**](classSR__AUDIO__NS_1_1SoundDevice.md#function-init) () = 0<br> |
|   | [**~SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md#function-sounddevice) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |




## Public Static Functions inherited from SR_AUDIO_NS::SoundDevice

See [SR\_AUDIO\_NS::SoundDevice](classSR__AUDIO__NS_1_1SoundDevice.md)

| Type | Name |
| ---: | :--- |
|  [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* | [**Allocate**](classSR__AUDIO__NS_1_1SoundDevice.md#function-allocate) (AudioLibrary audioLibrary, const std::string & name) <br> |


















## Protected Attributes inherited from SR_AUDIO_NS::SoundDevice

See [SR\_AUDIO\_NS::SoundDevice](classSR__AUDIO__NS_1_1SoundDevice.md)

| Type | Name |
| ---: | :--- |
|  AudioLibrary | [**m\_library**](classSR__AUDIO__NS_1_1SoundDevice.md#variable-m_library)  <br> |
|  std::string | [**m\_name**](classSR__AUDIO__NS_1_1SoundDevice.md#variable-m_name)  <br> |
















































## Protected Functions inherited from SR_AUDIO_NS::SoundDevice

See [SR\_AUDIO\_NS::SoundDevice](classSR__AUDIO__NS_1_1SoundDevice.md)

| Type | Name |
| ---: | :--- |
|   | [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md#function-sounddevice) (AudioLibrary library, const std::string & name) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function GetALDevice 

```C++
SR_NODISCARD ALCdevice * SR_AUDIO_NS::OpenALDevice::GetALDevice () const
```




<hr>



### function Init 

```C++
virtual bool SR_AUDIO_NS::OpenALDevice::Init () override
```



Implements [*SR\_AUDIO\_NS::SoundDevice::Init*](classSR__AUDIO__NS_1_1SoundDevice.md#function-init)


<hr>



### function OpenALDevice 

```C++
explicit SR_AUDIO_NS::OpenALDevice::OpenALDevice (
    AudioLibrary library,
    const std::string & name
) 
```




<hr>



### function ~OpenALDevice 

```C++
SR_AUDIO_NS::OpenALDevice::~OpenALDevice () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Audio/inc/Audio/Impl/OpenALDevice.h`

