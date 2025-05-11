

# File ShaderType.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**ShaderType.h**](ShaderType_8h.md)

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


