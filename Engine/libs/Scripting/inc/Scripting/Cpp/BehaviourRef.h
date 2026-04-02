//
// Created by Monika on 28.03.2026.
//

#ifndef SR_ENGINE_SCRIPTING_BEHAVIOUR_REF_H
#define SR_ENGINE_SCRIPTING_BEHAVIOUR_REF_H

#include <Scripting/Cpp/CppBehaviour.h>
#include <Scripting/Base/Behaviour.h>

#include <Utils/ECS/EntityRef.h>

namespace SR_SCRIPTING_NS {
    template<typename T> class BehaviourRef : public SR_UTILS_NS::EntityRef<Behaviour> {
    public:
        SR_NODISCARD SR_UTILS_NS::StringAtom GetTypeName() const noexcept override {
            return SR_UTILS_NS::EntityRefExtractTypeName<T>();
        }

        SR_NODISCARD bool IsApplicable(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::Entity>& pEntity) const noexcept override {
            if (!pEntity) {
                SRHalt("BehaviourRef::IsApplicable() : entity is null!");
                return false;
            }

            if (!pEntity->GetMeta()) {
                SRHalt("BehaviourRef::IsApplicable() : entity with id {} has no meta!", pEntity->GetEntityId());
                return false;
            }

            static const auto&& meta = Behaviour::GetClassStaticName();
            if (!pEntity->GetMeta()->IsSameOrInherited(meta)) {
                SRHalt("BehaviourRef::IsApplicable() : entity with id {} is not a behaviour!", pEntity->GetEntityId());
                return false;
            }

            return true;
            // if (auto&& pBehaviour = pEntity.template StaticCast<Behaviour>()) {
            //     auto&& pCppBehaviour = pBehaviour->GetBehaviour();
            //     if (pCppBehaviour && pCppBehaviour->GetMeta() && pCppBehaviour->GetMeta()->IsSameOrInherited(T::GetClassStaticName())) {
            //         return true;
            //     }
            // }

            // SRHalt("BehaviourRef::IsApplicable() : entity with id {} does not have a behaviour of type {}!", pEntity->GetEntityId(), T::GetClassStaticName());
            // return false;
        }

        SR_NODISCARD SR_HTYPES_NS::SharedPtr<T> GetBehaviour() const {
            SR_TRACY_ZONE;
            auto&& pEntity = GetEntity();
            static const auto&& meta = Behaviour::GetClassStaticName();
            if (!pEntity || !pEntity->GetMeta() || !pEntity->GetMeta()->IsSameOrInherited(meta)) {
                return nullptr;
            }
            return pEntity.template StaticCast<Behaviour>()->template GetBehaviour<T>();
        }
    };
}

#endif //SR_ENGINE_SCRIPTING_BEHAVIOUR_REF_H
