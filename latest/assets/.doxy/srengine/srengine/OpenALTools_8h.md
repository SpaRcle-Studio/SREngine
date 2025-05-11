

# File OpenALTools.h



[**FileList**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**Impl**](dir_1bd135d85244281d14f19c1ce566dd82.md) **>** [**OpenALTools.h**](OpenALTools_8h.md)

[Go to the source code of this file](OpenALTools_8h_source.md)



* `#include <Utils/macros.h>`
* `#include <AL/al.h>`
* `#include <AL/alc.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**ALfVec3**](structSR__AUDIO__NS_1_1ALfVec3.md) <br> |
| struct | [**ALfVec6**](structSR__AUDIO__NS_1_1ALfVec6.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_ALC\_CALL**](OpenALTools_8h.md#define-sr_alc_call) (function, device, ...) `SR\_AUDIO\_NS::alcCallImpl(\_\_FILE\_\_, \_\_LINE\_\_, function, device, \_\_VA\_ARGS\_\_)`<br> |
| define  | [**SR\_AL\_CALL**](OpenALTools_8h.md#define-sr_al_call) (function, ...) `SR\_AUDIO\_NS::alCallImpl(\_\_FILE\_\_, \_\_LINE\_\_, function, \_\_VA\_ARGS\_\_)`<br> |

## Macro Definition Documentation





### define SR\_ALC\_CALL 

```C++
#define SR_ALC_CALL (
    function,
    device,
    ...
) `SR_AUDIO_NS::alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)`
```




<hr>



### define SR\_AL\_CALL 

```C++
#define SR_AL_CALL (
    function,
    ...
) `SR_AUDIO_NS::alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Audio/inc/Audio/Impl/OpenALTools.h`

