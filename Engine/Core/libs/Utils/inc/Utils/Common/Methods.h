//
// Created by Monika on 07.03.2022.
//

#ifndef SR_ENGINE_METHODS_H
#define SR_ENGINE_METHODS_H

#include <Utils/macros.h>

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

#endif //SR_ENGINE_METHODS_H
