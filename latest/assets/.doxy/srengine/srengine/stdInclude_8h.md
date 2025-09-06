

# File stdInclude.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**stdInclude.h**](stdInclude_8h.md)

[Go to the source code of this file](stdInclude_8h_source.md)



* `#include <Utils/macros.h>`
* `#include <string>`
* `#include <array>`
* `#include <map>`
* `#include <vector>`
* `#include <cstdint>`
* `#include <set>`
* `#include <optional>`
* `#include <cfloat>`
* `#include <span>`
* `#include <limits>`
* `#include <bitset>`
* `#include <type_traits>`
* `#include <cstdio>`
* `#include <iosfwd>`
* `#include <regex>`
* `#include <stdexcept>`
* `#include <string_view>`
* `#include <shared_mutex>`
* `#include <cstdarg>`
* `#include <initializer_list>`
* `#include <codecvt>`
* `#include <cstddef>`
* `#include <unordered_set>`
* `#include <stack>`
* `#include <cctype>`
* `#include <charconv>`
* `#include <locale>`
* `#include <cstring>`
* `#include <variant>`
* `#include <memory>`
* `#include <fstream>`
* `#include <ostream>`
* `#include <queue>`
* `#include <mutex>`
* `#include <cassert>`
* `#include <cmath>`
* `#include <ranges>`
* `#include <atomic>`
* `#include <utility>`
* `#include <functional>`
* `#include <exception>`
* `#include <unordered_map>`
* `#include <algorithm>`
* `#include <any>`
* `#include <thread>`
* `#include <sstream>`
* `#include <list>`
* `#include <ctime>`
* `#include <iostream>`
* `#include <ratio>`
* `#include <chrono>`
* `#include <random>`
* `#include <iomanip>`
* `#include <concepts>`
* `#include <condition_variable>`
* `#include <numeric>`
* `#include <numbers>`
* `#include <execution>`
* `#include <xxHash/xxhash.h>`
* `#include <zlib.h>`
* `#include <fmt/format.h>`
* `#include <fmt/printf.h>`
* `#include <fmt/color.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**Codegen**](namespaceCodegen.md) <br> |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |
| namespace | [**string\_literals**](namespacestd_1_1literals_1_1string__literals.md) <br> |
| namespace | [**string\_view\_literals**](namespacestd_1_1literals_1_1string__view__literals.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**EnumSelector**](structCodegen_1_1EnumSelector.md) &lt;typename EnumType&gt;<br> |
| struct | [**InputIteratorPointer**](structSR__UTILS__NS_1_1InputIteratorPointer.md) &lt;typename T&gt;<br> |
| struct | [**IsDerivedFrom**](structSR__UTILS__NS_1_1IsDerivedFrom.md) &lt;T, class U&gt;<br> |
| struct | [**SmallStack**](structSR__UTILS__NS_1_1SmallStack.md) &lt;typename T, N&gt;<br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  constexpr uint32\_t | [**SR\_INVALID\_DESCRIPTOR\_SET**](#variable-sr_invalid_descriptor_set)   = `SR\_ID\_INVALID`<br> |
|  constexpr uint32\_t | [**SR\_INVALID\_FBO**](#variable-sr_invalid_fbo)   = `SR\_ID\_INVALID`<br> |
|  constexpr uint32\_t | [**SR\_INVALID\_IBO**](#variable-sr_invalid_ibo)   = `SR\_ID\_INVALID`<br> |
|  constexpr uint32\_t | [**SR\_INVALID\_SSBO**](#variable-sr_invalid_ssbo)   = `SR\_ID\_INVALID`<br> |
|  constexpr uint32\_t | [**SR\_INVALID\_UBO**](#variable-sr_invalid_ubo)   = `SR\_ID\_INVALID`<br> |
|  constexpr uint32\_t | [**SR\_INVALID\_VBO**](#variable-sr_invalid_vbo)   = `SR\_ID\_INVALID`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string\_view | [**SRGetClassName**](#function-srgetclassname) (std::string\_view func\_signature) <br> |



























## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_EXCHANGE**](stdInclude_8h.md#define-sr_exchange) (x, y) `SR\_UTILS\_NS::Exchange(x, y)`<br> |
| define  | [**SR\_GET\_CLASS\_NAME**](stdInclude_8h.md#define-sr_get_class_name) () `SRGetClassName(\_\_PRETTY\_FUNCTION\_\_)`<br> |
| define  | [**SR\_GET\_COMPILE\_TIME\_CLASS\_NAME**](stdInclude_8h.md#define-sr_get_compile_time_class_name) (T) `SR\_UTILS\_NS::GetCompileTimeTypeName&lt;T&gt;()`<br> |
| define  | [**SR\_IGNORE\_UNUSED**](stdInclude_8h.md#define-sr_ignore_unused) (...) `SR\_UTILS\_NS::IgnoreUnused(\_\_VA\_ARGS\_\_)`<br> |
| define  | [**XXH\_STATIC\_LINKING\_ONLY**](stdInclude_8h.md#define-xxh_static_linking_only)  <br> |

## Public Attributes Documentation




### variable SR\_INVALID\_DESCRIPTOR\_SET 

```C++
constexpr uint32_t SR_INVALID_DESCRIPTOR_SET;
```




<hr>



### variable SR\_INVALID\_FBO 

```C++
constexpr uint32_t SR_INVALID_FBO;
```




<hr>



### variable SR\_INVALID\_IBO 

```C++
constexpr uint32_t SR_INVALID_IBO;
```




<hr>



### variable SR\_INVALID\_SSBO 

```C++
constexpr uint32_t SR_INVALID_SSBO;
```




<hr>



### variable SR\_INVALID\_UBO 

```C++
constexpr uint32_t SR_INVALID_UBO;
```




<hr>



### variable SR\_INVALID\_VBO 

```C++
constexpr uint32_t SR_INVALID_VBO;
```




<hr>
## Public Functions Documentation




### function SRGetClassName 

```C++
inline std::string_view SRGetClassName (
    std::string_view func_signature
) 
```



C++17 - 201703L C++14 - 201402L C++11 - 201103L C++98 - 199711L 


        

<hr>
## Macro Definition Documentation





### define SR\_EXCHANGE 

```C++
#define SR_EXCHANGE (
    x,
    y
) `SR_UTILS_NS::Exchange(x, y)`
```




<hr>



### define SR\_GET\_CLASS\_NAME 

```C++
#define SR_GET_CLASS_NAME (
    
) `SRGetClassName(__PRETTY_FUNCTION__)`
```




<hr>



### define SR\_GET\_COMPILE\_TIME\_CLASS\_NAME 

```C++
#define SR_GET_COMPILE_TIME_CLASS_NAME (
    T
) `SR_UTILS_NS::GetCompileTimeTypeName<T>()`
```




<hr>



### define SR\_IGNORE\_UNUSED 

```C++
#define SR_IGNORE_UNUSED (
    ...
) `SR_UTILS_NS::IgnoreUnused(__VA_ARGS__)`
```




<hr>



### define XXH\_STATIC\_LINKING\_ONLY 

```C++
#define XXH_STATIC_LINKING_ONLY 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/stdInclude.h`

