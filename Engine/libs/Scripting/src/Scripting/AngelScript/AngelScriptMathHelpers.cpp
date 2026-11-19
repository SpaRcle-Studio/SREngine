//
// Created by Codex on 13.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptMathHelpers.h>

#include <Utils/Math/Quaternion.h>
#include <Utils/Math/Matrix3x3.h>
#include <Utils/Math/Matrix4x4.h>
#include <Utils/Math/AABB.h>
#include <Utils/Math/Size.h>

namespace SR_SCRIPTING_NS::AngelScriptMathHelpers {
    Layout Describe(const SR_UTILS_NS::Reflection::TypeInfo& info) {
        static_assert(sizeof(SR_MATH_NS::Unit) == sizeof(float_t));
        static_assert(sizeof(SR_MATH_NS::FVector3) == 3 * sizeof(float_t));

        Layout result;

        if (!info.IsMath()) {
            return result;
        }

        const char* pAxes[] = { "x", "y", "z", "w", "v", "u" };
        const char* pRect[] = { "x", "y", "w", "h" };
        const char* pColors[] = { "r", "g", "b", "a" };
        const char* pBounds[] = { "minX", "minY", "minZ", "maxX", "maxY", "maxZ" };
        const char* pMatrix3[] = { "m00", "m01", "m02", "m10", "m11", "m12", "m20", "m21", "m22" };
        const char* pMatrix4[] = { "m00", "m01", "m02", "m03", "m10", "m11", "m12", "m13", "m20", "m21", "m22", "m23", "m30", "m31", "m32", "m33" };

        const char* const* pNames = nullptr;
        const SR_UTILS_NS::Reflection::TypeInfo* pScalar = info.pNext[0];
        uint32_t stride = pScalar ? static_cast<uint32_t>(pScalar->GetScalarSize()) : 0;

        switch (info.kind) {
            case SR_UTILS_NS::Reflection::TypeKind::MathVector:
                result.count = info.detailedSize <= 6 ? info.detailedSize : 0;
                pNames = pAxes;
                break;
            case SR_UTILS_NS::Reflection::TypeKind::MathRect:
                result.count = 4;
                pNames = pRect;
                break;
            case SR_UTILS_NS::Reflection::TypeKind::MathSize: {
                // Size<T> contains a scalar followed by SizeMetric; Size2<T> contains two Size<T>.
                // Derive the stride from reflected scalar size/alignment, preserving each metric byte.
                if (info.detailedSize == 0 || info.detailedSize > 2 || stride == 0) {
                    return result;
                }

                auto&& pMetricType = SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::UInt8);
                const uint32_t elementStride = ((stride + static_cast<uint32_t>(sizeof(SR_MATH_NS::SizeMetric)) + stride - 1) / stride) * stride;
                const char* pValues[] = { info.detailedSize == 1 ? "value" : "width", "height" };
                const char* pMetrics[] = { info.detailedSize == 1 ? "metric" : "widthMetric", "heightMetric" };

                for (uint32_t i = 0; i < info.detailedSize; ++i) {
                    result.components[result.count++] = { pValues[i], pScalar, i * elementStride };
                    result.components[result.count++] = { pMetrics[i], pMetricType, i * elementStride + stride };
                }

                return result;
            }
            default:
                pScalar = SR_UTILS_NS::Reflection::GetScalarTypeInfo(SR_UTILS_NS::Reflection::TypeKind::Float);
                stride = sizeof(float_t);

                if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Quaternion) {
                    result.count = 4;
                    pNames = pAxes;
                }
                else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Color) {
                    result.count = 4;
                    pNames = pColors;
                    stride = sizeof(SR_MATH_NS::Unit);
                }
                else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Matrix3x3) {
                    result.count = 9;
                    pNames = pMatrix3;
                    stride = sizeof(SR_MATH_NS::Unit);
                }
                else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::Matrix4x4) {
                    result.count = 16;
                    pNames = pMatrix4;
                }
                else if (info.kind == SR_UTILS_NS::Reflection::TypeKind::AABB) {
                    result.count = 6;
                    pNames = pBounds;
                }
                break;
        }

        if (!pScalar) {
            result.count = 0;
            return result;
        }

        for (uint32_t i = 0; i < result.count; ++i) {
            uint32_t offset = i * stride;
            if (info.kind == SR_UTILS_NS::Reflection::TypeKind::AABB) {
                offset = i < 3 ? static_cast<uint32_t>(offsetof(SR_MATH_NS::AABB, min)) + i * stride :
                    static_cast<uint32_t>(offsetof(SR_MATH_NS::AABB, max)) + (i - 3) * stride;
            }

            result.components[i] = { pNames[i], pScalar, offset };
        }

        return result;
    }
}

#endif
