//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_WINDOWFORMAT_H
#define GAMEENGINE_WINDOWFORMAT_H

#include <string>
#include <Debug.h>
#include <Math/Vector2.h>

namespace Framework::Graphics::Types {
    using namespace Framework::Helper::Math;

    class WindowFormat {
    public:
        enum Value {
            Unknown,
            Free,
            _640_360,
            _1280_720,
            _1366_768,
            _1600_900
        };

        WindowFormat(const Vector2& size) : value(Value::Free) {
            this->m_width = (unsigned int)size.x;
            this->m_height = (unsigned int)size.y;
        }

        WindowFormat(Value v) : value(v) {
            switch (value) {
                case WindowFormat::Unknown:
                    break;
                case Free:
                    Helper::Debug::Error("WindowFormat : for setting \"free-size\" window use different constructor!");
                    break;
                case WindowFormat::_640_360:
                    this->m_width = 640;
                    this->m_height = 360;
                    break;
                case WindowFormat::_1280_720:
                    this->m_width = 1280;
                    this->m_height = 720;
                    break;
                case WindowFormat::_1366_768:
                    this->m_width = 1366;
                    this->m_height = 768;
                    break;
                case WindowFormat::_1600_900:
                    this->m_width = 1600;
                    this->m_height = 900;
                    break;
                default:
                    Helper::Debug::Error("WindowFormat : unknown type " + std::to_string((int)value) + "!");
                    break;
            }
        }
    public:
        [[nodiscard]] Value GetValue() const noexcept { return value; }

        [[nodiscard]] unsigned int Width() const noexcept { return m_width; }
        [[nodiscard]] unsigned int Height() const noexcept { return m_height; }
        [[nodiscard]] float GetRatio() const noexcept {
            if (value == Value::Free)
                return 16.0 / 9.0;
            else
                return (float)m_width / (float)m_height;
        }
    private:
        Value value;
        unsigned int m_width  = 0;
        unsigned int m_height = 0;
    };
}

#endif //GAMEENGINE_WINDOWFORMAT_H
