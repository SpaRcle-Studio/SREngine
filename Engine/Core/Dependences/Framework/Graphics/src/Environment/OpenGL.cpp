//
// Created by Nikita on 18.11.2020.
//



#include <Environment/OpenGL.h>

#include <Utils/Common/StringUtils.h>
#include <Utils/GUI.h>
#include <Utils/ResourceManager/ResourceManager.h>

#include <Environment/Win32Window.h>

#define OpenGLSetVertexAttribPointer(id, count, vertex, offset) \
    glEnableVertexAttribArray(id); \
    glVertexAttribPointer(id, count, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offset); \

unsigned int SR_GRAPH_NS::OpenGL::CreateTexture(unsigned char *pixels, int w, int h, int components) {
    GLuint textureID;
    /// glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    /// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    ///glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    ///glTexImage2D(GL_TEXTURE_2D, 0, components, w, h, 0, (components == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    return (unsigned int)textureID;
}

bool Framework::Graphics::OpenGL::InitGUI() {
    SR_GRAPH_LOG("OpenGL::InitGUI() : initializing ImGUI library...");

#ifdef  SR_OPENGL_USE_WINAPI
    this->m_basicWindow->InitGUI();
    ImGui_ImplOpenGL3_Init("#version 130");
#else
    ImGui_ImplGlfw_InitForOpenGL(this->m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
#endif

    return true;
}


bool Framework::Graphics::OpenGL::StopGUI() {
    SR_GRAPH_LOG("OpenGL::StopGUI() : stopping ImGUI library...");

#ifdef  SR_OPENGL_USE_WINAPI
    ImGui_ImplOpenGL3_Init();
    this->m_basicWindow->InitGUI();

    ImGui::DestroyContext();
#else
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();
#endif

    return true;
}

bool Framework::Graphics::OpenGL::PreInit(
        unsigned int smooth_samples,
        const std::string& appName,
        const std::string& engineName,
        const std::string& glslc) {
#ifdef  SR_OPENGL_USE_WINAPI

#else
    SR_GRAPH_LOG("OpenGL::PreInit() : initializing glfw...");

    if (!glfwInit()) {
        SR_ERROR("OpenGL::PreInit() : failed initializing glfw!");
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, (int)smooth_samples); // 4x сглаживание
    //glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); //3
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#endif


    return true;
}

bool Framework::Graphics::OpenGL::MakeWindow(const std::string& name, const SR_MATH_NS::IVector2& size, bool fullScreen, bool resizable, bool headerEnabled) {
#ifdef  SR_OPENGL_USE_WINAPI
    this->m_basicWindow = new Win32Window(this->GetPipeLine());
    if (!this->m_basicWindow->Create(
            winName, 0, 0,
            (int)m_winFormat->Width(), (int)m_winFormat->Height(),
            fullScreen, resizable))
    {
        SR_ERROR("OpenGL::MakeWindow() : failed create window!");
        return false;
    } else
        return true;
#else
    m_monitor = glfwGetPrimaryMonitor();
    m_vidMode = glfwGetVideoMode(m_monitor);

    m_window = glfwCreateWindow(size.x, size.y, name.c_str(), fullScreen ? m_monitor : nullptr, nullptr);

    return m_window != nullptr;
#endif
}

bool Framework::Graphics::OpenGL::SetContextCurrent() {
#ifdef  SR_OPENGL_USE_WINAPI
    this->m_basicWindow->MakeContextCurrent();
#else
    if (m_window)
        glfwMakeContextCurrent(m_window);
#endif

    return true;
}

bool Framework::Graphics::OpenGL::Init(int swapInterval) {
#ifdef  SR_OPENGL_USE_WINAPI
    this->m_basicWindow->SetSwapInterval(swapInterval);
#else
    glfwSwapInterval(swapInterval);

    glfwSetWindowFocusCallback(m_window, [](GLFWwindow* win, int focus) {
        bool bFocus = focus == 1;
        g_callback(WinEvents::Focus, win, &bFocus, nullptr);
    });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* win, int w, int h) {
        g_callback(WinEvents::Resize, win, &w, &h);
    });

    glfwSetWindowCloseCallback(m_window, (GLFWwindowclosefun)[](GLFWwindow* win) {
        g_callback(WinEvents::Close, win, nullptr, nullptr);
    });

    glfwSetWindowPosCallback(m_window, [](GLFWwindow* win, int x, int y){
        g_callback(WinEvents::Move, win, &x, &y);
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* win, double xoffset, double yoffset){
        for (const auto& a : g_scrollEvents)
            a(xoffset, yoffset);

        g_callback(WinEvents::Scroll, win, &xoffset, &yoffset);
    });
#endif


    SR_GRAPH_LOG("OpenGL::PreInit() : initializing glew...");
    ///glewExperimental = TRUE;
    ///if (glewInit() != GLEW_OK) {
    ///    Helper::Debug::Error("OpenGL::PreInit() : failed initializing glew!");
    ///    return false;
    ///}

    ///if (wglewIsSupported("WGL_ARB_create_context") != 1) {
    ///    Helper::Debug::Error("OpenGL::PreInit() : wglew is not support!");
    ///    return false;
    /// }

    return true;
}

bool Framework::Graphics::OpenGL::PostInit() {
    glEnable(GL_BLEND); // Прозрачность стекла
    /// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /// glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    glBlendEquation(GL_FUNC_ADD);

    glEnable(GL_TEXTURE_2D);
    /// glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    /// glEnable(GL_ALPHA_TEST);
    /// glEnable(GL_COLOR_MATERIAL);

    ///glEnable(GL_MULTISAMPLE);

    ///\%info ПРОВЕРЯЕМ ГЛУБИНУ, ЧТОБЫ ИЗБАВИТЬСЯ ОТ "ЭФФЕКТИА ПЕРЕКРЫТИЯ" ДАЛЬНИМИ ОБЪЕКТАМИ
    /// glDepthFunc(GL_LEQUAL);
    /// glDepthRange(0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // Отсечение граней

///    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Действительно хорошие вычисления перспективы

    return true;
}

bool Framework::Graphics::OpenGL::CloseWindow() {
    return true;
}

void Framework::Graphics::OpenGL::SetWindowSize(unsigned int w, unsigned int h) {
    //if (m_winFormat->GetValue() != Types::WindowFormat::Free) {
    //    w = m_winFormat->Width();
    //    h = m_winFormat->Height();
    // } else

    //if (SR_Debug::GetLevel() >= Debug::Level::High) {
        SR_LOG("OpenGL::SetWindowSize() : width = " + std::to_string(w) + "; height = " + std::to_string(h));
    //}

#ifdef  SR_OPENGL_USE_WINAPI

#else
    //m_winFormat->SetFreeValue(w, h);
    glfwSetWindowSize(m_window, w, h);
#endif

    glViewport(0, 0, w, h);// определ¤ем окно просмотра
}

void Framework::Graphics::OpenGL::SetWindowPosition(int x, int y) {
#ifdef  SR_OPENGL_USE_WINAPI

#else
    glfwSetWindowPos(m_window, x, y);
#endif
}

bool Framework::Graphics::OpenGL::FreeVAO(int* VAO) const {
    //if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
    //    Helper::Debug::Log("OpenGL::FreeVAO() : free mesh \""+std::to_string(VAO) + "\" VAO...");

    if (VAO) {
        //glDeleteVertexArrays(1, &VAO);
        return true;
    }
    else {
        SR_ERROR("OpenGL::FreeVAO() : VAO is zero! Something went wrong...");
        return false;
    }
}

std::vector<std::string> FindFields(const std::string& path) {
    std::ifstream stream(path, std::ios::in);

    auto fields = std::vector<std::string>();

    if (stream.is_open()) {
        std::string line;
        while (getline(stream, line)) {
            auto p = line.find("uniform");
            if (p != -1) {
                line = SR_UTILS_NS::StringUtils::ReadTo(line, ';', p);
                if (line.find("//") == -1) {
                    line = SR_UTILS_NS::StringUtils::BackRead(line, ' ', -1);
                    //std::cout << line << std::endl;
                    fields.push_back(line);
                }
            }
        }
        stream.close();
    }

    return fields;
}

std::map<std::string, unsigned int> Framework::Graphics::OpenGL::GetShaderFields(const unsigned int& ID, const std::string &path) const {
    auto v = FindFields(path + "_vertex.glsl");
    auto f = FindFields(path + "_fragment.glsl");

    v.insert(v.end(), f.begin(), f.end());

    auto fields = std::map<std::string, unsigned int>();

    for (const auto& field : v)
        if (fields.find(field) == fields.end()) {
            int location = glGetUniformLocation(ID, field.c_str());
            if (location < 0) {
                SR_ERROR("OpenGL::GetShaderFields() : field \""+field+"\" not found! ("+std::to_string(location)+") \n\tMay be this field is not using...");
            }
            else {
                SR_LOG("OpenGL::GetShaderFields() : add field \"" + field + "\"");

                fields.insert(std::make_pair(field, location));
            }
        }

    return fields;
}

struct GLShaderData {
    unsigned int m_vertex = 0;
    unsigned int m_fragment = 0;
};

bool Framework::Graphics::OpenGL::CompileShader(
        const std::string& name,
        int32_t FBO,
        void** shaderData,
        const std::vector<uint64_t>& uniformSizes)
{
    auto shadersPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Shaders");

    auto vertexPath = shadersPath.Concat("Common").Concat(name).ConcatExt(".vert");
    auto fragmentPath = shadersPath.Concat("Common").Concat(name).ConcatExt(".frag");

    if (!Helper::FileSystem::FileExists(vertexPath))
        vertexPath = shadersPath.Concat(GetPipeLineName()).Concat(name).ConcatExt(".vert");

    if (!Helper::FileSystem::FileExists(fragmentPath))
        fragmentPath = shadersPath.Concat(GetPipeLineName()).Concat(name).ConcatExt(".frag");

    auto* glShader = new GLShaderData();

    int	  InfoLogLength	= 0;
    GLint Result		= GL_FALSE;

    //! создаем шейдеры
    glShader->m_vertex   = glCreateShader(GL_VERTEX_SHADER);
    glShader->m_fragment = glCreateShader(GL_FRAGMENT_SHADER);

    //! читаем вершинный шейдер из файла
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertexPath, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::string line;
        while (getline(VertexShaderStream, line))
            VertexShaderCode += "\n" + line;
        VertexShaderStream.close();
    }
    else {
        SR_ERROR("OpenGL::CompileShader() : failed to read vertex shader! \n\tPath: " + vertexPath.ToString());
        return false;
    }

    //! читаем фрагментный шейдер из файла
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragmentPath, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::string line;
        while (getline(FragmentShaderStream, line))
            FragmentShaderCode += "\n" + line;
        FragmentShaderStream.close();
    }
    else {
        SR_ERROR("OpenGL::CompileShader() : failed to read fragment shader! \n\tPath: " + fragmentPath.ToString());
        return false;
    }

    std::string error;

    {
        // Компилируем вершинный шейдер
        char const* VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(glShader->m_vertex, 1, &VertexSourcePointer, NULL);
        glCompileShader(glShader->m_vertex);

        // Устанавливаем параметры
        glGetShaderiv(glShader->m_vertex, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(glShader->m_vertex, GL_INFO_LOG_LENGTH, &InfoLogLength);

        //?===========================================[ ERRORS ]==============================================
        if (InfoLogLength != 0) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength);
            glGetShaderInfoLog(glShader->m_vertex, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
            if (VertexShaderErrorMessage.size() > 10) {
                SR_ERROR("OpenGL::CompileShader : Failed compiling vertex shader!\n\tReason : " +
                             std::string(VertexShaderErrorMessage.data()));
                return false;
            }
        }
        //?===================================================================================================
    }

    {
        // Компилируем фрагментный шейдер
        char const* FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(glShader->m_fragment, 1, &FragmentSourcePointer, nullptr);
        glCompileShader(glShader->m_fragment);

        // Устанавливаем параметры
        glGetShaderiv(glShader->m_fragment, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(glShader->m_fragment, GL_INFO_LOG_LENGTH, &InfoLogLength);

        //?===========================================[ ERRORS ]==============================================
        if (InfoLogLength != 0) {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
            glGetShaderInfoLog(glShader->m_fragment, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
            if (FragmentShaderErrorMessage.size() > 10) {
                bool isError = SR_UTILS_NS::StringUtils::Contains(std::string(FragmentShaderErrorMessage.data()), "error");

                if (isError) {
                    SR_ERROR("OpenGL::CompileShader() : Failed compiling fragment shader!\n\tReason : " +
                                 std::string(FragmentShaderErrorMessage.data()));
                    return false;
                }
                else {
                    SR_WARN("OpenGL::CompileShader() : There are warnings in the shader!\n\tReason: " +
                            std::string(FragmentShaderErrorMessage.data()));
                }
            }
        }
        //?===================================================================================================
    }

    *shaderData = (void*)glShader;

    return true;
}

bool Framework::Graphics::OpenGL::LinkShader(
        SR_SHADER_PROGRAM* shaderProgram,
        void** shaderData,
        const std::vector<SR_VERTEX_DESCRIPTION>& vertexDescriptions,
        const std::vector<std::pair<Vertices::Attribute, size_t>>& vertexAttributes,
        SRShaderCreateInfo shaderCreateInfo) const
{
    if (!shaderProgram)
        return false;

    if (!shaderData) {
        SR_ERROR("OpenGL::LinkShader() : shader data is nullptr!");
        return false;
    }

    auto* glShader = (GLShaderData*)(*shaderData);

    unsigned int ProgramID = glCreateProgram();
    glAttachShader(ProgramID, glShader->m_vertex);
    glAttachShader(ProgramID, glShader->m_fragment);
    glLinkProgram(ProgramID);

    int	  InfoLogLength	= 0;
    GLint Result		= GL_FALSE;

    // Устанавливаем параметры
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    //?===========================================[ ERRORS ]==============================================
    if (InfoLogLength != 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        std::string error = SR_UTILS_NS::StringUtils::FromCharVector(ProgramErrorMessage);
        if (!error.empty()) {
            auto index = error.find("error");
            if (index == std::string::npos) {
                SR_WARN("OpenGL::LinkShader : Warning linking program! Reason : " + error);
            }
            else {
                SR_ERROR("OpenGL::LinkShader : Failed linking program! Reason : " + error);
                SRAssert(false);
                return false;
            }
        }
    }
    //?===================================================================================================

    glDeleteShader(glShader->m_vertex);
    glDeleteShader(glShader->m_fragment);

    glShader->m_vertex    = 0;
    glShader->m_fragment  = 0;

    delete glShader;
    *shaderData = nullptr;

    *shaderProgram = ProgramID;

    return true;
}

bool Framework::Graphics::OpenGL::CreateFrameBuffer(glm::vec2 size, int32_t& rboDepth, int32_t &hdrFBO, std::vector<int32_t>& colorBuffers) {
    bool isNew = hdrFBO <= 0;//!((bool)hdrFBO);

    /**if (size.x == 0 || size.y == 0){
        Helper::Debug::Error("OpenGL::CreateFrameBuffer() : frame buffer has incorrect size!");
        return false;
    }

    if (isNew){
        Helper::Debug::Log("OpenGL::CreateFrameBuffer() : creating new frame buffers...");
    }

    if (isNew)
        glGenFramebuffers(1, reinterpret_cast<GLuint *>(&hdrFBO));
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    // create n floating point color buffers (1 for normal rendering, other for brightness threshold values)

    if (isNew)
        glGenTextures(colorBuffers.size(), reinterpret_cast<GLuint *>(colorBuffers.data()));

    for (unsigned int i = 0; i < colorBuffers.size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, size.x, size.y, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // attach texture to framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }
    // create and attach depth buffer (renderbuffer)
    if (isNew)
        glGenRenderbuffers(1, reinterpret_cast<GLuint *>(&rboDepth));
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    //unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    std::vector<unsigned int> attachments;
    for (unsigned int i = 0; i < colorBuffers.size(); i++)
    {
        attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
    }
    glDrawBuffers(attachments.size(), attachments.data());

    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        Debug::Error("OpenGL::CreateFrameBuffer() : frame buffer is not complete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (isNew){
        std::string colorBfs = "\n\tColorBuffers: ";
        for (size_t t = 0; t < colorBuffers.size(); t++)
            colorBfs += std::to_string(colorBuffers[t]) + (t+1 == colorBuffers.size() ? "" : ",");

        Debug::Log("OpenGL::CreateFrameBuffer() : successful!\n\tRBODepth: "+std::to_string(rboDepth)+
            "\n\tHDR_FBO: "+std::to_string(hdrFBO) + colorBfs);
    }*/

    return true;
}

bool Framework::Graphics::OpenGL::CreatePingPongFrameBuffer(
        glm::vec2 size,
        std::vector<int32_t> &pingpongFBO,
        std::vector<int32_t>& pingpongColorBuffers) const
{
    bool isNew = pingpongFBO[0] <= 0;

    if (isNew) {
        SR_LOG("OpenGL::CreatePingPongFrameBuffer() : creating ping-pong frame buffers...");
        /// glGenFramebuffers(pingpongFBO.size(), reinterpret_cast<GLuint *>(pingpongFBO.data()));
        glGenTextures(pingpongColorBuffers.size(), reinterpret_cast<GLuint *>(pingpongColorBuffers.data()));
    }

    for (unsigned int i = 0; i < pingpongFBO.size(); i++)
    {
///        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongColorBuffers[i]);
///        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, size.x, size.y, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
///        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
///        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
///        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorBuffers[i], 0);
        // also check if framebuffers are complete (no need for depth buffer)
///        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
///            Debug::Error("OpenGL::CreatePingPongFrameBufferObject() : frame buffer is not complete!");
///            return false;
///        }
    }

///    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (isNew){
        std::string PingPongFBOBufs = "\n\tPingPongFBO: ";
        for (size_t t = 0; t < pingpongFBO.size(); t++)
            PingPongFBOBufs += std::to_string(pingpongFBO[t]) + (t+1 == pingpongFBO.size() ? "" : ",");

        std::string PingPongColorBufs = "\n\tPingPongColorBuffers: ";
        for (size_t t = 0; t < pingpongColorBuffers.size(); t++)
            PingPongColorBufs += std::to_string(pingpongColorBuffers[t]) + (t+1 == pingpongColorBuffers.size() ? "" : ",");

        SR_LOG("OpenGL::CreateHDRFrameBufferObject() : successful!"+PingPongFBOBufs+PingPongColorBufs);
    }

    return true;
}

int32_t Framework::Graphics::OpenGL::CalculateTexture(
        uint8_t *data,
        TextureFormat format,
        uint32_t w, uint32_t h,
        Framework::Graphics::TextureFilter filter,
        TextureCompression compression,
        uint8_t mipLevels,
        bool alpha,
        bool cpuUsage
) const {
    unsigned int id;
    glGenTextures(1, &id);

    /**
    GLuint gl_filter = 0;
    switch(filter){
        case TextureFilter::NEAREST:
            gl_filter = GL_NEAREST; break;
        case TextureFilter::LINEAR:
            gl_filter = GL_LINEAR; break;
        case TextureFilter::NEAREST_MIPMAP_NEAREST:
            gl_filter = GL_NEAREST_MIPMAP_NEAREST; break;
        case TextureFilter::LINEAR_MIPMAP_NEAREST:
            gl_filter = GL_LINEAR_MIPMAP_NEAREST; break;
        case TextureFilter::NEAREST_MIPMAP_LINEAR:
            gl_filter = GL_NEAREST_MIPMAP_LINEAR; break;
        case TextureFilter::LINEAR_MIPMAP_LINEAR:
            gl_filter = GL_LINEAR_MIPMAP_LINEAR; break;
        case TextureFilter::Unknown:
            break; // TODO
    }
*/
    SR_LOG("OpenGL::CalculateTexture() : calculating (ID "+std::to_string(id)+") texture...");

    glBindTexture(GL_TEXTURE_2D, id);

    // TODO: use alpha or format == 4 ?????????
    /// GLuint compress = alpha ? GL_COMPRESSED_RGBA_S3TC_DXT5_EXT : GL_COMPRESSED_RGB_S3TC_DXT1_EXT; //GL_RGBA16F
    ///glTexImage2D(GL_TEXTURE_2D, 0, compress, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    ///glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter);
    ///glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter);

    /**GLuint texParam = GL_CLAMP_TO_BORDER; // GL_REPEAT, GL_CLAMP_TO_BORDER
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texParam); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texParam);*/

    /*
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texParam);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter);

    //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, m_image->m_width, m_image->m_height, m_image->m_format,
    //	GL_UNSIGNED_BYTE, (unsigned int*)m_image->m_data);

    if(!alpha)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, w, h,
                     0, format, GL_UNSIGNED_BYTE, (unsigned int*)data);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, w, h,
                     0, format, GL_UNSIGNED_BYTE, (unsigned int*)data);


       // GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT - black-white
       // GL_COMPRESSED_RGB_S3TC_DXT1_EXT
       // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
       // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
       // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // What it need?
    */

    glBindTexture(GL_TEXTURE_2D, 0);

    return id;
}

int32_t Framework::Graphics::OpenGL::CalculateCubeMap(uint32_t w, uint32_t h, const std::array<uint8_t*, 6>& data, bool cpuUsage) {
    uint32_t cubemap = 0;

    glGenTextures(1, &cubemap);
    /*glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

    for (unsigned char c = 0; c < 6; c++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + c,
                     0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data[c]
        );
        delete data[c];
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);*/

    return cubemap;
}

unsigned int Framework::Graphics::OpenGL::CalculateSkybox() const {
    const float skyboxVertices[36 * 3] = {
            // positions
            -10.0f,  10.0f, -10.0f,
            -10.0f, -10.0f, -10.0f,
            10.0f, -10.0f, -10.0f,
            10.0f, -10.0f, -10.0f,
            10.0f,  10.0f, -10.0f,
            -10.0f,  10.0f, -10.0f,

            -10.0f, -10.0f,  10.0f,
            -10.0f, -10.0f, -10.0f,
            -10.0f,  10.0f, -10.0f,
            -10.0f,  10.0f, -10.0f,
            -10.0f,  10.0f,  10.0f,
            -10.0f, -10.0f,  10.0f,

            10.0f, -10.0f, -10.0f,
            10.0f, -10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            10.0f,  10.0f, -10.0f,
            10.0f, -10.0f, -10.0f,

            -10.0f, -10.0f,  10.0f,
            -10.0f,  10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            10.0f, -10.0f,  10.0f,
            -10.0f, -10.0f,  10.0f,

            -10.0f,  10.0f, -10.0f,
            10.0f,  10.0f, -10.0f,
            10.0f,  10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            -10.0f,  10.0f,  10.0f,
            -10.0f,  10.0f, -10.0f,

            -10.0f, -10.0f, -10.0f,
            -10.0f, -10.0f,  10.0f,
            10.0f, -10.0f, -10.0f,
            10.0f, -10.0f, -10.0f,
            -10.0f, -10.0f,  10.0f,
            10.0f, -10.0f,  10.0f
    };

    unsigned int VAO = 0;
    unsigned int VBO = 0;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

///    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);

    return VAO;
}

bool Framework::Graphics::OpenGL::BeginDrawGUI() {
    ImGui_ImplOpenGL3_NewFrame();
#ifdef  SR_OPENGL_USE_WINAPI
    this->m_basicWindow->NextFrameGUI();
#else
    ImGui_ImplGlfw_NewFrame();
#endif

    ImGui::NewFrame();

    ImGuizmo::BeginFrame();
    ImGuizmo::Enable(true);

    ImGui::GetStyle().WindowRounding = 0.0f;

    return true;
}

void Framework::Graphics::OpenGL::EndDrawGUI() {
    ImGui::Render();
    int display_w, display_h;
#ifdef  SR_OPENGL_USE_WINAPI
    display_w = m_basicWindow->GetWidth();
    display_h = m_basicWindow->GetHeight();
#else
    glfwGetFramebufferSize(this->m_window, &display_w, &display_h);
#endif

    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Framework::Graphics::OpenGL::CreateSingleFrameBuffer(glm::vec2 size, int32_t &rboDepth, int32_t &hdrFBO, int32_t &colorBuffer) {
    bool isNew = hdrFBO <= 0; //!((bool)hdrFBO);

    /**if (isNew)
        SR_GRAPH_LOG("OpenGL::CreateSingleFrameBuffer() : creating new single frame buffer object...");

    if (isNew)
        glGenFramebuffers(1, reinterpret_cast<GLuint *>(&hdrFBO));

    if (isNew)
        glGenTextures(1, reinterpret_cast<GLuint *>(&colorBuffer));

    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, size.x, size.y, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    //================================================================================================

    if (colorBuffer && hdrFBO) {
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        // присоедиение текстуры к объекту текущего кадрового буфера
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);
    }
    else {
        Debug::Error("OpenGL::CreateSingleFrameBuffer() : color buffer or FBO is not created!");
        return false;
    }

    if (isNew)
        glGenRenderbuffers(1, reinterpret_cast<GLuint *>(&rboDepth));

    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        Debug::Error("OpenGL::CreateSingleFrameBuffer() : frame buffer is not complete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (isNew){
        Debug::Log("OpenGL::CreateSingleFrameBuffer() : successful!\n\tRBODepth: "+std::to_string(rboDepth)+
                   "\n\tHDR_FBO: "+std::to_string(hdrFBO) + "\n\tColor buffer: "+std::to_string(colorBuffer));
    }
*/
    return true;
}

void Framework::Graphics::OpenGL::SetDepthTestEnabled(bool value) {
    if (value)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

[[nodiscard]] bool Framework::Graphics::OpenGL::FreeTexture(int32_t* id) const  {
    //glDeleteTextures(1, &ID);
    return true;
}

[[nodiscard]] bool Framework::Graphics::OpenGL::FreeTextures(int32_t *IDs, uint32_t count) const {
    if (count == 0 || !IDs)
        return false;
    glDeleteTextures(count, reinterpret_cast<const GLuint *>(IDs));
    return true;
}

int32_t Framework::Graphics::OpenGL::CalculateVAO(
        std::vector<Vertices::StaticMeshVertex> &vertices,
        size_t count_verts)
{
    if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
        SR_LOG("OpenGL::CalculateVAO() : calculating " + std::to_string(vertices.size()) + " vertices...");
    }

    int32_t VAO = 0;
    uint32_t VBO = 0;

    glGenVertexArrays(1, (GLuint*)&VAO);
    glGenBuffers(1, (GLuint*)&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /*{
        //? Binding vertex array
        ///glBufferData(
        ///        GL_ARRAY_BUFFER,
        ///        count_verts * sizeof(Vertices::Mesh3DVertex),
        ///        &vertices[0],
        ///        GL_STATIC_DRAW
        ///);

        //? Binding attrib vertex coordinates
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,
                              3, // glm::vec3 - has 3 floats
                              GL_FLOAT, GL_FALSE,
                              sizeof(Vertices::Mesh3DVertex), (void*)0);

        //? Binding attrib texture coordinates
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,
                              2, // glm::vec2 - has 2 floats
                              GL_FLOAT, GL_FALSE, sizeof(Vertices::Mesh3DVertex),
                              (void*)offsetof(Vertices::Mesh3DVertex, uv) // Сдвиг байт до соответствующего атрибута
        );

        //? Binding attrib normal coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2,
                              3, // glm::vec3 - has 3 floats
                              GL_FLOAT, GL_FALSE,
                              sizeof(Vertices::Mesh3DVertex),
                              (void*)offsetof(Vertices::Mesh3DVertex, norm) // Сдвиг байт до соответствующего атрибута
        );

        //? Binding attrib tangent coordinates
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3,
                              3, // glm::vec3 - has 3 floats
                              GL_FLOAT, GL_FALSE,
                              sizeof(Vertices::Mesh3DVertex),
                              (void*)offsetof(Vertices::Mesh3DVertex, tang) // Сдвиг байт до соответствующего атрибута
        );

    }

    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);*/

    return VAO;
}

int32_t Framework::Graphics::OpenGL::CalculateVBO(
        void *vertices,
        Framework::Graphics::Vertices::Type type,
        size_t count)
{
    if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
        SR_LOG("OpenGL::CalculateVBO() : calculating " + std::to_string(count) + " vertices...");
    }

    uint32_t _vbo = 0;
    uint32_t _vao = 0;

    int32_t vertexSize = Vertices::GetVertexSize(type);

    glGenVertexArrays(1, (GLuint*)&_vao);
    glGenBuffers(1, (GLuint*)&_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    /// glBufferData(GL_ARRAY_BUFFER, count * vertexSize, vertices, GL_STATIC_DRAW);

    /*switch (type) {
        case Vertices::Type::Mesh3DVertex:
        OpenGLSetVertexAttribPointer(0, 3, Vertices::Mesh3DVertex, offsetof(Vertices::Mesh3DVertex, pos))
            OpenGLSetVertexAttribPointer(1, 2, Vertices::Mesh3DVertex, offsetof(Vertices::Mesh3DVertex, uv))
            OpenGLSetVertexAttribPointer(2, 3, Vertices::Mesh3DVertex, offsetof(Vertices::Mesh3DVertex, norm))
            OpenGLSetVertexAttribPointer(3, 3, Vertices::Mesh3DVertex, offsetof(Vertices::Mesh3DVertex, tang))
            break;
        case Vertices::Type::SkyboxVertex:
        OpenGLSetVertexAttribPointer(0, 3, Vertices::SkyboxVertex, offsetof(Vertices::SkyboxVertex, pos))
            break;
        default:
            Helper::Debug::Error("OpenGL::CalculateVBO() : unknown vertex type!");
            return SR_ID_INVALID;
    }*/

    glBindVertexArray(0);
    glDeleteBuffers(1, &_vbo);

    return _vao; // it's normal
}

int32_t Framework::Graphics::OpenGL::CalculateIBO(
        void *indices,
        uint32_t indxSize,
        size_t count,
        int32_t VBO)
{
    if (VBO <= 0) {
        SR_ERROR("OpenGL::CalculateIBO() : to calculate the IBO, OpenGL needs a VBO (VAO)!");
        return SR_ID_INVALID;
    }

    if (count == 0 || !indices) {
        SR_ERROR("OpenGL::CalculateIBO() : count indices is zero or indices is nullptr!");
        return SR_ID_INVALID;
    }

    GLuint EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VBO); // VAO
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        /// glBufferData(GL_ELEMENT_ARRAY_BUFFER, indxSize, indices, GL_STATIC_DRAW);
    }
    glBindVertexArray(0);

    return EBO;
}

SR_MATH_NS::IVector2 Framework::Graphics::OpenGL::GetScreenSize() const {
    return SR_MATH_NS::IVector2(this->m_vidMode->width, this->m_vidMode->height);
}




