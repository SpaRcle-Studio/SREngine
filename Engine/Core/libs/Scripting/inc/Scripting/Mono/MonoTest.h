//
// Created by Monika on 15.03.2025.
//

#ifndef SR_ENGINE_MONO_TEST_H
#define SR_ENGINE_MONO_TEST_H

#include <Utils/stdInclude.h>

#ifdef SR_ANDROID
    class AAssetManager;
#endif

namespace SR_SCRIPTING_NS {
#ifdef SR_ANDROID
    void RunMonoTest(AAssetManager* pAssetManager);
#else
    void RunMonoTest();
#endif
}

#endif //SR_ENGINE_MONO_TEST_H
