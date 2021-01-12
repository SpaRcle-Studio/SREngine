//
// Created by Nikita on 13.01.2021.
//

#include "GUI/Canvas.h"

Framework::Canvas::Canvas(Scripting::Script* script) {

}

bool Framework::Canvas::Close() {
    Helper::Debug::Log("Canvas::Close() : close canvas...");
    return true;
}

bool Framework::Canvas::Free() {
    Helper::Debug::Info("Canvas::Free() : free canvas pointer...");
    delete this;
    return true;
}

void Framework::Canvas::Draw() {

}
