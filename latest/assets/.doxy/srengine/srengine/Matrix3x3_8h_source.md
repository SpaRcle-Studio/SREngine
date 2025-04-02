

# File Matrix3x3.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Math**](dir_3900fe4b4d95d895210b9082ab5cdd34.md) **>** [**Matrix3x3.h**](Matrix3x3_8h.md)

[Go to the documentation of this file](Matrix3x3_8h.md)


```C++
//
// Created by Nikita on 01.03.2021.
//

#ifndef SR_ENGINE_MATRIX3X3_H
#define SR_ENGINE_MATRIX3X3_H

#include <Utils/Math/Quaternion.h>
#include <Utils/Math/Vector3.h>

namespace SR_MATH_NS {
    class SR_DLL_EXPORT Matrix3x3 {
    public:
        FVector3 elements[3] = {
                FVector3(1, 0, 0),
                FVector3(0, 1, 0),
                FVector3(0, 0, 1)
        };

        SR_FORCE_INLINE const FVector3 &operator[](int axis) const {
            return elements[axis];
        }
        SR_FORCE_INLINE FVector3 &operator[](int axis) {
            return elements[axis];
        }

        SR_FORCE_INLINE void Set(double xx, double xy, double xz, double yx, double yy, double yz, double zx, double zy, double zz) {
            elements[0][0] = xx;
            elements[0][1] = xy;
            elements[0][2] = xz;
            elements[1][0] = yx;
            elements[1][1] = yy;
            elements[1][2] = yz;
            elements[2][0] = zx;
            elements[2][1] = zy;
            elements[2][2] = zz;
        }

        FVector3 GetEulerXYZ() const {
            FVector3 euler;
            double sy = elements[0][2];
            if (sy < (1.0 - CMP_EPSILON)) {
                if (sy > -(1.0 - CMP_EPSILON)) {
                    // is this a pure Y rotation?
                    if (elements[1][0] == 0.0 && elements[0][1] == 0.0 && elements[1][2] == 0 && elements[2][1] == 0 && elements[1][1] == 1) {
                        // return the simplest form (human friendlier in editor and scripts)
                        euler.x = 0;
                        euler.y = atan2(elements[0][2], elements[0][0]);
                        euler.z = 0;
                    } else {
                        euler.x = atan2(-elements[1][2], elements[2][2]);
                        euler.y = asin(sy);
                        euler.z = atan2(-elements[0][1], elements[0][0]);
                    }
                } else {
                    euler.x = atan2(elements[2][1], elements[1][1]);
                    euler.y = -SR_PI / 2.0;
                    euler.z = 0.0;
                }
            } else {
                euler.x = atan2(elements[2][1], elements[1][1]);
                euler.y = SR_PI / 2.0;
                euler.z = 0.0;
            }
            return euler;
        }
    };
}

#endif //SR_ENGINE_MATRIX3X3_H
```


