//
// Created by innerviewer on 2024-04-28.
//

#include <Libraries/Types/Behaviour.h>
#include <Libraries/Utils/Allocator.h>

#include <Libraries/Button.h>
#include <Libraries/Casts.h>
#include <Libraries/Component.h>
#include <Libraries/Debug.h>
#include <Libraries/Engine.h>
#include <Libraries/Rigidbody.h>
#include <Libraries/Text.h>
#include <Libraries/Window.h>

class LauncherButtonController : public Behaviour {
public:
    static void OnKeyDown() { std::cout << "BUTTON IS HOVERED !!! ----------------------------- " << std::endl; }

public:
    void Awake() override {
        auto&& button = DynamicCastComponentToButton(gameObject->GetComponent("Button"));
        if (button) {
            button->SetKeyDownCallback(&OnKeyDown);
        }
    }
};

REGISTER_BEHAVIOUR(LauncherButtonController)