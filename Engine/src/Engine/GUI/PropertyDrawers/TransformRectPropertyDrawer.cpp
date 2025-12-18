//
// Created by Monika on 18.12.2025.
//

#include <Engine/GUI/PropertyDrawers/TransformRectPropertyDrawer.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/EditorGUI.h>

#include <Graphics/GUI/ImmediateGUI.h>

#include <Utils/ECS/TransformRect.h>
#include <Utils/ECS/SceneObject.h>
#include <Utils/ECS/Component.h>

#include <Codegen/TransformRectPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    namespace {
        enum class AnchorPreset {
            TopLeft,
            TopCenter,
            TopRight,
            TopStretch,
            MiddleLeft,
            MiddleCenter,
            MiddleRight,
            MiddleStretch,
            BottomLeft,
            BottomCenter,
            BottomRight,
            BottomStretch,
            StretchLeft,
            StretchCenter,
            StretchRight,
            StretchStretch,
            Custom
        };

        struct PresetData {
            SR_MATH_NS::FVector2 anchorMin;
            SR_MATH_NS::FVector2 anchorMax;
            SR_MATH_NS::FVector2 pivot;
        };

        constexpr PresetData PRESETS[] = {
            { {0.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 1.0f} }, // TopLeft
            { {0.5f, 1.0f}, {0.5f, 1.0f}, {0.5f, 1.0f} }, // TopCenter
            { {1.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f} }, // TopRight
            { {0.0f, 1.0f}, {1.0f, 1.0f}, {0.5f, 1.0f} }, // TopStretch
            { {0.0f, 0.5f}, {0.0f, 0.5f}, {0.0f, 0.5f} }, // MiddleLeft
            { {0.5f, 0.5f}, {0.5f, 0.5f}, {0.5f, 0.5f} }, // MiddleCenter
            { {1.0f, 0.5f}, {1.0f, 0.5f}, {1.0f, 0.5f} }, // MiddleRight
            { {0.0f, 0.5f}, {1.0f, 0.5f}, {0.5f, 0.5f} }, // MiddleStretch
            { {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} }, // BottomLeft
            { {0.5f, 0.0f}, {0.5f, 0.0f}, {0.5f, 0.0f} }, // BottomCenter
            { {1.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 0.0f} }, // BottomRight
            { {0.0f, 0.0f}, {1.0f, 0.0f}, {0.5f, 0.0f} }, // BottomStretch
            { {0.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.5f} }, // StretchLeft
            { {0.5f, 0.0f}, {0.5f, 1.0f}, {0.5f, 0.5f} }, // StretchCenter
            { {1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 0.5f} }, // StretchRight
            { {0.0f, 0.0f}, {1.0f, 1.0f}, {0.5f, 0.5f} }, // StretchStretch
        };

        constexpr const char* PRESET_ROW_LABELS[] = { "", "top", "middle", "bottom", "stretch" };
        constexpr const char* PRESET_COL_LABELS[] = { "custom", "left", "center", "right", "stretch" };

        AnchorPreset GetCurrentPreset(const SR_UTILS_NS::RectAnchors& anchors, const SR_MATH_NS::FVector2& pivot) {
            for (int i = 0; i < 16; ++i) {
                const float epsilon = 0.001f;
                if (std::abs(anchors.min.x - PRESETS[i].anchorMin.x) < epsilon &&
                    std::abs(anchors.min.y - PRESETS[i].anchorMin.y) < epsilon &&
                    std::abs(anchors.max.x - PRESETS[i].anchorMax.x) < epsilon &&
                    std::abs(anchors.max.y - PRESETS[i].anchorMax.y) < epsilon &&
                    std::abs(pivot.x - PRESETS[i].pivot.x) < epsilon &&
                    std::abs(pivot.y - PRESETS[i].pivot.y) < epsilon) {
                    return static_cast<AnchorPreset>(i);
                }
            }
            return AnchorPreset::Custom;
        }

        int GetPresetGridIndex(AnchorPreset preset) {
            if (preset == AnchorPreset::Custom) return 0;
            
            // Map presets to grid: row * 5 + col
            // Row 0: custom row (empty)
            // Row 1: top (0-3)
            // Row 2: middle (4-7)
            // Row 3: bottom (8-11)
            // Row 4: stretch (12-15)
            
            int presetIdx = static_cast<int>(preset);
            int row = (presetIdx / 4) + 1;
            int col = (presetIdx % 4) + 1;
            return row * 5 + col;
        }

        AnchorPreset GetPresetFromGridIndex(int gridIdx) {
            int row = gridIdx / 5;
            int col = gridIdx % 5;
            
            if (row == 0 || col == 0) return AnchorPreset::Custom;
            
            int presetIdx = (row - 1) * 4 + (col - 1);
            if (presetIdx >= 0 && presetIdx < 16) {
                return static_cast<AnchorPreset>(presetIdx);
            }
            return AnchorPreset::Custom;
        }

        uint32_t ColorToU32(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
            return (static_cast<uint32_t>(a) << 24) | (static_cast<uint32_t>(b) << 16) | 
                   (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(r);
        }

        void DrawPresetIcon(void* pDrawList, const SR_MATH_NS::FVector2& pos, const SR_MATH_NS::FVector2& size, 
                           const PresetData& preset, bool isSelected, bool isHovered) {
            const float padding = 4.0f;
            const SR_MATH_NS::FVector2 innerSize = size - SR_MATH_NS::FVector2(padding * 2, padding * 2);
            const SR_MATH_NS::FVector2 innerPos = pos + SR_MATH_NS::FVector2(padding, padding);
            
            // Outer rect (parent)
            const uint32_t outerColor = isSelected ? ColorToU32(255, 255, 255, 255) : ColorToU32(125, 125, 125, 255);
            SR_GRAPH_GUI_NS::Immediate::DrawListAddRect(
                pDrawList,
                pos,
                pos + size,
                outerColor, 0.0f, 1.5f
            );
            
            // Calculate inner rect position based on anchors
            const SR_MATH_NS::FVector2 anchorMinPos = innerPos + SR_MATH_NS::FVector2(
                preset.anchorMin.x * innerSize.x,
                (1.0f - preset.anchorMax.y) * innerSize.y
            );
            const SR_MATH_NS::FVector2 anchorMaxPos = innerPos + SR_MATH_NS::FVector2(
                preset.anchorMax.x * innerSize.x,
                (1.0f - preset.anchorMin.y) * innerSize.y
            );
            
            // Inner rect (element)
            const uint32_t innerColor = isHovered ? ColorToU32(100, 150, 255, 200) : ColorToU32(100, 150, 255, 150);
            SR_GRAPH_GUI_NS::Immediate::DrawListAddRectFilled(
                pDrawList,
                anchorMinPos,
                anchorMaxPos,
                innerColor
            );
            
            // Draw anchor lines (red)
            const uint32_t anchorColor = ColorToU32(255, 0, 0, 255);
            const float lineThickness = 1.5f;
            
            // Vertical lines
            if (preset.anchorMin.x == preset.anchorMax.x) {
                float x = innerPos.x + preset.anchorMin.x * innerSize.x;
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(
                    pDrawList,
                    SR_MATH_NS::FVector2(x, innerPos.y),
                    SR_MATH_NS::FVector2(x, innerPos.y + innerSize.y),
                    anchorColor, lineThickness
                );
            } else {
                // Draw left and right lines
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(
                    pDrawList,
                    SR_MATH_NS::FVector2(innerPos.x + preset.anchorMin.x * innerSize.x, innerPos.y),
                    SR_MATH_NS::FVector2(innerPos.x + preset.anchorMin.x * innerSize.x, innerPos.y + innerSize.y),
                    anchorColor, lineThickness
                );
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(
                    pDrawList,
                    SR_MATH_NS::FVector2(innerPos.x + preset.anchorMax.x * innerSize.x, innerPos.y),
                    SR_MATH_NS::FVector2(innerPos.x + preset.anchorMax.x * innerSize.x, innerPos.y + innerSize.y),
                    anchorColor, lineThickness
                );
            }
            
            // Horizontal lines
            if (preset.anchorMin.y == preset.anchorMax.y) {
                float y = innerPos.y + (1.0f - preset.anchorMin.y) * innerSize.y;
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(
                    pDrawList,
                    SR_MATH_NS::FVector2(innerPos.x, y),
                    SR_MATH_NS::FVector2(innerPos.x + innerSize.x, y),
                    anchorColor, lineThickness
                );
            } else {
                // Draw top and bottom lines
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(
                    pDrawList,
                    SR_MATH_NS::FVector2(innerPos.x, innerPos.y + (1.0f - preset.anchorMax.y) * innerSize.y),
                    SR_MATH_NS::FVector2(innerPos.x + innerSize.x, innerPos.y + (1.0f - preset.anchorMax.y) * innerSize.y),
                    anchorColor, lineThickness
                );
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(
                    pDrawList,
                    SR_MATH_NS::FVector2(innerPos.x, innerPos.y + (1.0f - preset.anchorMin.y) * innerSize.y),
                    SR_MATH_NS::FVector2(innerPos.x + innerSize.x, innerPos.y + (1.0f - preset.anchorMin.y) * innerSize.y),
                    anchorColor, lineThickness
                );
            }
            
            // Draw pivot (yellow square)
            const SR_MATH_NS::FVector2 pivotPos = anchorMinPos + SR_MATH_NS::FVector2(
                preset.pivot.x * (anchorMaxPos.x - anchorMinPos.x),
                preset.pivot.y * (anchorMaxPos.y - anchorMinPos.y)
            );
            const float pivotSize = 4.0f;
            SR_GRAPH_GUI_NS::Immediate::DrawListAddRectFilled(
                pDrawList,
                pivotPos - SR_MATH_NS::FVector2(pivotSize, pivotSize),
                pivotPos + SR_MATH_NS::FVector2(pivotSize, pivotSize),
                ColorToU32(255, 255, 0, 255)
            );
            
            // Draw stretch arrows if needed
            if (preset.anchorMin.x != preset.anchorMax.x) {
                // Horizontal stretch arrow
                const float arrowY = (anchorMinPos.y + anchorMaxPos.y) * 0.5f;
                const float arrowLen = 8.0f;
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(
                    pDrawList,
                    SR_MATH_NS::FVector2(anchorMinPos.x + 2, arrowY),
                    SR_MATH_NS::FVector2(anchorMinPos.x + 2 + arrowLen, arrowY),
                    ColorToU32(100, 150, 255, 255), 1.5f
                );
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(
                    pDrawList,
                    SR_MATH_NS::FVector2(anchorMaxPos.x - 2, arrowY),
                    SR_MATH_NS::FVector2(anchorMaxPos.x - 2 - arrowLen, arrowY),
                    ColorToU32(100, 150, 255, 255), 1.5f
                );
            }
            if (preset.anchorMin.y != preset.anchorMax.y) {
                // Vertical stretch arrow
                const float arrowX = (anchorMinPos.x + anchorMaxPos.x) * 0.5f;
                const float arrowLen = 8.0f;
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(
                    pDrawList,
                    SR_MATH_NS::FVector2(arrowX, anchorMinPos.y + 2),
                    SR_MATH_NS::FVector2(arrowX, anchorMinPos.y + 2 + arrowLen),
                    ColorToU32(100, 150, 255, 255), 1.5f
                );
                SR_GRAPH_GUI_NS::Immediate::DrawListAddLine(
                    pDrawList,
                    SR_MATH_NS::FVector2(arrowX, anchorMaxPos.y - 2),
                    SR_MATH_NS::FVector2(arrowX, anchorMaxPos.y - 2 - arrowLen),
                    ColorToU32(100, 150, 255, 255), 1.5f
                );
            }
        }

        bool DrawPresetButton(const char* id, const SR_MATH_NS::FVector2& size, const PresetData& preset, bool isSelected) {
            void* pWindow = SR_GRAPH_GUI_NS::Immediate::GetCurrentWindow();
            void* pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList(pWindow);
            SR_MATH_NS::FVector2 cursorPos = SR_GRAPH_GUI_NS::Immediate::GetCursorScreenPos();
            
            // Draw icon
            DrawPresetIcon(pDrawList, cursorPos, size, preset, isSelected, false);
            
            // Invisible button for interaction
            SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::FramePadding, SR_MATH_NS::FVector2(0, 0));
            //SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Button, SR_MATH_NS::FColor(0, 0, 0, 0));
            //SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonHovered, SR_MATH_NS::FColor(0, 0, 0, 0));
            //SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonActive, SR_MATH_NS::FColor(0, 0, 0, 0));
            
            bool clicked = SR_GRAPH_GUI_NS::Immediate::Button(id, size);
            
            //SR_GRAPH_GUI_NS::Immediate::PopStyleColor(3);
            SR_GRAPH_GUI_NS::Immediate::PopStyleVar();
            
            return clicked;
        }

        void DrawPresetPopup(SR_UTILS_NS::TransformRect* pTransformRect, PropertyDrawerFeedback& feedback) {
            const char* popupId = "##AnchorPresetsPopup";
            
            if (SR_GRAPH_GUI_NS::Immediate::BeginPopup(popupId)) {
                // SR_GRAPH_GUI_NS::Immediate::Text("Anchor Presets");
                // SR_GRAPH_GUI_NS::Immediate::Separator();
                // SR_GRAPH_GUI_NS::Immediate::Text("Shift: Also set pivot");
                // SR_GRAPH_GUI_NS::Immediate::Text("Alt: Also set position");
                
                AnchorPreset currentPreset = GetCurrentPreset(pTransformRect->GetAnchors(), pTransformRect->GetPivot());
                int currentGridIdx = GetPresetGridIndex(currentPreset);
                
                const float buttonSize = 80.0f;
                const float spacing = 2.0f;
                
                // Draw grid
                for (int row = 0; row < 5; ++row) {
                    for (int col = 0; col < 5; ++col) {
                        SR_GRAPH_GUI_NS::Immediate::PushID(row * 5 + col);
                        
                        int gridIdx = row * 5 + col;
                        bool isSelected = (gridIdx == currentGridIdx);
                        
                        if (row == 0 || col == 0) {
                            // Header cells

                            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Button, SR_MATH_NS::FColor(0, 0, 0, 0));
                            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonHovered, SR_MATH_NS::FColor(0, 0, 0, 0));
                            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonActive, SR_MATH_NS::FColor(0, 0, 0, 0));

                            if (row == 0 && col > 0) {
                                SR_GRAPH_GUI_NS::Immediate::Button(PRESET_COL_LABELS[col], SR_MATH_NS::FVector2(buttonSize, buttonSize));
                            } else if (col == 0 && row > 0) {
                                SR_GRAPH_GUI_NS::Immediate::Button(PRESET_ROW_LABELS[row], SR_MATH_NS::FVector2(buttonSize, buttonSize));
                            } else {
                                SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(buttonSize, buttonSize));
                            }

                            SR_GRAPH_GUI_NS::Immediate::PopStyleColor(3);
                        } else {
                            // Preset buttons
                            AnchorPreset preset = GetPresetFromGridIndex(gridIdx);
                            if (preset != AnchorPreset::Custom) {
                                char buttonId[32];
                                snprintf(buttonId, sizeof(buttonId), "##preset_%d", gridIdx);
                                
                                if (DrawPresetButton(buttonId, SR_MATH_NS::FVector2(buttonSize, buttonSize), 
                                                    PRESETS[static_cast<int>(preset)], isSelected)) {
                                    SR_UTILS_NS::RectAnchors newAnchors;
                                    newAnchors.min = PRESETS[static_cast<int>(preset)].anchorMin;
                                    newAnchors.max = PRESETS[static_cast<int>(preset)].anchorMax;
                                    pTransformRect->SetAnchors(newAnchors);
                                    pTransformRect->SetPivot(PRESETS[static_cast<int>(preset)].pivot);
                                    feedback.isChanged = true;
                                    SR_GRAPH_GUI_NS::Immediate::CloseCurrentPopup();
                                }
                            } else {
                                SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(buttonSize, buttonSize));
                            }
                        }
                        
                        if (col < 4) {
                            SR_GRAPH_GUI_NS::Immediate::SameLine(0, spacing);
                        }
                        
                        SR_GRAPH_GUI_NS::Immediate::PopID();
                    }
                }
                
                SR_GRAPH_GUI_NS::Immediate::EndPopup();
            }
        }

        void DrawVector3Field(const char* label, SR_MATH_NS::FVector3& value, float_t dragSpeed, float_t fieldWidth, float_t axisButtonWidth) {
            SR_GRAPH_GUI_NS::Immediate::PushID(label);

            constexpr std::array<const char*, 3> labels = { "X", "Y", "Z" };
            static const std::array<SR_MATH_NS::FColor, 3> colors = {
                SR_MATH_NS::FColor(0.8f, 0.1f, 0.15f, 1.0f), // red
                SR_MATH_NS::FColor(0.2f, 0.7f, 0.2f, 1.0f), // green
                SR_MATH_NS::FColor(0.1f, 0.3f, 0.8f, 1.0f), // blue
            };

            SR_GRAPH_GUI_NS::Immediate::Text(label);
            SR_GRAPH_GUI_NS::Immediate::SameLine();

            const float_t partItemWidth = (fieldWidth / 3.0f) - axisButtonWidth;
            const SR_MATH_NS::FVector2 buttonSize = { axisButtonWidth, 0.0f };

            float_t v[3] = { value.x, value.y, value.z };
            bool valueChanged = false;

            for (uint8_t i = 0; i < 3; ++i) {
                SR_GRAPH_GUI_NS::Immediate::PushID(i);

                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Button, colors[i]);
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonHovered, colors[i] + SR_MATH_NS::FColor(0.1f, 0.1f, 0.1f, 0.0f));
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonActive, colors[i] + SR_MATH_NS::FColor(0.2f, 0.2f, 0.2f, 0.0f));

                if (SR_GRAPH_GUI_NS::Immediate::Button(labels[i], buttonSize)) {
                    v[i] = 0.0f;
                    valueChanged = true;
                }

                SR_GRAPH_GUI_NS::Immediate::PopStyleColor(3);
                SR_GRAPH_GUI_NS::Immediate::SameLine();

                SR_GRAPH_GUI_NS::Immediate::PushItemWidth(partItemWidth);
                if (SR_GRAPH_GUI_NS::Immediate::DragFloat("", &v[i], dragSpeed)) {
                    valueChanged = true;
                }
                SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

                if (i < 2) {
                    SR_GRAPH_GUI_NS::Immediate::SameLine();
                }

                SR_GRAPH_GUI_NS::Immediate::PopID();
            }

            if (valueChanged) {
                value = SR_MATH_NS::FVector3(v[0], v[1], v[2]);
            }

            SR_GRAPH_GUI_NS::Immediate::PopID();
        }

        void DrawVector2Field(const char* label, SR_MATH_NS::FVector2& value, float_t dragSpeed, float_t fieldWidth, float_t axisButtonWidth) {
            SR_GRAPH_GUI_NS::Immediate::PushID(label);

            constexpr std::array<const char*, 2> labels = { "X", "Y" };
            static const std::array<SR_MATH_NS::FColor, 2> colors = {
                SR_MATH_NS::FColor(0.8f, 0.1f, 0.15f, 1.0f), // red
                SR_MATH_NS::FColor(0.2f, 0.7f, 0.2f, 1.0f), // green
            };

            SR_GRAPH_GUI_NS::Immediate::Text(label);
            SR_GRAPH_GUI_NS::Immediate::SameLine();

            const float_t partItemWidth = (fieldWidth / 2.0f) - axisButtonWidth;
            const SR_MATH_NS::FVector2 buttonSize = { axisButtonWidth, 0.0f };

            float_t v[2] = { value.x, value.y };
            bool valueChanged = false;

            for (uint8_t i = 0; i < 2; ++i) {
                SR_GRAPH_GUI_NS::Immediate::PushID(i);

                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Button, colors[i]);
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonHovered, colors[i] + SR_MATH_NS::FColor(0.1f, 0.1f, 0.1f, 0.0f));
                SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonActive, colors[i] + SR_MATH_NS::FColor(0.2f, 0.2f, 0.2f, 0.0f));

                if (SR_GRAPH_GUI_NS::Immediate::Button(labels[i], buttonSize)) {
                    v[i] = 0.0f;
                    valueChanged = true;
                }

                SR_GRAPH_GUI_NS::Immediate::PopStyleColor(3);
                SR_GRAPH_GUI_NS::Immediate::SameLine();

                SR_GRAPH_GUI_NS::Immediate::PushItemWidth(partItemWidth);
                if (SR_GRAPH_GUI_NS::Immediate::DragFloat("", &v[i], dragSpeed)) {
                    valueChanged = true;
                }
                SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

                if (i < 1) {
                    SR_GRAPH_GUI_NS::Immediate::SameLine();
                }

                SR_GRAPH_GUI_NS::Immediate::PopID();
            }

            if (valueChanged) {
                value = SR_MATH_NS::FVector2(v[0], v[1]);
            }

            SR_GRAPH_GUI_NS::Immediate::PopID();
        }
    }

    bool TransformRectEditDragFloat(const char* label, const SR_MATH_NS::FVector2& buttonSize, const SR_MATH_NS::FColor& color, float& value, float dragSpeed, float fieldWidth) {
        SR_GRAPH_GUI_NS::Immediate::PushID(label);

        bool changed = false;
        if (SR_GRAPH_GUI_NS::Immediate::ButtonColored(label, color, buttonSize)) {
            value = 0.f;
            changed = true;
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();
        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(fieldWidth);
        changed |= SR_GRAPH_GUI_NS::Immediate::DragFloat("", &value, dragSpeed);
        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        return changed;
    }

    TransformRectPropertyDrawer::TransformRectPropertyDrawer()
        : Super()
    {
        m_anchorsDrawer = SRNew<ObjectPropertyDrawer>();
    }

    PropertyDrawerFeedback TransformRectPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        auto&& pTransformRect = dynamic_cast<SR_UTILS_NS::TransformRect *>(value.GetSRClass());
        if (!pTransformRect) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map value!");
            return feedback;
        }

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pOwner);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetPropertyName().ToCStr());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2(0, 2));

        const float_t dragSpeed = context.GetEditorParams().GetDragSpeed();
        const float_t presetButtonWidth = 80.0f * (context.lineHeight / 18.f);
        const float_t presetButtonHeight = presetButtonWidth;

        {
            AnchorPreset currentPreset = GetCurrentPreset(pTransformRect->GetAnchors(), pTransformRect->GetPivot());

            // Draw current preset icon as button
            char presetButtonId[64];
            snprintf(presetButtonId, sizeof(presetButtonId), "##PresetButton_%p", pTransformRect);

            if (currentPreset != AnchorPreset::Custom) {
                if (DrawPresetButton(presetButtonId, SR_MATH_NS::FVector2(presetButtonWidth, presetButtonHeight), PRESETS[static_cast<int>(currentPreset)], true)) {
                    SR_GRAPH_GUI_NS::Immediate::OpenPopup("##AnchorPresetsPopup");
                }
            } else {
                // Custom preset - show text button
                if (SR_GRAPH_GUI_NS::Immediate::Button("Custom", SR_MATH_NS::FVector2(presetButtonWidth, presetButtonHeight))) {
                    SR_GRAPH_GUI_NS::Immediate::OpenPopup("##AnchorPresetsPopup");
                }
            }

            DrawPresetPopup(pTransformRect, feedback);
        }

        const bool anchorsTogetherX = pTransformRect->AreAnchorsTogetherX();
        const bool anchorsTogetherY = pTransformRect->AreAnchorsTogetherY();

        static const auto redColor = SR_MATH_NS::FColor(0.8f, 0.1f, 0.15f, 1.0f);
        static const auto greenColor = SR_MATH_NS::FColor(0.2f, 0.7f, 0.2f, 1.0f);
        static const auto blueColor = SR_MATH_NS::FColor(0.1f, 0.3f, 0.8f, 1.0f);
        static const auto whiteColor = SR_MATH_NS::FColor(0.6f, 0.6f, 0.6f, 1.0f);

        const SR_MATH_NS::FVector2 smallButtonSize = {context.lineHeight, context.fieldHeight};
        const SR_MATH_NS::FVector2 buttonSize = {context.lineHeight * 2.2f, context.fieldHeight};
        const float_t threeSegmentWidth = SR_MAX((((context.fieldTitleWidth + context.fieldWidth) - presetButtonWidth) - buttonSize.x * 3.f) / 3.0f, 0.f);
        const float_t threeSegmentMainWidth = SR_MAX((((context.fieldTitleWidth + context.fieldWidth) - presetButtonWidth) - smallButtonSize.x * 3.f) / 3.0f, 0.f);

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        SR_GRAPH_GUI_NS::Immediate::BeginGroup();
        {
            /// ========================================= Position / Left-Top ==========================================

            auto&& anchoredPos = pTransformRect->GetTranslation();
            auto&& offsetMin = pTransformRect->GetOffsetMin();
            auto&& offsetMax = pTransformRect->GetOffsetMax();
            auto&& size = pTransformRect->GetSize();

            float_t posXLeftValue = anchorsTogetherX ? anchoredPos.x : offsetMin.x;
            if (TransformRectEditDragFloat(anchorsTogetherX ? "Pos X" : "Left", buttonSize, anchorsTogetherX ? redColor : whiteColor, posXLeftValue, dragSpeed, threeSegmentWidth)) {
                feedback.isChanged = true;
                if (anchorsTogetherX) {
                    anchoredPos.x = posXLeftValue;
                    pTransformRect->SetTranslation(anchoredPos);
                }
                else {
                    offsetMin.x = posXLeftValue;
                    pTransformRect->SetOffsetMin(offsetMin);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            float_t posYTopValue = anchorsTogetherY ? anchoredPos.y : offsetMax.y;
            if (TransformRectEditDragFloat(anchorsTogetherY ? "Pos Y" : "Top", buttonSize, anchorsTogetherY ? greenColor : whiteColor, posYTopValue, dragSpeed, threeSegmentWidth)) {
                feedback.isChanged = true;
                if (anchorsTogetherY) {
                    anchoredPos.y = posYTopValue;
                    pTransformRect->SetTranslation(anchoredPos);
                }
                else {
                    offsetMax.y = posYTopValue;
                    pTransformRect->SetOffsetMax(offsetMax);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            float_t posZValue = anchoredPos.z;
            if (TransformRectEditDragFloat("Pos Z", buttonSize, blueColor, posZValue, dragSpeed, threeSegmentWidth)) {
                feedback.isChanged = true;
                anchoredPos.z = posZValue;
                pTransformRect->SetTranslation(anchoredPos);
            }

            /// ========================================= Size / Right-Bottom ==========================================

            float_t widthRightValue = anchorsTogetherX ? size.x : offsetMax.x;
            if (TransformRectEditDragFloat(anchorsTogetherX ? "Width" : "Right", buttonSize, anchorsTogetherX ? redColor : whiteColor, widthRightValue, dragSpeed, threeSegmentWidth)) {
                feedback.isChanged = true;
                if (anchorsTogetherX) {
                    size.x = widthRightValue;
                    pTransformRect->SetSize(size);
                }
                else {
                    offsetMax.x = widthRightValue;
                    pTransformRect->SetOffsetMax(offsetMax);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            float_t heightBottomValue = anchorsTogetherY ? size.y : offsetMin.y;
            if (TransformRectEditDragFloat(anchorsTogetherY ? "Height" : "Bottom", buttonSize, anchorsTogetherY ? greenColor : whiteColor, heightBottomValue, dragSpeed, threeSegmentWidth)) {
                feedback.isChanged = true;
                if (anchorsTogetherY) {
                    size.y = heightBottomValue;
                    pTransformRect->SetSize(size);
                }
                else {
                    offsetMin.y = heightBottomValue;
                    pTransformRect->SetOffsetMin(offsetMin);
                }
            }
        }
        SR_GRAPH_GUI_NS::Immediate::EndGroup();

        {
            SR_GRAPH_GUI_NS::Immediate::PushID("Rotation");
            SR_GRAPH_GUI_NS::Immediate::Button("Rotation", SR_MATH_NS::FVector2(presetButtonWidth, context.fieldHeight));
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_MATH_NS::FVector3 rotation = pTransformRect->GetRotation();
            const SR_MATH_NS::FVector3 oldRotation = rotation;
            TransformRectEditDragFloat("X", smallButtonSize, redColor, rotation.x, dragSpeed, threeSegmentMainWidth);
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            TransformRectEditDragFloat("Y", smallButtonSize, greenColor, rotation.y, dragSpeed, threeSegmentMainWidth);
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            TransformRectEditDragFloat("Z", smallButtonSize, blueColor, rotation.z, dragSpeed, threeSegmentMainWidth);
            if (rotation != oldRotation) {
                pTransformRect->SetRotation(rotation);
                feedback.isChanged = true;
            }
            SR_GRAPH_GUI_NS::Immediate::PopID();
        }

        {
            SR_GRAPH_GUI_NS::Immediate::PushID("Scale");
            SR_GRAPH_GUI_NS::Immediate::Button("Scale", SR_MATH_NS::FVector2(presetButtonWidth, context.fieldHeight));
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_MATH_NS::FVector3 scale = pTransformRect->GetScale();
            const SR_MATH_NS::FVector3 oldScale = scale;
            TransformRectEditDragFloat("X", smallButtonSize, redColor, scale.x, dragSpeed, threeSegmentMainWidth);
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            TransformRectEditDragFloat("Y", smallButtonSize, greenColor, scale.y, dragSpeed, threeSegmentMainWidth);
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            TransformRectEditDragFloat("Z", smallButtonSize, blueColor, scale.z, dragSpeed, threeSegmentMainWidth);
            if (scale != oldScale) {
                pTransformRect->SetScale(scale);
                feedback.isChanged = true;
            }
            SR_GRAPH_GUI_NS::Immediate::PopID();
        }

        {
            SR_GRAPH_GUI_NS::Immediate::PushID("Pivot");
            SR_GRAPH_GUI_NS::Immediate::Button("Pivot", SR_MATH_NS::FVector2(presetButtonWidth, context.fieldHeight));
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_MATH_NS::FVector2 pivot = pTransformRect->GetPivot();
            const SR_MATH_NS::FVector2 oldPivot = pivot;
            TransformRectEditDragFloat("X", smallButtonSize, redColor, pivot.x, dragSpeed, threeSegmentMainWidth);
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            TransformRectEditDragFloat("Y", smallButtonSize, greenColor, pivot.y, dragSpeed, threeSegmentMainWidth);
            if (pivot != oldPivot) {
                pTransformRect->SetPivot(pivot);
                feedback.isChanged = true;
            }
            SR_GRAPH_GUI_NS::Immediate::PopID();
        }

        m_lastAnchors = pTransformRect->GetAnchors();
        auto&& anchorsValue = SR_UTILS_NS::Reflection::Value::CreateRef(m_lastAnchors);

        PropertyDrawerContext propertyContext = context;
        const float_t totalFieldWidth = context.fieldTitleWidth + context.fieldWidth + context.GetArrowWidth();

        propertyContext.pProperty = nullptr;
        propertyContext.pValue = &anchorsValue;
        propertyContext.customDisplayName = "Anchors";
        propertyContext.fieldTitleWidth = 0.f;
        propertyContext.fieldWidth = totalFieldWidth;
        propertyContext.noHeader = false;
        propertyContext.openedByDefault = true;

        if (auto&& anchorFeedback = m_anchorsDrawer->Draw(propertyContext); anchorFeedback.isChanged || anchorFeedback.isDrag) {
            pTransformRect->SetAnchors(*anchorsValue.TryCast<SR_UTILS_NS::RectAnchors>());
            feedback.isChanged = true;
        }


        /*// Rect section
        {
            SR_GRAPH_GUI_NS::Immediate::Text("Rect");

            if (anchorsTogetherX && anchorsTogetherY) {
                // Show Position X, Y and Width, Height
                SR_MATH_NS::FVector2 anchoredPos = pTransformRect->GetAnchoredPosition();
                SR_MATH_NS::FVector2 size = pTransformRect->GetSize();
                const SR_MATH_NS::FVector2 oldAnchoredPos = anchoredPos;
                const SR_MATH_NS::FVector2 oldSize = size;

                DrawVector2Field("Pos X, Y", anchoredPos, dragSpeed, fieldWidth, axisButtonWidth);
                DrawVector2Field("Width, Height", size, dragSpeed, fieldWidth, axisButtonWidth);

                if (anchoredPos != oldAnchoredPos) {
                    SR_MATH_NS::FVector3 newTranslation = pTransformRect->GetTranslation();
                    newTranslation.x = anchoredPos.x;
                    newTranslation.y = anchoredPos.y;
                    pTransformRect->SetTranslation(newTranslation);
                    feedback.isChanged = true;
                }

                if (size != oldSize) {
                    pTransformRect->SetSize(size);
                    feedback.isChanged = true;
                }
            }
            else {
                // Show Left, Top, Right, Bottom
                SR_MATH_NS::FVector2 offsetMin = pTransformRect->GetOffsetMin();
                SR_MATH_NS::FVector2 offsetMax = pTransformRect->GetOffsetMax();

                constexpr std::array<const char*, 4> labels = { "Left", "Top", "Right", "Bottom" };
                static const std::array<SR_MATH_NS::FColor, 4> colors = {
                    SR_MATH_NS::FColor(0.6f, 0.6f, 0.6f, 1.0f),
                    SR_MATH_NS::FColor(0.6f, 0.6f, 0.6f, 1.0f),
                    SR_MATH_NS::FColor(0.6f, 0.6f, 0.6f, 1.0f),
                    SR_MATH_NS::FColor(0.6f, 0.6f, 0.6f, 1.0f),
                };

                float_t offsets[4] = { offsetMin.x, offsetMax.y, offsetMax.x, offsetMin.y };

                for (uint8_t i = 0; i < 4; ++i) {
                    SR_GRAPH_GUI_NS::Immediate::PushID(i);

                    if (i > 0) {
                        SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(context.fieldTitleWidth, 0.0f));
                        SR_GRAPH_GUI_NS::Immediate::SameLine();
                    }

                    SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Button, colors[i]);
                    SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonHovered, colors[i] + SR_MATH_NS::FColor(0.1f, 0.1f, 0.1f, 0.0f));
                    SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonActive, colors[i] + SR_MATH_NS::FColor(0.2f, 0.2f, 0.2f, 0.0f));

                    const SR_MATH_NS::FVector2 buttonSize = { axisButtonWidth * 2.2f, 0.0f };
                    if (SR_GRAPH_GUI_NS::Immediate::Button(labels[i], buttonSize)) {
                        offsets[i] = 0.0f;
                    }

                    SR_GRAPH_GUI_NS::Immediate::PopStyleColor(3);
                    SR_GRAPH_GUI_NS::Immediate::SameLine();

                    const float_t partItemWidth = fieldWidth - axisButtonWidth * 2.2f;
                    SR_GRAPH_GUI_NS::Immediate::PushItemWidth(partItemWidth);
                    if (SR_GRAPH_GUI_NS::Immediate::DragFloat("", &offsets[i], dragSpeed)) {
                        if (i == 0) offsetMin.x = offsets[i];
                        else if (i == 1) offsetMax.y = offsets[i];
                        else if (i == 2) offsetMax.x = offsets[i];
                        else if (i == 3) offsetMin.y = offsets[i];

                        pTransformRect->SetOffsetMin(offsetMin);
                        pTransformRect->SetOffsetMax(offsetMax);
                        feedback.isChanged = true;
                    }
                    SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

                    SR_GRAPH_GUI_NS::Immediate::PopID();
                }
            }
        }*/

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        return feedback;
    }
}
