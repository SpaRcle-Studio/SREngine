

# Class SR\_UTILS\_NS::PropertyContainer



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md)








Inherits the following classes: [SR\_UTILS\_NS::Property](classSR__UTILS__NS_1_1Property.md)


Inherited by the following classes: [SR\_GRAPH\_NS::MaterialProperties](classSR__GRAPH__NS_1_1MaterialProperties.md)














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
|  [**ArrayReferenceProperty**](classSR__UTILS__NS_1_1ArrayReferenceProperty.md) & | [**AddArrayReferenceProperty**](#function-addarrayreferenceproperty) (const char \* name) <br> |
|  [**PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md) & | [**AddContainer**](#function-addcontainer) (const char \* name) <br> |
|  T & | [**AddCustomProperty**](#function-addcustomproperty) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, Args... args) <br> |
|  [**EntityRefProperty**](classSR__UTILS__NS_1_1EntityRefProperty.md) & | [**AddEntityRefProperty**](#function-addentityrefproperty) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, const [**EntityRefUtils::OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & owner) <br> |
|  [**EnumProperty**](classSR__UTILS__NS_1_1EnumProperty.md) & | [**AddEnumProperty**](#function-addenumproperty-12) (const char \* name, T \* pRawProperty) <br> |
|  [**EnumProperty**](classSR__UTILS__NS_1_1EnumProperty.md) & | [**AddEnumProperty**](#function-addenumproperty-22) (const char \* name) <br> |
|  void | [**AddExternalProperty**](#function-addexternalproperty) ([**Property**](classSR__UTILS__NS_1_1Property.md) \* pProperty) <br> |
|  [**StandardProperty**](classSR__UTILS__NS_1_1StandardProperty.md) & | [**AddStandardProperty**](#function-addstandardproperty-12) (const char \* name) <br> |
|  [**StandardProperty**](classSR__UTILS__NS_1_1StandardProperty.md) & | [**AddStandardProperty**](#function-addstandardproperty-22) (const char \* name, T \* pRawProperty) <br> |
| virtual void | [**ClearContainer**](#function-clearcontainer) () <br> |
|  SR\_NODISCARD T \* | [**Find**](#function-find-14) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) noexcept const<br> |
|  SR\_NODISCARD T \* | [**Find**](#function-find-24) (uint64\_t hashName) noexcept const<br> |
|  T \* | [**Find**](#function-find-34) (uint64\_t hashName) noexcept const<br> |
|  T \* | [**Find**](#function-find-44) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) noexcept const<br> |
|  [**PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md) & | [**ForEachProperty**](#function-foreachproperty-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*)&gt; & function) <br> |
|  const [**PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md) & | [**ForEachProperty**](#function-foreachproperty-22) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*)&gt; & function) const<br> |
|  bool | [**ForEachPropertyRet**](#function-foreachpropertyret) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool(T \*)&gt; & function) const<br> |
|  SR\_NODISCARD PropertyList & | [**GetProperties**](#function-getproperties-12) () noexcept<br> |
|  SR\_NODISCARD const PropertyList & | [**GetProperties**](#function-getproperties-22) () noexcept const<br> |
| virtual void | [**LoadProperty**](#function-loadproperty) (MarshalRef marshal) noexcept override<br> |
| virtual void | [**OnPropertyAdded**](#function-onpropertyadded) ([**Property**](classSR__UTILS__NS_1_1Property.md) \* pProprerty) <br> |
|   | [**PropertyContainer**](#function-propertycontainer) () <br> |
| virtual void | [**SaveProperty**](#function-saveproperty) (MarshalRef marshal) noexcept override const<br> |
|  void | [**SetShowErrors**](#function-setshowerrors) (bool value) noexcept<br> |
|   | [**~PropertyContainer**](#function-propertycontainer) () override<br> |


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
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |








## Public Functions Documentation




### function AddArrayReferenceProperty 

```C++
ArrayReferenceProperty & SR_UTILS_NS::PropertyContainer::AddArrayReferenceProperty (
    const char * name
) 
```




<hr>



### function AddContainer 

```C++
PropertyContainer & SR_UTILS_NS::PropertyContainer::AddContainer (
    const char * name
) 
```




<hr>



### function AddCustomProperty 

```C++
template<typename T, typename ... Args>
T & SR_UTILS_NS::PropertyContainer::AddCustomProperty (
    SR_UTILS_NS::StringAtom name,
    Args... args
) 
```




<hr>



### function AddEntityRefProperty 

```C++
EntityRefProperty & SR_UTILS_NS::PropertyContainer::AddEntityRefProperty (
    SR_UTILS_NS::StringAtom name,
    const EntityRefUtils::OwnerRef & owner
) 
```




<hr>



### function AddEnumProperty [1/2]

```C++
template<typename T>
EnumProperty & SR_UTILS_NS::PropertyContainer::AddEnumProperty (
    const char * name,
    T * pRawProperty
) 
```




<hr>



### function AddEnumProperty [2/2]

```C++
template<typename T>
EnumProperty & SR_UTILS_NS::PropertyContainer::AddEnumProperty (
    const char * name
) 
```




<hr>



### function AddExternalProperty 

```C++
void SR_UTILS_NS::PropertyContainer::AddExternalProperty (
    Property * pProperty
) 
```




<hr>



### function AddStandardProperty [1/2]

```C++
template<typename T>
StandardProperty & SR_UTILS_NS::PropertyContainer::AddStandardProperty (
    const char * name
) 
```




<hr>



### function AddStandardProperty [2/2]

```C++
template<typename T>
StandardProperty & SR_UTILS_NS::PropertyContainer::AddStandardProperty (
    const char * name,
    T * pRawProperty
) 
```




<hr>



### function ClearContainer 

```C++
virtual void SR_UTILS_NS::PropertyContainer::ClearContainer () 
```




<hr>



### function Find [1/4]

```C++
template<typename T>
SR_NODISCARD T * SR_UTILS_NS::PropertyContainer::Find (
    const SR_UTILS_NS::StringAtom & name
) noexcept const
```




<hr>



### function Find [2/4]

```C++
template<typename T>
SR_NODISCARD T * SR_UTILS_NS::PropertyContainer::Find (
    uint64_t hashName
) noexcept const
```




<hr>



### function Find [3/4]

```C++
template<typename T>
T * SR_UTILS_NS::PropertyContainer::Find (
    uint64_t hashName
) noexcept const
```




<hr>



### function Find [4/4]

```C++
template<typename T>
T * SR_UTILS_NS::PropertyContainer::Find (
    const StringAtom & name
) noexcept const
```




<hr>



### function ForEachProperty [1/2]

```C++
template<typename T>
PropertyContainer & SR_UTILS_NS::PropertyContainer::ForEachProperty (
    const SR_HTYPES_NS::Function < void(T *)> & function
) 
```




<hr>



### function ForEachProperty [2/2]

```C++
template<typename T>
const PropertyContainer & SR_UTILS_NS::PropertyContainer::ForEachProperty (
    const SR_HTYPES_NS::Function < void(T *)> & function
) const
```




<hr>



### function ForEachPropertyRet 

```C++
template<typename T>
bool SR_UTILS_NS::PropertyContainer::ForEachPropertyRet (
    const SR_HTYPES_NS::Function < bool(T *)> & function
) const
```




<hr>



### function GetProperties [1/2]

```C++
inline SR_NODISCARD PropertyList & SR_UTILS_NS::PropertyContainer::GetProperties () noexcept
```




<hr>



### function GetProperties [2/2]

```C++
inline SR_NODISCARD const PropertyList & SR_UTILS_NS::PropertyContainer::GetProperties () noexcept const
```




<hr>



### function LoadProperty 

```C++
virtual void SR_UTILS_NS::PropertyContainer::LoadProperty (
    MarshalRef marshal
) noexcept override
```



Implements [*SR\_UTILS\_NS::Property::LoadProperty*](classSR__UTILS__NS_1_1Property.md#function-loadproperty)


<hr>



### function OnPropertyAdded 

```C++
inline virtual void SR_UTILS_NS::PropertyContainer::OnPropertyAdded (
    Property * pProprerty
) 
```




<hr>



### function PropertyContainer 

```C++
SR_UTILS_NS::PropertyContainer::PropertyContainer () 
```




<hr>



### function SaveProperty 

```C++
virtual void SR_UTILS_NS::PropertyContainer::SaveProperty (
    MarshalRef marshal
) noexcept override const
```



Implements [*SR\_UTILS\_NS::Property::SaveProperty*](classSR__UTILS__NS_1_1Property.md#function-saveproperty)


<hr>



### function SetShowErrors 

```C++
inline void SR_UTILS_NS::PropertyContainer::SetShowErrors (
    bool value
) noexcept
```




<hr>



### function ~PropertyContainer 

```C++
SR_UTILS_NS::PropertyContainer::~PropertyContainer () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/Properties.h`

