//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_OPENGL_H
#define GAMEENGINE_OPENGL_H
#include <easy/profiler.h>
#include <Environment/Environment.h>
#include <GL/glew.h>
#include <GL/wglew.h>

#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <Debug.h>

#ifdef WIN32
    #include <wingdi.h>
#endif

//#define SR_OPENGL_USE_WINAPI

namespace Framework::Graphics {
    class OpenGL : public Environment {
        OpenGL(OpenGL&) = delete;
    public:
        OpenGL() = default;
        ~OpenGL() = default;
    private:
#ifdef  SR_OPENGL_USE_WINAPI

#else
        GLFWwindow*             m_window          = nullptr;
        GLFWmonitor*            m_monitor         = nullptr;
        const GLFWvidmode*      m_vidMode         = nullptr;
#endif
    public:
        bool PreInitGUI(const std::string& fontPath) override;
        bool InitGUI() override;
        bool StopGUI() override;
        bool BeginDrawGUI() override;
        void EndDrawGUI() override;
        [[nodiscard]] SR_FORCE_INLINE bool IsGUISupport() const noexcept override {
            return true;
        }
        [[nodiscard]] SR_FORCE_INLINE bool IsDrawSupport() const noexcept override { return true; }

        [[nodiscard]] inline std::string GetPipeLineName() const noexcept override { return "OpenGL"; }
        [[nodiscard]] SR_FORCE_INLINE PipeLine GetPipeLine() const noexcept override { return PipeLine::OpenGL; }

        unsigned int CreateTexture(unsigned char* pixels, int w, int h, int components) override;

        // ============================= [ WINDOW METHODS ] =============================

        bool MakeWindow(const char* winName, bool fullScreen, bool resizable) override;

        bool PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) override;
        bool SetContextCurrent() override;
        bool Init(int swapInterval) override;
        bool PostInit() override;

        //bool IsWindowOpen() override;

        [[nodiscard]] SR_FORCE_INLINE bool Framework::Graphics::OpenGL::IsWindowOpen() const noexcept override {
#ifdef  SR_OPENGL_USE_WINAPI
            return m_basicWindow->IsWindowOpen();
#else
            return !glfwWindowShouldClose(m_window);
#endif
        }
        bool CloseWindow() override;

        SR_FORCE_INLINE void ClearBuffers() const noexcept override {
            glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }
        SR_FORCE_INLINE void ClearColorBuffers(float r, float g, float b, float a) const noexcept override { glClearColor(r, g, b, a); }
        SR_FORCE_INLINE void SwapBuffers() const noexcept override  {
#ifdef  SR_OPENGL_USE_WINAPI
            this->m_basicWindow->SwapBuffers();
#else
            glfwSwapBuffers(m_window);
#endif
        }

        void SetWindowSize(unsigned int w, unsigned int h) override;
        void SetWindowPosition(int x, int y) override;
        void SetDepthTestEnabled(bool value) override;

        [[nodiscard]] glm::vec2 GetWindowSize() const noexcept override {
#ifdef  SR_OPENGL_USE_WINAPI
            return { this->m_basicWindow->GetWidth(), this->m_basicWindow->GetHeight() };
#else
            return { this->m_winFormat->Width(), this->m_winFormat->Height() };
#endif
        }

        glm::vec2 GetMousePos() override {
            double posx = 0.0, posy = 0.0;
#ifdef  SR_OPENGL_USE_WINAPI

#else
            glfwGetCursorPos(m_window, &posx, &posy);
#endif
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

       /* glm::vec2 GetWindowSize() noexcept override {
            glm::vec2 val;
#ifdef  SR_OPENGL_USE_WINAPI

#else
            glfwGetWindowSize(m_window, (int*)&val.x, (int*)&val.y);
#endif
            return val;
        }*/

        [[nodiscard]] inline bool IsFullScreen() const noexcept override {
#ifdef  SR_OPENGL_USE_WINAPI
            return m_basicWindow->IsFullScreen();
#else
            return glfwGetWindowMonitor(m_window) != nullptr;
#endif
        }
        SR_FORCE_INLINE void SetFullScreen(bool value) override {
            if (IsFullScreen() == value)
                return;

            if (value) {
                Helper::Debug::Graph("OpenGL::SetFullScreen(): enable full screen...");
#ifdef  SR_OPENGL_USE_WINAPI

#else
                const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                // switch to full screen
                glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0 );
#endif
            }
            else {
                Helper::Debug::Graph("OpenGL::SetFullScreen(): disable full screen...");
#ifdef  SR_OPENGL_USE_WINAPI

#else
                const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                glfwSetWindowMonitor(m_window, NULL, 0, 0,  mode->width, mode->height, 0);
#endif
            }
        }

        SR_FORCE_INLINE void PollEvents() const noexcept override {
#ifdef  SR_OPENGL_USE_WINAPI
            this->m_basicWindow->PollEvents();
#else
            glfwPollEvents();
#endif
        }

        SR_FORCE_INLINE std::string GetVendor()  const noexcept override { return std::string((char*)glGetString(GL_VENDOR));      }
        SR_FORCE_INLINE std::string GetRenderer()const noexcept override { return std::string((char*)glGetString(GL_RENDERER));    }
        SR_FORCE_INLINE std::string GetVersion() const noexcept override { return std::string((char*)glGetString(GL_VERSION));     }

        SR_FORCE_INLINE void SetCursorPosition(glm::vec2 pos) const noexcept override {
#ifdef  SR_OPENGL_USE_WINAPI

#else
            glfwSetCursorPos(m_window, pos.x, pos.y);
#endif
        }

        bool CreateSingleHDRFrameBO(glm::vec2 size, unsigned int& rboDepth, unsigned int& hdrFBO, unsigned int& colorBuffer) const noexcept override;
        bool CreateHDRFrameBufferObject(glm::vec2 size,unsigned int& rboDepth,  unsigned int& hdrFBO, std::vector<unsigned int>& colorBuffers)const noexcept override;
        bool CreatePingPongFrameBufferObject(glm::vec2 size,std::vector<unsigned int> & pingpongFBO, std::vector<unsigned int>& pingpongColorBuffers) const noexcept override;

        SR_FORCE_INLINE void BindFrameBuffer(const unsigned int& FBO) noexcept override {
            this->m_currentFBO = FBO;
            glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        }

        SR_FORCE_INLINE void DeleteBuffer(unsigned int& FBO)const noexcept override {
        }

        // ============================= [ SHADER METHODS ] =============================

        [[nodiscard]] std::map<std::string, unsigned int> GetShaderFields(const unsigned int& ID, const std::string& path) const noexcept override;
        [[nodiscard]] SR_SHADER_PROGRAM AllocShaderProgram() const noexcept override {
            //return (OpenGLShader*)malloc(sizeof(OpenGLShader));
            return SR_NULL;
        }
        void FreeShaderProgram(SR_SHADER_PROGRAM shaderProgram) const noexcept override {
            //if (shaderProgram != nullptr)
            //    free((OpenGLShader*)shaderProgram);
        }
        bool CompileShader(
                const std::string& path,
                int32_t FBO,
                void** shaderData,
                const std::vector<uint64_t>& uniformSizes = {}) const noexcept override;
        bool LinkShader(
                SR_SHADER_PROGRAM* shaderProgram,
                void** shaderData,
                const std::vector<SR_VERTEX_DESCRIPTION>& vertexDescriptions = {},
                const std::vector<std::pair<Vertices::Attribute, size_t>>& vertexAttributes = {},
                SRShaderCreateInfo shaderCreateInfo = {}) const noexcept override;
        SR_FORCE_INLINE void DeleteShader(SR_SHADER_PROGRAM shaderProgram) const noexcept override {
            //glDeleteProgram(reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID);
            glDeleteProgram(shaderProgram);
            //reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID = 0;
        }
        SR_FORCE_INLINE void UseShader(SR_SHADER_PROGRAM shaderProgram) const noexcept override {
            if (shaderProgram)
                glUseProgram(shaderProgram);
                //glUseProgram(reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID);
        }

        SR_FORCE_INLINE void SetBool(SR_SHADER_PROGRAM shaderProgram, const char* name, bool v)               const noexcept override {
            glUniform1iv(glGetUniformLocation(
                    //reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID,
                    shaderProgram,
                    name), 1, (int*)&v);
        }
        SR_FORCE_INLINE void SetFloat(SR_SHADER_PROGRAM shaderProgram, const char* name, float v)             const noexcept override {
            glUniform1fv(glGetUniformLocation(
                    //reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID,
                    shaderProgram,
                    name), 1, &v);
        }
        SR_FORCE_INLINE void SetInt(SR_SHADER_PROGRAM shaderProgram, const char* name, int v)                 const noexcept override {
            glUniform1iv(glGetUniformLocation(
                    //reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID,
                    shaderProgram,
                    name), 1, &v);
        }
        SR_FORCE_INLINE void SetMat4(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::mat4& v)   const noexcept override {
            glUniformMatrix4fv(glGetUniformLocation(
                    //reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID,
                    shaderProgram,
                    name), 1, GL_FALSE, &v[0][0]);
        }
        SR_FORCE_INLINE void SetVec4(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec4& v)   const noexcept override {
            glUniform4fv(glGetUniformLocation(
                    //reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID,
                    shaderProgram,
                    name), 1, &v[0]);
        }
        SR_FORCE_INLINE void SetVec3(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec3& v)   const noexcept override {
            glUniform3fv(glGetUniformLocation(
                    //reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID,
                    shaderProgram,
                    name), 1, &v[0]);
        }
        SR_FORCE_INLINE void SetVec2(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec2& v)   const noexcept override {
            glUniform2fv(glGetUniformLocation(
                    //reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID,
                    shaderProgram,
                    name), 1, &v[0]);
        }
        SR_FORCE_INLINE void SetIVec2(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::ivec2& v) const noexcept override {
            glUniform2iv(glGetUniformLocation(
                    //reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID,
                    shaderProgram,
                    name), 1, &v[0]);
        }

        // ============================== [ MESH METHODS ] ==============================

        SR_FORCE_INLINE void SetCullFacingEnabled(const bool& enabled) const noexcept override {
            if (enabled)
                glEnable(GL_CULL_FACE); // Отсечение граней
            else
                glDisable(GL_CULL_FACE); // Отсечение граней
        }
        SR_FORCE_INLINE void SetWireFrameEnabled(const bool& enabled) const noexcept override {
            if (enabled)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        SR_FORCE_INLINE bool CalculateEmptyVAO(unsigned int& VAO) const noexcept override {
            glGenVertexArrays(1, &VAO);

            return true;
        }
        SR_FORCE_INLINE bool CalculateVAO(unsigned int& VAO, std::vector<Vertex>& vertices, size_t count_verts) const noexcept override{
            if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
                Helper::Debug::Log("OpenGL::CalculateMesh() : calculating " + std::to_string(vertices.size()) + " vertices...");

            unsigned int VBO = 0;

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

                //? Binding attrib color
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(3,
                                      3, // glm::vec3 - has 3 floats
                                      GL_FLOAT, GL_FALSE,
                                      sizeof(Vertex),
                                      (void*)offsetof(Vertex, color) // Сдвиг байт до соответствующего атрибута
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
        bool FreeMesh(unsigned int VAO)const noexcept override;
        SR_FORCE_INLINE void DrawLines(const unsigned int& VAO, const unsigned int& count_vertices) const noexcept override {
            glBindVertexArray(VAO);
            glDrawArrays(GL_LINES, 0, count_vertices);
        }
        SR_FORCE_INLINE void DrawTriangles(const unsigned int& VAO, const unsigned int& count_vertices) const noexcept override {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, count_vertices);
        }
        SR_FORCE_INLINE void DrawInstancedVertices(unsigned int VAO, unsigned int IBO, unsigned int count) const noexcept override {
            glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, IBO);
            glDrawElements(
                    GL_TRIANGLES,      // mode
                    count,             // count
                    GL_UNSIGNED_INT,   // type
                    (void*)0           // element array buffer offset
            );
            glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        SR_FORCE_INLINE bool CalculateQuad(unsigned int& VBO, unsigned int& VAO) const noexcept override{
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
        unsigned int CalculateSkybox() const  noexcept override;
        SR_FORCE_INLINE void DrawSkybox(const unsigned int& VAO, const unsigned int& CubeMap) const noexcept override {
            glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
            // ... задание видовой и проекционной матриц
            glBindVertexArray(VAO);
            glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMap);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDepthFunc(GL_LESS); // set depth function back to default
        }

        SR_FORCE_INLINE void DrawQuad(const unsigned int& VAO) const noexcept override{
            glBindVertexArray(VAO);
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            //glBindVertexArray(0);
        }

        SR_FORCE_INLINE void BindVAO(const unsigned int&  VAO) const noexcept override {
            glBindVertexArray(VAO);
        }
        SR_FORCE_INLINE void Draw6Triangles() const noexcept override {
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        SR_FORCE_INLINE void BindTexture(const unsigned int&  ID) const noexcept override {
            glBindTexture(GL_TEXTURE_2D, ID);
        }

        SR_FORCE_INLINE void BindTexture(const unsigned char activeTexture, const unsigned int&  ID) const noexcept override{
            glActiveTexture(GL_TEXTURE0 + activeTexture);
            glBindTexture(GL_TEXTURE_2D, ID);
        }
        SR_FORCE_INLINE void SetActiveTexture(const unsigned char activeTexture) const noexcept override {
            glActiveTexture(GL_TEXTURE0 + activeTexture);
        }
        unsigned int CalculateTexture(unsigned char* data, int format, unsigned int w, unsigned int h, TextureFilter filter, bool alpha)const noexcept override;
        [[nodiscard]] unsigned int CalculateCubeMap(unsigned int w, unsigned int h, const std::vector<unsigned char*>& data) const noexcept override;
        SR_FORCE_INLINE void DeleteTexture(unsigned int ID) const  noexcept override {
            glDeleteTextures(1, &ID);
        }
        SR_FORCE_INLINE void FreeCubeMap(unsigned int ID)const noexcept override{
            Helper::Debug::Graph("OpenGL::FreeCubeMap() : free ("+std::to_string(ID)+") cube map...");
            //glClearTexSubImage()
            glDeleteTextures(6, &ID); // TODO: I don't know if this works
        }
    };
}

#endif //GAMEENGINE_OPENGL_H
