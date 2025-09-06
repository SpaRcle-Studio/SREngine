

# File DebugLogComponent.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Game**](dir_8f1885d18d834cf9a317dd74a37ec10b.md) **>** [**DebugLogComponent.h**](DebugLogComponent_8h.md)

[Go to the documentation of this file](DebugLogComponent_8h.md)


```C++
//
// Created by Monika on 26.11.2023.
//

#ifndef SR_ENGINE_UTILS_DEBUG_LOG_COMPONENT_H
#define SR_ENGINE_UTILS_DEBUG_LOG_COMPONENT_H

#include <Utils/ECS/EntityRefOld.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API DebugLogComponent final : public Component {
        SR_CLASS()
        using Super = Component;
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
        }
    };
}

#endif //SR_ENGINE_UTILS_DEBUG_LOG_COMPONENT_H
```


