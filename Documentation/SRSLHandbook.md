# SpaRcle Shader Language (SRSL) Handbook

??? note "Shader variables Types"
    - Trivial types:
        * int, uint, float, bool (int alias)
    - Floating vectors: 
        * vec2, vec3, vec4
    - Integer vectors: 
        * ivec2, ivec3, ivec4
    - Boolean vectors:
        * bvec2, bvec3, bvec4
    - Matrices:
        * mat2, Mat3, mat4
    - Samplers: 
        * sampler1D, sampler2D, sampler3D, samplerCube, sampler1DShadow, sampler2DShadow, sampler2DMS

??? note "Default shader uniforms"
    - Shared
        * mat4 VIEW_MATRIX           
        * mat4 INVERSE_VIEW_MATRIX           
        * mat4 PROJECTION_MATRIX           
        * mat4 INVERSE_PROJECTION_MATRIX           
        * mat4 PROJECTION_NO_FOV_MATRIX           
        * mat4 ORTHOGONAL_MATRIX           
        * mat4 VIEW_NO_TRANSLATE_MATRIX           
        * mat4 LIGHT_SPACE_MATRIX           
        * float TIME          
        * float CAMERA_FAR          
        * float CAMERA_NEAR          
        * int RENDER_PASS_TYPE            
        * vec2 RESOLUTION           
        * vec2 ASPECT           
        * mat4[4] CASCADE_LIGHT_SPACE_MATRICES        
        * vec4 CASCADE_SPLITS           
        * vec3 DIRECTIONAL_LIGHT_DIRECTION           
        * vec3 VIEW_POSITION           
        * vec3 VIEW_DIRECTION           

    - Per Mesh
        * mat4 MODEL_MATRIX                   
        * mat4 MODEL_NO_SCALE_MATRIX          
        * vec2 HALF_SIZE_NEAR_PLANE           
        * vec2 SLICED_TEXTURE_BORDER          
        * vec2 SLICED_WINDOW_BORDER           
        * vec3 LINE_START_POINT               
        * vec3 LINE_END_POINT                 
        * vec4[64] SSAO_SAMPLES                    
        * vec4 LINE_COLOR                     
        * vec4 RGBA_VALUE                     
        * float TEXT_RECT_X                    
        * float TEXT_RECT_Y                    
        * float TEXT_RECT_WIDTH                
        * float TEXT_RECT_HEIGHT               

??? note "Fragment shader outputs"
    - vec4 COLOR (alias for COLOR_INDEX_0)
    - vec4 COLOR_INDEX_0 
    - vec4 COLOR_INDEX_1 
    - vec4 COLOR_INDEX_2
    - vec4 COLOR_INDEX_3
    - vec4 COLOR_INDEX_4
    - vec4 COLOR_INDEX_5
    - vec4 COLOR_INDEX_6
    - vec4 COLOR_INDEX_7

??? note "Fragment shader inputs"
    - Spatial/SpatialCustom:
        * vec3 VERTEX;
        * vec2 UV;
        * vec3 NORMAL;
        * vec3 TANGENT;
        * vec3 BITANGENT;
    - Skinned:
        * vec3 VERTEX;
        * vec2 UV;
        * vec3 NORMAL;
        * vec3 TANGENT;
        * vec3 BITANGENT;
        * uint WEIGHTS_COUNT;
        * vec2[8] WEIGHTS;

??? note "Vertex shader inputs"
    * Spatial/SpatialCustom:
        * vec3 VERTEX;
        * vec2 UV;
        * vec3 NORMAL;
        * vec3 TANGENT;
        * vec3 BITANGENT;
    * Skinned:
        * vec3 VERTEX;
        * vec2 UV;
        * vec3 NORMAL;
        * vec3 TANGENT;
        * vec3 BITANGENT;
        * uint WEIGHTS_COUNT;
        * vec2[8] WEIGHTS;

