//
// Created by Monika on 17.02.2022.
//

#include <Utils/Input/InputDispatcher.h>
#include <Utils/Input/InputHandler.h>

void SR_UTILS_NS::InputDispatcher::Check() {
    for (const auto& code : KeyCodes) {
        if (Input::GetKeyDown(code))
            Dispatch<InputHandler>(code, MouseCode::None, KeyState::Down);
        else if (Input::GetKeyUp(code))
            Dispatch<InputHandler>(code, MouseCode::None, KeyState::Up);
        else if (Input::GetKey(code))
            Dispatch<InputHandler>(code, MouseCode::None, KeyState::Press);
    }

    for (const auto& code : MouseCodes) {
        if (Input::GetMouseDown(code))
            Dispatch<InputHandler>(KeyCode::None, code, KeyState::Down);
        else if (Input::GetMouseUp(code))
            Dispatch<InputHandler>(KeyCode::None, code, KeyState::Up);
        else if (Input::GetMouse(code))
            Dispatch<InputHandler>(KeyCode::None, code, KeyState::Press);
    }
}
