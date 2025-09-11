

# Class SR\_UTILS\_NS::Transform2D



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Transform2D**](classSR__UTILS__NS_1_1Transform2D.md)








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




























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  SR\_INLINE constexpr SR\_MATH\_NS::FVector2 | [**RIGHT**](#variable-right)   = `Math::FVector2(1, 0)`<br> |
|  SR\_INLINE constexpr SR\_MATH\_NS::FVector2 | [**UP**](#variable-up)   = `Math::FVector2(0, 1)`<br> |




















































































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddModifier**](#function-addmodifier) ([**UI::UIModifierComponent**](classSR__UTILS__NS_1_1UI_1_1UIModifierComponent.md) \* pModifier) <br> |
|  SR\_NODISCARD int32\_t | [**GetLocalPriority**](#function-getlocalpriority) () noexcept const<br> |
| virtual SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetMatrix**](#function-getmatrix) () override const<br> |
| virtual SR\_NODISCARD Measurement | [**GetMeasurement**](#function-getmeasurement) () override const<br> |
|  SR\_NODISCARD int32\_t | [**GetPriority**](#function-getpriority) () <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetRotation**](#function-getrotation) () override const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetScale**](#function-getscale) () override const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetSkew**](#function-getskew) () override const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetTranslation**](#function-gettranslation) () override const<br> |
|  SR\_NODISCARD bool | [**IsRelativePriority**](#function-isrelativepriority) () noexcept const<br> |
| virtual void | [**OnHierarchyChanged**](#function-onhierarchychanged) () override<br> |
|  void | [**OnUITreeChanged**](#function-onuitreechanged) () <br> |
|  void | [**RemoveModifier**](#function-removemodifier) ([**UI::UIModifierComponent**](classSR__UTILS__NS_1_1UI_1_1UIModifierComponent.md) \* pModifier) <br> |
| virtual void | [**Rotate**](#function-rotate) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) override<br> |
| virtual void | [**Scale**](#function-scale) (const SR\_MATH\_NS::FVector3 & scale) override<br> |
| virtual void | [**SetGlobalRotation**](#function-setglobalrotation) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) override<br> |
| virtual void | [**SetGlobalTranslation**](#function-setglobaltranslation) (const SR\_MATH\_NS::FVector3 & translation) override<br> |
|  void | [**SetLocalPriority**](#function-setlocalpriority) (int32\_t priority) <br> |
|  void | [**SetRelativePriority**](#function-setrelativepriority) (bool relative) <br> |
| virtual void | [**SetRotation**](#function-setrotation-12) (const SR\_MATH\_NS::FVector3 & euler) override<br> |
| virtual void | [**SetRotation**](#function-setrotation-22) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) override<br> |
| virtual void | [**SetScale**](#function-setscale) (const SR\_MATH\_NS::FVector3 & scale) override<br> |
| virtual void | [**SetSkew**](#function-setskew) (const SR\_MATH\_NS::FVector3 & skew) override<br> |
| virtual void | [**SetTranslation**](#function-settranslation) (const SR\_MATH\_NS::FVector3 & translation) override<br> |
| virtual void | [**SetTranslationAndRotation**](#function-settranslationandrotation) (const SR\_MATH\_NS::FVector3 & translation, const SR\_MATH\_NS::FVector3 & euler) override<br> |
|   | [**Transform2D**](#function-transform2d) () <br> |
| virtual void | [**Translate**](#function-translate) (const SR\_MATH\_NS::FVector3 & translation) override<br> |


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
| virtual void | [**CloneTo**](classSR__UTILS__NS_1_1SRClass.md#function-cloneto) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) & clone) const<br> |
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




























## Protected Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FSize2 | [**m\_contentSize**](#variable-m_contentsize)  <br> |
|  bool | [**m\_isDirtyPriority**](#variable-m_isdirtypriority)   = `true`<br> |
|  [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**m\_localMatrix**](#variable-m_localmatrix)   = `SR\_MATH\_NS::Matrix4x4::Identity()`<br> |
|  int32\_t | [**m\_localPriority**](#variable-m_localpriority)   = `0`<br> |
|  [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**m\_matrix**](#variable-m_matrix)   = `SR\_MATH\_NS::Matrix4x4::Identity()`<br> |
|  std::vector&lt; [**UI::UIModifierComponent**](classSR__UTILS__NS_1_1UI_1_1UIModifierComponent.md) \* &gt; | [**m\_modifiers**](#variable-m_modifiers)  <br> |
|  int32\_t | [**m\_priority**](#variable-m_priority)   = `0`<br> |
|  [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**m\_quaternion**](#variable-m_quaternion)   = `SR\_MATH\_NS::Quaternion::Identity()`<br> |
|  bool | [**m\_relativePriority**](#variable-m_relativepriority)   = `true`<br> |
|  SR\_MATH\_NS::FVector3 | [**m\_rotation**](#variable-m_rotation)   = `SR\_MATH\_NS::FVector3::Zero()`<br> |
|  SR\_MATH\_NS::FVector3 | [**m\_scale**](#variable-m_scale)   = `SR\_MATH\_NS::FVector3::One()`<br> |
|  SR\_MATH\_NS::FVector3 | [**m\_skew**](#variable-m_skew)   = `SR\_MATH\_NS::FVector3::One()`<br> |
|  SR\_MATH\_NS::FVector3 | [**m\_translation**](#variable-m_translation)   = `SR\_MATH\_NS::FVector3::Zero()`<br> |


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






















































































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**BuildUITree**](#function-builduitree) () <br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetSize**](#function-getsize) () const<br> |
| virtual void | [**UpdateMatrix**](#function-updatematrix) () override const<br> |


## Protected Functions inherited from SR_UTILS_NS::Transform

See [SR\_UTILS\_NS::Transform](classSR__UTILS__NS_1_1Transform.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**UpdateMatrix**](classSR__UTILS__NS_1_1Transform.md#function-updatematrix) () const<br> |






















## Public Static Attributes Documentation




### variable RIGHT 

```C++
SR_INLINE constexpr SR_MATH_NS::FVector2 SR_UTILS_NS::Transform2D::RIGHT;
```




<hr>



### variable UP 

```C++
SR_INLINE constexpr SR_MATH_NS::FVector2 SR_UTILS_NS::Transform2D::UP;
```




<hr>
## Public Functions Documentation




### function AddModifier 

```C++
inline void SR_UTILS_NS::Transform2D::AddModifier (
    UI::UIModifierComponent * pModifier
) 
```




<hr>



### function GetLocalPriority 

```C++
inline SR_NODISCARD int32_t SR_UTILS_NS::Transform2D::GetLocalPriority () noexcept const
```




<hr>



### function GetMatrix 

```C++
virtual SR_NODISCARD const SR_MATH_NS::Matrix4x4 & SR_UTILS_NS::Transform2D::GetMatrix () override const
```



Implements [*SR\_UTILS\_NS::Transform::GetMatrix*](classSR__UTILS__NS_1_1Transform.md#function-getmatrix)


<hr>



### function GetMeasurement 

```C++
inline virtual SR_NODISCARD Measurement SR_UTILS_NS::Transform2D::GetMeasurement () override const
```



Implements [*SR\_UTILS\_NS::Transform::GetMeasurement*](classSR__UTILS__NS_1_1Transform.md#function-getmeasurement)


<hr>



### function GetPriority 

```C++
SR_NODISCARD int32_t SR_UTILS_NS::Transform2D::GetPriority () 
```




<hr>



### function GetRotation 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform2D::GetRotation () override const
```



Implements [*SR\_UTILS\_NS::Transform::GetRotation*](classSR__UTILS__NS_1_1Transform.md#function-getrotation)


<hr>



### function GetScale 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform2D::GetScale () override const
```



Implements [*SR\_UTILS\_NS::Transform::GetScale*](classSR__UTILS__NS_1_1Transform.md#function-getscale)


<hr>



### function GetSkew 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform2D::GetSkew () override const
```



Implements [*SR\_UTILS\_NS::Transform::GetSkew*](classSR__UTILS__NS_1_1Transform.md#function-getskew)


<hr>



### function GetTranslation 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::Transform2D::GetTranslation () override const
```



Implements [*SR\_UTILS\_NS::Transform::GetTranslation*](classSR__UTILS__NS_1_1Transform.md#function-gettranslation)


<hr>



### function IsRelativePriority 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Transform2D::IsRelativePriority () noexcept const
```




<hr>



### function OnHierarchyChanged 

```C++
virtual void SR_UTILS_NS::Transform2D::OnHierarchyChanged () override
```



Implements [*SR\_UTILS\_NS::Transform::OnHierarchyChanged*](classSR__UTILS__NS_1_1Transform.md#function-onhierarchychanged)


<hr>



### function OnUITreeChanged 

```C++
void SR_UTILS_NS::Transform2D::OnUITreeChanged () 
```




<hr>



### function RemoveModifier 

```C++
void SR_UTILS_NS::Transform2D::RemoveModifier (
    UI::UIModifierComponent * pModifier
) 
```




<hr>



### function Rotate 

```C++
virtual void SR_UTILS_NS::Transform2D::Rotate (
    const SR_MATH_NS::Quaternion & quaternion
) override
```



Implements [*SR\_UTILS\_NS::Transform::Rotate*](classSR__UTILS__NS_1_1Transform.md#function-rotate-23)


<hr>



### function Scale 

```C++
virtual void SR_UTILS_NS::Transform2D::Scale (
    const SR_MATH_NS::FVector3 & scale
) override
```



Implements [*SR\_UTILS\_NS::Transform::Scale*](classSR__UTILS__NS_1_1Transform.md#function-scale-12)


<hr>



### function SetGlobalRotation 

```C++
virtual void SR_UTILS_NS::Transform2D::SetGlobalRotation (
    const SR_MATH_NS::Quaternion & quaternion
) override
```



Implements [*SR\_UTILS\_NS::Transform::SetGlobalRotation*](classSR__UTILS__NS_1_1Transform.md#function-setglobalrotation-22)


<hr>



### function SetGlobalTranslation 

```C++
virtual void SR_UTILS_NS::Transform2D::SetGlobalTranslation (
    const SR_MATH_NS::FVector3 & translation
) override
```



Implements [*SR\_UTILS\_NS::Transform::SetGlobalTranslation*](classSR__UTILS__NS_1_1Transform.md#function-setglobaltranslation)


<hr>



### function SetLocalPriority 

```C++
void SR_UTILS_NS::Transform2D::SetLocalPriority (
    int32_t priority
) 
```




<hr>



### function SetRelativePriority 

```C++
void SR_UTILS_NS::Transform2D::SetRelativePriority (
    bool relative
) 
```




<hr>



### function SetRotation [1/2]

```C++
virtual void SR_UTILS_NS::Transform2D::SetRotation (
    const SR_MATH_NS::FVector3 & euler
) override
```



Implements [*SR\_UTILS\_NS::Transform::SetRotation*](classSR__UTILS__NS_1_1Transform.md#function-setrotation-13)


<hr>



### function SetRotation [2/2]

```C++
virtual void SR_UTILS_NS::Transform2D::SetRotation (
    const SR_MATH_NS::Quaternion & quaternion
) override
```



Implements [*SR\_UTILS\_NS::Transform::SetRotation*](classSR__UTILS__NS_1_1Transform.md#function-setrotation-23)


<hr>



### function SetScale 

```C++
virtual void SR_UTILS_NS::Transform2D::SetScale (
    const SR_MATH_NS::FVector3 & scale
) override
```



Implements [*SR\_UTILS\_NS::Transform::SetScale*](classSR__UTILS__NS_1_1Transform.md#function-setscale-12)


<hr>



### function SetSkew 

```C++
virtual void SR_UTILS_NS::Transform2D::SetSkew (
    const SR_MATH_NS::FVector3 & skew
) override
```



Implements [*SR\_UTILS\_NS::Transform::SetSkew*](classSR__UTILS__NS_1_1Transform.md#function-setskew-12)


<hr>



### function SetTranslation 

```C++
virtual void SR_UTILS_NS::Transform2D::SetTranslation (
    const SR_MATH_NS::FVector3 & translation
) override
```



Implements [*SR\_UTILS\_NS::Transform::SetTranslation*](classSR__UTILS__NS_1_1Transform.md#function-settranslation-12)


<hr>



### function SetTranslationAndRotation 

```C++
virtual void SR_UTILS_NS::Transform2D::SetTranslationAndRotation (
    const SR_MATH_NS::FVector3 & translation,
    const SR_MATH_NS::FVector3 & euler
) override
```



Implements [*SR\_UTILS\_NS::Transform::SetTranslationAndRotation*](classSR__UTILS__NS_1_1Transform.md#function-settranslationandrotation)


<hr>



### function Transform2D 

```C++
SR_UTILS_NS::Transform2D::Transform2D () 
```




<hr>



### function Translate 

```C++
virtual void SR_UTILS_NS::Transform2D::Translate (
    const SR_MATH_NS::FVector3 & translation
) override
```



Implements [*SR\_UTILS\_NS::Transform::Translate*](classSR__UTILS__NS_1_1Transform.md#function-translate-12)


<hr>
## Protected Attributes Documentation




### variable m\_contentSize 

```C++
SR_MATH_NS::FSize2 SR_UTILS_NS::Transform2D::m_contentSize;
```




<hr>



### variable m\_isDirtyPriority 

```C++
bool SR_UTILS_NS::Transform2D::m_isDirtyPriority;
```




<hr>



### variable m\_localMatrix 

```C++
SR_MATH_NS::Matrix4x4 SR_UTILS_NS::Transform2D::m_localMatrix;
```




<hr>



### variable m\_localPriority 

```C++
int32_t SR_UTILS_NS::Transform2D::m_localPriority;
```




<hr>



### variable m\_matrix 

```C++
SR_MATH_NS::Matrix4x4 SR_UTILS_NS::Transform2D::m_matrix;
```




<hr>



### variable m\_modifiers 

```C++
std::vector<UI::UIModifierComponent*> SR_UTILS_NS::Transform2D::m_modifiers;
```




<hr>



### variable m\_priority 

```C++
int32_t SR_UTILS_NS::Transform2D::m_priority;
```




<hr>



### variable m\_quaternion 

```C++
SR_MATH_NS::Quaternion SR_UTILS_NS::Transform2D::m_quaternion;
```




<hr>



### variable m\_relativePriority 

```C++
bool SR_UTILS_NS::Transform2D::m_relativePriority;
```




<hr>



### variable m\_rotation 

```C++
SR_MATH_NS::FVector3 SR_UTILS_NS::Transform2D::m_rotation;
```




<hr>



### variable m\_scale 

```C++
SR_MATH_NS::FVector3 SR_UTILS_NS::Transform2D::m_scale;
```




<hr>



### variable m\_skew 

```C++
SR_MATH_NS::FVector3 SR_UTILS_NS::Transform2D::m_skew;
```




<hr>



### variable m\_translation 

```C++
SR_MATH_NS::FVector3 SR_UTILS_NS::Transform2D::m_translation;
```




<hr>
## Protected Functions Documentation




### function BuildUITree 

```C++
void SR_UTILS_NS::Transform2D::BuildUITree () 
```




<hr>



### function GetSize 

```C++
SR_NODISCARD SR_MATH_NS::FVector2 SR_UTILS_NS::Transform2D::GetSize () const
```




<hr>



### function UpdateMatrix 

```C++
virtual void SR_UTILS_NS::Transform2D::UpdateMatrix () override const
```



Implements [*SR\_UTILS\_NS::Transform::UpdateMatrix*](classSR__UTILS__NS_1_1Transform.md#function-updatematrix)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/ECS/Transform2D.h`

