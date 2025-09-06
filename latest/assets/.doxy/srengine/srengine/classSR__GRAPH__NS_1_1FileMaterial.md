

# Class SR\_GRAPH\_NS::FileMaterial



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**FileMaterial**](classSR__GRAPH__NS_1_1FileMaterial.md)








Inherits the following classes: [SR\_GRAPH\_NS::BaseMaterial](classSR__GRAPH__NS_1_1BaseMaterial.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**FileMaterial**](classSR__GRAPH__NS_1_1FileMaterial.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


## Public Types inherited from SR_GRAPH_NS::BaseMaterial

See [SR\_GRAPH\_NS::BaseMaterial](classSR__GRAPH__NS_1_1BaseMaterial.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**BaseMaterial**](classSR__GRAPH__NS_1_1BaseMaterial.md) &gt; | [**Ptr**](classSR__GRAPH__NS_1_1BaseMaterial.md#typedef-ptr)  <br> |


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
| virtual SR\_NODISCARD const MaterialData::Ptr & | [**GetMaterialData**](#function-getmaterialdata) () noexcept override const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetMaterialPath**](#function-getmaterialpath) () noexcept const<br> |
| virtual SR\_NODISCARD MaterialType | [**GetMaterialType**](#function-getmaterialtype) () noexcept override const<br> |
|  void | [**SetMaterialPath**](#function-setmaterialpath) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) noexcept<br> |
|   | [**~FileMaterial**](#function-filematerial) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::BaseMaterial

See [SR\_GRAPH\_NS::BaseMaterial](classSR__GRAPH__NS_1_1BaseMaterial.md)

| Type | Name |
| ---: | :--- |
|   | [**BaseMaterial**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-basematerial) () <br> |
|  SR\_NODISCARD RenderContextPtr | [**GetContext**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-getcontext) () const<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**GetDefaultShader**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-getdefaultshader) () noexcept const<br> |
| virtual SR\_NODISCARD const MaterialData::Ptr & | [**GetMaterialData**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-getmaterialdata) () noexcept const = 0<br> |
| virtual SR\_NODISCARD MaterialType | [**GetMaterialType**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-getmaterialtype) () noexcept const = 0<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetRenderStageId**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-getrenderstageid) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**GetShader**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-getshader) (const [**SR\_SRSL\_NS::ShaderMacrosParams**](structSR__SRSL__NS_1_1ShaderMacrosParams.md) & macros) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsValid**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-isvalid) () const<br> |
|  void | [**OnPropertyChanged**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-onpropertychanged) (bool onlyUniforms) const<br> |
|  void | [**OnShaderChanged**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-onshaderchanged) () <br> |
| virtual SR\_NODISCARD uint32\_t | [**RegisterMesh**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-registermesh) (MeshPtr pMesh) <br> |
|  void SR\_FASTCALL | [**SetBool**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-setbool) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, bool v) noexcept<br> |
|  void SR\_FASTCALL | [**SetColor**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-setcolor) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & v) noexcept<br> |
| virtual void | [**SetShader**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-setshader-12) (ShaderPtr pShader) <br> |
|  void | [**SetShader**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-setshader-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void SR\_FASTCALL | [**SetTexture**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-settexture) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Texture**](classSR__GTYPES__NS_1_1Texture.md) &gt; & pTexture) noexcept<br> |
|  void SR\_FASTCALL | [**SetVec4**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-setvec4) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const SR\_MATH\_NS::FVector4 & v) noexcept<br> |
| virtual void | [**UnregisterMesh**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-unregistermesh) (uint32\_t \* pId) <br> |
|  void | [**Use**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-use) () <br> |
|  void | [**UseSamplers**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-usesamplers) () <br> |
|   | [**~BaseMaterial**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-basematerial) () override<br> |


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


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD BaseMaterial::Ptr | [**Load**](#function-load) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & rawPath) <br> |
|  SR\_NODISCARD BaseMaterial::Ptr | [**LoadAsUnique**](#function-loadasunique) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & rawPath) <br> |






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






## Protected Types inherited from SR_GRAPH_NS::BaseMaterial

See [SR\_GRAPH\_NS::BaseMaterial](classSR__GRAPH__NS_1_1BaseMaterial.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](classSR__GRAPH__NS_1_1BaseMaterial.md#typedef-meshptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) &gt; | [**RenderContextPtr**](classSR__GRAPH__NS_1_1BaseMaterial.md#typedef-rendercontextptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) &gt; | [**ShaderPtr**](classSR__GRAPH__NS_1_1BaseMaterial.md#typedef-shaderptr)  <br> |
| typedef [**SR\_GTYPES\_NS::Texture**](classSR__GTYPES__NS_1_1Texture.md) \* | [**TexturePtr**](classSR__GRAPH__NS_1_1BaseMaterial.md#typedef-textureptr)  <br> |




























## Protected Attributes inherited from SR_GRAPH_NS::BaseMaterial

See [SR\_GRAPH\_NS::BaseMaterial](classSR__GRAPH__NS_1_1BaseMaterial.md)

| Type | Name |
| ---: | :--- |
|  RenderContextPtr | [**m\_context**](classSR__GRAPH__NS_1_1BaseMaterial.md#variable-m_context)  <br> |
|  std::map&lt; SR\_UTILS\_NS::SRHashType, [**SR\_SRSL\_NS::ShaderMacrosParams**](structSR__SRSL__NS_1_1ShaderMacrosParams.md) &gt; | [**m\_hashRedirect**](classSR__GRAPH__NS_1_1BaseMaterial.md#variable-m_hashredirect)  <br> |
|  [**SR\_HTYPES\_NS::ObjectPool**](classSR__HTYPES__NS_1_1ObjectPool.md)&lt; MeshPtr, uint32\_t &gt; | [**m\_meshes**](classSR__GRAPH__NS_1_1BaseMaterial.md#variable-m_meshes)  <br> |
|  [**SR\_UTILS\_NS::Subscription**](classSR__UTILS__NS_1_1Subscription.md) | [**m\_propertyChangedSubscription**](classSR__GRAPH__NS_1_1BaseMaterial.md#variable-m_propertychangedsubscription)  <br> |
|  [**SR\_UTILS\_NS::Subscription**](classSR__UTILS__NS_1_1Subscription.md) | [**m\_shaderChangedSubscription**](classSR__GRAPH__NS_1_1BaseMaterial.md#variable-m_shaderchangedsubscription)  <br> |
|  std::map&lt; SR\_UTILS\_NS::SRHashType, SR\_GTYPES\_NS::Shader::Ptr &gt; | [**m\_variants**](classSR__GRAPH__NS_1_1BaseMaterial.md#variable-m_variants)  <br> |










## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |






































































































## Protected Functions inherited from SR_GRAPH_NS::BaseMaterial

See [SR\_GRAPH\_NS::BaseMaterial](classSR__GRAPH__NS_1_1BaseMaterial.md)

| Type | Name |
| ---: | :--- |
|  void | [**DeInitMaterialDataSubscriptions**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-deinitmaterialdatasubscriptions) () <br> |
| virtual void | [**InitContext**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-initcontext) () const<br> |
|  void | [**InitMaterialDataSubscriptions**](classSR__GRAPH__NS_1_1BaseMaterial.md#function-initmaterialdatasubscriptions) () <br> |






## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |




















## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_NS::FileMaterial::Ptr =  SR_HTYPES_NS::SharedPtr<FileMaterial>;
```




<hr>
## Public Functions Documentation




### function GetMaterialData 

```C++
virtual SR_NODISCARD const MaterialData::Ptr & SR_GRAPH_NS::FileMaterial::GetMaterialData () noexcept override const
```



Implements [*SR\_GRAPH\_NS::BaseMaterial::GetMaterialData*](classSR__GRAPH__NS_1_1BaseMaterial.md#function-getmaterialdata)


<hr>



### function GetMaterialPath 

```C++
inline SR_NODISCARD SR_UTILS_NS::Path SR_GRAPH_NS::FileMaterial::GetMaterialPath () noexcept const
```




<hr>



### function GetMaterialType 

```C++
inline virtual SR_NODISCARD MaterialType SR_GRAPH_NS::FileMaterial::GetMaterialType () noexcept override const
```



Implements [*SR\_GRAPH\_NS::BaseMaterial::GetMaterialType*](classSR__GRAPH__NS_1_1BaseMaterial.md#function-getmaterialtype)


<hr>



### function SetMaterialPath 

```C++
void SR_GRAPH_NS::FileMaterial::SetMaterialPath (
    const SR_UTILS_NS::Path & path
) noexcept
```




<hr>



### function ~FileMaterial 

```C++
SR_GRAPH_NS::FileMaterial::~FileMaterial () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD BaseMaterial::Ptr SR_GRAPH_NS::FileMaterial::Load (
    const SR_UTILS_NS::Path & rawPath
) 
```




<hr>



### function LoadAsUnique 

```C++
static SR_NODISCARD BaseMaterial::Ptr SR_GRAPH_NS::FileMaterial::LoadAsUnique (
    const SR_UTILS_NS::Path & rawPath
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Material/FileMaterial.h`

