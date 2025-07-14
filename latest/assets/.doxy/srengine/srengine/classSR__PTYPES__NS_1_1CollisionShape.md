

# Class SR\_PTYPES\_NS::CollisionShape



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md)








Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md),  [SR\_HTYPES\_NS::IRawMeshHolder](classSR__HTYPES__NS_1_1IRawMeshHolder.md),  [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)


Inherited by the following classes: [SR\_PTYPES\_NS::Bullet3CollisionShape](classSR__PTYPES__NS_1_1Bullet3CollisionShape.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](#typedef-libraryptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; PhysicsScene &gt; | [**PhysicsScenePtr**](#typedef-physicssceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


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
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**CalculateLocalInertia**](#function-calculatelocalinertia) (float\_t mass) const<br> |
|   | [**CollisionShape**](#function-collisionshape) () <br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetBounds**](#function-getbounds) () const<br> |
|  SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetHeight**](#function-getheight) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetPlaneSize**](#function-getplanesize) () const<br> |
|  SR\_NODISCARD float\_t | [**GetRadius**](#function-getradius) () const<br> |
|  SR\_NODISCARD [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* | [**GetRigidbody**](#function-getrigidbody) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetSize**](#function-getsize) () const<br> |
|  SR\_NODISCARD ShapeType | [**GetType**](#function-gettype) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasGeometry**](#function-hasgeometry) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsShapeValid**](#function-isshapevalid) () noexcept const<br> |
| virtual void | [**OnRawMeshChanged**](#function-onrawmeshchanged) () override<br> |
|  void | [**ReInitDebugShape**](#function-reinitdebugshape) () <br> |
|  void | [**RemoveDebugShape**](#function-removedebugshape) () <br> |
|  void | [**SetBounds**](#function-setbounds) (const SR\_MATH\_NS::FVector3 & bounds) <br> |
|  void | [**SetHeight**](#function-setheight) (float\_t height) <br> |
|  void | [**SetPlaneSize**](#function-setplanesize) (const SR\_MATH\_NS::FVector2 & size) <br> |
|  void | [**SetRadius**](#function-setradius) (float\_t radius) <br> |
|  void | [**SetRigidbody**](#function-setrigidbody) ([**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* pRigidbody) <br> |
|  void | [**SetSize**](#function-setsize) (const SR\_MATH\_NS::FVector3 & size) <br> |
|  void | [**SetType**](#function-settype) (ShapeType type) <br> |
|  void | [**Update**](#function-update) (float\_t dt) <br> |
|  void | [**UpdateDebugShape**](#function-updatedebugshape) () <br> |
|  bool | [**UpdateMatrix**](#function-updatematrix) () <br> |
|  bool | [**UpdateShape**](#function-updateshape) () <br> |
|   | [**~CollisionShape**](#function-collisionshape) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
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
|  SR\_NODISCARD RawMeshPtr | [**GetRawMesh**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getrawmesh) () noexcept const<br> |
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


























## Protected Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FVector3 | [**m\_bounds**](#variable-m_bounds)   = `SR\_MATH\_NS::FVector3::One()`<br> |
|  uint64\_t | [**m\_debugId**](#variable-m_debugid)   = `SR\_ID\_INVALID`<br> |
|  [**CollisionShapeImpl**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md) \* | [**m\_impl**](#variable-m_impl)   = `nullptr`<br> |
|  [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* | [**m\_rigidbody**](#variable-m_rigidbody)   = `nullptr`<br> |
|  ShapeType | [**m\_type**](#variable-m_type)   = `ShapeType::Unknown`<br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |




















































































































## Public Types Documentation




### typedef LibraryPtr 

```C++
using SR_PTYPES_NS::CollisionShape::LibraryPtr =  SR_PHYSICS_NS::LibraryImpl*;
```




<hr>



### typedef PhysicsScenePtr 

```C++
using SR_PTYPES_NS::CollisionShape::PhysicsScenePtr =  SR_HTYPES_NS::SafePtr<PhysicsScene>;
```




<hr>



### typedef Ptr 

```C++
using SR_PTYPES_NS::CollisionShape::Ptr =  SR_HTYPES_NS::SharedPtr<CollisionShape>;
```




<hr>
## Public Functions Documentation




### function CalculateLocalInertia 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::CalculateLocalInertia (
    float_t mass
) const
```




<hr>



### function CollisionShape 

```C++
SR_PTYPES_NS::CollisionShape::CollisionShape () 
```




<hr>



### function GetBounds 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::GetBounds () const
```




<hr>



### function GetHandle 

```C++
SR_NODISCARD void * SR_PTYPES_NS::CollisionShape::GetHandle () noexcept const
```




<hr>



### function GetHeight 

```C++
SR_NODISCARD float_t SR_PTYPES_NS::CollisionShape::GetHeight () const
```




<hr>



### function GetPlaneSize 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector2 SR_PTYPES_NS::CollisionShape::GetPlaneSize () const
```




<hr>



### function GetRadius 

```C++
SR_NODISCARD float_t SR_PTYPES_NS::CollisionShape::GetRadius () const
```




<hr>



### function GetRigidbody 

```C++
SR_NODISCARD Rigidbody * SR_PTYPES_NS::CollisionShape::GetRigidbody () const
```




<hr>



### function GetSize 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::GetSize () const
```




<hr>



### function GetType 

```C++
SR_NODISCARD ShapeType SR_PTYPES_NS::CollisionShape::GetType () noexcept const
```




<hr>



### function HasGeometry 

```C++
SR_NODISCARD bool SR_PTYPES_NS::CollisionShape::HasGeometry () noexcept const
```




<hr>



### function IsShapeValid 

```C++
SR_NODISCARD bool SR_PTYPES_NS::CollisionShape::IsShapeValid () noexcept const
```




<hr>



### function OnRawMeshChanged 

```C++
virtual void SR_PTYPES_NS::CollisionShape::OnRawMeshChanged () override
```



Implements [*SR\_HTYPES\_NS::IRawMeshHolder::OnRawMeshChanged*](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-onrawmeshchanged)


<hr>



### function ReInitDebugShape 

```C++
void SR_PTYPES_NS::CollisionShape::ReInitDebugShape () 
```




<hr>



### function RemoveDebugShape 

```C++
void SR_PTYPES_NS::CollisionShape::RemoveDebugShape () 
```




<hr>



### function SetBounds 

```C++
void SR_PTYPES_NS::CollisionShape::SetBounds (
    const SR_MATH_NS::FVector3 & bounds
) 
```




<hr>



### function SetHeight 

```C++
void SR_PTYPES_NS::CollisionShape::SetHeight (
    float_t height
) 
```




<hr>



### function SetPlaneSize 

```C++
void SR_PTYPES_NS::CollisionShape::SetPlaneSize (
    const SR_MATH_NS::FVector2 & size
) 
```




<hr>



### function SetRadius 

```C++
void SR_PTYPES_NS::CollisionShape::SetRadius (
    float_t radius
) 
```




<hr>



### function SetRigidbody 

```C++
inline void SR_PTYPES_NS::CollisionShape::SetRigidbody (
    Rigidbody * pRigidbody
) 
```




<hr>



### function SetSize 

```C++
void SR_PTYPES_NS::CollisionShape::SetSize (
    const SR_MATH_NS::FVector3 & size
) 
```




<hr>



### function SetType 

```C++
void SR_PTYPES_NS::CollisionShape::SetType (
    ShapeType type
) 
```




<hr>



### function Update 

```C++
void SR_PTYPES_NS::CollisionShape::Update (
    float_t dt
) 
```




<hr>



### function UpdateDebugShape 

```C++
void SR_PTYPES_NS::CollisionShape::UpdateDebugShape () 
```




<hr>



### function UpdateMatrix 

```C++
bool SR_PTYPES_NS::CollisionShape::UpdateMatrix () 
```




<hr>



### function UpdateShape 

```C++
bool SR_PTYPES_NS::CollisionShape::UpdateShape () 
```




<hr>



### function ~CollisionShape 

```C++
SR_PTYPES_NS::CollisionShape::~CollisionShape () override
```




<hr>
## Protected Attributes Documentation




### variable m\_bounds 

```C++
SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::m_bounds;
```




<hr>



### variable m\_debugId 

```C++
uint64_t SR_PTYPES_NS::CollisionShape::m_debugId;
```




<hr>



### variable m\_impl 

```C++
CollisionShapeImpl* SR_PTYPES_NS::CollisionShape::m_impl;
```




<hr>



### variable m\_rigidbody 

```C++
Rigidbody* SR_PTYPES_NS::CollisionShape::m_rigidbody;
```




<hr>



### variable m\_type 

```C++
ShapeType SR_PTYPES_NS::CollisionShape::m_type;
```




<hr>## Friends Documentation





### friend PhysicsScene 

```C++
class SR_PTYPES_NS::CollisionShape::PhysicsScene (
    SR_PHYSICS_NS::PhysicsScene
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/CollisionShape.h`

