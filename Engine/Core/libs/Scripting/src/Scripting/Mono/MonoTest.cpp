//
// Created by Monika on 15.03.2025.
//

#include <Scripting/Mono/MonoTest.h>

#include <Utils/Resources/ResourceManager.h>

#ifdef SR_ENGINE_MONO_SUPPORT

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

namespace SR_SCRIPTING_NS {
    const std::string csharpCode = R"(
        using System;
        public class Script {
            public static void Run() {
                Console.WriteLine("Hello from in-memory compiled C#!");
            }
        }
    )";

    std::vector<char> CompileScript(MonoDomain* domain) {
        MonoAssembly* assembly = mono_domain_assembly_open(domain, "C:/Work/SREngine/Resources/Engine/Net/mono/4.5/RuntimeCompiler.dll");
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
        MonoArray* result = (MonoArray*)mono_runtime_invoke(method, nullptr, args, &exception);

        if (exception) {
            MonoString* exc_str = mono_object_to_string(exception, nullptr);
            if (exc_str) {
                char* exc_cstr = mono_string_to_utf8(exc_str);
                std::cerr << "Runtime error in Compile: " << exc_cstr << std::endl;
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


    void RunMonoTest() {
        std::string netPath = "C:/Work/SREngine/Resources/Engine/Net";
        mono_set_dirs(netPath.c_str(), "");
        MonoDomain* domain = mono_jit_init("MonoDomain");

        auto&& data = CompileScript(domain);
        if (data.empty()) {
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