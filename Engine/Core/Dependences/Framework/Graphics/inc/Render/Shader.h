//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <Types/Vertices.h>
#include <Types/Uniforms.h>
#include <Utils/NonCopyable.h>
#include <Utils/Hashes.h>
#include <ResourceManager/IResource.h>
#include <Environment/Basic/IShaderProgram.h>
#include <Types/Map.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    class Render;
    class Shader;
    class Environment;

    class ShaderUBOBlock {
        friend class Shader;

        struct SubBlock {
            ShaderVarType type;
            uint32_t size;
            uint32_t offset;
            bool hidden;
        };

    public:
        ShaderUBOBlock();

    public:

        void Append(uint64_t hashId, ShaderVarType type, bool hidden);
        void Init();
        void DeInit();
        void SetField(uint64_t hashId, const void* data) noexcept;

        SR_NODISCARD uint32_t GetBinding() const { return m_binding; }
        SR_NODISCARD bool Valid() const { return m_memory && m_binding != SR_ID_INVALID; }

    private:
        uint32_t m_binding = SR_ID_INVALID;
        google::dense_hash_map<uint64_t, SubBlock> m_data;
        uint32_t m_size = 0;
        char* m_memory = nullptr;

    };

    class Shader : public Helper::IResource {
    public:
        explicit Shader(std::string path);
        Shader(std::string path, std::string name);

    private:
        ~Shader() override;

    public:
        typedef enum {
            Skybox = 1,
            DebugWireframe = 3,
            Grid = 4,
            Custom = 0xffff,
        } StandardID;

        static constexpr uint64_t MODEL_MATRIX = SR_COMPILE_TIME_CRC32_STR("MODEL_MATRIX");
        static constexpr uint64_t VIEW_MATRIX = SR_COMPILE_TIME_CRC32_STR("VIEW_MATRIX");
        static constexpr uint64_t VIEW_NO_TRANSLATE_MATRIX = SR_COMPILE_TIME_CRC32_STR("VIEW_NO_TRANSLATE_MATRIX");
        static constexpr uint64_t PROJECTION_MATRIX = SR_COMPILE_TIME_CRC32_STR("PROJECTION_MATRIX");
        static constexpr uint64_t TIME = SR_COMPILE_TIME_CRC32_STR("TIME");
        static constexpr uint64_t SKYBOX_DIFFUSE = SR_COMPILE_TIME_CRC32_STR("SKYBOX_DIFFUSE");

    private:
        bool Link();
        bool Compile();

    public:
        bool Init();
        SR_FORCE_INLINE static Shader* GetCurrentShader() { return g_currentShader; }

        static Shader* Load(const SR_UTILS_NS::Path& path);
        static Shader* LoadFromConfig(const std::string& name);

    public:
        SR_NODISCARD SR_FORCE_INLINE std::string GetPath() const { return m_path; }
        SR_NODISCARD SR_FORCE_INLINE Render* GetRender() const { return m_render; }
        SR_NODISCARD SR_FORCE_INLINE std::string GetName() const { return m_name; }
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
        //SR_NODISCARD int32_t GetUBO(const uint32_t& index) const;
        SR_NODISCARD int32_t GetID();
        SR_NODISCARD bool Ready() const;
        SR_NODISCARD uint64_t GetUBOBlockSize() const;
        SR_NODISCARD uint32_t GetSamplersCount() const;
        SR_NODISCARD ShaderProperties GetProperties();

    public:
        SR_NODISCARD SR_FORCE_INLINE bool Complete() const { return m_isInit; }

        bool Use() noexcept;
        void UnUse() noexcept;
        bool InitUBOBlock();
        bool Flush() const;
        void FreeVideoMemory();
        bool Reload() override;

        bool SetVertex(const VertexDescriptions& descriptions, const VertexAttributes& attributes);

        /**
         * 0 - binding
         * 1 - type
         * 2 - ubo size
         */
        bool SetUniforms(const UBOInfo& uniforms);
        bool SetCreateInfo(SRShaderCreateInfo shaderCreateInfo);

    public:
        template<typename T> void SetValue(uint64_t hashId, const T& v) noexcept {
            if (!IsLoaded()) {
                return;
            }

            m_uniformBlock.SetField(hashId, &v);
        }

        void SetBool(uint64_t hashId, const bool& v) noexcept;
        void SetFloat(uint64_t hashId, const float& v) noexcept;
        void SetInt(uint64_t hashId, const int& v) noexcept;
        void SetMat4(uint64_t hashId, const glm::mat4& v) noexcept;
        void SetVec4(uint64_t hashId, const glm::vec4& v) noexcept;
        void SetVec3(uint64_t hashId, const glm::vec3& v) noexcept;
        void SetVec2(uint64_t hashId, const glm::vec2& v) noexcept;
        void SetIVec2(uint64_t hashId, const glm::ivec2& v) noexcept;
        void SetSampler2D(const std::string& name, Types::Texture* sampler) noexcept;
        void SetSamplerCube(uint64_t hashId, int32_t sampler) noexcept;
        void SetSampler2D(uint64_t hashId, Types::Texture* sampler) noexcept;

    private:
        void SetSampler(uint64_t hashId, int32_t sampler) noexcept;

    private:
        inline static Shader* g_currentShader        = nullptr;

        SR_SHADER_PROGRAM     m_shaderProgram        = SR_NULL_SHADER;
        void*                 m_shaderTempData       = nullptr;

        std::atomic<bool>     m_isLink               = false;
        std::atomic<bool>     m_isCompile            = false;
        std::atomic<bool>     m_hasErrors            = false;
        std::atomic<bool>     m_isInit               = false;

    private: // For vulkan
        SRShaderCreateInfo    m_shaderCreateInfo     = {};
        VertexAttributes      m_verticesAttributes   = {};
        VertexDescriptions    m_verticesDescription  = {};

        int32_t               m_fbo                  = -1;

        UBOInfo               m_uniformsInfo         = {};
        ShaderUBOBlock        m_uniformBlock         = ShaderUBOBlock();
        ShaderSamplers        m_samplers             = ShaderSamplers();
        ShaderProperties      m_properties           = ShaderProperties();

    private:
        Render*               m_render               = nullptr;
        Environment*          m_env                  = nullptr;
        std::string           m_name                 = "Unnamed";
        std::string           m_path                 = "Unknown";

    };
}

#endif //GAMEENGINE_SHADER_H
