//
// Created by Monika on 07.07.2022.
//

#include <Audio/Decoders/ModPlugDataProvider.h>

#include <modplug.h>

namespace SR_AUDIO_NS {
    static bool g_ModPlugLoaded = false;

    static void LoadModPlug()
    {
        if ( g_ModPlugLoaded ) return;

        ModPlug_Settings Settings;
        ModPlug_GetSettings( &Settings );

        // all "basic settings" are set before ModPlug_Load
        Settings.mResamplingMode = MODPLUG_RESAMPLE_FIR;
        Settings.mChannels = 2;
        Settings.mBits = 16;
        Settings.mFrequency = 44100;
        Settings.mStereoSeparation = 128;
        Settings.mMaxMixChannels = 256;
        Settings.mLoopCount = -1;

        ModPlug_SetSettings( &Settings );

        g_ModPlugLoaded = true;
    }

    ModPlugDataProvider::ModPlugDataProvider(const SoundData& data)
            : m_data(data)
            , m_format()
            , m_decodingBuffer()
            , m_bufferUsed(0)
            , m_isEndOfStream(false)
    {
        LoadModPlug();

        m_format.m_numChannels      = 2;
        m_format.m_samplesPerSecond = 44100;
        m_format.m_bitsPerSample    = 16;

        m_ModPlugFile = ModPlug_Load(data->data(), static_cast<int>(data->size()));
    }

    ModPlugDataProvider::~ModPlugDataProvider()
    {
        if (m_ModPlugFile) {
            ModPlug_Unload(m_ModPlugFile);
        }
    }

    const uint8_t* ModPlugDataProvider::GetWaveData() const
    {
        return m_decodingBuffer.data();
    }

    size_t ModPlugDataProvider::GetWaveDataSize() const
    {
        return m_bufferUsed;
    }

    int ModPlugDataProvider::DecodeFromFile( size_t Size )
    {
        if (m_isEndOfStream)
        {
            return 0;
        }

        return ModPlug_Read(m_ModPlugFile, m_decodingBuffer.data(), Size);
    }

    size_t ModPlugDataProvider::StreamWaveData( size_t Size )
    {
        if ( m_isEndOfStream )
        {
            return 0;
        }

        size_t OldSize = m_decodingBuffer.size();

        if ( Size > OldSize )
        {
            m_decodingBuffer.resize( Size, 0 );
        }

        m_bufferUsed = DecodeFromFile( Size );

        if ( m_bufferUsed <= 0 ) m_isEndOfStream = true;

        return m_bufferUsed;
    }

    void ModPlugDataProvider::Seek( float Seconds )
    {
        m_isEndOfStream = false;

        ModPlug_Seek( m_ModPlugFile, static_cast<int>( Seconds * 1000.0f ) );
    }
}