

# File AtlasBuilderTest.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Tests**](dir_98cd65c77c4c44b0f9320fc0543d4121.md) **>** [**AtlasBuilderTest.h**](libs_2Utils_2inc_2Utils_2Tests_2AtlasBuilderTest_8h.md)

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


