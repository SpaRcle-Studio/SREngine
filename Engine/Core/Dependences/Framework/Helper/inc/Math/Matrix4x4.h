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
        static Matrix4x4 CreateViewMat(Unit pitch = 0, Unit yaw = 0, Unit roll = 0) {
            auto matrix = glm::rotate(glm::mat4(1), (float)pitch, { 1, 0, 0 });
            matrix = glm::rotate(matrix,            (float)yaw,   { 0, 1, 0 });
            matrix = glm::rotate(matrix,            (float)roll,  { 0, 0, 1 });
            return Matrix4x4(glm::translate(matrix, { 0, 0, 0 }));
        }

        glm::mat4 self = glm::mat4(1);

        Matrix4x4(const FVector3& translate, const Quaternion& rotation, const FVector3& scale){
            this->self = glm::translate(glm::mat4(1), {
                    translate.x,
                    translate.y,
                    translate.z
            });

            self *= mat4_cast(rotation.ToGLM());

            self = glm::scale(self, scale.ToGLM());
        }

        explicit Matrix4x4(const Unit& scalar) {
            this->self = glm::mat4((float)scalar);
        }

        explicit Matrix4x4(const glm::mat4& mat) {
            this->self = mat;
        }

        [[nodiscard]] Matrix4x4 Inverse() const {
            return Matrix4x4(glm::inverse(self));
        }

        [[nodiscard]] Matrix4x4 RotateAxis(const FVector3& axis, const double& angle) const {
            return Matrix4x4(glm::rotate(self, glm::radians((float)angle), axis.ToGLM()));
        }
        [[nodiscard]] Matrix4x4 Rotate(const FVector3& angle) const {
            return Matrix4x4(self * mat4_cast(angle.ToQuat().ToGLM()));
        }

        [[nodiscard]] glm::mat4 ToGLM() const {
            return self;
        }

        [[nodiscard]] Matrix4x4 Translate(const FVector3& vec3) const {
            return Matrix4x4(glm::translate(self, vec3.ToGLM()));
        }

        [[nodiscard]] FVector3 GetTranslate() const {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;

            glm::vec3 skew;
            glm::vec4 perspective;

            glm::decompose(self, scale, rotation, translation, skew, perspective);

            return FVector3(translation);
        }
        [[nodiscard]] Quaternion GetQuat() const {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;

            glm::vec3 skew;
            glm::vec4 perspective;

            glm::decompose(self, scale, rotation, translation, skew, perspective);

            return Quaternion(rotation);
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
