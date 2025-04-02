

# Namespace SR\_ANIMATIONS\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**AnimationChannel**](classSR__ANIMATIONS__NS_1_1AnimationChannel.md) <br> |
| class | [**AnimationClip**](classSR__ANIMATIONS__NS_1_1AnimationClip.md) <br> |
| class | [**AnimationClipState**](classSR__ANIMATIONS__NS_1_1AnimationClipState.md) <br> |
| class | [**AnimationEntryPointState**](classSR__ANIMATIONS__NS_1_1AnimationEntryPointState.md) <br> |
| struct | [**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) <br> |
| class | [**AnimationGraph**](classSR__ANIMATIONS__NS_1_1AnimationGraph.md) <br> |
| class | [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) <br> |
| class | [**AnimationGraphNodeFinal**](classSR__ANIMATIONS__NS_1_1AnimationGraphNodeFinal.md) <br> |
| class | [**AnimationGraphNodeStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationGraphNodeStateMachine.md) <br> |
| class | [**AnimationInterpolationFunction**](classSR__ANIMATIONS__NS_1_1AnimationInterpolationFunction.md) <br> |
| struct | [**AnimationLink**](structSR__ANIMATIONS__NS_1_1AnimationLink.md) <br> |
| class | [**AnimationNoneState**](classSR__ANIMATIONS__NS_1_1AnimationNoneState.md) <br> |
| class | [**AnimationPose**](classSR__ANIMATIONS__NS_1_1AnimationPose.md) <br> |
| class | [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) <br> |
| class | [**AnimationStateCondition**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md) <br> |
| class | [**AnimationStateConditionAnd**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionAnd.md) <br> |
| class | [**AnimationStateConditionBool**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionBool.md) <br> |
| class | [**AnimationStateConditionExitTime**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionExitTime.md) <br> |
| class | [**AnimationStateConditionNot**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionNot.md) <br> |
| class | [**AnimationStateConditionOr**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionOr.md) <br> |
| class | [**AnimationStateConditionTrue**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionTrue.md) <br> |
| class | [**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) <br> |
| class | [**AnimationStateTransition**](classSR__ANIMATIONS__NS_1_1AnimationStateTransition.md) <br> |
| class | [**Animator**](classSR__ANIMATIONS__NS_1_1Animator.md) <br> |
| struct | [**Bone**](structSR__ANIMATIONS__NS_1_1Bone.md) <br> |
| class | [**BoneComponent**](classSR__ANIMATIONS__NS_1_1BoneComponent.md) <br> |
| struct | [**ChannelUpdateContext**](structSR__ANIMATIONS__NS_1_1ChannelUpdateContext.md) <br> |
| struct | [**CompileContext**](structSR__ANIMATIONS__NS_1_1CompileContext.md) <br> |
| class | [**IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md) <br> |
| struct | [**RotationKey**](structSR__ANIMATIONS__NS_1_1RotationKey.md) <br> |
| struct | [**ScalingKey**](structSR__ANIMATIONS__NS_1_1ScalingKey.md) <br> |
| class | [**Skeleton**](classSR__ANIMATIONS__NS_1_1Skeleton.md) <br> |
| struct | [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) <br> |
| struct | [**TranslationKey**](structSR__ANIMATIONS__NS_1_1TranslationKey.md) <br> |
| struct | [**UnionAnimationKey**](structSR__ANIMATIONS__NS_1_1UnionAnimationKey.md) <br> |
| struct | [**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (AnimationGraphNodeType, uint8\_t, None, Final, Mix, Clip, StateMachine) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (AnimationStateType, uint8\_t, None, Graph, Entry) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (AnimationStateConditionOperationType, uint8\_t, Equals, Less, More, NotEquals) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (AnimationKeyType, uint8\_t, None, Translation, Rotation, Scaling) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (AnimationInterpolationFunctionType, uint8\_t, Linear, Step, Smooth) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**AiQToQ**](#function-aiqtoq) (const aiQuaternion & q) <br> |
|  SR\_MATH\_NS::FVector3 | [**AiV3ToFV3**](#function-aiv3tofv3) (const aiVector3D & v, float\_t multiplier) <br>_Это тип свойства которое изменяет AnimationKey._  |
|  [**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) | [**Merge**](#function-merge) ([**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) & from, [**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) & to, float\_t weight) <br> |


























## Public Functions Documentation




### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_ANIMATIONS_NS::SR_ENUM_NS_CLASS_T (
    AnimationGraphNodeType,
    uint8_t,
    None,
    Final,
    Mix,
    Clip,
    StateMachine
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_ANIMATIONS_NS::SR_ENUM_NS_CLASS_T (
    AnimationStateType,
    uint8_t,
    None,
    Graph,
    Entry
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_ANIMATIONS_NS::SR_ENUM_NS_CLASS_T (
    AnimationStateConditionOperationType,
    uint8_t,
    Equals,
    Less,
    More,
    NotEquals
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_ANIMATIONS_NS::SR_ENUM_NS_CLASS_T (
    AnimationKeyType,
    uint8_t,
    None,
    Translation,
    Rotation,
    Scaling
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_ANIMATIONS_NS::SR_ENUM_NS_CLASS_T (
    AnimationInterpolationFunctionType,
    uint8_t,
    Linear,
    Step,
    Smooth
) 
```




<hr>
## Public Static Functions Documentation




### function AiQToQ 

```C++
static SR_MATH_NS::Quaternion SR_ANIMATIONS_NS::AiQToQ (
    const aiQuaternion & q
) 
```




<hr>



### function AiV3ToFV3 

_Это тип свойства которое изменяет AnimationKey._ 
```C++
static SR_MATH_NS::FVector3 SR_ANIMATIONS_NS::AiV3ToFV3 (
    const aiVector3D & v,
    float_t multiplier
) 
```




<hr>



### function Merge 

```C++
static AnimationGameObjectData SR_ANIMATIONS_NS::Merge (
    AnimationGameObjectData & from,
    AnimationGameObjectData & to,
    float_t weight
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/inc/Core/Common/Importers.h`

