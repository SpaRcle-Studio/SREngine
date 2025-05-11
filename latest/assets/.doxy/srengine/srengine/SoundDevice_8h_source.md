

# File SoundDevice.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**SoundDevice.h**](SoundDevice_8h.md)

[Go to the documentation of this file](SoundDevice_8h.md)


```C++
//
// Created by Monika on 08.07.2022.
//

#ifndef SR_ENGINE_SOUNDDEVICE_H
#define SR_ENGINE_SOUNDDEVICE_H

#include <Audio/macros.h>

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
```


