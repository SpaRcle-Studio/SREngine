

# File AnimationCommon.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**AnimationCommon.h**](AnimationCommon_8h.md)

[Go to the documentation of this file](AnimationCommon_8h.md)


```C++
//
// Created by Monika on 23.04.2023.
//

#ifndef SR_ENGINE_ANIMATION_COMMON_H
#define SR_ENGINE_ANIMATION_COMMON_H

#include <Graphics/macros.h>

#include <Utils/Types/Map.h>
#include <Utils/Types/Time.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Enumerations.h>

#ifdef SR_UTILS_ASSIMP
    #include <assimp/vector3.h>
    #include <assimp/quaternion.h>
#endif

namespace SR_ANIMATIONS_NS {
    /*SR_ENUM_NS_CLASS_T(AnimationPropertyType, uint8_t,
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
    );*/

#ifdef SR_UTILS_ASSIMP
    static SR_MATH_NS::FVector3 AiV3ToFV3(const aiVector3D& v, float_t multiplier) {
        return SR_MATH_NS::FVector3(v.x, v.y, v.z) * multiplier;
    }

    static SR_MATH_NS::Quaternion AiQToQ(const aiQuaternion& q) {
        return SR_MATH_NS::Quaternion(q.x, q.y, q.z, q.w);
    }
#endif

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

    struct StateConditionContext {
        float_t dt = 0.f;
        const AnimationStateMachine* pMachine = nullptr;
        AnimationState* pState = nullptr;
    };

    class IAnimationDataSet {
    public:
        void SetBool(const SR_UTILS_NS::StringAtom& name, const bool value) {
            m_boolTable[name] = value;
        }
        void SetInt(const SR_UTILS_NS::StringAtom& name, const int32_t value) {
            m_intTable[name] = value;
        }
        void SetFloat(const SR_UTILS_NS::StringAtom& name, const float_t value) {
            m_floatTable[name] = value;
        }
        void SetString(const SR_UTILS_NS::StringAtom& name, const std::string& value) {
            m_stringTable[name] = value;
        }

        SR_NODISCARD std::optional<bool> GetBool(const SR_UTILS_NS::StringAtom& name) const;
        SR_NODISCARD std::optional<int32_t> GetInt(const SR_UTILS_NS::StringAtom& name) const;
        SR_NODISCARD std::optional<float_t> GetFloat(const SR_UTILS_NS::StringAtom& name) const;
        SR_NODISCARD std::optional<std::string> GetString(const SR_UTILS_NS::StringAtom& name) const;

        void SetAnimationDataSetParent(IAnimationDataSet* pParent) {
            m_parent = pParent;
        }

    protected:
        IAnimationDataSet() = default;

        explicit IAnimationDataSet(IAnimationDataSet* pParent)
            : m_parent(pParent)
        { }

        virtual ~IAnimationDataSet() = default;

    protected:
        std::map<SR_UTILS_NS::StringAtom, bool> m_boolTable;
        std::map<SR_UTILS_NS::StringAtom, int32_t> m_intTable;
        std::map<SR_UTILS_NS::StringAtom, float_t> m_floatTable;
        std::map<SR_UTILS_NS::StringAtom, std::string> m_stringTable;

        IAnimationDataSet* m_parent = nullptr;

    };
}

#endif //SR_ENGINE_ANIMATION_COMMON_H
```


