//
// Created by Monika on 13.05.2023.
//

#ifndef SRENGINE_TRACYCONTEXT_H
#define SRENGINE_TRACYCONTEXT_H

#ifdef SR_TRACY_ENABLE

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Types/Map.h>

#include <Tracy.hpp>

namespace SR_UTILS_NS {
    SR_ENUM_NS_STRUCT_T(TracyType, uint8_t,
        Common,
        Vulkan,

        All
    );

    class TracyContextManager : public SR_UTILS_NS::Singleton<TracyContextManager> {
        SR_REGISTER_SINGLETON(TracyContextManager)
        using TracyContextPtr = void*;
        using IdentifierPtr = void*;
        using ContextMap = std::map<IdentifierPtr, TracyContextPtr>;
    public:
        TracyContextPtr& GetContext(TracyTypeFlag type, IdentifierPtr pIdentifier) {
            if (type >= TracyType::TracyTypeTMAX - 1) {
                SRHalt0();
                static TracyContextPtr pNull = nullptr;
                return pNull;
            }

            return m_contexts[type][pIdentifier];
        }

        void Destroy(TracyTypeFlag type);

    #ifdef SR_USE_VULKAN
        std::function<void(void*)> VulkanDestroy;
    #endif

    private:
        void Destroy(TracyContextPtr pContext, TracyTypeFlag type);

    private:
        std::array<ContextMap, TracyType::TracyTypeTMAX - 1> m_contexts;

    };
}
#endif

#ifdef SR_TRACY_ENABLE
    #define SR_TRACY_TEXT_N(name, text) ZoneText(text.c_str(), text.size())
    #define SR_TRACY_ZONE ZoneScoped
    #define SR_TRACY_ZONE_N(name) ZoneScopedN(name)
    #define SR_TRACY_ZONE_S(name) ZoneTransientN(TracyConcat(__tracy_source_location, TracyLine), name, true)

    #define SR_TRACY_GET_CONTEXT(tracyType, pIdentifier) \
        SR_UTILS_NS::TracyContextManager::Instance().GetContext(tracyType, pIdentifier)

    #define SR_TRACY_DESTROY(tracyType) SR_UTILS_NS::TracyContextManager::Instance().Destroy(tracyType);

#else
    #define SR_TRACY_TEXT_N(name, text)
    #define SR_TRACY_ZONE SR_NOOP
    #define SR_TRACY_ZONE_N(name) SR_NOOP
    #define SR_TRACY_ZONE_S(name) SR_NOOP

    #define SR_TRACY_GET_CONTEXT(tracyType, pIdentifier)
    #define SR_TRACY_DESTROY(tracyType)
#endif


#endif //SRENGINE_TRACYCONTEXT_H
