//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_ENVIRONMENT_H
#define GAMEENGINE_ENVIRONMENT_H

#include <Utils/GUI.h>

#include <Graphics/Pipeline/TextureHelper.h>
#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/Pipeline/PipelineType.h>

#include <Graphics/Types/Vertices.h>
#include <Graphics/Types/Descriptors.h>
#include <Graphics/Window/BasicWindowImpl.h>
#include <Graphics/Window/Window.h>

namespace SR_GTYPES_NS {
    class Shader;
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    struct ColorLayer {
        int32_t texture = SR_ID_INVALID;
        ColorFormat format = ColorFormat::Unknown;
    };

    struct DepthLayer {
        int32_t texture = SR_ID_INVALID;
        DepthFormat format = DepthFormat::Unknown;
    };

    typedef ImGuiContext* GUIContext;
    typedef ImFont* ImguiFont;

    namespace Vertices {
        struct StaticMeshVertex;
        struct SimpleMeshVertex;
    }

    enum class RenderBuffGroup { Kernel, Small, Normal, Large };

    /// TODO: TO_REFACTORING
    class Environment {
    public:
        using WindowPtr = SR_HTYPES_NS::SafePtr<Window>;

        enum class WinEvents{
            Close, Move, Resize, LeftClick, RightClick, Focus, Scroll
        };
    public:
        Environment(Environment&) = delete;
    protected:
        inline static std::vector<std::function<void(double x, double y)>> g_scrollEvents = std::vector<std::function<void(double x, double y)>>();
        static inline std::mutex g_mutex = std::mutex();

        GUIContext        m_guiContext             = nullptr;
        ImguiFont         m_iconFont               = nullptr;

        bool              m_hasErrors              = false;
        bool              m_guiEnabled             = false;
        bool              m_undocking              = false;

        int32_t           m_currentUBOid           = -1;
        int32_t           m_currentFBOid           = -1;
        int32_t           m_currentDescriptorSetId = -1;
        int32_t           m_currentShaderID        = -1;
        int32_t           m_preferredDevice        = -1;
        int32_t           m_currentBuildIteration  = 0;

        std::atomic<bool> m_needReBuild            = true;

        Types::Shader* m_currentShader = nullptr;
        Types::Framebuffer* m_currentFramebuffer = nullptr;

        WindowPtr m_window;

    protected:
        Environment()  = default;
        ~Environment() = default;
    private:
        inline static Environment* g_environment = nullptr;
    public:
        inline static std::function<void(WinEvents, void* win, void* arg1, void* arg2)> g_callback = std::function<void(WinEvents, void* win, void* arg1, void* arg2)>();
    public:
        void SetPreferredDevice(int32_t id) { m_preferredDevice = id; }
        virtual void SetBuildState(const bool& isBuild) { }

        SR_NODISCARD ImguiFont GetIconFont() const { return m_iconFont; }
        SR_NODISCARD GUIContext GetGUIContext() const { return m_guiContext; }
        SR_NODISCARD bool IsGUIEnabled() const { return m_guiEnabled; }

        /// \warning Could be the cause of a critical error
        void SetBuildIteration(const uint8_t& iter) { m_currentBuildIteration = iter;   }
        void SetCurrentShaderId(const int32_t& id)  { m_currentShaderID = id;           }
        void SetCurrentShader(Types::Shader* pShader)  { m_currentShader = pShader;           }
        void SetCurrentFramebuffer(Types::Framebuffer* pFramebuffer)  { m_currentFramebuffer = pFramebuffer; }
        SR_NODISCARD int32_t GetCurrentShaderId() const noexcept { return m_currentShaderID; }
        SR_NODISCARD Types::Shader* GetCurrentShader() const noexcept { return m_currentShader; }
        SR_NODISCARD Types::Framebuffer* GetCurrentFramebuffer() const noexcept { return m_currentFramebuffer; }
        SR_NODISCARD virtual void* GetCurrentCmd() const noexcept { return nullptr; }
        SR_NODISCARD int32_t GetCurrentFramebufferId() const noexcept { return m_currentFBOid; }

        virtual uint64_t GetVRAMUsage() { return 0; }
        virtual Helper::Math::IVector2 GetScreenSize() const { return {}; }

        SR_NODISCARD virtual uint8_t GetSmoothSamplesCount() const { return 0; }
        SR_NODISCARD SR_FORCE_INLINE uint32_t GetCurrentUBO()             const { return m_currentUBOid;           }
        SR_DEPRECATED SR_NODISCARD SR_FORCE_INLINE uint32_t GetCurrentFBO()             const { return m_currentFBOid;           }
        SR_NODISCARD SR_FORCE_INLINE uint32_t GetCurrentDescriptorSet()   const { return m_currentDescriptorSetId; }
        SR_NODISCARD virtual SR_FORCE_INLINE uint8_t GetCountBuildIter()  const { return 1;                        }
        SR_NODISCARD SR_FORCE_INLINE bool IsNeedReBuild()                 const { return m_needReBuild;            }
        SR_NODISCARD SR_FORCE_INLINE bool HasErrors()                     const { return m_hasErrors;              }
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsGUISupport()          const { return false;                    }
        SR_NODISCARD SR_FORCE_INLINE virtual bool IsDrawSupport()         const { return false;                    }
        SR_NODISCARD virtual SR_FORCE_INLINE PipelineType GetType()       const { return PipelineType::Unknown;        }

        SR_FORCE_INLINE static void RegisterScrollEvent(const std::function<void(double, double)>& fun){
            g_mutex.lock();
            g_scrollEvents.push_back(fun);
            g_mutex.unlock();
        }

        static bool Set(Environment* env) {
            if (g_environment != nullptr) {
                SR_ERROR("Environment::Set() : environment already set!");
                return false;
            }
            else {
                g_environment = env;
                return true;
            }
        }
        static Environment* Get();

        static void SetWinCallBack(const std::function<void(WinEvents, void* win, void* arg1, void* arg2)>& callback);
    public:
        virtual bool PreInitGUI(const SR_UTILS_NS::Path& fontPath);
        virtual void SetGUIEnabled(bool enabled) { }
        virtual bool InitGUI() { return false; }
        virtual bool StopGUI() { return false; }
        virtual bool BeginDrawGUI() { return false; }
        virtual void EndDrawGUI()   { }

        virtual void OnWindowClose() { }
        virtual void DeInitialize() { }

        virtual bool IsMultiSamplingSupports() const { return false; }

        //[[nodiscard]] virtual int32_t GetImGuiTextureDescriptorFromTexture(uint32_t id) const { return -2; }
        SR_NODISCARD virtual InternalTexture GetTexture(uint32_t id) const { return {}; }
        SR_NODISCARD virtual void* TryGetDescriptorSetFromTexture(uint32_t id, bool imgui) const { return nullptr; }
        SR_NODISCARD virtual void* GetDescriptorSetFromTexture(uint32_t id, bool imgui) const { return nullptr; }

        /// Get descriptor set from dynamic texture descriptor set
       // [[nodiscard]] virtual void* GetDescriptorSetFromDTDSet(uint32_t id) const { return nullptr; }

        SR_NODISCARD virtual std::string GetPipeLineName() const = 0;

        virtual uint32_t CreateTexture(unsigned char* pixels, int w, int h, int components) { return -1; }

        // ============================= [ WINDOW METHODS ] =============================

        /* create window instance */

        SR_NODISCARD WindowPtr GetWindow() const { return m_window; }

        virtual bool OnResize(const SR_MATH_NS::UVector2& size) { return false; }

        virtual bool PreInit(
                uint32_t smooth_samples,
                const std::string& appName,
                const std::string& engineName,
                const std::string& glslc) { return false; }

        /* set current opengl/vulkan/directx context */
        virtual bool SetContextCurrent() { return false; }

        virtual bool Init(const WindowPtr& windowPtr, int swapInterval) { return false; }
        virtual bool PostInit() { return false; }

        [[nodiscard]] virtual void* GetHWND() const { return nullptr; }

        virtual SR_FORCE_INLINE void ClearFramebuffersQueue() { }
        /* clear depth/stencil/color buffers */
        virtual SR_FORCE_INLINE void ClearBuffers() { }

        virtual SR_FORCE_INLINE void ClearColorBuffers(float r, float g, float b, float a) const { }
        virtual SR_FORCE_INLINE void ClearBuffers(float r, float g, float b, float a, float depth, uint8_t colorCount) { }
        virtual SR_FORCE_INLINE void ClearBuffers(const std::vector<SR_MATH_NS::FColor>& colors, float_t depth) { }

        /* Swap window color buffers */
        virtual SR_FORCE_INLINE void SwapBuffers() const { }
        virtual SR_FORCE_INLINE void DrawFrame() { }
        virtual SR_FORCE_INLINE bool BeginCmdBuffer() { return false; }
        virtual SR_FORCE_INLINE bool BeginRender() { return false; }
        virtual SR_FORCE_INLINE void EndRender() { }
        virtual SR_FORCE_INLINE void ResetCmdBuffer() { }
        virtual SR_FORCE_INLINE void ResetCmdPool() { }
        virtual SR_FORCE_INLINE void EndCmdBuffer() { }

        virtual glm::vec2 GetMousePos() { return glm::vec2(0); }
        virtual glm::vec4 GetTexturePixel(glm::vec2 uPos, uint32_t ID, glm::vec2 size) { return glm::vec4(0); }
        virtual glm::vec3 GetPixelColor(glm::vec2 uPos) { return glm::vec3(0); }

        /**
         * \if w and h = -1 then use auto
         */
        virtual void SetViewport(int32_t width = -1, int32_t height = -1) { }
        /**
        * \if w and h = -1 then use auto
        */
        virtual void SetScissor(int32_t width = -1, int32_t height = -1) { }

        virtual SR_FORCE_INLINE void PollEvents() const { }

        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetVendor()   const { return "None"; }
        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetRenderer() const { return "None"; }
        [[nodiscard]] virtual SR_FORCE_INLINE std::string GetVersion()  const { return "None"; }

        SR_NODISCARD virtual SR_MATH_NS::FColor GetPixelColor(uint64_t textureId, uint32_t x, uint32_t y) { return SR_MATH_NS::FColor(0.f); }

        virtual SR_FORCE_INLINE void SetCursorPosition(glm::vec2 pos) const { }

        virtual bool CreateFrameBuffer(const SR_MATH_NS::IVector2& size, int32_t& FBO, DepthLayer* pDepth, std::vector<ColorLayer>& colors, uint8_t sampleCount) { return false; }

        virtual SR_FORCE_INLINE void BindFrameBuffer(const uint32_t& FBO) { }
        virtual SR_FORCE_INLINE void DeleteBuffer(uint32_t& FBO)const { }

        SR_NODISCARD virtual inline bool IsFullScreen() const { return false; }
        virtual SR_FORCE_INLINE void SetFullScreen(bool value) {  }
        virtual void SetDepthTestEnabled(bool value) { }

        // ============================= [ SHADER METHODS ] =============================

        virtual int32_t AllocateShaderProgram(const SRShaderCreateInfo& createInfo, int32_t fbo) { return SR_ID_INVALID; }

        SR_NODISCARD virtual std::map<std::string, uint32_t> GetShaderFields(const uint32_t& ID, const std::string& path) const {
            return std::map<std::string, uint32_t>(); }
        SR_NODISCARD virtual SR_SHADER_PROGRAM AllocShaderProgram() const { return SR_NULL_SHADER; }
        virtual bool CompileShader(
                const std::map<ShaderStage, SR_UTILS_NS::Path>& stages,
                int32_t FBO,
                void** shaderData,
                const std::vector<uint64_t>& uniformSizes = {}
                ) { return false; }
        virtual bool LinkShader(
                SR_SHADER_PROGRAM* shaderProgram,
                void** shaderData,
                const SRShaderCreateInfo& shaderCreateInfo = {}) const { return false; }
        virtual SR_FORCE_INLINE bool ReCreateShader(uint32_t shaderProgram) { return false; }
        virtual SR_FORCE_INLINE bool DeleteShader(SR_SHADER_PROGRAM shaderProgram) { return false; }
        virtual SR_FORCE_INLINE void UseShader(SR_SHADER_PROGRAM shaderProgram) { }
        virtual SR_FORCE_INLINE void UnUseShader() { }

        virtual SR_FORCE_INLINE void SetBool(SR_SHADER_PROGRAM shaderProgram, const char* name, bool v)               const { }
        virtual SR_FORCE_INLINE void SetFloat(SR_SHADER_PROGRAM shaderProgram, const char* name, float v)             const { }
        virtual SR_FORCE_INLINE void SetInt(SR_SHADER_PROGRAM shaderProgram, const char* name, int v)                 const { }
        virtual SR_FORCE_INLINE void SetMat4(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::mat4& v)   const { }
        virtual SR_FORCE_INLINE void SetVec4(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec4& v)   const { }
        virtual SR_FORCE_INLINE void SetVec3(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec3& v)   const { }
        virtual SR_FORCE_INLINE void SetVec2(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::vec2& v)   const { }
        virtual SR_FORCE_INLINE void SetIVec2(SR_SHADER_PROGRAM shaderProgram, const char* name, const glm::ivec2& v) const { }

        // ============================== [ MESH METHODS ] ==============================

        SR_NODISCARD virtual SR_FORCE_INLINE int32_t AllocateUBO(uint32_t uboSize) const { return SR_ID_INVALID; }

        virtual SR_FORCE_INLINE bool FreeDescriptorSet(int32_t* descriptorSet) { return false; }
        virtual SR_FORCE_INLINE int32_t AllocDescriptorSet(std::vector<uint64_t> types) { return SR_ID_INVALID; }
        virtual SR_FORCE_INLINE int32_t AllocDescriptorSetFromTexture(uint32_t textureID) { return SR_ID_INVALID; }
        virtual SR_FORCE_INLINE void BindDescriptorSet(const uint32_t& descriptorSet) { m_currentDescriptorSetId = descriptorSet; }
        virtual SR_FORCE_INLINE void ResetDescriptorSet() { m_currentDescriptorSetId = SR_ID_INVALID; }

        virtual SR_FORCE_INLINE void UpdateUBO(const uint32_t& UBO, void* data, const uint64_t& uboSize) { }

        /*
         *   0 - type
         *   1 - bind
         *   2 - uniform id / texture id
         */
        virtual SR_FORCE_INLINE bool UpdateDescriptorSets(uint32_t descriptorSet, const std::vector<std::pair<DescriptorType, std::pair<uint32_t, uint32_t>>>& updateValues) { return false; }

        virtual SR_FORCE_INLINE void SetCullFacingEnabled(const bool& enabled) const { }
        virtual SR_FORCE_INLINE void SetWireFrameEnabled(const bool& enabled) const { }
        virtual SR_FORCE_INLINE bool CalculateEmptyVAO(uint32_t& VAO) const { return false; }
        virtual int32_t CalculateVAO(std::vector<Vertices::StaticMeshVertex>& vertices, size_t count_verts) { return SR_ID_INVALID; }
        virtual int32_t CalculateVBO(void* vertices, Vertices::VertexType type, size_t count) { return SR_ID_INVALID; }
        virtual int32_t CalculateIBO(void* indices, uint32_t indxSize, size_t count, int32_t VBO) { return SR_ID_INVALID; }

        /** Vertex pos and texture cords */
        virtual SR_FORCE_INLINE bool CalculateQuad(uint32_t& VBO, uint32_t& VAO) const { return false; }
        SR_NODISCARD virtual uint32_t CalculateSkybox() const { return -1; }

        virtual SR_FORCE_INLINE void BindVBO(const uint32_t& VBO) { }
        virtual SR_FORCE_INLINE void BindIBO(const uint32_t& IBO) { }
        virtual SR_FORCE_INLINE void BindVAO(const uint32_t& VAO) { }
        virtual SR_FORCE_INLINE void BindUBO(const uint32_t& UBO) { }
        virtual SR_FORCE_INLINE void Draw6Triangles() const { }

        virtual SR_FORCE_INLINE void DrawSkybox(const uint32_t&  VAO, const uint32_t& CubeMap) const { }
        virtual SR_FORCE_INLINE void DrawQuad(const uint32_t&  VAO) const { }
        virtual SR_FORCE_INLINE void DrawTriangles(const uint32_t&  VAO, const uint32_t& count_vertices) const { }
        virtual SR_FORCE_INLINE void DrawTriangles(const uint32_t& count_vertices) const { }
        virtual SR_FORCE_INLINE void DrawLines(const uint32_t&  VAO, const uint32_t& count_vertices) const { }
        virtual SR_FORCE_INLINE void DrawInstancedVertices(uint32_t VAO, uint32_t IBO, uint32_t count) const { }
        virtual SR_FORCE_INLINE void DrawIndices(const uint32_t& countIndices) const { }
        virtual SR_FORCE_INLINE void Draw(const uint32_t& countVerts) const { }
        virtual SR_FORCE_INLINE void SetLineWidth(float_t width) const { }

        // ============================== [ TEXTURE METHODS ] ==============================

        virtual SR_FORCE_INLINE void BindTexture(const uint32_t&  ID) const { }
        virtual SR_FORCE_INLINE void BindTexture(const uint8_t activeTexture, const uint32_t&  ID) const { }
        virtual SR_FORCE_INLINE void SetActiveTexture(unsigned char activeTexture) const { }
        virtual SR_FORCE_INLINE bool FreeCubeMap(int32_t* ID) { return false; }

        SR_NODISCARD virtual int32_t CalculateCubeMap(uint32_t w, uint32_t h, const std::array<uint8_t*, 6>& data, bool cpuUsage) { return -1; }

        SR_NODISCARD virtual SR_FORCE_INLINE bool FreeVBO(int32_t* ID) const { return false; }
        SR_NODISCARD virtual SR_FORCE_INLINE bool FreeIBO(int32_t* ID) const { return false; }
        SR_NODISCARD virtual SR_FORCE_INLINE bool FreeUBO(int32_t* ID) const { return false; }
        SR_NODISCARD virtual bool FreeVAO(int32_t* VAO) const { return false; }
        SR_NODISCARD virtual bool FreeFBO(uint32_t FBO) const { return false; }
        SR_NODISCARD virtual bool FreeRBO(uint32_t RBO) const { return false; }
        SR_NODISCARD virtual bool FreeTextures(int32_t* IDs, uint32_t count) const { return false; }
        SR_NODISCARD virtual bool FreeTexture(int32_t* id) const { return false; }

        /* mipLevels :
              0 - auto
              1 - without
              2,3,4,5...
         */
        virtual int32_t CalculateTexture(
                uint8_t * data,
                ColorFormat format,
                uint32_t w, uint32_t h,
                TextureFilter filter,
                TextureCompression compression,
                uint8_t mipLevels,
                bool alpha,
                bool cpuUsage) const { return -1; }
    };
}

#endif //GAMEENGINE_ENVIRONMENT_H
