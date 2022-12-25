//
// Created by Monika on 18.07.2022.
//

#ifndef SRENGINE_IGRAHPICSRESOURCE_H
#define SRENGINE_IGRAHPICSRESOURCE_H

namespace SR_GRAPH_NS::Memory {
    /// Не наследуемся от NonCopyable, чтобы не возникло конфликтов с IResource
    class IGraphicsResource {
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
        /// в котором он был инициализирован
        virtual void FreeVideoMemory() {
            m_isCalculated = false;
        }

        SR_NODISCARD SR_FORCE_INLINE bool IsCalculated() const noexcept { return m_isCalculated; }

    protected:
        std::atomic<bool> m_isCalculated = false;

    };
}

#endif //SRENGINE_IGRAHPICSRESOURCE_H
