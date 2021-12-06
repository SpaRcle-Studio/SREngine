//
// Created by Monika on 22.11.2021.
//

#ifndef GAMEENGINE_CMDOPTIONS_H
#define GAMEENGINE_CMDOPTIONS_H

#include <algorithm>
#include <string>

namespace Framework::Helper {
    std::string GetCmdOption(char **begin, char **end, const std::string &option) {
        char **itr = std::find(begin, end, option);
        if (itr != end && ++itr != end) {
            return *itr;
        }
        return std::string();
    }
}

#endif //GAMEENGINE_CMDOPTIONS_H
