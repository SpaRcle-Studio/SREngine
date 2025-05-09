

# File FreeType.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Font**](dir_193e1c173bb6bd0681658b8507d31117.md) **>** [**FreeType.h**](FreeType_8h.md)

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


