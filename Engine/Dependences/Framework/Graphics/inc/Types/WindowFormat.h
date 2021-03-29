//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_WINDOWFORMAT_H
#define GAMEENGINE_WINDOWFORMAT_H

#include <string>
#include <Debug.h>
#include <glm/glm.hpp>

namespace Framework::Graphics::Types {
    //using namespace Framework::Helper::Math;

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

        [[nodiscard]] static WindowFormat* AllocMemory() {
            return (WindowFormat*)malloc(sizeof(WindowFormat));
        }
        void FreeMemory() {
            free(this);
        }

        //WindowFormat(const glm::vec2& size) : value(Value::Free) {
        //    this->m_width = (unsigned int)size.x;
        //    this->m_height = (unsigned int)size.y;
       // }

        void SetPreset(const Value& preset) {
            this->value = preset;
            switch (preset) {
                case WindowFormat::Unknown:
                    break;
                case Free:
                    Helper::Debug::Error("WindowFormat::SetFormat() : for setting \"free-size\" window use different constructor!");
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
                    Helper::Debug::Error("WindowFormat::SetFormat() : unknown type " + std::to_string((int)value) + "!");
                    break;
            }
        }
        void SetFormat(const WindowFormat& windowFormat) {
            if (windowFormat.value == Value::Free) {
                this->m_height = windowFormat.m_height;
                this->m_width  = windowFormat.m_width;
                this->value    = Value::Free;
            } else
                this->SetPreset(windowFormat.value);
        }

        WindowFormat(Value v) {
            this->SetPreset(v);
        }
    public:
        [[nodiscard]] Value GetValue() const noexcept { return value; }

        inline void SetFreeValue(unsigned int w, unsigned int h) noexcept {
            this->value = Free;
            this->m_height = h;
            this->m_width = w;
        }

        [[nodiscard]] unsigned int Width() const noexcept { return m_width; }
        [[nodiscard]] unsigned int Height() const noexcept { return m_height; }
        [[nodiscard]] float GetRatio() const noexcept {
            if (value == Value::Free)
                return 16.0 / 9.0; // TODO: change
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
