

# File HTMLDrawerPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**HTMLDrawerPass.h**](HTMLDrawerPass_8h.md)

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


