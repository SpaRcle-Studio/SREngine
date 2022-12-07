//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_MATERIAL_H
#define GAMEENGINE_MATERIAL_H

#include <Utils/ResourceManager/IResource.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>

#include <Graphics/Loaders/ShaderProperties.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GRAPH_NS {
    class RenderContext;
}

namespace SR_GTYPES_NS {
    class Mesh;
    class Mesh3D;
    class Texture;
    class Shader;

    class Material : public SR_UTILS_NS::IResource {
        friend class Mesh;
        friend class Mesh3D;

        using Super = SR_UTILS_NS::IResource;
        using PipelinePtr = Environment*;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;

    private:
        Material();
        ~Material() override = default;

    public:
        static Material* Load(SR_UTILS_NS::Path rawPath);

    public:
        Super* Copy(Super* destination) const override;

        SR_NODISCARD bool IsTransparent() const;
        SR_NODISCARD Shader* GetShader() const { return m_shader; }
        SR_NODISCARD MaterialProperties& GetProperties() { return m_properties; }
        SR_NODISCARD MaterialProperty* GetProperty(const std::string& id);
        SR_NODISCARD MaterialProperty* GetProperty(uint64_t hashId);
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;

        void SetTexture(MaterialProperty* property, Texture* pTexture);

        void OnResourceUpdated(IResource* pResource, int32_t depth) override;

        void SetShader(Shader* shader);

        void Use();
        void UseSamplers();
        bool Destroy() override;

    private:
        bool Reload() override;
        bool Load() override;
        bool Unload() override;

        void InitContext();

        bool LoadProperties(const SR_XML_NS::Node& propertiesNode);

    private:
        Types::Shader*     m_shader      = nullptr;
        std::atomic<bool>  m_dirtyShader = false;
        MaterialProperties m_properties  = { };
        RenderContextPtr   m_context     = { };

    };
}

#endif //GAMEENGINE_MATERIAL_H
