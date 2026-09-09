//
// Created by Monika on 23.09.2025.
//

#ifndef SR_ENGINE_GUI_CREATE_NEW_PROJECT_H
#define SR_ENGINE_GUI_CREATE_NEW_PROJECT_H

#include <Engine/stdInclude.h>

#include <Graphics/GUI/WidgetManager.h>
#include <Graphics/GUI/Widget.h>

#include <Utils/FileSystem/VFS.h>

namespace SR_CORE_GUI_NS {
    class SR_CORE_DLL_API CreateNewProject : public SR_GRAPH_GUI_NS::Widget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        CreateNewProject();
        ~CreateNewProject() override;

    public:
        void Draw() override;
        void OnOpen() override;

    private:
        bool CreateProject();
        void ResetSettings();
        void SaveLastProjectPath();
        void SetProjectPath(const SR_UTILS_NS::Path& path);

    private:
        SR_UTILS_NS::IVFSBackend* m_pVFSBackend = nullptr;
        std::string m_projectName;
        std::string m_projectPathInput;
        SR_UTILS_NS::Path m_projectFinalPath;
        SR_UTILS_NS::Path m_projectPath;
        SR_UTILS_NS::Path m_lastProjectPath;

    };
}

#endif //SR_ENGINE_GUI_CREATE_NEW_PROJECT_H
