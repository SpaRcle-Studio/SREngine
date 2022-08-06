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
        virtual ~IGraphicsResource() = default;

    public:
        IGraphicsResource(const IGraphicsResource&) = delete;
        IGraphicsResource& operator=(const IGraphicsResource&) = delete;

    public:
        /// данный метод можно вызывать только из контекста рендера,
        /// в котором он был инициализирован
        virtual void FreeVideoMemory() = 0;

    };
}

#endif //SRENGINE_IGRAHPICSRESOURCE_H
