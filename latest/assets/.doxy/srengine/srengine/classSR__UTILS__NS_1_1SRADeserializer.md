

# Class SR\_UTILS\_NS::SRADeserializer



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SRADeserializer**](classSR__UTILS__NS_1_1SRADeserializer.md)








Inherits the following classes: [SR\_UTILS\_NS::IBaseDeserializer](classSR__UTILS__NS_1_1IBaseDeserializer.md),  [SR\_UTILS\_NS::SRAISerialization](classSR__UTILS__NS_1_1SRAISerialization.md)


















## Public Types inherited from SR_UTILS_NS::IDeserializer

See [SR\_UTILS\_NS::IDeserializer](classSR__UTILS__NS_1_1IDeserializer.md)

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**ReAllocPointerReason**](classSR__UTILS__NS_1_1IDeserializer.md#enum-reallocpointerreason)  <br>_Если обнаружена проблема при загрузке указателя, то нужно его пересоздать_  |
| typedef std::unique\_ptr&lt; [**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &gt; | [**UniquePtr**](classSR__UTILS__NS_1_1IDeserializer.md#typedef-uniqueptr)  <br> |
































































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**AllowNewMapKeys**](#function-allownewmapkeys) () noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**AllowReAllocPointer**](#function-allowreallocpointer) ([**ReAllocPointerReason**](classSR__UTILS__NS_1_1IDeserializer.md#enum-reallocpointerreason) reason) noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**IsPreserveMode**](#function-ispreservemode) () noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**LoadFromFile**](#function-loadfromfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) override<br> |
| virtual SR\_NODISCARD bool | [**LoadFromString**](#function-loadfromstring) (const std::string & str) override<br> |
| virtual void | [**ReportError**](#function-reporterror) (const std::string & message) override<br> |
| virtual SR\_NODISCARD bool | [**ShouldSetDefaults**](#function-shouldsetdefaults-12) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**ShouldSetDefaults**](#function-shouldsetdefaults-22) () noexcept override const<br> |


## Public Functions inherited from SR_UTILS_NS::IBaseDeserializer

See [SR\_UTILS\_NS::IBaseDeserializer](classSR__UTILS__NS_1_1IBaseDeserializer.md)

| Type | Name |
| ---: | :--- |
| virtual uint64\_t | [**BeginArray**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-beginarray) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) override<br> |
| virtual bool | [**BeginItem**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-beginitem) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id, uint32\_t index) override<br> |
| virtual bool | [**BeginObject**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-beginobject) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) override<br> |
| virtual void | [**EndArray**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-endarray) () override<br> |
| virtual void | [**EndItem**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-enditem) () override<br> |
| virtual void | [**EndObject**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-endobject) () override<br> |
| virtual SR\_NODISCARD bool | [**IsDefault**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-isdefault) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) noexcept override const<br> |
| virtual void | [**ReadBool**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readbool) (bool & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadDouble**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readdouble) (double\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadFloat**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readfloat) (float\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadInt**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readint-14) (int8\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadInt**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readint-24) (int16\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadInt**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readint-34) (int32\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadInt**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readint-44) (int64\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadString**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readstring-14) (std::string & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadString**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readstring-24) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadString**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readstring-34) ([**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadString**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readstring-44) ([**SR\_HTYPES\_NS::UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadUInt**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readuint-14) (uint8\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadUInt**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readuint-24) (uint16\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadUInt**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readuint-34) (uint32\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ReadUInt**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-readuint-44) (uint64\_t & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**ResetWalker**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-resetwalker) () override<br> |
| virtual SR\_NODISCARD bool | [**SaveToFile**](classSR__UTILS__NS_1_1IBaseDeserializer.md#function-savetofile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) override const<br> |


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


## Public Functions inherited from SR_UTILS_NS::SRAISerialization

See [SR\_UTILS\_NS::SRAISerialization](classSR__UTILS__NS_1_1SRAISerialization.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**IsNeedUseTabs**](classSR__UTILS__NS_1_1SRAISerialization.md#function-isneedusetabs) () noexcept const<br> |
|  void | [**SetUseTabs**](classSR__UTILS__NS_1_1SRAISerialization.md#function-setusetabs) (const bool value) noexcept<br> |
| virtual SR\_NODISCARD std::string | [**ToStringBase**](classSR__UTILS__NS_1_1SRAISerialization.md#function-tostringbase) () noexcept override const<br> |


## Public Functions inherited from SR_UTILS_NS::IBaseSerialization

See [SR\_UTILS\_NS::IBaseSerialization](classSR__UTILS__NS_1_1IBaseSerialization.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetCurrentNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getcurrentnode-12) () noexcept<br> |
|  SR\_NODISCARD const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetCurrentNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getcurrentnode-22) () noexcept const<br> |
|  SR\_NODISCARD [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetWalkNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getwalknode-12) () noexcept<br> |
|  SR\_NODISCARD const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetWalkNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getwalknode-22) () noexcept const<br> |
| virtual SR\_NODISCARD std::string | [**ToStringBase**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-tostringbase) () noexcept const = 0<br> |








































## Protected Attributes inherited from SR_UTILS_NS::IBaseSerialization

See [SR\_UTILS\_NS::IBaseSerialization](classSR__UTILS__NS_1_1IBaseSerialization.md)

| Type | Name |
| ---: | :--- |
|  [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) | [**m\_root**](classSR__UTILS__NS_1_1IBaseSerialization.md#variable-m_root)  <br> |
|  std::vector&lt; uint64\_t &gt; | [**m\_stack**](classSR__UTILS__NS_1_1IBaseSerialization.md#variable-m_stack)  <br> |
|  std::vector&lt; uint64\_t &gt; | [**m\_walker**](classSR__UTILS__NS_1_1IBaseSerialization.md#variable-m_walker)  <br> |
















































































## Protected Functions inherited from SR_UTILS_NS::IBaseSerialization

See [SR\_UTILS\_NS::IBaseSerialization](classSR__UTILS__NS_1_1IBaseSerialization.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getnode-12) (const std::vector&lt; uint64\_t &gt; & stack) noexcept<br> |
|  SR\_NODISCARD const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getnode-22) (const std::vector&lt; uint64\_t &gt; & stack) noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsAllowEmptyElementsInArrayImpl**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-isallowemptyelementsinarrayimpl) () noexcept const<br> |
|  SR\_NODISCARD bool | [**SaveToFileImpl**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-savetofileimpl) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |












## Public Functions Documentation




### function AllowNewMapKeys 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::SRADeserializer::AllowNewMapKeys () noexcept override const
```



Implements [*SR\_UTILS\_NS::IDeserializer::AllowNewMapKeys*](classSR__UTILS__NS_1_1IDeserializer.md#function-allownewmapkeys)


<hr>



### function AllowReAllocPointer 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::SRADeserializer::AllowReAllocPointer (
    ReAllocPointerReason reason
) noexcept override const
```



Implements [*SR\_UTILS\_NS::IDeserializer::AllowReAllocPointer*](classSR__UTILS__NS_1_1IDeserializer.md#function-allowreallocpointer)


<hr>



### function IsPreserveMode 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::SRADeserializer::IsPreserveMode () noexcept override const
```



Implements [*SR\_UTILS\_NS::IDeserializer::IsPreserveMode*](classSR__UTILS__NS_1_1IDeserializer.md#function-ispreservemode)


<hr>



### function LoadFromFile 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::SRADeserializer::LoadFromFile (
    const SR_UTILS_NS::Path & path
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::LoadFromFile*](classSR__UTILS__NS_1_1IDeserializer.md#function-loadfromfile)


<hr>



### function LoadFromString 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::SRADeserializer::LoadFromString (
    const std::string & str
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::LoadFromString*](classSR__UTILS__NS_1_1IDeserializer.md#function-loadfromstring)


<hr>



### function ReportError 

```C++
virtual void SR_UTILS_NS::SRADeserializer::ReportError (
    const std::string & message
) override
```



Implements [*SR\_UTILS\_NS::IDeserializer::ReportError*](classSR__UTILS__NS_1_1IDeserializer.md#function-reporterror)


<hr>



### function ShouldSetDefaults [1/2]

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::SRADeserializer::ShouldSetDefaults (
    const SerializationId & name
) noexcept override const
```



Implements [*SR\_UTILS\_NS::IDeserializer::ShouldSetDefaults*](classSR__UTILS__NS_1_1IDeserializer.md#function-shouldsetdefaults-12)


<hr>



### function ShouldSetDefaults [2/2]

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::SRADeserializer::ShouldSetDefaults () noexcept override const
```



Implements [*SR\_UTILS\_NS::IDeserializer::ShouldSetDefaults*](classSR__UTILS__NS_1_1IDeserializer.md#function-shouldsetdefaults-22)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/SRASerialization.h`

