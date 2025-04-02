

# Class SR\_HTYPES\_NS::DataStorage



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md)








Inherits the following classes: NonCopyable














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) \* | [**Ptr**](#typedef-ptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Clear**](#function-clear) () <br> |
|   | [**DataStorage**](#function-datastorage-12) () = default<br> |
|   | [**DataStorage**](#function-datastorage-22) ([**DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) && data) noexcept<br> |
|  T \* | [**GetPointer**](#function-getpointer-13) (const std::string & name) const<br> |
|  T \* | [**GetPointer**](#function-getpointer-23) () const<br> |
|  T \* | [**GetPointerDef**](#function-getpointerdef-13) (const std::string & name, T \* def) const<br> |
|  T \* | [**GetPointerDef**](#function-getpointerdef-23) (T \* def) const<br> |
|  T | [**GetValue**](#function-getvalue-14) (const char \* name) const<br> |
|  T | [**GetValue**](#function-getvalue-24) (const std::string & name) const<br> |
|  T | [**GetValue**](#function-getvalue-34) () const<br> |
|  T | [**GetValueDef**](#function-getvaluedef-13) (const std::string & name, const T & def) const<br> |
|  T | [**GetValueDef**](#function-getvaluedef-23) (const T & def) const<br> |
|  std::vector&lt; std::pair&lt; std::string, T &gt; &gt; | [**GetValues**](#function-getvalues) () <br> |
|  bool | [**RemovePointer**](#function-removepointer-13) () <br> |
|  bool | [**RemovePointer**](#function-removepointer-23) (const std::string & name) <br> |
|  bool | [**RemoveValue**](#function-removevalue-13) () <br> |
|  bool | [**RemoveValue**](#function-removevalue-23) (const std::string & name) <br> |
|  void | [**SetPointer**](#function-setpointer-13) (const std::string & name, T \* pointer) <br> |
|  void | [**SetPointer**](#function-setpointer-23) (T \* pointer) <br> |
|  void | [**SetValue**](#function-setvalue-13) (const std::string & name, const T & value) <br> |
|  void | [**SetValue**](#function-setvalue-23) (const T & value) <br> |
|  [**DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) & | [**operator=**](#function-operator) ([**DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) && data) noexcept<br> |
|   | [**~DataStorage**](#function-datastorage) () override<br> |




























## Public Types Documentation




### typedef Ptr 

```C++
using SR_HTYPES_NS::DataStorage::Ptr =  DataStorage*;
```




<hr>
## Public Functions Documentation




### function Clear 

```C++
inline void SR_HTYPES_NS::DataStorage::Clear () 
```




<hr>



### function DataStorage [1/2]

```C++
SR_HTYPES_NS::DataStorage::DataStorage () = default
```




<hr>



### function DataStorage [2/2]

```C++
inline SR_HTYPES_NS::DataStorage::DataStorage (
    DataStorage && data
) noexcept
```




<hr>



### function GetPointer [1/3]

```C++
template<typename T>
T * SR_HTYPES_NS::DataStorage::GetPointer (
    const std::string & name
) const
```




<hr>



### function GetPointer [2/3]

```C++
template<typename T>
T * SR_HTYPES_NS::DataStorage::GetPointer () const
```




<hr>



### function GetPointerDef [1/3]

```C++
template<typename T>
T * SR_HTYPES_NS::DataStorage::GetPointerDef (
    const std::string & name,
    T * def
) const
```




<hr>



### function GetPointerDef [2/3]

```C++
template<typename T>
T * SR_HTYPES_NS::DataStorage::GetPointerDef (
    T * def
) const
```




<hr>



### function GetValue [1/4]

```C++
template<typename T>
T SR_HTYPES_NS::DataStorage::GetValue (
    const char * name
) const
```




<hr>



### function GetValue [2/4]

```C++
template<typename T>
T SR_HTYPES_NS::DataStorage::GetValue (
    const std::string & name
) const
```




<hr>



### function GetValue [3/4]

```C++
template<typename T>
T SR_HTYPES_NS::DataStorage::GetValue () const
```




<hr>



### function GetValueDef [1/3]

```C++
template<typename T>
T SR_HTYPES_NS::DataStorage::GetValueDef (
    const std::string & name,
    const T & def
) const
```




<hr>



### function GetValueDef [2/3]

```C++
template<typename T>
T SR_HTYPES_NS::DataStorage::GetValueDef (
    const T & def
) const
```




<hr>



### function GetValues 

```C++
template<typename T>
std::vector< std::pair< std::string, T > > SR_HTYPES_NS::DataStorage::GetValues () 
```




<hr>



### function RemovePointer [1/3]

```C++
template<typename T>
bool SR_HTYPES_NS::DataStorage::RemovePointer () 
```




<hr>



### function RemovePointer [2/3]

```C++
template<typename T>
bool SR_HTYPES_NS::DataStorage::RemovePointer (
    const std::string & name
) 
```




<hr>



### function RemoveValue [1/3]

```C++
template<typename T>
bool SR_HTYPES_NS::DataStorage::RemoveValue () 
```




<hr>



### function RemoveValue [2/3]

```C++
template<typename T>
bool SR_HTYPES_NS::DataStorage::RemoveValue (
    const std::string & name
) 
```




<hr>



### function SetPointer [1/3]

```C++
template<typename T>
void SR_HTYPES_NS::DataStorage::SetPointer (
    const std::string & name,
    T * pointer
) 
```




 


        

<hr>



### function SetPointer [2/3]

```C++
template<typename T>
void SR_HTYPES_NS::DataStorage::SetPointer (
    T * pointer
) 
```




<hr>



### function SetValue [1/3]

```C++
template<typename T>
void SR_HTYPES_NS::DataStorage::SetValue (
    const std::string & name,
    const T & value
) 
```




<hr>



### function SetValue [2/3]

```C++
template<typename T>
void SR_HTYPES_NS::DataStorage::SetValue (
    const T & value
) 
```




<hr>



### function operator= 

```C++
inline DataStorage & SR_HTYPES_NS::DataStorage::operator= (
    DataStorage && data
) noexcept
```




<hr>



### function ~DataStorage 

```C++
inline SR_HTYPES_NS::DataStorage::~DataStorage () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/DataStorage.h`

