

# Struct SR\_UTILS\_NS::Platform::PlatformHooks



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Platform**](namespaceSR__UTILS__NS_1_1Platform.md) **>** [**PlatformHooks**](structSR__UTILS__NS_1_1Platform_1_1PlatformHooks.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::function&lt; Path::Type(const std::string\_view &)&gt; | [**getFileTypeHook**](#variable-getfiletypehook)  <br> |
|  decltype(&GetPathType) | [**originalGetPathType**](#variable-originalgetpathtype)   = `nullptr`<br> |
|  decltype(&ReadFile) | [**originalReadFile**](#variable-originalreadfile)   = `nullptr`<br> |
|  std::function&lt; std::string\_view(std::string\_view)&gt; | [**pathResolver**](#variable-pathresolver)  <br> |
|  std::function&lt; std::optional&lt; std::string &gt;(const [**Path**](classSR__UTILS__NS_1_1Path.md) &)&gt; | [**readFileHook**](#variable-readfilehook)  <br> |












































## Public Attributes Documentation




### variable getFileTypeHook 

```C++
std::function<Path::Type(const std::string_view&)> SR_UTILS_NS::Platform::PlatformHooks::getFileTypeHook;
```




<hr>



### variable originalGetPathType 

```C++
decltype(&GetPathType) SR_UTILS_NS::Platform::PlatformHooks::originalGetPathType;
```




<hr>



### variable originalReadFile 

```C++
decltype(&ReadFile) SR_UTILS_NS::Platform::PlatformHooks::originalReadFile;
```




<hr>



### variable pathResolver 

```C++
std::function<std::string_view(std::string_view)> SR_UTILS_NS::Platform::PlatformHooks::pathResolver;
```




<hr>



### variable readFileHook 

```C++
std::function<std::optional<std::string>(const Path&)> SR_UTILS_NS::Platform::PlatformHooks::readFileHook;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Platform/Platform.h`

