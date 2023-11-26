//
// Created by Monika on 05.10.2023.
//

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>

#include <Libraries/Debug.h>
#include <Libraries/Text.h>
#include <Libraries/Window.h>
#include <Libraries/Engine.h>
#include <Libraries/Casts.h>

class FPSCounter : public Behaviour {
public:
    void Update(float_t dt) override {
		auto&& pText = DynamicCastComponentToText2D(gameObject->GetComponent("Text2D"));
		if (!pText) {
			return;
		}

		auto&& pWindow = Engine::Instance().GetWindow();
        if (pWindow) {
            pText->SetText(std::to_string(pWindow->GetFramesPerSecond()));
        }
    }
};

REGISTER_BEHAVIOUR(FPSCounter)