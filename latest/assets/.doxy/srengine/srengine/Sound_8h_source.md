

# File Sound.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**Sound.h**](Sound_8h.md)

[Go to the documentation of this file](Sound_8h.md)


```C++
//
// Created by Igor on 05/07/2022.
//

#ifndef SR_ENGINE_SOUND_H
#define SR_ENGINE_SOUND_H

#include <Audio/macros.h>

#include <Utils/Resources/IResource.h>
#include <Audio/PlayParams.h>

namespace SR_AUDIO_NS {
    class RawSound;
    struct SoundData;

    class Sound : public SR_UTILS_NS::IResource {
        using Handle = void*;
    protected:
        Sound();
        ~Sound() override;

        SR_NODISCARD uint64_t GetFileHash() const override { return 0; };

    public:
        static Sound* Load(const SR_UTILS_NS::Path& path);

        Handle Play(const PlayParams& params);
        Handle Play();

        SR_NODISCARD bool IsAllowedToRevive() const override;

        SR_NODISCARD const uint8_t* GetBufferData() const;
        SR_NODISCARD uint64_t GetBufferSize() const;
        SR_NODISCARD uint8_t GetChannels() const;
        SR_NODISCARD uint8_t GetBitsPerSample() const;
        SR_NODISCARD uint32_t GetSampleRate() const;
        SR_NODISCARD SoundData* GetData() const;

    protected:
        bool Load() override;
        bool Unload() override;
        bool Reload() override;

    private:
        void SetRawSound(RawSound* pRawSound);

    private:
        RawSound* m_rawSound = nullptr;
        SoundData* m_data = nullptr;

    };
}

#endif //SR_ENGINE_SOUND_H

```


