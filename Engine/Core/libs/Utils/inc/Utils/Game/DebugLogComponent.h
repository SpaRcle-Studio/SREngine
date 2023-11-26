//
// Created by Monika on 26.11.2023.
//

#ifndef SR_ENGINE_UTILS_DEBUG_LOG_COMPONENT_H
#define SR_ENGINE_UTILS_DEBUG_LOG_COMPONENT_H

#include <Utils/ECS/EntityRef.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT DebugLogComponent final : public Component {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(DebugLogComponent);
        using Super = Component;
    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
            return new DebugLogComponent();
        }

    public:
        void OnLoaded() override { SR_DEBUG_LOG("DebugLogComponent::OnLoaded()"); Super::OnLoaded(); }
        void Start() override { SR_DEBUG_LOG("DebugLogComponent::Start()"); Super::Start(); }
        void Awake() override { SR_DEBUG_LOG("DebugLogComponent::Awake()"); Super::Awake(); }
        void OnEnable() override { SR_DEBUG_LOG("DebugLogComponent::OnEnable()"); Super::OnEnable(); }
        void OnDisable() override { SR_DEBUG_LOG("DebugLogComponent::OnDisable()"); Super::OnDisable(); }
        void OnAttached() override { SR_DEBUG_LOG("DebugLogComponent::OnAttached()"); Super::OnAttached(); }
        void OnDetached() override { SR_DEBUG_LOG("DebugLogComponent::OnDetached()"); Super::OnDetached(); }

        void OnDestroy() override {
            SR_DEBUG_LOG("DebugLogComponent::OnDestroy()");
            Super::OnDestroy();
            GetThis().AutoFree([](auto&& pData) {
                delete pData;
            });
        }
    };
}

#endif //SR_ENGINE_UTILS_DEBUG_LOG_COMPONENT_H
