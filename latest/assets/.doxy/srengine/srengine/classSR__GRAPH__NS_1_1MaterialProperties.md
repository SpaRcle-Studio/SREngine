

# Class SR\_GRAPH\_NS::MaterialProperties



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**MaterialProperties**](classSR__GRAPH__NS_1_1MaterialProperties.md)








Inherits the following classes: [SR\_UTILS\_NS::PropertyContainer](classSR__UTILS__NS_1_1PropertyContainer.md)


















## Public Types inherited from SR_UTILS_NS::Property

See [SR\_UTILS\_NS::Property](classSR__UTILS__NS_1_1Property.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool()&gt; | [**ActiveConditionFn**](classSR__UTILS__NS_1_1Property.md#typedef-activeconditionfn)  <br> |
| typedef [**Property**](classSR__UTILS__NS_1_1Property.md) | [**Base**](classSR__UTILS__NS_1_1Property.md#typedef-base)  <br> |
| typedef SR\_HTYPES\_NS::Marshal::Ptr | [**MarshalPtr**](classSR__UTILS__NS_1_1Property.md#typedef-marshalptr)  <br> |
| typedef [**SR\_HTYPES\_NS::Marshal**](classSR__HTYPES__NS_1_1Marshal.md) & | [**MarshalRef**](classSR__UTILS__NS_1_1Property.md#typedef-marshalref)  <br> |
| typedef std::unique\_ptr&lt; [**SR\_HTYPES\_NS::Marshal**](classSR__HTYPES__NS_1_1Marshal.md) &gt; | [**MarshalUniquePtr**](classSR__UTILS__NS_1_1Property.md#typedef-marshaluniqueptr)  <br> |












































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**ClearContainer**](#function-clearcontainer) () override<br> |
|  const std::vector&lt; [**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md) \* &gt; & | [**GetMaterialSamplerProperties**](#function-getmaterialsamplerproperties) () noexcept const<br> |
|  const std::vector&lt; [**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md) \* &gt; & | [**GetMaterialUniformsProperties**](#function-getmaterialuniformsproperties) () noexcept const<br> |
|   | [**MaterialProperties**](#function-materialproperties) () = default<br> |
| virtual void | [**OnPropertyAdded**](#function-onpropertyadded) ([**SR\_UTILS\_NS::Property**](classSR__UTILS__NS_1_1Property.md) \* pProperty) override<br> |
|  void | [**UseMaterialSamplers**](#function-usematerialsamplers) ([**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) <br> |
|  void | [**UseMaterialUniforms**](#function-usematerialuniforms) ([**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) <br> |


## Public Functions inherited from SR_UTILS_NS::PropertyContainer

See [SR\_UTILS\_NS::PropertyContainer](classSR__UTILS__NS_1_1PropertyContainer.md)

| Type | Name |
| ---: | :--- |
|  [**ArrayReferenceProperty**](classSR__UTILS__NS_1_1ArrayReferenceProperty.md) & | [**AddArrayReferenceProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-addarrayreferenceproperty) (const char \* name) <br> |
|  [**PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md) & | [**AddContainer**](classSR__UTILS__NS_1_1PropertyContainer.md#function-addcontainer) (const char \* name) <br> |
|  T & | [**AddCustomProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-addcustomproperty) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, Args... args) <br> |
|  [**EntityRefProperty**](classSR__UTILS__NS_1_1EntityRefProperty.md) & | [**AddEntityRefProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-addentityrefproperty) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, const [**EntityRefUtils::OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & owner) <br> |
|  [**EnumProperty**](classSR__UTILS__NS_1_1EnumProperty.md) & | [**AddEnumProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-addenumproperty-12) (const char \* name, T \* pRawProperty) <br> |
|  [**EnumProperty**](classSR__UTILS__NS_1_1EnumProperty.md) & | [**AddEnumProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-addenumproperty-22) (const char \* name) <br> |
|  void | [**AddExternalProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-addexternalproperty) ([**Property**](classSR__UTILS__NS_1_1Property.md) \* pProperty) <br> |
|  [**StandardProperty**](classSR__UTILS__NS_1_1StandardProperty.md) & | [**AddStandardProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-addstandardproperty-12) (const char \* name) <br> |
|  [**StandardProperty**](classSR__UTILS__NS_1_1StandardProperty.md) & | [**AddStandardProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-addstandardproperty-22) (const char \* name, T \* pRawProperty) <br> |
| virtual void | [**ClearContainer**](classSR__UTILS__NS_1_1PropertyContainer.md#function-clearcontainer) () <br> |
|  SR\_NODISCARD T \* | [**Find**](classSR__UTILS__NS_1_1PropertyContainer.md#function-find-14) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) noexcept const<br> |
|  SR\_NODISCARD T \* | [**Find**](classSR__UTILS__NS_1_1PropertyContainer.md#function-find-24) (uint64\_t hashName) noexcept const<br> |
|  T \* | [**Find**](classSR__UTILS__NS_1_1PropertyContainer.md#function-find-34) (uint64\_t hashName) noexcept const<br> |
|  T \* | [**Find**](classSR__UTILS__NS_1_1PropertyContainer.md#function-find-44) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) noexcept const<br> |
|  [**PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md) & | [**ForEachProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-foreachproperty-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*)&gt; & function) <br> |
|  const [**PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md) & | [**ForEachProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-foreachproperty-22) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*)&gt; & function) const<br> |
|  bool | [**ForEachPropertyRet**](classSR__UTILS__NS_1_1PropertyContainer.md#function-foreachpropertyret) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool(T \*)&gt; & function) const<br> |
|  SR\_NODISCARD PropertyList & | [**GetProperties**](classSR__UTILS__NS_1_1PropertyContainer.md#function-getproperties-12) () noexcept<br> |
|  SR\_NODISCARD const PropertyList & | [**GetProperties**](classSR__UTILS__NS_1_1PropertyContainer.md#function-getproperties-22) () noexcept const<br> |
| virtual void | [**LoadProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-loadproperty) (MarshalRef marshal) noexcept override<br> |
| virtual void | [**OnPropertyAdded**](classSR__UTILS__NS_1_1PropertyContainer.md#function-onpropertyadded) ([**Property**](classSR__UTILS__NS_1_1Property.md) \* pProprerty) <br> |
|   | [**PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md#function-propertycontainer) () <br> |
| virtual void | [**SaveProperty**](classSR__UTILS__NS_1_1PropertyContainer.md#function-saveproperty) (MarshalRef marshal) noexcept override const<br> |
|  void | [**SetShowErrors**](classSR__UTILS__NS_1_1PropertyContainer.md#function-setshowerrors) (bool value) noexcept<br> |
|   | [**~PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md#function-propertycontainer) () override<br> |


## Public Functions inherited from SR_UTILS_NS::Property

See [SR\_UTILS\_NS::Property](classSR__UTILS__NS_1_1Property.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](classSR__UTILS__NS_1_1Property.md#function-getname) () noexcept const<br> |
|  SR\_NODISCARD bool | [**GetOptional**](classSR__UTILS__NS_1_1Property.md#function-getoptional) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetPropertyTypeName**](classSR__UTILS__NS_1_1Property.md#function-getpropertytypename) () noexcept const = 0<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetPropertyVersion**](classSR__UTILS__NS_1_1Property.md#function-getpropertyversion) () noexcept const = 0<br> |
|  SR\_NODISCARD PropertyPublicity | [**GetPublicity**](classSR__UTILS__NS_1_1Property.md#function-getpublicity) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetWidth**](classSR__UTILS__NS_1_1Property.md#function-getwidth) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsActive**](classSR__UTILS__NS_1_1Property.md#function-isactive) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsDontSave**](classSR__UTILS__NS_1_1Property.md#function-isdontsave) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsOptionalMode**](classSR__UTILS__NS_1_1Property.md#function-isoptionalmode) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsSameLine**](classSR__UTILS__NS_1_1Property.md#function-issameline) () noexcept const<br> |
| virtual void | [**LoadProperty**](classSR__UTILS__NS_1_1Property.md#function-loadproperty) (MarshalRef marshal) noexcept<br> |
|   | [**Property**](classSR__UTILS__NS_1_1Property.md#function-property-12) () = default<br> |
|   | [**Property**](classSR__UTILS__NS_1_1Property.md#function-property-22) ([**Property**](classSR__UTILS__NS_1_1Property.md) && other) noexcept<br> |
| virtual void | [**SaveProperty**](classSR__UTILS__NS_1_1Property.md#function-saveproperty) (MarshalRef marshal) noexcept const<br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetActiveCondition**](classSR__UTILS__NS_1_1Property.md#function-setactivecondition) (ActiveConditionFn value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetDontSave**](classSR__UTILS__NS_1_1Property.md#function-setdontsave) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetName**](classSR__UTILS__NS_1_1Property.md#function-setname) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetOptional**](classSR__UTILS__NS_1_1Property.md#function-setoptional) (bool value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetOptionalMode**](classSR__UTILS__NS_1_1Property.md#function-setoptionalmode) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetPublicity**](classSR__UTILS__NS_1_1Property.md#function-setpublicity) (PropertyPublicity publicity) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetReadOnly**](classSR__UTILS__NS_1_1Property.md#function-setreadonly) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetSameLine**](classSR__UTILS__NS_1_1Property.md#function-setsameline) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetWidth**](classSR__UTILS__NS_1_1Property.md#function-setwidth) (float\_t value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**operator=**](classSR__UTILS__NS_1_1Property.md#function-operator) ([**Property**](classSR__UTILS__NS_1_1Property.md) && other) noexcept<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






























































































## Protected Functions inherited from SR_UTILS_NS::Property

See [SR\_UTILS\_NS::Property](classSR__UTILS__NS_1_1Property.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD MarshalUniquePtr | [**AllocatePropertyBlock**](classSR__UTILS__NS_1_1Property.md#function-allocatepropertyblock) () const<br> |
|  SR\_NODISCARD MarshalUniquePtr | [**LoadPropertyBase**](classSR__UTILS__NS_1_1Property.md#function-loadpropertybase) (MarshalRef marshal) const<br> |
|  void | [**SavePropertyBase**](classSR__UTILS__NS_1_1Property.md#function-savepropertybase) (MarshalRef marshal, MarshalUniquePtr pBlock) const<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |










## Public Functions Documentation




### function ClearContainer 

```C++
inline virtual void SR_GRAPH_NS::MaterialProperties::ClearContainer () override
```



Implements [*SR\_UTILS\_NS::PropertyContainer::ClearContainer*](classSR__UTILS__NS_1_1PropertyContainer.md#function-clearcontainer)


<hr>



### function GetMaterialSamplerProperties 

```C++
inline const std::vector< MaterialProperty * > & SR_GRAPH_NS::MaterialProperties::GetMaterialSamplerProperties () noexcept const
```




<hr>



### function GetMaterialUniformsProperties 

```C++
inline const std::vector< MaterialProperty * > & SR_GRAPH_NS::MaterialProperties::GetMaterialUniformsProperties () noexcept const
```




<hr>



### function MaterialProperties 

```C++
SR_GRAPH_NS::MaterialProperties::MaterialProperties () = default
```




<hr>



### function OnPropertyAdded 

```C++
inline virtual void SR_GRAPH_NS::MaterialProperties::OnPropertyAdded (
    SR_UTILS_NS::Property * pProperty
) override
```



Implements [*SR\_UTILS\_NS::PropertyContainer::OnPropertyAdded*](classSR__UTILS__NS_1_1PropertyContainer.md#function-onpropertyadded)


<hr>



### function UseMaterialSamplers 

```C++
inline void SR_GRAPH_NS::MaterialProperties::UseMaterialSamplers (
    SR_GTYPES_NS::Shader * pShader
) 
```




<hr>



### function UseMaterialUniforms 

```C++
inline void SR_GRAPH_NS::MaterialProperties::UseMaterialUniforms (
    SR_GTYPES_NS::Shader * pShader
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Material/MaterialProperty.h`

