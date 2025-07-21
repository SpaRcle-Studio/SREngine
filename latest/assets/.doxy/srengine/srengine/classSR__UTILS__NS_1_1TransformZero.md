

# Class SR\_UTILS\_NS::TransformZero



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**TransformZero**](classSR__UTILS__NS_1_1TransformZero.md)








Inherits the following classes: [SR\_UTILS\_NS::Transform](classSR__UTILS__NS_1_1Transform.md)
















## Public Types inherited from SR_UTILS_NS::Transform

See [SR\_UTILS\_NS::Transform](classSR__UTILS__NS_1_1Transform.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Transform**](classSR__UTILS__NS_1_1Transform.md) &gt; | [**Ptr**](classSR__UTILS__NS_1_1Transform.md#typedef-ptr)  <br> |


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
| virtual SR\_NODISCARD Measurement | [**GetMeasurement**](#function-getmeasurement) () override const<br> |


## Public Functions inherited from SR_UTILS_NS::Transform

See [SR\_UTILS\_NS::Transform](classSR__UTILS__NS_1_1Transform.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**Forward**](classSR__UTILS__NS_1_1Transform.md#function-forward) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**GameObject**](classSR__UTILS__NS_1_1GameObject.md) &gt; | [**GetGameObject**](classSR__UTILS__NS_1_1Transform.md#function-getgameobject) () const<br> |
| virtual SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetMatrix**](classSR__UTILS__NS_1_1Transform.md#function-getmatrix) () const<br> |
| virtual SR\_NODISCARD Measurement | [**GetMeasurement**](classSR__UTILS__NS_1_1Transform.md#function-getmeasurement) () const = 0<br> |
|  SR\_NODISCARD [**Transform**](classSR__UTILS__NS_1_1Transform.md) \* | [**GetParentTransform**](classSR__UTILS__NS_1_1Transform.md#function-getparenttransform) () const<br> |
| virtual SR\_NODISCARD [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**GetQuaternion**](classSR__UTILS__NS_1_1Transform.md#function-getquaternion) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetRotation**](classSR__UTILS__NS_1_1Transform.md#function-getrotation) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetScale**](classSR__UTILS__NS_1_1Transform.md#function-getscale) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetScale2D**](classSR__UTILS__NS_1_1Transform.md#function-getscale2d) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetSkew**](classSR__UTILS__NS_1_1Transform.md#function-getskew) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetTranslation**](classSR__UTILS__NS_1_1Transform.md#function-gettranslation) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetTranslation2D**](classSR__UTILS__NS_1_1Transform.md#function-gettranslation2d) () const<br> |
| virtual void | [**GlobalRotate**](classSR__UTILS__NS_1_1Transform.md#function-globalrotate-13) (const SR\_MATH\_NS::FVector3 & eulers) <br> |
| virtual void | [**GlobalRotate**](classSR__UTILS__NS_1_1Transform.md#function-globalrotate-23) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) <br> |
| virtual void | [**GlobalRotate**](classSR__UTILS__NS_1_1Transform.md#function-globalrotate-33) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual void | [**GlobalScale**](classSR__UTILS__NS_1_1Transform.md#function-globalscale) (const SR\_MATH\_NS::FVector3 & scale) <br> |
| virtual void | [**GlobalSkew**](classSR__UTILS__NS_1_1Transform.md#function-globalskew) (const SR\_MATH\_NS::FVector3 & skew) <br> |
| virtual void | [**GlobalTranslate**](classSR__UTILS__NS_1_1Transform.md#function-globaltranslate) (const SR\_MATH\_NS::FVector3 & translation) <br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE bool | [**IsDirty**](classSR__UTILS__NS_1_1Transform.md#function-isdirty) () noexcept const<br> |
| virtual void | [**LookAt**](classSR__UTILS__NS_1_1Transform.md#function-lookat-12) (const SR\_MATH\_NS::FVector3 & position) <br> |
| virtual void | [**LookAt**](classSR__UTILS__NS_1_1Transform.md#function-lookat-22) (const SR\_MATH\_NS::FVector3 & position, LookAtAxis axis) <br> |
| virtual void | [**OnHierarchyChanged**](classSR__UTILS__NS_1_1Transform.md#function-onhierarchychanged) () <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**Right**](classSR__UTILS__NS_1_1Transform.md#function-right) () const<br> |
| virtual void | [**Rotate**](classSR__UTILS__NS_1_1Transform.md#function-rotate-13) (const SR\_MATH\_NS::FVector3 & eulers) <br> |
| virtual void | [**Rotate**](classSR__UTILS__NS_1_1Transform.md#function-rotate-23) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q) <br> |
| virtual void | [**Rotate**](classSR__UTILS__NS_1_1Transform.md#function-rotate-33) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual void | [**RotateAround**](classSR__UTILS__NS_1_1Transform.md#function-rotatearound) (const SR\_MATH\_NS::FVector3 & point, const SR\_MATH\_NS::FVector3 & eulers) <br> |
| virtual void | [**RotateAroundParent**](classSR__UTILS__NS_1_1Transform.md#function-rotatearoundparent) (const SR\_MATH\_NS::FVector3 & eulers) <br> |
| virtual void | [**Scale**](classSR__UTILS__NS_1_1Transform.md#function-scale-12) (const SR\_MATH\_NS::FVector3 & scale) <br> |
| virtual void | [**Scale**](classSR__UTILS__NS_1_1Transform.md#function-scale-22) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
|  void | [**SetGameObject**](classSR__UTILS__NS_1_1Transform.md#function-setgameobject) ([**GameObject**](classSR__UTILS__NS_1_1GameObject.md) \* pGameObject) <br> |
| virtual void | [**SetGlobalRotation**](classSR__UTILS__NS_1_1Transform.md#function-setglobalrotation-12) (const SR\_MATH\_NS::FVector3 & eulers) <br> |
| virtual void | [**SetGlobalRotation**](classSR__UTILS__NS_1_1Transform.md#function-setglobalrotation-22) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) <br> |
| virtual void | [**SetGlobalTranslation**](classSR__UTILS__NS_1_1Transform.md#function-setglobaltranslation) (const SR\_MATH\_NS::FVector3 & translation) <br> |
| virtual void | [**SetMatrix**](classSR__UTILS__NS_1_1Transform.md#function-setmatrix) (const std::optional&lt; SR\_MATH\_NS::FVector3 &gt; & translation, const std::optional&lt; [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) &gt; & rotation, const std::optional&lt; SR\_MATH\_NS::FVector3 &gt; & scale) <br> |
| virtual void | [**SetRotation**](classSR__UTILS__NS_1_1Transform.md#function-setrotation-13) (const SR\_MATH\_NS::FVector3 & euler) <br> |
| virtual void | [**SetRotation**](classSR__UTILS__NS_1_1Transform.md#function-setrotation-23) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) <br> |
| virtual void | [**SetRotation**](classSR__UTILS__NS_1_1Transform.md#function-setrotation-33) (SR\_MATH\_NS::Unit yaw, SR\_MATH\_NS::Unit pitch, SR\_MATH\_NS::Unit roll) <br> |
| virtual void | [**SetScale**](classSR__UTILS__NS_1_1Transform.md#function-setscale-12) (const SR\_MATH\_NS::FVector3 & scale) <br> |
| virtual void | [**SetScale**](classSR__UTILS__NS_1_1Transform.md#function-setscale-22) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual void | [**SetSkew**](classSR__UTILS__NS_1_1Transform.md#function-setskew-12) (const SR\_MATH\_NS::FVector3 & skew) <br> |
| virtual void | [**SetSkew**](classSR__UTILS__NS_1_1Transform.md#function-setskew-22) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual void | [**SetTranslation**](classSR__UTILS__NS_1_1Transform.md#function-settranslation-12) (const SR\_MATH\_NS::FVector3 & translation) <br> |
| virtual void | [**SetTranslation**](classSR__UTILS__NS_1_1Transform.md#function-settranslation-22) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual void | [**SetTranslationAndRotation**](classSR__UTILS__NS_1_1Transform.md#function-settranslationandrotation) (const SR\_MATH\_NS::FVector3 & translation, const SR\_MATH\_NS::FVector3 & euler) <br> |
|   | [**Transform**](classSR__UTILS__NS_1_1Transform.md#function-transform) () <br> |
| virtual void | [**Translate**](classSR__UTILS__NS_1_1Transform.md#function-translate-12) (const SR\_MATH\_NS::FVector3 & translation) <br> |
| virtual void | [**Translate**](classSR__UTILS__NS_1_1Transform.md#function-translate-22) (SR\_MATH\_NS::Unit x, SR\_MATH\_NS::Unit y, SR\_MATH\_NS::Unit z) <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**Up**](classSR__UTILS__NS_1_1Transform.md#function-up) () const<br> |
|  void | [**UpdateTree**](classSR__UTILS__NS_1_1Transform.md#function-updatetree) () <br> |
|   | [**~Transform**](classSR__UTILS__NS_1_1Transform.md#function-transform) () override<br> |


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






























## Protected Attributes inherited from SR_UTILS_NS::Transform

See [SR\_UTILS\_NS::Transform](classSR__UTILS__NS_1_1Transform.md)

| Type | Name |
| ---: | :--- |
|  [**GameObject**](classSR__UTILS__NS_1_1GameObject.md) \* | [**m\_gameObject**](classSR__UTILS__NS_1_1Transform.md#variable-m_gameobject)   = `nullptr`<br> |








## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |
























































































## Protected Functions inherited from SR_UTILS_NS::Transform

See [SR\_UTILS\_NS::Transform](classSR__UTILS__NS_1_1Transform.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**UpdateMatrix**](classSR__UTILS__NS_1_1Transform.md#function-updatematrix) () const<br> |






















## Public Functions Documentation




### function GetMeasurement 

```C++
inline virtual SR_NODISCARD Measurement SR_UTILS_NS::TransformZero::GetMeasurement () override const
```



Implements [*SR\_UTILS\_NS::Transform::GetMeasurement*](classSR__UTILS__NS_1_1Transform.md#function-getmeasurement)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/ECS/TransformZero.h`

