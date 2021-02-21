//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MATERIAL_H
#define GAMEENGINE_MATERIAL_H

#include "Types/Texture.h"
#include <glm/glm.hpp>

#include <Render/Shader.h>

namespace Framework::Graphics::Types {
    using namespace Helper;

    class Mesh;
    class Material {
        friend class Mesh;
    public:
        Material(Texture* diffuse, Texture* normal, Texture* specular, Texture* glossiness);
        ~Material();
    private:
        inline static Environment*      m_env               = nullptr;

        bool                            m_transparent       = false;
        volatile bool                   m_bloom             = false;

        glm::vec4                       m_color             = glm::vec4(1,1,1,1);

        Mesh*                           m_mesh              = nullptr;

        volatile bool                   m_texturesIsFree    = false;

        Texture*                        m_diffuse           = nullptr;
        Texture*                        m_normal            = nullptr;
        Texture*                        m_specular          = nullptr;
        Texture*                        m_glossiness        = nullptr;
    private:
        [[nodiscard]] static inline int RandomNumber(int a, int b) noexcept { return rand()%(b-a+1) + a; }
    public:
        static glm::vec3 GetRandomColor();
    public:
        void Use() const noexcept;
    public:
        [[nodiscard]] inline bool IsTransparent() const noexcept { return m_transparent; };
        bool SetTransparent(bool value);
        bool SetMesh(Mesh* mesh);
        inline void SetBloom(bool value) noexcept { this->m_bloom = value; };
        [[nodiscard]] inline bool GetBloomEnabled() const noexcept { return this->m_bloom; };

        inline void SetColor(glm::vec3 color) { this->m_color = {color,1}; }
        inline void SetColor(glm::vec4 color) { this->m_color = color; }

        [[nodiscard]] inline glm::vec3 GetColor() const noexcept { return this->m_color; }

        bool FreeTextures();

        void SetDiffuse(Texture* tex);
        void SetNormal(Texture* tex);
        void SetSpecular(Texture* tex);
        void SetGlossiness(Texture* tex);
    };
}

#endif //GAMEENGINE_MATERIAL_H
