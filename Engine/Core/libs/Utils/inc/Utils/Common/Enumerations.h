//
// Created by Monika on 01.10.2021.
//

#ifndef GAMEENGINE_ENUMERATIONS_H
#define GAMEENGINE_ENUMERATIONS_H

#include <Utils/Common/EnumReflector.h>

/// -----------------------------------------[Базовые с настройкой типа]------------------------------------------------

/// Declare an enumeration inside a class
#define SR_ENUM_T(enumName, type, ...) \
      SR_ENUM_DETAIL_MAKE(enum, class, enumName, type, __VA_ARGS__ )

/// Declare an enumeration inside a class
#define SR_ENUM_CLASS_T(enumName, type, ...) \
      SR_ENUM_DETAIL_MAKE(enum class, class, enumName, type, __VA_ARGS__ )

/// Declare an enumeration inside a namespace
#define SR_ENUM_NS_T(enumName, type, ...) \
      SR_ENUM_DETAIL_MAKE(enum, namespace, enumName, type, __VA_ARGS__ )

/// Declare an enumeration inside a namespace
#define SR_ENUM_NS_CLASS_T(enumName, type, ...) \
      SR_ENUM_DETAIL_MAKE(enum class, namespace, enumName, type, __VA_ARGS__ ) \
      typedef type SR_MACRO_CONCAT(enumName, Flag);

/// Declare an enumeration inside a namespace
#define SR_ENUM_NS_STRUCT_T(enumName, type, ...)                                \
      struct enumName {                                                         \
            SR_ENUM_DETAIL_MAKE(enum, class, SR_MACRO_CONCAT(enumName, T), type, __VA_ARGS__ )  \
      };                                                                                        \
      typedef type SR_MACRO_CONCAT(enumName, Flag);                                             \

/// ---------------------------------------[Для объявления внутри классов]----------------------------------------------

#define SR_ENUM_CLASS(enumName, ...) SR_ENUM_CLASS_T(enumName, int32_t, __VA_ARGS__)
#define SR_ENUM(enumName, ...) SR_ENUM_T(enumName, int32_t, __VA_ARGS__)

/// ----------------------------------[Для объявления внутри пространств имен]------------------------------------------

#define SR_ENUM_NS_CLASS(enumName, ...) SR_ENUM_NS_CLASS_T(enumName, int32_t, __VA_ARGS__)
#define SR_ENUM_NS(enumName, ...) SR_ENUM_NS_T(enumName, int32_t, __VA_ARGS__)

/// --------------------------------------------------------------------------------------------------------------------

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(BoolExt, int8_t,
          None  = -1,
          False = 0,
          True  = 1
    );
}

#endif //GAMEENGINE_ENUMERATIONS_H
