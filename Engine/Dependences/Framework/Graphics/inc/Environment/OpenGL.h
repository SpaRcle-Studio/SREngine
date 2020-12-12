//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_OPENGL_H
#define GAMEENGINE_OPENGL_H

#include <Environment/Environment.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace Framework::Graphics {
    class OpenGL : public Environment {
        OpenGL(OpenGL&) = delete;
    public:
        OpenGL() = default;
        ~OpenGL() = default;
    private:
        GLFWwindow*             m_window          = nullptr;
        GLFWmonitor*            m_monitor         = nullptr;
        const GLFWvidmode*      m_vidMode         = nullptr;
    public:
        // ============================= [ WINDOW METHODS ] =============================

        bool MakeWindow(const char* winName, Types::WindowFormat* format, bool fullScreen) override;

        bool PreInit(unsigned int smooth_samples) override;
        bool SetContextCurrent() override;
        bool Init() override;
        bool PostInit() override;

        bool IsWindowOpen() override;
        bool CloseWindow() override;

        inline void ClearBuffers() noexcept override { glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); }
        inline void ClearColorBuffers(float r, float g, float b, float a) noexcept override { glClearColor(r, g, b, a); }
        inline void SwapBuffers() noexcept override  { glfwSwapBuffers(m_window); }

        void SetWindowSize(float ratio, unsigned int w, unsigned int h) override;
        void SetWindowPosition(int x, int y) override;

        glm::vec2 GetWindowSize() noexcept override {
            glm::vec2 val;
            glfwGetWindowSize(m_window, (int*)&val.x, (int*)&val.y);
            return val;
        }
        glm::vec2 GetWindowPosition() noexcept override {
            return {0,0};
        }



        void PoolEvents() override;

        inline std::string GetVendor()   override { return std::string((char*)glGetString(GL_VENDOR));      }
        inline std::string GetRenderer() override { return std::string((char*)glGetString(GL_RENDERER));    }
        inline std::string GetVersion()  override { return std::string((char*)glGetString(GL_VERSION));     }

        inline void SetCursorPosition(glm::vec2 pos) noexcept override {
            glfwSetCursorPos(m_window, pos.x, pos.y);
        }

        bool CreateHDRFrameBufferObject(glm::vec2 size,unsigned int& rboDepth,  unsigned int& hdrFBO, std::vector<unsigned int>& colorBuffers) override;
        bool CreatePingPongFrameBufferObject(glm::vec2 size,std::vector<unsigned int> & pingpongFBO, std::vector<unsigned int>& pingpongColorBuffers) override;

        inline void BindFrameBuffer(unsigned int FBO) const noexcept override {
            glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        }

        inline void DeleteBuffer(unsigned int& FBO) override {
        }

        // ============================= [ SHADER METHODS ] =============================

        bool CompileShader(std::string path, unsigned int* fragment, unsigned int* vertex) override;
        unsigned int LinkShader(unsigned int* fragment, unsigned int* vertex) override;
        inline void UseShader(unsigned int ID) noexcept override  { glUseProgram(ID); }

        inline void SetBool(unsigned int ID, const std::string& name, bool v)       const noexcept override {
            glUniform1iv(glGetUniformLocation(ID, name.c_str()), 1, (int*)&v);
        }
        inline void SetFloat(unsigned int ID, const std::string& name, float v)     const noexcept override {
            glUniform1fv(glGetUniformLocation(ID, name.c_str()), 1, &v);
        }
        inline void SetInt(unsigned int ID, const std::string& name, int v)         const noexcept override {
            glUniform1iv(glGetUniformLocation(ID, name.c_str()), 1, &v);
            //glUniform1i(glGetUniformLocation(ID, name.c_str()), v);
        }
        inline void SetMat4(unsigned int ID, const std::string& name, glm::mat4 v)  const noexcept override {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(v));
        }
        inline void SetVec4(unsigned int ID, const std::string& name, glm::vec4 v)  const noexcept override {  }
        inline void SetVec3(unsigned int ID, const std::string& name, glm::vec3 v)  const noexcept override {
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &v[0]);
        }
        inline void SetVec2(unsigned int ID, const std::string& name, glm::vec2 v)  const noexcept override {
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &v[0]);
        }

        // ============================== [ MESH METHODS ] ==============================

        inline bool CalculateMesh(unsigned int& VBO, unsigned int& VAO, std::vector<Vertex>& vertices, size_t count_verts) noexcept override{
            if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
                Helper::Debug::Log("OpenGL::CalculateMesh() : calculating " + std::to_string(vertices.size()) + " vertices...");

            glGenVertexArrays(1, (GLuint*)&VAO);
            glGenBuffers(1, (GLuint*)&VBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            {
                //? Binding vertex array
                glBufferData(
                        GL_ARRAY_BUFFER,
                        count_verts * sizeof(Vertex),
                        &vertices[0],
                        GL_STATIC_DRAW
                );

                //? Binding attrib vertex coordinates
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0,
                                      3, // glm::vec3 - has 3 floats
                                      GL_FLOAT, GL_FALSE,
                                      sizeof(Vertex), (void*)0);

                //? Binding attrib texture coordinates
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1,
                                      2, // glm::vec2 - has 2 floats
                                      GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                      (void*)offsetof(Vertex, texCoords) // Сдвиг байт до соответствующего атрибута
                );

                //? Binding attrib normal coordinates
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(3,
                                      3, // glm::vec3 - has 3 floats
                                      GL_FLOAT, GL_FALSE,
                                      sizeof(Vertex),
                                      (void*)offsetof(Vertex, normal) // Сдвиг байт до соответствующего атрибута
                );

                //? Binding attrib tangent coordinates
                glEnableVertexAttribArray(4);
                glVertexAttribPointer(4,
                                      3, // glm::vec3 - has 3 floats
                                      GL_FLOAT, GL_FALSE,
                                      sizeof(Vertex),
                                      (void*)offsetof(Vertex, tangent) // Сдвиг байт до соответствующего атрибута
                );

            }

            glBindVertexArray(0);
            glDeleteBuffers(1, &VBO);

            return true;
        }
        bool FreeMesh(unsigned int VAO) noexcept override;
        inline void DrawTriangles(unsigned int VAO, size_t count_vertices) noexcept override {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, count_vertices);
            glBindVertexArray(0);
        }
        inline bool CalculateQuad(unsigned int& VBO, unsigned int& VAO) noexcept override{
            static const float QuadVertices[] = {
                    // positions   // texCoords
                    -1.0f,  1.0f,  0.0f, 1.0f,
                    -1.0f, -1.0f,  0.0f, 0.0f,
                    1.0f, -1.0f,  1.0f, 0.0f,

                    -1.0f,  1.0f,  0.0f, 1.0f,
                    1.0f, -1.0f,  1.0f, 0.0f,
                    1.0f,  1.0f,  1.0f, 1.0f
            };

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), &QuadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

            glBindVertexArray(0);
            return true;
        }

        inline void DrawQuad(unsigned int VAO) noexcept override{
            glBindVertexArray(VAO);
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }

        inline void BindTexture(unsigned int ID) const noexcept override {
            glBindTexture(GL_TEXTURE_2D, ID);
        }

        inline void BindTexture(const unsigned char activeTexture, unsigned int ID) const noexcept override{
            glActiveTexture(GL_TEXTURE0 + activeTexture);
            glBindTexture(GL_TEXTURE_2D, ID);
        }
        inline void SetActiveTexture(const unsigned char activeTexture) const noexcept override {
            glActiveTexture(GL_TEXTURE0 + activeTexture);
        }
        unsigned int CalculateTexture(unsigned char* data, int format, unsigned int w, unsigned int h, TextureFilter filter, bool alpha) override;
    };
}

#endif //GAMEENGINE_OPENGL_H
