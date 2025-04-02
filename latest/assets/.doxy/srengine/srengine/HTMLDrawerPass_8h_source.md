

# File HTMLDrawerPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**HTMLDrawerPass.h**](HTMLDrawerPass_8h.md)

[Go to the documentation of this file](HTMLDrawerPass_8h.md)


```C++
//
// Created by Monika on 15.08.2024.
//

#ifndef SR_ENGINE_HTML_DRAWER_PASS_H
#define SR_ENGINE_HTML_DRAWER_PASS_H

#include <Graphics/Pass/BasePass.h>
#include <Graphics/Render/HTMLRenderer.h>

namespace SR_GRAPH_NS {
#ifdef SR_COMMON_LITEHTML
    class HTMLDrawerPass : public BasePass {
        SR_REGISTER_LOGICAL_NODE(HTMLDrawerPass, HTML Drawer Pass, { "Passes" })
        using Super = BasePass;
    public:
        ~HTMLDrawerPass() override;

        bool Load(const SR_XML_NS::Node& passNode) override;

        void Prepare() override;
        bool Render() override;
        void Update() override;

        bool Init() override;
        void DeInit() override;

        void OnResize(const SR_MATH_NS::UVector2& size) override;

    private:
        bool LoadPage(const SR_UTILS_NS::Path& path);
        void UnloadPage();
        bool ReloadPage();
        void AddWatcher(const SR_UTILS_NS::Path& path);
        void InitRenderer();

    private:
        SR_UTILS_NS::Path m_pagePath;
        std::vector<SR_UTILS_NS::FileWatcher::Ptr> m_fileWatchers;
        SR_UTILS_NS::Web::HTMLPage::Ptr m_pPage = nullptr;
        std::atomic<uint16_t> m_needReloadPage = false;

    };
#endif //SR_COMMON_LITEHTML
}

#endif //SR_ENGINE_HTML_DRAWER_PASS_H
```


