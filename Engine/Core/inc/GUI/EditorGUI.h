//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_EDITORGUI_H
#define GAMEENGINE_EDITORGUI_H

#include <GUI/ICanvas.h>
#include <Base/Script.h>
#include <Base/Compiler.h>
#include <GUI/WidgetManager.h>
#include <GUI/Editor/Hierarchy.h>
#include <GUI/Editor/SceneViewer.h>

namespace SR_GRAPH_NS::GUI {
    class FileBrowser;
}

namespace Framework::Core::GUI {
    class VisualScriptEditor;
    class Inspector;
    class WorldEdit;

    class EditorGUI : public SR_GRAPH_NS::GUI::WidgetManager {
    public:
        explicit EditorGUI(Scripting::Compiler* compiler);

    private:
        ~EditorGUI() override;

    public:
        void Enable(bool value);
        bool Destroy();
        void Free();

        SR_NODISCARD SR_GRAPH_NS::GUI::FileBrowser* GetFileBrowser() const { return m_fileBrowser; }
        SR_NODISCARD SR_GRAPH_NS::GUI::Hierarchy* GetHierarchy() const { return m_hierarchy; }
        SR_NODISCARD SR_GRAPH_NS::GUI::SceneViewer* GetSceneViewer() const { return m_sceneViewer; }
        SR_NODISCARD VisualScriptEditor* GetVisualScriptEditor() const { return m_scriptEditor; }
        SR_NODISCARD WorldEdit* GetWorldEdit() const { return m_worldEdit; }
        SR_NODISCARD Inspector* GetInspector() const { return m_inspector; }
        SR_NODISCARD bool Enabled() const { return m_enabled; }

        void Draw() override;
        void Update();

    private:
        bool Init();
        void Save();
        void Load();

    private:
        Graphics::Window*              m_window       = nullptr;
        Scripting::Compiler*           m_compiler     = nullptr;
        Scripting::Script*             m_script       = nullptr;
        VisualScriptEditor*            m_scriptEditor = nullptr;
        WorldEdit*                     m_worldEdit    = nullptr;
        Inspector*                     m_inspector    = nullptr;
        SR_GRAPH_NS::GUI::FileBrowser* m_fileBrowser  = nullptr;
        SR_GRAPH_NS::GUI::SceneViewer* m_sceneViewer  = nullptr;
        SR_GRAPH_NS::GUI::Hierarchy*   m_hierarchy    = nullptr;
        std::atomic<bool>              m_isInit       = false;
        std::atomic<bool>              m_hasErrors    = false;
        std::atomic<bool>              m_enabled      = false;

    };
}

#endif //GAMEENGINE_EDITORGUI_H
