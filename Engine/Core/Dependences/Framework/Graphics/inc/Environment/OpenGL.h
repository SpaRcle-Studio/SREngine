//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_OPENGL_H
#define GAMEENGINE_OPENGL_H

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
        OpenGL()  = default;
        ~OpenGL() = default;
    private:
#ifdef  SR_OPENGL_USE_WINAPI

#else
        GLFWwindow*             m_window          = nullptr;
        GLFWmonitor*            m_monitor         = nullptr;
        const GLFWvidmode*      m_vidMode         = nullptr;
#endif
    public:
        bool InitGUI() override;
        bool StopGUI() override;
        bool BeginDrawGUI() override;
        void EndDrawGUI() override;

        Helper::Math::IVector2 GetScreenSize() const override;

        [[nodiscard]] SR_FORCE_INLINE bool IsGUISupport()  const override { return true; }
        [[nodiscard]] SR_FORCE_INLINE bool IsDrawSupport() const override { return true; }

        [[nodiscard]] std::string GetPipeLineName() const override { return "OpenGL"; }
        [[nodiscard]] SR_FORCE_INLINE PipeLine GetPipeLine() const override { return PipeLine::OpenGL; }

        uint32_t CreateTexture(unsigned char* pixels, int w, int h, int components) override;

        // ============================= [ WINDOW METHODS ] =============================

        bool MakeWindow(const char* winName, bool fullScreen, bool resizable, bool headerEnabled) override;

        bool PreInit(
                uint32_t smooth_samples,
                const std::string& appName,
                const std::string& engineName,
                const std::string& glslc) override;

        bool SetContextCurrent() override;
        bool Init(int swapInterval) override;
        bool PostInit() override;

        //bool IsWindowOpen() override;

        [[nodiscard]] SR_FORCE_INLINE bool IsWindowOpen() const override {
#ifdef  SR_OPENGL_USE_WINAPI
            return m_basicWindow->IsWindowOpen();
#else
            return !glfwWindowShouldClose(m_window);
#endif
        }
        bool CloseWindow() override;

        SR_FORCE_INLINE void ClearBuffers() override {
            glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }
        SR_FORCE_INLINE void ClearColorBuffers(float r, float g, float b, float a) const override { glClearColor(r, g, b, a); }
        SR_FORCE_INLINE void SwapBuffers() const override  {
#ifdef  SR_OPENGL_USE_WINAPI
            this->m_basicWindow->SwapBuffers();
#else
            glfwSwapBuffers(m_window);
#endif
        }

        void SetWindowSize(uint32_t w, uint32_t h) override;
        void SetWindowPosition(int x, int y) override;
        void SetDepthTestEnabled(bool value) override;

        [[nodiscard]] glm::vec2 GetWindowSize() const override {
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
        glm::vec4 GetTexturePixel(glm::vec2 uPos, uint32_t ID, glm::vec2 size) override {
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

       /* glm::vec2 GetWindowSize() override {
            glm::vec2 val;
#ifdef  SR_OPENGL_USE_WINAPI

#else
            glfwGetWindowSize(m_window, (int*)&val.x, (int*)&val.y);
#endif
            return val;
        }*/

        [[nodiscard]] inline bool IsFullScreen() const override {
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

        SR_FORCE_INLINE void PollEvents() const override {
#ifdef  SR_OPENGL_USE_WINAPI
            this->m_basicWindow->PollEvents();
#else
            glfwPollEvents();
#endif
        }

        SR_FORCE_INLINE std::string GetVendor()   const override { return std::string((char*)glGetString(GL_VENDOR));      }
        SR_FORCE_INLINE std::string GetRenderer() const override { return std::string((char*)glGetString(GL_RENDERER));    }
        SR_FORCE_INLINE std::string GetVersion()  const override { return std::string((char*)glGetString(GL_VERSION));     }

        SR_FORCE_INLINE void SetCursorPosition(glm::vec2 pos) const override {
#ifdef  SR_OPENGL_USE_WINAPI

#else
            glfwSetCursorPos(m_window, pos.x, pos.y);
#endif
        }

        bool CreateSingleFrameBuffer(glm::vec2 size, int32_t& rboDepth, int32_t& hdrFBO, int32_t& colorBuffer) override;
        bool CreateFrameBuffer(glm::vec2 size, int32_t& rboDepth, int32_t& FBO, std::vector<int32_t>& colorBuffers) override;
        bool CreatePingPongFrameBuffer(glm::vec2 size,std::vector<int32_t> & pingpongFBO, std::vector<int32_t>& pingpongColorBuffers) const override;

        SR_FORCE_INLINE void BindFrameBuffer(const uint32_t& FBO) override {
            this->m_currentFBOid = FBO;
            glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        }

        SR_FORCE_INLINE void DeleteBuffer(uint32_t& FBO) const override {
        }

        // ============================= [ SHADER METHODS ] =============================

        SR_FORCE_INLINE bool ReCreateShader(uint32_t shaderProgram) override { return true; }
        [[nodiscard]] std::map<std::string, uint32_t> GetShaderFields(const uint32_t& ID, const std::string& path) const override;
        [[nodiscard]] SR_SHADER_PROGRAM AllocShaderProgram() const override {
            //return (OpenGLShader*)malloc(sizeof(OpenGLShader));
            return SR_NULL;
        }
        bool CompileShader(
                const std::string& path,
                int32_t FBO,
                void** shaderData,
                const std::vector<uint64_t>& uniformSizes
                ) const override;
        bool LinkShader(
                SR_SHADER_PROGRAM* shaderProgram,
                void** shaderData,
                const std::vector<SR_VERTEX_DESCRIPTION>& vertexDescriptions = {},
                const std::vector<std::pair<Vertices::Attribute, size_t>>& vertexAttributes = {},
                SRShaderCreateInfo shaderCreateInfo = {}) const override;
        SR_FORCE_INLINE bool DeleteShader(SR_SHADER_PROGRAM shaderProgram) override {
            //glDeleteProgram(reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID);
            glDeleteProgram(shaderProgram);
            return true;
            //reinterpret_cast<OpenGLShader*>(shaderProgram)->m_programID = 0;
        }
        SR_FORCE_INLINE void UseShader(SR_SHADER_PROGRAM shaderProgram) override {
            if (shaderProgram)
                glUseProgram(shaderProgram);
        }

        SR_FORCE_INLINE void SetBool(SR_SHADER_PROGRAM shaderProgram, const char* name, bool v) const override {
            glUniform1iv(glGetUniformLocation(shaderProgram, name), 1, (int*)&v);
        }
        SR_FORCE_INLINE void SetFloat(SR_SHADER_PROGRAM shaderProgram, const char* name, float v) const override {
            glUniform1fv(glGetUniformLocation(shaderProgram, name), 1, &v);
        }
        SR_FORCE_INLINE void SetInt(SR_SHADER_PROGRAM shaderProgram, const char* name, int v) const override {
            glUniform1iv(glGetUniformLocation(shaderProgram, name), 1, &v);
        }
        SR_FORCE_INLINE void SetMat4(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::mat4& v) const override {
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, &v[0][0]);
        }
        SR_FORCE_INLINE void SetVec4(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec4& v) const override {
            glUniform4fv(glGetUniformLocation(shaderProgram, name), 1, &v[0]);
        }
        SR_FORCE_INLINE void SetVec3(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec3& v) const override {
            glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, &v[0]);
        }
        SR_FORCE_INLINE void SetVec2(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec2& v) const override {
            glUniform2fv(glGetUniformLocation(shaderProgram, name), 1, &v[0]);
        }
        SR_FORCE_INLINE void SetIVec2(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::ivec2& v) const override {
            glUniform2iv(glGetUniformLocation(shaderProgram, name), 1, &v[0]);
        }

        // ============================== [ MESH METHODS ] ==============================

        SR_FORCE_INLINE void SetCullFacingEnabled(const bool& enabled) const override {
            if (enabled)
                glEnable(GL_CULL_FACE); // Отсечение граней
            else
                glDisable(GL_CULL_FACE); // Отсечение граней
        }
        SR_FORCE_INLINE void SetWireFrameEnabled(const bool& enabled) const override {
            if (enabled)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        SR_FORCE_INLINE bool CalculateEmptyVAO(uint32_t& VAO) const override {
            glGenVertexArrays(1, &VAO);

            return true;
        }
        /*
            В OpenGL не используется в чистом виде VBO, OpenGL работает с VAO, но для универсальности
            здесь под VBO будет скрываться VAO
         */
        int32_t CalculateVBO(void* vertices, Vertices::Type type, size_t count) override;
        int32_t CalculateIBO(void* indices, uint32_t indxSize, size_t count, int32_t VBO = SR_ID_INVALID) override;
        int32_t CalculateVAO(std::vector<Vertices::Mesh3DVertex>& vertices, size_t count_verts) override;
        [[nodiscard]] bool FreeVAO(uint32_t VAO) const override;
        SR_FORCE_INLINE void DrawLines(const uint32_t& VAO, const uint32_t& count_vertices) const override {
            glBindVertexArray(VAO);
            glDrawArrays(GL_LINES, 0, count_vertices);
        }
        [[nodiscard]] SR_FORCE_INLINE bool FreeVBO(uint32_t ID) const override {
            if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
                Helper::Debug::Log("OpenGL::FreeVBO() : free VBO \"" + std::to_string(ID) + "\" VAO...");

            if (ID > 0) {
                glDeleteVertexArrays(1, &ID); // VAO
                return true;
            } else {
                Helper::Debug::Error("OpenGL::FreeVBO() : VBO (VAO) is zero! Something went wrong...");
                return false;
            }
        }
        [[nodiscard]] SR_FORCE_INLINE bool FreeIBO(uint32_t ID) const override {
            return true; // nothing
        }

        SR_FORCE_INLINE void DrawTriangles(const uint32_t& count_vertices) const override {
            glDrawArrays(GL_TRIANGLES, 0, count_vertices);
        }

        SR_FORCE_INLINE void DrawTriangles(const uint32_t& VAO, const uint32_t& count_vertices) const override {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, count_vertices);
        }
        SR_FORCE_INLINE void DrawInstancedVertices(uint32_t VAO, uint32_t IBO, uint32_t count) const override {
            glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, IBO);
            glDrawElements(
                    GL_TRIANGLES,      // mode
                    count,             // count
                    GL_UNSIGNED_INT,   // type
                    (void*)0           // element array buffer offset
            );
            glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        SR_FORCE_INLINE bool CalculateQuad(uint32_t& VBO, uint32_t& VAO) const override{
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
        uint32_t CalculateSkybox() const override;
        SR_FORCE_INLINE void DrawSkybox(const uint32_t& VAO, const uint32_t& CubeMap) const override {
            glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
            // ... задание видовой и проекционной матриц
            glBindVertexArray(VAO);
            glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMap);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glDepthFunc(GL_LESS); // set depth function back to default
        }

        SR_FORCE_INLINE void Draw(const uint32_t& vertCount) const override {
            glDrawArrays(GL_TRIANGLES, 0, vertCount);
        }

        SR_FORCE_INLINE void DrawIndices(const uint32_t& countIndices) const override {
            GLuint indices[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

            glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, indices);
        }

        SR_FORCE_INLINE void DrawQuad(const uint32_t& VAO) const override{
            glBindVertexArray(VAO);
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            //glBindVertexArray(0);
        }

        SR_FORCE_INLINE void BindIBO(const uint32_t& IBO) const override {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); // EBO
        }

        SR_FORCE_INLINE void BindVAO(const uint32_t& VAO) const override {
            glBindVertexArray(VAO);
        }

        SR_FORCE_INLINE void BindVBO(const uint32_t& VBO) const override {
            glBindVertexArray(VBO); // VAO
        }

        SR_FORCE_INLINE void Draw6Triangles() const override {
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        SR_FORCE_INLINE void BindTexture(const uint32_t&  ID) const override {
            glBindTexture(GL_TEXTURE_2D, ID);
        }

        SR_FORCE_INLINE void BindTexture(const uint8_t activeTexture, const uint32_t&  ID) const override {
            glActiveTexture(GL_TEXTURE0 + activeTexture);
            glBindTexture(GL_TEXTURE_2D, ID);
        }
        SR_FORCE_INLINE void SetActiveTexture(const unsigned char activeTexture) const override {
            glActiveTexture(GL_TEXTURE0 + activeTexture);
        }
        int32_t CalculateTexture(
                uint8_t* data,
                TextureFormat format,
                uint32_t w, uint32_t h,
                TextureFilter filter,
                TextureCompression compression,
                uint8_t mipLevels,
                bool alpha,
                bool cpuUsage) const override;
        [[nodiscard]] int32_t CalculateCubeMap(uint32_t w, uint32_t h, const std::array<uint8_t*, 6>& data, bool cpuUsage) override;
        SR_FORCE_INLINE bool FreeCubeMap(int32_t ID) override{
            Helper::Debug::Graph("OpenGL::FreeCubeMap() : free ("+std::to_string(ID)+") cube map...");
            //glClearTexSubImage()
            glDeleteTextures(6, reinterpret_cast<const GLuint *>(&ID)); // TODO: I don't know if this works
            return true;
        }
        [[nodiscard]] bool FreeFBO(uint32_t FBO) const override {
            glDeleteFramebuffers(1, &FBO);
            return true;
        }
        [[nodiscard]] bool FreeRBO(uint32_t RBO) const override {
            glDeleteFramebuffers(1, &RBO);
            return true;
        }
        [[nodiscard]] bool FreeTexture(uint32_t ID) const override;
        [[nodiscard]] bool FreeTextures(int32_t* IDs, uint32_t count) const override;
    };
}

#endif //GAMEENGINE_OPENGL_H
