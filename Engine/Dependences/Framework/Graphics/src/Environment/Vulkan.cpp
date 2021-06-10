//
// Created by Nikita on 25.03.2021.
//

#include <Environment/Vulkan.h>
#include <ResourceManager/ResourceManager.h>
#include <FileSystem/FileSystem.h>
#include <Types/Vertices.h>

namespace Framework::Graphics{
    namespace VulkanTools {
        static VkFormat AttributeToVkFormat(const Vertices::Attribute& attr) {
            switch (attr) {
                case Vertices::Attribute::FLOAT_R32G32B32A32: return VK_FORMAT_R32G32B32A32_SFLOAT;
                case Vertices::Attribute::FLOAT_R32G32B32:    return VK_FORMAT_R32G32B32_SFLOAT;
                case Vertices::Attribute::FLOAT_R32G32:       return VK_FORMAT_R32G32_SFLOAT;
                default:                                      return VK_FORMAT_UNDEFINED;
            }
        }

        static std::vector<VkVertexInputBindingDescription> AbstractVertexDescriptionsToVk(const std::vector<SR_VERTEX_DESCRIPTION>& descriptions) {
            auto vkDescriptions = std::vector<VkVertexInputBindingDescription>();

            for (uint32_t i = 0; i < descriptions.size(); i++)
                vkDescriptions.push_back(EvoVulkan::Tools::Initializers::VertexInputBindingDescription(i, descriptions[i], VK_VERTEX_INPUT_RATE_VERTEX));

            return vkDescriptions;
        }

        static ShaderType VkShaderStageToShaderType(VkShaderStageFlagBits stage) {
            switch (stage) {
                case VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT: return ShaderType::Fragment;
                case VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT:   return ShaderType::Vertex;
                default:
                    Helper::Debug::Error("VulkanTools::VkShaderStageToShaderType() : unknown stage!");
                    return ShaderType::Unknown;
            }
        }

        static std::vector<VkVertexInputAttributeDescription> AbstractAttributesToVkAttributes(
                const std::vector<std::pair<Vertices::Attribute, size_t>>& attributes)
        {
            auto vkDescrs = std::vector<VkVertexInputAttributeDescription>();

            for (uint32_t i = 0; i < attributes.size(); i++) {
                auto format = AttributeToVkFormat(attributes[i].first);
                if (format == VK_FORMAT_UNDEFINED) {
                    Helper::Debug::Error("VulkanTools::AbstractDescriptionsToVkDescriptions() : unknown attribute!");
                    return { };
                }

                vkDescrs.emplace_back(EvoVulkan::Tools::Initializers::VertexInputAttributeDescription(0, i, format, attributes[i].second));
            }

            return vkDescrs;
        }

        static std::vector<std::pair<std::string, ShaderType>> VkModulesToAbstractModules(
                const std::vector<std::pair<std::string, VkShaderStageFlagBits>>& modules)
        {
            auto abstract = std::vector<std::pair<std::string, ShaderType>>();
            for (const auto& a : modules)
                abstract.emplace_back(std::pair(a.first, VkShaderStageToShaderType(a.second)));
            return abstract;
        }

        static VkPolygonMode AbstractPolygonModeToVk(PolygonMode polygonMode) {
            switch (polygonMode) {
                case PolygonMode::Fill:  return VK_POLYGON_MODE_FILL;
                case PolygonMode::Line:  return VK_POLYGON_MODE_LINE;
                case PolygonMode::Point: return VK_POLYGON_MODE_POINT;
            }
        }

        static VkCullModeFlagBits AbstractCullModeToVk(CullMode cullMode) {
            switch (cullMode) {
                case CullMode::None:         return VK_CULL_MODE_NONE;
                case CullMode::Front:        return VK_CULL_MODE_FRONT_BIT;
                case CullMode::Back:         return VK_CULL_MODE_BACK_BIT;
                case CullMode::FrontAndBack: return VK_CULL_MODE_FRONT_AND_BACK;
            }
        }

        static VkCompareOp AbstractDepthOpToVk(DepthCompare depthCompare) {
            switch (depthCompare) {
                case DepthCompare::Never:          return VK_COMPARE_OP_NEVER;
                case DepthCompare::Less:           return VK_COMPARE_OP_LESS;
                case DepthCompare::Equal:          return VK_COMPARE_OP_EQUAL;
                case DepthCompare::LessOrEqual:    return VK_COMPARE_OP_LESS_OR_EQUAL;
                case DepthCompare::Greater:        return VK_COMPARE_OP_GREATER;
                case DepthCompare::NotEqual:       return VK_COMPARE_OP_NOT_EQUAL;
                case DepthCompare::GreaterOrEqual: return VK_COMPARE_OP_GREATER_OR_EQUAL;
                case DepthCompare::Always:         return VK_COMPARE_OP_ALWAYS;
            }
        }
    }

    bool Vulkan::PreInit(unsigned int smooth_samples, const std::string& appName, const std::string& engineName) {
        EvoVulkan::Tools::VkDebug::Log   = [](const std::string& msg) { Helper::Debug::VulkanLog(msg); };
        EvoVulkan::Tools::VkDebug::Warn  = [](const std::string& msg) { Helper::Debug::Warn(msg);      };
        EvoVulkan::Tools::VkDebug::Error = [](const std::string& msg) { Helper::Debug::Error(msg);     };
        EvoVulkan::Tools::VkDebug::Graph = [](const std::string& msg) { Helper::Debug::Vulkan(msg);    };

        this->m_kernel = new SRVulkan();
        Helper::Debug::Info("Vulkan::PreInit() : pre-initializing vulkan...");

        if (m_enableValidationLayers)
            m_kernel->SetValidationLayersEnabled(true);

        this->m_viewport     = EvoVulkan::Tools::Initializers::Viewport(0, 0, 0, 0);
        this->m_scissor      = EvoVulkan::Tools::Initializers::Rect2D(0, 0, 0, 0);
        this->m_cmdBufInfo   = EvoVulkan::Tools::Initializers::CommandBufferBeginInfo();
        this->m_renderPassBI = EvoVulkan::Tools::Insert::RenderPassBeginInfo(0, 0, VK_NULL_HANDLE, VK_NULL_HANDLE, nullptr, 0);

        if (!this->m_kernel->PreInit(appName, engineName, m_instanceExtensions, m_validationLayers)) {
            Helper::Debug::Error("Vulkan::PreInit() : failed to pre-init Evo Vulkan kernel!");
            return false;
        }

        return true;
    }

    bool Vulkan::MakeWindow(const char *winName, bool fullScreen, bool resizable) {
        Helper::Debug::Graph("Vulkan::MakeWindow() : creating window...");

        if (!this->m_winFormat) {
            Helper::Debug::Error("Vulkan::MakeWindow() : format isn't initialized!");
            return false;
        }

        this->m_basicWindow = new Win32Window(this->GetPipeLine());

        m_basicWindow->SetCallbackResize([this](BasicWindow* win, int w, int h) {
            m_kernel->SetSize(w, h);
            g_callback(WinEvents::Resize, win, &w, &h);
        });

        if (!this->m_basicWindow->Create(winName, 0, 0, m_winFormat->Width(), m_winFormat->Height(), fullScreen, resizable)) {
            Helper::Debug::Error("Vulkan::MakeWindow() : failed to create window!");
            return false;
        }

        this->m_kernel->SetSize(m_basicWindow->GetRealWidth(), m_basicWindow->GetRealHeight());

        return true;
    }

    bool Vulkan::CloseWindow() {
        Helper::Debug::Graph("Vulkan::CloseWindow() : close window...");

        if (m_kernel)
            if (!this->m_kernel->Destroy()) {
                Helper::Debug::Error("Vulkan::CloseWindow() : failed to destroy Evo Vulkan kernel!");
                return false;
            }

        return true;
    }

    bool Vulkan::Init(int swapInterval) {
        Helper::Debug::Graph("Vulkan::Init() : initializing vulkan...");

        auto window = m_basicWindow;

        auto createSurf = [window](const VkInstance& instance) -> VkSurfaceKHR {
#ifdef WIN32 // TODO: use VK_USE_PLATFORM_WIN32_KHR
            if (window->GetType() == BasicWindow::Type::Win32) {
                VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
                surfaceInfo.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
                surfaceInfo.pNext     = nullptr;
                surfaceInfo.flags     = 0;
                surfaceInfo.hinstance = dynamic_cast<Win32Window *>(window)->GetHINSTANCE();
                surfaceInfo.hwnd      = dynamic_cast<Win32Window *>(window)->GetHWND();

                VkSurfaceKHR surface = VK_NULL_HANDLE;
                VkResult result = vkCreateWin32SurfaceKHR(instance, &surfaceInfo, nullptr, &surface);
                if (result != VK_SUCCESS)
                    return VK_NULL_HANDLE;
                else
                    return surface;
            }
            else {
                Helper::Debug::Error("Vulkan::Init() : window is not support this architecture!");
                return VK_NULL_HANDLE;
            }
#endif
        };

        if (!m_kernel->Init(createSurf, m_deviceExtensions, true, swapInterval > 0)) {
            Helper::Debug::Error("Vulkan::Init() : failed to initialize Evo Vulkan kernel!");
            return false;
        }

        Helper::Debug::Info("Vulkan::Init() : create vulkan memory manager...");
        this->m_memory = VulkanTools::MemoryManager::Create(this->m_kernel);
        if (!m_memory) {
            Helper::Debug::Error("Vulkan::Init() : failed to create vulkan memory manager!");
            return false;
        }

        this->m_screenSize = m_basicWindow->GetScreenResolution(0).ToGLM();

        return true;
    }

    void Vulkan::SetWindowSize(unsigned int w, unsigned int h) {
        if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
            Helper::Debug::Log("Vulkan::SetWindowSize() : width = " + std::to_string(w) + "; height = "+ std::to_string(h));

        this->m_basicWindow->Resize(w, h);
    }

    void Vulkan::SetWindowPosition(int x, int y) {
        this->m_basicWindow->Move(x, y);
    }

    bool Vulkan::PostInit() {
        Helper::Debug::Graph("Vulkan::PostInit() : post-initializing vulkan...");

        if (!m_kernel->PostInit()) {
            Helper::Debug::Error("Vulkan::PostInit() : failed to post-initialize Evo Vulkan kernel!");
            return false;
        }

        return true;
    }

    bool Vulkan::CompileShader(
            const std::string &path,
            int32_t FBO,
            void **shaderData,
            const std::vector<uint64_t>& uniformSizes
            ) const noexcept
    {
        if (FBO < 0) {
            Helper::Debug::Error("Vulkan::CompileShader() : vulkan required valid FBO for shaders!");
            return false;
        }

        EvoVulkan::Types::RenderPass renderPass = {};
        if (FBO == 0)
            renderPass = m_kernel->GetRenderPass();
        else {
            auto fbo = m_memory->m_FBOs[FBO - 1];
            if (!fbo) {
                Helper::Debug::Error("Vulkan::CompileShader() : invalid FBO! SOMETHING WENT WRONG! MEMORY MAY BE CORRUPTED!");
                return false;
            }

            renderPass = fbo->GetRenderPass();
        }

        if (!renderPass.Ready()) {
            Helper::Debug::Error("Vulkan::CompileShader() : internal Evo Vulkan error! Render pass isn't ready!");
            return false;
        }

        int32_t ID = m_memory->AllocateShaderProgram(renderPass);
        if (ID < 0) {
            Helper::Debug::Error("Vulkan::CompileShader() : failed to allocate shader program ID!");
            return false;
        } else {
            int* dynamicID = new int();
            *dynamicID = ID;
            *shaderData = reinterpret_cast<void*>(dynamicID);
        }

        std::string sharedShaderModule = Helper::ResourceManager::GetResourcesFolder()
                .append("\\Shaders\\")
                .append(GetPipeLineName())
                .append("\\")
                .append(path);

        std::string pathToShaderModules = Helper::StringUtils::GetDirToFileFromFullPath(sharedShaderModule);
        std::string shaderName = Helper::StringUtils::GetFileNameFromFullPath(path);

        std::vector<std::pair<std::string, VkShaderStageFlagBits>> modules = {};
        {
            std::string shaderModule = pathToShaderModules + "\\" + shaderName;

            if (Helper::FileSystem::FileExists(std::string(shaderModule + ".vert").c_str()))
                modules.emplace_back(std::pair(shaderName + ".vert", VK_SHADER_STAGE_VERTEX_BIT));

            if (Helper::FileSystem::FileExists(std::string(shaderModule + ".frag").c_str()))
                modules.emplace_back(std::pair(shaderName + ".frag", VK_SHADER_STAGE_FRAGMENT_BIT));
        }

        bool errors = false;
        std::vector<std::pair<LayoutBinding, ShaderType>> bindings =
                Graphics::AnalyseShader(VulkanTools::VkModulesToAbstractModules(modules), pathToShaderModules, &errors);
        if (errors) {
            Helper::Debug::Error("Vulkan::CompileShader() : failed to analyse shader!");
            return false;
        }

        std::vector<VkDescriptorSetLayoutBinding> descriptorLayoutBindings = {};
        {
            VkDescriptorType      type  = VK_DESCRIPTOR_TYPE_MAX_ENUM;
            VkShaderStageFlagBits stage = VK_SHADER_STAGE_ALL;

            for (uint32_t i = 0; i < bindings.size(); i++) {
                switch (bindings[i].first) {
                    case LayoutBinding::Sampler2D : type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER; break;
                    case LayoutBinding::Uniform:    type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;         break;
                    default:
                        Helper::Debug::Error("Vulkan::CompileShader() : unknown binding type!");
                        return false;
                }

                switch (bindings[i].second) {
                    case ShaderType::Vertex:   stage = VK_SHADER_STAGE_VERTEX_BIT;   break;
                    case ShaderType::Fragment: stage = VK_SHADER_STAGE_FRAGMENT_BIT; break;
                    default:
                        Helper::Debug::Error("Vulkan::CompileShader() : unknown binding stage!");
                        return false;
                }

                descriptorLayoutBindings.emplace_back(EvoVulkan::Tools::Initializers::DescriptorSetLayoutBinding(type, stage, i));
            }
        }

        if (!m_memory->m_ShaderPrograms[ID]->Load(
                pathToShaderModules,
                Helper::ResourceManager::GetResourcesFolder() + "\\Cache\\Shaders",
                modules,
                descriptorLayoutBindings,
                uniformSizes
                )) {
            Helper::Debug::Error("Vulkan::CompileShader() : failed to load Evo Vulkan shader!");
            return false;
        }

        return true;
    }

    bool Vulkan::LinkShader(
            unsigned int *shaderProgram,
            void **shaderData,
            const std::vector<SR_VERTEX_DESCRIPTION>& vertexDescriptions,
            const std::vector<std::pair<Vertices::Attribute, size_t>>& vertexAttributes,
            SRShaderCreateInfo shaderCreateInfo) const noexcept
    {
        if (!shaderData) {
            Helper::Debug::Error("Vulkan::LinkShader() : shader data is nullptr!");
            return false;
        }
        int* dynamicID = reinterpret_cast<int*>(*shaderData);
        if (!dynamicID) {
            Helper::Debug::Error("Vulkan::LinkShader() : dynamic ID is nullptr!");
            return false;
        }

        //auto vkVertexDescriptions = std::vector<VkVertexInputBindingDescription>(vertexDescriptions.size());
        auto vkVertexDescriptions = VulkanTools::AbstractVertexDescriptionsToVk(vertexDescriptions);
        auto vkVertexAttributes   = VulkanTools::AbstractAttributesToVkAttributes(vertexAttributes);
        if (vkVertexAttributes.size() != vertexAttributes.size()) {
            Helper::Debug::Error("Vulkan::LinkShader() : vkVertexDescriptions size != vertexDescriptions size!");
            delete dynamicID;
            return false;
        }

        if (!m_memory->m_ShaderPrograms[*dynamicID]->SetVertexDescriptions(vkVertexDescriptions, vkVertexAttributes)) {
            Helper::Debug::Error("Vulkan::LinkShader() : failed to set vertex descriptions!");
            delete dynamicID;
            return false;
        }

        if (!m_memory->m_ShaderPrograms[*dynamicID]->Compile(
                VulkanTools::AbstractPolygonModeToVk(shaderCreateInfo.polygonMode),
                VulkanTools::AbstractCullModeToVk(shaderCreateInfo.cullMode),
                VulkanTools::AbstractDepthOpToVk(shaderCreateInfo.depthCompare),
                shaderCreateInfo.blendEnabled,
                shaderCreateInfo.depthEnabled))
        {
            Helper::Debug::Error("Vulkan::LinkShader() : failed to compile Evo Vulkan shader!");
            delete dynamicID;
            return false;
        }

        delete dynamicID;
        return true;
    }
}