

# Struct SR\_SRSL\_NS::ShaderMacrosParams



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**ShaderMacrosParams**](structSR__SRSL__NS_1_1ShaderMacrosParams.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddDefine**](#function-adddefine) (const std::string & define) <br> |
|  void | [**Clear**](#function-clear) () <br> |
|  SR\_NODISCARD SR\_UTILS\_NS::SRHashType | [**GetHash**](#function-gethash) () const<br> |
|  SR\_NODISCARD std::string | [**GetHashStr**](#function-gethashstr) () const<br> |
|  SR\_NODISCARD const std::map&lt; std::string, std::string &gt; & | [**GetParams**](#function-getparams) () const<br> |
|  void | [**InitHash**](#function-inithash) () <br> |
|  bool | [**IsDefined**](#function-isdefined) (const std::string\_view & key) const<br> |
|  void | [**SetParam**](#function-setparam) (const std::string & key, const std::string & value) <br> |
|  SR\_NODISCARD bool | [**empty**](#function-empty) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  const [**ShaderMacrosParams**](structSR__SRSL__NS_1_1ShaderMacrosParams.md) & | [**GetDefault**](#function-getdefault) () <br> |


























## Public Functions Documentation




### function AddDefine 

```C++
inline void SR_SRSL_NS::ShaderMacrosParams::AddDefine (
    const std::string & define
) 
```




<hr>



### function Clear 

```C++
inline void SR_SRSL_NS::ShaderMacrosParams::Clear () 
```




<hr>



### function GetHash 

```C++
SR_NODISCARD SR_UTILS_NS::SRHashType SR_SRSL_NS::ShaderMacrosParams::GetHash () const
```




<hr>



### function GetHashStr 

```C++
SR_NODISCARD std::string SR_SRSL_NS::ShaderMacrosParams::GetHashStr () const
```




<hr>



### function GetParams 

```C++
inline SR_NODISCARD const std::map< std::string, std::string > & SR_SRSL_NS::ShaderMacrosParams::GetParams () const
```




<hr>



### function InitHash 

```C++
void SR_SRSL_NS::ShaderMacrosParams::InitHash () 
```




<hr>



### function IsDefined 

```C++
inline bool SR_SRSL_NS::ShaderMacrosParams::IsDefined (
    const std::string_view & key
) const
```




<hr>



### function SetParam 

```C++
inline void SR_SRSL_NS::ShaderMacrosParams::SetParam (
    const std::string & key,
    const std::string & value
) 
```




<hr>



### function empty 

```C++
inline SR_NODISCARD bool SR_SRSL_NS::ShaderMacrosParams::empty () const
```




<hr>
## Public Static Functions Documentation




### function GetDefault 

```C++
static const ShaderMacrosParams & SR_SRSL_NS::ShaderMacrosParams::GetDefault () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Loaders/SRSL.h`

