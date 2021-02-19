//
// Created by Nikita on 18.02.2021.
//

#ifndef GAMEENGINE_COLORBUFFER_H
#define GAMEENGINE_COLORBUFFER_H

#include <glm/glm.hpp>
#include <vector>

namespace Framework::Graphics {
    class ColorBuffer {
        struct cbInfo_t {
            int Name;
            glm::u8vec3 Color; // uint8 => 0 - 255 (unsigned char)
        };
    public:
        ColorBuffer() = default;
        ~ColorBuffer() { Names.clear(); }
    private:
        std::vector<cbInfo_t> Names = std::vector<cbInfo_t>();
        size_t next = 0;
    public:
        inline void InitNames(size_t count_models) noexcept {
            if (count_models > Names.size())
                Names.resize(count_models);

            for (auto& a : Names) {
                a.Color = { 0, 0, 0 };
                a.Name = 0;
            }

            next = 0;
        }
        inline void LoadName(size_t OBJECT_ID, glm::u8vec3 color) noexcept {
            Names[next].Name = OBJECT_ID;
            Names[next].Color = color;
            next++;
        }
        //static inline bool CheckColor(glm::u8vec3& one, const unsigned char* two) noexcept {
        static inline bool CheckColor(glm::u8vec3& one, glm::u8vec3& two) noexcept {
            //return one.x == two[0] && one.y == two[1] && one.z == two[2];
            return one.x == two.x && one.y == two.y && one.z == two.z;
        }
        //inline int GetSelectColorObject(unsigned char* pixel) noexcept {
        inline int GetSelectColorObject(glm::u8vec3 pixel) noexcept {
            if (pixel != glm::u8vec3(0,0,0))
                for (int i = 0; i < next; i++) {
                    if (CheckColor(Names[i].Color, pixel))
                        return Names[i].Name;
                }
            return -1;
        }
    };
}

#endif //GAMEENGINE_COLORBUFFER_H
