

# Class SR\_AUDIO\_NS::SoundDevice



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_AUDIO\_NS::OpenALDevice](classSR__AUDIO__NS_1_1OpenALDevice.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD AudioLibrary | [**GetLibrary**](#function-getlibrary) () const<br> |
|  SR\_NODISCARD std::string | [**GetName**](#function-getname) () const<br> |
| virtual bool | [**Init**](#function-init) () = 0<br> |
|   | [**~SoundDevice**](#function-sounddevice) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**SoundDevice**](classSR__AUDIO__NS_1_1SoundDevice.md) \* | [**Allocate**](#function-allocate) (AudioLibrary audioLibrary, const std::string & name) <br> |












## Protected Attributes

| Type | Name |
| ---: | :--- |
|  AudioLibrary | [**m\_library**](#variable-m_library)  <br> |
|  std::string | [**m\_name**](#variable-m_name)  <br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**SoundDevice**](#function-sounddevice) (AudioLibrary library, const std::string & name) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function GetLibrary 

```C++
SR_NODISCARD AudioLibrary SR_AUDIO_NS::SoundDevice::GetLibrary () const
```




<hr>



### function GetName 

```C++
SR_NODISCARD std::string SR_AUDIO_NS::SoundDevice::GetName () const
```




<hr>



### function Init 

```C++
virtual bool SR_AUDIO_NS::SoundDevice::Init () = 0
```




<hr>



### function ~SoundDevice 

```C++
SR_AUDIO_NS::SoundDevice::~SoundDevice () override
```




<hr>
## Public Static Functions Documentation




### function Allocate 

```C++
static SoundDevice * SR_AUDIO_NS::SoundDevice::Allocate (
    AudioLibrary audioLibrary,
    const std::string & name
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_library 

```C++
AudioLibrary SR_AUDIO_NS::SoundDevice::m_library;
```




<hr>



### variable m\_name 

```C++
std::string SR_AUDIO_NS::SoundDevice::m_name;
```




<hr>
## Protected Functions Documentation




### function SoundDevice 

```C++
explicit SR_AUDIO_NS::SoundDevice::SoundDevice (
    AudioLibrary library,
    const std::string & name
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Audio/inc/Audio/SoundDevice.h`

