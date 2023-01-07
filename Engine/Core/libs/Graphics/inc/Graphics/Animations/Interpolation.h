//
// Created by Monika on 07.01.2023.
//

#ifndef SRENGINE_INTERPOLATION_H
#define SRENGINE_INTERPOLATION_H

#include <Utils/Common/Enumerations.h>

namespace SR_ANIMATIONS_NS {
    SR_ENUM_NS_CLASS_T(AnimationInterpolationFunctionType, uint8_t,
        Linear,  /// линейный переход
        Step,    /// мгновенное изменение состояния
        Smooth   /// то же что и Linear, но сглаженный
    );

    /// Принимает интервал времени от 0.f до 1.f, начальное значение и конечное.
    /// Возвращает промежуточное значение.
    class AnimationInterpolationFunction : public SR_UTILS_NS::NonCopyable {
        virtual float_t Calculate(float_t time, float_t start, float_t end) = 0;
        virtual double_t Calculate(double_t time, double_t start, double_t end) = 0;
        virtual int32_t Calculate(float_t time, int32_t start, int32_t end) = 0;
        virtual bool Calculate(float_t time, bool start, bool end) = 0;
    };
}

#endif //SRENGINE_INTERPOLATION_H
