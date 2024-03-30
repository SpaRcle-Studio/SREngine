//
// Created by innerviewer on 2024-03-20.
//

#include <Core/Launcher.h>
#include <Utils/Resources/ResourceEmbedder.h>

#include <Utils/EmbedResources/Featuresxml.h>

namespace SR_CORE_NS {
    void Launcher::Init(int argc, char** argv) {
        PreInit(argc, argv);

        ExportResources();
    }

    void Launcher::ExportResources() {
        SR_UTILS_NS::Path featuresXmlPath = "E:/repos/SREngine/Resources/Engine/Configs/Features.xml";

        //SR_UTILS_NS::ResourceEmbedder::ExportToFile<ResourceEmbedder::Resources::Featuresxml>(featuresXmlPath);
    }
}