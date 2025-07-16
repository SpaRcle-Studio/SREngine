

# Class SR\_UTILS\_NS::SRASerializer



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SRASerializer**](classSR__UTILS__NS_1_1SRASerializer.md)








Inherits the following classes: [SR\_UTILS\_NS::IBaseSerializer](classSR__UTILS__NS_1_1IBaseSerializer.md),  [SR\_UTILS\_NS::SRAISerialization](classSR__UTILS__NS_1_1SRAISerialization.md)


















## Public Types inherited from SR_UTILS_NS::ISerializer

See [SR\_UTILS\_NS::ISerializer](classSR__UTILS__NS_1_1ISerializer.md)

| Type | Name |
| ---: | :--- |
| typedef std::unique\_ptr&lt; [**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) &gt; | [**UniquePtr**](classSR__UTILS__NS_1_1ISerializer.md#typedef-uniqueptr)  <br> |
































































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD std::unique\_ptr&lt; [**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &gt; | [**CreateDeserializer**](#function-createdeserializer) () override const<br> |
|   | [**SRASerializer**](#function-sraserializer) () <br> |


## Public Functions inherited from SR_UTILS_NS::IBaseSerializer

See [SR\_UTILS\_NS::IBaseSerializer](classSR__UTILS__NS_1_1IBaseSerializer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginArray**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-beginarray) (uint64\_t size, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) override<br> |
| virtual void | [**BeginItem**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-beginitem) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) override<br> |
| virtual void | [**BeginObject**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-beginobject) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) override<br> |
| virtual void | [**EndArray**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-endarray) () override<br> |
| virtual void | [**EndItem**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-enditem) () override<br> |
| virtual void | [**EndObject**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-endobject) () override<br> |
| virtual SR\_NODISCARD bool | [**SaveToFile**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-savetofile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) override const<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-tostring) () noexcept override const<br> |
| virtual void | [**WriteBool**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writebool) (bool value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteDouble**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writedouble) (double\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteFloat**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writefloat) (float\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteInt**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writeint-14) (int8\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteInt**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writeint-24) (int16\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteInt**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writeint-34) (int32\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteInt**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writeint-44) (int64\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteString**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writestring-12) (std::string\_view value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteString**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writestring-22) (std::u32string\_view value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteUInt**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writeuint-14) (uint8\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteUInt**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writeuint-24) (uint16\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteUInt**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writeuint-34) (uint32\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |
| virtual void | [**WriteUInt**](classSR__UTILS__NS_1_1IBaseSerializer.md#function-writeuint-44) (uint64\_t value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & name) override<br> |


## Public Functions inherited from SR_UTILS_NS::ISerializer

See [SR\_UTILS\_NS::ISerializer](classSR__UTILS__NS_1_1ISerializer.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddDontSaveTag**](classSR__UTILS__NS_1_1ISerializer.md#function-adddontsavetag) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & tag) <br> |
| virtual void | [**BeginArray**](classSR__UTILS__NS_1_1ISerializer.md#function-beginarray) (uint64\_t size, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual void | [**BeginItem**](classSR__UTILS__NS_1_1ISerializer.md#function-beginitem) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
| virtual void | [**BeginObject**](classSR__UTILS__NS_1_1ISerializer.md#function-beginobject) (const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) = 0<br> |
|  SR\_NODISCARD bool | [**CanSaveByTags**](classSR__UTILS__NS_1_1ISerializer.md#function-cansavebytags) (const std::set&lt; [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & tags) const<br> |
| virtual SR\_NODISCARD std::unique\_ptr&lt; [**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &gt; | [**CreateDeserializer**](classSR__UTILS__NS_1_1ISerializer.md#function-createdeserializer) () const = 0<br> |
| virtual void | [**EndArray**](classSR__UTILS__NS_1_1ISerializer.md#function-endarray) () = 0<br> |
| virtual void | [**EndItem**](classSR__UTILS__NS_1_1ISerializer.md#function-enditem) () = 0<br> |
| virtual void | [**EndObject**](classSR__UTILS__NS_1_1ISerializer.md#function-endobject) () = 0<br> |
|  SR\_NODISCARD const std::set&lt; [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & | [**GetDontSaveTags**](classSR__UTILS__NS_1_1ISerializer.md#function-getdontsavetags) () noexcept const<br> |
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
|   | [**IBaseSerialization**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-ibaseserialization) () <br> |
| virtual SR\_NODISCARD std::string | [**ToStringBase**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-tostringbase) () noexcept const = 0<br> |
|  void | [**WriteNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-writenode) (const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & node) noexcept<br> |








































## Protected Attributes inherited from SR_UTILS_NS::IBaseSerialization

See [SR\_UTILS\_NS::IBaseSerialization](classSR__UTILS__NS_1_1IBaseSerialization.md)

| Type | Name |
| ---: | :--- |
|  [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) | [**m\_root**](classSR__UTILS__NS_1_1IBaseSerialization.md#variable-m_root)  <br> |
|  [**SR\_HTYPES\_NS::FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md)&lt; [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) \* &gt; | [**m\_stack**](classSR__UTILS__NS_1_1IBaseSerialization.md#variable-m_stack)  <br> |
|  [**SR\_HTYPES\_NS::FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md)&lt; [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) \* &gt; | [**m\_walker**](classSR__UTILS__NS_1_1IBaseSerialization.md#variable-m_walker)  <br> |
















































































## Protected Functions inherited from SR_UTILS_NS::IBaseSerialization

See [SR\_UTILS\_NS::IBaseSerialization](classSR__UTILS__NS_1_1IBaseSerialization.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**IsAllowEmptyElementsInArrayImpl**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-isallowemptyelementsinarrayimpl) () noexcept const<br> |
|  SR\_NODISCARD bool | [**SaveToFileImpl**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-savetofileimpl) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |












## Public Functions Documentation




### function CreateDeserializer 

```C++
virtual SR_NODISCARD std::unique_ptr< IDeserializer > SR_UTILS_NS::SRASerializer::CreateDeserializer () override const
```



Implements [*SR\_UTILS\_NS::ISerializer::CreateDeserializer*](classSR__UTILS__NS_1_1ISerializer.md#function-createdeserializer)


<hr>



### function SRASerializer 

```C++
SR_UTILS_NS::SRASerializer::SRASerializer () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/SRASerialization.h`

