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
        //std::vector<std::function<void(lua_State* L)>>          m_classes                   = std::vector<std::function<void(lua_State* L)>>();
        std::map<std::string, std::vector<std::function<void(lua_State* L)>>>   m_libs                      = std::map<std::string, std::vector<std::function<void(lua_State* L)>>>();
        std::mutex                                                              m_mutex_load                = std::mutex();
        std::mutex                                                              m_mutex_register            = std::mutex();
        std::vector<Script*>                                                    m_scripts                   = std::vector<Script*>();
    public:
        std::vector<std::function<void(lua_State* L)>> GetClasses(std::string libName) noexcept;
    public:
        void RegisterScriptClass(std::string libName, std::function<void(lua_State *L)> fun);
        Script* Load(std::string name, bool fromEngine = false);
    public:
        void AwakeAll();
        void FixedUpdateAll();
        void UpdateAll();
    };
}

#endif //GAMEENGINE_COMPILER_H
