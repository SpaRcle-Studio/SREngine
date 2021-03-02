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

        [[nodiscard]] Matrix4x4 Rotate(const Vector3& angle) const {
            return self * mat4_cast(angle.ToQuat().ToGLM());
        }

        [[nodiscard]] Quaternion GetQuat() const {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;

            glm::vec3 skew;
            glm::vec4 perspective;

            glm::decompose(self, scale, rotation, translation, skew, perspective);

            return rotation;
        }
    };
}

#endif //GAMEENGINE_MATRIX4X4_H
