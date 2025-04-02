

# Class SR\_UTILS\_NS::IBaseDeserializer



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**IBaseDeserializer**](classSR__UTILS__NS_1_1IBaseDeserializer.md)








Inherits the following classes: [SR\_UTILS\_NS::IDeserializer](classSR__UTILS__NS_1_1IDeserializer.md)


Inherited by the following classes: [SR\_UTILS\_NS::SRADeserializer](classSR__UTILS__NS_1_1SRADeserializer.md)














## Public Types inherited from SR_UTILS_NS::IDeserializer

See [SR\_UTILS\_NS::IDeserializer](classSR__UTILS__NS_1_1IDeserializer.md)

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**ReAllocPointerReason**](classSR__UTILS__NS_1_1IDeserializer.md#enum-reallocpointerreason)  <br>_Если обнаружена проблема при загрузке указателя, то нужно его пересоздать_  |
| typedef std::unique\_ptr&lt; [**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &gt; | [**UniquePtr**](classSR__UTILS__NS_1_1IDeserializer.md#typedef-uniqueptr)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual uint64\_t | [**BeginArray**](#function-beginarray) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) override<br> |
| virtual bool | [**BeginItem**](#function-beginitem) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id, uint32\_t index) override<br> |
| virtual bool | [**BeginObject**](#function-beginobject) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) override<br> |
| virtual void | [**EndArray**](#function-endarray) () override<br> |
| virtual void | [**EndItem**](#function-enditem) () override<br> |
| virtual void | [**EndObject**](#function-endobject) () override<br> |
| virtual SR\_NODISCARD bool | [**IsDefault**](#function-isdefault) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) noexcept override const<br> |
| virtual void | [**ReadBool**](#function-readbool) (bool & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadDouble**](#function-readdouble) (double\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadFloat**](#function-readfloat) (float\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadInt**](#function-readint-14) (int8\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadInt**](#function-readint-24) (int16\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadInt**](#function-readint-34) (int32\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadInt**](#function-readint-44) (int64\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadString**](#function-readstring-14) (std::string & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadString**](#function-readstring-24) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadString**](#function-readstring-34) ([**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadString**](#function-readstring-44) ([**SR\_HTYPES\_NS::UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadUInt**](#function-readuint-14) (uint8\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadUInt**](#function-readuint-24) (uint16\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadUInt**](#function-readuint-34) (uint32\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadUInt**](#function-readuint-44) (uint64\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ResetWalker**](#function-resetwalker) () override<br> |
| virtual SR\_NODISCARD bool | [**SaveToFile**](#function-savetofile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) override const<br> |


## Public Functions inherited from SR_UTILS_NS::IDeserializer

See [SR\_UTILS\_NS::IDeserializer](classSR__UTILS__NS_1_1IDeserializer.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**AllowNewMapKeys**](classSR__UTILS__NS_1_1IDeserializer.md#function-allownewmapkeys) () noexcept const = 0<br> |
| virtual SR\_NODISCARD bool | [**AllowReAllocPointer**](classSR__UTILS__NS_1_1IDeserializer.md#function-allowreallocpointer) ([**ReAllocPointerReason**](classSR__UTILS__NS_1_1IDeserializer.md#enum-reallocpointerreason) reason) noexcept const = 0<br> |
| virtual uint64\_t | [**BeginArray**](classSR__UTILS__NS_1_1IDeserializer.md#function-beginarray) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual bool | [**BeginItem**](classSR__UTILS__NS_1_1IDeserializer.md#function-beginitem) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id, uint32\_t index) = 0<br> |
| virtual bool | [**BeginObject**](classSR__UTILS__NS_1_1IDeserializer.md#function-beginobject) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual void | [**EndArray**](classSR__UTILS__NS_1_1IDeserializer.md#function-endarray) () = 0<br> |
| virtual void | [**EndItem**](classSR__UTILS__NS_1_1IDeserializer.md#function-enditem) () = 0<br> |
| virtual void | [**EndObject**](classSR__UTILS__NS_1_1IDeserializer.md#function-endobject) () = 0<br> |
| virtual SR\_NODISCARD bool | [**IsDefault**](classSR__UTILS__NS_1_1IDeserializer.md#function-isdefault) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) noexcept const = 0<br> |
| virtual SR\_NODISCARD bool | [**IsPreserveMode**](classSR__UTILS__NS_1_1IDeserializer.md#function-ispreservemode) () noexcept const = 0<br> |
| virtual SR\_NODISCARD bool | [**LoadFromFile**](classSR__UTILS__NS_1_1IDeserializer.md#function-loadfromfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) = 0<br> |
| virtual SR\_NODISCARD bool | [**LoadFromString**](classSR__UTILS__NS_1_1IDeserializer.md#function-loadfromstring) (const std::string & str) = 0<br> |
|  void | [**ReadAny**](classSR__UTILS__NS_1_1IDeserializer.md#function-readany) (std::any & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) <br> |
| virtual void | [**ReadBool**](classSR__UTILS__NS_1_1IDeserializer.md#function-readbool) (bool & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadDouble**](classSR__UTILS__NS_1_1IDeserializer.md#function-readdouble) (double\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadFloat**](classSR__UTILS__NS_1_1IDeserializer.md#function-readfloat) (float\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadInt**](classSR__UTILS__NS_1_1IDeserializer.md#function-readint-14) (int8\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadInt**](classSR__UTILS__NS_1_1IDeserializer.md#function-readint-24) (int16\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadInt**](classSR__UTILS__NS_1_1IDeserializer.md#function-readint-34) (int32\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadInt**](classSR__UTILS__NS_1_1IDeserializer.md#function-readint-44) (int64\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadString**](classSR__UTILS__NS_1_1IDeserializer.md#function-readstring-14) (std::string & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadString**](classSR__UTILS__NS_1_1IDeserializer.md#function-readstring-24) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadString**](classSR__UTILS__NS_1_1IDeserializer.md#function-readstring-34) ([**SR\_HTYPES\_NS::UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadString**](classSR__UTILS__NS_1_1IDeserializer.md#function-readstring-44) ([**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadUInt**](classSR__UTILS__NS_1_1IDeserializer.md#function-readuint-14) (uint8\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadUInt**](classSR__UTILS__NS_1_1IDeserializer.md#function-readuint-24) (uint16\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadUInt**](classSR__UTILS__NS_1_1IDeserializer.md#function-readuint-34) (uint32\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReadUInt**](classSR__UTILS__NS_1_1IDeserializer.md#function-readuint-44) (uint64\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**ReportError**](classSR__UTILS__NS_1_1IDeserializer.md#function-reporterror) (const std::string & message) = 0<br> |
| virtual void | [**ResetWalker**](classSR__UTILS__NS_1_1IDeserializer.md#function-resetwalker) () = 0<br> |
| virtual SR\_NODISCARD bool | [**SaveToFile**](classSR__UTILS__NS_1_1IDeserializer.md#function-savetofile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const = 0<br> |
| virtual SR\_NODISCARD bool | [**ShouldSetDefaults**](classSR__UTILS__NS_1_1IDeserializer.md#function-shouldsetdefaults-12) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) noexcept const = 0<br> |
| virtual SR\_NODISCARD bool | [**ShouldSetDefaults**](classSR__UTILS__NS_1_1IDeserializer.md#function-shouldsetdefaults-22) () noexcept const = 0<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](classSR__UTILS__NS_1_1IDeserializer.md#function-tostring) () noexcept const<br> |
| virtual  | [**~IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md#function-ideserializer) () = default<br> |






















































## Public Functions Documentation




### function BeginArray 

```C++
virtual uint64_t SR_UTILS_NS::IBaseDeserializer::BeginArray (
    const SerializationId & id
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::BeginArray*](classSR__UTILS__NS_1_1IDeserializer.md#function-beginarray)


<hr>



### function BeginItem 

```C++
virtual bool SR_UTILS_NS::IBaseDeserializer::BeginItem (
    const SerializationId & id,
    uint32_t index
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::BeginItem*](classSR__UTILS__NS_1_1IDeserializer.md#function-beginitem)


<hr>



### function BeginObject 

```C++
virtual bool SR_UTILS_NS::IBaseDeserializer::BeginObject (
    const SerializationId & id
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::BeginObject*](classSR__UTILS__NS_1_1IDeserializer.md#function-beginobject)


<hr>



### function EndArray 

```C++
virtual void SR_UTILS_NS::IBaseDeserializer::EndArray () override
```



Implements [*SR\_UTILS\_NS::IDeserializer::EndArray*](classSR__UTILS__NS_1_1IDeserializer.md#function-endarray)


<hr>



### function EndItem 

```C++
virtual void SR_UTILS_NS::IBaseDeserializer::EndItem () override
```



Implements [*SR\_UTILS\_NS::IDeserializer::EndItem*](classSR__UTILS__NS_1_1IDeserializer.md#function-enditem)


<hr>



### function EndObject 

```C++
virtual void SR_UTILS_NS::IBaseDeserializer::EndObject () override
```



Implements [*SR\_UTILS\_NS::IDeserializer::EndObject*](classSR__UTILS__NS_1_1IDeserializer.md#function-endobject)


<hr>



### function IsDefault 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::IBaseDeserializer::IsDefault (
    const SerializationId & name
) noexcept override const
```



Implements [*SR\_UTILS\_NS::IDeserializer::IsDefault*](classSR__UTILS__NS_1_1IDeserializer.md#function-isdefault)


<hr>



### function ReadBool 

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadBool (
    bool & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadBool*](classSR__UTILS__NS_1_1IDeserializer.md#function-readbool)


<hr>



### function ReadDouble 

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadDouble (
    double_t & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadDouble*](classSR__UTILS__NS_1_1IDeserializer.md#function-readdouble)


<hr>



### function ReadFloat 

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadFloat (
    float_t & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadFloat*](classSR__UTILS__NS_1_1IDeserializer.md#function-readfloat)


<hr>



### function ReadInt [1/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadInt (
    int8_t & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadInt*](classSR__UTILS__NS_1_1IDeserializer.md#function-readint-14)


<hr>



### function ReadInt [2/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadInt (
    int16_t & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadInt*](classSR__UTILS__NS_1_1IDeserializer.md#function-readint-24)


<hr>



### function ReadInt [3/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadInt (
    int32_t & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadInt*](classSR__UTILS__NS_1_1IDeserializer.md#function-readint-34)


<hr>



### function ReadInt [4/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadInt (
    int64_t & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadInt*](classSR__UTILS__NS_1_1IDeserializer.md#function-readint-44)


<hr>



### function ReadString [1/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadString (
    std::string & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadString*](classSR__UTILS__NS_1_1IDeserializer.md#function-readstring-14)


<hr>



### function ReadString [2/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadString (
    SR_UTILS_NS::StringAtom & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadString*](classSR__UTILS__NS_1_1IDeserializer.md#function-readstring-24)


<hr>



### function ReadString [3/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadString (
    SR_UTILS_NS::Path & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadString*](classSR__UTILS__NS_1_1IDeserializer.md#function-readstring-44)


<hr>



### function ReadString [4/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadString (
    SR_HTYPES_NS::UnicodeString & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadString*](classSR__UTILS__NS_1_1IDeserializer.md#function-readstring-34)


<hr>



### function ReadUInt [1/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadUInt (
    uint8_t & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadUInt*](classSR__UTILS__NS_1_1IDeserializer.md#function-readuint-14)


<hr>



### function ReadUInt [2/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadUInt (
    uint16_t & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadUInt*](classSR__UTILS__NS_1_1IDeserializer.md#function-readuint-24)


<hr>



### function ReadUInt [3/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadUInt (
    uint32_t & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadUInt*](classSR__UTILS__NS_1_1IDeserializer.md#function-readuint-34)


<hr>



### function ReadUInt [4/4]

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ReadUInt (
    uint64_t & value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReadUInt*](classSR__UTILS__NS_1_1IDeserializer.md#function-readuint-44)


<hr>



### function ResetWalker 

```C++
inline virtual void SR_UTILS_NS::IBaseDeserializer::ResetWalker () override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ResetWalker*](classSR__UTILS__NS_1_1IDeserializer.md#function-resetwalker)


<hr>



### function SaveToFile 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::IBaseDeserializer::SaveToFile (
    const SR_UTILS_NS::Path & path
) override const
```



Implements [*SR\_UTILS\_NS::IDeserializer::SaveToFile*](classSR__UTILS__NS_1_1IDeserializer.md#function-savetofile)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/BaseSerialization.h`

