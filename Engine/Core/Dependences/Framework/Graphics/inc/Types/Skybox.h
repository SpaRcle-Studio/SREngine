//
// Created by Nikita on 20.11.2020.
//

#ifndef GAMEENGINE_SKYBOX_H
#define GAMEENGINE_SKYBOX_H

#include <Utils/NonCopyable.h>
#include <Types/Texture.h>
#include <vector>
#include <array>
#include <Environment/Environment.h>
#include <glm/glm.hpp>

namespace Framework::Graphics {
    class Camera;
    class Shader;
}

namespace Framework::Graphics::Types {
    class Skybox : Helper::NonCopyable {
    private:
        Skybox();
        ~Skybox() override = default;

    public:
        static Skybox* Load(const std::string& name);

    public:
        SR_NODISCARD std::string GetName() const { return m_name; }

        /// WARNING: Call only from render!
        bool FreeVideoMemory();

        bool SetRender(Render* render);
        void DrawOpenGL();
        void DrawVulkan();

        bool AwaitFreeVideoMemory();
        bool Free();
        bool Calculate();

    private:
        Environment*            m_env            = nullptr;
        Render*                 m_render         = nullptr;
        Shader*                 m_shader         = nullptr;

        int32_t                 m_VAO            = -1;
        int32_t                 m_VBO            = -1;
        int32_t                 m_IBO            = -1;
        int32_t                 m_descriptorSet  = -1;
        int32_t                 m_cubeMap        = -1;

        uint32_t                m_width          = 0;
        uint32_t                m_height         = 0;

        std::array<uint8_t*, 6> m_data           = std::array<uint8_t*, 6>();

        std::atomic<bool>       m_hasErrors      = false;
        std::atomic<bool>       m_isCalculated   = false;
        std::atomic<bool>       m_isVideoMemFree = false;

        std::string             m_name           = "Unnamed";

    };
}

#endif //GAMEENGINE_SKYBOX_H
