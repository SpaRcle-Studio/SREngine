

# File Interpolation.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**Interpolation.h**](Interpolation_8h.md)

[Go to the documentation of this file](Interpolation_8h.md)


```C++
//
// Created by Monika on 07.01.2023.
//

#ifndef SR_ENGINE_INTERPOLATION_H
#define SR_ENGINE_INTERPOLATION_H

#include <Graphics/macros.h>

#include <Utils/Common/Enumerations.h>
#include <Utils/Math/Vector3.h>

namespace SR_ANIMATIONS_NS {
    SR_ENUM_NS_CLASS_T(AnimationInterpolationFunctionType, uint8_t,
        Linear,  
        Step,    
        Smooth   
    );

    class AnimationInterpolationFunction : public SR_UTILS_NS::NonCopyable {
        virtual float_t Calculate(float_t time, float_t start, float_t end) = 0;
        virtual double_t Calculate(double_t time, double_t start, double_t end) = 0;
        virtual int32_t Calculate(float_t time, int32_t start, int32_t end) = 0;
        virtual bool Calculate(float_t time, bool start, bool end) = 0;
    };
}

#endif //SR_ENGINE_INTERPOLATION_H
```


