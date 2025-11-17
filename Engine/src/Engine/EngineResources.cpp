//
// Created by Monika on 09.03.2023.
//

#include <Engine/EngineResources.h>
#include <Engine/Utils/GraphicsResourceReloader.h>
#include <Engine/Engine.h>

#include <Utils/Types/RawMesh.h>
#include <Utils/SRLM/LogicalMachine.h>

#include <Graphics/Types/Shader.h>
#include <Graphics/Font/Font.h>
#include <Graphics/Types/Skybox.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Animations/AnimationClip.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Material/FileMaterial.h>

#include <Audio/RawSound.h>
#include <Audio/Sound.h>

#include <Scripting/Base/Behaviour.h>
//#include <Scripting/Impl/EvoScriptResourceReloader.h>
//#include <Scripting/Impl/EvoBehaviour.h>

namespace SR_CORE_NS::Resources {
    bool RegisterResources(const SR_HTYPES_NS::SharedPtr<Engine>& pEngine) {
        auto&& resourcesManager = SR_UTILS_NS::ResourceManager::Instance();

        //resourcesManager.RegisterReloader<SR_SCRIPTING_NS::EvoBehaviour, SR_SCRIPTING_NS::EvoScriptResourceReloader>();

        const auto contextGetter = [pEngine]() -> SR_GRAPH_NS::RenderContext::Ptr {
            return pEngine ? pEngine->GetRenderContext() : SR_GRAPH_NS::RenderContext::Ptr();
        };

        resourcesManager.RegisterReloader<SR_HTYPES_NS::RawMesh, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);
        resourcesManager.RegisterReloader<SR_GTYPES_NS::Texture, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);
        resourcesManager.RegisterReloader<SR_GTYPES_NS::Shader, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);
        resourcesManager.RegisterReloader<SR_GRAPH_NS::FileMaterialResource, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);

        return true;
    }
}
