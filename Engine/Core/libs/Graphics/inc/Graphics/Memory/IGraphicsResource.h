//
// Created by Monika on 18.07.2022.
//

#ifndef SRENGINE_IGRAHPICSRESOURCE_H
#define SRENGINE_IGRAHPICSRESOURCE_H

#include <Utils/Debug.h>

namespace SR_GRAPH_NS {
    class RenderContext;
    class Environment;
}

namespace SR_GRAPH_NS::Memory {
    /// Не наследуемся от NonCopyable, чтобы не возникло конфликтов с IResource
    class IGraphicsResource {
    public:
        using RenderContextPtr = RenderContext*;
        using PipelinePtr = Environment*;
    protected:
        constexpr IGraphicsResource() = default;
        virtual ~IGraphicsResource() {
            SRAssert(m_isCalculated == false);
        }

    public:
        IGraphicsResource(const IGraphicsResource&) = delete;
        IGraphicsResource& operator=(const IGraphicsResource&) = delete;

    public:
        /// данный метод можно вызывать только из контекста рендера,
        /// в котором он был инициализирован. Либо из кластера если это меш
        virtual void DeInitGraphicsResource() {
            m_pipeline = nullptr;
            m_renderContext = nullptr;
        }

        virtual void FreeVideoMemory() {
            m_isCalculated = false;
        }

        void SetRenderContext(const RenderContextPtr& renderContext);

        SR_NODISCARD PipelinePtr GetPipeline() const noexcept {
            return m_pipeline;
        }

        SR_NODISCARD RenderContextPtr GetRenderContext() const noexcept {
            return m_renderContext;
        }

        SR_NODISCARD SR_FORCE_INLINE bool IsCalculated() const noexcept { return m_isCalculated; }
        SR_NODISCARD SR_FORCE_INLINE bool IsGraphicsResourceRegistered() const noexcept { return m_pipeline; }

    protected:
        std::atomic<bool> m_isCalculated = false;

        PipelinePtr m_pipeline = nullptr;
        RenderContextPtr m_renderContext = nullptr;

    };
}

#endif //SRENGINE_IGRAHPICSRESOURCE_H
