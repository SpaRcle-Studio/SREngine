

# File Compiler.h

[**File List**](files.md) **>** [**Compilation**](dir_f4efc9bee95c06127bdf4e6c5eda8bf7.md) **>** [**Compiler.h**](Compilation_2Compiler_8h.md)

[Go to the documentation of this file](Compilation_2Compiler_8h.md)


```C++
//
// Created by Nikita on 03.07.2021.
//

#ifndef SR_ENGINE_SCRIPTING_COMPILER_H
#define SR_ENGINE_SCRIPTING_COMPILER_H

#include <Scripting/Script.h>
#include <Scripting/Tools/StringUtils.h>
#include <Scripting/Tools/HashUtils.h>

namespace EvoScript {
    typedef std::unordered_map<std::string, std::vector<uint32_t>> ModuleCopies;

    class Compiler : public SR_UTILS_NS::NonCopyable {
    public:
        explicit Compiler(std::string cachePath);
        ~Compiler() override = default;

    public:
        SR_NODISCARD std::string GetCachePath() const { return m_cachePath; }
        SR_NODISCARD std::string GetAPIVersion() const { return m_apiVersion; }

        SR_NODISCARD std::string GetCompilerPath() const { return m_compilerPath; }
        void SetCompilerPath(const std::string& compilerPath) { m_compilerPath = compilerPath; }

        IState* AllocateState(const std::string& path);

        void SetApiVersion(std::string version);
        void SetMultiInstances(bool enabled) { m_multiInstances = enabled; }

        void AddIncludePath(const std::string& path);

        bool Compile(Script* script);

        void SetCompilePDB(bool value) { m_compilePDB = value; }

        bool TryLoad(Script* script);
        bool Load(Script* script);

        bool LoadState(IState* state);

    private:
        bool ClearModulesCache(const std::string& path);
        uint32_t FindFreeID(const std::string& pathToModule);
        bool CheckSourceHash(const std::string& source, const std::string& pathToScript, bool debug);
        bool CheckApiHash(const std::string& pathToScript, bool debug);

    private:
        std::vector<std::string> m_includes;

        bool m_compilePDB = false;
        bool m_multiInstances = true;

        std::string m_apiVersion = "None";
        std::string m_cachePath  = "None";

        std::recursive_mutex m_mutex;
        ModuleCopies m_moduleCopies;

        std::string m_compilerPath = "";
    };
}

#endif //SR_ENGINE_SCRIPTING_COMPILER_H
```


