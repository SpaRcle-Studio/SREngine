//
// Created by mantsurov-n on 02.11.2022.
//

#ifndef SRENGINE_FREETYPE_H
#define SRENGINE_FREETYPE_H

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
        tt_glyphzone_done(nullptr);
        tt_glyphzone_new(nullptr, 0, 0, nullptr);
        tt_size_init(nullptr);
        tt_size_done(nullptr);
        tt_size_run_fpgm(nullptr, false);
        tt_size_run_prep(nullptr, false);
        tt_size_ready_bytecode(nullptr, false);
        tt_size_reset(nullptr, false);
        tt_driver_init(nullptr);
        tt_driver_done(nullptr);
        tt_slot_init(nullptr);
    }
}

#define SRFreeTypeErrToString(err) (FreeTypeErrToString(err))

#endif //SRENGINE_FREETYPE_H
