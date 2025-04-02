

# Class SR\_UTILS\_NS::IDeserializer



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md)










Inherited by the following classes: [SR\_UTILS\_NS::IBaseDeserializer](classSR__UTILS__NS_1_1IBaseDeserializer.md)












## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**ReAllocPointerReason**](#enum-reallocpointerreason)  <br>_Если обнаружена проблема при загрузке указателя, то нужно его пересоздать_  |
| typedef std::unique\_ptr&lt; [**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &gt; | [**UniquePtr**](#typedef-uniqueptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**AllowNewMapKeys**](#function-allownewmapkeys) () noexcept const = 0<br> |
| virtual SR\_NODISCARD bool | [**AllowReAllocPointer**](#function-allowreallocpointer) ([**ReAllocPointerReason**](classSR__UTILS__NS_1_1IDeserializer.md#enum-reallocpointerreason) reason) noexcept const = 0<br> |
| virtual uint64\_t | [**BeginArray**](#function-beginarray) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual bool | [**BeginItem**](#function-beginitem) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id, uint32\_t index) = 0<br> |
| virtual bool | [**BeginObject**](#function-beginobject) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual void | [**EndArray**](#function-endarray) () = 0<br> |
| virtual void | [**EndItem**](#function-enditem) () = 0<br> |
| virtual void | [**EndObject**](#function-endobject) () = 0<br> |
| virtual SR\_NODISCARD bool | [**IsDefault**](#function-isdefault) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) noexcept const = 0<br> |
| virtual SR\_NODISCARD bool | [**IsPreserveMode**](#function-ispreservemode) () noexcept const = 0<br> |
| virtual SR\_NODISCARD bool | [**LoadFromFile**](#function-loadfromfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) = 0<br> |
| virtual SR\_NODISCARD bool | [**LoadFromString**](#function-loadfromstring) (const std::string & str) = 0<br> |
|  void | [**ReadAny**](#function-readany) (std::any & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) <br> |
| virtual void | [**ReadBool**](#function-readbool) (bool & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadDouble**](#function-readdouble) (double\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadFloat**](#function-readfloat) (float\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadInt**](#function-readint-14) (int8\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadInt**](#function-readint-24) (int16\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadInt**](#function-readint-34) (int32\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadInt**](#function-readint-44) (int64\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadString**](#function-readstring-14) (std::string & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadString**](#function-readstring-24) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadString**](#function-readstring-34) ([**SR\_HTYPES\_NS::UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadString**](#function-readstring-44) ([**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadUInt**](#function-readuint-14) (uint8\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadUInt**](#function-readuint-24) (uint16\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadUInt**](#function-readuint-34) (uint32\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadUInt**](#function-readuint-44) (uint64\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReportError**](#function-reporterror) (const std::string & message) = 0<br> |
| virtual void | [**ResetWalker**](#function-resetwalker) () = 0<br> |
| virtual SR\_NODISCARD bool | [**SaveToFile**](#function-savetofile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const = 0<br> |
| virtual SR\_NODISCARD bool | [**ShouldSetDefaults**](#function-shouldsetdefaults-12) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) noexcept const = 0<br> |
| virtual SR\_NODISCARD bool | [**ShouldSetDefaults**](#function-shouldsetdefaults-22) () noexcept const = 0<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](#function-tostring) () noexcept const<br> |
| virtual  | [**~IDeserializer**](#function-ideserializer) () = default<br> |




























## Public Types Documentation




### enum ReAllocPointerReason 

_Если обнаружена проблема при загрузке указателя, то нужно его пересоздать_ 
```C++
enum SR_UTILS_NS::IDeserializer::ReAllocPointerReason {
    None,
    IsNull,
    HasDifferentType
};
```




<hr>



### typedef UniquePtr 

```C++
using SR_UTILS_NS::IDeserializer::UniquePtr =  std::unique_ptr<IDeserializer>;
```




<hr>
## Public Functions Documentation




### function AllowNewMapKeys 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IDeserializer::AllowNewMapKeys () noexcept const = 0
```




<hr>



### function AllowReAllocPointer 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IDeserializer::AllowReAllocPointer (
    ReAllocPointerReason reason
) noexcept const = 0
```




<hr>



### function BeginArray 

```C++
virtual uint64_t SR_UTILS_NS::IDeserializer::BeginArray (
    const SerializationId & id
) = 0
```




<hr>



### function BeginItem 

```C++
virtual bool SR_UTILS_NS::IDeserializer::BeginItem (
    const SerializationId & id,
    uint32_t index
) = 0
```




<hr>



### function BeginObject 

```C++
virtual bool SR_UTILS_NS::IDeserializer::BeginObject (
    const SerializationId & id
) = 0
```




<hr>



### function EndArray 

```C++
virtual void SR_UTILS_NS::IDeserializer::EndArray () = 0
```




<hr>



### function EndItem 

```C++
virtual void SR_UTILS_NS::IDeserializer::EndItem () = 0
```




<hr>



### function EndObject 

```C++
virtual void SR_UTILS_NS::IDeserializer::EndObject () = 0
```




<hr>



### function IsDefault 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IDeserializer::IsDefault (
    const SerializationId & name
) noexcept const = 0
```




<hr>



### function IsPreserveMode 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IDeserializer::IsPreserveMode () noexcept const = 0
```




<hr>



### function LoadFromFile 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IDeserializer::LoadFromFile (
    const SR_UTILS_NS::Path & path
) = 0
```




<hr>



### function LoadFromString 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IDeserializer::LoadFromString (
    const std::string & str
) = 0
```




<hr>



### function ReadAny 

```C++
void SR_UTILS_NS::IDeserializer::ReadAny (
    std::any & value,
    const SerializationId & name
) 
```




<hr>



### function ReadBool 

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadBool (
    bool & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadDouble 

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadDouble (
    double_t & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadFloat 

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadFloat (
    float_t & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadInt [1/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadInt (
    int8_t & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadInt [2/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadInt (
    int16_t & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadInt [3/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadInt (
    int32_t & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadInt [4/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadInt (
    int64_t & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadString [1/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadString (
    std::string & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadString [2/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadString (
    SR_UTILS_NS::StringAtom & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadString [3/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadString (
    SR_HTYPES_NS::UnicodeString & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadString [4/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadString (
    SR_UTILS_NS::Path & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadUInt [1/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadUInt (
    uint8_t & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadUInt [2/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadUInt (
    uint16_t & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadUInt [3/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadUInt (
    uint32_t & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReadUInt [4/4]

```C++
virtual void SR_UTILS_NS::IDeserializer::ReadUInt (
    uint64_t & value,
    const SerializationId & name
) = 0
```




<hr>



### function ReportError 

```C++
virtual void SR_UTILS_NS::IDeserializer::ReportError (
    const std::string & message
) = 0
```




<hr>



### function ResetWalker 

```C++
virtual void SR_UTILS_NS::IDeserializer::ResetWalker () = 0
```




<hr>



### function SaveToFile 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IDeserializer::SaveToFile (
    const SR_UTILS_NS::Path & path
) const = 0
```




<hr>



### function ShouldSetDefaults [1/2]

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IDeserializer::ShouldSetDefaults (
    const SerializationId & name
) noexcept const = 0
```




<hr>



### function ShouldSetDefaults [2/2]

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IDeserializer::ShouldSetDefaults () noexcept const = 0
```




<hr>



### function ToString 

```C++
inline virtual SR_NODISCARD std::string SR_UTILS_NS::IDeserializer::ToString () noexcept const
```




<hr>



### function ~IDeserializer 

```C++
virtual SR_UTILS_NS::IDeserializer::~IDeserializer () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/Deserializer.h`

