

# File CSSSizeValue.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Web**](dir_70f8c8659136766207f9e88b26ae6fb0.md) **>** [**CSS**](dir_c67fdec84752b754610b5eee0005e4af.md) **>** [**CSSSizeValue.h**](CSSSizeValue_8h.md)

[Go to the documentation of this file](CSSSizeValue_8h.md)


```C++
//
// Created by Monika on 20.08.2024.
//


#ifndef SR_COMMON_WEB_CSS_SIZE_VALUE_H
#define SR_COMMON_WEB_CSS_SIZE_VALUE_H

#include <Utils/Web/CSS/CSSOptional.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Debug.h>

namespace SR_UTILS_NS::Web {
    struct CSSSizeValue {
        enum class Unit : uint8_t {
            Px,
            Percent,
            Dpi,
            Deg,
        } unit = Unit::Px;

        bool autoValue = false;

        CSSSizeValue() = default;

        CSSSizeValue(const int32_t px) : px(static_cast<int16_t>(px)) { } 
        CSSSizeValue(const int16_t px) : px(px) { } 
        CSSSizeValue(const float_t percent) : unit(Unit::Percent), percent(percent) { } 
        CSSSizeValue(const float_t v, const Unit unit) : unit(unit) {
            switch (unit) {
                case Unit::Px: px = static_cast<int16_t>(v); break;
                case Unit::Percent: percent = v; break;
                case Unit::Dpi: dpi = static_cast<int16_t>(v); break;
                case Unit::Deg: deg = v; break;
                default: SRHalt("Unknown CSS size unit!"); break;
            }
        }

        virtual ~CSSSizeValue() = default;

        static std::optional<CSSSizeValue> Parse(std::string_view value) {
            CSSSizeValue result;
            if (value.ends_with("px")) {
                result.SetPx(SR_UTILS_NS::LexicalCast<uint16_t>(value.substr(0, value.size() - 2)));
            } else if (value.ends_with("%")) {
                result.SetPercent(SR_UTILS_NS::LexicalCast<float_t>(value.substr(0, value.size() - 1)));
            } else if (value.ends_with("dpi")) {
                result.SetDpi(SR_UTILS_NS::LexicalCast<uint16_t>(value.substr(0, value.size() - 3)));
            } else if (value.ends_with("deg")) {
                result.SetDeg(SR_UTILS_NS::LexicalCast<float_t>(value.substr(0, value.size() - 1)));
            } else if (value == "0") {
                result.SetPx(0);
            } else if (value == "auto") {
                result.autoValue = true;
            }
            else {
                SR_ERROR("Unknown CSS size value: {}", value.data());
                return {};
            }
            return result;
        }

        static void Parse(CSSSizeValue& result, std::string_view value) {
            if (auto&& parsed = Parse(value); parsed.has_value()) {
                result = parsed.value();
            }
        }

        void SetDpi(const int16_t dpi) { unit = Unit::Dpi; this->dpi = dpi; OnChanged(); }
        void SetPx(const int16_t px) { unit = Unit::Px; this->px = px; OnChanged(); }
        void SetPercent(const float_t percent) { unit = Unit::Percent; this->percent = percent; OnChanged(); }
        void SetDeg(const float_t deg) { unit = Unit::Deg; this->deg = deg; OnChanged(); }

        SR_NODISCARD std::string ToString() const {
            switch (unit) {
                case Unit::Px: return SR_FORMAT("{}px", px);
                case Unit::Percent: return SR_FORMAT("{}%", percent);
                case Unit::Dpi: return SR_FORMAT("{}dpi", dpi);
                case Unit::Deg: return SR_FORMAT("{}deg", deg);
            }
            return {};
        }

        SR_NODISCARD uint16_t GetPx() const { return SRVerify(unit == Unit::Px) ? px : 0; }
        SR_NODISCARD float_t GetPercent() const { return SRVerify(unit == Unit::Percent) ? percent : 0; }
        SR_NODISCARD uint16_t GetDpi() const { return SRVerify(unit == Unit::Dpi) ? dpi : 0; }
        SR_NODISCARD float_t GetDeg() const { return SRVerify(unit == Unit::Deg) ? deg : 0; }

        SR_NODISCARD Unit GetUnit() const { return unit; }

        SR_NODISCARD SR_MATH_NS::Unit CalculateValue(const SR_MATH_NS::Unit& parentPx) const {
            switch (unit) {
                case Unit::Px: return px;
                case Unit::Percent: return parentPx * percent / 100;
                case Unit::Dpi: return dpi;
                case Unit::Deg: return deg;
            }
            return 0;
        }

        union {
            int16_t px = 0;
            float_t percent;
            int16_t dpi;
            float_t deg;
        };

    protected:
        virtual void OnChanged() { }

    };

    using CSSOptionalSizeValue = CSSOptional<CSSSizeValue>;
}

#endif //SR_COMMON_WEB_CSS_SIZE_VALUE_H
```


