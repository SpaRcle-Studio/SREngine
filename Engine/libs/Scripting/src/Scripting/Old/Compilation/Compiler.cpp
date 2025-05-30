//
// Created by Nikita on 03.07.2021.
//

#include <Scripting/Compilation/Compiler.h>
#include <Scripting/Tools/Finder.h>

namespace EvoScript {
    Compiler::Compiler(std::string cachePath) : m_cachePath(std::move(cachePath)) {
        ClearModulesCache(m_cachePath + "/Modules");
    }

    bool Compiler::ClearModulesCache(const std::string& path) {
        if (!Tools::ESFileSystem::GetAllFoldersInDir) {
            SR_ERROR("Compiler::ClearModulesCache() : \"GetAllFoldersInDir\" "
                     "is nullptr!");
            return false;
        }

        const auto dirs = Tools::ESFileSystem::GetAllFoldersInDir(path);

        /// предполагается, что dll файлы лежат в конкретной директории, и там
        /// кроме них нет ничего больше
        if (!dirs.empty()) {
            for (const auto& dir : dirs) {
                if (!ClearModulesCache(dir))
                    return false;

                if (Tools::IsDirectoryEmpty(dir)) {
                    Tools::ESFileSystem::Delete(dir);
                }
            }

            return true;
        }

        for (const auto& file : Tools::GetAllFilesInDirWithExt(path, IState::Extension)) {
            /// проверка, на случай, если попали в иную директорию, чтобы не
            /// удалить пол системы
            if (file.find("Module-") == std::string::npos) {
                ES_WARN(
                    "Compiler::ClearModulesCache() : a suspicious file has "
                    "been detected! I can't perform automatic cache cleanup! "
                    "\n\tFile: " +
                    file
                );
                return false;
            }
            Tools::ESFileSystem::Delete(file);
        }

        return true;
    }

    bool Compiler::CheckApiHash(const std::string& pathToScript, bool debug) {
        const std::string fullPath = pathToScript + "/api.hash";

        auto currHash = std::pair(debug, std::vector<std::string>{m_apiVersion});

        if (Tools::ESFileSystem::IsExists(fullPath)) {
            auto loadHash = Tools::LoadHashInfo(fullPath);
            if (Tools::HashEquals(loadHash, currHash)) {
                return true;
            } else {
                Tools::SaveHashInfo(fullPath, currHash);
            }
        } else {
            Tools::SaveHashInfo(fullPath, currHash);
        }

        return false;
    }

    bool Compiler::CheckSourceHash(const std::string& source, const std::string& pathToScript, bool debug) {
        const std::string fullPath = pathToScript + "/source.hash";

        auto currHash =
            std::pair(debug, std::vector{Tools::GetFileHash(source + ".cpp"), Tools::GetFileHash(source + ".h")});

        if (Tools::ESFileSystem::IsExists(fullPath)) {
            auto loadHash = Tools::LoadHashInfo(fullPath);

            if (Tools::HashEquals(loadHash, currHash)) {
                return true;
            } else {
                Tools::SaveHashInfo(fullPath, currHash);
            }
        } else {
            Tools::SaveHashInfo(fullPath, currHash);
        }

        return false;
    }

    bool Compiler::Compile(Script* script) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (m_apiVersion == "None" || m_apiVersion.empty()) {
            ES_ERROR("Compiler::Compile() : api hash is not set!");
            return false;
        }

        bool success = false;

        {
            const auto path = m_cachePath + "/Scripts/" + Tools::FixPath(script->GetName());
            const auto source = Tools::FixPath(script->GetPath());

            const auto name = EvoScript::Tools::BackReadTo(script->GetName(), '/');
            const auto module = path + "/Module" + IState::Extension;

            const bool isDebug = script->IsDebug();

            Tools::CreatePath(path);

            /// чтобы все хеш суммы сразу создались, нужно их проверить
            uint32_t hashCompare = 0;
            hashCompare += static_cast<uint32_t>(CheckSourceHash(source, path, isDebug));
            hashCompare += static_cast<uint32_t>(CheckApiHash(path, isDebug));

            if (hashCompare == 2) {
                if (TryLoad(script)) {
                    return true;
                }
            } else if (Tools::ESFileSystem::IsExists(module)) {
                if (!Tools::ESFileSystem::Delete(module)) {
                    ES_WARN(
                        "Compiler::Compile() : failed to delete "
                        "module!\n\tPath: " +
                        module
                    );
                }
            }

            /// auto&& build  = path + "/Build/" +
            /// std::to_string(Tools::RandomUInt32()) + "/";
            auto&& build = path + "/Build/";

            /// Чистим папку сборки, чтобы не возникло конфликтов
            if (Tools::ESFileSystem::IsExists(build) && !Tools::ESFileSystem::Delete(build)) {
                ES_ERROR("Compiler::Compile() : failed to delete build folder!");
            }
            Tools::CreatePath(build);

            ES_LOG(
                "Compiler::Compile() : compile \"" + script->GetName() + "\" " +
                std::string(script->IsDebug() ? "[Debug]" : "[Release]") + " script..."
            );

#ifdef ES_MSVC
            std::string vars;
            if (m_compilerPath.empty()) {
                m_compilerPath = Tools::FindMSVCCompiler();
                vars = Tools::FindMSVCVars64();
            } else {
                vars = Tools::FindMSVCVars64(m_compilerPath);
            }

            if (m_compilerPath.empty()) {
                ES_ERROR("Compiler::Compile() : MSVC compiler not found!");
                return false;
            }

            if (vars.empty()) {
                ES_ERROR("Compiler::Compile() : MSVC vars64 not found!");
                return false;
            }

            std::string includes;
            for (auto&& include : m_includes) {
                includes.append("/I\"").append(include).append("\" ");
            }

            auto&& command = ES_FORMAT(
                "cd \"%s\" && call \"%s\" && \"%s\" %s %s /std:c++17 /nologo "
                "/O1 %s /Os /GF /GS- \"%s.cpp\"",
                build.c_str(), vars.c_str(), m_compilerPath.c_str(), includes.c_str(),
                script->IsDebug() ? "/LDd" : "/LD", m_compilePDB ? " /ZI " : " ", source.c_str()
            );

            system(command.c_str());

            if (auto files = Tools::GetAllFilesInDirWithExt(build, IState::Extension); files.size() == 1) {
                Tools::ESFileSystem::Copy(files[0], module);
            } else {
                SR_ERROR("Compiler::Compile() : file not found! \n\tPath: " + module);
            }
#elif defined(ES_GCC)
            // TODO: What should we use here? Search by path or just use 'g++'
            // from PATH in system() call?
            if (m_compilerPath.empty()) {
                m_compilerPath = "/usr/bin/g++";
            }

            std::string includes;
            for (auto&& include : m_includes) {
                includes.append("-I ").append(include).append(" ");
            }

            /*auto&& command = ES_FORMAT("cd \"%s\" && call \"%s\" && \"%s\" %s
            %s /std:c++17 /nologo /O1 %s /Os /GF /GS- \"%s.cpp\"",
                build.c_str(),
                vars.c_str(),
                compiler.c_str(),
                includes.c_str(),
                script->IsDebug() ? "/LDd" : "/LD",
                m_compilePDB ? " /ZI " : " ",
                source.c_str()
            );
            */

            std::string debug = script->IsDebug() ? "-g " : "-O3 ";
            auto&& command = "cd " + build + " && " + m_compilerPath + " -shared -fPIC " + includes +
                             " -std=c++17 -ldl " + debug + "-rdynamic " + source + ".cpp -o " + module;

            system(command.c_str());
#else
            SR_ERROR("Compiler::Compile() : unsupported compiler! Please, "
                     "install MSVC on Windows or GCC on Linux!");
#endif

            if (success = Tools::ESFileSystem::IsExists(module); success) {
                SR_LOG("Compiler::Compile() : successfully compiled the \"" + script->GetName() + "\" script!");
            } else {
                SR_ERROR("Compiler::Compile() : failed to compile the \"" + script->GetName() + "\" script!");
            }
        }

        return success;
    }

    IState* Compiler::AllocateState(const std::string& name) {
        if (!m_multiInstances) {
            const std::string module = m_cachePath + "/Scripts/" + name + "/Module" + IState::Extension;
            return IState::Allocate(module);
        }

    ret:
        if (auto find = m_moduleCopies.find(name); find == m_moduleCopies.end()) {
            m_moduleCopies[name] = std::vector<uint32_t>();
            goto ret;
        } else {
            auto&& id = FindFreeID(name);

            const std::string module = m_cachePath + "/Scripts/" + name + "/Module" + IState::Extension;
            const std::string copy =
                m_cachePath + "/Modules/" + name + "/Module-" + std::to_string(id) + IState::Extension;

            if (Tools::ESFileSystem::IsExists(copy)) {
                goto ret;
            }

            Tools::CreatePath(m_cachePath + "/Modules/" + name);
            if (!Tools::ESFileSystem::Copy(module, copy)) {
                ES_ERROR(
                    "Compiler::AllocateState() : failed to copy file! "
                    "\n\tSource:" +
                    module + "\n\tDestination: " + copy
                );
                return nullptr;
            }

            find->second.emplace_back(id);

            return IState::Allocate(copy);
        }
    }

    uint32_t Compiler::FindFreeID(const std::string& pathToModule) {
        if (auto find = m_moduleCopies.find(pathToModule); find == m_moduleCopies.end()) {
            SR_ERROR("Compiler::FindFreeID() : module not found! Something "
                     "went wrong...");
            return UINT32_MAX;
        } else {
        ret:
            uint32_t id = SR_UTILS_NS::Random::Instance().UInt32();

            auto [key, value] = *find;

            for (const auto& copy : value)
                if (id == copy)
                    goto ret;

            return id;
        }
    }

    void Compiler::SetApiVersion(std::string version) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        m_apiVersion = std::move(version);
    }

    bool Compiler::Load(Script* script) {
        if (!TryLoad(script)) {
            ES_ERROR("Compiler::Load() : failed to load the \"" + script->GetName() + "\" script!");
            return false;
        }

        return true;
    }

    bool Compiler::TryLoad(Script* script) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        const auto path = m_cachePath + "/Scripts/" + Tools::FixPath(script->GetName());
        const auto module = path + "/Module" + IState::Extension;

        if (Tools::ESFileSystem::IsExists(module)) {
            /// ES_LOG("Compiler::Load() : successfully loaded the \"" +
            /// script->GetName() + "\" script!");
            SR_NOOP;
            return true;
        }

        return false;
    }

    bool Compiler::LoadState(IState* state) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        return state->Load();
    }

    void Compiler::AddIncludePath(const std::string& path) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        m_includes.emplace_back(path);
    }
} // namespace EvoScript