//
// Created by Monika on 23.04.2023.
//

#ifndef SRENGINE_ANIMATIONCOMMON_H
#define SRENGINE_ANIMATIONCOMMON_H

#include <Utils/Types/Map.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Enumerations.h>

namespace SR_ANIMATIONS_NS {
    SR_ENUM_NS_CLASS_T(AnimationGraphNodeType, uint8_t,
        None, Final, Mix, Clip, StateMachine
    );

    SR_ENUM_NS_CLASS_T(AnimationStateType, uint8_t ,
        None, Graph, Entry
    );

    class IAnimationDataSet {
    protected:
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
