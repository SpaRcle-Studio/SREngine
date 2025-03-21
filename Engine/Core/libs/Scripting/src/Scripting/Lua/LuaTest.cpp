//
// Created by Monika on 21.03.2025.
//

#include <Scripting/Lua/LuaTest.h>

#include <sol/sol.hpp>

namespace SR_SCRIPTING_NS {
    void RunLuaTest() {
        sol::state lua;

        // Открываем стандартные библиотеки Lua (например, string, math)
        lua.open_libraries(sol::lib::base, sol::lib::math);

        // Загружаем и выполняем Lua-скрипт из файла
        try {
            lua.script_file("C:\\Work\\SREngine\\Resources\\Tests\\script.lua");

            // Получаем значение переменной из Lua
            int sum = lua["sum"];
            std::cout << "Sum from Lua: " << sum << std::endl;
        } catch (const sol::error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
