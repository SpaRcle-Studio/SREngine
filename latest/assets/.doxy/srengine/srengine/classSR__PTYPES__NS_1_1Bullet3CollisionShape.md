

# Class SR\_PTYPES\_NS::Bullet3CollisionShape



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**Bullet3CollisionShape**](classSR__PTYPES__NS_1_1Bullet3CollisionShape.md)








Inherits the following classes: [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md)
















## Public Types inherited from SR_PTYPES_NS::CollisionShape

See [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](classSR__PTYPES__NS_1_1CollisionShape.md#typedef-libraryptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; PhysicsScene &gt; | [**PhysicsScenePtr**](classSR__PTYPES__NS_1_1CollisionShape.md#typedef-physicssceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md) &gt; | [**Ptr**](classSR__PTYPES__NS_1_1CollisionShape.md#typedef-ptr)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |




## Public Types inherited from SR_HTYPES_NS::IRawMeshHolder

See [SR\_HTYPES\_NS::IRawMeshHolder](classSR__HTYPES__NS_1_1IRawMeshHolder.md)

| Type | Name |
| ---: | :--- |
| typedef int32\_t | [**MeshIndex**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#typedef-meshindex)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) &gt; | [**RawMeshPtr**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#typedef-rawmeshptr)  <br> |


## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |


































































































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Bullet3CollisionShape**](#function-bullet3collisionshape) (LibraryPtr pLibrary) <br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**CalculateLocalInertia**](#function-calculatelocalinertia) (float\_t mass) override const<br> |
|  SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () noexcept override const<br> |
|  bool | [**UpdateMatrix**](#function-updatematrix) () override<br> |
|  bool | [**UpdateShape**](#function-updateshape) () override<br> |
|   | [**~Bullet3CollisionShape**](#function-bullet3collisionshape) () override<br> |


## Public Functions inherited from SR_PTYPES_NS::CollisionShape

See [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**CalculateLocalInertia**](classSR__PTYPES__NS_1_1CollisionShape.md#function-calculatelocalinertia) (float\_t mass) const<br> |
|   | [**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md#function-collisionshape) () <br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetBounds**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getbounds) () const<br> |
|  SR\_NODISCARD void \* | [**GetHandle**](classSR__PTYPES__NS_1_1CollisionShape.md#function-gethandle) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetHeight**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getheight) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetPlaneSize**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getplanesize) () const<br> |
|  SR\_NODISCARD float\_t | [**GetRadius**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getradius) () const<br> |
|  SR\_NODISCARD [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* | [**GetRigidbody**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getrigidbody) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetSize**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getsize) () const<br> |
|  SR\_NODISCARD ShapeType | [**GetType**](classSR__PTYPES__NS_1_1CollisionShape.md#function-gettype) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasGeometry**](classSR__PTYPES__NS_1_1CollisionShape.md#function-hasgeometry) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsShapeValid**](classSR__PTYPES__NS_1_1CollisionShape.md#function-isshapevalid) () noexcept const<br> |
| virtual void | [**OnRawMeshChanged**](classSR__PTYPES__NS_1_1CollisionShape.md#function-onrawmeshchanged) () override<br> |
|  void | [**ReInitDebugShape**](classSR__PTYPES__NS_1_1CollisionShape.md#function-reinitdebugshape) () <br> |
|  void | [**RemoveDebugShape**](classSR__PTYPES__NS_1_1CollisionShape.md#function-removedebugshape) () <br> |
|  void | [**SetBounds**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setbounds) (const SR\_MATH\_NS::FVector3 & bounds) <br> |
|  void | [**SetHeight**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setheight) (float\_t height) <br> |
|  void | [**SetPlaneSize**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setplanesize) (const SR\_MATH\_NS::FVector2 & size) <br> |
|  void | [**SetRadius**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setradius) (float\_t radius) <br> |
|  void | [**SetRigidbody**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setrigidbody) ([**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* pRigidbody) <br> |
|  void | [**SetSize**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setsize) (const SR\_MATH\_NS::FVector3 & size) <br> |
|  void | [**SetType**](classSR__PTYPES__NS_1_1CollisionShape.md#function-settype) (ShapeType type) <br> |
|  void | [**Update**](classSR__PTYPES__NS_1_1CollisionShape.md#function-update) (float\_t dt) <br> |
|  void | [**UpdateDebugShape**](classSR__PTYPES__NS_1_1CollisionShape.md#function-updatedebugshape) () <br> |
|  bool | [**UpdateMatrix**](classSR__PTYPES__NS_1_1CollisionShape.md#function-updatematrix) () <br> |
|  bool | [**UpdateShape**](classSR__PTYPES__NS_1_1CollisionShape.md#function-updateshape) () <br> |
|   | [**~CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md#function-collisionshape) () override<br> |


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
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br>_NOLINT(modernize-use-nodiscard)_  |
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
|  bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_2) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_3) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_4) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_5) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_6) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
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
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |


## Public Functions inherited from SR_HTYPES_NS::IRawMeshHolder

See [SR\_HTYPES\_NS::IRawMeshHolder](classSR__HTYPES__NS_1_1IRawMeshHolder.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string\_view | [**GetGeometryName**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getgeometryname) () noexcept const<br> |
|  SR\_NODISCARD MeshIndex | [**GetMeshId**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getmeshid) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetMeshPath**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getmeshpath) () noexcept const<br> |
|  SR\_NODISCARD std::string | [**GetMeshStringPath**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getmeshstringpath) () noexcept const<br> |
|  SR\_NODISCARD const RawMeshPtr & | [**GetRawMesh**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getrawmesh) () noexcept const<br> |
|  SR\_NODISCARD std::vector&lt; [**SR\_UTILS\_NS::Vertex**](structSR__UTILS__NS_1_1Vertex.md) &gt; | [**GetVertices**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getvertices) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsValidMeshId**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-isvalidmeshid) () noexcept const<br> |
| virtual void | [**OnRawMeshChanged**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-onrawmeshchanged) () <br> |
|  void | [**SetMeshId**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-setmeshid) (MeshIndex meshIndex, bool forceReload=false) <br> |
|  void | [**SetRawMesh**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-setrawmesh-12) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**SetRawMesh**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-setrawmesh-22) (RawMeshPtr pRawMesh) <br> |
| virtual  | [**~IRawMeshHolder**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-irawmeshholder) () <br> |


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
| virtual SR\_NODISCARD const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMeta**](classSR__UTILS__NS_1_1SRClass.md#function-getmeta) () noexcept const = 0<br> |
| virtual  | [**~SRClass**](classSR__UTILS__NS_1_1SRClass.md#function-srclass) () = default<br> |






## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |








## Public Static Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**AllocateStatic**](classSR__UTILS__NS_1_1SRClass.md#function-allocatestatic) () noexcept<br> |
|  SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](classSR__UTILS__NS_1_1SRClass.md#function-getbasemetas) () noexcept<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetClassStaticName**](classSR__UTILS__NS_1_1SRClass.md#function-getclassstaticname) () noexcept<br> |
|  const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMetaStatic**](classSR__UTILS__NS_1_1SRClass.md#function-getmetastatic) () noexcept<br> |
|  bool | [**RegisterPropertiesCodegen**](classSR__UTILS__NS_1_1SRClass.md#function-registerpropertiescodegen) () <br> |
































## Protected Attributes inherited from SR_PTYPES_NS::CollisionShape

See [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md)

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FVector3 | [**m\_bounds**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_bounds)   = `SR\_MATH\_NS::FVector3::One()`<br> |
|  uint64\_t | [**m\_debugId**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_debugid)   = `SR\_ID\_INVALID`<br> |
|  [**CollisionShapeImpl**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md) \* | [**m\_impl**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_impl)   = `nullptr`<br> |
|  [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* | [**m\_rigidbody**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_rigidbody)   = `nullptr`<br> |
|  ShapeType | [**m\_type**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_type)   = `ShapeType::Unknown`<br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |






































































































































## Public Functions Documentation




### function Bullet3CollisionShape 

```C++
SR_PTYPES_NS::Bullet3CollisionShape::Bullet3CollisionShape (
    LibraryPtr pLibrary
) 
```




<hr>



### function CalculateLocalInertia 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::Bullet3CollisionShape::CalculateLocalInertia (
    float_t mass
) override const
```




<hr>



### function GetHandle 

```C++
inline SR_NODISCARD void * SR_PTYPES_NS::Bullet3CollisionShape::GetHandle () noexcept override const
```




<hr>



### function UpdateMatrix 

```C++
bool SR_PTYPES_NS::Bullet3CollisionShape::UpdateMatrix () override
```




<hr>



### function UpdateShape 

```C++
bool SR_PTYPES_NS::Bullet3CollisionShape::UpdateShape () override
```




<hr>



### function ~Bullet3CollisionShape 

```C++
SR_PTYPES_NS::Bullet3CollisionShape::~Bullet3CollisionShape () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/Bullet3/Bullet3CollisionShape.h`

