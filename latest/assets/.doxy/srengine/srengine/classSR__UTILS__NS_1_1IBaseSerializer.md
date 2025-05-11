

# Class SR\_UTILS\_NS::IBaseSerializer



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**IBaseSerializer**](classSR__UTILS__NS_1_1IBaseSerializer.md)








Inherits the following classes: [SR\_UTILS\_NS::ISerializer](classSR__UTILS__NS_1_1ISerializer.md)


Inherited by the following classes: [SR\_UTILS\_NS::SRASerializer](classSR__UTILS__NS_1_1SRASerializer.md)














## Public Types inherited from SR_UTILS_NS::ISerializer

See [SR\_UTILS\_NS::ISerializer](classSR__UTILS__NS_1_1ISerializer.md)

| Type | Name |
| ---: | :--- |
| typedef std::unique\_ptr&lt; [**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) &gt; | [**UniquePtr**](classSR__UTILS__NS_1_1ISerializer.md#typedef-uniqueptr)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginArray**](#function-beginarray) (uint64\_t size, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) override<br> |
| virtual void | [**BeginItem**](#function-beginitem) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) override<br> |
| virtual void | [**BeginObject**](#function-beginobject) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) override<br> |
| virtual void | [**EndArray**](#function-endarray) () override<br> |
| virtual void | [**EndItem**](#function-enditem) () override<br> |
| virtual void | [**EndObject**](#function-endobject) () override<br> |
| virtual SR\_NODISCARD bool | [**SaveToFile**](#function-savetofile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) override const<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](#function-tostring) () noexcept override const<br> |
| virtual void | [**WriteBool**](#function-writebool) (bool value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteDouble**](#function-writedouble) (double\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteFloat**](#function-writefloat) (float\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteInt**](#function-writeint-14) (int8\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteInt**](#function-writeint-24) (int16\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteInt**](#function-writeint-34) (int32\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteInt**](#function-writeint-44) (int64\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteString**](#function-writestring-12) (std::string\_view value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteString**](#function-writestring-22) (std::u32string\_view value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteUInt**](#function-writeuint-14) (uint8\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteUInt**](#function-writeuint-24) (uint16\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteUInt**](#function-writeuint-34) (uint32\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteUInt**](#function-writeuint-44) (uint64\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |


## Public Functions inherited from SR_UTILS_NS::ISerializer

See [SR\_UTILS\_NS::ISerializer](classSR__UTILS__NS_1_1ISerializer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginArray**](classSR__UTILS__NS_1_1ISerializer.md#function-beginarray) (uint64\_t size, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual void | [**BeginItem**](classSR__UTILS__NS_1_1ISerializer.md#function-beginitem) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual void | [**BeginObject**](classSR__UTILS__NS_1_1ISerializer.md#function-beginobject) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual SR\_NODISCARD std::unique\_ptr&lt; [**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &gt; | [**CreateDeserializer**](classSR__UTILS__NS_1_1ISerializer.md#function-createdeserializer) () const = 0<br> |
| virtual void | [**EndArray**](classSR__UTILS__NS_1_1ISerializer.md#function-endarray) () = 0<br> |
| virtual void | [**EndItem**](classSR__UTILS__NS_1_1ISerializer.md#function-enditem) () = 0<br> |
| virtual void | [**EndObject**](classSR__UTILS__NS_1_1ISerializer.md#function-endobject) () = 0<br> |
| virtual SR\_NODISCARD bool | [**IsAllowEmptyElementsInArray**](classSR__UTILS__NS_1_1ISerializer.md#function-isallowemptyelementsinarray) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsEditorAllowed**](classSR__UTILS__NS_1_1ISerializer.md#function-iseditorallowed) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsWriteDefaults**](classSR__UTILS__NS_1_1ISerializer.md#function-iswritedefaults) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsWriteVersion**](classSR__UTILS__NS_1_1ISerializer.md#function-iswriteversion) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**SaveToFile**](classSR__UTILS__NS_1_1ISerializer.md#function-savetofile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |
|  void | [**SetAllowEmptyElementsInArray**](classSR__UTILS__NS_1_1ISerializer.md#function-setallowemptyelementsinarray) (const bool value) noexcept<br> |
|  void | [**SetEditorAllowed**](classSR__UTILS__NS_1_1ISerializer.md#function-seteditorallowed) (const bool value) noexcept<br> |
|  void | [**SetWriteDefaults**](classSR__UTILS__NS_1_1ISerializer.md#function-setwritedefaults) (const bool value) noexcept<br> |
|  void | [**SetWriteVersion**](classSR__UTILS__NS_1_1ISerializer.md#function-setwriteversion) (const bool value) noexcept<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](classSR__UTILS__NS_1_1ISerializer.md#function-tostring) () noexcept const<br> |
|  void | [**WriteAny**](classSR__UTILS__NS_1_1ISerializer.md#function-writeany) (const std::any & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) <br> |
| virtual void | [**WriteBool**](classSR__UTILS__NS_1_1ISerializer.md#function-writebool) (bool value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteDouble**](classSR__UTILS__NS_1_1ISerializer.md#function-writedouble) (double\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteFloat**](classSR__UTILS__NS_1_1ISerializer.md#function-writefloat) (float\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteInt**](classSR__UTILS__NS_1_1ISerializer.md#function-writeint-14) (int8\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteInt**](classSR__UTILS__NS_1_1ISerializer.md#function-writeint-24) (int16\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteInt**](classSR__UTILS__NS_1_1ISerializer.md#function-writeint-34) (int32\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteInt**](classSR__UTILS__NS_1_1ISerializer.md#function-writeint-44) (int64\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteString**](classSR__UTILS__NS_1_1ISerializer.md#function-writestring-12) (std::string\_view value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteString**](classSR__UTILS__NS_1_1ISerializer.md#function-writestring-22) (std::u32string\_view value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteUInt**](classSR__UTILS__NS_1_1ISerializer.md#function-writeuint-14) (uint8\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteUInt**](classSR__UTILS__NS_1_1ISerializer.md#function-writeuint-24) (uint16\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteUInt**](classSR__UTILS__NS_1_1ISerializer.md#function-writeuint-34) (uint32\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual void | [**WriteUInt**](classSR__UTILS__NS_1_1ISerializer.md#function-writeuint-44) (uint64\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) = 0<br> |
| virtual  | [**~ISerializer**](classSR__UTILS__NS_1_1ISerializer.md#function-iserializer) () = default<br> |






















































## Public Functions Documentation




### function BeginArray 

```C++
virtual void SR_UTILS_NS::IBaseSerializer::BeginArray (
    uint64_t size,
    const SerializationId & id
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::BeginArray*](classSR__UTILS__NS_1_1ISerializer.md#function-beginarray)


<hr>



### function BeginItem 

```C++
virtual void SR_UTILS_NS::IBaseSerializer::BeginItem (
    const SerializationId & id
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::BeginItem*](classSR__UTILS__NS_1_1ISerializer.md#function-beginitem)


<hr>



### function BeginObject 

```C++
virtual void SR_UTILS_NS::IBaseSerializer::BeginObject (
    const SerializationId & id
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::BeginObject*](classSR__UTILS__NS_1_1ISerializer.md#function-beginobject)


<hr>



### function EndArray 

```C++
virtual void SR_UTILS_NS::IBaseSerializer::EndArray () override
```



Implements [*SR\_UTILS\_NS::ISerializer::EndArray*](classSR__UTILS__NS_1_1ISerializer.md#function-endarray)


<hr>



### function EndItem 

```C++
virtual void SR_UTILS_NS::IBaseSerializer::EndItem () override
```



Implements [*SR\_UTILS\_NS::ISerializer::EndItem*](classSR__UTILS__NS_1_1ISerializer.md#function-enditem)


<hr>



### function EndObject 

```C++
virtual void SR_UTILS_NS::IBaseSerializer::EndObject () override
```



Implements [*SR\_UTILS\_NS::ISerializer::EndObject*](classSR__UTILS__NS_1_1ISerializer.md#function-endobject)


<hr>



### function SaveToFile 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::IBaseSerializer::SaveToFile (
    const SR_UTILS_NS::Path & path
) override const
```



Implements [*SR\_UTILS\_NS::ISerializer::SaveToFile*](classSR__UTILS__NS_1_1ISerializer.md#function-savetofile)


<hr>



### function ToString 

```C++
inline virtual SR_NODISCARD std::string SR_UTILS_NS::IBaseSerializer::ToString () noexcept override const
```



Implements [*SR\_UTILS\_NS::ISerializer::ToString*](classSR__UTILS__NS_1_1ISerializer.md#function-tostring)


<hr>



### function WriteBool 

```C++
virtual void SR_UTILS_NS::IBaseSerializer::WriteBool (
    bool value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteBool*](classSR__UTILS__NS_1_1ISerializer.md#function-writebool)


<hr>



### function WriteDouble 

```C++
virtual void SR_UTILS_NS::IBaseSerializer::WriteDouble (
    double_t value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteDouble*](classSR__UTILS__NS_1_1ISerializer.md#function-writedouble)


<hr>



### function WriteFloat 

```C++
inline virtual void SR_UTILS_NS::IBaseSerializer::WriteFloat (
    float_t value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteFloat*](classSR__UTILS__NS_1_1ISerializer.md#function-writefloat)


<hr>



### function WriteInt [1/4]

```C++
inline virtual void SR_UTILS_NS::IBaseSerializer::WriteInt (
    int8_t value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteInt*](classSR__UTILS__NS_1_1ISerializer.md#function-writeint-14)


<hr>



### function WriteInt [2/4]

```C++
inline virtual void SR_UTILS_NS::IBaseSerializer::WriteInt (
    int16_t value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteInt*](classSR__UTILS__NS_1_1ISerializer.md#function-writeint-24)


<hr>



### function WriteInt [3/4]

```C++
inline virtual void SR_UTILS_NS::IBaseSerializer::WriteInt (
    int32_t value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteInt*](classSR__UTILS__NS_1_1ISerializer.md#function-writeint-34)


<hr>



### function WriteInt [4/4]

```C++
virtual void SR_UTILS_NS::IBaseSerializer::WriteInt (
    int64_t value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteInt*](classSR__UTILS__NS_1_1ISerializer.md#function-writeint-44)


<hr>



### function WriteString [1/2]

```C++
virtual void SR_UTILS_NS::IBaseSerializer::WriteString (
    std::string_view value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteString*](classSR__UTILS__NS_1_1ISerializer.md#function-writestring-12)


<hr>



### function WriteString [2/2]

```C++
virtual void SR_UTILS_NS::IBaseSerializer::WriteString (
    std::u32string_view value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteString*](classSR__UTILS__NS_1_1ISerializer.md#function-writestring-22)


<hr>



### function WriteUInt [1/4]

```C++
inline virtual void SR_UTILS_NS::IBaseSerializer::WriteUInt (
    uint8_t value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteUInt*](classSR__UTILS__NS_1_1ISerializer.md#function-writeuint-14)


<hr>



### function WriteUInt [2/4]

```C++
inline virtual void SR_UTILS_NS::IBaseSerializer::WriteUInt (
    uint16_t value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteUInt*](classSR__UTILS__NS_1_1ISerializer.md#function-writeuint-24)


<hr>



### function WriteUInt [3/4]

```C++
inline virtual void SR_UTILS_NS::IBaseSerializer::WriteUInt (
    uint32_t value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteUInt*](classSR__UTILS__NS_1_1ISerializer.md#function-writeuint-34)


<hr>



### function WriteUInt [4/4]

```C++
inline virtual void SR_UTILS_NS::IBaseSerializer::WriteUInt (
    uint64_t value,
    const SerializationId & name
) override
```



Implements [*SR\_UTILS\_NS::ISerializer::WriteUInt*](classSR__UTILS__NS_1_1ISerializer.md#function-writeuint-44)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/BaseSerialization.h`

