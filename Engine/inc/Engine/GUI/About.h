//
// Created by Igor on 12/03/2023.
//

#ifndef SR_ENGINE_ABOUT_H
#define SR_ENGINE_ABOUT_H

#include <Engine/stdInclude.h>

#include <Graphics/GUI/Widget.h>
#include <Graphics/Types/Texture.h>

#include <Utils/Resources/ResourceRef.h>

namespace SR_CORE_GUI_NS {
    class About : public SR_GRAPH_GUI_NS::Widget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        About();

    protected:
        void Draw() override;

    private:
        void CollectBuildInfo();

    private:
        SR_UTILS_NS::ResourceRef<SR_GTYPES_NS::Texture> m_logo;
        /// высота содержимого, измеренная в прошлом кадре
        float_t m_contentHeight = 0.0f;

        SR_UTILS_NS::String m_commit;
        SR_UTILS_NS::String m_branch;
        SR_UTILS_NS::String m_commitDate;
        SR_UTILS_NS::String m_modulesHash;
        SR_UTILS_NS::String m_buildInfo;

    };
}

#endif //SR_ENGINE_ABOUT_H
