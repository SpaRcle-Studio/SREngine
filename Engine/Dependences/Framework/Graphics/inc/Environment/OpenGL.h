//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_OPENGL_H
#define GAMEENGINE_OPENGL_H
#include <easy/profiler.h>
#include <Environment/Environment.h>
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <Debug.h>

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
        bool PreInitGUI(const std::string& fontPath) override;
        bool InitGUI() override;
        bool StopGUI() override;
        void BeginDrawGUI() override;
        void EndDrawGUI() override;

        inline std::string GetPipeLineName() const noexcept override { return "OpenGL"; }

        unsigned int CreateTexture(unsigned char* pixels, int w, int h, int components) override;

        // ============================= [ WINDOW METHODS ] =============================

        bool MakeWindow(const char* winName, Types::WindowFormat* format, bool fullScreen) override;

        bool PreInit(unsigned int smooth_samples) override;
        bool SetContextCurrent() override;
        bool Init(int swapInterval) override;
        bool PostInit() override;

        bool IsWindowOpen() override;
        bool CloseWindow() override;

        inline void ClearBuffers() noexcept override { glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); }
        inline void ClearColorBuffers(float r, float g, float b, float a) noexcept override { glClearColor(r, g, b, a); }
        inline void SwapBuffers() noexcept override  {
            if (Helper::Debug::Profile()) {
                EASY_FUNCTION(profiler::colors::Red);
            }
            glfwSwapBuffers(m_window);
        }

        void SetWindowSize(float ratio, unsigned int w, unsigned int h) override;
        void SetWindowPosition(int x, int y) override;
        void SetDepthTestEnabled(bool value) override;

        glm::vec2 GetMousePos() override {
            double posx = 0.0, posy = 0.0;
            glfwGetCursorPos(m_window, &posx, &posy);
            return { posx, posy };
        }
        glm::vec3 GetPixelColor(glm::vec2 uPos) override {
            unsigned char uColor[3] = { 0, 0, 0 };
            glReadPixels(uPos.x, uPos.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &uColor[0]);
            return {
                uColor[0],
                uColor[1],
                uColor[2]
            };
        }

        // Dont work!
        glm::vec4 GetTexturePixel(glm::vec2 uPos, unsigned int ID, glm::vec2 size) override {
            if (uPos.x >= size.x || uPos.y >= size.y || uPos.x <= 2 || uPos.y <= 2)
                return glm::vec4();

            //std::cout << uPos.x << " " << uPos.y << std::endl;

            glBindTexture(GL_TEXTURE_2D, ID);

            unsigned long bytes = (unsigned long)size.x * (unsigned long)size.y * 4;

            auto *pixels = new float[bytes];
            glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, pixels);

            GLuint r, g, b, a; // or GLubyte r, g, b, a;

            size_t x = uPos.x, y = uPos.y; // line and column of the pixel

            size_t elmes_per_line = size.x * 4; // elements per line = 256 * "RGBA"

            size_t row = y * elmes_per_line;
            size_t col = x * 4;

            r = pixels[row + col];
            g = pixels[row + col + 1];
            b = pixels[row + col + 2];
            a = pixels[row + col + 3];

            //printf("%i %i %i\n", r,g,b);

            delete[] pixels;
            return glm::vec4(r,g,b,a);
        }

        glm::vec2 GetWindowSize() noexcept override {
            glm::vec2 val;
            glfwGetWindowSize(m_window, (int*)&val.x, (int*)&val.y);
            return val;
        }
        glm::vec2 GetWindowPosition() noexcept override {
            return {0,0};
        }

        [[nodiscard]] inline bool IsFullScreen() const noexcept override {
            return glfwGetWindowMonitor(m_window) != nullptr;
        }
        inline void SetFullScreen(bool value) override {
            if (IsFullScreen() == value)
                return;

            if (value) {
                Helper::Debug::Graph("OpenGL::SetFullScreen(): enable full screen...");
                const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                // switch to full screen
                glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0 );
            }
            else {
                Helper::Debug::Graph("OpenGL::SetFullScreen(): disable full screen...");

                const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                glfwSetWindowMonitor(m_window, NULL, 0, 0,  mode->width, mode->height, 0);
            }
        }

        void PoolEvents() override;

        inline std::string GetVendor()   override { return std::string((char*)glGetString(GL_VENDOR));      }
        inline std::string GetRenderer() override { return std::string((char*)glGetString(GL_RENDERER));    }
        inline std::string GetVersion()  override { return std::string((char*)glGetString(GL_VERSION));     }

        inline void SetCursorPosition(glm::vec2 pos) noexcept override {
            glfwSetCursorPos(m_window, pos.x, pos.y);
        }

        bool CreateSingleHDRFrameBO(glm::vec2 size, unsigned int& rboDepth, unsigned int& hdrFBO, unsigned int& colorBuffer) override;
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
        inline void DeleteShader(unsigned int ID) override { glDeleteProgram(ID); }
        inline void UseShader(const unsigned int& ID) noexcept override  { glUseProgram(ID); }

        inline void SetBool(const unsigned int& ID, const char* name, bool v)       const noexcept override {
            glUniform1iv(glGetUniformLocation(ID, name), 1, (int*)&v);
        }
        inline void SetFloat(const unsigned int& ID, const char* name, float v)     const noexcept override {
            glUniform1fv(glGetUniformLocation(ID, name), 1, &v);
        }
        inline void SetInt(const unsigned int& ID, const char* name, int v)         const noexcept override {
            glUniform1iv(glGetUniformLocation(ID, name), 1, &v);
        }
        inline void SetMat4(const unsigned int& ID, const char* name, glm::mat4 v)  const noexcept override {
            glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(v));
        }
        inline void SetVec4(const unsigned int& ID, const char* name, glm::vec4 v)  const noexcept override {
            glUniform4fv(glGetUniformLocation(ID, name), 1, &v[0]);
        }
        inline void SetVec3(const unsigned int& ID, const char* name, glm::vec3 v)  const noexcept override {
            glUniform3fv(glGetUniformLocation(ID, name), 1, &v[0]);
        }
        inline void SetVec2(const unsigned int& ID, const char* name, glm::vec2 v)  const noexcept override {
            glUniform2fv(glGetUniformLocation(ID, name), 1, &v[0]);
        }
        inline void SetIVec2(const unsigned int& ID, const char* name, glm::ivec2 v)  const noexcept override {
            glUniform2iv(glGetUniformLocation(ID, name), 1, &v[0]);
        }

        // ============================== [ MESH METHODS ] ==============================

        inline bool CalculateEmptyVAO(unsigned int& VAO) noexcept override {
            glGenVertexArrays(1, &VAO);

            return true;
        }
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
        inline void DrawTriangles(const unsigned int& VAO, const unsigned int& count_vertices) noexcept override {
            //if (Helper::Debug::Profile()) { EASY_FUNCTION(profiler::colors::Green); }

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, count_vertices);
            //glBindVertexArray(0);

            //if (Helper::Debug::Profile()) { EASY_END_BLOCK; }
        }
        inline void DrawInstancedVertices(unsigned int VAO, unsigned int IBO, unsigned int count) noexcept override {
            glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, IBO);
            glDrawElements(
                    GL_TRIANGLES,      // mode
                    count,             // count
                    GL_UNSIGNED_INT,   // type
                    (void*)0           // element array buffer offset
            );
            glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
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
        unsigned int CalculateSkybox() noexcept override;
        void DrawSkybox(const unsigned int& VAO, unsigned int CubeMap) noexcept override;

        inline void DrawQuad(const unsigned int& VAO) noexcept override{
            glBindVertexArray(VAO);
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            //glBindVertexArray(0);
        }

        inline void BindTexture(const unsigned int&  ID) const noexcept override {
            glBindTexture(GL_TEXTURE_2D, ID);
        }

        inline void BindTexture(const unsigned char activeTexture, const unsigned int&  ID) const noexcept override{
            glActiveTexture(GL_TEXTURE0 + activeTexture);
            glBindTexture(GL_TEXTURE_2D, ID);
        }
        inline void SetActiveTexture(const unsigned char activeTexture) const noexcept override {
            glActiveTexture(GL_TEXTURE0 + activeTexture);
        }
        unsigned int CalculateTexture(unsigned char* data, int format, unsigned int w, unsigned int h, TextureFilter filter, bool alpha) override;
        unsigned int CalculateCubeMap(unsigned int w, unsigned int h, std::vector<unsigned char*> data) override;
        inline void DeleteTexture(unsigned int ID) noexcept override {
            glDeleteTextures(1, &ID);
        }
        inline void FreeCubeMap(unsigned int ID) noexcept override{
            Helper::Debug::Graph("OpenGL::FreeCubeMap() : free ("+std::to_string(ID)+") cube map...");
            //glClearTexSubImage()
            glDeleteTextures(6, &ID); // TODO: I don't know if this works
        }
    };
}

#endif //GAMEENGINE_OPENGL_H
