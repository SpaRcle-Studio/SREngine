//
// Created by Nikita on 02.03.2021.
//

#ifndef GAMEENGINE_MATRIX4X4_H
#define GAMEENGINE_MATRIX4X4_H

#include <Utils/Math/Quaternion.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>

#include <glm/gtx/matrix_decompose.hpp>

namespace SR_MATH_NS {
    class SR_DLL_EXPORT Matrix4x4 {
        SR_INLINE_STATIC const glm::mat4 GLM_IDENTITY_MAT4X4 = glm::mat4(1); /** NOLINT */
    public:
        static Matrix4x4 CreateViewMat(Unit pitch = 0, Unit yaw = 0, Unit roll = 0) {
            auto matrix = glm::rotate(glm::mat4(1), (float)pitch, { 1, 0, 0 });
            matrix = glm::rotate(matrix,            (float)yaw,   { 0, 1, 0 });
            matrix = glm::rotate(matrix,            (float)roll,  { 0, 0, 1 });
            return Matrix4x4(glm::translate(matrix, { 0, 0, 0 }));
        }

        union {
            SR_MATH_NS::Vector4<float> value[4];
            glm::mat4 self;
        };

        constexpr Matrix4x4() noexcept;
        explicit constexpr Matrix4x4(const Unit& scalar) noexcept;
        explicit constexpr Matrix4x4(const glm::mat4& mat) noexcept;
        explicit Matrix4x4(glm::mat4&& mat) noexcept;

        Matrix4x4(const FVector3& translate, const Quaternion& rotation) noexcept;
        Matrix4x4(const FVector3& translate, const Quaternion& rotation, const FVector3& scale) noexcept;
        Matrix4x4(const FVector3& translate, const Quaternion& rotation, const FVector3& scale, const FVector3& skew) noexcept;

        static constexpr Matrix4x4 Identity() {
            return Matrix4x4(1);
        }

        static Matrix4x4 RotationYawPitchRoll(const FVector3& angles) {
            return Matrix4x4(0.f, angles.ToQuat(), 1.f);
        }

        static Matrix4x4 Perspective(float_t FOV, float_t aspect, float_t nearValue, float_t farValue) {
            return Matrix4x4(glm::perspective(FOV, aspect, nearValue, farValue));
        }

        static Matrix4x4 FromEulers(const FVector3& eulers) {
            return RotationYawPitchRoll(eulers.Radians());
        }

        static Matrix4x4 Ortho(Unit left, Unit right, Unit bottom, Unit top, Unit zNear, Unit zFar) {
            Matrix4x4 result = Matrix4x4::Identity();
            result[0][0] = Unit(2) / (right - left);
            result[1][1] = Unit(2) / (top - bottom);
            result[2][2] = - Unit(2) / (zFar - zNear);
            result[3][0] = - (right + left) / (right - left);
            result[3][1] = - (top + bottom) / (top - bottom);
            result[3][2] = - (zFar + zNear) / (zFar - zNear);
            return result;
        }

        static Matrix4x4 LookAt(const SR_MATH_NS::FVector3& eye, const SR_MATH_NS::FVector3& center, const SR_MATH_NS::FVector3& up) {
            return Matrix4x4(glm::lookAt(eye.ToGLM(), center.ToGLM(), up.ToGLM()));
        }

        static Matrix4x4 FromEulers(const Quaternion& quaternion) {
            return Matrix4x4(0.f, quaternion, 1.f);
        }

        static Matrix4x4 FromScale(const FVector3& scale) {
            return Matrix4x4(glm::scale(glm::mat4x4(1), scale.ToGLM()));
        }

        static Matrix4x4 FromTranslate(const FVector3& translation) {
            return Matrix4x4(translation, FVector3::Zero(), FVector3::One());
        }

        SR_NODISCARD Matrix4x4 Inverse() const {
            return Matrix4x4(glm::inverse(self));
        }

        SR_NODISCARD Matrix4x4 RotateAxis(const FVector3& axis, const double& angle) const {
            return Matrix4x4(glm::rotate(self, glm::radians((float)angle), axis.ToGLM()));
        }

        SR_NODISCARD Matrix4x4 Rotate(const FVector3& angle) const {
            return Matrix4x4(self * mat4_cast(angle.ToQuat().ToGLM()));
        }

        SR_NODISCARD Matrix4x4 Rotate(const SR_MATH_NS::Quaternion& q) const {
            return Matrix4x4(*this * q.ToMat4x4());
        }

        SR_NODISCARD const glm::mat4& ToGLM() const {
            return self;
        }

        SR_NODISCARD Matrix4x4 Translate(const FVector3& vec3) const {
            return Matrix4x4(glm::translate(self, vec3.ToGLM()));
        }

        SR_NODISCARD FVector3 GetTranslate() const {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;

            glm::vec3 skew;
            glm::vec4 perspective;

            glm::decompose(self, scale, rotation, translation, skew, perspective);

            return FVector3(translation);
        }

        SR_NODISCARD FVector3 GetScale() const {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;

            glm::vec3 skew;
            glm::vec4 perspective;

            glm::decompose(self, scale, rotation, translation, skew, perspective);

            return FVector3(scale);
        }

        bool Decompose(FVector3& translation, Quaternion& quaternion, FVector3& scale) const {
            translation = glm::vec3(self[3]);

            scale[0] = glm::length(glm::vec3(self[0]));
            scale[1] = glm::length(glm::vec3(self[1]));
            scale[2] = glm::length(glm::vec3(self[2]));

            const glm::mat3 rotMtx(
                    glm::vec3(self[0]) / static_cast<float>(scale[0]),
                    glm::vec3(self[1]) / static_cast<float>(scale[1]),
                    glm::vec3(self[2]) / static_cast<float>(scale[2]));

            quaternion = glm::quat_cast(rotMtx);

            return true;
        }

        bool Decompose(FVector3& translation, Quaternion& quaternion) const {
            translation = glm::vec3(self[3]);

            auto&& scaleX = glm::length(glm::vec3(self[0]));
            auto&& scaleY = glm::length(glm::vec3(self[1]));
            auto&& scaleZ = glm::length(glm::vec3(self[2]));

            const glm::mat3 rotMtx(
                    glm::vec3(self[0]) / static_cast<float_t>(scaleX),
                    glm::vec3(self[1]) / static_cast<float_t>(scaleY),
                    glm::vec3(self[2]) / static_cast<float_t>(scaleZ)
            );

            quaternion = glm::quat_cast(rotMtx);

            return true;
        }

        bool Decompose(FVector3& translation, FVector3& eulers, FVector3& scale) const {
            translation = glm::vec3(self[3]);

            scale[0] = glm::length(glm::vec3(self[0]));
            scale[1] = glm::length(glm::vec3(self[1]));
            scale[2] = glm::length(glm::vec3(self[2]));

            const glm::mat3 rotMtx(
                    glm::vec3(self[0]) / static_cast<float>(scale[0]),
                    glm::vec3(self[1]) / static_cast<float>(scale[1]),
                    glm::vec3(self[2]) / static_cast<float>(scale[2]));

            eulers = glm::eulerAngles(glm::normalize(glm::quat_cast(rotMtx)));
            eulers = eulers.Degrees();

            return true;
        }

        bool Decompose(FVector3& translation, FVector3& eulers, FVector3& scale, FVector3& skew) const {
            //glm::vec3 _scale;
            //glm::quat _rotation;
            //glm::vec3 _translation;

            //glm::vec3 _skew;
            //glm::vec4 _perspective;

            //if (glm::decompose(self, _scale, _rotation, _translation, _skew, _perspective)) {
            //    translation = _translation;
            //    eulers = Quaternion(_rotation).EulerAngle();
            //    scale = scale;
            //    skew = _skew;
            //    return true;
            //}

            // return false

            translation = glm::vec3(self[3]);

            scale[0] = glm::length(glm::vec3(self[0]));
            scale[1] = glm::length(glm::vec3(self[1]));
            scale[2] = glm::length(glm::vec3(self[2]));

            const glm::mat3 rotMtx(
                    glm::vec3(self[0]) / static_cast<float>(scale[0]),
                    glm::vec3(self[1]) / static_cast<float>(scale[1]),
                    glm::vec3(self[2]) / static_cast<float>(scale[2]));

            eulers = glm::eulerAngles(glm::normalize(glm::quat_cast(rotMtx)));
            eulers = eulers.Degrees();

            return true;
        }

        bool Decompose(FVector3& translation, Quaternion& rotation, FVector3& scale, FVector3& skew) const {
            glm::vec3 _scale;
            glm::quat _rotation;
            glm::vec3 _translation;

            glm::vec3 _skew;
            glm::vec4 _perspective;

            if (glm::decompose(self, _scale, _rotation, _translation, _skew, _perspective)) {
                translation = _translation;
                rotation = _rotation;
                scale = _scale;
                skew = _skew;
                return true;
            }

            return false;
        }

        SR_NODISCARD Quaternion GetQuat() const {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;

            glm::vec3 skew;
            glm::vec4 perspective;

            glm::decompose(self, scale, rotation, translation, skew, perspective);

            return Quaternion(rotation);
        }

        SR_NODISCARD FVector3 GetEulers() const {
            return GetQuat().EulerAngle();
        }

        SR_FORCE_INLINE const SR_MATH_NS::FVector4& operator[](int32_t row) const {
            return value[row];
        }

        SR_FORCE_INLINE SR_MATH_NS::FVector4& operator[](int32_t row) {
            return value[row];
        }

        Matrix4x4 operator*(const Matrix4x4& mat) const;
        void operator*=(const Matrix4x4& right) {
            *this = *this * right;
        }

        Matrix4x4 operator+(const Matrix4x4& mat) const {
            return Matrix4x4(self + mat.self);
        }
        void operator+=(const Matrix4x4& right) {
            *this = *this + right;
        }

        Matrix4x4 operator*(const Unit& scalar) const {
            return Matrix4x4(self * static_cast<float>(scalar));
        }
        void operator*=(const Unit& scalar) {
            *this = *this * static_cast<float>(scalar);
        }

        template<typename U> Vector4<U> operator*(const Vector4<U>& vector4) const {
            const glm::vec4 v = self * glm::vec4(
                    static_cast<float>(vector4.x),
                    static_cast<float>(vector4.y),
                    static_cast<float>(vector4.z),
                    static_cast<float>(vector4.w)
            );
            return Vector4<U>(
                    static_cast<U>(v.x),
                    static_cast<U>(v.y),
                    static_cast<U>(v.z),
                    static_cast<U>(v.w)
            );
        }
        template<typename U> void operator*=(const Vector4<U>& vector4) {
            *this = *this * vector4;
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

    static bool DecomposeTransform(const glm::mat4& matrix, FVector3& translation, FVector3& rotation, FVector3& scale);

    SR_MAYBE_UNUSED bool DecomposeTransform(const glm::mat4 &matrix, FVector3 &translation, FVector3 &rotation, FVector3 &scale) {
        // From glm::decompose in matrix_decompose.inl

        using namespace glm;
        using T = float;

        mat4 LocalMatrix(matrix);

        // Normalize the matrix.
        if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
            return false;

        // First, isolate perspective.  This is the messiest.
        if (
                epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
                epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
                epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
        {
            // Clear the perspective partition
            LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
            LocalMatrix[3][3] = static_cast<T>(1);
        }

        // Next take care of translation (easy).
        translation = vec3(LocalMatrix[3]);
        LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

        vec3 Row[3];

        // Now get scale and shear.
        for (length_t i = 0; i < 3; ++i)
            for (length_t j = 0; j < 3; ++j)
                Row[i][j] = LocalMatrix[i][j];

        // Compute X scale factor and normalize first row.
        scale.x = length(Row[0]);
        Row[0] = detail::scale(Row[0], static_cast<T>(1));
        scale.y = length(Row[1]);
        Row[1] = detail::scale(Row[1], static_cast<T>(1));
        scale.z = length(Row[2]);
        Row[2] = detail::scale(Row[2], static_cast<T>(1));

        rotation.y = asin(-Row[0][2]);
        if (cos(rotation.y) != 0) {
            rotation.x = atan2(Row[1][2], Row[2][2]);
            rotation.z = atan2(Row[0][1], Row[0][0]);
        }
        else {
            rotation.x = atan2(-Row[2][0], Row[1][1]);
            rotation.z = 0;
        }

        return true;
    }
}

#endif //GAMEENGINE_MATRIX4X4_H
