//
// Created by Monika on 08.07.2022.
//

#ifndef SR_ENGINE_SOUNDDEVICE_H
#define SR_ENGINE_SOUNDDEVICE_H

#include <Utils/Common/NonCopyable.h>
#include <Audio/AudioLibrary.h>

namespace SR_AUDIO_NS {
    class SoundDevice : public SR_UTILS_NS::NonCopyable {
    protected:
        explicit SoundDevice(AudioLibrary library, const std::string& name);

    public:
        ~SoundDevice() override = default;

    public:
        static SoundDevice* Allocate(AudioLibrary audioLibrary, const std::string& name);

    public:
        virtual bool Init() = 0;

        SR_NODISCARD std::string GetName() const;
        SR_NODISCARD AudioLibrary GetLibrary() const;

    protected:
        std::string m_name;
        AudioLibrary m_library;

    };
}

#endif //SR_ENGINE_SOUNDDEVICE_H
