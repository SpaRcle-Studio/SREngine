

# File AtlasBuilderTest.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**Tests**](dir_b306193d88a6a4b0067721036c79fdf5.md) **>** [**AtlasBuilderTest.h**](inc_2Engine_2Tests_2AtlasBuilderTest_8h.md)

[Go to the documentation of this file](inc_2Engine_2Tests_2AtlasBuilderTest_8h.md)


```C++
//
// Created by innerviewer on 2024-06-01.
//

#ifndef SR_ATLAS_BUILDER_TEST_H
#define SR_ATLAS_BUILDER_TEST_H

#include <Graphics/Utils/AtlasBuilder.h>
#include <Utils/Platform/Platform.h>

namespace SR_CORE_NS::Tests {
    class AtlasBuilderTest {
    public:
        static bool Run() {
            SR_GRAPH_NS::AtlasBuilderData data;

            data.saveInCache = true;
            data.source = "Tests/Sprites";

            SR_GRAPH_NS::AtlasBuilder builder(data);
            return builder.Generate();
        }
    };
}

#endif //SR_ATLAS_BUILDER_TEST_H
```


