//
// Created by Monika on 17.06.2022.
//

#ifndef SR_ENGINE_PROJECT_SETTINGS_H
#define SR_ENGINE_PROJECT_SETTINGS_H

#include <Engine/macros.h>

#include <Utils/Resources/Asset.h>
#include <Utils/FileSystem/PathDataAccessor.h>

namespace SR_CORE_NS {
    SR_ENUM_NS_CLASS_T(GameBuildConfiguration, uint8_t,
        Release,
        Debug
    )

    SR_ENUM_NS_CLASS_T(DesktopBuildPackageMode, uint8_t,
        Monolithic,
        PortableZip
    )

    struct GameBuildProfile : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        /// @property
        SR_UTILS_NS::String name = "Default";
        /// @property
        GameBuildConfiguration configuration = GameBuildConfiguration::Release;
        /// @property
        DesktopBuildPackageMode desktopPackageMode = DesktopBuildPackageMode::Monolithic;
        /// @property
        SR_UTILS_NS::Path outputPath = "Builds";
        /// @property
        SR_UTILS_NS::String organization = "SpaRcle-Studio";
        /// @property
        SR_UTILS_NS::String androidPackageId = "com.organization.game";
        /// @property
        uint32_t androidVersionCode = 1;
        /// @property
        bool windows = true;
        /// @property
        bool linux = true;
        /// @property
        bool androidArm64 = true;
        /// @property
        bool androidX64 = true;
        /// @property
        bool emscripten = true;
        /// @property
        bool createPlatformArchives = true;
        /// @property
        bool packEditor = false;
        /// @property
        bool enableWebPreview = true;

        SR_NODISCARD bool operator==(const GameBuildProfile& rhs) const;
        SR_NODISCARD bool operator!=(const GameBuildProfile& rhs) const;

    };

    /// @extension(srproject)
    class ProjectSettings : public SR_UTILS_NS::Asset {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ProjectSettings>;

    public:
        const GameBuildProfile& GetActiveProfile() const;

        /// @property
        SR_UTILS_NS::StringAtom projectName = "New Project";
        /// @property
        /// @customArgs(pick: enabled, filter name: Scene, relative: resources)
        /// @customArg(filter value: scene)
        SR_UTILS_NS::Path mainScene;
        /// @property
        SR_UTILS_NS::String version = "1.0.0";
        /// @property
        SR_UTILS_NS::Set<SR_UTILS_NS::StringAtom> packages;
        /// @property
        SR_UTILS_NS::Vector<GameBuildProfile> buildProfiles = { GameBuildProfile() };
        /// @property
        bool enableCppScripts = true;

        /// @property @hidden
        uint32_t activeBuildProfile = 0;

    };
}

#endif //SR_ENGINE_PROJECT_SETTINGS_H
