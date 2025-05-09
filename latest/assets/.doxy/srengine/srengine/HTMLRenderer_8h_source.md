

# File HTMLRenderer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Render**](dir_5ea2fe9b8fa53724ec2c57fac60d8202.md) **>** [**HTMLRenderer.h**](HTMLRenderer_8h.md)

[Go to the documentation of this file](HTMLRenderer_8h.md)


```C++
//
// Created by Monika on 14.08.2024.
//

#ifndef SR_ENGINE_GRAPHICS_HTML_RENDERER_H
#define SR_ENGINE_GRAPHICS_HTML_RENDERER_H

#include <Graphics/macros.h>

#include <Graphics/Render/HTML/HTMLDrawableElement.h>

namespace SR_GRAPH_NS {
    class TextBuilder;

#ifdef SR_COMMON_LITEHTML
    class HTMLRenderContainer : public SR_UTILS_NS::Web::HTMLContainerInterface {
        using Super = SR_UTILS_NS::Web::HTMLContainerInterface;
        struct ShaderInfo {
            SR_GTYPES_NS::Shader::Ptr pShader;

            uint32_t index = 0;

            struct MemInfo {
                Memory::UBOManager::VirtualUBO virtualUBO;
                DescriptorManager::VirtualDescriptorSet virtualDescriptor;
            };

            std::vector<MemInfo> UBOs;
        };
        struct TextAtlas {
            int32_t id;
            std::string text;
            SR_GRAPH_NS::TextBuilder* pTextBuilderRef;
        };
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<HTMLRenderContainer>;

    public:
        HTMLRenderContainer();
        ~HTMLRenderContainer() override;

        virtual bool Init();
        virtual void DeInit();

        virtual void Draw();
        virtual void Update();

        void SetCamera(const SR_GTYPES_NS::Camera::Ptr& pCamera) { m_pCamera = pCamera; }
        void SetPipeline(Pipeline* pipeline) { m_pipeline = pipeline; }

    private:
        void get_media_features(litehtml::media_features& media) const override;
        void get_client_rect(litehtml::position& client) const override;

        litehtml::uint_ptr create_font(const char* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) override;
        void delete_font(litehtml::uint_ptr hFont) override;

        SR_NODISCARD int32_t text_width(const char* text, litehtml::uint_ptr hFont) override;

        void draw_solid_fill(litehtml::uint_ptr hdc, const litehtml::background_layer& layer, const litehtml::web_color& color) override;
        void draw_text(litehtml::uint_ptr hdc, const char* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) override;

        litehtml::element::ptr create_element(const char* tag_name, const litehtml::string_map& attributes, const std::shared_ptr<litehtml::document>& doc) override;

    private:
        bool BeginElement(ShaderInfo& shaderInfo);
        void DrawElement(ShaderInfo& shaderInfo);
        void UpdateElement(ShaderInfo& shaderInfo);
        void EndElement(ShaderInfo& shaderInfo);

        SR_NODISCARD TextAtlas* GetTextAtlas(const char* text, TextBuilder* pTextBuilder);

        void ClearTextAtlases();

    private:
        SR_MATH_NS::IVector2 m_scroll;

        SR_GRAPH_NS::Memory::UBOManager& m_uboManager;
        SR_GRAPH_NS::DescriptorManager& m_descriptorManager;

        SR_MATH_NS::FVector2 m_viewSize;

        bool m_isRendered = false;
        bool m_updateMode = false;
        Pipeline* m_pipeline = nullptr;
        SR_GTYPES_NS::Camera::Ptr m_pCamera = nullptr;

        struct TextBuilderInfo {
            TextBuilder* pTextBuilder;
            SR_UTILS_NS::StringAtom fontName;
        };
        std::vector<TextBuilderInfo> m_textBuilders;

        std::map<SR_UTILS_NS::StringAtom, ShaderInfo> m_shaders;
        std::vector<TextAtlas> m_textAtlases;
    };
#endif //SR_COMMON_LITEHTML
}

#endif //SR_ENGINE_GRAPHICS_HTML_RENDERER_H
```


