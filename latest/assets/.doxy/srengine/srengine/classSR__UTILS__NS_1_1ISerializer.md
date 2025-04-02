

# Class SR\_UTILS\_NS::ISerializer



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md)










Inherited by the following classes: [SR\_UTILS\_NS::IBaseSerializer](classSR__UTILS__NS_1_1IBaseSerializer.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::unique\_ptr&lt; [**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) &gt; | [**UniquePtr**](#typedef-uniqueptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginArray**](#function-beginarray) (uint64\_t size, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual void | [**BeginItem**](#function-beginitem) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual void | [**BeginObject**](#function-beginobject) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual SR\_NODISCARD std::unique\_ptr&lt; [**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &gt; | [**CreateDeserializer**](#function-createdeserializer) () const = 0<br> |
| virtual void | [**EndArray**](#function-endarray) () = 0<br> |
| virtual void | [**EndItem**](#function-enditem) () = 0<br> |
| virtual void | [**EndObject**](#function-endobject) () = 0<br> |
| virtual SR\_NODISCARD bool | [**IsAllowEmptyElementsInArray**](#function-isallowemptyelementsinarray) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsEditorAllowed**](#function-iseditorallowed) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsWriteDefaults**](#function-iswritedefaults) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsWriteVersion**](#function-iswriteversion) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**SaveToFile**](#function-savetofile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |
|  void | [**SetAllowEmptyElementsInArray**](#function-setallowemptyelementsinarray) (const bool value) noexcept<br> |
|  void | [**SetEditorAllowed**](#function-seteditorallowed) (const bool value) noexcept<br> |
|  void | [**SetWriteDefaults**](#function-setwritedefaults) (const bool value) noexcept<br> |
|  void | [**SetWriteVersion**](#function-setwriteversion) (const bool value) noexcept<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](#function-tostring) () noexcept const<br> |
|  void | [**WriteAny**](#function-writeany) (const std::any & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) <br> |
| virtual void | [**WriteBool**](#function-writebool) (bool value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteDouble**](#function-writedouble) (double\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteFloat**](#function-writefloat) (float\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteInt**](#function-writeint-14) (int8\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteInt**](#function-writeint-24) (int16\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteInt**](#function-writeint-34) (int32\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteInt**](#function-writeint-44) (int64\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteString**](#function-writestring-12) (std::string\_view value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteString**](#function-writestring-22) (std::u32string\_view value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteUInt**](#function-writeuint-14) (uint8\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteUInt**](#function-writeuint-24) (uint16\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteUInt**](#function-writeuint-34) (uint32\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteUInt**](#function-writeuint-44) (uint64\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual  | [**~ISerializer**](#function-iserializer) () = default<br> |




























## Public Types Documentation




### typedef UniquePtr 

```C++
using SR_UTILS_NS::ISerializer::UniquePtr =  std::unique_ptr<ISerializer>;
```




<hr>
## Public Functions Documentation




### function BeginArray 

```C++
virtual void SR_UTILS_NS::ISerializer::BeginArray (
    uint64_t size,
    const SerializationId & id
) = 0
```




<hr>



### function BeginItem 

```C++
virtual void SR_UTILS_NS::ISerializer::BeginItem (
    const SerializationId & id
) = 0
```




<hr>



### function BeginObject 

```C++
virtual void SR_UTILS_NS::ISerializer::BeginObject (
    const SerializationId & id
) = 0
```




<hr>



### function CreateDeserializer 

```C++
virtual SR_NODISCARD std::unique_ptr< IDeserializer > SR_UTILS_NS::ISerializer::CreateDeserializer () const = 0
```




<hr>



### function EndArray 

```C++
virtual void SR_UTILS_NS::ISerializer::EndArray () = 0
```




<hr>



### function EndItem 

```C++
virtual void SR_UTILS_NS::ISerializer::EndItem () = 0
```




<hr>



### function EndObject 

```C++
virtual void SR_UTILS_NS::ISerializer::EndObject () = 0
```




<hr>



### function IsAllowEmptyElementsInArray 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::ISerializer::IsAllowEmptyElementsInArray () noexcept const
```




<hr>



### function IsEditorAllowed 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::ISerializer::IsEditorAllowed () noexcept const
```




<hr>



### function IsWriteDefaults 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::ISerializer::IsWriteDefaults () noexcept const
```




<hr>



### function IsWriteVersion 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::ISerializer::IsWriteVersion () noexcept const
```




<hr>



### function SaveToFile 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::ISerializer::SaveToFile (
    const SR_UTILS_NS::Path & path
) const
```




<hr>



### function SetAllowEmptyElementsInArray 

```C++
inline void SR_UTILS_NS::ISerializer::SetAllowEmptyElementsInArray (
    const bool value
) noexcept
```




<hr>



### function SetEditorAllowed 

```C++
inline void SR_UTILS_NS::ISerializer::SetEditorAllowed (
    const bool value
) noexcept
```




<hr>



### function SetWriteDefaults 

```C++
inline void SR_UTILS_NS::ISerializer::SetWriteDefaults (
    const bool value
) noexcept
```




<hr>



### function SetWriteVersion 

```C++
inline void SR_UTILS_NS::ISerializer::SetWriteVersion (
    const bool value
) noexcept
```




<hr>



### function ToString 

```C++
inline virtual SR_NODISCARD std::string SR_UTILS_NS::ISerializer::ToString () noexcept const
```




<hr>



### function WriteAny 

```C++
void SR_UTILS_NS::ISerializer::WriteAny (
    const std::any & value,
    const SerializationId & name
) 
```




<hr>



### function WriteBool 

```C++
virtual void SR_UTILS_NS::ISerializer::WriteBool (
    bool value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteDouble 

```C++
virtual void SR_UTILS_NS::ISerializer::WriteDouble (
    double_t value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteFloat 

```C++
virtual void SR_UTILS_NS::ISerializer::WriteFloat (
    float_t value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteInt [1/4]

```C++
virtual void SR_UTILS_NS::ISerializer::WriteInt (
    int8_t value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteInt [2/4]

```C++
virtual void SR_UTILS_NS::ISerializer::WriteInt (
    int16_t value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteInt [3/4]

```C++
virtual void SR_UTILS_NS::ISerializer::WriteInt (
    int32_t value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteInt [4/4]

```C++
virtual void SR_UTILS_NS::ISerializer::WriteInt (
    int64_t value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteString [1/2]

```C++
virtual void SR_UTILS_NS::ISerializer::WriteString (
    std::string_view value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteString [2/2]

```C++
virtual void SR_UTILS_NS::ISerializer::WriteString (
    std::u32string_view value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteUInt [1/4]

```C++
virtual void SR_UTILS_NS::ISerializer::WriteUInt (
    uint8_t value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteUInt [2/4]

```C++
virtual void SR_UTILS_NS::ISerializer::WriteUInt (
    uint16_t value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteUInt [3/4]

```C++
virtual void SR_UTILS_NS::ISerializer::WriteUInt (
    uint32_t value,
    const SerializationId & name
) = 0
```




<hr>



### function WriteUInt [4/4]

```C++
virtual void SR_UTILS_NS::ISerializer::WriteUInt (
    uint64_t value,
    const SerializationId & name
) = 0
```




<hr>



### function ~ISerializer 

```C++
virtual SR_UTILS_NS::ISerializer::~ISerializer () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/Serializer.h`

