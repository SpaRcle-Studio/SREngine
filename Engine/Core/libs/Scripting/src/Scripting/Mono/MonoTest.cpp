//
// Created by Monika on 15.03.2025.
//

#include <Scripting/Mono/MonoTest.h>

#include <Utils/Resources/ResourceManager.h>

#ifdef SR_ENGINE_MONO_SUPPORT

#include <mono/jit/jit.h>
#include <mono/utils/mono-logger.h>
#include <mono/utils/mono-publib.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/object.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/debug-helpers.h>

#ifdef SR_ANDROID
    #include <jni.h>
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
    #include <android/log.h>

    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <errno.h>
    #include <signal.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <execinfo.h>

    #define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SREngine", __VA_ARGS__))
    #define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "SREngine", __VA_ARGS__))
    #define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "SREngine", __VA_ARGS__))

void signalHandler(int signum, siginfo_t* info, void* context) {
    LOGE("Caught signal %d (%s)\n", signum, strsignal(signum));
    LOGE("Fault address: %p\n", info->si_addr);

    switch (info->si_code) {
        case SEGV_MAPERR:
            LOGE("Cause: Address not mapped to object\n");
            break;
        case SEGV_ACCERR:
            LOGE("Cause: Invalid permissions for mapped object\n");
            break;
        default:
            LOGE("Cause: Unknown (%d)\n", info->si_code);
            break;
    }

    exit(1);
}

void setupSignalHandler() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signalHandler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, NULL);
}
#endif

namespace SR_SCRIPTING_NS {
    const std::string csharpCode = R"(
        using System;
        public class Script {
            public static void Run() {
                Console.WriteLine("Hello from in-memory compiled C#!");
            }
        }
    )";

    void mono_log_handler(const char* log_domain, const char* log_level, const char* message, mono_bool fatal, void* user_data) {
#ifdef SR_ANDROID
        LOGI("%s: %s", log_level, message);
        if (fatal) {
            LOGE("Fatal error intercepted! Preventing crash...");
        }
#else
        std::cout << "[Mono] " << log_level << ": " << message << std::endl;
        if (fatal) {
            std::cerr << "[Mono] Fatal error intercepted! Preventing crash..." << std::endl;
        }
#endif
    }

    std::vector<char> CompileScript(MonoDomain* domain, const std::string& scriptPath) {
        MonoAssembly* assembly = mono_domain_assembly_open(domain, scriptPath.c_str());
        if (!assembly) {
            std::cerr << "Ошибка загрузки RuntimeCompiler.dll!" << std::endl;
            return {};
        }

        MonoImage* image = mono_assembly_get_image(assembly);
        MonoClass* klass = mono_class_from_name(image, "", "RuntimeCompiler");
        if (!klass) {
            std::cerr << "Не найден класс Compiler!" << std::endl;
            return {};
        }

        MonoMethod* method = mono_class_get_method_from_name(klass, "Compile", 1);
        if (!method) {
            std::cerr << "Не найден метод Compile!" << std::endl;
            return {};
        }

        MonoString* monoCode = mono_string_new(domain, csharpCode.c_str());
        void* args[] = { monoCode };

        MonoObject* exception = nullptr;

        mono_set_crash_chaining(TRUE);
        MonoArray* result = (MonoArray*)mono_runtime_invoke(method, nullptr, args, &exception);

        if (exception) {
            MonoString* exc_str = mono_object_to_string(exception, nullptr);
            if (exc_str) {
                char* exc_cstr = mono_string_to_utf8(exc_str);
#ifdef SR_ANDROID
                LOGE("Runtime error in Compile: %s", exc_cstr);
#else
                std::cerr << "Runtime error in Compile: " << exc_cstr << std::endl;
#endif
                mono_free(exc_cstr);
            } else {
                std::cerr << "Runtime error in Compile (exception object could not be converted to string)" << std::endl;
            }
            return {};
        }

        int length = mono_array_length(result);
        std::vector<char> assemblyData(length);
        for (int i = 0; i < length; i++) {
            assemblyData[i] = mono_array_get(result, char, i);
        }

        return assemblyData;
    }

    void RunCompiledScript(MonoDomain* domain, const std::vector<char>& assemblyData) {
        if (assemblyData.empty()) {
            std::cerr << "Ошибка: пустой массив данных сборки!" << std::endl;
            return;
        }

        MonoImageOpenStatus status;
        MonoImage* image = mono_image_open_from_data_with_name(
                const_cast<char*>(reinterpret_cast<const char*>(assemblyData.data())),
                static_cast<uint32_t>(assemblyData.size()),
                true, &status, false, "InMemoryAssembly"
        );

        if (!image || status != MONO_IMAGE_OK) {
            std::cerr << "Ошибка загрузки сборки в Mono! Код ошибки: " << status << std::endl;
            return;
        }

        MonoAssembly* assembly = mono_assembly_load_from_full(image, "InMemoryAssembly", &status, false);
        if (!assembly) {
            std::cerr << "Ошибка: не удалось загрузить сборку в Mono!" << std::endl;
            return;
        }

        MonoClass* klass = mono_class_from_name(mono_assembly_get_image(assembly), "", "Script");
        if (!klass) {
            std::cerr << "Ошибка: класс Script не найден!" << std::endl;
            return;
        }

        MonoMethod* method = mono_class_get_method_from_name(klass, "Run", 0);
        if (!method) {
            std::cerr << "Ошибка: метод Run не найден!" << std::endl;
            return;
        }

        mono_runtime_invoke(method, nullptr, nullptr, nullptr);
    }

#ifdef SR_ANDROID
    void ensure_directory_exists(const char* path) {
        std::string dir_path = path;
        size_t pos = 0;

        while ((pos = dir_path.find('/', pos + 1)) != std::string::npos) {
            std::string subdir = dir_path.substr(0, pos);
            mkdir(subdir.c_str(), 0755); // Игнорируем ошибку, если каталог уже существует
        }
    }

    void extract_asset(AAssetManager* assetManager, const char* asset_path, const char* output_path) {
        LOGI("Extracting asset: \n\t%s to \n\t%s", asset_path, output_path);

        AAsset* asset = AAssetManager_open(assetManager, asset_path, AASSET_MODE_STREAMING);
        if (!asset) {
            LOGE("Failed to open asset: %s", asset_path);
            return;
        }

        ensure_directory_exists(output_path);
        int fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            LOGE("Failed to open output file: %s, error: %s (%d)", output_path, strerror(errno), errno);

            AAsset_close(asset);
            return;
        }

        char buffer[4096];
        int bytesRead;
        int totalBytes = 0;
        while ((bytesRead = AAsset_read(asset, buffer, sizeof(buffer))) > 0) {
            write(fd, buffer, bytesRead);
            totalBytes += bytesRead;
        }

        close(fd);
        AAsset_close(asset);

        LOGI("Asset extracted successfully. Total bytes: %d", totalBytes);
    }

    void extract_directory(AAssetManager* assetManager, const char* source_dir, const char* dest_dir) {
        LOGI("Extracting directory: %s to %s", source_dir, dest_dir);

        // Создаем целевую папку, если её нет
        mkdir(dest_dir, 0755);

        // Открываем папку в AAssetManager
        AAssetDir* assetDir = AAssetManager_openDir(assetManager, source_dir);
        if (!assetDir) {
            LOGE("Failed to open asset directory: %s", source_dir);
            return;
        }

        const char* file_name;
        while ((file_name = AAssetDir_getNextFileName(assetDir)) != nullptr) {
            // Формируем полный путь к файлу в assets
            std::string asset_path = std::string(source_dir) + "/" + file_name;
            std::string output_path = std::string(dest_dir) + "/" + file_name;

            // Вызываем extract_asset для копирования файла
            extract_asset(assetManager, asset_path.c_str(), output_path.c_str());
        }

        AAssetDir_close(assetDir);
        LOGI("Directory extracted successfully: %s", source_dir);
    }

    /*void RunMonoTest(AAssetManager* pAssetManager) {
        LOGI("Init mono log handler...");

        mono_trace_set_log_handler(mono_log_handler, NULL);

        LOGI("Creating Mono directories...");

        const char* mono_lib_dir = "/data/data/com.monika.sparcle/files/mono/lib";

        setenv("MONO_PATH", mono_lib_dir, 1);
        setenv("MONO_LOG_LEVEL", "debug", 1);
        setenv("MONO_LOG_MASK", "dll", 1);

        mkdir("/data/data/com.monika.sparcle/files/mono", 0755);
        mkdir("/data/data/com.monika.sparcle/files/mono/lib", 0755);
        mkdir("/data/data/com.monika.sparcle/files/mono/lib/mono", 0755);
        mkdir("/data/data/com.monika.sparcle/files/mono/lib/mono/4.5", 0755);

        LOGI("Extracting Mono assets...");

        //extract_directory(pAssetManager, "Engine/Net/android-x64/net8.0", "/data/data/com.monika.sparcle/files/mono/lib");
        extract_directory(pAssetManager, "Engine/Net/mono/4.5", "/data/data/com.monika.sparcle/files/mono/lib");
        //extract_asset(pAssetManager, "Engine/Net/android-x64/net8.0/System.Private.CoreLib.dll", "/data/data/com.monika.sparcle/files/mono/lib/System.Private.CoreLib.dll");
        //extract_asset(pAssetManager, "Engine/Net/android-arm64/net8.0/mscorlib.dll", "/data/data/com.monika.sparcle/files/mono/lib/mscorlib.dll");
        //extract_asset(pAssetManager, "Engine/Net/mono/4.5/mscorlib.dll", "/data/data/com.monika.sparcle/files/mono/lib/mono/4.5/mscorlib.dll");
        mono_set_dirs(mono_lib_dir, mono_lib_dir);
        //mono_set_assemblies_path (mono_lib_dir);

        LOGI("Initializing Mono...");

        MonoDomain* domain = mono_jit_init("MonoDomain");
        //MonoDomain* domain = mono_jit_init_version_for_test_only ("TEST RUNNER", "mobile");
        if (!domain) {
            LOGE("Failed to initialize Mono domain.");
            return;
        }
        LOGI("Mono initialized.");
        return;

        const char* path = "Engine/Net/mono/4.5/RuntimeCompiler.dll";
        AAsset* asset = AAssetManager_open(pAssetManager, path, AASSET_MODE_BUFFER);
        if (!asset) {
            LOGE("Failed to open asset: %s", path);
            return;
        }

        off_t assetSize = AAsset_getLength(asset);
        char* buffer = new char[assetSize];
        AAsset_read(asset, buffer, assetSize);
        AAsset_close(asset);

        // Загружаем assembly напрямую из памяти
        LOGI("Loading assembly...");

        MonoImageOpenStatus status;
        MonoImage* image = mono_image_open_from_data_with_name(buffer, assetSize, true, &status, false, path);
        if (status != MONO_IMAGE_OK) {
            LOGE("Failed to load assembly image.");
            delete[] buffer;
            return;
        }

        MonoAssembly* assembly = mono_assembly_load_from_full(image, path, &status, false);
        delete[] buffer;

        if (!assembly) {
            LOGE("Failed to load assembly.");
            return;
        }

        LOGI("Assembly loaded successfully.");
    }*/
#endif

#ifdef SR_ANDROID
    void RunMonoTest(AAssetManager* pAssetManager) {
#else
    void RunMonoTest() {
#endif
        setupSignalHandler();

        SR_PLATFORM_NS::SetEnvironmentVar("DOTNET_SYSTEM_GLOBALIZATION_INVARIANT", "1");
        SR_PLATFORM_NS::SetEnvironmentVar("ROSLYN_HASH_ALGORITHM", "SHA1");

#ifdef SR_ANDROID
        LOGI("Extracting Mono assets...");

        std::string netPath = "/data/data/com.monika.sparcle/files/Engine/Net/10.0-android";
        std::string scriptPath = "/data/data/com.monika.sparcle/files/Engine/Net/Scripts/RuntimeCompiler.dll";

        mkdir("/data/data/com.monika.sparcle/files/Net", 0755);
        mkdir("/data/data/com.monika.sparcle/files/Net/10.0-android", 0755);
        mkdir("/data/data/com.monika.sparcle/files/Net/Scripts", 0755);
        mkdir("/data/data/com.monika.sparcle/files/libs", 0755);

        extract_directory(pAssetManager, "Engine/Net/10.0-android", "/data/data/com.monika.sparcle/files/Engine/Net/10.0-android-arm64");

    #ifdef SR_ENGINE_ANDROID_ABI_ARM64
    #else
        //extract_directory(pAssetManager, "Engine/Net/10.0-android", "/data/data/com.monika.sparcle/files/Engine/Net/10.0-android-x64");
    #endif

        extract_directory(pAssetManager, "Engine/Net/Scripts", "/data/data/com.monika.sparcle/files/Engine/Net/Scripts");
        extract_directory(pAssetManager, "Engine/Net/android-x64", "/data/data/com.monika.sparcle/files/libs");
#else
        std::string netPath = "C:/Work/SREngine/Resources/Engine/Net/10.0-windows";
        std::string scriptPath = "C:/Work/SREngine/Resources/Engine/Net/Scripts/RuntimeCompiler.dll";
#endif

        mono_set_crash_chaining(TRUE);
        mono_trace_set_log_handler(mono_log_handler, NULL);
        mono_trace_set_level_string("debug");
        mono_trace_set_mask_string("all");

        const char* version = mono_get_runtime_build_info();
        printf("Mono version: %s\n", version);

        mono_set_dirs(netPath.c_str(), "");
        MonoDomain* domain = mono_jit_init("MonoDomain");

        auto&& data = CompileScript(domain, scriptPath);
        if (data.empty()) { // //
            std::cerr << "Ошибка компиляции скрипта!" << std::endl;
            return;
        }

        RunCompiledScript(domain, data);
    }

    void RunMonoTest2() {
        // Инициализация Mono
        //mono_set_dirs("/usr/lib/mono", "/etc/mono");

        std::string netPath = "C:/Work/SREngine/Resources/Engine/Net";
        //auto&& netPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Net");

        mono_set_dirs(netPath.c_str(), ""); ///C:/Work/SREngine/cmake-build-debug/Mono/etc"
        MonoDomain* domain = mono_jit_init("MonoDomain");

        // Загружаем сборку .NET Core, чтобы вызвать компилятор
        //MonoAssembly* assembly = mono_domain_assembly_open(domain, "System.Reflection.dll");
        MonoAssembly* assembly = mono_domain_assembly_open(domain, "Mono.CSharp.dll");
        if (!assembly) {
            std::cerr << "Не удалось загрузить System.Reflection!" << std::endl;
            return;
        }

        MonoImage* image = mono_assembly_get_image(assembly);
        if (!image) {
            std::cerr << "Ошибка: не удалось получить MonoImage!" << std::endl;
            return;
        }
        // Получаем класс CompilerContext
        MonoClass* compilerContextClass = mono_class_from_name(image, "Mono.CSharp", "CompilerContext");
        if (!compilerContextClass) {
            std::cerr << "Ошибка: класс CompilerContext не найден!" << std::endl;
            return;
        }

        // Получаем конструктор CompilerContext (он требует Report и Settings)
        MonoMethod* compilerContextCtor = mono_class_get_method_from_name(compilerContextClass, ".ctor", 2);
        if (!compilerContextCtor) {
            std::cerr << "Ошибка: конструктор CompilerContext не найден!" << std::endl;
            return;
        }

        // Получаем класс CompilerSettings
        MonoClass* compilerSettingsClass = mono_class_from_name(image, "Mono.CSharp", "CompilerSettings");
        if (!compilerSettingsClass) {
            std::cerr << "Ошибка: класс CompilerSettings не найден!" << std::endl;
            return;
        }

        // Создаём объект CompilerSettings
        MonoObject* compilerSettings = mono_object_new(domain, compilerSettingsClass);
        mono_runtime_object_init(compilerSettings);

        // Получаем класс Report
        MonoClass* reportClass = mono_class_from_name(image, "Mono.CSharp", "Report");
        if (!reportClass) {
            std::cerr << "Ошибка: класс Report не найден!" << std::endl;
            return;
        }

        // Создаём объект Report
        MonoObject* report = mono_object_new(domain, reportClass);
        mono_runtime_object_init(report);

        // Создаём CompilerContext
        void* ctorArgs[] = { compilerSettings, report };
        MonoObject* compilerContext = mono_object_new(domain, compilerContextClass);
        mono_runtime_invoke(compilerContextCtor, compilerContext, ctorArgs, nullptr);

        // Получаем класс Evaluator
        MonoClass* evaluatorClass = mono_class_from_name(image, "Mono.CSharp", "Evaluator");
        if (!evaluatorClass) {
            std::cerr << "Ошибка: класс Evaluator не найден!" << std::endl;
            return;
        }

        // Получаем конструктор Evaluator
        MonoMethod* evaluatorCtor = mono_class_get_method_from_name(evaluatorClass, ".ctor", 1);
        if (!evaluatorCtor) {
            std::cerr << "Ошибка: конструктор Evaluator не найден!" << std::endl;
            return;
        }

        // Создаём Evaluator
        void* evalArgs[] = { compilerContext };
        MonoObject* evaluator = mono_object_new(domain, evaluatorClass);
        mono_runtime_invoke(evaluatorCtor, evaluator, evalArgs, nullptr);

        // Получаем метод Run
        MonoMethod* runMethod = mono_class_get_method_from_name(evaluatorClass, "Run", 1);
        if (!runMethod) {
            std::cerr << "Ошибка: метод Run не найден!" << std::endl;
            return;
        }

        // Компилируемый код
        const char* script = "Console.WriteLine(\"Hello from Mono!\");";

        // Запускаем выполнение кода
        void* args[] = { mono_string_new(domain, script) };
        MonoObject* exception = nullptr;
        mono_runtime_invoke(runMethod, evaluator, args, &exception);

        if (exception) {
            std::cerr << "Ошибка при выполнении скрипта!" << std::endl;
        }

        // Завершаем работу Mono
        mono_jit_cleanup(domain);
    }
}

#endif