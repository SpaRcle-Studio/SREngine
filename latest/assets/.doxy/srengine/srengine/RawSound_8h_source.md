

# File RawSound.h

[**File List**](files.md) **>** [**Audio**](dir_af8f778bf511d1bbb5230b0ab41e3424.md) **>** [**inc**](dir_1caa84b6edd46a6082f45882423e2ed3.md) **>** [**Audio**](dir_9d91a3f4ef73924e6058505af21a433d.md) **>** [**RawSound.h**](RawSound_8h.md)

[Go to the documentation of this file](RawSound_8h.md)


```C++
//
// Created by Monika on 06.07.2022.
//

#ifndef SR_ENGINE_RAWSOUND_H
#define SR_ENGINE_RAWSOUND_H

#include <Audio/macros.h>

#include <Utils/Resources/IResource.h>

namespace SR_AUDIO_NS {
    class IWaveDataProvider;

    class RawSound : public SR_UTILS_NS::IResource {
    private:
        RawSound();
        ~RawSound() override;

    public:
        static RawSound* Load(const SR_UTILS_NS::Path& rawPath);

    public:
        SR_NODISCARD uint64_t GetFileHash() const override { return 0; };
        SR_NODISCARD uint64_t GetBufferSize() const;
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
        SR_NODISCARD const uint8_t* GetBufferData() const;
        SR_NODISCARD uint8_t GetChannels() const;
        SR_NODISCARD uint8_t GetBitsPerSample() const;
        SR_NODISCARD uint32_t GetSampleRate() const;
        SR_NODISCARD bool IsAllowedToRevive() const override { return true; }

    protected:
        bool Unload() override;
        bool Load() override;
        bool Reload() override;

    private:
        std::shared_ptr<IWaveDataProvider> m_dataProvider;

    };
}

#endif //SR_ENGINE_RAWSOUND_H
```


