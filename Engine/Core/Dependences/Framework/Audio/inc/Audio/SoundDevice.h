//
// Created by Monika on 08.07.2022.
//

#ifndef SRENGINE_SOUNDDEVICE_H
#define SRENGINE_SOUNDDEVICE_H

#include <Utils/Common/NonCopyable.h>
#include <Audio/AudioLibrary.h>

namespace SR_AUDIO_NS {
    class SoundDevice : public SR_UTILS_NS::NonCopyable {
    protected:
        explicit SoundDevice(AudioLibrary library);

    public:
        ~SoundDevice() override = default;

    public:
        static SoundDevice* Allocate(AudioLibrary audioLibrary);

    public:
        virtual bool Init() = 0;

        SR_NODISCARD std::string GetName() const;
        SR_NODISCARD AudioLibrary GetLibrary() const;

    private:
        std::string m_name;
        AudioLibrary m_library;

    };
}

#endif //SRENGINE_SOUNDDEVICE_H
