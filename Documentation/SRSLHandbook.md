# SpaRcle Shader Language (SRSL) Handbook

## Shader Variables Types:
* Unknown;
* Bool;
* Int;
* Float;
* Vec2;
* Vec3;
* Vec4;
* IVec2;
* IVec3;
* IVec4;
* BVec2;
* BVec3;
* BVec4;
* Mat2;
* Mat3;
* Mat4;
* Sampler1D;
* Sampler2D;
* Sampler3D;
* SamplerCube;
* Sampler1DShadow;
* Sampler2DShadow.

## Default Shader Variables:
* All stages (Standard Variables):
    * vec2 HALF_SIZE_NEAR_PLANE;
    * mat4 MODEL_MATRIX;
    * mat4 VIEW_MATRIX;
    * mat4 PROJECTION_MATRIX;
    * mat4 ORTHOGONAL_MATRIX;
    * mat4 VIEW_NO_TRANSLATE_MATRIX;
    * mat4[128] SKELETON_MATRICES_128;
    * mat4[128] SKELETON_MATRIX_OFFSETS_128;
    * samplerCube SKYBOX_DIFFUSE;
    * sampler2D TEXT_ATLAS_TEXTURE;
    * float TIME;
    * float TEXT_RECT_X;
    * float TEXT_RECT_Y;
    * float TEXT_RECT_WIDTH;
    * float TEXT_RECT_HEIGHT;
    * vec3 VIEW_POSITION;
    * vec3 VIEW_DIRECTION;
    * vec3 LINE_START_POINT;
    * vec3 LINE_END_POINT;
    * vec4 LINE_COLOR;
    * vec4 COLOR_INDEX_0, COLOR_INDEX_1, COLOR_INDEX_2, COLOR_INDEX_3, COLOR_INDEX_4, COLOR_INDEX_5, COLOR_INDEX_6, COLOR_INDEX_7;
* Vertex stage:
    * TextUI/Text:
        * vec2 UV;
    * Spatial/SpatialCustom:
        * vec3 VERTEX;
        * vec2 UV;
        * vec3 NORMAL;
        * vec3 TANGENT;
        * vec3 BITANGENT;
        * float VERTEX_INDEX_OUT;
    * Skinned:
        * vec3 VERTEX;
        * vec2 UV;
        * vec3 NORMAL;
        * vec3 TANGENT;
        * vec3 BITANGENT;
        * float VERTEX_INDEX_OUT;
        * vec2 WEIGHT0, WEIGHT1, WEIGHT2, WEIGHT3, WEIGHT4, WEIGHT5, WEIGHT6, WEIGHT7;
    * PostProcessing:
        * vec3 VERTEX;
        * vec2 UV;
        * float VERTEX_INDEX_OUT;
    * Simple/Canvas:
        * vec3 VERTEX;
        * vec2 UV;
    * Skybox:
        * vec3 VERTEX;
        * vec3 UV;
        * float VERTEX_INDEX_OUT;
    * Custom/Line:
        * NONE;
* Fragment stage:
    * Spatial/SpatialCustom:
        * vec3 VERTEX;
        * vec2 UV;
        * vec3 NORMAL;
        * vec3 TANGENT;
        * vec3 BITANGENT;
        * float VERTEX_INDEX;
        * vec4 COLOR;
    * Skinned:
        * vec3 VERTEX;
        * vec2 UV;
        * vec3 NORMAL;
        * vec3 TANGENT;
        * vec3 BITANGENT;
        * float VERTEX_INDEX_OUT;
        * vec2 WEIGHT0, WEIGHT1, WEIGHT2, WEIGHT3, WEIGHT4, WEIGHT5, WEIGHT6, WEIGHT7;
        * vec4 COLOR;
    * Simple/Canvas:
        * vec3 VERTEX;
        * vec2 UV;
        * vec4 COLOR
    * Skybox:
        * vec3 VERTEX;
        * vec2 UV;
        * ec4 COLOR;
    * TextUI/Text:
        * vec2 UV;
        * vec4 COLOR;
    * PostProcessing:
        * vec3 VERTEX;
        * vec2 UV;
        * float VERTEX_INDEX;
    * Custom/Line:
        * NONE.
