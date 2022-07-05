//
// Created by Igor on 05/07/2022.
//

#ifndef SRENGINE_LOADER_H
#define SRENGINE_LOADER_H

#include <Utils/macros.h>

namespace SR_AUDIO_NS {
    //this is here thanks to https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
    std::int32_t convert_to_int(char* buffer, std::size_t len)
    {
        std::int32_t a = 0;
        if(std::endian::native == std::endian::little)
            std::memcpy(&a, buffer, len);
        else
            for(std::size_t i = 0; i < len; ++i)
                reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
        return a;
    }

    bool load_wav_file_header(std::ifstream& file,
                              std::uint8_t& channels,
                              std::int32_t& sampleRate,
                              std::uint8_t& bitsPerSample,
                              ALsizei& size)
    {
        char buffer[4];
        if(!file.is_open())
            return false;

        // the RIFF
        if(!file.read(buffer, 4))
        {
            std::cerr << "ERROR: could not read RIFF" << std::endl;
            return false;
        }
        if(std::strncmp(buffer, "RIFF", 4) != 0)
        {
            std::cerr << "ERROR: file is not a valid WAVE file (header doesn't begin with RIFF)" << std::endl;
            return false;
        }

        // the size of the file
        if(!file.read(buffer, 4))
        {
            std::cerr << "ERROR: could not read size of file" << std::endl;
            return false;
        }

        // the WAVE
        if(!file.read(buffer, 4))
        {
            std::cerr << "ERROR: could not read WAVE" << std::endl;
            return false;
        }
        if(std::strncmp(buffer, "WAVE", 4) != 0)
        {
            std::cerr << "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)" << std::endl;
            return false;
        }

        // "fmt/0"
        if(!file.read(buffer, 4))
        {
            std::cerr << "ERROR: could not read fmt/0" << std::endl;
            return false;
        }

        // this is always 16, the size of the fmt data chunk
        if(!file.read(buffer, 4))
        {
            std::cerr << "ERROR: could not read the 16" << std::endl;
            return false;
        }

        // PCM should be 1?
        if(!file.read(buffer, 2))
        {
            std::cerr << "ERROR: could not read PCM" << std::endl;
            return false;
        }

        // the number of channels
        if(!file.read(buffer, 2))
        {
            std::cerr << "ERROR: could not read number of channels" << std::endl;
            return false;
        }
        channels = convert_to_int(buffer, 2);

        // sample rate
        if(!file.read(buffer, 4))
        {
            std::cerr << "ERROR: could not read sample rate" << std::endl;
            return false;
        }
        sampleRate = convert_to_int(buffer, 4);

        // (sampleRate * bitsPerSample * channels) / 8
        if(!file.read(buffer, 4))
        {
            std::cerr << "ERROR: could not read (sampleRate * bitsPerSample * channels) / 8" << std::endl;
            return false;
        }

        // ?? dafaq
        if(!file.read(buffer, 2))
        {
            std::cerr << "ERROR: could not read dafaq" << std::endl;
            return false;
        }

        // bitsPerSample
        if(!file.read(buffer, 2))
        {
            std::cerr << "ERROR: could not read bits per sample" << std::endl;
            return false;
        }
        bitsPerSample = convert_to_int(buffer, 2);

        // data chunk header "data"
        if(!file.read(buffer, 4))
        {
            std::cerr << "ERROR: could not read data chunk header" << std::endl;
            return false;
        }
        if(std::strncmp(buffer, "data", 4) != 0)
        {
            std::cerr << "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)" << std::endl;
            return false;
        }

        // size of data
        if(!file.read(buffer, 4))
        {
            std::cerr << "ERROR: could not read data size" << std::endl;
            return false;
        }
        size = convert_to_int(buffer, 4);

        /* cannot be at the end of file */
        if(file.eof())
        {
            std::cerr << "ERROR: reached EOF on the file" << std::endl;
            return false;
        }
        if(file.fail())
        {
            std::cerr << "ERROR: fail state set on the file" << std::endl;
            return false;
        }

        return true;
    }

    char* load_wav(const std::string& filename,
                   std::uint8_t& channels,
                   std::int32_t& sampleRate,
                   std::uint8_t& bitsPerSample,
                   ALsizei& size)
    {
        std::ifstream in(filename, std::ios::binary);
        if(!in.is_open())
        {
            std::cerr << "ERROR: Could not open \"" << filename << "\"" << std::endl;
            return nullptr;
        }
        if(!load_wav_file_header(in, channels, sampleRate, bitsPerSample, size))
        {
            std::cerr << "ERROR: Could not load wav header of \"" << filename << "\"" << std::endl;
            return nullptr;
        }

        char* data = new char[size];

        in.read(data, size);

        return data;
    }
    //this is here thanks to https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
}
#endif //SRENGINE_LOADER_H
