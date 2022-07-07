//
// Created by Monika on 07.07.2022.
//

#include <Audio/Decoders/IWaveDataProvider.h>
#include <Audio/Decoders/WAVDataProvider.h>
#include <Audio/Decoders/MP3DataProvider.h>
#include <Audio/Decoders/ModPlugDataProvider.h>

namespace SR_AUDIO_NS::Tools {
    bool IsModule( const char* Ext )
    {
        return (
                ( SR_STRCMPI( Ext, "mod" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "s3m" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "xm" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "it" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "669" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "amf" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "ams" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "dbm" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "dmf" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "dsm" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "far" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "mdl" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "med" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "mtm" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "okt" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "ptm" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "stm" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "ult" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "umx" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "mt2" ) == 0 ) ||
                ( SR_STRCMPI( Ext, "psm" ) == 0 ) ||
                // MIDI
                ( SR_STRCMPI( Ext, "mid" ) == 0 )
                // compressed modules
        /*		||
                ( strcmpi( Ext, "mdz" ) == 0 ) ||
                ( strcmpi( Ext, "s3z" ) == 0 ) ||
                ( strcmpi( Ext, "xmz" ) == 0 ) ||
                ( strcmpi( Ext, "itz" ) == 0 ) ||
                ( strcmpi( Ext, "mdr" ) == 0 ) ||
                ( strcmpi( Ext, "s3r" ) == 0 ) ||
                ( strcmpi( Ext, "xmr" ) == 0 ) ||
                ( strcmpi( Ext, "itr" ) == 0 ) ||
                ( strcmpi( Ext, "mdgz" ) == 0 ) ||
                ( strcmpi( Ext, "s3gz" ) == 0 ) ||
                ( strcmpi( Ext, "xmgz" ) == 0 ) ||
                ( strcmpi( Ext, "itgz" ) == 0 )
        */
        );
    }
}

namespace SR_AUDIO_NS {
    IWaveDataProvider::Ptr CreateWaveDataProvider(const SR_UTILS_NS::Path &path, const SoundData &data) {
        const char* ext = path.GetExtensionView().data();

        //if ( strcmpi( Ext, "mp3" ) == 0 )
        //    return std::make_shared<clMP3DataProvider>( Data );
        //
        //if ( strcmpi( Ext, "ogg" ) == 0 )
        //    return std::make_shared<clOGGDataProvider>( Data );
        //
        //if ( strcmpi( Ext, "flac" ) == 0 )
        //    return std::make_shared<clFLACDataProvider>( Data );
        //
        //if ( strcmpi( Ext, "ape" ) == 0 )
        //    return std::make_shared<clAPEDataProvider>( Data );
        //
        //if ( strcmpi( Ext, "opus" ) == 0 )
        //    return std::make_shared<clOpusDataProvider>( Data );
        //
        //if ( IsModule( Ext ) )
        //    return std::make_shared<clModPlugDataProvider>( Data );

        if (auto&& mp3Blob = TryMP3InsideWAV(data)) {
            return std::make_shared<MP3DataProvider>(mp3Blob);
        }

        if (SR_STRCMPI(ext, "wav") == 0) {
            if (auto&& provider = std::make_shared<ModPlugDataProvider>(data); provider->IsValid()) {
                return provider;
            }
        }

        /// default
        return std::make_shared<WAVDataProvider>(data);
    }
}
