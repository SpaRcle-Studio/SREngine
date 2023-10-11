//
// Created by Capitan_Slider on 30.09.2023.
//

#ifndef SRENGINE_LISTENERSOUND_H
#define SRENGINE_LISTENERSOUND_H

#include <Utils/Common/NonCopyable.h>

namespace SR_AUDIO_NS{
    class SoundDevice;

class ListenerContext : public SR_UTILS_NS::NonCopyable{
    protected:
        explicit ListenerContext(SoundDevice* pDevice);

    public:
        ~ListenerContext() override;

    public:
        SR_NODISCARD SoundDevice* GetDevice() const;
        void OnMatrixDirty();

    protected:
        SoundDevice* m_device = nullptr;

    };
}

#endif //SRENGINE_LISTENERSOUND_H