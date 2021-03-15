//
// Created by Nikita on 02.03.2021.
//

#ifndef GAMEENGINE_MATRIX4X4_H
#define GAMEENGINE_MATRIX4X4_H

#include <Math/Quaternion.h>
#include <Math/Vector3.h>

#include <glm/gtx/matrix_decompose.hpp>

namespace Framework::Helper::Math {
    class Matrix4x4 {
    public:
        glm::mat4 self = glm::mat4(1);

        Matrix4x4(const Vector3& translate, const Quaternion& rotation, const Vector3& scale){
            this->self = glm::translate(glm::mat4(1), {
                    translate.x,
                    translate.y,
                    translate.z
            });

            self *= mat4_cast(rotation.ToGLM());

            self = glm::scale(self, scale.ToGLM());
        }

        Matrix4x4(const glm::mat4& mat) {
            this->self = mat;
        }

        Matrix4x4 Inverse() const {
            return glm::inverse(self);
        }

        [[nodiscard]] inline Matrix4x4 RotateAxis(const Vector3& axis, const double& angle) const noexcept {
            return glm::rotate(self, glm::radians((float)angle), axis.ToGLM());
        }
        [[nodiscard]] Matrix4x4 Rotate(const Vector3& angle) const noexcept {
            return self * mat4_cast(angle.ToQuat().ToGLM());
        }

        [[nodiscard]] glm::mat4 ToGLM() const {
            return self;
        }

        [[nodiscard]] Vector3 Translate(const Vector3& vec3) const noexcept {
            return Matrix4x4(glm::translate(self, vec3.ToGLM())).GetTranslate();
        }

        [[nodiscard]] Vector3 GetTranslate() const noexcept {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;

            glm::vec3 skew;
            glm::vec4 perspective;

            glm::decompose(self, scale, rotation, translation, skew, perspective);

            return translation;
        }
        [[nodiscard]] Quaternion GetQuat() const noexcept {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;

            glm::vec3 skew;
            glm::vec4 perspective;

            glm::decompose(self, scale, rotation, translation, skew, perspective);

            return rotation;
        }

        Matrix4x4 operator*(Matrix4x4 mat) {
            return Matrix4x4(this->self * mat.self);
        }
        void operator*=(const Matrix4x4& right) {
            *this = *this * right;
        }

        Matrix4x4 operator/(Matrix4x4 mat) {
            return Matrix4x4(this->self / mat.self);
        }

        Matrix4x4 operator+(Matrix4x4 mat) {
            return Matrix4x4(this->self + mat.self);
        }
        Matrix4x4 operator-(Matrix4x4 mat) {
            return Matrix4x4(this->self - mat.self);
        }
    };
}

#endif //GAMEENGINE_MATRIX4X4_H
