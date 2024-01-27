//
// Created by Monika on 28.12.2021.
//

#ifndef SR_ENGINE_ICONS_H
#define SR_ENGINE_ICONS_H

#include <imgui.h>

#define SR_ICON_MIN 0xe005
#define SR_ICON_MAX 0xf8ff

#define SR_ICON_FOLDER "\xef\x81\xbb" // U+f07b
#define SR_ICON_FOLDER_MINUS "\xef\x99\x9d"	// U+f65d
#define SR_ICON_FOLDER_OPEN "\xef\x81\xbc"	// U+f07c
#define SR_ICON_FOLDER_PLUS "\xef\x99\x9e"	// U+f65e

#define SR_ICON_FILE "\xef\x85\x9b"	// U+f15b
#define SR_ICON_FILE_ALT "\xef\x85\x9c"	// U+f15c
#define SR_ICON_FILE_ARCHIVE "\xef\x87\x86"	// U+f1c6
#define SR_ICON_FILE_AUDIO "\xef\x87\x87"	// U+f1c7
#define SR_ICON_FILE_CODE "\xef\x87\x89"	// U+f1c9
#define SR_ICON_FILE_CONTRACT "\xef\x95\xac"	// U+f56c
#define SR_ICON_FILE_CSV "\xef\x9b\x9d"	// U+f6dd
#define SR_ICON_FILE_DOWNLOAD "\xef\x95\xad"	// U+f56d
#define SR_ICON_FILE_EXCEL "\xef\x87\x83"	// U+f1c3
#define SR_ICON_FILE_EXPORT "\xef\x95\xae"	// U+f56e
#define SR_ICON_FILE_IMAGE "\xef\x87\x85"	// U+f1c5
#define SR_ICON_FILE_IMPORT "\xef\x95\xaf"	// U+f56f
#define SR_ICON_FILE_INVOICE "\xef\x95\xb0"	// U+f570
#define SR_ICON_FILE_INVOICE_DOLLAR "\xef\x95\xb1"	// U+f571
#define SR_ICON_FILE_MEDICAL "\xef\x91\xb7"	// U+f477
#define SR_ICON_FILE_MEDICAL_ALT "\xef\x91\xb8"	// U+f478
#define SR_ICON_FILE_PDF "\xef\x87\x81"	// U+f1c1
#define SR_ICON_FILE_POWERPOINT "\xef\x87\x84"	// U+f1c4
#define SR_ICON_FILE_PRESCRIPTION "\xef\x95\xb2"	// U+f572
#define SR_ICON_FILE_SIGNATURE "\xef\x95\xb3"	// U+f573
#define SR_ICON_FILE_UPLOAD "\xef\x95\xb4"	// U+f574
#define SR_ICON_FILE_VIDEO "\xef\x87\x88"	// U+f1c8
#define SR_ICON_FILE_WORD "\xef\x87\x82"	// U+f1c2

#define SR_ICON_PLAY "\xef\x81\x8b"	// U+f04b
#define SR_ICON_PLAY_CIRCLE "\xef\x85\x84"	// U+f144
#define SR_ICON_PAUSE "\xef\x81\x8c"	// U+f04c
#define SR_ICON_PAUSE_CIRCLE "\xef\x8a\x8b"	// U+f28b
#define SR_ICON_STOP "\xef\x81\x8d"	// U+f04d
#define SR_ICON_STOP_CIRCLE "\xef\x8a\x8d"	// U+f28d
#define SR_ICON_STOPWATCH "\xef\x8b\xb2"	// U+f2f2
#define SR_ICON_STOPWATCH_20 "\xee\x81\xaf"	// U+e06f

#define SR_ICON_BACKSPACE "\xef\x95\x9a"	// U+f55a
#define SR_ICON_UNDO "\xef\x83\xa2"


inline static const char* SR_ICONS[] = {
    SR_ICON_FOLDER,
    SR_ICON_FOLDER_MINUS,
    SR_ICON_FOLDER_OPEN,
    SR_ICON_FOLDER_PLUS,

    SR_ICON_FILE,
    SR_ICON_FILE_ALT,
    SR_ICON_FILE_ARCHIVE,
    SR_ICON_FILE_AUDIO,
    SR_ICON_FILE_CODE,
    SR_ICON_FILE_CONTRACT,
    SR_ICON_FILE_CSV,
    SR_ICON_FILE_DOWNLOAD,
    SR_ICON_FILE_EXCEL,
    SR_ICON_FILE_EXPORT,
    SR_ICON_FILE_IMAGE,
    SR_ICON_FILE_IMPORT,
    SR_ICON_FILE_INVOICE,
    SR_ICON_FILE_INVOICE_DOLLAR,
    SR_ICON_FILE_MEDICAL,
    SR_ICON_FILE_MEDICAL_ALT,
    SR_ICON_FILE_PDF,
    SR_ICON_FILE_POWERPOINT,
    SR_ICON_FILE_PRESCRIPTION,
    SR_ICON_FILE_SIGNATURE,
    SR_ICON_FILE_UPLOAD,
    SR_ICON_FILE_VIDEO,
    SR_ICON_FILE_WORD,

    SR_ICON_PLAY,
    SR_ICON_PLAY_CIRCLE,
    SR_ICON_PAUSE,
    SR_ICON_PAUSE_CIRCLE,
    SR_ICON_STOP,
    SR_ICON_STOP_CIRCLE,
    SR_ICON_STOPWATCH,
    SR_ICON_STOPWATCH_20,
};

namespace SR_GRAPH_NS::GUI {
    SR_ENUM_NS_CLASS(IconType,
          Flow,
          Circle,
          Square,
          Grid,
          RoundSquare,
          Diamond
    );

    void DrawIcon(ImDrawList* drawList, const ImVec2& a, const ImVec2& b, IconType type, bool filled, ImU32 color, ImU32 innerColor);
    void Icon(const ImVec2& size, IconType type, bool filled, const ImVec4& color = ImVec4(1, 1, 1, 1), const ImVec4& innerColor = ImVec4(0, 0, 0, 0));
}

#endif //SR_ENGINE_ICONS_H
