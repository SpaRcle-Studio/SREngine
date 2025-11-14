//
// Created by Monika on 23.09.2025.
//

#ifndef SR_ENGINE_GUI_CREATE_NEW_PROJECT_H
#define SR_ENGINE_GUI_CREATE_NEW_PROJECT_H

#include <Engine/macros.h>

#include <Graphics/GUI/WidgetManager.h>
#include <Graphics/GUI/Widget.h>

/**
 * Widget allowing the user to create a new project by entering name and path.
 */
 
/**
 * Initialize the CreateNewProject widget.
 */
 
/**
 * Render the create-new-project widget UI and handle its interactive elements.
 */
 
/**
 * Handle actions to perform when the widget is opened (e.g., focus inputs or refresh state).
 */
 
/**
 * Create a new project using the current input values and resolved paths.
 * @returns `true` if the project was created successfully, `false` otherwise.
 */
 
/**
 * Reset the widget's input fields and internal path state to their default values.
 */
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