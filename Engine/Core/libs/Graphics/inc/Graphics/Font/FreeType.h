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

namespace SR_GRAPH_NS {
    static std::string FreeTypeErrToString(FT_Error err) {
#undef FTERRORS_H_
#define FT_ERRORDEF(e, v, s)  case e: return s;
#define FT_ERROR_START_LIST     switch (err) {
#define FT_ERROR_END_LIST       }

#include FT_ERRORS_H
        return "(Unknown error)";
    }
}

#define SRFreeTypeErrToString(err) (FreeTypeErrToString(err))

#endif //SRENGINE_FREETYPE_H
