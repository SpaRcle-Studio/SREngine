//
// Created by Igor on 05/07/2022.
//

#ifndef SRENGINE_SOUND_H
#define SRENGINE_SOUND_H
namespace SR_SCRIPTING_NS {
    class Behaviour : public SR_UTILS_NS::IResource, public SR_UTILS_NS::Component {
        using GameObjectPtr = SR_HTYPES_NS::SafePtr<SR_UTILS_NS::GameObject>;
        using TransformPtr = SR_UTILS_NS::Transform3D*;
        using Properties = std::vector<std::string>;
        SR_INLINE_STATIC SR_CONSTEXPR const char* EMPTY_ID = "EmptyBehaviour";
        SR_ENTITY_SET_VERSION(1002);
    protected:
        Behaviour();
        ~Behaviour() override = default;
#endif //SRENGINE_SOUND_H

