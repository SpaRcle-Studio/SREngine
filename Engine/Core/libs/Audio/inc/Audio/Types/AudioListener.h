//
// Created by Capitan_Slider on 16.09.2023.
//

#ifndef SRENGINE_AUDIOLSTENER_H
#define SRENGINE_AUDIOLSTENER_H

#include <Utils/ECS/Component.h>

namespace SR_AUDIO_NS
{
    class ListenerContext;

    class AudioListener : public SR_UTILS_NS::Component{
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(AudioListener);
        using Super = SR_UTILS_NS::Component;
        using Handle = void*;
    public:
        AudioListener();

    public:
        static SR_UTILS_NS::Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_UTILS_NS::SavableSaveData data) const override;

        void OnMatrixDirty() override;

        void OnAttached() override;
    protected:
        void OnDestroy() override;

    private:
        Handle m_handle = nullptr;

        ListenerContext* m_listenerContext = nullptr;
    };
}

#endif //SRENGINE_AUDIOLSTENER_H
