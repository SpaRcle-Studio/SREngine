

# File FreeType.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Font**](dir_0f9fa5c8aefacabb9ad499652a4f09bc.md) **>** [**FreeType.h**](FreeType_8h.md)

[Go to the documentation of this file](FreeType_8h.md)


```C++
//
// Created by mantsurov-n on 02.11.2022.
//

#ifndef SR_ENGINE_FREETYPE_H
#define SR_ENGINE_FREETYPE_H

#include <Graphics/macros.h>

#include <Utils/macros.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftglyph.h>
#include <freetype/tttables.h>
#include <freetype/src/truetype/ttobjs.h>

namespace SR_GRAPH_NS {
    static std::string FreeTypeErrToString(FT_Error err) {
#undef FTERRORS_H_
#define FT_ERRORDEF(e, v, s)  case e: return s;
#define FT_ERROR_START_LIST     switch (err) {
#define FT_ERROR_END_LIST       }

#include FT_ERRORS_H
        return "(Unknown error)";
    }

    SR_MAYBE_UNUSED static void FTUnusedFunctions() {
    #ifdef SR_LINUX
    #else
        tt_glyphzone_done(nullptr);
        tt_glyphzone_new(nullptr, 0, 0, nullptr);
        tt_size_init(nullptr);
        tt_size_done(nullptr);
        tt_size_run_fpgm(nullptr, false);
        tt_size_run_prep(nullptr, false);
        tt_size_ready_bytecode(nullptr, false);
        tt_size_reset(nullptr);
        tt_driver_init(nullptr);
        tt_driver_done(nullptr);
        tt_slot_init(nullptr);
    #endif
    }
}

#define SRFreeTypeErrToString(err) (FreeTypeErrToString(err))

#endif //SR_ENGINE_FREETYPE_H
```


