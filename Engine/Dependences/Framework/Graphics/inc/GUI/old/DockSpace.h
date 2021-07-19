//
// Created by Nikita on 14.01.2021.
//

#ifndef GAMEENGINE_DOCKSPACE_H
#define GAMEENGINE_DOCKSPACE_H

namespace Framework::Graphics::GUI {
    class DockSpace {
    public:
        DockSpace()                 = delete;
        DockSpace(DockSpace&)       = delete;
        DockSpace(const DockSpace&) = delete;
        ~DockSpace()                = delete;
    public:
        static void Begin();
    };
}

#endif //GAMEENGINE_DOCKSPACE_H
