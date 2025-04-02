

# File StringFormat.h



[**FileList**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**StringFormat.h**](StringFormat_8h.md)

[Go to the source code of this file](StringFormat_8h_source.md)



* `#include <Utils/Math/Mathematics.h>`
* `#include <Utils/Types/StringAtom.h>`
* `#include <Utils/Common/Breakpoint.h>`
* `#include <Utils/Math/Vector4.h>`
* `#include <Utils/Platform/Platform.h>`
* `#include <Utils/Common/StringUtils.h>`
* `#include <fmt/format.h>`
* `#include <fmt/printf.h>`
* `#include <fmt/color.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |



















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_FORMAT**](StringFormat_8h.md#define-sr_format) (...) `SR\_UTILS\_NS::Format(\_\_VA\_ARGS\_\_)`<br> |
| define  | [**SR\_FORMAT\_C**](StringFormat_8h.md#define-sr_format_c) (...) `SR\_UTILS\_NS::Format(\_\_VA\_ARGS\_\_).c\_str()`<br> |
| define  | [**SR\_SPRINTF**](StringFormat_8h.md#define-sr_sprintf) (...) `SR\_UTILS\_NS::SPrintF(\_\_VA\_ARGS\_\_)`<br> |

## Macro Definition Documentation





### define SR\_FORMAT 

```C++
#define SR_FORMAT (
    ...
) `SR_UTILS_NS::Format(__VA_ARGS__)`
```




<hr>



### define SR\_FORMAT\_C 

```C++
#define SR_FORMAT_C (
    ...
) `SR_UTILS_NS::Format(__VA_ARGS__).c_str()`
```




<hr>



### define SR\_SPRINTF 

```C++
#define SR_SPRINTF (
    ...
) `SR_UTILS_NS::SPrintF(__VA_ARGS__)`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/StringFormat.h`

