//
// Created by Monika on 17.06.2022.
//

#include <Engine/Settings/ProjectSettings.h>

#include <Enum/GameBuildConfiguration.hpp>
#include <Enum/DesktopBuildPackageMode.hpp>

#include <Codegen/ProjectSettings.generated.hpp>

namespace SR_CORE_NS {
    bool GameBuildProfile::operator==(const GameBuildProfile& rhs) const {
        return name == rhs.name &&
               configuration == rhs.configuration &&
               desktopPackageMode == rhs.desktopPackageMode &&
               outputPath == rhs.outputPath &&
               startScene == rhs.startScene &&
               organization == rhs.organization &&
               androidPackageId == rhs.androidPackageId &&
               androidVersionCode == rhs.androidVersionCode &&
               windows == rhs.windows &&
               linux == rhs.linux &&
               androidArm64 == rhs.androidArm64 &&
               androidX64 == rhs.androidX64 &&
               emscripten == rhs.emscripten &&
               createPlatformArchives == rhs.createPlatformArchives &&
               enableWebPreview == rhs.enableWebPreview;
    }

    bool GameBuildProfile::operator!=(const GameBuildProfile& rhs) const {
        return !(*this == rhs);
    }

    const GameBuildProfile& ProjectSettings::GetActiveProfile() const {
        if (buildProfiles.size() <= activeBuildProfile) {
            static GameBuildProfile empty;
            return empty;
        }
        return buildProfiles.at(activeBuildProfile);
    }
}
