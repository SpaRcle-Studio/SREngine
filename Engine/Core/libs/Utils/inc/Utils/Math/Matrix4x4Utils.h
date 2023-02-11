//
// Created by Monika on 17.01.2023.
//

#ifndef SRENGINE_MATRIX4X4UTILS_H
#define SRENGINE_MATRIX4X4UTILS_H

#include <Utils/Math/Mathematics.h>
#include <Utils/Math/Vector3.h>

namespace SR_MATH_NS {
    SR_INLINE_STATIC void SR_FASTCALL GLMScaleMat4x4(glm::mat4& matrix, const glm::vec3& v) {
        typename glm::mat4::col_type& DstB0 = *(typename glm::mat4::col_type*)(((char*)&matrix) + sizeof(typename glm::mat4::col_type) * 0);
        typename glm::mat4::col_type& DstB1 = *(typename glm::mat4::col_type*)(((char*)&matrix) + sizeof(typename glm::mat4::col_type) * 1);
        typename glm::mat4::col_type& DstB2 = *(typename glm::mat4::col_type*)(((char*)&matrix) + sizeof(typename glm::mat4::col_type) * 2);
        typename glm::mat4::col_type& DstB3 = *(typename glm::mat4::col_type*)(((char*)&matrix) + sizeof(typename glm::mat4::col_type) * 3);

        DstB0.x = DstB0.x * v.x;
        DstB0.y = DstB0.y * v.x;
        DstB0.z = DstB0.z * v.x;
        DstB0.w = DstB0.w * v.x;

        DstB1.x = DstB1.x * v.y;
        DstB1.y = DstB1.y * v.y;
        DstB1.z = DstB1.z * v.y;
        DstB1.w = DstB1.w * v.y;

        DstB2.x = DstB2.x * v.z;
        DstB2.y = DstB2.y * v.z;
        DstB2.z = DstB2.z * v.z;
        DstB2.w = DstB2.w * v.z;
    }

    SR_INLINE_STATIC void SR_FASTCALL GLMTranslateMat4x4(glm::mat4& matrix, const glm::vec3& v) {
        typename glm::mat4::col_type& DstB0 = *(typename glm::mat4::col_type*)(((char*)&matrix) + sizeof(typename glm::mat4::col_type) * 0);
        typename glm::mat4::col_type& DstB1 = *(typename glm::mat4::col_type*)(((char*)&matrix) + sizeof(typename glm::mat4::col_type) * 1);
        typename glm::mat4::col_type& DstB2 = *(typename glm::mat4::col_type*)(((char*)&matrix) + sizeof(typename glm::mat4::col_type) * 2);
        typename glm::mat4::col_type& DstB3 = *(typename glm::mat4::col_type*)(((char*)&matrix) + sizeof(typename glm::mat4::col_type) * 3);

        DstB3.x = DstB0.x * v.x + DstB1.x * v.y + DstB2.x * v.z + DstB3.x;
        DstB3.y = DstB0.y * v.x + DstB1.y * v.y + DstB2.y * v.z + DstB3.y;
        DstB3.z = DstB0.z * v.x + DstB1.z * v.y + DstB2.z * v.z + DstB3.z;
        DstB3.w = DstB0.w * v.x + DstB1.w * v.y + DstB2.w * v.z + DstB3.w;
    }

    SR_INLINE_STATIC void SR_FASTCALL GLMMultiplyMat4x4(glm::mat4& result, const glm::mat4& m1, const glm::mat4& m2) noexcept {
        typename glm::mat4::col_type& SrcA0 = *(typename glm::mat4::col_type*)(((char*)&m1) + sizeof(typename glm::mat4::col_type) * 0);
        typename glm::mat4::col_type& SrcA1 = *(typename glm::mat4::col_type*)(((char*)&m1) + sizeof(typename glm::mat4::col_type) * 1);
        typename glm::mat4::col_type& SrcA2 = *(typename glm::mat4::col_type*)(((char*)&m1) + sizeof(typename glm::mat4::col_type) * 2);
        typename glm::mat4::col_type& SrcA3 = *(typename glm::mat4::col_type*)(((char*)&m1) + sizeof(typename glm::mat4::col_type) * 3);

        typename glm::mat4::col_type& SrcB0 = *(typename glm::mat4::col_type*)(((char*)&m2) + sizeof(typename glm::mat4::col_type) * 0);
        typename glm::mat4::col_type& SrcB1 = *(typename glm::mat4::col_type*)(((char*)&m2) + sizeof(typename glm::mat4::col_type) * 1);
        typename glm::mat4::col_type& SrcB2 = *(typename glm::mat4::col_type*)(((char*)&m2) + sizeof(typename glm::mat4::col_type) * 2);
        typename glm::mat4::col_type& SrcB3 = *(typename glm::mat4::col_type*)(((char*)&m2) + sizeof(typename glm::mat4::col_type) * 3);

        typename glm::mat4::col_type& DstB0 = *(typename glm::mat4::col_type*)(((char*)&result) + sizeof(typename glm::mat4::col_type) * 0);
        typename glm::mat4::col_type& DstB1 = *(typename glm::mat4::col_type*)(((char*)&result) + sizeof(typename glm::mat4::col_type) * 1);
        typename glm::mat4::col_type& DstB2 = *(typename glm::mat4::col_type*)(((char*)&result) + sizeof(typename glm::mat4::col_type) * 2);
        typename glm::mat4::col_type& DstB3 = *(typename glm::mat4::col_type*)(((char*)&result) + sizeof(typename glm::mat4::col_type) * 3);

        DstB0.x = SrcA0.x * SrcB0.x + SrcA1.x * SrcB0.y + SrcA2.x * SrcB0.z + SrcA3.x * SrcB0.w;
        DstB0.y = SrcA0.y * SrcB0.x + SrcA1.y * SrcB0.y + SrcA2.y * SrcB0.z + SrcA3.y * SrcB0.w;
        DstB0.z = SrcA0.z * SrcB0.x + SrcA1.z * SrcB0.y + SrcA2.z * SrcB0.z + SrcA3.z * SrcB0.w;
        DstB0.w = SrcA0.w * SrcB0.x + SrcA1.w * SrcB0.y + SrcA2.w * SrcB0.z + SrcA3.w * SrcB0.w;

        DstB1.x = SrcA0.x * SrcB1.x + SrcA1.x * SrcB1.y + SrcA2.x * SrcB1.z + SrcA3.x * SrcB1.w;
        DstB1.y = SrcA0.y * SrcB1.x + SrcA1.y * SrcB1.y + SrcA2.y * SrcB1.z + SrcA3.y * SrcB1.w;
        DstB1.z = SrcA0.z * SrcB1.x + SrcA1.z * SrcB1.y + SrcA2.z * SrcB1.z + SrcA3.z * SrcB1.w;
        DstB1.w = SrcA0.w * SrcB1.x + SrcA1.w * SrcB1.y + SrcA2.w * SrcB1.z + SrcA3.w * SrcB1.w;

        DstB2.x = SrcA0.x * SrcB2.x + SrcA1.x * SrcB2.y + SrcA2.x * SrcB2.z + SrcA3.x * SrcB2.w;
        DstB2.y = SrcA0.y * SrcB2.x + SrcA1.y * SrcB2.y + SrcA2.y * SrcB2.z + SrcA3.y * SrcB2.w;
        DstB2.z = SrcA0.z * SrcB2.x + SrcA1.z * SrcB2.y + SrcA2.z * SrcB2.z + SrcA3.z * SrcB2.w;
        DstB2.w = SrcA0.w * SrcB2.x + SrcA1.w * SrcB2.y + SrcA2.w * SrcB2.z + SrcA3.w * SrcB2.w;

        DstB3.x = SrcA0.x * SrcB3.x + SrcA1.x * SrcB3.y + SrcA2.x * SrcB3.z + SrcA3.x * SrcB3.w;
        DstB3.y = SrcA0.y * SrcB3.x + SrcA1.y * SrcB3.y + SrcA2.y * SrcB3.z + SrcA3.y * SrcB3.w;
        DstB3.z = SrcA0.z * SrcB3.x + SrcA1.z * SrcB3.y + SrcA2.z * SrcB3.z + SrcA3.z * SrcB3.w;
        DstB3.w = SrcA0.w * SrcB3.x + SrcA1.w * SrcB3.y + SrcA2.w * SrcB3.z + SrcA3.w * SrcB3.w;
    }

    SR_INLINE_STATIC void SR_FASTCALL GLMMultiplyMat4x4(glm::mat4& result, const glm::mat4& m1, const glm::mat3& m2) noexcept {
        typename glm::mat4::col_type& SrcA0 = *(typename glm::mat4::col_type*)(((char*)&m1) + sizeof(typename glm::mat4::col_type) * 0);
        typename glm::mat4::col_type& SrcA1 = *(typename glm::mat4::col_type*)(((char*)&m1) + sizeof(typename glm::mat4::col_type) * 1);
        typename glm::mat4::col_type& SrcA2 = *(typename glm::mat4::col_type*)(((char*)&m1) + sizeof(typename glm::mat4::col_type) * 2);
        typename glm::mat4::col_type& SrcA3 = *(typename glm::mat4::col_type*)(((char*)&m1) + sizeof(typename glm::mat4::col_type) * 3);

        typename glm::mat3::col_type& SrcB0 = *(typename glm::mat3::col_type*)(((char*)&m2) + sizeof(typename glm::mat3::col_type) * 0);
        typename glm::mat3::col_type& SrcB1 = *(typename glm::mat3::col_type*)(((char*)&m2) + sizeof(typename glm::mat3::col_type) * 1);
        typename glm::mat3::col_type& SrcB2 = *(typename glm::mat3::col_type*)(((char*)&m2) + sizeof(typename glm::mat3::col_type) * 2);

        typename glm::mat4::col_type& DstB0 = *(typename glm::mat4::col_type*)(((char*)&result) + sizeof(typename glm::mat4::col_type) * 0);
        typename glm::mat4::col_type& DstB1 = *(typename glm::mat4::col_type*)(((char*)&result) + sizeof(typename glm::mat4::col_type) * 1);
        typename glm::mat4::col_type& DstB2 = *(typename glm::mat4::col_type*)(((char*)&result) + sizeof(typename glm::mat4::col_type) * 2);
        typename glm::mat4::col_type& DstB3 = *(typename glm::mat4::col_type*)(((char*)&result) + sizeof(typename glm::mat4::col_type) * 3);

        DstB0.x = SrcA0.x * SrcB0.x + SrcA1.x * SrcB0.y + SrcA2.x * SrcB0.z;
        DstB0.y = SrcA0.y * SrcB0.x + SrcA1.y * SrcB0.y + SrcA2.y * SrcB0.z;
        DstB0.z = SrcA0.z * SrcB0.x + SrcA1.z * SrcB0.y + SrcA2.z * SrcB0.z;
        DstB0.w = SrcA0.w * SrcB0.x + SrcA1.w * SrcB0.y + SrcA2.w * SrcB0.z;

        DstB1.x = SrcA0.x * SrcB1.x + SrcA1.x * SrcB1.y + SrcA2.x * SrcB1.z;
        DstB1.y = SrcA0.y * SrcB1.x + SrcA1.y * SrcB1.y + SrcA2.y * SrcB1.z;
        DstB1.z = SrcA0.z * SrcB1.x + SrcA1.z * SrcB1.y + SrcA2.z * SrcB1.z;
        DstB1.w = SrcA0.w * SrcB1.x + SrcA1.w * SrcB1.y + SrcA2.w * SrcB1.z;

        DstB2.x = SrcA0.x * SrcB2.x + SrcA1.x * SrcB2.y + SrcA2.x * SrcB2.z;
        DstB2.y = SrcA0.y * SrcB2.x + SrcA1.y * SrcB2.y + SrcA2.y * SrcB2.z;
        DstB2.z = SrcA0.z * SrcB2.x + SrcA1.z * SrcB2.y + SrcA2.z * SrcB2.z;
        DstB2.w = SrcA0.w * SrcB2.x + SrcA1.w * SrcB2.y + SrcA2.w * SrcB2.z;

        DstB3.x = SrcA3.x;
        DstB3.y = SrcA3.y;
        DstB3.z = SrcA3.z;
        DstB3.w = SrcA3.w;
    }

    SR_NODISCARD SR_INLINE_STATIC glm::mat4 SR_FASTCALL GLMMultiplyMat4x4(const glm::mat4& m1, const glm::mat4& m2) noexcept {
        glm::mat4 result;
        GLMMultiplyMat4x4(result, m1, m2);
        return result;
    }

    SR_INLINE_STATIC void SR_FASTCALL GLMRotateMat4x4(glm::mat4& matrix, const glm::quat& q) {
        static const glm::mat3 mat3x3Identity = glm::mat3(1);
        glm::mat3 mat3x3 = mat3x3Identity;

        typename glm::mat3::col_type& Src0 = *(typename glm::mat3::col_type*)(((char*)&mat3x3) + sizeof(typename glm::mat3::col_type) * 0);
        typename glm::mat3::col_type& Src1 = *(typename glm::mat3::col_type*)(((char*)&mat3x3) + sizeof(typename glm::mat3::col_type) * 1);
        typename glm::mat3::col_type& Src2 = *(typename glm::mat3::col_type*)(((char*)&mat3x3) + sizeof(typename glm::mat3::col_type) * 2);

        /// rotation matrix
        {
            const float_t qxx(q.x * q.x);
            const float_t qyy(q.y * q.y);
            const float_t qzz(q.z * q.z);
            const float_t qxz(q.x * q.z);
            const float_t qxy(q.x * q.y);
            const float_t qyz(q.y * q.z);
            const float_t qwx(q.w * q.x);
            const float_t qwy(q.w * q.y);
            const float_t qwz(q.w * q.z);

            Src0.x = float_t(1) - float_t(2) * (qyy + qzz);
            Src0.y = float_t(2) * (qxy + qwz);
            Src0.z = float_t(2) * (qxz - qwy);

            Src1.x = float_t(2) * (qxy - qwz);
            Src1.y = float_t(1) - float_t(2) * (qxx + qzz);
            Src1.z = float_t(2) * (qyz + qwx);

            Src2.x = float_t(2) * (qxz + qwy);
            Src2.y = float_t(2) * (qyz - qwx);
            Src2.z = float_t(1) - float_t(2) * (qxx + qyy);
        }

        glm::mat4 source = matrix;
        GLMMultiplyMat4x4(matrix, source, mat3x3);
    }
}

#endif //SRENGINE_MATRIX4X4UTILS_H
