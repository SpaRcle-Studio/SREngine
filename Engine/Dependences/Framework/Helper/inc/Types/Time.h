//
// Created by Nikita on 30.12.2020.
//

#ifndef GAMEENGINE_TIME_H
#define GAMEENGINE_TIME_H

#include <ctime>

namespace Framework::Helper::Types {
    class Time {
        Time() = delete;

        Time(Time &) = delete;

        ~Time() = delete;

    private:
        inline static float num_fps_limit = 60.f;
        inline static float fps_limit_timer = 0.f;
        inline static float fps_lim = 1 / num_fps_limit;
        inline static float frameDeltaTime;
        inline static int now = 0, then = 0;
    public:
        inline static void SetFPSLimit(int count) {
            num_fps_limit = (float)count;
        }

        static float DeltaTime() { return frameDeltaTime; }

        static bool Begin() {
            now = clock();
            frameDeltaTime = (float) (now - then) / 1000.f;
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
