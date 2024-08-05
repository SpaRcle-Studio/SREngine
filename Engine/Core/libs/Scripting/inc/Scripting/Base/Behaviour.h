//
// Created by Monika on 24.05.2022.
//

#ifndef SR_ENGINE_SCRIPTING_BEHAVIOUR_H
#define SR_ENGINE_SCRIPTING_BEHAVIOUR_H

#include <Utils/ECS/Component.h>
#include <Utils/Resources/IResource.h>

namespace SR_UTILS_NS {
    class GameObject;
    class Transform3D;
    class Transform2D;
    class Transform;
}

namespace SR_SCRIPTING_NS {
    class Behaviour;

    class IRawBehaviour : public SR_UTILS_NS::IResource {
        using Super = SR_UTILS_NS::IResource;
        using Properties = std::vector<std::string>;
        using ValueProperties = std::list<std::pair<std::string, std::any>>;
    public:
        explicit IRawBehaviour(uint64_t hashName)
            : Super(hashName)
        { }

    public:
        static IRawBehaviour* Load(SR_UTILS_NS::Path path);

    public:
        virtual void SetComponent(Behaviour* pBehaviour) {
            m_component = pBehaviour;
        }

        bool Load() override { return SR_UTILS_NS::IResource::Load(); }
        bool Unload() override { return SR_UTILS_NS::IResource::Unload(); }
        bool Reload() override;

        void OnReloadDone() override;

        virtual Properties GetProperties() const = 0;
        virtual std::any GetProperty(const std::string& id) const = 0;
        virtual void SetProperty(const std::string& id, const std::any& val) = 0;

        virtual void Awake() = 0;
        virtual void OnEnable() = 0;
        virtual void OnDisable() = 0;
        virtual void OnAttached() = 0;
        virtual void OnDetached() = 0;
        virtual void OnDestroy() = 0;
        virtual void Start() = 0;
        virtual void Update(float_t dt) = 0;
        virtual void FixedUpdate() = 0;

        virtual void OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) = 0;
        virtual void OnCollisionStay(const SR_UTILS_NS::CollisionData& data) = 0;
        virtual void OnCollisionExit(const SR_UTILS_NS::CollisionData& data) = 0;
        virtual void OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) = 0;
        virtual void OnTriggerExit(const SR_UTILS_NS::CollisionData& data) = 0;
        virtual void OnTriggerStay(const SR_UTILS_NS::CollisionData& data) = 0;

        virtual void OnTransformSet() = 0;

    protected:
        mutable bool m_hasErrors = false;
        Behaviour* m_component = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class Behaviour final : public SR_UTILS_NS::Component {
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject>;
        using Properties = std::vector<std::string>;
        using ValueProperties = std::list<std::pair<std::string, std::any>>;
        SR_ENTITY_SET_VERSION(1002);
        SR_INITIALIZE_COMPONENT(Behaviour);
        using Super = SR_UTILS_NS::Component;
    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        void SetRawBehaviour(const SR_UTILS_NS::Path& path);
        void Reload();
        void OnBehaviourChanged();

        SR_NODISCARD IRawBehaviour* GetRawBehaviour() const noexcept { return m_rawBehaviour; }

    protected:
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_UTILS_NS::SavableContext data) const override;

        SR_NODISCARD Component* CopyComponent() const override;

        void Awake() override;
        void OnEnable() override;
        void OnDisable() override;
        void OnAttached() override;
        void OnDetached() override;
        void OnDestroy() override;
        void Start() override;
        void Update(float_t dt) override;
        void FixedUpdate() override;

        void OnTransformSet() override;

        void OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) override;
        void OnCollisionStay(const SR_UTILS_NS::CollisionData& data) override;
        void OnCollisionExit(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerExit(const SR_UTILS_NS::CollisionData& data) override;
        void OnTriggerStay(const SR_UTILS_NS::CollisionData& data) override;

    protected:
        IRawBehaviour* m_rawBehaviour = nullptr;

    };
}

#endif //SR_ENGINE_BEHAVIOUR_H
