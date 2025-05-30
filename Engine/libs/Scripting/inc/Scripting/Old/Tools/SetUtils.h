//
// Created by Nikita on 10.07.2021.
//

#ifndef SR_ENGINE_SCRIPTING_SET_UTILS_H
#define SR_ENGINE_SCRIPTING_SET_UTILS_H

#include <iostream>
#include <set>

namespace EvoScript::Tools {
    template<typename T> std::set<T> Merge(const std::set<T>& s1, const std::set<T>& s2) {
        std::set<T> s3 = s1;
        s3.insert(s2.begin(), s2.end());
        return s3;
    }

    template<typename T> void PrintSet(const std::set<T>& s) {
        for (auto it = s.begin(); it != s.end(); ++it)
            std::cout << *it << ' ';
        std::cout << std::endl;
    }
} // namespace EvoScript::Tools

#endif // SR_ENGINE_SCRIPTING_SET_UTILS_H
