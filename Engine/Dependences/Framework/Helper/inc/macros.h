//
// Created by Nikita on 21.03.2021.
//

#ifndef GAMEENGINE_MACROS_H
#define GAMEENGINE_MACROS_H

#define SR_FORCE_INLINE __forceinline
#define SR_NULL 0

#ifdef WIN32
    #define SR_WIN32_BOOL true
    #define SR_WIN32
#else
    #define SR_WIN32_BOOL false
#endif

#endif //GAMEENGINE_MACROS_H
