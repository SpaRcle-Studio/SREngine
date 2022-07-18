//
// Created by Nikita on 28.01.2021.
//

#ifndef GAMEENGINE_EDITORGRID_H
#define GAMEENGINE_EDITORGRID_H

/*
#include <Environment/Environment.h>

namespace SR_GRAPH_NS::Types {
    class Camera;
    class Shader;
}

namespace Framework::Graphics {
    class Render;

    class EditorGrid {
    private:
        EditorGrid(const std::string& shaderName, Render* render);
        ~EditorGrid();
    public:
        EditorGrid(EditorGrid&) = delete;
    public:
        static EditorGrid* Create(const std::string& shaderName, Render* render);
    private:
        Environment* m_env           = nullptr;
        Shader*      m_shader        = nullptr;
        Render*      m_render        = nullptr;
        bool         m_isCalculated  = false;
        bool         m_hasErrors     = false;
        unsigned int VAO             = 0;
    private:
        bool Calculate();
    public:
        ///\warning Call only from OpenGL context!
        void Free();
        ///\warning Call only from OpenGL context!
        void Draw();
    };
}*/

#endif //GAMEENGINE_EDITORGRID_H
