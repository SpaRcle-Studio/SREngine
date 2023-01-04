//
// Created by Nikita on 20.11.2020.
//

#ifndef GAMEENGINE_SKYBOX_H
#define GAMEENGINE_SKYBOX_H

#include <Utils/ResourceManager/IResource.h>
#include <Graphics/Memory/IGraphicsResource.h>

namespace SR_GRAPH_NS::Types {
    class Shader;
}

namespace SR_GRAPH_NS {
    class Render;
    class Environment;
}

namespace SR_GTYPES_NS {
    class Texture;

    class Skybox : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource {
    private:
        Skybox();
        ~Skybox() override;

    public:
        static Skybox* Load(const SR_UTILS_NS::Path& path);

    public:
        SR_NODISCARD Shader* GetShader() const { return m_shader; }
        SR_NODISCARD int32_t GetVBO();
        SR_NODISCARD int32_t GetIBO();
        SR_NODISCARD int32_t GetVirtualUBO();

        SR_NODISCARD bool IsAllowRevive() const override { return true; }

        void FreeVideoMemory() override;
        void Draw();

    protected:
        void OnResourceUpdated(IResource* pResource, int32_t depth) override;
        uint64_t GetFileHash() const override { return 0; }

    private:
        bool Calculate();
        void DrawOpenGL();
        void DrawVulkan();
        void SetShader(Shader *shader);

    private:
        Shader*                 m_shader         = nullptr;

        int32_t                 m_VAO            = SR_ID_INVALID;
        int32_t                 m_VBO            = SR_ID_INVALID;
        int32_t                 m_IBO            = SR_ID_INVALID;

        int32_t                 m_cubeMap        = SR_ID_INVALID;

        int32_t                 m_virtualUBO     = SR_ID_INVALID;

        uint32_t                m_width          = 0;
        uint32_t                m_height         = 0;

        std::array<uint8_t*, 6> m_data           = std::array<uint8_t*, 6>();

        std::atomic<bool>       m_hasErrors      = false;
        std::atomic<bool>       m_dirtyShader    = false;

    };
}

#endif //GAMEENGINE_SKYBOX_H
