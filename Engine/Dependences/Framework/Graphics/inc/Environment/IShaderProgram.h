//
// Created by Nikita on 29.03.2021.
//

#ifndef GAMEENGINE_ISHADERPROGRAM_H
#define GAMEENGINE_ISHADERPROGRAM_H

namespace Framework::Graphics {
    interface IShaderProgram {
        [[nodiscard]] virtual bool IsReady() const noexcept { return false; }
    };
}

#endif //GAMEENGINE_ISHADERPROGRAM_H
