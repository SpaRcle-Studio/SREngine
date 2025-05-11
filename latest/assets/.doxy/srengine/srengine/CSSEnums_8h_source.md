

# File CSSEnums.h

[**File List**](files.md) **>** [**CSS**](dir_8392c415e30628e2ce7c2879273a6118.md) **>** [**CSSEnums.h**](CSSEnums_8h.md)

[Go to the documentation of this file](CSSEnums_8h.md)


```C++
//
// Created by Monika on 20.08.2024.
//

#ifndef SR_COMMON_WEB_CSS_ENUMS_H
#define SR_COMMON_WEB_CSS_ENUMS_H

#include <Utils/Math/Vector2.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Common/StringAtomLiterals.h>

namespace SR_UTILS_NS::Web {
    enum class CSSBoxSizing : uint8_t {
        ContentBox, BorderBox, Inherit
    };

    enum class CSSPosition : uint8_t {
        Absolute,
        Relative,
        Fixed,
        Static,
        Sticky,
    };

    enum class CSSDisplay : uint8_t {
       Block , Inline, RunIn,

        Flow, FlowRoot, Table, Flex, Grid, Ruby,

        BlockFlow, InlineTable, FlexRunIn,

        ListItem, ListItemBlock, ListItemInline, ListItemFlow,
        ListItemFlowRoot, ListItemBlockFlow, ListItemBlockFlowRoot,
        FlowListItemBlock,

        TableRowGroup, TableHeaderGroup, TableFooterGroup,
        TableRow, TableCell, TableColumnGroup, TableColumn,
        TableCaption, RubyBase, RubyText, RubyBaseContainer,
        RubyTextContainer,

        Contents, None,

        InlineBlock, InlineFlex, InlineGrid,

        Inherit, Initial, Unset,

        SIZE
    };

    SR_INLINE_STATIC CSSDisplay DEFAULT_CSS_DISPLAY = CSSDisplay::Inline;
    SR_INLINE_STATIC CSSDisplay DEFAULT_CSS_DISPLAY_BODY = CSSDisplay::Block;
    SR_INLINE_STATIC CSSPosition DEFAULT_CSS_POSITION = CSSPosition::Static;
    SR_INLINE_STATIC CSSBoxSizing DEFAULT_CSS_BOX_SIZING = CSSBoxSizing::ContentBox;

    static CSSPosition StringToCSSPosition(const std::string_view str) {
        static std::unordered_map<SRHashType, CSSPosition> map = {
            { "absolute"_atom_hash, CSSPosition::Absolute },
            { "relative"_atom_hash, CSSPosition::Relative },
            { "fixed"_atom_hash, CSSPosition::Fixed },
            { "static"_atom_hash, CSSPosition::Static },
            { "sticky"_atom_hash, CSSPosition::Sticky },
        };

        if (auto it = map.find(SR_HASH_STR_VIEW(str)); it != map.end()) {
            return it->second;
        }
        return DEFAULT_CSS_POSITION;
    }

    static CSSBoxSizing StringToCSSBoxSizing(const std::string_view str) {
        static std::unordered_map<SRHashType, CSSBoxSizing> map = {
            { "content-box"_atom_hash, CSSBoxSizing::ContentBox },
            { "border-box"_atom_hash, CSSBoxSizing::BorderBox },
            { "inherit"_atom_hash, CSSBoxSizing::Inherit },
        };

        if (auto it = map.find(SR_HASH_STR_VIEW(str)); it != map.end()) {
            return it->second;
        }
        return DEFAULT_CSS_BOX_SIZING;
    }

    static CSSDisplay StringToCSSDisplay(const std::string_view str) {
        static std::unordered_map<SRHashType, CSSDisplay> map = {
            { "block"_atom_hash, CSSDisplay::Block },
            { "inline"_atom_hash, CSSDisplay::Inline },
            { "run-in"_atom_hash, CSSDisplay::RunIn },
            { "flow"_atom_hash, CSSDisplay::Flow },
            { "flow-root"_atom_hash, CSSDisplay::FlowRoot },
            { "table"_atom_hash, CSSDisplay::Table },
            { "flex"_atom_hash, CSSDisplay::Flex },
            { "grid"_atom_hash, CSSDisplay::Grid },
            { "ruby"_atom_hash, CSSDisplay::Ruby },
            { "block-flow"_atom_hash, CSSDisplay::BlockFlow },
            { "inline-table"_atom_hash, CSSDisplay::InlineTable },
            { "flex-run-in"_atom_hash, CSSDisplay::FlexRunIn },
            { "list-item"_atom_hash, CSSDisplay::ListItem },
            { "list-item-block"_atom_hash, CSSDisplay::ListItemBlock },
            { "list-item-inline"_atom_hash, CSSDisplay::ListItemInline },
            { "list-item-flow"_atom_hash, CSSDisplay::ListItemFlow },
            { "list-item-flow-root"_atom_hash, CSSDisplay::ListItemFlowRoot },
            { "list-item-block-flow"_atom_hash, CSSDisplay::ListItemBlockFlow },
            { "list-item-block-flow-root"_atom_hash, CSSDisplay::ListItemBlockFlowRoot },
            { "flow-list-item-block"_atom_hash, CSSDisplay::FlowListItemBlock },
            { "table-row-group"_atom_hash, CSSDisplay::TableRowGroup },
            { "table-header-group"_atom_hash, CSSDisplay::TableHeaderGroup },
            { "table-footer-group"_atom_hash, CSSDisplay::TableFooterGroup },
            { "table-row"_atom_hash, CSSDisplay::TableRow },
            { "table-cell"_atom_hash, CSSDisplay::TableCell },
            { "table-column-group"_atom_hash, CSSDisplay::TableColumnGroup },
            { "table-column"_atom_hash, CSSDisplay::TableColumn },
            { "table-caption"_atom_hash, CSSDisplay::TableCaption },
            { "ruby-base"_atom_hash, CSSDisplay::RubyBase },
            { "ruby-text"_atom_hash, CSSDisplay::RubyText },
            { "ruby-base-container"_atom_hash, CSSDisplay::RubyBaseContainer },
            { "ruby-text-container"_atom_hash, CSSDisplay::RubyTextContainer },
            { "contents"_atom_hash, CSSDisplay::Contents },
            { "none"_atom_hash, CSSDisplay::None },
            { "inline-block"_atom_hash, CSSDisplay::InlineBlock },
            { "inline-flex"_atom_hash, CSSDisplay::InlineFlex },
            { "inline-grid"_atom_hash, CSSDisplay::InlineGrid },
            { "inherit"_atom_hash, CSSDisplay::Inherit },
            { "initial"_atom_hash, CSSDisplay::Initial },
            { "unset"_atom_hash, CSSDisplay::Unset },
        };

        if (auto it = map.find(SR_HASH_STR_VIEW(str)); it != map.end()) {
            return it->second;
        }
        return DEFAULT_CSS_DISPLAY;
    }

    static SR_UTILS_NS::StringAtom CSSPositionToString(CSSPosition position) { 
        static std::array<SR_UTILS_NS::StringAtom, static_cast<uint32_t>(CSSPosition::Sticky) + 1> strings = {
            "absolute"_atom,
            "relative"_atom,
            "fixed"_atom,
            "static"_atom,
            "sticky"_atom,
        };

        if (static_cast<uint32_t>(position) < strings.size()) {
            return strings[static_cast<uint32_t>(position)];
        }
        SRHalt("Unknown CSSPosition value: %d", static_cast<uint32_t>(position));
        return CSSPositionToString(DEFAULT_CSS_POSITION);
    }

    static SR_UTILS_NS::StringAtom CSSBoxSizingToString(CSSBoxSizing boxSizing) { 
        static std::array<SR_UTILS_NS::StringAtom, static_cast<uint32_t>(CSSBoxSizing::Inherit) + 1> strings = {
            "content-box"_atom,
            "border-box"_atom,
            "inherit"_atom,
        };

        if (static_cast<uint32_t>(boxSizing) < strings.size()) {
            return strings[static_cast<uint32_t>(boxSizing)];
        }
        SRHalt("Unknown CSSBoxSizing value: %d", static_cast<uint32_t>(boxSizing));
        return CSSBoxSizingToString(DEFAULT_CSS_BOX_SIZING);
    }

    static SR_UTILS_NS::StringAtom CSSDisplayToString(CSSDisplay display) { 
        static std::array<SR_UTILS_NS::StringAtom, static_cast<uint32_t>(CSSDisplay::SIZE)> strings = {
            "block"_atom,
            "inline"_atom,
            "run-in"_atom,
            "flow"_atom,
            "flow-root"_atom,
            "table"_atom,
            "flex"_atom,
            "grid"_atom,
            "ruby"_atom,
            "block-flow"_atom,
            "inline-table"_atom,
            "flex-run-in"_atom,
            "list-item"_atom,
            "list-item-block"_atom,
            "list-item-inline"_atom,
            "list-item-flow"_atom,
            "list-item-flow-root"_atom,
            "list-item-block-flow"_atom,
            "list-item-block-flow-root"_atom,
            "flow-list-item-block"_atom,
            "table-row-group"_atom,
            "table-header-group"_atom,
            "table-footer-group"_atom,
            "table-row"_atom,
            "table-cell"_atom,
            "table-column-group"_atom,
            "table-column"_atom,
            "table-caption"_atom,
            "ruby-base"_atom,
            "ruby-text"_atom,
            "ruby-base-container"_atom,
            "ruby-text-container"_atom,
            "contents"_atom,
            "none"_atom,
            "inline-block"_atom,
            "inline-flex"_atom,
            "inline-grid"_atom,
            "inherit"_atom,
            "initial"_atom,
            "unset"_atom,
        };

        if (static_cast<uint32_t>(display) < strings.size()) {
            return strings[static_cast<uint32_t>(display)];
        }
        SRHalt("Unknown CSSDisplay value: %d", static_cast<uint32_t>(display));
        return CSSDisplayToString(DEFAULT_CSS_DISPLAY);
    }

    /*enum class Overflow : uint8_t {
        Visible, Hidden, Scroll, Auto,
    } overflow = Overflow::Visible;

    enum class TextAlign : uint8_t {
        Left, Right, Center, Justify,
    } textAlign = TextAlign::Left;

    enum class TextTransform : uint8_t {
        None, Uppercase, Lowercase, Capitalize,
    } textTransform = TextTransform::None;

    enum class TextDecoration : uint8_t {
        None, Underline, Overline, LineThrough,
    } textDecoration = TextDecoration::None;

    enum class FontStyle : uint8_t {
        Normal, Italic, Oblique,
    } fontStyle = FontStyle::Normal;

    enum class FontWeight : uint8_t {
        Normal, Bold, Bolder, Lighter,
    } fontWeight = FontWeight::Normal;

    enum class TextOverflow : uint8_t {
        Clip, Ellipsis,
    } textOverflow = TextOverflow::Clip;

    enum class WhiteSpace : uint8_t {
        Normal, Nowrap, Pre, PreLine, PreWrap,
    } whiteSpace = WhiteSpace::Normal;

    enum class Display : uint8_t {
        None, Block, Inline, InlineBlock, Flex, InlineFlex, Grid, InlineGrid,
    } display = Display::Block;

    enum class Position : uint8_t {
        Static, Relative, Absolute, Fixed, Sticky,
    } position = Position::Static;

    enum class Float : uint8_t {
        None, Left, Right,
    } floatType = Float::None;

    enum class Clear : uint8_t {
        None, Left, Right, Both,
    } clear = Clear::None;

    enum class Visibility : uint8_t {
        Visible, Hidden, Collapse,
    } visibility = Visibility::Visible;

    enum class Direction : uint8_t {
        Ltr, Rtl
    } direction = Direction::Ltr;

    enum class FlexDirection : uint8_t {
        Row, RowReverse, Column, ColumnReverse,
    } flexDirection = FlexDirection::Row;*/

    // CSSSizeValue fontSize;
    // CSSSizeValue lineHeight;
    // CSSSizeValue letterSpacing;
    // CSSSizeValue wordSpacing;
    // CSSSizeValue flex;
}

#endif //SR_COMMON_WEB_CSS_ENUMS_H
```


