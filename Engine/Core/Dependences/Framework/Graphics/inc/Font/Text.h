//
// Created by Monika on 14.02.2022.
//

#ifndef SRENGINE_TEXT_H
#define SRENGINE_TEXT_H

#include <string>
#include <atomic>
#include <mutex>

namespace Framework::Graphics {
    class Text {
    private:
        std::u32string m_text;
    };
}

#endif //SRENGINE_TEXT_H
