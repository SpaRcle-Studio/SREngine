

# File DebugLogComponent.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Game**](dir_29b5b52e34c278ad0cd05efb71f95f71.md) **>** [**DebugLogComponent.h**](DebugLogComponent_8h.md)

[Go to the documentation of this file](DebugLogComponent_8h.md)


```C++
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
            GetThis().AutoFree([](auto&& pData) {
                delete pData;
            });
        }
    };
}

#endif //SR_ENGINE_UTILS_DEBUG_LOG_COMPONENT_H
```


