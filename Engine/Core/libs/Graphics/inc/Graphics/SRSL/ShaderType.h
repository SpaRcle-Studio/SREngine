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
}

#endif //SRENGINE_SRSL_SHADERTYPE_H
