

# File OpenALDevice.h

[**File List**](files.md) **>** [**Audio**](dir_3b2bdb60abfc21f80d0d742b38f9bf0d.md) **>** [**inc**](dir_e119e7616d11278def47bdba41f03e3f.md) **>** [**Audio**](dir_d71989b0a6c56e7cf67d0c5ae6ec80fd.md) **>** [**Impl**](dir_45f97ee406bd7a76126228ed02b235a4.md) **>** [**OpenALDevice.h**](OpenALDevice_8h.md)

[Go to the documentation of this file](OpenALDevice_8h.md)


```C++
//
// Created by Monika on 08.07.2022.
//

#ifndef SR_ENGINE_OPENALDEVICE_H
#define SR_ENGINE_OPENALDEVICE_H

#include <Audio/SoundDevice.h>

class ALCdevice;

namespace SR_AUDIO_NS {
    class OpenALDevice : public SoundDevice {
    public:
        explicit OpenALDevice(AudioLibrary library, const std::string& name);
        ~OpenALDevice() override;

    public:
        bool Init() override;

        SR_NODISCARD ALCdevice* GetALDevice() const;

    private:
        ALCdevice* m_openALDevice = nullptr;

    };
}

#endif //SR_ENGINE_OPENALDEVICE_H
```


