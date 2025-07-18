

# File Debug.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Debug.h**](Debug_8h.md)

[Go to the source code of this file](Debug_8h_source.md)



* `#include <Utils/FileSystem/Path.h>`
* `#include <Utils/Common/Singleton.h>`
* `#include <Utils/Common/Enumerations.h>`
* `#include <Utils/Common/StringFormat.h>`
* `#include <Utils/Common/CastUtils.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**Debug**](classSR__UTILS__NS_1_1Debug.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SRAssert**](Debug_8h.md#define-srassert) (expr) `(SR\_NOOP)`<br> |
| define  | [**SRAssert1**](Debug_8h.md#define-srassert1) (expr) `SRAssert(expr)`<br> |
| define  | [**SRAssert1Once**](Debug_8h.md#define-srassert1once) (expr) `SRAssert2Once(expr, #expr)`<br> |
| define  | [**SRAssert2**](Debug_8h.md#define-srassert2) (expr, ...) `(SR\_NOOP)`<br> |
| define  | [**SRAssert2Once**](Debug_8h.md#define-srassert2once) (expr, ...) `(SR\_NOOP)`<br> |
| define  | [**SRAssertOnce**](Debug_8h.md#define-srassertonce) (expr) `SRAssert2Once(expr, "An exception has been occured!")`<br> |
| define  | [**SRHalt**](Debug_8h.md#define-srhalt) (...) `SR\_UTILS\_NS::Debug::Instance().Assert(SR\_MAKE\_ASSERT(SR\_FORMAT(\_\_VA\_ARGS\_\_)))`<br> |
| define  | [**SRHalt0**](Debug_8h.md#define-srhalt0) () `SRHalt("An exception has been occured!")`<br> |
| define  | [**SRHaltOnce**](Debug_8h.md#define-srhaltonce) (...) `SR\_UTILS\_NS::Debug::Instance().AssertOnceCheck(SR\_MAKE\_ASSERT(SR\_FORMAT(\_\_VA\_ARGS\_\_))) \|\| SRHalt(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SRHaltOnce0**](Debug_8h.md#define-srhaltonce0) () `SRHaltOnce("An exception has been occured!")`<br> |
| define  | [**SRVerify**](Debug_8h.md#define-srverify) (expr) `SRVerify2(expr, "An exception has been occured!")`<br> |
| define  | [**SRVerify2**](Debug_8h.md#define-srverify2) (expr, ...) `((expr))`<br> |
| define  | [**SRVerifyFalse**](Debug_8h.md#define-srverifyfalse) (expr) `SRVerifyFalse2(expr, "An exception has been occured!")`<br> |
| define  | [**SRVerifyFalse2**](Debug_8h.md#define-srverifyfalse2) (expr, ...) `((!(expr)))`<br> |
| define  | [**SR\_CHECK\_ERROR**](Debug_8h.md#define-sr_check_error) (fun, notEquals, errorMsg) `fun`<br> |
| define  | [**SR\_DEBUG\_LOG**](Debug_8h.md#define-sr_debug_log) (...) `SR\_UTILS\_NS::Debug::Instance().Print(SR\_FORMAT(\_\_VA\_ARGS\_\_), SR\_UTILS\_NS::DebugLogType::Debug)`<br> |
| define  | [**SR\_ERROR**](Debug_8h.md#define-sr_error) (...) `SR\_UTILS\_NS::Debug::Instance().Error(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_GRAPH**](Debug_8h.md#define-sr_graph) (...) `SR\_UTILS\_NS::Debug::Instance().Graph(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_GRAPH\_LOG**](Debug_8h.md#define-sr_graph_log) (...) `SR\_GRAPH(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_INFO**](Debug_8h.md#define-sr_info) (...) `SR\_UTILS\_NS::Debug::Instance().Info(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_LOG**](Debug_8h.md#define-sr_log) (...) `SR\_UTILS\_NS::Debug::Instance().Log(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_LOG\_TEST**](Debug_8h.md#define-sr_log_test) (...) `SR\_UTILS\_NS::Debug::Instance().Print(SR\_FORMAT(\_\_VA\_ARGS\_\_), SR\_UTILS\_NS::DebugLogType::Test)`<br> |
| define  | [**SR\_MAKE\_ASSERT**](Debug_8h.md#define-sr_make_assert) (msg) `(msg).append("\nFile: ").append(\_\_FILE\_\_).append("\nLine: ").append(std::to\_string(\_\_LINE\_\_))`<br> |
| define  | [**SR\_SAFE\_PTR\_ASSERT**](Debug_8h.md#define-sr_safe_ptr_assert) (expr, msg) `(SR\_NOOP)`<br> |
| define  | [**SR\_SHADER**](Debug_8h.md#define-sr_shader) (...) `SR\_UTILS\_NS::Debug::Instance().Shader(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_SHADER\_LOG**](Debug_8h.md#define-sr_shader_log) (...) `SR\_UTILS\_NS::Debug::Instance().Shader(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_SUCCESS**](Debug_8h.md#define-sr_success) (...) `SR\_UTILS\_NS::Debug::Instance().Success(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_SYSTEM\_LOG**](Debug_8h.md#define-sr_system_log) (...) `SR\_UTILS\_NS::Debug::Instance().System(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_VULKAN\_ERROR**](Debug_8h.md#define-sr_vulkan_error) (...) `SR\_UTILS\_NS::Debug::Instance().VulkanError(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_VULKAN\_LOG**](Debug_8h.md#define-sr_vulkan_log) (...) `SR\_UTILS\_NS::Debug::Instance().VulkanLog(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_VULKAN\_MSG**](Debug_8h.md#define-sr_vulkan_msg) (...) `SR\_UTILS\_NS::Debug::Instance().Vulkan(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |
| define  | [**SR\_WARN**](Debug_8h.md#define-sr_warn) (...) `SR\_UTILS\_NS::Debug::Instance().Warn(SR\_FORMAT(\_\_VA\_ARGS\_\_))`<br> |

## Macro Definition Documentation





### define SRAssert 

```C++
#define SRAssert (
    expr
) `(SR_NOOP)`
```




<hr>



### define SRAssert1 

```C++
#define SRAssert1 (
    expr
) `SRAssert(expr)`
```




<hr>



### define SRAssert1Once 

```C++
#define SRAssert1Once (
    expr
) `SRAssert2Once(expr, #expr)`
```




<hr>



### define SRAssert2 

```C++
#define SRAssert2 (
    expr,
    ...
) `(SR_NOOP)`
```




<hr>



### define SRAssert2Once 

```C++
#define SRAssert2Once (
    expr,
    ...
) `(SR_NOOP)`
```




<hr>



### define SRAssertOnce 

```C++
#define SRAssertOnce (
    expr
) `SRAssert2Once(expr, "An exception has been occured!")`
```




<hr>



### define SRHalt 

```C++
#define SRHalt (
    ...
) `SR_UTILS_NS::Debug::Instance().Assert(SR_MAKE_ASSERT(SR_FORMAT(__VA_ARGS__)))`
```




<hr>



### define SRHalt0 

```C++
#define SRHalt0 (
    
) `SRHalt("An exception has been occured!")`
```




<hr>



### define SRHaltOnce 

```C++
#define SRHaltOnce (
    ...
) `SR_UTILS_NS::Debug::Instance().AssertOnceCheck(SR_MAKE_ASSERT(SR_FORMAT(__VA_ARGS__))) || SRHalt(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SRHaltOnce0 

```C++
#define SRHaltOnce0 (
    
) `SRHaltOnce("An exception has been occured!")`
```




<hr>



### define SRVerify 

```C++
#define SRVerify (
    expr
) `SRVerify2(expr, "An exception has been occured!")`
```




<hr>



### define SRVerify2 

```C++
#define SRVerify2 (
    expr,
    ...
) `((expr))`
```




<hr>



### define SRVerifyFalse 

```C++
#define SRVerifyFalse (
    expr
) `SRVerifyFalse2(expr, "An exception has been occured!")`
```




<hr>



### define SRVerifyFalse2 

```C++
#define SRVerifyFalse2 (
    expr,
    ...
) `((!(expr)))`
```




<hr>



### define SR\_CHECK\_ERROR 

```C++
#define SR_CHECK_ERROR (
    fun,
    notEquals,
    errorMsg
) `fun`
```




<hr>



### define SR\_DEBUG\_LOG 

```C++
#define SR_DEBUG_LOG (
    ...
) `SR_UTILS_NS::Debug::Instance().Print(SR_FORMAT(__VA_ARGS__), SR_UTILS_NS::DebugLogType::Debug)`
```




<hr>



### define SR\_ERROR 

```C++
#define SR_ERROR (
    ...
) `SR_UTILS_NS::Debug::Instance().Error(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_GRAPH 

```C++
#define SR_GRAPH (
    ...
) `SR_UTILS_NS::Debug::Instance().Graph(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_GRAPH\_LOG 

```C++
#define SR_GRAPH_LOG (
    ...
) `SR_GRAPH(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_INFO 

```C++
#define SR_INFO (
    ...
) `SR_UTILS_NS::Debug::Instance().Info(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_LOG 

```C++
#define SR_LOG (
    ...
) `SR_UTILS_NS::Debug::Instance().Log(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_LOG\_TEST 

```C++
#define SR_LOG_TEST (
    ...
) `SR_UTILS_NS::Debug::Instance().Print(SR_FORMAT(__VA_ARGS__), SR_UTILS_NS::DebugLogType::Test)`
```




<hr>



### define SR\_MAKE\_ASSERT 

```C++
#define SR_MAKE_ASSERT (
    msg
) `(msg).append("\nFile: ").append(__FILE__).append("\nLine: ").append(std::to_string(__LINE__))`
```




<hr>



### define SR\_SAFE\_PTR\_ASSERT 

```C++
#define SR_SAFE_PTR_ASSERT (
    expr,
    msg
) `(SR_NOOP)`
```




<hr>



### define SR\_SHADER 

```C++
#define SR_SHADER (
    ...
) `SR_UTILS_NS::Debug::Instance().Shader(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_SHADER\_LOG 

```C++
#define SR_SHADER_LOG (
    ...
) `SR_UTILS_NS::Debug::Instance().Shader(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_SUCCESS 

```C++
#define SR_SUCCESS (
    ...
) `SR_UTILS_NS::Debug::Instance().Success(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_SYSTEM\_LOG 

```C++
#define SR_SYSTEM_LOG (
    ...
) `SR_UTILS_NS::Debug::Instance().System(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_VULKAN\_ERROR 

```C++
#define SR_VULKAN_ERROR (
    ...
) `SR_UTILS_NS::Debug::Instance().VulkanError(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_VULKAN\_LOG 

```C++
#define SR_VULKAN_LOG (
    ...
) `SR_UTILS_NS::Debug::Instance().VulkanLog(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_VULKAN\_MSG 

```C++
#define SR_VULKAN_MSG (
    ...
) `SR_UTILS_NS::Debug::Instance().Vulkan(SR_FORMAT(__VA_ARGS__))`
```




<hr>



### define SR\_WARN 

```C++
#define SR_WARN (
    ...
) `SR_UTILS_NS::Debug::Instance().Warn(SR_FORMAT(__VA_ARGS__))`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Debug.h`

