

# File HTML.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Web**](dir_70f8c8659136766207f9e88b26ae6fb0.md) **>** [**HTML**](dir_af4ae9837b771a51caa1e83523f573f1.md) **>** [**HTML.h**](HTML_8h.md)

[Go to the documentation of this file](HTML_8h.md)


```C++
//
// Created by Monika on 15.08.2024.
//

#ifndef SR_COMMON_WEB_HTML_H
#define SR_COMMON_WEB_HTML_H

#include <Utils/Types/ObjectPool.h>
#include <Utils/Web/CSS/CSS.h>
#include <Utils/Web/HTML/Tag.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/PassKey.h>

#ifdef SR_COMMON_LITEHTML
    #include <litehtml.h>
#endif

namespace SR_UTILS_NS::Web {
    class HTMLPage;

#ifdef SR_COMMON_LITEHTML
    class HTMLContainerInterface : public SR_HTYPES_NS::SharedPtr<HTMLContainerInterface>, public litehtml::document_container {
        using Super = SR_HTYPES_NS::SharedPtr<HTMLContainerInterface>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<HTMLContainerInterface>;

        HTMLContainerInterface()
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        { }

        ~HTMLContainerInterface() override = default;

    public:
        litehtml::uint_ptr create_font(const char* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) override { return 0; }
        void delete_font(litehtml::uint_ptr hFont) override { }
        int                 text_width(const char* text, litehtml::uint_ptr hFont) override { return 0; }
        void                draw_text(litehtml::uint_ptr hdc, const char* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) override { }
        int pt_to_px(int pt) const override;
        int get_default_font_size() const override;
        const char* get_default_font_name() const override;
        void                draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker) override { }
        void                load_image(const char* src, const char* baseurl, bool redraw_on_ready) override { }
        void                get_image_size(const char* src, const char* baseurl, litehtml::size& sz) override { }
        void                draw_image(litehtml::uint_ptr hdc, const litehtml::background_layer& layer, const std::string& url, const std::string& base_url) override { }
        void draw_solid_fill(litehtml::uint_ptr hdc, const litehtml::background_layer& layer, const litehtml::web_color& color) override { }
        void                draw_linear_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer& layer, const litehtml::background_layer::linear_gradient& gradient) override { }
        void                draw_radial_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer& layer, const litehtml::background_layer::radial_gradient& gradient) override { }
        void                draw_conic_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer& layer, const litehtml::background_layer::conic_gradient& gradient) override { }
        void                draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root) override { }

        void                set_caption(const char* caption) override { }
        void                set_base_url(const char* base_url) override { }
        void                link(const std::shared_ptr<litehtml::document>& doc, const litehtml::element::ptr& el) override { }
        void                on_anchor_click(const char* url, const litehtml::element::ptr& el) override { }
        void                on_mouse_event(const litehtml::element::ptr& el, litehtml::mouse_event event) override { }
        void                set_cursor(const char* cursor) override { }
        void                transform_text(litehtml::string& text, litehtml::text_transform tt) override { }
        void import_css(litehtml::string& text, const litehtml::string& url, litehtml::string& baseurl) override;
        void                set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius) override { }
        void                del_clip() override { }
        void                get_client_rect(litehtml::position& client) const override { }
        litehtml::element::ptr  create_element( const char* tag_name,
                                                const litehtml::string_map& attributes,
                                                const std::shared_ptr<litehtml::document>& doc) override { return nullptr; }

        void get_media_features(litehtml::media_features& media) const override { }
        void get_language(litehtml::string& language, litehtml::string& culture) const override { }

    public:
        void AddPath(const SR_UTILS_NS::Path& path);
        void SetPage(HTMLPage* page) { m_page = page; }

        SR_NODISCARD const std::vector<SR_UTILS_NS::Path>& GetPaths() const { return m_paths; }
        SR_NODISCARD const SR_UTILS_NS::Path& GetPath() const;
        SR_NODISCARD HTMLPage* GetPage() const { return m_page; }

    private:
        HTMLPage* m_page = nullptr;
        std::vector<SR_UTILS_NS::Path> m_paths;

    };
#else
    class HTMLContainerInterface : public SR_HTYPES_NS::SharedPtr<HTMLContainerInterface> {

    };
#endif

    class HTMLPage final : public SR_HTYPES_NS::SharedPtr<HTMLPage> {
        using Super = SR_HTYPES_NS::SharedPtr<HTMLPage>;
    private:
        HTMLPage();

    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<HTMLPage>;

        ~HTMLPage();

    public:
        static Ptr Load(const SR_UTILS_NS::Path& path, const HTMLContainerInterface::Ptr& pContainer = nullptr);

        SR_NODISCARD const std::vector<SR_UTILS_NS::Path>& GetPaths() const;
        SR_NODISCARD HTMLContainerInterface::Ptr GetContainer() const { return m_container; }
    #ifdef SR_COMMON_LITEHTML
        SR_NODISCARD litehtml::document::ptr GetDocument() const { return m_document; }
    #else
        SR_NODISCARD void* GetDocument() const { return nullptr; }
    #endif

    protected:

    private:
        HTMLContainerInterface::Ptr m_container;
    #ifdef SR_COMMON_LITEHTML
        litehtml::document::ptr m_document;
    #else
        void* m_document;
    #endif

    };
}

#endif //SR_COMMON_WEB_HTML_H
```


