

# File ShaderVariables.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**ShaderVariables.h**](ShaderVariables_8h.md)

[Go to the documentation of this file](ShaderVariables_8h.md)


```C++
//
// Created by Monika on 26.01.2024.
//

#ifndef SR_ENGINE_SRSL_SHADER_VARIABLES_H
#define SR_ENGINE_SRSL_SHADER_VARIABLES_H

#include <Graphics/SRSL/ShaderType.h>

namespace SR_SRSL_NS {
    SR_INLINE_STATIC const std::map<std::string, std::string> SR_SRSL_DEFAULT_PUSH_CONSTANTS = { 
            { "PC_SHADOW_CASCADE_INDEX",           "int"        },
            { "PC_COLOR_BUFFER_MODE",              "int"        },
            { "COMPUTE_STAGE",                     "int"        },
            { "PC_COLOR_BUFFER_VALUE",             "vec3"       },
    };

    SR_INLINE_STATIC const std::map<std::string, std::string> SR_SRSL_DEFAULT_SHARED_UNIFORMS = { 
            { "VIEW_MATRIX",                    "mat4"          },
            { "PROJECTION_MATRIX",              "mat4"          },
            { "PROJECTION_NO_FOV_MATRIX",       "mat4"          },
            { "ORTHOGONAL_MATRIX",              "mat4"          },
            { "VIEW_NO_TRANSLATE_MATRIX",       "mat4"          },
            { "LIGHT_SPACE_MATRIX",             "mat4"          },

            { "TIME",                           "float"         },

            { "RESOLUTION",                     "vec2"          },
            { "ASPECT",                         "vec2"          },

            { "CASCADE_LIGHT_SPACE_MATRICES",   "mat4[4]"       },
            { "CASCADE_SPLITS",                 "vec4"          },

            { "DIRECTIONAL_LIGHT_POSITION",     "vec3"          },
            { "VIEW_POSITION",                  "vec3"          },
            { "VIEW_DIRECTION",                 "vec3"          },
    };

    SR_INLINE_STATIC const std::map<std::string, std::string> SR_SRSL_DEFAULT_UNIFORMS = { 
            { "MODEL_MATRIX",                   "mat4"          },
            { "MODEL_NO_SCALE_MATRIX",          "mat4"          },

            { "SKELETON_MATRICES_128",          "mat4[128]"     },
            { "SKELETON_MATRIX_OFFSETS_128",    "mat4[128]"     },

            { "SKELETON_MATRICES_256",          "mat4[256]"     },
            { "SKELETON_MATRIX_OFFSETS_256",    "mat4[256]"     },

            { "SKELETON_MATRICES_384",          "mat4[384]"     },
            { "SKELETON_MATRIX_OFFSETS_384",    "mat4[384]"     },

            { "HALF_SIZE_NEAR_PLANE",           "vec2"          },
            { "SLICED_TEXTURE_BORDER",          "vec2"          },
            { "SLICED_WINDOW_BORDER",           "vec2"          },

            { "LINE_START_POINT",               "vec3"          },
            { "LINE_END_POINT",                 "vec3"          },

            { "SSAO_SAMPLES",                   "vec4[64]"      },

            { "LINE_COLOR",                     "vec4"          },
            { "RGBA_VALUE",                     "vec4"          },

            { "TEXT_RECT_X",                    "float"         },
            { "TEXT_RECT_Y",                    "float"         },
            { "TEXT_RECT_WIDTH",                "float"         },
            { "TEXT_RECT_HEIGHT",               "float"         },
    };

    SR_INLINE_STATIC const std::map<std::string, std::string> SR_SRSL_DEFAULT_SAMPLERS = { 
            { "SKYBOX_DIFFUSE",                 "samplerCube"   },
            { "TEXT_ATLAS_TEXTURE",             "sampler2D"     },
            { "SSAO_NOISE",                     "sampler2D"     },
    };

    SR_INLINE_STATIC const std::string SR_SRSL_MAIN_OUT_LAYER = "COLOR_INDEX_0"; 
    SR_INLINE_STATIC const std::set<std::string> SR_SRSL_DEFAULT_OUT_LAYERS = { 
            { "COLOR_INDEX_0" },
            { "COLOR_INDEX_1" },
            { "COLOR_INDEX_2" },
            { "COLOR_INDEX_3" },
            { "COLOR_INDEX_4" },
            { "COLOR_INDEX_5" },
            { "COLOR_INDEX_6" },
            { "COLOR_INDEX_7" },
            { "COLOR_INDEX_8" },
    };

    SR_INLINE_STATIC const std::map<ShaderStage, std::string> SR_SRSL_ENTRY_POINTS = { 
            { ShaderStage::Vertex,   "vertex"     },
            { ShaderStage::Fragment, "fragment" },
            { ShaderStage::Compute,  "compute"   },
    };

    SR_INLINE_STATIC const std::map<ShaderStage, std::string> SR_SRSL_STAGE_EXTENSIONS = { 
            { ShaderStage::Vertex,        "vert"        },
            { ShaderStage::Fragment,      "frag"        },
            { ShaderStage::Compute,       "comp"        },
            { ShaderStage::Raygen,        "rgen"        },
            { ShaderStage::Intersection,  "rint"        },
            { ShaderStage::HitClosest,    "rchit"       },
            { ShaderStage::HitAny,        "rahit"       },
            { ShaderStage::MissPrimary  , "rmiss"       },
            { ShaderStage::MissSecondary, "rmiss"       },
    };

    static std::map<std::string, ShaderVarType> SR_SRSL_TYPE_STRINGS = { 
            { "bool",               ShaderVarType::Bool             },

            { "int",                ShaderVarType::Int              },
            { "float",              ShaderVarType::Float            },

            { "bvec2",              ShaderVarType::BVec2            },
            { "bvec3",              ShaderVarType::BVec3            },
            { "bvec4",              ShaderVarType::BVec4            },

            { "ivec2",              ShaderVarType::IVec2            },
            { "ivec3",              ShaderVarType::IVec3            },
            { "ivec4",              ShaderVarType::IVec4            },

            { "vec2",               ShaderVarType::Vec2             },
            { "vec3",               ShaderVarType::Vec3             },
            { "vec4",               ShaderVarType::Vec4             },

            { "mat2",               ShaderVarType::Mat2             },
            { "mat3",               ShaderVarType::Mat3             },
            { "mat4",               ShaderVarType::Mat4             },

            { "sampler1D",          ShaderVarType::Sampler1D        },
            { "sampler2D",          ShaderVarType::Sampler2D        },
            { "sampler3D",          ShaderVarType::Sampler3D        },
            { "sampler1DShadow",    ShaderVarType::Sampler1DShadow  },
            { "sampler2DShadow",    ShaderVarType::Sampler2DShadow  },
            { "samplerCube",        ShaderVarType::SamplerCube      },
    };

    static std::map<std::string, uint64_t> SR_SRSL_TYPE_SIZE_TABLE = { 
            { "bool",         4         },

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
        return
            type.find("ampler") != std::string::npos ||
            type.find("mage2DMS") != std::string::npos ||
            type.find("ubpassInput") != std::string::npos;
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

#endif //SR_ENGINE_SRSL_SHADER_VARIABLES_H
```


