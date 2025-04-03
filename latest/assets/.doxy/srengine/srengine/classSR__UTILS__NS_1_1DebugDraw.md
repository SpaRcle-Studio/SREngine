

# Class SR\_UTILS\_NS::DebugDraw



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**DebugDraw**](classSR__UTILS__NS_1_1DebugDraw.md)



[More...](#detailed-description)

* `#include <DebugDraw.h>`



Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Callbacks**](structSR__UTILS__NS_1_1DebugDraw_1_1Callbacks.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef DrawCubeCallback | [**DrawCapsuleCallback**](#typedef-drawcapsulecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; uint64\_t(uint64\_t id, const SR\_MATH\_NS::FVector3 &pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) &rot, const SR\_MATH\_NS::FVector3 &scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) &color, float\_t time)&gt; | [**DrawCubeCallback**](#typedef-drawcubecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; uint64\_t(uint64\_t id, const SR\_MATH\_NS::FVector3 &start, const SR\_MATH\_NS::FVector3 &end, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) &color, float\_t time)&gt; | [**DrawLineCallback**](#typedef-drawlinecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; uint64\_t([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \*pRawMesh, int32\_t meshId, uint64\_t id, const SR\_MATH\_NS::FVector3 &pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) &rot, const SR\_MATH\_NS::FVector3 &scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) &color, float\_t time)&gt; | [**DrawMeshCallback**](#typedef-drawmeshcallback)  <br> |
| typedef DrawCubeCallback | [**DrawPlaneCallback**](#typedef-drawplanecallback)  <br> |
| typedef DrawCubeCallback | [**DrawSphereCallback**](#typedef-drawspherecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(uint64\_t id)&gt; | [**RemoveCallback**](#typedef-removecallback)  <br> |
























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**DEFAULT\_COLOR**](#variable-default_color)   = `[**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md)(255, 255, 255, 255)`<br> |
|  constexpr float\_t | [**DEFAULT\_DURATION**](#variable-default_duration)   = `10.f`<br> |
|  constexpr SR\_MATH\_NS::FVector3 | [**DEFAULT\_POSITION**](#variable-default_position)   = `SR\_MATH\_NS::FVector3::Zero()`<br> |
|  constexpr [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**DEFAULT\_QUATERNION**](#variable-default_quaternion)   = `SR\_MATH\_NS::Quaternion::Identity()`<br> |
|  constexpr SR\_MATH\_NS::FVector3 | [**DEFAULT\_SCALE**](#variable-default_scale)   = `SR\_MATH\_NS::FVector3::One()`<br> |
























































## Public Functions

| Type | Name |
| ---: | :--- |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-118) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-218) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-318) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-418) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-518) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-618) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-718) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, float\_t time) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-818) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-918) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-1018) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-1118) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-1218) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-1318) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-1418) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-1518) (const SR\_MATH\_NS::FVector3 & pos, float\_t time) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-1618) (const SR\_MATH\_NS::FVector3 & pos) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-1718) (uint64\_t id) <br> |
|  uint64\_t | [**DrawCapsule**](#function-drawcapsule-1818) () <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-118) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-218) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-318) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-418) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-518) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-618) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-718) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, float\_t time) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-818) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-918) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-1018) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-1118) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-1218) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-1318) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-1418) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-1518) (const SR\_MATH\_NS::FVector3 & pos, float\_t time) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-1618) (const SR\_MATH\_NS::FVector3 & pos) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-1718) (uint64\_t id) <br> |
|  uint64\_t | [**DrawCube**](#function-drawcube-1818) () <br> |
|  uint64\_t | [**DrawLine**](#function-drawline-110) (uint64\_t id, const SR\_MATH\_NS::FVector3 & start, const SR\_MATH\_NS::FVector3 & end, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawLine**](#function-drawline-210) (uint64\_t id, const SR\_MATH\_NS::FVector3 & start, const SR\_MATH\_NS::FVector3 & end, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawLine**](#function-drawline-310) (uint64\_t id, const SR\_MATH\_NS::FVector3 & start, const SR\_MATH\_NS::FVector3 & end, float\_t time) <br> |
|  uint64\_t | [**DrawLine**](#function-drawline-410) (uint64\_t id, const SR\_MATH\_NS::FVector3 & start, const SR\_MATH\_NS::FVector3 & end) <br> |
|  uint64\_t | [**DrawLine**](#function-drawline-510) (const SR\_MATH\_NS::FVector3 & start, const SR\_MATH\_NS::FVector3 & end, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawLine**](#function-drawline-610) (const SR\_MATH\_NS::FVector3 & start, const SR\_MATH\_NS::FVector3 & end, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawLine**](#function-drawline-710) (const SR\_MATH\_NS::FVector3 & start, const SR\_MATH\_NS::FVector3 & end, float\_t time) <br> |
|  uint64\_t | [**DrawLine**](#function-drawline-810) (const SR\_MATH\_NS::FVector3 & start, const SR\_MATH\_NS::FVector3 & end) <br> |
|  uint64\_t | [**DrawLine**](#function-drawline-910) (uint64\_t id) <br> |
|  uint64\_t | [**DrawLine**](#function-drawline-1010) () <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-118) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-218) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-318) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-418) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-518) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-618) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-718) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, float\_t time) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-818) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, uint64\_t id, const SR\_MATH\_NS::FVector3 & pos) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-918) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-1018) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-1118) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-1218) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-1318) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-1418) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-1518) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, const SR\_MATH\_NS::FVector3 & pos, float\_t time) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-1618) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, const SR\_MATH\_NS::FVector3 & pos) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-1718) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId, uint64\_t id) <br> |
|  uint64\_t | [**DrawMesh**](#function-drawmesh-1818) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, int32\_t meshId) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-118) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-218) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-318) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-418) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-518) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-618) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-718) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, float\_t time) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-818) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-918) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-1018) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-1118) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-1218) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-1318) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-1418) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-1518) (const SR\_MATH\_NS::FVector3 & pos, float\_t time) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-1618) (const SR\_MATH\_NS::FVector3 & pos) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-1718) (uint64\_t id) <br> |
|  uint64\_t | [**DrawPlane**](#function-drawplane-1818) () <br> |
|  void | [**DrawQuaternion**](#function-drawquaternion) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-118) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-218) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-318) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-418) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-518) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-618) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-718) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos, float\_t time) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-818) (uint64\_t id, const SR\_MATH\_NS::FVector3 & pos) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-918) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-1018) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-1118) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-1218) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rot) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-1318) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color, float\_t time) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-1418) (const SR\_MATH\_NS::FVector3 & pos, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-1518) (const SR\_MATH\_NS::FVector3 & pos, float\_t time) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-1618) (const SR\_MATH\_NS::FVector3 & pos) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-1718) (uint64\_t id) <br> |
|  uint64\_t | [**DrawSphere**](#function-drawsphere-1818) () <br> |
|  void \* | [**GetUserIdentifier**](#function-getuseridentifier) () const<br> |
|  void | [**Remove**](#function-remove) (uint64\_t id) <br> |
|  void | [**RemoveCallbacks**](#function-removecallbacks) (void \* pUserIdentifier) <br> |
|  void | [**SetCallbacks**](#function-setcallbacks) (void \* pUserIdentifier, [**Callbacks**](structSR__UTILS__NS_1_1DebugDraw_1_1Callbacks.md) callbacks) <br> |
|  void | [**SwitchCallbacks**](#function-switchcallbacks) (void \* pUserIdentifier) <br> |




## Public Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|   | [**~SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |




## Public Static Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySingleton**](classSR__UTILS__NS_1_1Singleton.md#function-destroysingleton) () <br> |
|  SR\_MAYBE\_UNUSED std::recursive\_mutex & | [**GetMutex**](classSR__UTILS__NS_1_1Singleton.md#function-getmutex) () noexcept<br> |
|  SR\_MAYBE\_UNUSED T & | [**Instance**](classSR__UTILS__NS_1_1Singleton.md#function-instance) () noexcept<br>_TODO: (Multi-threading) Refactor Singleton::Instance()._  |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](classSR__UTILS__NS_1_1Singleton.md#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-unlocksingleton) () noexcept<br> |


























## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |






























































## Protected Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|   | [**Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () <br> |
|   | [**~Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSingletonName**](classSR__UTILS__NS_1_1SingletonBase.md#function-getsingletonname) () noexcept const = 0<br> |
| virtual void | [**InitSingleton**](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton) () <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed) () const<br> |
| virtual void | [**OnSingletonDestroy**](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy) () <br> |
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |










## Detailed Description



* Time: SR\_FLOAT\_MAX - infinity life; 0.f - remove;


* Id: maybe SR\_ID\_INVALID 




    
## Public Types Documentation




### typedef DrawCapsuleCallback 

```C++
using SR_UTILS_NS::DebugDraw::DrawCapsuleCallback =  DrawCubeCallback;
```




<hr>



### typedef DrawCubeCallback 

```C++
using SR_UTILS_NS::DebugDraw::DrawCubeCallback =  SR_HTYPES_NS::Function<uint64_t(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time)>;
```




<hr>



### typedef DrawLineCallback 

```C++
using SR_UTILS_NS::DebugDraw::DrawLineCallback =  SR_HTYPES_NS::Function<uint64_t(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t time)>;
```




<hr>



### typedef DrawMeshCallback 

```C++
using SR_UTILS_NS::DebugDraw::DrawMeshCallback =  SR_HTYPES_NS::Function<uint64_t(SR_HTYPES_NS::RawMesh* pRawMesh, int32_t meshId, uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time)>;
```




<hr>



### typedef DrawPlaneCallback 

```C++
using SR_UTILS_NS::DebugDraw::DrawPlaneCallback =  DrawCubeCallback;
```




<hr>



### typedef DrawSphereCallback 

```C++
using SR_UTILS_NS::DebugDraw::DrawSphereCallback =  DrawCubeCallback;
```




<hr>



### typedef RemoveCallback 

```C++
using SR_UTILS_NS::DebugDraw::RemoveCallback =  SR_HTYPES_NS::Function<void(uint64_t id)>;
```




<hr>
## Public Static Attributes Documentation




### variable DEFAULT\_COLOR 

```C++
constexpr SR_MATH_NS::FColor SR_UTILS_NS::DebugDraw::DEFAULT_COLOR;
```




<hr>



### variable DEFAULT\_DURATION 

```C++
constexpr float_t SR_UTILS_NS::DebugDraw::DEFAULT_DURATION;
```




<hr>



### variable DEFAULT\_POSITION 

```C++
constexpr SR_MATH_NS::FVector3 SR_UTILS_NS::DebugDraw::DEFAULT_POSITION;
```




<hr>



### variable DEFAULT\_QUATERNION 

```C++
constexpr SR_MATH_NS::Quaternion SR_UTILS_NS::DebugDraw::DEFAULT_QUATERNION;
```




<hr>



### variable DEFAULT\_SCALE 

```C++
constexpr SR_MATH_NS::FVector3 SR_UTILS_NS::DebugDraw::DEFAULT_SCALE;
```




<hr>
## Public Functions Documentation




### function DrawCapsule [1/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawCapsule [2/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawCapsule [3/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function DrawCapsule [4/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot
) 
```




<hr>



### function DrawCapsule [5/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawCapsule [6/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawCapsule [7/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    float_t time
) 
```




<hr>



### function DrawCapsule [8/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos
) 
```




<hr>



### function DrawCapsule [9/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawCapsule [10/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawCapsule [11/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function DrawCapsule [12/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot
) 
```




<hr>



### function DrawCapsule [13/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawCapsule [14/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawCapsule [15/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    const SR_MATH_NS::FVector3 & pos,
    float_t time
) 
```




<hr>



### function DrawCapsule [16/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    const SR_MATH_NS::FVector3 & pos
) 
```




<hr>



### function DrawCapsule [17/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule (
    uint64_t id
) 
```




<hr>



### function DrawCapsule [18/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCapsule () 
```




<hr>



### function DrawCube [1/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawCube [2/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawCube [3/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function DrawCube [4/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot
) 
```




<hr>



### function DrawCube [5/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawCube [6/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawCube [7/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    float_t time
) 
```




<hr>



### function DrawCube [8/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos
) 
```




<hr>



### function DrawCube [9/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawCube [10/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawCube [11/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function DrawCube [12/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot
) 
```




<hr>



### function DrawCube [13/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawCube [14/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawCube [15/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    const SR_MATH_NS::FVector3 & pos,
    float_t time
) 
```




<hr>



### function DrawCube [16/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    const SR_MATH_NS::FVector3 & pos
) 
```




<hr>



### function DrawCube [17/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube (
    uint64_t id
) 
```




<hr>



### function DrawCube [18/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawCube () 
```




<hr>



### function DrawLine [1/10]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawLine (
    uint64_t id,
    const SR_MATH_NS::FVector3 & start,
    const SR_MATH_NS::FVector3 & end,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawLine [2/10]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawLine (
    uint64_t id,
    const SR_MATH_NS::FVector3 & start,
    const SR_MATH_NS::FVector3 & end,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawLine [3/10]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawLine (
    uint64_t id,
    const SR_MATH_NS::FVector3 & start,
    const SR_MATH_NS::FVector3 & end,
    float_t time
) 
```




<hr>



### function DrawLine [4/10]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawLine (
    uint64_t id,
    const SR_MATH_NS::FVector3 & start,
    const SR_MATH_NS::FVector3 & end
) 
```




<hr>



### function DrawLine [5/10]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawLine (
    const SR_MATH_NS::FVector3 & start,
    const SR_MATH_NS::FVector3 & end,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawLine [6/10]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawLine (
    const SR_MATH_NS::FVector3 & start,
    const SR_MATH_NS::FVector3 & end,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawLine [7/10]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawLine (
    const SR_MATH_NS::FVector3 & start,
    const SR_MATH_NS::FVector3 & end,
    float_t time
) 
```




<hr>



### function DrawLine [8/10]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawLine (
    const SR_MATH_NS::FVector3 & start,
    const SR_MATH_NS::FVector3 & end
) 
```




<hr>



### function DrawLine [9/10]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawLine (
    uint64_t id
) 
```




<hr>



### function DrawLine [10/10]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawLine () 
```




<hr>



### function DrawMesh [1/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawMesh [2/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawMesh [3/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function DrawMesh [4/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot
) 
```




<hr>



### function DrawMesh [5/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawMesh [6/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawMesh [7/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    float_t time
) 
```




<hr>



### function DrawMesh [8/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos
) 
```




<hr>



### function DrawMesh [9/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawMesh [10/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawMesh [11/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function DrawMesh [12/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot
) 
```




<hr>



### function DrawMesh [13/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawMesh [14/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawMesh [15/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    const SR_MATH_NS::FVector3 & pos,
    float_t time
) 
```




<hr>



### function DrawMesh [16/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    const SR_MATH_NS::FVector3 & pos
) 
```




<hr>



### function DrawMesh [17/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId,
    uint64_t id
) 
```




<hr>



### function DrawMesh [18/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawMesh (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    int32_t meshId
) 
```




<hr>



### function DrawPlane [1/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawPlane [2/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawPlane [3/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function DrawPlane [4/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot
) 
```




<hr>



### function DrawPlane [5/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawPlane [6/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawPlane [7/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    float_t time
) 
```




<hr>



### function DrawPlane [8/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos
) 
```




<hr>



### function DrawPlane [9/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawPlane [10/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawPlane [11/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function DrawPlane [12/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot
) 
```




<hr>



### function DrawPlane [13/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawPlane [14/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawPlane [15/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    const SR_MATH_NS::FVector3 & pos,
    float_t time
) 
```




<hr>



### function DrawPlane [16/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    const SR_MATH_NS::FVector3 & pos
) 
```




<hr>



### function DrawPlane [17/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane (
    uint64_t id
) 
```




<hr>



### function DrawPlane [18/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawPlane () 
```




<hr>



### function DrawQuaternion 

```C++
void SR_UTILS_NS::DebugDraw::DrawQuaternion (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & q,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawSphere [1/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawSphere [2/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawSphere [3/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function DrawSphere [4/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot
) 
```




<hr>



### function DrawSphere [5/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawSphere [6/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawSphere [7/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos,
    float_t time
) 
```




<hr>



### function DrawSphere [8/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    uint64_t id,
    const SR_MATH_NS::FVector3 & pos
) 
```




<hr>



### function DrawSphere [9/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawSphere [10/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawSphere [11/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function DrawSphere [12/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::Quaternion & rot
) 
```




<hr>



### function DrawSphere [13/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color,
    float_t time
) 
```




<hr>



### function DrawSphere [14/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    const SR_MATH_NS::FVector3 & pos,
    const SR_MATH_NS::FColor & color
) 
```




<hr>



### function DrawSphere [15/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    const SR_MATH_NS::FVector3 & pos,
    float_t time
) 
```




<hr>



### function DrawSphere [16/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    const SR_MATH_NS::FVector3 & pos
) 
```




<hr>



### function DrawSphere [17/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere (
    uint64_t id
) 
```




<hr>



### function DrawSphere [18/18]

```C++
uint64_t SR_UTILS_NS::DebugDraw::DrawSphere () 
```




<hr>



### function GetUserIdentifier 

```C++
inline void * SR_UTILS_NS::DebugDraw::GetUserIdentifier () const
```




<hr>



### function Remove 

```C++
void SR_UTILS_NS::DebugDraw::Remove (
    uint64_t id
) 
```




<hr>



### function RemoveCallbacks 

```C++
void SR_UTILS_NS::DebugDraw::RemoveCallbacks (
    void * pUserIdentifier
) 
```




<hr>



### function SetCallbacks 

```C++
void SR_UTILS_NS::DebugDraw::SetCallbacks (
    void * pUserIdentifier,
    Callbacks callbacks
) 
```




<hr>



### function SwitchCallbacks 

```C++
void SR_UTILS_NS::DebugDraw::SwitchCallbacks (
    void * pUserIdentifier
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/DebugDraw.h`

