//
// Created by Nikita on 01.03.2021.
//

#ifndef GAMEENGINE_MATRIX3X3_H
#define GAMEENGINE_MATRIX3X3_H

#include <Math/Quaternion.h>
#include <Math/Vector3.h>

namespace Framework::Helper::Math {
    class Matrix3x3 {
    public:
        Vector3 elements[3] = {
                Vector3(1, 0, 0),
                Vector3(0, 1, 0),
                Vector3(0, 0, 1)
        };

        _FORCE_INLINE_ const Vector3 &operator[](int axis) const {
            return elements[axis];
        }
        _FORCE_INLINE_ Vector3 &operator[](int axis) {
            return elements[axis];
        }

        _FORCE_INLINE_ void Set(double xx, double xy, double xz, double yx, double yy, double yz, double zx, double zy, double zz) {
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
/*
        Matrix3x3(const Quaternion &p_quat) {
            SetQuaternion(p_quat);
        }

        void SetQuaternion(const Quaternion &p_quat) {
            double d = p_quat.lengthSquared();
            double s = 2.0 / d;
            double xs = p_quat.x * s, ys = p_quat.y * s, zs = p_quat.z * s;
            double wx = p_quat.w * xs, wy = p_quat.w * ys, wz = p_quat.w * zs;
            double xx = p_quat.x * xs, xy = p_quat.x * ys, xz = p_quat.x * zs;
            double yy = p_quat.y * ys, yz = p_quat.y * zs, zz = p_quat.z * zs;
            Set(1.0 - (yy + zz), xy - wz, xz + wy,
                xy + wz, 1.0 - (xx + zz), yz - wx,
                xz - wy, yz + wx, 1.0 - (xx + yy));
        }*/

        Vector3 GetEulerXYZ() const {
            // Euler angles in XYZ convention.
            // See https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix
            //
            // rot =  cy*cz          -cy*sz           sy
            //        cz*sx*sy+cx*sz  cx*cz-sx*sy*sz -cy*sx
            //       -cx*cz*sy+sx*sz  cz*sx+cx*sy*sz  cx*cy

            Vector3 euler;
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
                    euler.y = -Math_PI / 2.0;
                    euler.z = 0.0;
                }
            } else {
                euler.x = atan2(elements[2][1], elements[1][1]);
                euler.y = Math_PI / 2.0;
                euler.z = 0.0;
            }
            return euler;
        }
    };
}

#endif //GAMEENGINE_MATRIX3X3_H
