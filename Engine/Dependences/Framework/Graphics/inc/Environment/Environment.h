//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_ENVIRONMENT_H
#define GAMEENGINE_ENVIRONMENT_H

#include <Debug.h>
#include <utility>
#include <vector>
#include <map>
#include <Types/WindowFormat.h>
#include <functional>
#include <glm/glm.hpp>
#include <Environment/Vertex.h>
#include <Environment/TextureFilters.h>
#include <macros.h>
#include <Environment/Basic/BasicWindow.h>
#include <Environment/Basic/IShaderProgram.h>

#include <Environment/PipeLine.h>
#include <Types/Vertices.h>

#define SR_SHADER_PROGRAM unsigned int
#define SR_NULL_SHADER 0

namespace Framework::Graphics {
    struct Vertex;

    //enum class RenderBufferType { Small, Normal, Large };

    class Environment {
    public:
        enum class WinEvents{
            Close, Move, Resize, LeftClick, RightClick, Focus, Scroll
        };
    private:
        Environment(Environment&) = delete;
    protected:
        inline static std::vector<std::function<void(double x, double y)>> g_scrollEvents = std::vector<std::function<void(double x, double y)>>();
        Types::WindowFormat* m_winFormat = nullptr;
        glm::vec2 m_screenSize = glm::vec2(0, 0);
        static inline std::mutex g_mutex = std::mutex();

        BasicWindow*    m_basicWindow         = nullptr;
        bool            m_hasErrors           = false;

        __int16         m_preferredDevice     = -1;
        unsigned __int8 m_currentDrawingStage = 0;
        uint32_t        m_currentFBO          = 0;

        bool            m_needReBuild         = false;
    protected:
        Environment() = default;
        ~Environment() = default;
    private:
        inline static Environment* g_environment = nullptr;
    public:
        inline static std::function<void(WinEvents, void* win, void* arg1, void* arg2)> g_callback = std::function<void(WinEvents, void* win, void* arg1, void* arg2)>();
    public:
        void SetPreferredDevice(unsigned __int16 id) { m_preferredDevice = (__int16)id; }
        void SetBuildState(const bool& isBuild)      { m_needReBuild = !isBuild;        }

        [[nodiscard]] SR_FORCE_INLINE uint32_t GetCurrentFBO()       const noexcept { return m_currentFBO;      }
        [[nodiscard]] SR_FORCE_INLINE bool IsNeedReBuild()           const noexcept { return m_needReBuild;     }
        [[nodiscard]] SR_FORCE_INLINE bool HasErrors()               const noexcept { return m_hasErrors;       }
        [[nodiscard]] Types::WindowFormat* GetWindowFormat()         const noexcept { return this->m_winFormat; }
        [[nodiscard]] SR_FORCE_INLINE BasicWindow* GetBasicWindow()  const noexcept { return m_basicWindow;     }
        [[nodiscard]] SR_FORCE_INLINE glm::vec2 GetScreenSize()      const noexcept { return m_screenSize;      }
        [[nodiscard]] SR_FORCE_INLINE virtual bool IsGUISupport()    const noexcept { return false;             }
        [[nodiscard]] SR_FORCE_INLINE virtual bool IsDrawSupport()   const noexcept { return false;             }
        [[nodiscard]] virtual SR_FORCE_INLINE PipeLine GetPipeLine() const noexcept { return PipeLine::Unknown; }

        bool InitWindowFormat(const Types::WindowFormat& windowFormat) {
            if (m_winFormat)
                return false;
            else {
                this->m_winFormat = Types::WindowFormat::AllocMemory();
                this->m_winFormat->SetFormat(windowFormat);
                return true;
            }
        }

        SR_FORCE_INLINE static void RegisterScrollEvent(const std::function<void(double, double)>& fun){
            g_mutex.lock();
            g_scrollEvents.push_back(fun);
            g_mutex.unlock();
        }

        static bool Set(Environment* env) {
            if (g_environment != nullptr) {
                Helper::Debug::Error("Environment::Set() : environment already set!");
                return false;
            }
            else {
                g_environment = env;
                return true;
            }
        }
        static Environment* Get() noexcept {
            if (g_environment == nullptr){
                Framework::Helper::Debug::Error("Environment::Get() : environment is not set!");
                return nullptr;
            }
            else
                return g_environment;
        }

        inline void SetWinCallBack(std::function<void(WinEvents, void* win, void* arg1, void* arg2)> callback) { g_callback = std::move(callback); }
    public:
        virtual bool PreInitGUI(const std::string& fontPath) { return false; };
        virtual bool InitGUI() { return false; }
        virtual bool StopGUI() { return false; }
        virtual bool BeginDrawGUI() { return false; }
        virtual void EndDrawGUI()   { }

        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetPipeLineName() const noexcept = 0;

        virtual unsigned int CreateTexture(unsigned char* pixels, int w, int h, int components) { return -1; }

        [[nodiscard]] virtual unsigned __int8 GetCountDrawRepeats() const noexcept { return 0; }
        void SetDrawingStage(const unsigned __int8& stage) noexcept { this->m_currentDrawingStage = stage; }

        // ============================= [ WINDOW METHODS ] =============================

        /* create window instance */
        virtual bool MakeWindow(const char* winName, bool fullScreen, bool resizable) { return false; }
        virtual void SetWindowIcon(const char* path) {  }

        virtual bool PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) { return false; }
        [[nodiscard]] virtual glm::vec2 GetWindowSize() const noexcept { return {0,0}; }

        /* set current opengl/vulkan/directx context */
        virtual bool SetContextCurrent() { return false; }

        virtual bool Init(int swapInterval) { return false; }
        virtual bool PostInit() { return false; }

        [[nodiscard]]  virtual SR_FORCE_INLINE bool IsWindowOpen() const noexcept { return false; }
        virtual bool CloseWindow() { return false; }
        [[nodiscard]] virtual void* GetHWND() const { return nullptr; }

        /* clear depth/stencil/color buffers */
        virtual SR_FORCE_INLINE void ClearBuffers() const noexcept { }

        virtual SR_FORCE_INLINE void ClearColorBuffers(float r, float g, float b, float a) const noexcept { }

        /* Swap window color buffers */
        virtual SR_FORCE_INLINE void SwapBuffers() const noexcept { }
        virtual SR_FORCE_INLINE void DrawFrame() { }

        virtual glm::vec2 GetMousePos() { return glm::vec2(0); }
        virtual glm::vec4 GetTexturePixel(glm::vec2 uPos, unsigned int ID, glm::vec2 size) { return glm::vec4(0); }
        virtual glm::vec3 GetPixelColor(glm::vec2 uPos) { return glm::vec3(0); }

        virtual void SetWindowSize(unsigned int w, unsigned int h) {  }
        virtual void SetWindowPosition(int x, int y) { }

        virtual SR_FORCE_INLINE void PollEvents() const noexcept { }

        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetVendor() const noexcept { return "None"; }
        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetRenderer() const noexcept { return "None"; }
        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetVersion() const noexcept { return "None"; }

        virtual SR_FORCE_INLINE void SetCursorPosition(glm::vec2 pos) const noexcept { }

        virtual bool CreateSingleHDRFrameBO(glm::vec2 size, unsigned int& rboDepth, unsigned int& hdrFBO, unsigned int& colorBuffer) const noexcept { return false; }
        virtual bool CreateHDRFrameBufferObject(
                glm::vec2 size, unsigned int& rboDepth, unsigned int& hdrFBO, std::vector<unsigned int>& colorBuffers)const noexcept { return false;}
        virtual bool CreatePingPongFrameBufferObject(
                glm::vec2 size,std::vector<unsigned int> & pingpongFBO, std::vector<unsigned int>& pingpongColorBuffers) const noexcept { return false; }

        virtual SR_FORCE_INLINE void BindFrameBuffer(const unsigned int& FBO) noexcept { }
        virtual SR_FORCE_INLINE void DeleteBuffer(unsigned int& FBO)const noexcept { }

        [[nodiscard]] virtual inline bool IsFullScreen() const noexcept { return false; }
        virtual SR_FORCE_INLINE void SetFullScreen(bool value) {  }
        virtual void SetDepthTestEnabled(bool value) { }

        // ============================= [ SHADER METHODS ] =============================

        [[nodiscard]] virtual std::map<std::string, unsigned int> GetShaderFields(const unsigned int& ID, const std::string& path) const noexcept {
            return std::map<std::string, unsigned int>(); }
        [[nodiscard]] virtual SR_SHADER_PROGRAM AllocShaderProgram() const noexcept { return SR_NULL_SHADER; }
        virtual void FreeShaderProgram(SR_SHADER_PROGRAM shaderProgram) const noexcept {  }
        virtual bool CompileShader(
                const std::string& path,
                int32_t FBO,
                void** shaderData,
                const std::vector<uint64_t>& uniformSizes = {}) const noexcept { return false; }
        virtual bool LinkShader(
                SR_SHADER_PROGRAM* shaderProgram,
                void** shaderData,
                const std::vector<size_t>& vertexDescriptions = {},
                const std::vector<std::pair<Vertices::Attribute, size_t>>& vertexAttributes = {},
                SRShaderCreateInfo shaderCreateInfo = {}) const noexcept { return false; }
        virtual SR_FORCE_INLINE void DeleteShader(SR_SHADER_PROGRAM shaderProgram) const noexcept { }
        virtual SR_FORCE_INLINE void UseShader(SR_SHADER_PROGRAM shaderProgram) const noexcept { }

        virtual SR_FORCE_INLINE void SetBool(SR_SHADER_PROGRAM shaderProgram, const char* name, bool v)                 const noexcept { }
        virtual SR_FORCE_INLINE void SetFloat(SR_SHADER_PROGRAM shaderProgram, const char* name, float v)               const noexcept { }
        virtual SR_FORCE_INLINE void SetInt(SR_SHADER_PROGRAM shaderProgram, const char* name, int v)                   const noexcept { }
        virtual SR_FORCE_INLINE void SetMat4(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::mat4& v)     const noexcept { }
        virtual SR_FORCE_INLINE void SetVec4(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec4& v)     const noexcept { }
        virtual SR_FORCE_INLINE void SetVec3(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec3& v)     const noexcept { }
        virtual SR_FORCE_INLINE void SetVec2(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec2& v)     const noexcept { }
        virtual SR_FORCE_INLINE void SetIVec2(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::ivec2& v)   const noexcept { }

        // ============================== [ MESH METHODS ] ==============================

        virtual SR_FORCE_INLINE void SetCullFacingEnabled(const bool& enabled) const noexcept { }
        virtual SR_FORCE_INLINE void SetWireFrameEnabled(const bool& enabled) const noexcept { }
        virtual SR_FORCE_INLINE bool CalculateEmptyVAO(unsigned int& VAO) const noexcept { return false; }
        virtual SR_FORCE_INLINE bool CalculateVAO(unsigned int& VAO, std::vector<Vertex>& vertices, size_t count_verts) const noexcept { return false; }
        virtual SR_FORCE_INLINE bool CalculateVBO(unsigned int& VBO, void* vertices, uint32_t vertSize, size_t count)   const noexcept { return false; }
        virtual SR_FORCE_INLINE bool CalculateIBO(unsigned int& IBO, void* indices, uint32_t indxSize, size_t count)    const noexcept { return false; }
        virtual SR_FORCE_INLINE bool CalculateUBO(unsigned int& IBO, uint32_t uboSize)    const noexcept { return false; }

        /** Vertex pos and texture cords */
        virtual SR_FORCE_INLINE bool CalculateQuad(unsigned int& VBO, unsigned int& VAO) const noexcept { return false; }
        [[nodiscard]] virtual unsigned int CalculateSkybox() const noexcept { return -1; }
        virtual SR_FORCE_INLINE void DrawSkybox(const unsigned int&  VAO, const unsigned int& CubeMap) const noexcept { }
        virtual SR_FORCE_INLINE void DrawQuad(const unsigned int&  VAO) const noexcept { }

        virtual SR_FORCE_INLINE void BindVBO(const unsigned int& VBO) const noexcept { }
        virtual SR_FORCE_INLINE void BindIBO(const unsigned int& IBO) const noexcept { }
        virtual SR_FORCE_INLINE void BindVAO(const unsigned int& VAO) const noexcept { }
        virtual SR_FORCE_INLINE void BindUBO(const unsigned int& UBO) const noexcept { }
        virtual SR_FORCE_INLINE void Draw6Triangles() const noexcept { }

        virtual bool FreeMesh(unsigned int VAO) const noexcept { return false; }
        virtual SR_FORCE_INLINE void DrawTriangles(const unsigned int&  VAO, const unsigned int& count_vertices) const noexcept { }
        virtual SR_FORCE_INLINE void DrawLines(const unsigned int&  VAO, const unsigned int& count_vertices) const noexcept { }
        virtual SR_FORCE_INLINE void DrawInstancedVertices(unsigned int VAO, unsigned int IBO, unsigned int count) const noexcept { }

        // ============================== [ TEXTURE METHODS ] ==============================

        virtual SR_FORCE_INLINE void BindTexture(const unsigned int&  ID) const noexcept { }
        virtual SR_FORCE_INLINE void BindTexture(unsigned char activeTexture, const unsigned int&  ID) const noexcept { }
        virtual SR_FORCE_INLINE void SetActiveTexture(unsigned char activeTexture) const noexcept { }
        virtual unsigned int CalculateTexture(unsigned char* data, int format, unsigned int w, unsigned int h, TextureFilter filter, bool alpha) const noexcept { return -1; }
        [[nodiscard]] virtual unsigned int CalculateCubeMap(unsigned int w, unsigned int h, const std::vector<unsigned char*>& data) const noexcept { return -1; }
        virtual SR_FORCE_INLINE void DeleteTexture(unsigned int ID) const noexcept { }
        virtual SR_FORCE_INLINE void FreeCubeMap(unsigned int ID) const noexcept { }
    };
}

#endif //GAMEENGINE_ENVIRONMENT_H
