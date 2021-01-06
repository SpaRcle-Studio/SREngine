//
// Created by Nikita on 30.12.2020.
//

#ifndef GAMEENGINE_TIME_H
#define GAMEENGINE_TIME_H

#include <ctime>
#include <iostream>
#include <ratio>
#include <chrono>

namespace Framework::Helper::Types {
    class Time {
        Time() = delete;

        Time(Time &) = delete;

        ~Time() = delete;

    private:
        inline static double num_fps_limit = 120.f;
        inline static double fps_limit_timer = 0.f;
        inline static double fps_lim = 1 / num_fps_limit;
        inline static double frameDeltaTime;
        inline static int now = 0, then = 0;
    public:
        inline static void SetFPSLimit(int count) {
            num_fps_limit = (float)count;
        }

        static double DeltaTime() { return frameDeltaTime; }

        static bool Begin() {
            now = clock();
            frameDeltaTime = (double) (now - then) / 1000.f;
            fps_limit_timer += frameDeltaTime;

            if (fps_limit_timer >= fps_lim) {
                fps_limit_timer = 0.0f;
                return true;
            } else
                return false;
        }

        static void End() {
            then = now;
        }
    };
}

#endif //GAMEENGINE_TIME_H
