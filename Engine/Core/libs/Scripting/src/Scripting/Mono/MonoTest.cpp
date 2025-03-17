//
// Created by Monika on 15.03.2025.
//

#include <Scripting/Mono/MonoTest.h>

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

    void RunMonoTest() {
        // Инициализация Mono
        //mono_set_dirs("/usr/lib/mono", "/etc/mono");
        mono_set_dirs("C:/Work/SREngine/cmake-build-debug/Mono/lib", "C:/Work/SREngine/cmake-build-debug/Mono/etc");
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
