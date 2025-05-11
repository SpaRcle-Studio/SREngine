

# File FreeType.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Font**](dir_0f9fa5c8aefacabb9ad499652a4f09bc.md) **>** [**FreeType.h**](FreeType_8h.md)

[Go to the source code of this file](FreeType_8h_source.md)



* `#include <Graphics/macros.h>`
* `#include <Utils/macros.h>`
* `#include <ft2build.h>`
* `#include <freetype/ftglyph.h>`
* `#include <freetype/tttables.h>`
* `#include <freetype/src/truetype/ttobjs.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) <br> |



















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**FT\_ERRORDEF**](FreeType_8h.md#define-ft_errordef) (e, v, s) `case e: return s;`<br> |
| define  | [**FT\_ERROR\_END\_LIST**](FreeType_8h.md#define-ft_error_end_list)  `}`<br> |
| define  | [**FT\_ERROR\_START\_LIST**](FreeType_8h.md#define-ft_error_start_list)  `switch (err) {`<br> |
| define  | [**SRFreeTypeErrToString**](FreeType_8h.md#define-srfreetypeerrtostring) (err) `(FreeTypeErrToString(err))`<br> |

## Macro Definition Documentation





### define FT\_ERRORDEF 

```C++
#define FT_ERRORDEF (
    e,
    v,
    s
) `case e: return s;`
```




<hr>



### define FT\_ERROR\_END\_LIST 

```C++
#define FT_ERROR_END_LIST `}`
```




<hr>



### define FT\_ERROR\_START\_LIST 

```C++
#define FT_ERROR_START_LIST `switch (err) {`
```




<hr>



### define SRFreeTypeErrToString 

```C++
#define SRFreeTypeErrToString (
    err
) `(FreeTypeErrToString(err))`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Font/FreeType.h`

