//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MATERIAL_H
#define GAMEENGINE_MATERIAL_H

#include "Types/Texture.h"
#include <glm/glm.hpp>

namespace Framework::Graphics::Types {
    using namespace Helper;

    class Mesh;
    class Material {
        friend class Mesh;
    public:
        Material(Texture* diffuse, Texture* normal, Texture* specular, Texture* glossiness);
        ~Material();
    private:
        bool        m_transparent  = false;
        bool        m_bloom        = false;

        glm::vec3   m_color        = glm::vec3(1,1,1);

        Mesh*       m_mesh         = nullptr;

        Texture*    m_diffuse      = nullptr;
        Texture*    m_normal       = nullptr;
        Texture*    m_specular     = nullptr;
        Texture*    m_glossiness   = nullptr;
    private:
        [[nodiscard]] static inline int RandomNumber(int a, int b) noexcept { return rand()%(b-a+1) + a; }
    public:
        static glm::vec3 GetRandomColor();
    public:
        [[nodiscard]] inline bool IsTransparent() const noexcept { return m_transparent; };
        bool SetTransparent(bool value);
        bool SetMesh(Mesh* mesh);
        inline void SetBloom(bool value) noexcept { this->m_bloom = value; };

        inline void SetColor(glm::vec3 color) { this->m_color = color; }

        void SetDiffuse(Texture* tex);
        void SetNormal(Texture* tex);
        void SetSpecular(Texture* tex);
        void SetGlossiness(Texture* tex);

        Material* Copy();
    };
}

#endif //GAMEENGINE_MATERIAL_H
