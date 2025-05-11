

# File MaterialData.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Material**](dir_d7c89fdc4b5407f55bdfbb167bac987a.md) **>** [**MaterialData.h**](MaterialData_8h.md)

[Go to the documentation of this file](MaterialData_8h.md)


```C++
//
// Created by Monika on 08.02.2025.
//

#ifndef SR_ENGINE_GRAPHICS_MATERIAL_DATA_H
#define SR_ENGINE_GRAPHICS_MATERIAL_DATA_H

#include <Utils/Serialization/Serializable.h>

#include <Graphics/Types/Shader.h>

namespace SR_GRAPH_NS {
    /*SR_ENUM_NS_CLASS_T(MaterialShader, uint16_t,
        Default,
        Simple,
        Shadows, SSAO, HDAO, HBAO, VXAO, Bloom,
        SSAOShadows, HDAOShadows, HBAOShadows, VXAOShadows,
        SSAOShadowsBloom
    );*/

    class MaterialData;

    enum class MaterialPropertyChangeResult : uint8_t {
        None, Error, Update, ReDraw
    };

    struct MaterialShaderProperty : public SR_UTILS_NS::Serializable {
        SR_STRUCT()
    private:
        using Super = SR_UTILS_NS::Serializable;

    public:
        void Save(SR_UTILS_NS::ISerializer& serializer) const override;
        bool Load(SR_UTILS_NS::IDeserializer& deserializer) override;

    public:
        uint32_t editorOrder = 0;
        SR_UTILS_NS::StringAtom displayName;
        ShaderPropertyVariant data;

        SR_UTILS_NS::StringAtom id;
        ShaderVarType type = ShaderVarType::Unknown;
        bool pushConstant = false;
    };

    struct MaterialShaderData : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        MaterialData* pOwnedMaterialData = nullptr;
        SR_GTYPES_NS::Shader* pShader = nullptr;

        std::vector<MaterialShaderProperty> uniforms;
        std::vector<MaterialShaderProperty> samplers;

        void OnPreLoad() override;
        void OnPostLoad() override;

        void ForEachProperty(const SR_HTYPES_NS::Function<void(MaterialShaderProperty&)>& func);

        MaterialPropertyChangeResult SR_FASTCALL SetData(SR_UTILS_NS::StringAtom id, const ShaderPropertyVariant& v, ShaderVarType type) noexcept;
        void UpdateProperties();

    };

    class MaterialData final : public SR_UTILS_NS::Serializable
        , public SR_UTILS_NS::NonCopyable
        , public SR_HTYPES_NS::SharedPtr<MaterialData>
        , public SR_UTILS_NS::SubscriptionHolder
    {
        using Super = SR_UTILS_NS::Serializable;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<MaterialData>;

        SR_INLINE_STATIC const SR_UTILS_NS::StringAtom PROPERTY_CHANGED_EVENT = "PropertyChanged";
        SR_INLINE_STATIC const SR_UTILS_NS::StringAtom SHADER_CHANGED_EVENT = "ShaderChanged";
        SR_INLINE_STATIC const SR_UTILS_NS::StringAtom ONLY_UNIFORMS_BOOL_ID = "OnlyUniforms";

        MaterialData();
        ~MaterialData() override;

        void Save(SR_UTILS_NS::ISerializer& serializer) const override;
        bool Load(SR_UTILS_NS::IDeserializer& deserializer) override;

        SR_NODISCARD SR_GTYPES_NS::Shader* GetShader(const Pipeline* pPipeline) const noexcept;

        void Finalize();

        void UseUniforms(const Pipeline* pPipeline);
        void UseSamplers(const Pipeline* pPipeline);

        SR_NODISCARD MaterialShaderData& GetDefaultShaderData() noexcept { return m_defaultShader; }
        SR_NODISCARD const MaterialShaderData& GetDefaultShaderData() const noexcept { return m_defaultShader; }
        SR_NODISCARD const std::map<SR_UTILS_NS::StringAtom, MaterialShaderData>& GetShadersData() const noexcept { return m_shaders; }
        SR_NODISCARD std::map<SR_UTILS_NS::StringAtom, MaterialShaderData>& GetShadersData() noexcept { return m_shaders; }
        SR_NODISCARD MaterialShaderData* GetShaderData(SR_UTILS_NS::StringAtom id) noexcept;
        SR_NODISCARD const MaterialShaderData* GetShaderData(SR_UTILS_NS::StringAtom id) const noexcept;

        void SR_FASTCALL SetSampler(SR_UTILS_NS::StringAtom id, const SR_UTILS_NS::Path& path) noexcept;
        void SR_FASTCALL SetShader(const SR_UTILS_NS::Path& path, SR_UTILS_NS::StringAtom stage = SR_UTILS_NS::StringAtom());
        void SR_FASTCALL SetShader(SR_GTYPES_NS::Shader* pShader, SR_UTILS_NS::StringAtom stage = SR_UTILS_NS::StringAtom());
        void SR_FASTCALL SetData(SR_UTILS_NS::StringAtom id, const ShaderPropertyVariant& v, ShaderVarType type) noexcept;
        void SR_FASTCALL OnSamplerChanged(SR_GTYPES_NS::Texture* pOldTexture, SR_GTYPES_NS::Texture* pNewTexture) noexcept;

        void RemoveStage(SR_UTILS_NS::StringAtom stage);
        void OnPropertyChanged(bool onlyUniforms);

    private:
        void OnShaderChanged();

    private:
        std::map<SR_GTYPES_NS::Shader*, std::pair<SR_UTILS_NS::Subscription, uint32_t>> m_shaderSubscriptions;
        std::map<SR_GTYPES_NS::Texture*, std::pair<SR_UTILS_NS::Subscription, uint32_t>> m_textureSubscriptions;
        MaterialShaderData m_defaultShader;
        std::map<SR_UTILS_NS::StringAtom, MaterialShaderData> m_shaders;

    };
}

#endif //SR_ENGINE_GRAPHICS_MATERIAL_DATA_H
```


