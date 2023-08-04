//
// Created by Monika on 23.04.2023.
//

#ifndef SRENGINE_ANIMATIONCOMMON_H
#define SRENGINE_ANIMATIONCOMMON_H

#include <Utils/Types/Map.h>
#include <Utils/Types/Time.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Enumerations.h>

namespace SR_ANIMATIONS_NS {
    /// Это тип свойства которое изменяет AnimationKey
    SR_ENUM_NS_CLASS_T(AnimationPropertyType, uint8_t,
        Translation,
        Rotation,
        Scale,
        Skew,

        InstanceFromFile,

        ComponentEnable,
        ComponentProperty,
        ComponentRemove,
        ComponentAdd,

        GameObjectAdd,
        GameObjectRemove,
        GameObjectMove,
        GameObjectEnable,
        GameObjectName,
        GameObjectTag
    );

    static SR_MATH_NS::FVector3 AiV3ToFV3(const aiVector3D& v, float_t multiplier) {
        return SR_MATH_NS::FVector3(v.x, v.y, v.z) * multiplier;
    }

    static SR_MATH_NS::Quaternion AiQToQ(const aiQuaternion& q) {
        return SR_MATH_NS::Quaternion(q.x, q.y, q.z, q.w);
    }

    SR_ENUM_NS_CLASS_T(AnimationGraphNodeType, uint8_t,
        None, Final, Mix, Clip, StateMachine
    );

    SR_ENUM_NS_CLASS_T(AnimationStateType, uint8_t ,
        None, Graph, Entry
    );

    struct AnimationLink {
    public:
        AnimationLink(uint16_t targetNodeIndex, uint16_t targetPinIndex)
            : m_targetNodeIndex(targetNodeIndex)
            , m_targetPinIndex(targetPinIndex)
        { }

    public:
        uint16_t m_targetNodeIndex = 0;
        uint16_t m_targetPinIndex = 0;

    };

    SR_ENUM_NS_CLASS_T(AnimationStateConditionOperationType, uint8_t,
        Equals, Less, More, NotEquals
    );

    class IAnimationDataSet;
    class AnimationGraphNode;
    class AnimationState;
    class AnimationStateMachine;
    class AnimationPose;

    struct UpdateContext {
        AnimationPose* pWorkingPose = nullptr;
        AnimationPose* pStaticPose = nullptr;
        float_t dt = 0.f;
        float_t weight = 1.f;
        SR_HTYPES_NS::Time::Point now;
        bool fpsCompensation = false;

    };

    struct StateConditionContext {
        AnimationStateMachine* pMachine = nullptr;
        AnimationState* pState = nullptr;
    };

    class IAnimationDataSet {
    protected:
        explicit IAnimationDataSet(IAnimationDataSet* pParent)
            : m_parent(pParent)
        { }

        virtual ~IAnimationDataSet() = default;

    protected:
        using Hash = uint64_t;

    protected:
        ska::flat_hash_map<Hash, std::string> m_stringTable;
        ska::flat_hash_map<Hash, uint64_t> m_intTable;
        ska::flat_hash_map<Hash, float_t> m_floatTable;
        ska::flat_hash_map<Hash, bool> m_boolTable;

        IAnimationDataSet* m_parent = nullptr;

    };
}

#endif //SRENGINE_ANIMATIONCOMMON_H
