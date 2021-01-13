//
// Created by Nikita on 29.12.2020.
//

#ifndef GAMEENGINE_COMPILER_H
#define GAMEENGINE_COMPILER_H

#include <Script.h>
#include <vector>
#include <string>
#include <mutex>
#include <functional>

namespace Framework::Scripting {
    class Compiler {
    private:
        ~Compiler() = default;
    private:
        std::map<std::string, std::vector<std::function<void(lua_State* L)>>>   m_libs                           = std::map<std::string, std::vector<std::function<void(lua_State* L)>>>();
        std::mutex                                                              m_mutex_load                     = std::mutex();
        std::mutex                                                              m_mutex_destroy                  = std::mutex();
        std::mutex                                                              m_mutex_register                 = std::mutex();
        std::mutex                                                              m_mutex_delayed                  = std::mutex();

        size_t                                                                  m_countScripts                   = 0;
        std::vector<Script*>                                                    m_scripts                        = std::vector<Script*>();

        std::vector<Script*>                                                    m_scriptsToDestroy               = std::vector<Script*>();
        size_t                                                                  m_countScriptsToDestroy          = 0;

        std::vector<Script*>                                                    m_delayedLoadingScripts          = std::vector<Script*>();
        size_t                                                                  m_countDelayedLoadingScripts     = 0;
    private:
        bool Remove(Script* script);
    public:
        std::vector<std::function<void(lua_State* L)>> GetClasses(const std::string& libName) noexcept;
    private:
        static bool Compile(Script* script);
    public:
        void RegisterScriptClass(const std::string& libName, std::function<void(lua_State *L)> fun);
        Script* Load(const std::string& name, bool fromEngine = false);
        Script* DelayedLoad(const std::string& name, bool fromEngine = false);
    public:
        void PoolEvents();

        void DestroyScript(Script* script);

        void AwakeAll();
        void FixedUpdateAll();
        void UpdateAll();

        void CloseAll();
        void DestroyAll();

        bool Free();
    };
}

#endif //GAMEENGINE_COMPILER_H
