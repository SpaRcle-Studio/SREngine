

# File StringUtils.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**Tools**](dir_34b1643912c4d8f0022f3f30c24098db.md) **>** [**StringUtils.h**](Scripting_2inc_2Scripting_2Old_2Tools_2StringUtils_8h.md)

[Go to the documentation of this file](Scripting_2inc_2Scripting_2Old_2Tools_2StringUtils_8h.md)


```C++
//
// Created by Nikita on 08.07.2021.
//

#ifndef EVOSCRIPT_STRINGUTILS_H
#define EVOSCRIPT_STRINGUTILS_H

#include <string>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <sys/stat.h>
#include <fstream>
#include <list>
#include <vector>
#include <stdarg.h>

namespace EvoScript::Tools {
    static std::vector<std::string> RemoveFirstSpaces(std::vector<std::string> strings) {
        for (auto& str : strings)
            if (str[0] == ' ')
                str.erase(0, 1);
        return strings;
    }

    inline static std::string Read(const std::string& str, uint32_t count) {
        return str.substr(0, count);
    }

    inline static std::string ReadTo(const std::string& str, char c) {
        std::string s = str.substr(0, str.find(c));
        return s;
    }

    inline static std::string ReadToLast(const std::string& str, char c) {
        std::string s = str.substr(0, str.rfind(c));
        return s;
    }

    static std::string ToUpper(std::string str) {
        for (char& i : str)
            i = (char)toupper(i);
        return str;
    }

    static std::string TabString(std::string str) {
        str = "\t" + str;

        size_t pos = 0;

        ret:
        size_t start_pos = str.find('\n', pos);
        if(start_pos == std::string::npos)
            return str;
        pos += start_pos - pos;
        str.insert(str.begin() + pos + 1, '\t');
        pos += 1;
        goto ret;
    }

    static std::string Replace(std::string str, const std::string& from, const std::string& to) {
    ret:
        size_t start_pos = str.find(from);
        if(start_pos == std::string::npos)
            return str;
        str.replace(start_pos, from.length(), to);
        goto ret;
    }

    static std::string GetDate() {
        std::time_t result = std::time(nullptr);
        std::string str = std::ctime(&result);
        return str.substr(0, str.size() - 1);
    }

    static std::string FixPath(const std::string& path) {
        return Tools::Replace(Tools::Replace(path, "\\", "/"), "//", "/");
    }

    static std::string DeleteSymbolsInStr(std::string str, const std::string& symbols) {
        for (const auto& symbol : symbols)
            str.erase(remove(str.begin(),str.end(), symbol),str.end());
        return str;
    }

    static std::vector<std::string> Split(const std::string& s) {
        std::vector<std::string> result;
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, ','))
            result.push_back(token);
        return result;
    }

    static std::string BackReadTo(const std::string& str, const char c) {
        std::string result;

        for (int32_t i = (str.size() - 1); i >= 0; i--) {
            if (str[i] != c)
                result += str[i];
            else
                break;
        }

        std::reverse(result.begin(), result.end());

        return result;
    }

    static std::vector<std::string> GetArgs(const std::string& str) {
        if (str.size() <= 2) {
            return {};
        }

        auto left = str.find('(');
        auto right = str.find(')');

        auto args = str.substr(left, right);
        args = EvoScript::Tools::DeleteSymbolsInStr(args, "()");

        std::vector<std::string> strArgs = EvoScript::Tools::RemoveFirstSpaces(EvoScript::Tools::Split(args));
        return strArgs;
    }
}

#endif //EVOSCRIPT_STRINGUTILS_H
```


