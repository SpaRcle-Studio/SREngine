

# File CreateNewProject.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**CreateNewProject.h**](CreateNewProject_8h.md)

[Go to the documentation of this file](CreateNewProject_8h.md)


```C++
//
// Created by Monika on 23.09.2025.
//

#ifndef SR_ENGINE_GUI_CREATE_NEW_PROJECT_H
#define SR_ENGINE_GUI_CREATE_NEW_PROJECT_H

#include <Engine/macros.h>

#include <Graphics/GUI/WidgetManager.h>

namespace SR_CORE_GUI_NS {
    class SR_CORE_DLL_API CreateNewProject : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        CreateNewProject();

    public:
        void Draw() override;
        void OnOpen() override;

    private:
        bool CreateProject();
        void ResetSettings();

    private:
        std::string m_projectName;
        std::string m_projectPathInput;
        SR_UTILS_NS::Path m_projectFinalPath;
        SR_UTILS_NS::Path m_projectPath;

    };
}

#endif //SR_ENGINE_GUI_CREATE_NEW_PROJECT_H
```


