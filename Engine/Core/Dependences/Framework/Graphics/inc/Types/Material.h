//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MATERIAL_H
#define GAMEENGINE_MATERIAL_H

#include <ResourceManager/IResource.h>

#include <Math/Vector3.h>
#include <Math/Vector4.h>

namespace SR_GRAPH_NS {
    class Shader;
}

namespace SR_GRAPH_NS::Types {
    class Mesh;
    class Mesh3D;
    class Texture;

    SR_ENUM(MatProperty,
        /// Texture*

        MAT_PROPERTY_DIFFUSE_TEXTURE,
        MAT_PROPERTY_NORMAL_TEXTURE,
        MAT_PROPERTY_SPECULAR_TEXTURE,
        MAT_PROPERTY_GLOSSINESS_TEXTURE,
        MAT_PROPERTY_AMBIENT_TEXTURE,
        MAT_PROPERTY_EMISSIVE_TEXTURE,
        MAT_PROPERTY_HEIGHT_TEXTURE,
        MAT_PROPERTY_OPACITY_TEXTURE,
        MAT_PROPERTY_DISPLACEMENT_TEXTURE,
        MAT_PROPERTY_LIGHTMAP_TEXTURE,
        MAT_PROPERTY_REFLECTION_TEXTURE,

        /// FColor

        MAT_PROPERTY_DIFFUSE_COLOR,
        MAT_PROPERTY_SPECULAR_COLOR,
        MAT_PROPERTY_AMBIENT_COLOR,
        MAT_PROPERTY_EMISSIVE_COLOR,

        /// float

        MAT_PROPERTY_SHININESS,

        MAT_PROPERTY_MAX_ENUM
    );

    inline static const MatProperty MAT_COLOR_PROPERTIES[] = {
            MAT_PROPERTY_DIFFUSE_COLOR,
            MAT_PROPERTY_SPECULAR_COLOR,
            MAT_PROPERTY_AMBIENT_COLOR,
            MAT_PROPERTY_EMISSIVE_COLOR,
    };

    inline static const MatProperty MAT_TEXTURE_PROPERTIES[] = {
            MAT_PROPERTY_DIFFUSE_TEXTURE,
            MAT_PROPERTY_NORMAL_TEXTURE,
            MAT_PROPERTY_SPECULAR_TEXTURE,
            MAT_PROPERTY_GLOSSINESS_TEXTURE,
            MAT_PROPERTY_AMBIENT_TEXTURE,
            MAT_PROPERTY_EMISSIVE_TEXTURE,
            MAT_PROPERTY_HEIGHT_TEXTURE,
            MAT_PROPERTY_OPACITY_TEXTURE,
            MAT_PROPERTY_DISPLACEMENT_TEXTURE,
            MAT_PROPERTY_LIGHTMAP_TEXTURE,
            MAT_PROPERTY_REFLECTION_TEXTURE,
    };

    class Material : public Helper::IResource {
        friend class Mesh;
        friend class Mesh3D;

        using Property = std::variant<Texture*, SR_MATH_NS::FColor, float_t>;
        using Properties = std::array<Property, MAT_PROPERTY_MAX_ENUM>;

    private:
        Material();
        Material(Texture* diffuse, Texture* normal, Texture* specular, Texture* glossiness);

        ~Material() override;

    public:
        static Material* GetDefault();
        static bool FreeDefault();
        static bool InitDefault(Render* render);

        static Material* Load(const std::string& name);

    public:
        Helper::IResource* Copy(Helper::IResource* destination) const override;

        SR_NODISCARD bool IsBloomEnabled() const { return m_bloom;  }
        SR_NODISCARD bool IsTransparent() const { return m_transparent;  }
        SR_NODISCARD uint32_t GetCountSubscriptions() const;
        SR_NODISCARD Shader* GetShader() const { return m_shader; }

        void SetTexture(Texture* pTexture, MatProperty property);
        SR_NODISCARD Texture* GetTexture(MatProperty property) const;

        SR_NODISCARD SR_MATH_NS::FColor GetColor(MatProperty property) const;

        void SetColor(MatProperty property, float_t r, float_t g, float_t b);
        void SetColor(MatProperty property, float_t r, float_t g, float_t b, float_t a);
        void SetColor(MatProperty property, const SR_MATH_NS::FVector3& color);
        void SetColor(MatProperty property, const glm::vec4& color);
        void SetColor(MatProperty property, const SR_MATH_NS::FColor& color);

        void SetShader(Shader* shader);
        void SetBloom(bool value);
        bool SetTransparent(bool value);

        void UseVulkan();
        void UseOpenGL() const;

        void Subscribe(Mesh* mesh);
        void UnSubscribe(Mesh* mesh);

        bool Register(Render* render);

    private:
        bool Destroy() override;
        void UpdateSubscribers();

    private:
        SR_INLINE static Material*   m_default       = nullptr;

        std::unordered_set<Mesh*>    m_subscriptions = {};

        const Environment*           m_env           = nullptr;
        Render*                      m_render        = nullptr;
        Shader*                      m_shader        = nullptr;

        std::atomic<bool>            m_transparent   = false;
        std::atomic<bool>            m_bloom         = false;

        mutable std::recursive_mutex m_mutex         = std::recursive_mutex();

        Properties                   m_properties    = Properties();

    };
}

#endif //GAMEENGINE_MATERIAL_H
