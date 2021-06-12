//
// Created by Nikita on 12.02.2021.
//

#ifndef GAMEENGINE_FRAMEBUFFER_H
#define GAMEENGINE_FRAMEBUFFER_H

#include <Types/Texture.h>
#include <Environment/Environment.h>
#include <vector>
#include <Debug.h>

namespace Framework::Graphics {
    class FrameBuffer {
    private:
        std::vector<uint32_t> m_colorAttachments = { };
    };
}

#endif //GAMEENGINE_FRAMEBUFFER_H
