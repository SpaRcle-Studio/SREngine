

# Namespace SR\_UTILS\_NS::EntityRefUtils



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**EntityRefUtils**](namespaceSR__UTILS__NS_1_1EntityRefUtils.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) <br> |
| struct | [**PathItem**](structSR__UTILS__NS_1_1EntityRefUtils_1_1PathItem.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**PathItem**](structSR__UTILS__NS_1_1EntityRefUtils_1_1PathItem.md) &gt; | [**RefPath**](#typedef-refpath)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED RefPath | [**CalculatePath**](#function-calculatepath) (const [**OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & from) <br> |
|  SR\_MAYBE\_UNUSED RefPath | [**CalculateRelativePath**](#function-calculaterelativepath) (const [**OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & from, const [**OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & target) <br> |
|  SR\_MAYBE\_UNUSED [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; Entity &gt; | [**GetEntity**](#function-getentity) (const [**OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & owner, const RefPath & path) <br> |
|  SR\_MAYBE\_UNUSED [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**GetSceneFromOwner**](#function-getscenefromowner) (const [**OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & owner) <br> |
|  SR\_MAYBE\_UNUSED bool | [**IsOwnerValid**](#function-isownervalid) (const [**OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & owner) <br> |
|  SR\_MAYBE\_UNUSED bool | [**IsTargetInitialized**](#function-istargetinitialized) (const [**OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & owner) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (Action, uint8\_t, Action\_Parent, Action\_Child, Action\_Component) <br> |




























## Public Types Documentation




### typedef RefPath 

```C++
typedef std::vector<PathItem> SR_UTILS_NS::EntityRefUtils::RefPath;
```




<hr>
## Public Functions Documentation




### function CalculatePath 

```C++
SR_MAYBE_UNUSED RefPath SR_UTILS_NS::EntityRefUtils::CalculatePath (
    const OwnerRef & from
) 
```




<hr>



### function CalculateRelativePath 

```C++
SR_MAYBE_UNUSED RefPath SR_UTILS_NS::EntityRefUtils::CalculateRelativePath (
    const OwnerRef & from,
    const OwnerRef & target
) 
```




<hr>



### function GetEntity 

```C++
SR_MAYBE_UNUSED SR_HTYPES_NS::SharedPtr < Entity > SR_UTILS_NS::EntityRefUtils::GetEntity (
    const OwnerRef & owner,
    const RefPath & path
) 
```




<hr>



### function GetSceneFromOwner 

```C++
SR_MAYBE_UNUSED SR_HTYPES_NS::SharedPtr < SR_WORLD_NS::Scene > SR_UTILS_NS::EntityRefUtils::GetSceneFromOwner (
    const OwnerRef & owner
) 
```




<hr>



### function IsOwnerValid 

```C++
SR_MAYBE_UNUSED bool SR_UTILS_NS::EntityRefUtils::IsOwnerValid (
    const OwnerRef & owner
) 
```




<hr>



### function IsTargetInitialized 

```C++
SR_MAYBE_UNUSED bool SR_UTILS_NS::EntityRefUtils::IsTargetInitialized (
    const OwnerRef & owner
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_UTILS_NS::EntityRefUtils::SR_ENUM_NS_CLASS_T (
    Action,
    uint8_t,
    Action_Parent,
    Action_Child,
    Action_Component
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/ECS/EntityRefUtils.h`

