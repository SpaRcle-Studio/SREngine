//
// Created by Monika on 04.02.2023.
//

#ifndef SRENGINE_SRSL_SHADERTYPE_H
#define SRENGINE_SRSL_SHADERTYPE_H

#include <Utils/Common/Enumerations.h>

namespace SR_SRSL_NS {
    SR_ENUM_NS_CLASS(ShaderType,
        Unknown,
        Spatial,            /// пространственный шейдер, все статические меши
        SpatialCustom,      /// пространственный шейдер (только вершины), все статические меши
        Skinned,            /// пространтсвенный шейдер, геометрия со скелетом
        PostProcessing,     /// шейдер пост-обработки
        Skybox,             /// шейдер скайбокса
        Simple,             ///
        Canvas,             /// шейдер 2д пользовательского интерфейса
        Particles,          /// шейдер для частиц
        Compute,            ///
        Line,               /// просто линия, имеет начало и конец
        Text,               /// специальный шейдер для рендера 3d текста
        TextUI,             /// специальный шейдер для рендера 2d текста
        Custom,             /// полностью чистый шейдер, все настраивается вручную
        Raygen,             /// трасировка лучей. генерация лучей и вызов трассировки
        AnyHit,             /// трасировка лучей. проверка на пересечение с примитивом (необязательный)
        ClosestHit,         /// трасировка лучей. проверка на пересечение с примитивом (обязательный)
        Miss,               /// трасировка лучей. пересечение не было найдено (в пределах [tmin; tmax])
        Intersection        /// трасировка лучей. проверка пересечения луча и геометрии
    );

    enum VertexAttribute {
        SRSL_VERTEX_ATTRIBUTE_AUTO = 0,
        SRSL_VERTEX_ATTRIBUTE_POSITION = 1 << 0,
        SRSL_VERTEX_ATTRIBUTE_UV = 1 << 1,
        SRSL_VERTEX_ATTRIBUTE_NORMAL = 1 << 2,
        SRSL_VERTEX_ATTRIBUTE_TANGENT = 1 << 3,
        SRSL_VERTEX_ATTRIBUTE_BITANGENT = 1 << 4,
    };

    SR_INLINE_STATIC const std::map<std::string, std::string> SR_SRSL_DEFAULT_UNIFORMS = { /** NOLINT */
            { "MODEL_MATRIX",                   "mat4"          },
            { "VIEW_MATRIX",                    "mat4"          },
            { "PROJECTION_MATRIX",              "mat4"          },
            { "ORTHOGONAL_MATRIX",              "mat4"          },
            { "VIEW_NO_TRANSLATE_MATRIX",       "mat4"          },

            { "SKELETON_MATRICES_128",          "mat4[128]"     },
            { "SKELETON_MATRIX_OFFSETS_128",    "mat4[128]"     },

            { "HALF_SIZE_NEAR_PLANE",           "vec2"          },

            { "VIEW_POSITION",                  "vec3"          },
            { "VIEW_DIRECTION",                 "vec3"          },
            { "LINE_START_POINT",               "vec3"          },
            { "LINE_END_POINT",                 "vec3"          },

            { "LINE_COLOR",                     "vec4"          },

            { "TIME",                           "float"         },
            { "TEXT_RECT_X",                    "float"         },
            { "TEXT_RECT_Y",                    "float"         },
            { "TEXT_RECT_WIDTH",                "float"         },
            { "TEXT_RECT_HEIGHT",               "float"         },
    };

    SR_INLINE_STATIC const std::map<std::string, std::string> SR_SRSL_DEFAULT_SAMPLERS = { /** NOLINT */
            { "SKYBOX_DIFFUSE",                 "samplerCube"   },
            { "TEXT_ATLAS_TEXTURE",             "sampler2D"     },
    };

    SR_INLINE_STATIC const std::map<ShaderStage, std::string> SR_SRSL_ENTRY_POINTS = { /** NOLINT */
            { ShaderStage::Vertex, "vertex"     },
            { ShaderStage::Fragment, "fragment" },
            { ShaderStage::Compute, "compute"   },
    };

    SR_INLINE_STATIC const std::map<ShaderStage, std::string> SR_SRSL_STAGE_EXTENSIONS = { /** NOLINT */
            { ShaderStage::Vertex, "vert"       },
            { ShaderStage::Fragment, "frag"     },
            { ShaderStage::Compute, "comp"      },
    };

    static std::map<std::string, uint64_t> SR_SRSL_TYPE_SIZE_TABLE = { /** NOLINT */
            { "bool",         1         },

            { "int",          4         },
            { "float",        4         },

            { "bvec2",        1 * 2     },
            { "bvec3",        1 * 3     },
            { "bvec4",        1 * 4     },

            { "ivec2",        4 * 2     },
            { "ivec3",        4 * 3     },
            { "ivec4",        4 * 4     },

            { "vec2",         4 * 2     },
            { "vec3",         4 * 3     },
            { "vec4",         4 * 4     },

            { "mat2",         4 * 2 * 2 },
            { "mat3",         4 * 3 * 3 },
            { "mat4",         4 * 4 * 4 },
    };

    SR_INLINE_STATIC bool IsShaderEntryPoint(const std::string& name) {
        for (auto&& [stage, entryPoint] : SR_SRSL_ENTRY_POINTS) {
            if (entryPoint == name) {
                return true;
            }
        }

        return false;
    }

    SR_INLINE_STATIC bool IsSampler(const std::string& type) {
        return type.find("ampler") != std::string::npos;
    }

    SR_INLINE_STATIC uint64_t GetTypeSize(const std::string& type) {
        if (IsSampler(type)) {
            SRHalt("Samplers have not size!");
            return 0;
        }

        static std::map<std::string, uint64_t> typeSizes = {
            { "float", 4 }, { "int", 4 },
            { "vec2", 8 }, { "ivec2", 8 },
            { "vec3", 12 }, { "ivec3", 12 },
            { "vec4", 16 }, { "ivec4", 16 },
            { "mat2", 4 * 2 * 2 }, { "mat3", 4 * 3 * 3 }, { "mat4", 4 * 4 * 4 },
        };

        if (auto&& pIt = typeSizes.find(type); pIt != typeSizes.end()) {
            return pIt->second;
        }

        return 0;
    }
}

#endif //SRENGINE_SRSL_SHADERTYPE_H
