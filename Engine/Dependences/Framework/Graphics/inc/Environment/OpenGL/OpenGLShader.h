//
// Created by Nikita on 29.03.2021.
//

#ifndef GAMEENGINE_OPENGLSHADER_H
#define GAMEENGINE_OPENGLSHADER_H

#include <Environment/Basic/IShaderProgram.h>

namespace Framework::Graphics {
    class OpenGLShader : public IShaderProgram {
    public:
        unsigned __int32 m_programID = 0;
        unsigned __int32 m_fragment  = 0;
        unsigned __int32 m_vertex    = 0;
    };
}

#endif //GAMEENGINE_OPENGLSHADER_H
