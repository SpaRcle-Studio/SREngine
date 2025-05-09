

# Class EvoScript::AddressTableGen



[**ClassList**](annotated.md) **>** [**EvoScript**](namespaceEvoScript.md) **>** [**AddressTableGen**](classEvoScript_1_1AddressTableGen.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**AddIncompleteType**](#function-addincompletetype) (const std::string & className, const std::string & header) <br> |
|  void | [**AddMethodPointer**](#function-addmethodpointer) (const std::function&lt; void([**EvoScript::IState**](classEvoScript_1_1IState.md) \*)&gt; & setter) <br> |
|   | [**AddressTableGen**](#function-addresstablegen-12) () = default<br> |
|   | [**AddressTableGen**](#function-addresstablegen-22) (const [**AddressTableGen**](classEvoScript_1_1AddressTableGen.md) &) = delete<br> |
|  SR\_NODISCARD std::vector&lt; std::function&lt; void([**EvoScript::IState**](classEvoScript_1_1IState.md) \*)&gt; &gt; | [**GetAddresses**](#function-getaddresses) () const<br> |
|  SR\_NODISCARD size\_t | [**GetApiHash**](#function-getapihash) () const<br> |
|  SR\_NODISCARD std::string | [**GetApiVersion**](#function-getapiversion) () const<br> |
|  SR\_NODISCARD [**Header**](structEvoScript_1_1Header.md) | [**GetHeader**](#function-getheader) (const std::string & name) const<br> |
|  T \* | [**GetPointer**](#function-getpointer) () const<br> |
|  void | [**HashCombine**](#function-hashcombine) (const std::string & hashString) <br> |
|  bool | [**RegisterDefine**](#function-registerdefine) (const std::string & name, const std::string & header, const std::string & value) <br> |
|  bool | [**RegisterEnum**](#function-registerenum) (const std::string & name, const std::string & header, bool asClass, const std::vector&lt; std::pair&lt; std::string, int32\_t &gt; &gt; & values) <br> |
|  bool | [**RegisterFunction**](#function-registerfunction) (const SetterFn & setter, const std::string & methodName, const std::string & returnType, const std::vector&lt; std::string &gt; & argTypes, const std::string & header) <br> |
|  bool | [**RegisterHeader**](#function-registerheader) (const std::string & name, const std::set&lt; std::string &gt; & includes={}) <br> |
|  bool | [**RegisterMethod**](#function-registermethod-12) (const SetterFn & setter, const std::string & className, const std::string & methodName, const std::string & returnType, const std::vector&lt; std::string &gt; & argTypes, MethodType type, const std::string & \_overrideClass="", Publicity publicity=Publicity::Public) <br> |
|  bool | [**RegisterMethod**](#function-registermethod-22) (const std::string & className, const std::string & methodName, const std::string & returnType, const std::vector&lt; std::string &gt; & argTypes, MethodType type, const std::string & \_overrideClass="", Publicity publicity=Publicity::Public) <br> |
|  bool | [**RegisterNewClass**](#function-registernewclass) (const std::string & name, const std::string & header, const std::set&lt; std::string &gt; & includes={}, const std::vector&lt; [**InheritClass**](structEvoScript_1_1InheritClass.md) &gt; & inherit={}) <br> |
|  bool | [**RegisterTypedef**](#function-registertypedef) (const std::string & name, const std::string & header, const std::string & value) <br> |
|  bool | [**RegisterUsing**](#function-registerusing) (const std::string & name, const std::string & header, const std::string & value) <br> |
|  bool | [**Save**](#function-save) (const std::string & libFolder) <br> |
|  void | [**SetPointer**](#function-setpointer) (T \* pointer) <br> |
|   | [**~AddressTableGen**](#function-addresstablegen) () = default<br> |




























## Public Functions Documentation




### function AddIncompleteType 

```C++
bool EvoScript::AddressTableGen::AddIncompleteType (
    const std::string & className,
    const std::string & header
) 
```




<hr>



### function AddMethodPointer 

```C++
void EvoScript::AddressTableGen::AddMethodPointer (
    const std::function< void( EvoScript::IState *)> & setter
) 
```




<hr>



### function AddressTableGen [1/2]

```C++
EvoScript::AddressTableGen::AddressTableGen () = default
```




<hr>



### function AddressTableGen [2/2]

```C++
EvoScript::AddressTableGen::AddressTableGen (
    const AddressTableGen &
) = delete
```




<hr>



### function GetAddresses 

```C++
inline SR_NODISCARD std::vector< std::function< void( EvoScript::IState *)> > EvoScript::AddressTableGen::GetAddresses () const
```




<hr>



### function GetApiHash 

```C++
inline SR_NODISCARD size_t EvoScript::AddressTableGen::GetApiHash () const
```




<hr>



### function GetApiVersion 

```C++
inline SR_NODISCARD std::string EvoScript::AddressTableGen::GetApiVersion () const
```




<hr>



### function GetHeader 

```C++
inline SR_NODISCARD Header EvoScript::AddressTableGen::GetHeader (
    const std::string & name
) const
```




<hr>



### function GetPointer 

```C++
template<typename T>
inline T * EvoScript::AddressTableGen::GetPointer () const
```




<hr>



### function HashCombine 

```C++
void EvoScript::AddressTableGen::HashCombine (
    const std::string & hashString
) 
```




<hr>



### function RegisterDefine 

```C++
bool EvoScript::AddressTableGen::RegisterDefine (
    const std::string & name,
    const std::string & header,
    const std::string & value
) 
```




<hr>



### function RegisterEnum 

```C++
bool EvoScript::AddressTableGen::RegisterEnum (
    const std::string & name,
    const std::string & header,
    bool asClass,
    const std::vector< std::pair< std::string, int32_t > > & values
) 
```




<hr>



### function RegisterFunction 

```C++
bool EvoScript::AddressTableGen::RegisterFunction (
    const SetterFn & setter,
    const std::string & methodName,
    const std::string & returnType,
    const std::vector< std::string > & argTypes,
    const std::string & header
) 
```




<hr>



### function RegisterHeader 

```C++
bool EvoScript::AddressTableGen::RegisterHeader (
    const std::string & name,
    const std::set< std::string > & includes={}
) 
```




<hr>



### function RegisterMethod [1/2]

```C++
bool EvoScript::AddressTableGen::RegisterMethod (
    const SetterFn & setter,
    const std::string & className,
    const std::string & methodName,
    const std::string & returnType,
    const std::vector< std::string > & argTypes,
    MethodType type,
    const std::string & _overrideClass="",
    Publicity publicity=Publicity::Public
) 
```




<hr>



### function RegisterMethod [2/2]

```C++
bool EvoScript::AddressTableGen::RegisterMethod (
    const std::string & className,
    const std::string & methodName,
    const std::string & returnType,
    const std::vector< std::string > & argTypes,
    MethodType type,
    const std::string & _overrideClass="",
    Publicity publicity=Publicity::Public
) 
```




<hr>



### function RegisterNewClass 

```C++
bool EvoScript::AddressTableGen::RegisterNewClass (
    const std::string & name,
    const std::string & header,
    const std::set< std::string > & includes={},
    const std::vector< InheritClass > & inherit={}
) 
```




<hr>



### function RegisterTypedef 

```C++
bool EvoScript::AddressTableGen::RegisterTypedef (
    const std::string & name,
    const std::string & header,
    const std::string & value
) 
```




<hr>



### function RegisterUsing 

```C++
bool EvoScript::AddressTableGen::RegisterUsing (
    const std::string & name,
    const std::string & header,
    const std::string & value
) 
```




<hr>



### function Save 

```C++
bool EvoScript::AddressTableGen::Save (
    const std::string & libFolder
) 
```




<hr>



### function SetPointer 

```C++
template<typename T>
inline void EvoScript::AddressTableGen::SetPointer (
    T * pointer
) 
```




<hr>



### function ~AddressTableGen 

```C++
EvoScript::AddressTableGen::~AddressTableGen () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Old/Compilation/AddressTableGen.h`

