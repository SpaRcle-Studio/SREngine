//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_GUISYSTEM_H
#define GAMEENGINE_GUISYSTEM_H

namespace Framework::Graphics::GUI {
    class GUISystem {
    private:
        GUISystem() = default;
        GUISystem(const GUISystem&) = default;
        ~GUISystem() = default;
    public:
        static GUISystem* Get() {
            static GUISystem* guiSystem = nullptr;
            if (!guiSystem)
                guiSystem = new GUISystem();
            return guiSystem;
        }
    public:
        void BeginDockSpace();
        void EndDockSpace();
        bool BeginWindow(const char* name);
        void EndWindow();
        bool BeginChildWindow(const char* name);
        void EndChildWindow();
    };
}

#endif //GAMEENGINE_GUISYSTEM_H
