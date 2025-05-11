

# Class SR\_UTILS\_NS::Transform



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Transform**](classSR__UTILS__NS_1_1Transform.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md),  [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)


Inherited by the following classes: [SR\_UTILS\_NS::Transform2D](classSR__UTILS__NS_1_1Transform2D.md),  [SR\_UTILS\_NS::Transform3D](classSR__UTILS__NS_1_1Transform3D.md),  [SR\_UTILS\_NS::TransformHolder](classSR__UTILS__NS_1_1TransformHolder.md),  [SR\_UTILS\_NS::TransformZero](classSR__UTILS__NS_1_1TransformZero.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Transform**](classSR__UTILS__NS_1_1Transform.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


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
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**Forward**](#function-forward) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**GameObject**](classSR__UTILS__NS_1_1GameObject.md) &gt; | [**GetGameObject**](#function-getgameobject) () const<br> |
| virtual SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetMatrix**](#function-getmatrix) () const<br> |
| virtual SR\_NODISCARD Measurement | [**GetMeasurement**](#function-getmeasurement) () const = 0<br> |
|  SR\_NODISCARD [**Transform**](classSR__UTILS__NS_1_1Transform.md) \* | [**GetParentTransform**](#function-getparenttransform) () const<br> |
| virtual SR\_NODISCARD [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**GetQuaternion**](#function-getquaternion) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetRotation**](#function-getrotation) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetScale**](#function-getscale) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetScale2D**](#function-getscale2d) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetSkew**](#function-getskew) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetTranslation**](#function-gettranslation) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetTranslation2D**](#function-gettranslation2d) () const<br> |
| virtual void | [**GlobalRotate**](#function-globalrotate-13) (const SR\_MATH\_NS::FVector3 & eulers) <br> |
| virtual void | [**GlobalRotate**](#function-globalrotate-23) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) <br> |
| virtual void | [**GlobalRotate**](#function-globalrotate-33) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual void | [**GlobalScale**](#function-globalscale) (const SR\_MATH\_NS::FVector3 & scale) <br> |
| virtual void | [**GlobalSkew**](#function-globalskew) (const SR\_MATH\_NS::FVector3 & skew) <br> |
| virtual void | [**GlobalTranslate**](#function-globaltranslate) (const SR\_MATH\_NS::FVector3 & translation) <br> |
| virtual void | [**LookAt**](#function-lookat-12) (const SR\_MATH\_NS::FVector3 & position) <br> |
| virtual void | [**LookAt**](#function-lookat-22) (const SR\_MATH\_NS::FVector3 & position, LookAtAxis axis) <br> |
| virtual void | [**OnHierarchyChanged**](#function-onhierarchychanged) () <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**Right**](#function-right) () const<br> |
| virtual void | [**Rotate**](#function-rotate-13) (const SR\_MATH\_NS::FVector3 & eulers) <br> |
| virtual void | [**Rotate**](#function-rotate-23) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q) <br> |
| virtual void | [**Rotate**](#function-rotate-33) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual void | [**RotateAround**](#function-rotatearound) (const SR\_MATH\_NS::FVector3 & point, const SR\_MATH\_NS::FVector3 & eulers) <br> |
| virtual void | [**RotateAroundParent**](#function-rotatearoundparent) (const SR\_MATH\_NS::FVector3 & eulers) <br> |
| virtual void | [**Scale**](#function-scale-12) (const SR\_MATH\_NS::FVector3 & scale) <br> |
| virtual void | [**Scale**](#function-scale-22) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
|  void | [**SetGameObject**](#function-setgameobject) ([**GameObject**](classSR__UTILS__NS_1_1GameObject.md) \* pGameObject) <br> |
| virtual void | [**SetGlobalRotation**](#function-setglobalrotation-12) (const SR\_MATH\_NS::FVector3 & eulers) <br> |
| virtual void | [**SetGlobalRotation**](#function-setglobalrotation-22) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) <br> |
| virtual void | [**SetGlobalTranslation**](#function-setglobaltranslation) (const SR\_MATH\_NS::FVector3 & translation) <br> |
| virtual void | [**SetMatrix**](#function-setmatrix) (const std::optional&lt; SR\_MATH\_NS::FVector3 &gt; & translation, const std::optional&lt; [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) &gt; & rotation, const std::optional&lt; SR\_MATH\_NS::FVector3 &gt; & scale) <br> |
| virtual void | [**SetRotation**](#function-setrotation-13) (const SR\_MATH\_NS::FVector3 & euler) <br> |
| virtual void | [**SetRotation**](#function-setrotation-23) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) <br> |
| virtual void | [**SetRotation**](#function-setrotation-33) (SR\_MATH\_NS::Unit yaw, SR\_MATH\_NS::Unit pitch, SR\_MATH\_NS::Unit roll) <br> |
| virtual void | [**SetScale**](#function-setscale-12) (const SR\_MATH\_NS::FVector3 & scale) <br> |
| virtual void | [**SetScale**](#function-setscale-22) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual void | [**SetSkew**](#function-setskew-12) (const SR\_MATH\_NS::FVector3 & skew) <br> |
| virtual void | [**SetSkew**](#function-setskew-22) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual void | [**SetTranslation**](#function-settranslation-12) (const SR\_MATH\_NS::FVector3 & translation) <br> |
| virtual void | [**SetTranslation**](#function-settranslation-22) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual void | [**SetTranslationAndRotation**](#function-settranslationandrotation) (const SR\_MATH\_NS::FVector3 & translation, const SR\_MATH\_NS::FVector3 & euler) <br> |
|   | [**Transform**](#function-transform) () <br> |
| virtual void | [**Translate**](#function-translate-12) (const SR\_MATH\_NS::FVector3 & translation) <br> |
| virtual void | [**Translate**](#function-translate-22) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**Up**](#function-up) () const<br> |
| virtual void | [**UpdateTree**](#function-updatetree) () <br> |
|   | [**~Transform**](#function-transform) () override<br> |


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
























## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**GameObject**](classSR__UTILS__NS_1_1GameObject.md) \* | [**m\_gameObject**](#variable-m_gameobject)   = `nullptr`<br> |








## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |








































































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**IsDirty**](#function-isdirty) () noexcept const<br> |
| virtual void | [**UpdateMatrix**](#function-updatematrix) () const<br> |




















## Public Types Documentation




### typedef Ptr 

```C++
using SR_UTILS_NS::Transform::Ptr =  SR_HTYPES_NS::SharedPtr<Transform>;
```




<hr>
## Public Functions Documentation




### function Forward 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform::Forward () const
```




<hr>



### function GetGameObject 

```C++
SR_NODISCARD SR_HTYPES_NS::SharedPtr < GameObject > SR_UTILS_NS::Transform::GetGameObject () const
```




<hr>



### function GetMatrix 

```C++
virtual SR_NODISCARD const SR_MATH_NS::Matrix4x4 & SR_UTILS_NS::Transform::GetMatrix () const
```




<hr>



### function GetMeasurement 

```C++
virtual SR_NODISCARD Measurement SR_UTILS_NS::Transform::GetMeasurement () const = 0
```




<hr>



### function GetParentTransform 

```C++
SR_NODISCARD Transform * SR_UTILS_NS::Transform::GetParentTransform () const
```




<hr>



### function GetQuaternion 

```C++
virtual SR_NODISCARD SR_MATH_NS::Quaternion SR_UTILS_NS::Transform::GetQuaternion () const
```




<hr>



### function GetRotation 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform::GetRotation () const
```




<hr>



### function GetScale 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform::GetScale () const
```




<hr>



### function GetScale2D 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector2 SR_UTILS_NS::Transform::GetScale2D () const
```




<hr>



### function GetSkew 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform::GetSkew () const
```




<hr>



### function GetTranslation 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform::GetTranslation () const
```




<hr>



### function GetTranslation2D 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector2 SR_UTILS_NS::Transform::GetTranslation2D () const
```




<hr>



### function GlobalRotate [1/3]

```C++
virtual void SR_UTILS_NS::Transform::GlobalRotate (
    const SR_MATH_NS::FVector3 & eulers
) 
```




<hr>



### function GlobalRotate [2/3]

```C++
virtual void SR_UTILS_NS::Transform::GlobalRotate (
    const SR_MATH_NS::Quaternion & quaternion
) 
```




<hr>



### function GlobalRotate [3/3]

```C++
virtual void SR_UTILS_NS::Transform::GlobalRotate (
    SR_MATH_NS::Unit x,
    SR_MATH_NS::Unit y,
    SR_MATH_NS::Unit z
) 
```




<hr>



### function GlobalScale 

```C++
virtual void SR_UTILS_NS::Transform::GlobalScale (
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function GlobalSkew 

```C++
virtual void SR_UTILS_NS::Transform::GlobalSkew (
    const SR_MATH_NS::FVector3 & skew
) 
```




<hr>



### function GlobalTranslate 

```C++
virtual void SR_UTILS_NS::Transform::GlobalTranslate (
    const SR_MATH_NS::FVector3 & translation
) 
```




<hr>



### function LookAt [1/2]

```C++
virtual void SR_UTILS_NS::Transform::LookAt (
    const SR_MATH_NS::FVector3 & position
) 
```




<hr>



### function LookAt [2/2]

```C++
virtual void SR_UTILS_NS::Transform::LookAt (
    const SR_MATH_NS::FVector3 & position,
    LookAtAxis axis
) 
```




<hr>



### function OnHierarchyChanged 

```C++
virtual void SR_UTILS_NS::Transform::OnHierarchyChanged () 
```




<hr>



### function Right 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform::Right () const
```




<hr>



### function Rotate [1/3]

```C++
virtual void SR_UTILS_NS::Transform::Rotate (
    const SR_MATH_NS::FVector3 & eulers
) 
```




<hr>



### function Rotate [2/3]

```C++
virtual void SR_UTILS_NS::Transform::Rotate (
    const SR_MATH_NS::Quaternion & q
) 
```




<hr>



### function Rotate [3/3]

```C++
virtual void SR_UTILS_NS::Transform::Rotate (
    SR_MATH_NS::Unit x,
    SR_MATH_NS::Unit y,
    SR_MATH_NS::Unit z
) 
```




<hr>



### function RotateAround 

```C++
virtual void SR_UTILS_NS::Transform::RotateAround (
    const SR_MATH_NS::FVector3 & point,
    const SR_MATH_NS::FVector3 & eulers
) 
```




<hr>



### function RotateAroundParent 

```C++
virtual void SR_UTILS_NS::Transform::RotateAroundParent (
    const SR_MATH_NS::FVector3 & eulers
) 
```




<hr>



### function Scale [1/2]

```C++
virtual void SR_UTILS_NS::Transform::Scale (
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function Scale [2/2]

```C++
virtual void SR_UTILS_NS::Transform::Scale (
    SR_MATH_NS::Unit x,
    SR_MATH_NS::Unit y,
    SR_MATH_NS::Unit z
) 
```




<hr>



### function SetGameObject 

```C++
void SR_UTILS_NS::Transform::SetGameObject (
    GameObject * pGameObject
) 
```




<hr>



### function SetGlobalRotation [1/2]

```C++
virtual void SR_UTILS_NS::Transform::SetGlobalRotation (
    const SR_MATH_NS::FVector3 & eulers
) 
```




<hr>



### function SetGlobalRotation [2/2]

```C++
virtual void SR_UTILS_NS::Transform::SetGlobalRotation (
    const SR_MATH_NS::Quaternion & quaternion
) 
```




<hr>



### function SetGlobalTranslation 

```C++
virtual void SR_UTILS_NS::Transform::SetGlobalTranslation (
    const SR_MATH_NS::FVector3 & translation
) 
```




<hr>



### function SetMatrix 

```C++
virtual void SR_UTILS_NS::Transform::SetMatrix (
    const std::optional< SR_MATH_NS::FVector3 > & translation,
    const std::optional< SR_MATH_NS::Quaternion > & rotation,
    const std::optional< SR_MATH_NS::FVector3 > & scale
) 
```




<hr>



### function SetRotation [1/3]

```C++
virtual void SR_UTILS_NS::Transform::SetRotation (
    const SR_MATH_NS::FVector3 & euler
) 
```




<hr>



### function SetRotation [2/3]

```C++
virtual void SR_UTILS_NS::Transform::SetRotation (
    const SR_MATH_NS::Quaternion & quaternion
) 
```




<hr>



### function SetRotation [3/3]

```C++
virtual void SR_UTILS_NS::Transform::SetRotation (
    SR_MATH_NS::Unit yaw,
    SR_MATH_NS::Unit pitch,
    SR_MATH_NS::Unit roll
) 
```




<hr>



### function SetScale [1/2]

```C++
virtual void SR_UTILS_NS::Transform::SetScale (
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function SetScale [2/2]

```C++
virtual void SR_UTILS_NS::Transform::SetScale (
    SR_MATH_NS::Unit x,
    SR_MATH_NS::Unit y,
    SR_MATH_NS::Unit z
) 
```




<hr>



### function SetSkew [1/2]

```C++
virtual void SR_UTILS_NS::Transform::SetSkew (
    const SR_MATH_NS::FVector3 & skew
) 
```




<hr>



### function SetSkew [2/2]

```C++
virtual void SR_UTILS_NS::Transform::SetSkew (
    SR_MATH_NS::Unit x,
    SR_MATH_NS::Unit y,
    SR_MATH_NS::Unit z
) 
```




<hr>



### function SetTranslation [1/2]

```C++
virtual void SR_UTILS_NS::Transform::SetTranslation (
    const SR_MATH_NS::FVector3 & translation
) 
```




<hr>



### function SetTranslation [2/2]

```C++
virtual void SR_UTILS_NS::Transform::SetTranslation (
    SR_MATH_NS::Unit x,
    SR_MATH_NS::Unit y,
    SR_MATH_NS::Unit z
) 
```




<hr>



### function SetTranslationAndRotation 

```C++
virtual void SR_UTILS_NS::Transform::SetTranslationAndRotation (
    const SR_MATH_NS::FVector3 & translation,
    const SR_MATH_NS::FVector3 & euler
) 
```




<hr>



### function Transform 

```C++
SR_UTILS_NS::Transform::Transform () 
```




<hr>



### function Translate [1/2]

```C++
virtual void SR_UTILS_NS::Transform::Translate (
    const SR_MATH_NS::FVector3 & translation
) 
```




<hr>



### function Translate [2/2]

```C++
virtual void SR_UTILS_NS::Transform::Translate (
    SR_MATH_NS::Unit x,
    SR_MATH_NS::Unit y,
    SR_MATH_NS::Unit z
) 
```




<hr>



### function Up 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform::Up () const
```




<hr>



### function UpdateTree 

```C++
virtual void SR_UTILS_NS::Transform::UpdateTree () 
```




<hr>



### function ~Transform 

```C++
SR_UTILS_NS::Transform::~Transform () override
```




<hr>
## Protected Attributes Documentation




### variable m\_gameObject 

```C++
GameObject* SR_UTILS_NS::Transform::m_gameObject;
```




<hr>
## Protected Functions Documentation




### function IsDirty 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::Transform::IsDirty () noexcept const
```




<hr>



### function UpdateMatrix 

```C++
virtual void SR_UTILS_NS::Transform::UpdateMatrix () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/ECS/Transform.h`

