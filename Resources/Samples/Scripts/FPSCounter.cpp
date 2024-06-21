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
		auto&& pText = DynamicCastComponentToText(gameObject->GetComponent("Text"));
		if (!pText) {
			return;
		}

        pText->SetText(std::to_string(Engine::Instance().GetFramesPerSecond()));
    }
};

REGISTER_BEHAVIOUR(FPSCounter)