

# File AtlasBuilderTest.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**Tests**](dir_a438f77ea296cf9ed84cc5f25e2e6a4d.md) **>** [**AtlasBuilderTest.h**](inc_2Core_2Tests_2AtlasBuilderTest_8h.md)

[Go to the documentation of this file](inc_2Core_2Tests_2AtlasBuilderTest_8h.md)


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


