

# Class SR\_GRAPH\_NS::BaseMaterial



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**BaseMaterial**](classSR__GRAPH__NS_1_1BaseMaterial.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md),  [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md),  [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)


Inherited by the following classes: [SR\_GRAPH\_NS::FileMaterial](classSR__GRAPH__NS_1_1FileMaterial.md),  [SR\_GRAPH\_NS::UniqueMaterial](classSR__GRAPH__NS_1_1UniqueMaterial.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**BaseMaterial**](classSR__GRAPH__NS_1_1BaseMaterial.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |






## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |
















































































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**BaseMaterial**](#function-basematerial) () <br> |
|  SR\_NODISCARD RenderContextPtr | [**GetContext**](#function-getcontext) () const<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**GetDefaultShader**](#function-getdefaultshader) () noexcept const<br> |
| virtual SR\_NODISCARD const MaterialData::Ptr & | [**GetMaterialData**](#function-getmaterialdata) () noexcept const = 0<br> |
| virtual SR\_NODISCARD MaterialType | [**GetMaterialType**](#function-getmaterialtype) () noexcept const = 0<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetRenderStageId**](#function-getrenderstageid) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**GetShader**](#function-getshader-12) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id) noexcept const<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**GetShader**](#function-getshader-22) (const [**SR\_SRSL\_NS::ShaderMacrosParams**](structSR__SRSL__NS_1_1ShaderMacrosParams.md) & macros) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () const<br> |
|  void | [**OnPropertyChanged**](#function-onpropertychanged) (bool onlyUniforms) const<br> |
|  void | [**OnShaderChanged**](#function-onshaderchanged) () <br> |
| virtual SR\_NODISCARD uint32\_t | [**RegisterMesh**](#function-registermesh) (MeshPtr pMesh) <br> |
|  void SR\_FASTCALL | [**SetBool**](#function-setbool) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, bool v) noexcept<br> |
|  void SR\_FASTCALL | [**SetColor**](#function-setcolor) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & v) noexcept<br> |
| virtual void | [**SetShader**](#function-setshader-12) (ShaderPtr pShader, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) stage=[**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md)()) <br> |
|  void | [**SetShader**](#function-setshader-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) stage=[**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md)()) <br> |
|  void SR\_FASTCALL | [**SetTexture**](#function-settexture) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Texture**](classSR__GTYPES__NS_1_1Texture.md) &gt; & pTexture) noexcept<br> |
|  void SR\_FASTCALL | [**SetVec4**](#function-setvec4) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const SR\_MATH\_NS::FVector4 & v) noexcept<br> |
| virtual void | [**UnregisterMesh**](#function-unregistermesh) (uint32\_t \* pId) <br> |
|  void | [**Use**](#function-use) () <br> |
|  void | [**UseSamplers**](#function-usesamplers) () <br> |
|   | [**~BaseMaterial**](#function-basematerial) () override<br> |


## Public Functions inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-addserializationflags) (SerializationFlags flags) noexcept<br> |
|  SR\_NODISCARD bool | [**HasSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-hasserializationflags) (SerializationFlags flags) noexcept const<br> |
| virtual bool | [**Load**](classSR__UTILS__NS_1_1Serializable.md#function-load) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer) <br> |
| virtual void | [**OnPostLoad**](classSR__UTILS__NS_1_1Serializable.md#function-onpostload) () <br> |
| virtual void | [**OnPostSave**](classSR__UTILS__NS_1_1Serializable.md#function-onpostsave) () <br> |
| virtual void | [**OnPreLoad**](classSR__UTILS__NS_1_1Serializable.md#function-onpreload) () <br> |
| virtual void | [**OnPreSave**](classSR__UTILS__NS_1_1Serializable.md#function-onpresave) () <br> |
|  void | [**RemoveSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-removeserializationflags) (SerializationFlags flags) noexcept<br> |
| virtual void | [**Save**](classSR__UTILS__NS_1_1Serializable.md#function-save) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer) const<br> |
| virtual void | [**VerifyAfterLoad**](classSR__UTILS__NS_1_1Serializable.md#function-verifyafterload) (SerializableVerifyContext & context) noexcept const<br> |


## Public Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  void | [**CloneTo**](classSR__UTILS__NS_1_1SRClass.md#function-cloneto) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) & clone) const<br> |
| virtual SR\_NODISCARD const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMeta**](classSR__UTILS__NS_1_1SRClass.md#function-getmeta) () noexcept const = 0<br> |
| virtual  | [**~SRClass**](classSR__UTILS__NS_1_1SRClass.md#function-srclass) () = default<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
|  SR\_NODISCARD const void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-12) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br> |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getthis) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-22) () <br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-incrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**PolymorphicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-polymorphiccast) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-recursivelockifvalid) () noexcept const<br> |
|  U | [**ReinterpretCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reinterpretcast) () <br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reset) () override<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtr.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) override<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-15) () = default<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-25) (const T \* constPtr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-35) (const T \* constPtr, SR\_UTILS\_NS::SharedPtrPolicy policy) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-45) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) const & ptr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-55) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) && ptr) noexcept<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**StaticCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-staticcast) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-tryrecursivelockifvalid) () noexcept const<br> |
|  void | [**Unlock**](classSR__HTYPES__NS_1_1SharedPtr.md#function-unlock) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_2) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_3) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_4) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_5) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|   | [**~SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-decrementpointer) () = 0<br> |
|  const [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-12) () const<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getsrclass) () const = 0<br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-incrementpointer) () = 0<br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-reset) () = 0<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) = 0<br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-12) () <br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-22) ([**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* data) <br> |
| virtual SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-valid) () const = 0<br> |
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |






## Public Static Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**AllocateStatic**](classSR__UTILS__NS_1_1SRClass.md#function-allocatestatic) () noexcept<br> |
|  SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](classSR__UTILS__NS_1_1SRClass.md#function-getbasemetas) () noexcept<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetClassStaticName**](classSR__UTILS__NS_1_1SRClass.md#function-getclassstaticname) () noexcept<br> |
|  const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMetaStatic**](classSR__UTILS__NS_1_1SRClass.md#function-getmetastatic) () noexcept<br> |
|  bool | [**RegisterPropertiesCodegen**](classSR__UTILS__NS_1_1SRClass.md#function-registerpropertiescodegen) () <br> |




## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |




## Protected Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](#typedef-meshptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) &gt; | [**RenderContextPtr**](#typedef-rendercontextptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) &gt; | [**ShaderPtr**](#typedef-shaderptr)  <br> |
| typedef [**SR\_GTYPES\_NS::Texture**](classSR__GTYPES__NS_1_1Texture.md) \* | [**TexturePtr**](#typedef-textureptr)  <br> |
























## Protected Attributes

| Type | Name |
| ---: | :--- |
|  RenderContextPtr | [**m\_context**](#variable-m_context)  <br> |
|  [**SR\_HTYPES\_NS::ObjectPool**](classSR__HTYPES__NS_1_1ObjectPool.md)&lt; MeshPtr, uint32\_t &gt; | [**m\_meshes**](#variable-m_meshes)  <br> |
|  [**SR\_UTILS\_NS::Subscription**](classSR__UTILS__NS_1_1Subscription.md) | [**m\_propertyChangedSubscription**](#variable-m_propertychangedsubscription)  <br> |
|  [**SR\_UTILS\_NS::Subscription**](classSR__UTILS__NS_1_1Subscription.md) | [**m\_shaderChangedSubscription**](#variable-m_shaderchangedsubscription)  <br> |
|  std::map&lt; SR\_UTILS\_NS::SRHashType, SR\_GTYPES\_NS::Shader::Ptr &gt; | [**m\_variants**](#variable-m_variants)  <br> |










## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |






















































































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**DeInitMaterialDataSubscriptions**](#function-deinitmaterialdatasubscriptions) () <br> |
| virtual void | [**InitContext**](#function-initcontext) () const<br> |
|  void | [**InitMaterialDataSubscriptions**](#function-initmaterialdatasubscriptions) () <br> |






## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |


















## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_NS::BaseMaterial::Ptr =  SR_HTYPES_NS::SharedPtr<BaseMaterial>;
```




<hr>
## Public Functions Documentation




### function BaseMaterial 

```C++
SR_GRAPH_NS::BaseMaterial::BaseMaterial () 
```




<hr>



### function GetContext 

```C++
inline SR_NODISCARD RenderContextPtr SR_GRAPH_NS::BaseMaterial::GetContext () const
```




<hr>



### function GetDefaultShader 

```C++
SR_NODISCARD SR_GTYPES_NS::Shader * SR_GRAPH_NS::BaseMaterial::GetDefaultShader () noexcept const
```




<hr>



### function GetMaterialData 

```C++
virtual SR_NODISCARD const MaterialData::Ptr & SR_GRAPH_NS::BaseMaterial::GetMaterialData () noexcept const = 0
```




<hr>



### function GetMaterialType 

```C++
virtual SR_NODISCARD MaterialType SR_GRAPH_NS::BaseMaterial::GetMaterialType () noexcept const = 0
```




<hr>



### function GetRenderStageId 

```C++
SR_NODISCARD SR_UTILS_NS::StringAtom SR_GRAPH_NS::BaseMaterial::GetRenderStageId () noexcept const
```




<hr>



### function GetShader [1/2]

```C++
SR_NODISCARD SR_GTYPES_NS::Shader * SR_GRAPH_NS::BaseMaterial::GetShader (
    SR_UTILS_NS::StringAtom id
) noexcept const
```




<hr>



### function GetShader [2/2]

```C++
SR_NODISCARD SR_GTYPES_NS::Shader * SR_GRAPH_NS::BaseMaterial::GetShader (
    const SR_SRSL_NS::ShaderMacrosParams & macros
) noexcept const
```




<hr>



### function IsValid 

```C++
SR_NODISCARD bool SR_GRAPH_NS::BaseMaterial::IsValid () const
```




<hr>



### function OnPropertyChanged 

```C++
void SR_GRAPH_NS::BaseMaterial::OnPropertyChanged (
    bool onlyUniforms
) const
```




<hr>



### function OnShaderChanged 

```C++
void SR_GRAPH_NS::BaseMaterial::OnShaderChanged () 
```




<hr>



### function RegisterMesh 

```C++
virtual SR_NODISCARD uint32_t SR_GRAPH_NS::BaseMaterial::RegisterMesh (
    MeshPtr pMesh
) 
```




<hr>



### function SetBool 

```C++
void SR_FASTCALL SR_GRAPH_NS::BaseMaterial::SetBool (
    SR_UTILS_NS::StringAtom id,
    bool v
) noexcept
```




<hr>



### function SetColor 

```C++
void SR_FASTCALL SR_GRAPH_NS::BaseMaterial::SetColor (
    SR_UTILS_NS::StringAtom id,
    const SR_MATH_NS::FColor & v
) noexcept
```




<hr>



### function SetShader [1/2]

```C++
virtual void SR_GRAPH_NS::BaseMaterial::SetShader (
    ShaderPtr pShader,
    SR_UTILS_NS::StringAtom stage=SR_UTILS_NS::StringAtom ()
) 
```




<hr>



### function SetShader [2/2]

```C++
void SR_GRAPH_NS::BaseMaterial::SetShader (
    const SR_UTILS_NS::Path & path,
    SR_UTILS_NS::StringAtom stage=SR_UTILS_NS::StringAtom ()
) 
```




<hr>



### function SetTexture 

```C++
void SR_FASTCALL SR_GRAPH_NS::BaseMaterial::SetTexture (
    SR_UTILS_NS::StringAtom id,
    const SR_HTYPES_NS::SharedPtr < SR_GTYPES_NS::Texture > & pTexture
) noexcept
```




<hr>



### function SetVec4 

```C++
void SR_FASTCALL SR_GRAPH_NS::BaseMaterial::SetVec4 (
    SR_UTILS_NS::StringAtom id,
    const SR_MATH_NS::FVector4 & v
) noexcept
```




<hr>



### function UnregisterMesh 

```C++
virtual void SR_GRAPH_NS::BaseMaterial::UnregisterMesh (
    uint32_t * pId
) 
```




<hr>



### function Use 

```C++
void SR_GRAPH_NS::BaseMaterial::Use () 
```




<hr>



### function UseSamplers 

```C++
void SR_GRAPH_NS::BaseMaterial::UseSamplers () 
```




<hr>



### function ~BaseMaterial 

```C++
SR_GRAPH_NS::BaseMaterial::~BaseMaterial () override
```




<hr>
## Protected Types Documentation




### typedef MeshPtr 

```C++
using SR_GRAPH_NS::BaseMaterial::MeshPtr =  SR_GTYPES_NS::Mesh*;
```




<hr>



### typedef RenderContextPtr 

```C++
using SR_GRAPH_NS::BaseMaterial::RenderContextPtr =  SR_HTYPES_NS::SafePtr<RenderContext>;
```




<hr>



### typedef ShaderPtr 

```C++
using SR_GRAPH_NS::BaseMaterial::ShaderPtr =  SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Shader>;
```




<hr>



### typedef TexturePtr 

```C++
using SR_GRAPH_NS::BaseMaterial::TexturePtr =  SR_GTYPES_NS::Texture*;
```




<hr>
## Protected Attributes Documentation




### variable m\_context 

```C++
RenderContextPtr SR_GRAPH_NS::BaseMaterial::m_context;
```




<hr>



### variable m\_meshes 

```C++
SR_HTYPES_NS::ObjectPool<MeshPtr, uint32_t> SR_GRAPH_NS::BaseMaterial::m_meshes;
```




<hr>



### variable m\_propertyChangedSubscription 

```C++
SR_UTILS_NS::Subscription SR_GRAPH_NS::BaseMaterial::m_propertyChangedSubscription;
```




<hr>



### variable m\_shaderChangedSubscription 

```C++
SR_UTILS_NS::Subscription SR_GRAPH_NS::BaseMaterial::m_shaderChangedSubscription;
```




<hr>



### variable m\_variants 

```C++
std::map<SR_UTILS_NS::SRHashType, SR_GTYPES_NS::Shader::Ptr> SR_GRAPH_NS::BaseMaterial::m_variants;
```




<hr>
## Protected Functions Documentation




### function DeInitMaterialDataSubscriptions 

```C++
void SR_GRAPH_NS::BaseMaterial::DeInitMaterialDataSubscriptions () 
```




<hr>



### function InitContext 

```C++
virtual void SR_GRAPH_NS::BaseMaterial::InitContext () const
```




<hr>



### function InitMaterialDataSubscriptions 

```C++
void SR_GRAPH_NS::BaseMaterial::InitMaterialDataSubscriptions () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Material/BaseMaterial.h`

