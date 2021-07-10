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
//#include <Environment/Vertex.h>
#include <Environment/TextureHelper.h>
#include <macros.h>
#include <Environment/Basic/BasicWindow.h>
#include <Environment/Basic/IShaderProgram.h>

#include <Environment/PipeLine.h>
#include <Types/Vertices.h>
#include <Types/Descriptors.h>
#include <set>

#define SR_SHADER_PROGRAM uint32_t
#define SR_NULL_SHADER 0

namespace Framework::Graphics {
    namespace Vertices {
        struct Mesh3DVertex;
    }

    enum class RenderBuffGroup { Kernel, Small, Normal, Large };

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

        BasicWindow*    m_basicWindow           = nullptr;
        bool            m_hasErrors             = false;

        int32_t         m_currentFBOid          = -1;
        int32_t         m_currentDescID         = -1;
        int             m_currentShaderID       = -1;
        __int16         m_preferredDevice       = -1;
        unsigned __int8 m_currentBuildIteration = 0;

        bool            m_needReBuild           = false;
    protected:
        Environment()  = default;
        ~Environment() = default;
    private:
        inline static Environment* g_environment = nullptr;
    public:
        inline static std::function<void(WinEvents, void* win, void* arg1, void* arg2)> g_callback = std::function<void(WinEvents, void* win, void* arg1, void* arg2)>();
    public:
        void SetPreferredDevice(unsigned __int16 id) { m_preferredDevice = (__int16)id; }
        void SetBuildState(const bool& isBuild)      { m_needReBuild = !isBuild;        }

        /// \warning Could be the cause of a critical error
        void SetBuildIteration(const uint8_t& iter) { m_currentBuildIteration = iter;   }
        void SetDescriptorID(const int32_t& id)     { m_currentDescID = id;             }
        void SetCurrentShaderID(const int32_t& id)  { m_currentShaderID = id;           }

        virtual uint64_t GetVRAMUsage() { return 0; }

        [[nodiscard]] SR_FORCE_INLINE uint32_t GetCurrentFBO()             const noexcept { return m_currentFBOid;    }
        [[nodiscard]] virtual SR_FORCE_INLINE uint8_t GetCountBuildIter()  const noexcept { return 1;                 }
        [[nodiscard]] SR_FORCE_INLINE bool IsNeedReBuild()                 const noexcept { return m_needReBuild;     }
        [[nodiscard]] SR_FORCE_INLINE bool HasErrors()                     const noexcept { return m_hasErrors;       }
        [[nodiscard]] Types::WindowFormat* GetWindowFormat()               const noexcept { return this->m_winFormat; }
        [[nodiscard]] SR_FORCE_INLINE BasicWindow* GetBasicWindow()        const noexcept { return m_basicWindow;     }
        [[nodiscard]] SR_FORCE_INLINE glm::vec2 GetScreenSize()            const noexcept { return m_screenSize;      }
        [[nodiscard]] SR_FORCE_INLINE virtual bool IsGUISupport()          const noexcept { return false;             }
        [[nodiscard]] SR_FORCE_INLINE virtual bool IsDrawSupport()         const noexcept { return false;             }
        [[nodiscard]] virtual SR_FORCE_INLINE PipeLine GetPipeLine()       const noexcept { return PipeLine::Unknown; }

        bool InitWindowFormat(const Types::WindowFormat& windowFormat);

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

        static inline void SetWinCallBack(std::function<void(WinEvents, void* win, void* arg1, void* arg2)> callback) { g_callback = std::move(callback); }
    public:
        virtual bool PreInitGUI(const std::string& fontPath);
        virtual bool InitGUI() { return false; }
        virtual bool StopGUI() { return false; }
        virtual bool BeginDrawGUI() { return false; }
        virtual void EndDrawGUI()   { }

        [[nodiscard]] virtual int32_t GetImGuiTextureDescriptorFromTexture(uint32_t id) const { return -2; }
        [[nodiscard]] virtual InternalTexture GetTexture(uint32_t id) const { return {}; }
        [[nodiscard]] virtual void* GetDescriptorSet(uint32_t id) const { return nullptr; }

        /// Get descriptor set from dynamic texture descriptor set
        [[nodiscard]] virtual void* GetDescriptorSetFromDTDSet(uint32_t id) const { return nullptr; }

        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetPipeLineName() const noexcept = 0;

        virtual uint32_t CreateTexture(unsigned char* pixels, int w, int h, int components) { return -1; }

        //void SetDrawingStage(const unsigned __int8& stage) noexcept { this->m_currentDrawingStage = stage; }

        // ============================= [ WINDOW METHODS ] =============================

        /* create window instance */
        virtual bool MakeWindow(const char* winName, bool fullScreen, bool resizable) { return false; }
        virtual void SetWindowIcon(const char* path) {  }

        virtual bool PreInit(uint32_t smooth_samples, const std::string& appName, const std::string& engineName) { return false; }
        [[nodiscard]] virtual glm::vec2 GetWindowSize() const noexcept { return {0,0}; }

        /* set current opengl/vulkan/directx context */
        virtual bool SetContextCurrent() { return false; }

        virtual bool Init(int swapInterval) { return false; }
        virtual bool PostInit() { return false; }

        [[nodiscard]] virtual SR_FORCE_INLINE bool IsWindowOpen() const noexcept { return false; }
        [[nodiscard]] virtual SR_FORCE_INLINE bool IsWindowCollapsed() const noexcept { return false; }
        virtual bool CloseWindow() { return false; }
        [[nodiscard]] virtual void* GetHWND() const { return nullptr; }

        /* clear depth/stencil/color buffers */
        virtual SR_FORCE_INLINE void ClearBuffers() noexcept { }

        virtual SR_FORCE_INLINE void ClearColorBuffers(float r, float g, float b, float a) const noexcept { }
        virtual SR_FORCE_INLINE void ClearBuffers(float r, float g, float b, float a, float depth, uint8_t colorCount) noexcept { }

        /* Swap window color buffers */
        virtual SR_FORCE_INLINE void SwapBuffers() const noexcept { }
        virtual SR_FORCE_INLINE void DrawFrame() { }
        virtual SR_FORCE_INLINE void BeginRender() { }
        virtual SR_FORCE_INLINE void EndRender() { }

        virtual glm::vec2 GetMousePos() { return glm::vec2(0); }
        virtual glm::vec4 GetTexturePixel(glm::vec2 uPos, uint32_t ID, glm::vec2 size) { return glm::vec4(0); }
        virtual glm::vec3 GetPixelColor(glm::vec2 uPos) { return glm::vec3(0); }

        virtual void SetWindowSize(uint32_t w, uint32_t h) {  }
        virtual void SetWindowPosition(int x, int y) { }

        /**
         * \if w and h = -1 then use auto
         */
        virtual void SetViewport(int32_t width = -1, int32_t height = -1) { }
        /**
        * \if w and h = -1 then use auto
        */
        virtual void SetScissor(int32_t width = -1, int32_t height = -1) { }

        virtual SR_FORCE_INLINE void PollEvents() const noexcept { }

        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetVendor()   const noexcept { return "None"; }
        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetRenderer() const noexcept { return "None"; }
        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetVersion()  const noexcept { return "None"; }

        virtual SR_FORCE_INLINE void SetCursorPosition(glm::vec2 pos) const noexcept { }

        virtual bool CreateFrameBuffer(glm::vec2 size, int32_t& rboDepth, int32_t& FBO, std::vector<int32_t>& colorBuffers) { return false; }
        virtual bool CreateSingleFrameBuffer(glm::vec2 size, int32_t& rboDepth, int32_t& FBO, int32_t& colorBuffer) const noexcept { return false; }
        virtual bool CreatePingPongFrameBuffer(glm::vec2 size,std::vector<int32_t> & pingpongFBO, std::vector<int32_t>& pingpongColorBuffers) const noexcept { return false; }

        virtual SR_FORCE_INLINE void BindFrameBuffer(const uint32_t& FBO) noexcept { }
        virtual SR_FORCE_INLINE void DeleteBuffer(uint32_t& FBO)const noexcept { }

        [[nodiscard]] virtual inline bool IsFullScreen() const noexcept { return false; }
        virtual SR_FORCE_INLINE void SetFullScreen(bool value) {  }
        virtual void SetDepthTestEnabled(bool value) { }

        // ============================= [ SHADER METHODS ] =============================

        [[nodiscard]] virtual std::map<std::string, uint32_t> GetShaderFields(const uint32_t& ID, const std::string& path) const noexcept {
            return std::map<std::string, uint32_t>(); }
        [[nodiscard]] virtual SR_SHADER_PROGRAM AllocShaderProgram() const noexcept { return SR_NULL_SHADER; }
        virtual void FreeShaderProgram(SR_SHADER_PROGRAM shaderProgram) const noexcept {  }
        virtual bool CompileShader(
                const std::string& path,
                int32_t FBO,
                void** shaderData,
                const std::vector<uint64_t>& uniformSizes = {}
                ) const noexcept { return false; }
        virtual bool LinkShader(
                SR_SHADER_PROGRAM* shaderProgram,
                void** shaderData,
                const std::vector<size_t>& vertexDescriptions = {},
                const std::vector<std::pair<Vertices::Attribute, size_t>>& vertexAttributes = {},
                SRShaderCreateInfo shaderCreateInfo = {}) const noexcept { return false; }
        virtual SR_FORCE_INLINE void DeleteShader(SR_SHADER_PROGRAM shaderProgram) noexcept { }
        virtual SR_FORCE_INLINE void UseShader(SR_SHADER_PROGRAM shaderProgram) noexcept { }
        virtual SR_FORCE_INLINE void UnUseShader() { }

        virtual SR_FORCE_INLINE void SetBool(SR_SHADER_PROGRAM shaderProgram, const char* name, bool v)               const noexcept { }
        virtual SR_FORCE_INLINE void SetFloat(SR_SHADER_PROGRAM shaderProgram, const char* name, float v)             const noexcept { }
        virtual SR_FORCE_INLINE void SetInt(SR_SHADER_PROGRAM shaderProgram, const char* name, int v)                 const noexcept { }
        virtual SR_FORCE_INLINE void SetMat4(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::mat4& v)   const noexcept { }
        virtual SR_FORCE_INLINE void SetVec4(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec4& v)   const noexcept { }
        virtual SR_FORCE_INLINE void SetVec3(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec3& v)   const noexcept { }
        virtual SR_FORCE_INLINE void SetVec2(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec2& v)   const noexcept { }
        virtual SR_FORCE_INLINE void SetIVec2(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::ivec2& v) const noexcept { }

        // ============================== [ MESH METHODS ] ==============================

        [[nodiscard]] virtual SR_FORCE_INLINE int32_t AllocateUBO(uint32_t uboSize) const noexcept { return -1; }

        virtual SR_FORCE_INLINE bool FreeDescriptorSet(const uint32_t& descriptorSet) { return false; }
        virtual SR_FORCE_INLINE int32_t AllocDescriptorSet(const std::set<DescriptorType>& types) { return -2; }
        virtual SR_FORCE_INLINE int32_t AllocDescriptorSetFromTexture(uint32_t textureID) { return -2; }
        //virtual SR_FORCE_INLINE void SetDescriptorSetBindingsSize(const uint32_t& size) { }
        virtual SR_FORCE_INLINE void BindDescriptorSet(const uint32_t& descriptorSet) { }

        virtual SR_FORCE_INLINE void UpdateUBO(const uint32_t& UBO, void* data, const uint64_t& uboSize) { }

        /*
         *   0 - type
         *   1 - bind
         *   2 - uniform id / texture id
         */
        virtual SR_FORCE_INLINE void UpdateDescriptorSets(uint32_t descriptorSet, const std::vector<std::pair<DescriptorType, std::pair<uint32_t, uint32_t>>>& updateValues) { }

        virtual SR_FORCE_INLINE void SetCullFacingEnabled(const bool& enabled) const noexcept { }
        virtual SR_FORCE_INLINE void SetWireFrameEnabled(const bool& enabled) const noexcept { }
        virtual SR_FORCE_INLINE bool CalculateEmptyVAO(uint32_t& VAO) const noexcept { return false; }
        virtual SR_FORCE_INLINE bool CalculateVAO(uint32_t& VAO, std::vector<Vertices::Mesh3DVertex>& vertices, size_t count_verts) const noexcept { return false; }
        virtual SR_FORCE_INLINE bool CalculateVBO(uint32_t& VBO, void* vertices, uint32_t vertSize, size_t count)   const noexcept { return false; }
        virtual SR_FORCE_INLINE bool CalculateIBO(uint32_t& IBO, void* indices, uint32_t indxSize, size_t count)    const noexcept { return false; }
        //virtual SR_FORCE_INLINE

        /** Vertex pos and texture cords */
        virtual SR_FORCE_INLINE bool CalculateQuad(uint32_t& VBO, uint32_t& VAO) const noexcept { return false; }
        [[nodiscard]] virtual uint32_t CalculateSkybox() const noexcept { return -1; }

        virtual SR_FORCE_INLINE void BindVBO(const uint32_t& VBO) const noexcept { }
        virtual SR_FORCE_INLINE void BindIBO(const uint32_t& IBO) const noexcept { }
        virtual SR_FORCE_INLINE void BindVAO(const uint32_t& VAO) const noexcept { }
        virtual SR_FORCE_INLINE void BindUBO(const uint32_t& UBO) const noexcept { }
        virtual SR_FORCE_INLINE void Draw6Triangles() const noexcept { }

        virtual SR_FORCE_INLINE void DrawSkybox(const uint32_t&  VAO, const uint32_t& CubeMap) const noexcept { }
        virtual SR_FORCE_INLINE void DrawQuad(const uint32_t&  VAO) const noexcept { }
        virtual SR_FORCE_INLINE void DrawTriangles(const uint32_t&  VAO, const uint32_t& count_vertices) const noexcept { }
        virtual SR_FORCE_INLINE void DrawTriangles(const uint32_t& count_vertices) const noexcept { }
        virtual SR_FORCE_INLINE void DrawLines(const uint32_t&  VAO, const uint32_t& count_vertices) const noexcept { }
        virtual SR_FORCE_INLINE void DrawInstancedVertices(uint32_t VAO, uint32_t IBO, uint32_t count) const noexcept { }
        virtual SR_FORCE_INLINE void DrawIndices(const uint32_t& countIndices) const noexcept { }
        virtual SR_FORCE_INLINE void Draw(const uint32_t& countVerts) const noexcept { }

        // ============================== [ TEXTURE METHODS ] ==============================

        virtual SR_FORCE_INLINE void BindTexture(const uint32_t&  ID) const noexcept { }
        virtual SR_FORCE_INLINE void BindTexture(const uint8_t activeTexture, const uint32_t&  ID) const noexcept { }
        virtual SR_FORCE_INLINE void SetActiveTexture(unsigned char activeTexture) const noexcept { }
        virtual SR_FORCE_INLINE void FreeCubeMap(uint32_t ID) const noexcept { }

        [[nodiscard]] virtual uint32_t CalculateCubeMap(uint32_t w, uint32_t h, const std::vector<unsigned char*>& data) const noexcept { return -1; }
        [[nodiscard]] virtual SR_FORCE_INLINE bool FreeVBO(uint32_t ID) const noexcept { return false; }
        [[nodiscard]] virtual SR_FORCE_INLINE bool FreeIBO(uint32_t ID) const noexcept { return false; }
        [[nodiscard]] virtual SR_FORCE_INLINE bool FreeUBO(uint32_t ID) const noexcept { return false; }
        [[nodiscard]] virtual bool FreeVAO(uint32_t VAO) const noexcept { return false; }
        [[nodiscard]] virtual bool FreeFBO(uint32_t FBO) const noexcept { return false; }
        [[nodiscard]] virtual bool FreeRBO(uint32_t RBO) const noexcept { return false; }
        [[nodiscard]] virtual bool FreeTextures(int32_t* IDs, uint32_t count) const noexcept { return false; }
        [[nodiscard]] virtual bool FreeTexture(uint32_t ID) const noexcept { return false; }

        /* mipLevels :
              0 - auto
              1 - without
              2,3,4,5...
         */
        virtual int32_t CalculateTexture(
                uint8_t * data,
                TextureFormat format,
                uint32_t w, uint32_t h,
                TextureFilter filter,
                TextureCompression compression,
                uint8_t mipLevels,
                bool alpha) const noexcept { return -1; }
    };
}

#endif //GAMEENGINE_ENVIRONMENT_H
