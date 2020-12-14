//
// Created by Nikita on 14.12.2020.
//

#ifndef GAMEENGINE_UNITTESTS_H
#define GAMEENGINE_UNITTESTS_H

#include <Debug.h>
#include <Render/Render.h>
#include <Window/Window.h>
#include <ResourceManager/ResourceManager.h>

using namespace Framework::Helper;
using namespace Framework::Helper::Math;
using namespace Framework::Helper::Types;
using namespace Framework::Graphics;
using namespace Framework::Graphics::Types;

inline static Render* g_render = nullptr;
inline static Window* g_window = nullptr;
inline static Scene*  g_scene  = nullptr;

static inline bool TestGameObjectInstancing() {

}

static inline bool TestProgram(Window* window, Render* render, Scene* scene) {
    g_window = window;
    g_render = render;
    g_scene  = scene;

    return true;
}

#endif //GAMEENGINE_UNITTESTS_H
