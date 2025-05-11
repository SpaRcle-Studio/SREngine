

# File AtlasBuilderTest.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Tests**](dir_c9bf2873816ed2ebb5fd18269f2ea03a.md) **>** [**AtlasBuilderTest.h**](libs_2Utils_2inc_2Utils_2Tests_2AtlasBuilderTest_8h.md)

[Go to the documentation of this file](libs_2Utils_2inc_2Utils_2Tests_2AtlasBuilderTest_8h.md)


```C++
#ifndef SR_ENGINE_ATLASBUILDERTEST_H
#define SR_ENGINE_ATLASBUILDERTEST_H

#include <Graphics/Utils/AtlasBuilder.h>
#include <Utils/Resources/ResourceManager.h>

namespace SR_UTILS_NS {

    class AtlasBuilderTest {
    public:
        static bool Test() {
    /*        auto&& resourcePath =*/
//

            auto&& spritesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Tests/Sprites");
            SR_LOG(spritesFolder.ToString());

            SR_GRAPH_NS::AtlasBuilder builder(spritesFolder);

            return true;
        }
    };
}



#endif //SR_ENGINE_ATLASBUILDERTEST_H
```


