

# File ShaderType.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**ShaderType.h**](ShaderType_8h.md)

[Go to the documentation of this file](ShaderType_8h.md)


```C++
//
// Created by Monika on 04.02.2023.
//

#ifndef SR_ENGINE_SRSL_SHADERTYPE_H
#define SR_ENGINE_SRSL_SHADERTYPE_H

#include <Graphics/Loaders/ShaderProperties.h>

namespace SR_SRSL_NS {
    SR_ENUM_NS_CLASS(ShaderType,
        Unknown,
        Spatial,            
        SpatialCustom,      
        Skinned,            
        PostProcessing,     
        Skybox,             
        Simple,             
        Canvas,             
        Particles,          
        Compute,            
        Line,               
        Text,               
        TextUI,             
        Custom,             
        //Raygen,             /// трасировка лучей. генерация лучей и вызов трассировки
        //AnyHit,             /// трасировка лучей. проверка на пересечение с примитивом (необязательный)
        //ClosestHit,         /// трасировка лучей. проверка на пересечение с примитивом (обязательный)
        //Miss,               /// трасировка лучей. пересечение не было найдено (в пределах [tmin; tmax])
        //Intersection        /// трасировка лучей. проверка пересечения луча и геометрии
        RayTrace           
    );

    enum VertexAttribute {
        SRSL_VERTEX_ATTRIBUTE_AUTO = 0,
        SRSL_VERTEX_ATTRIBUTE_POSITION = 1 << 0,
        SRSL_VERTEX_ATTRIBUTE_UV = 1 << 1,
        SRSL_VERTEX_ATTRIBUTE_NORMAL = 1 << 2,
        SRSL_VERTEX_ATTRIBUTE_TANGENT = 1 << 3,
        SRSL_VERTEX_ATTRIBUTE_BITANGENT = 1 << 4,
    };
}

#endif //SR_ENGINE_SRSL_SHADERTYPE_H
```


