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
