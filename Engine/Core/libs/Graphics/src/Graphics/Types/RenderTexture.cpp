//
// Created by Monika on 18.07.2022.
//

#include <Utils/ResourceManager/ResourceManager.h>
#include <Graphics/Types/RenderTexture.h>

namespace SR_GTYPES_NS {
    RenderTexture::RenderTexture()
        : SR_UTILS_NS::Settings()
    { }

    RenderTexture::~RenderTexture() {

    }

    RenderTexture *RenderTexture::Load(const SR_UTILS_NS::Path &rawPath) {
        SR_GLOBAL_LOCK

        auto&& path = SR_UTILS_NS::Path(rawPath).RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

        if (auto&& pResource = SR_UTILS_NS::ResourceManager::Instance().Find<Settings>(path)) {
            auto&& pRenderTexture = dynamic_cast<RenderTexture *>(pResource);

            if (!pRenderTexture) {
                SR_ERROR("RenderTexture::Load() : failed to cast the resource!\n\tPath: " + path.ToString());
            }

            return pRenderTexture;
        }

        auto&& pRenderTexture = new RenderTexture();

        pRenderTexture->SetId(path, false /** auto register */);

        if (!pRenderTexture->Reload()) {
            SR_ERROR("RenderTexture::Load() : failed to load render texture!\n\tPath: " + path.ToString());
            delete pRenderTexture;
            return nullptr;
        }

        /// отложенная ручная регистрация
        SR_UTILS_NS::ResourceManager::Instance().RegisterResource(pRenderTexture);

        return pRenderTexture;
    }

    void RenderTexture::ClearSettings() {
        Settings::ClearSettings();

        if (m_fbo) {
            RemoveDependency(m_fbo);
            /// Ресурс будет автоматически уничтожен либо при убирании use-point'а,
            /// либо синхронно будет освобождена видео память через контекстный класс,
            /// а затем будет уничтожен сам русурс.
            m_fbo->RemoveUsePoint();
            m_fbo = nullptr;
        }
    }

    bool RenderTexture::LoadSettings(const SR_XML_NS::Node &node) {
        //if (auto&& sizeNode = node.GetNode("Size")) {
        //    m_size = sizeNode.GetAttribute<SR_MATH_NS::UVector2>();
        //}

        //if (auto&& preScaleNode = node.GetNode("PreScale")) {
        //    m_preScale = preScaleNode.GetAttribute<SR_MATH_NS::FVector2>();
        //}

        //for (auto&& colorNode : node.GetNodes("Colors")) {
        //    m_colors.emplace_back(ColorLayer {
        //        StringToEnumColorFormat(colorNode.TryGetAttribute("Format").ToString("Unknown")),
        //        SR_ID_INVALID
        //    });
        //}

        //m_dynamicScaling = node.TryGetAttribute("dynamicScaling").ToBool(true);
        //m_depth.format = StringToEnumDepthFormat(node.GetNode("Depth").TryGetAttribute("Format").ToString("Unknown"));

        return Settings::LoadSettings(node);
    }
}
