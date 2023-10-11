//
// Created by Capitan_Slider on 30.09.2023.
//

#include <Audio/ListenerContext.h>

namespace SR_AUDIO_NS {
    ListenerContext::ListenerContext(SoundDevice *pDevice)
        : m_device(pDevice)
    { }

    ListenerContext::~ListenerContext() {
        delete m_device;
    }

    SoundDevice *ListenerContext::GetDevice() const {
        return m_device;
    }

    void ListenerContext::OnMatrixDirty() {

    }
}