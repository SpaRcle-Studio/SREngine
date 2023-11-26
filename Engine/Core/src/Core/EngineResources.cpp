//
// Created by Monika on 09.03.2023.
//

#include <Core/EngineResources.h>
#include <Core/Utils/GraphicsResourceReloader.h>

#include <Utils/Types/RawMesh.h>
#include <Utils/SRLM/LogicalMachine.h>

#include <Graphics/Types/Shader.h>
#include <Graphics/Font/Font.h>
#include <Graphics/Types/Skybox.h>

#include <Audio/RawSound.h>
#include <Audio/Sound.h>

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Impl/EvoScriptResourceReloader.h>
#include <Scripting/Impl/EvoBehaviour.h>

namespace SR_CORE_NS::Resources {
    bool RegisterResources(const SR_HTYPES_NS::SharedPtr<Engine>& pEngine) {
        auto&& resourcesManager = SR_UTILS_NS::ResourceManager::Instance();

        resourcesManager.RegisterType<SR_HTYPES_NS::RawMesh>();
        resourcesManager.RegisterType<SR_UTILS_NS::Settings>();
        resourcesManager.RegisterType<SR_UTILS_NS::Prefab>();

        resourcesManager.RegisterType<SR_SRLM_NS::LogicalMachine>();

        resourcesManager.RegisterType<SR_GTYPES_NS::Mesh>();
        resourcesManager.RegisterType<SR_GTYPES_NS::Texture>();
        resourcesManager.RegisterType<SR_GTYPES_NS::Material>();
        resourcesManager.RegisterType<SR_GTYPES_NS::Shader>();
        resourcesManager.RegisterType<SR_GTYPES_NS::Skybox>();
        resourcesManager.RegisterType<SR_GTYPES_NS::Framebuffer>();
        resourcesManager.RegisterType<SR_GTYPES_NS::Font>();

        resourcesManager.RegisterType<SR_SCRIPTING_NS::EvoBehaviour>();

        resourcesManager.RegisterType<SR_AUDIO_NS::Sound>();
        resourcesManager.RegisterType<SR_AUDIO_NS::RawSound>();

        resourcesManager.RegisterType<SR_ANIMATIONS_NS::AnimationClip>();

        resourcesManager.RegisterType<SR_PTYPES_NS::PhysicsMaterial>();

        /// ------------------------------------------------------------------------------------------------------------

        resourcesManager.RegisterReloader<SR_SCRIPTING_NS::EvoBehaviour, SR_SCRIPTING_NS::EvoScriptResourceReloader>();

        const auto contextGetter = [pEngine]() -> SR_GRAPH_NS::RenderContext::Ptr {
            return pEngine ? pEngine->GetRenderContext() : SR_GRAPH_NS::RenderContext::Ptr();
        };

        resourcesManager.RegisterReloader<SR_HTYPES_NS::RawMesh, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);
        resourcesManager.RegisterReloader<SR_GTYPES_NS::Texture, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);
        resourcesManager.RegisterReloader<SR_GTYPES_NS::Material, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);
        resourcesManager.RegisterReloader<SR_GTYPES_NS::Shader, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);

        return true;
    }
}
