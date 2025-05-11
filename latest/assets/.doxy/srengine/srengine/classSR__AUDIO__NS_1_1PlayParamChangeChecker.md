

# Class SR\_AUDIO\_NS::PlayParamChangeChecker

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**PlayParamChangeChecker**](classSR__AUDIO__NS_1_1PlayParamChangeChecker.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PlayParamChangeChecker**](#function-playparamchangechecker-12) () = default<br> |
|   | [**PlayParamChangeChecker**](#function-playparamchangechecker-22) (const T & value) <br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE bool | [**has\_value**](#function-has_value) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE bool | [**is\_changed**](#function-is_changed) () noexcept const<br> |
|  SR\_FORCE\_INLINE void | [**mark\_as\_changed**](#function-mark_as_changed) () noexcept const<br> |
|  [**PlayParamChangeChecker**](classSR__AUDIO__NS_1_1PlayParamChangeChecker.md) & | [**operator=**](#function-operator) (const T & value) <br> |
|  SR\_FORCE\_INLINE void | [**reset\_changed**](#function-reset_changed) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T & | [**value**](#function-value-12) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T & | [**value**](#function-value-22) () noexcept<br> |




























## Public Functions Documentation




### function PlayParamChangeChecker [1/2]

```C++
SR_AUDIO_NS::PlayParamChangeChecker::PlayParamChangeChecker () = default
```




<hr>



### function PlayParamChangeChecker [2/2]

```C++
inline explicit SR_AUDIO_NS::PlayParamChangeChecker::PlayParamChangeChecker (
    const T & value
) 
```




<hr>



### function has\_value 

```C++
inline SR_NODISCARD SR_FORCE_INLINE bool SR_AUDIO_NS::PlayParamChangeChecker::has_value () noexcept const
```




<hr>



### function is\_changed 

```C++
inline SR_NODISCARD SR_FORCE_INLINE bool SR_AUDIO_NS::PlayParamChangeChecker::is_changed () noexcept const
```




<hr>



### function mark\_as\_changed 

```C++
inline SR_FORCE_INLINE void SR_AUDIO_NS::PlayParamChangeChecker::mark_as_changed () noexcept const
```




<hr>



### function operator= 

```C++
inline PlayParamChangeChecker & SR_AUDIO_NS::PlayParamChangeChecker::operator= (
    const T & value
) 
```




<hr>



### function reset\_changed 

```C++
inline SR_FORCE_INLINE void SR_AUDIO_NS::PlayParamChangeChecker::reset_changed () noexcept const
```




<hr>



### function value [1/2]

```C++
inline SR_NODISCARD SR_FORCE_INLINE const T & SR_AUDIO_NS::PlayParamChangeChecker::value () noexcept const
```




<hr>



### function value [2/2]

```C++
inline SR_NODISCARD SR_FORCE_INLINE T & SR_AUDIO_NS::PlayParamChangeChecker::value () noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Audio/inc/Audio/PlayParams.h`

