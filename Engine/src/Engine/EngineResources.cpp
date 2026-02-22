//
// Created by Monika on 09.03.2023.
//

//namespace SR_CORE_NS::Resources {
//    bool RegisterResources(const SR_HTYPES_NS::SharedPtr<Engine>& pEngine) {
//        auto&& resourcesManager = SR_UTILS_NS::ResourceManager::Instance();
//
//        const auto contextGetter = [pEngine]() -> SR_GRAPH_NS::RenderContext::Ptr {
//            return pEngine ? pEngine->GetRenderContext() : SR_GRAPH_NS::RenderContext::Ptr();
//        };
//
//        resourcesManager.RegisterReloader<SR_HTYPES_NS::RawMesh, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);
//        resourcesManager.RegisterReloader<SR_GTYPES_NS::Texture, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);
//        resourcesManager.RegisterReloader<SR_GTYPES_NS::Shader, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);
//        resourcesManager.RegisterReloader<SR_GRAPH_NS::FileMaterialResource, SR_CORE_NS::GraphicsResourceReloader>(contextGetter);
//
//        return true;
//    }
//}
