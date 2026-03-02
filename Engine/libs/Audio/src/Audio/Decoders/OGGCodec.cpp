//
// Created by Monika on 09.12.2025.
//

#include <Audio/Decoders/OGGCodec.h>

#ifdef SR_AUDIO_USE_OGG
    #include <ogg/ogg.h>
#endif

namespace SR_AUDIO_NS {
    OggCodec DetectOggCodec(const char* data, size_t size) {
        if (!data || size < 27) return OggCodec::Unknown; // минимум заголовок страницы

        // 1) проверяем "OggS"
        if (std::memcmp(data, "OggS", 4) != 0) return OggCodec::Unknown;

        // 2) читаем количество сегментов (byte @ offset 26)
        const uint8_t segment_count = data[26];
        size_t headerSize = 27 + static_cast<size_t>(segment_count);
        if (headerSize > size) return OggCodec::Unknown; // нехватает данных для таблицы сегментов

        // 3) суммируем lacing values, чтобы получить длину первого логического пакета
        size_t packetLen = 0;
        bool packetFinished = false;
        for (size_t i = 0; i < segment_count; ++i) {
            uint8_t lace = data[27 + i];
            packetLen += lace;
            if (lace < 255) { // окончание пакета
                packetFinished = true;
                // первый пакет длиной packetLen
                break;
            }
            // если lace == 255, пакет продолжается в следующих сегментах/страницах
        }

        // если первый пакет не завершился в пределах первой страницы, надо прочитать дополнительные страницные сегменты.
        // здесь попробуем обработать простейший случай: пакет продолжается в следующих страницах, но мы их
        // не проанализировали — тогда нам нужно убедиться, что в буфере есть хотя бы headerSize + packetLen (может быть 0)
        if (!packetFinished) {
            // пакет продолжается: нам нужно прочитать дополнительные сегменты/страницы из файла,
            // но если у нас нет достаточного объёма данных — не можем детектировать
            // Попытаемся подсчитать максимально возможное из текущей таблицы: packetLen сейчас = sum всех 255 и т.д.
            // Если packetLen == 0 (в редких случаях), тоже bail out.
            // Чтобы быть безопасным — если у нас нет хотя бы headerSize bytes, вернём Unknown.
            // Лучше: caller должен дать больше байт (чтение первых 4-8KB обычно достаточно).
            // Здесь просто проверяем, что хотя бы есть какие-то данные для сопоставления сигнатуры.
            // Но в большинстве реальных файлов identification header содержится целиком в первой странице,
            // так что packetFinished обычно истинно.
        }

        // 4) начало первого пакета
        if (headerSize >= size) return OggCodec::Unknown; // нет места для первого сегмента
        const char* packet = data + headerSize;
        size_t available = size - headerSize;

        // Если packetLen > 0 и у нас есть packetLen байт — проверим сигнатуры на этих данных.
        // Если packetLen == 0 (не определили), просто проверяем первые несколько байт (грубая проверка).
        // Проверка Vorbis: packet[0] == 0x01 и далее "vorbis"
        if (available >= 7) {
            if (packet[0] == 0x01 && std::memcmp(packet + 1, "vorbis", 6) == 0) {
                return OggCodec::Vorbis;
            }
        } else if (packetLen > 0 && available >= packetLen && packetLen >= 7) {
            if (packet[0] == 0x01 && std::memcmp(packet + 1, "vorbis", 6) == 0) {
                return OggCodec::Vorbis;
            }
        }

        // Проверка Opus: начинается с "OpusHead"
        if (available >= 8) {
            if (std::memcmp(packet, "OpusHead", 8) == 0) {
                return OggCodec::Opus;
            }
        } else if (packetLen > 0 && available >= packetLen && packetLen >= 8) {
            if (std::memcmp(packet, "OpusHead", 8) == 0) {
                return OggCodec::Opus;
            }
        }

        if (available >= 5 && packet[0] == 0x7F && std::memcmp(packet + 1, "FLAC", 4) == 0)
            return OggCodec::Flac;

        // Проверка OggFLAC: начинается с "fLaC"
        if (available >= 4) {
            if (std::memcmp(packet, "fLaC", 4) == 0) {
                return OggCodec::Flac;
            }
        } else if (packetLen > 0 && available >= packetLen && packetLen >= 4) {
            if (std::memcmp(packet, "fLaC", 4) == 0) {
                return OggCodec::Flac;
            }
        }

        return OggCodec::Unknown;
    }

    RawSoundDataPtr UnpackOggData(const std::string& oggData) {
   #ifdef SR_AUDIO_USE_OGG
        if (oggData.empty()) {
            SR_ERROR("UnpackOggData() : input data is empty!");
            return {};
        }

        ogg_sync_state oy;
        ogg_sync_init(&oy);

        size_t pos = 0;
        ogg_stream_state os;
        bool osInitialized = false;
        int serialno = 0;

        auto packets = std::make_shared<RawSoundData>();
        packets->reserve(oggData.size() * 0.75); // примерный размер после распаковки

        while (pos < oggData.size()) {
            char* buffer = ogg_sync_buffer(&oy, 4096);
            size_t bytes = std::min<size_t>(4096, oggData.size() - pos);
            memcpy(buffer, oggData.data() + pos, bytes);
            pos += bytes;
            ogg_sync_wrote(&oy, bytes);

            ogg_page page;
            while (ogg_sync_pageout(&oy, &page) == 1) {
                if (!osInitialized) {
                    serialno = ogg_page_serialno(&page);
                    ogg_stream_init(&os, serialno);
                    osInitialized = true;
                }

                if (ogg_page_serialno(&page) != serialno) {
                    // для простоты игнорируем другие потоки
                    continue;
                }

                ogg_stream_pagein(&os, &page);

                ogg_packet packet;
                while (ogg_stream_packetout(&os, &packet) == 1) {
                    size_t currentSize = packets->size();
                    packets->resize(currentSize + packet.bytes);
                    memcpy(packets->data() + currentSize, packet.packet, packet.bytes);
                }
            }
        }

        if (osInitialized) {
            ogg_stream_clear(&os);
        }
        ogg_sync_clear(&oy);
        return packets;

    #else
        SR_ERROR("OGG support is disabled!");
        return nullptr;
    #endif
    }

    std::vector<RawSoundData> UnpackOggDataSeparated(const std::string& oggData) {
    #ifdef SR_AUDIO_USE_OGG
        if (oggData.empty()) {
            SR_ERROR("UnpackOggDataSeparated() : input data is empty!");
            return {};
        }

        ogg_sync_state oy;
        ogg_sync_init(&oy);

        size_t pos = 0;
        ogg_stream_state os;
        bool osInitialized = false;
        int serialno = 0;

        std::vector<RawSoundData> packets;

        while (pos < oggData.size()) {
            char* buffer = ogg_sync_buffer(&oy, 4096);
            size_t bytes = std::min<size_t>(4096, oggData.size() - pos);
            memcpy(buffer, oggData.data() + pos, bytes);
            pos += bytes;
            ogg_sync_wrote(&oy, bytes);

            ogg_page page;
            while (ogg_sync_pageout(&oy, &page) == 1) {
                if (!osInitialized) {
                    serialno = ogg_page_serialno(&page);
                    ogg_stream_init(&os, serialno);
                    osInitialized = true;
                }

                if (ogg_page_serialno(&page) != serialno) {
                    // для простоты игнорируем другие потоки
                    continue;
                }

                ogg_stream_pagein(&os, &page);

                ogg_packet packet;
                while (ogg_stream_packetout(&os, &packet) == 1) {
                    RawSoundData pkt;
                    pkt.resize(packet.bytes);
                    memcpy(pkt.data(), packet.packet, packet.bytes);
                    packets.push_back(std::move(pkt));
                }
            }
        }

        if (osInitialized) {
            ogg_stream_clear(&os);
        }
        ogg_sync_clear(&oy);
        return packets;

    #else
        SR_ERROR("OGG support is disabled!");
        return nullptr;
    #endif
    }
}