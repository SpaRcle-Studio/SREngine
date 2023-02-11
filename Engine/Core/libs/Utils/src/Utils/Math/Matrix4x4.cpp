//
// Created by Monika on 16.01.2023.
//

#include <Utils/Math/Matrix4x4.h>
#include <Utils/Math/Matrix4x4Utils.h>

namespace SR_MATH_NS {
    constexpr Matrix4x4::Matrix4x4() noexcept
        : self(GLM_IDENTITY_MAT4X4)
    { }

    constexpr Matrix4x4::Matrix4x4(const Unit& scalar) noexcept
        : self(glm::mat4(static_cast<float_t>(scalar)))
    {  }

    constexpr Matrix4x4::Matrix4x4(const glm::mat4& mat) noexcept
        : self(mat)
    { }

    Matrix4x4::Matrix4x4(glm::mat4&& mat) noexcept
        : self(mat)
    { }

    Matrix4x4::Matrix4x4(const FVector3& translate, const Quaternion& rotation, const FVector3& scale) noexcept
        : Matrix4x4()
    {
        GLMTranslateMat4x4(self, translate.ToGLM());
        GLMRotateMat4x4(self, rotation.ToGLM());
        GLMScaleMat4x4(self, scale.ToGLM());
    }

    Matrix4x4::Matrix4x4(const FVector3& translate, const Quaternion& rotation, const FVector3& scale, const FVector3& skew) noexcept
        : Matrix4x4()
    {
        GLMTranslateMat4x4(self, translate.ToGLM());

        GLMScaleMat4x4(self, skew.ToGLM());
        GLMRotateMat4x4(self, rotation.ToGLM());
        GLMScaleMat4x4(self, scale.ToGLM());
    }

    Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const {
        return Matrix4x4(GLMMultiplyMat4x4(self, mat.self));
    }
}