//
// Created by Monika on 17.02.2022.
//

#include <Utils/Input/InputDispatcher.h>
#include <Utils/Input/InputHandler.h>

void SR_UTILS_NS::InputDispatcher::Check() {
    for (const auto& code : KeyCodes) {
        if (Input::Instance().GetKeyDown(code))
            Dispatch<InputHandler>(code, MouseCode::None, KeyState::Down);
        else if (Input::Instance().GetKeyUp(code))
            Dispatch<InputHandler>(code, MouseCode::None, KeyState::Up);
        else if (Input::Instance().GetKey(code))
            Dispatch<InputHandler>(code, MouseCode::None, KeyState::Press);
    }

    for (const auto& code : MouseCodes) {
        if (Input::Instance().GetMouseDown(code))
            Dispatch<InputHandler>(KeyCode::None, code, KeyState::Down);
        else if (Input::Instance().GetMouseUp(code))
            Dispatch<InputHandler>(KeyCode::None, code, KeyState::Up);
        else if (Input::Instance().GetMouse(code))
            Dispatch<InputHandler>(KeyCode::None, code, KeyState::Press);
    }
}
