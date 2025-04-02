

# Struct SR\_UTILS\_NS::EntityRefUtils::OwnerRef



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**EntityRefUtils**](namespaceSR__UTILS__NS_1_1EntityRefUtils.md) **>** [**OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; Entity &gt; | [**pEntity**](#variable-pentity)  <br>_NOLINT._  |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**pScene**](#variable-pscene)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**OwnerRef**](#function-ownerref-13) () = default<br> |
|  SR\_MAYBE\_UNUSED | [**OwnerRef**](#function-ownerref-23) (const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; Entity &gt; & ptr) <br> |
|  SR\_MAYBE\_UNUSED | [**OwnerRef**](#function-ownerref-33) (const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; & ptr) <br>_NOLINT._  |




























## Public Attributes Documentation




### variable pEntity 

_NOLINT._ 
```C++
SR_HTYPES_NS::SharedPtr<Entity> SR_UTILS_NS::EntityRefUtils::OwnerRef::pEntity;
```




<hr>



### variable pScene 

```C++
SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene> SR_UTILS_NS::EntityRefUtils::OwnerRef::pScene;
```




<hr>
## Public Functions Documentation




### function OwnerRef [1/3]

```C++
SR_UTILS_NS::EntityRefUtils::OwnerRef::OwnerRef () = default
```




<hr>



### function OwnerRef [2/3]

```C++
SR_MAYBE_UNUSED SR_UTILS_NS::EntityRefUtils::OwnerRef::OwnerRef (
    const SR_HTYPES_NS::SharedPtr < Entity > & ptr
) 
```




<hr>



### function OwnerRef [3/3]

_NOLINT._ 
```C++
SR_MAYBE_UNUSED SR_UTILS_NS::EntityRefUtils::OwnerRef::OwnerRef (
    const SR_HTYPES_NS::SharedPtr < SR_WORLD_NS::Scene > & ptr
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/ECS/EntityRefUtils.h`

