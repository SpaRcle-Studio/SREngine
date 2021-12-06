//
// Created by Monika on 17.11.2021.
//

#ifndef GAMEENGINE_TIMER_H
#define GAMEENGINE_TIMER_H

#include <ctime>
#include <iostream>
#include <ratio>
#include <chrono>

namespace Framework::Helper::Types {
    class Timer {
    public:
        explicit Timer(float_t updateFrequency)
            : m_updateFrequency(updateFrequency)
        { }

    public:
        bool Update() {
            if (m_deltaTime > m_updateFrequency) {
                m_frames = 0; m_deltaTime = 0;
            }

            m_deltaTime += double_t(clock() - m_beginFrame) / (double_t) CLOCKS_PER_SEC;
            m_frames++;
            m_beginFrame = clock();

            return m_deltaTime > m_updateFrequency;
        }
        [[nodiscard]] float_t GetDeltaTime() const { return m_deltaTime; }
        [[nodiscard]] uint32_t GetFrames() const { return m_frames; }

    private:
        float_t  m_updateFrequency;
        double_t m_deltaTime = 0;
        uint32_t m_frames = 0;
        clock_t  m_beginFrame{};
    };
}

#endif //GAMEENGINE_TIMER_H
