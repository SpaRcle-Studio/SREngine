

# File FreeType.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Font**](dir_193e1c173bb6bd0681658b8507d31117.md) **>** [**FreeType.h**](FreeType_8h.md)

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
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Font/FreeType.h`

