//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MATERIAL_H
#define GAMEENGINE_MATERIAL_H

#include <Utils/ResourceManager/IResource.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>

#include <Environment/Basic/IShaderProgram.h>

namespace SR_GRAPH_NS {
    class Shader;
}

namespace SR_GTYPES_NS {
    class Mesh;
    class Mesh3D;
    class Texture;

    class Material : public SR_UTILS_NS::IResource {
        friend class Mesh;
        friend class Mesh3D;

        struct Property {
            std::string id;
            std::string displayName;
            ShaderPropertyVariant data;
            ShaderVarType type;
        };

        using Properties = std::list<Property>;
        using Super = SR_UTILS_NS::IResource;

    private:
        Material();
        ~Material() override = default;

    public:
        static Material* GetDefault();
        static bool FreeDefault();
        static bool InitDefault(Render* render);

        static Material* Load(const std::string& path);

    public:
        Super* Copy(Super* destination) const override;

        SR_NODISCARD bool IsBloomEnabled() const { return m_bloom;  }
        SR_NODISCARD bool IsTransparent() const { return m_transparent;  }
        SR_NODISCARD Shader* GetShader() const { return m_shader; }
        SR_NODISCARD Properties& GetProperties() { return m_properties; }
        SR_NODISCARD Property* GetProperty(const std::string& id);
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;

        void SetTexture(Property* property, Texture* pTexture);

        void OnResourceUpdated(IResource* pResource, int32_t depth) override;

        void SetShader(Shader* shader);
        void SetBloom(bool value);
        bool SetTransparent(bool value);

        void Use();
        void UseSamplers();

    protected:
        bool Reload() override;

    private:
        void InitShader();
        bool Destroy() override;

    private:
        SR_INLINE_STATIC Material*   m_default       = nullptr;

        const Environment*           m_env           = nullptr;
        Shader*                      m_shader        = nullptr;

        std::atomic<bool>            m_dirtyShader   = false;
        std::atomic<bool>            m_transparent   = false;
        std::atomic<bool>            m_bloom         = false;

        Properties                   m_properties    = Properties();

    };
}

#endif //GAMEENGINE_MATERIAL_H
