//
// Created by Monika on 24.05.2022.
//

#ifndef SRENGINE_BEHAVIOUR_H
#define SRENGINE_BEHAVIOUR_H

#include <Utils/ECS/Component.h>
#include <Utils/ResourceManager/IResource.h>

namespace SR_UTILS_NS {
    class GameObject;
    class Transform3D;
    class Transform2D;
    class Transform;
}

namespace SR_SCRIPTING_NS {
    class Behaviour : public SR_UTILS_NS::IResource, public SR_UTILS_NS::Component {
        using GameObjectPtr = SR_HTYPES_NS::SafePtr<SR_UTILS_NS::GameObject>;
        using TransformPtr = SR_UTILS_NS::Transform*;
        using Properties = std::vector<std::string>;
        using ValueProperties = std::list<std::pair<std::string, std::any>>;
        SR_INLINE_STATIC SR_CONSTEXPR const char* EMPTY_ID = "EmptyBehaviour";
        SR_ENTITY_SET_VERSION(1002);
    protected:
        Behaviour();
        ~Behaviour() override = default;

    public:
        static Behaviour* CreateEmpty();
        static Behaviour* Load(SR_UTILS_NS::Path path);

        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

        SR_NODISCARD GameObjectPtr GetGameObject() const;
        SR_NODISCARD bool IsEmpty() const;

    public:
        virtual Properties GetProperties() const { return {}; };
        virtual std::any GetProperty(const std::string& id) const { return std::any(); }
        virtual void SetProperty(const std::string& id, const std::any& val) { }

    protected:
        virtual SR_HTYPES_NS::DataStorage Stash();
        virtual void ApplyStash(const SR_HTYPES_NS::DataStorage& data);
        virtual void PopStash(const SR_HTYPES_NS::DataStorage& data);

        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
        SR_NODISCARD uint64_t GetFileHash() const override { return 0; };
        SR_HTYPES_NS::Marshal Save(SR_UTILS_NS::SavableFlags flags) const override;

        void OnAttached() override;

        bool Load() override { return SR_UTILS_NS::IResource::Load(); }
        bool Unload() override { return SR_UTILS_NS::IResource::Unload(); }
        bool Reload() override;
        void OnDestroy() override;

    };
}

#endif //SRENGINE_BEHAVIOUR_H
