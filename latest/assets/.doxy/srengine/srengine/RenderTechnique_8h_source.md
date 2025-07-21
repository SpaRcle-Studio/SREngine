

# File RenderTechnique.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**RenderTechnique.h**](RenderTechnique_8h.md)

[Go to the documentation of this file](RenderTechnique_8h.md)


```C++
//
// Created by Monika on 17.07.2022.
//

#ifndef SR_ENGINE_RENDERTECHNIQUE_H
#define SR_ENGINE_RENDERTECHNIQUE_H

#include <Graphics/Render/IRenderTechnique.h>

namespace SR_GRAPH_NS {
    class FileRenderTechniqueResource;

    class FileRenderTechnique : public IRenderTechnique {
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<FileRenderTechnique>;

    public:
        FileRenderTechnique() = default;
        ~FileRenderTechnique() override;

    public:
        static FileRenderTechnique::Ptr Load(const SR_UTILS_NS::Path& path);

    protected:
        bool Build() override;

    private:
        void LoadPass(const SR_XML_NS::Node& node);
        void ProcessNode(const SR_XML_NS::Node& passNode);

        void SetResource(const SR_HTYPES_NS::SharedPtr<FileRenderTechniqueResource>& pResource);

    private:
        SR_HTYPES_NS::SharedPtr<FileRenderTechniqueResource> m_resource;

    };

    class FileRenderTechniqueResource : public SR_UTILS_NS::Settings {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<FileRenderTechniqueResource>;

    public:
        FileRenderTechniqueResource() = default;

    public:
        static FileRenderTechniqueResource::Ptr Load(const SR_UTILS_NS::Path& path);

    public:
        void RegisterRenderTechnique(const FileRenderTechnique::Ptr& renderTechnique) {
            m_renderTechniques.insert(renderTechnique);
        }

        void UnregisterRenderTechnique(const FileRenderTechnique::Ptr& renderTechnique) {
            m_renderTechniques.erase(renderTechnique);
        }

        SR_NODISCARD bool IsAllowedMultiInstance() const override { return true; }

    protected:
        bool Load() override;
        bool Unload() override;

    protected:
        std::set<FileRenderTechnique::Ptr> m_renderTechniques;

    };
}

#endif //SR_ENGINE_RENDERTECHNIQUE_H
```


