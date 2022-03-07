//
// Created by Monika on 07.03.2022.
//

#ifndef SRENGINE_METHODS_H
#define SRENGINE_METHODS_H

#include <macros.h>

namespace SR_UTILS_NS {
    namespace SFINAE {
        template<typename Class, typename Enabled = void>
        struct HasMethodStruct {
            static constexpr bool value = false;
        };

        template<typename Class>
        struct HasMethodStruct<Class, std::enable_if_t<std::is_member_function_pointer_v<decltype(&Class::Name)>>> {
            static constexpr bool value = std::is_member_function_pointer_v<decltype(&Class::Name)>;
        };
    }
}

#endif //SRENGINE_METHODS_H
