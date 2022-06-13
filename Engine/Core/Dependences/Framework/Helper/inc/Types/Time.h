//
// Created by Nikita on 30.12.2020.
//

#ifndef GAMEENGINE_TIME_H
#define GAMEENGINE_TIME_H

#include <Debug.h>

namespace Framework::Helper::Types {
    class Time {
    public:
        Time() {
            //this->num_fps_limit = 120.f;
            //this->fps_lim = 1.f / num_fps_limit;
            SetFPSLimit(120);
        };

        //Time(Time &) = delete;

        ~Time() = default;

    private:
        volatile double num_fps_limit = 0.f;
        double          fps_limit_timer = 0.f;
        volatile double fps_lim = 0.f;
        volatile double frameDeltaTime = 0.f;
        volatile int    now = 0, then = 0;
    public:
        inline void SetFPSLimit(int count) {
            num_fps_limit = (float)count;
            fps_lim = 1.f / num_fps_limit * 1000000.f;
        }

        [[nodiscard]] inline double DeltaTime() const { return frameDeltaTime; }

        inline bool Begin() {
            now = clock();
            //frameDeltaTime = ((double) (now - then)) / 1000.f;
            frameDeltaTime = ((double) (now - then)) / 1000.f;
            fps_limit_timer += frameDeltaTime;

            if (fps_limit_timer >= fps_lim) {
                fps_limit_timer = 0.0f;
                return true;
            } else
                return false;
        }

        inline void End() {
            then = now;
        }
    };
}

#endif //GAMEENGINE_TIME_H
