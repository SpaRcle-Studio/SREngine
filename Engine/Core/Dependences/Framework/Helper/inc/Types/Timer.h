//
// Created by Monika on 17.11.2021.
//

#ifndef GAMEENGINE_TIMER_H
#define GAMEENGINE_TIMER_H

#include <Debug.h>

namespace SR_HTYPES_NS {
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

            auto&& now = clock();

            m_deltaTime += double_t(now - m_beginFrame) / (double_t) CLOCKS_PER_SEC;
            m_frames++;
            m_beginFrame = now;

            return m_deltaTime > m_updateFrequency;
        }

        SR_NODISCARD float_t GetDeltaTime() const { return m_deltaTime; }
        SR_NODISCARD uint32_t GetFrames() const { return m_frames; }

    private:
        float_t  m_updateFrequency;
        double_t m_deltaTime = 0;
        uint32_t m_frames = 0;
        clock_t  m_beginFrame{};

    };
}

#endif //GAMEENGINE_TIMER_H
