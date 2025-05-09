

# File Matrix4x4.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Math**](dir_3900fe4b4d95d895210b9082ab5cdd34.md) **>** [**Matrix4x4.h**](Matrix4x4_8h.md)

[Go to the documentation of this file](Matrix4x4_8h.md)


```C++
//
// Created by Nikita on 02.03.2021.
//

#ifndef SR_ENGINE_MATH_MATRIX4X4_H
#define SR_ENGINE_MATH_MATRIX4X4_H

#include <Utils/Math/Quaternion.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>

#include <glm/gtx/matrix_decompose.hpp>

namespace SR_MATH_NS {
    class SR_COMMON_DLL_API Matrix4x4 {
        SR_INLINE_STATIC constexpr glm::mat4 GLM_IDENTITY_MAT4X4 = glm::mat4(1); 
    public:
        union {
            SR_MATH_NS::Vector4<float_t> value[4];
            glm::mat4 self;
            struct {
                SR_MATH_NS::Vector4<float_t> right, up, dir, position;
            } v;
            float_t m[4][4];
            struct {
                float_t m00, m01, m02, m03;
                float_t m10, m11, m12, m13;
                float_t m20, m21, m22, m23;
                float_t m30, m31, m32, m33;
            };
        };

        Matrix4x4() noexcept;
        Matrix4x4(FVector4 rows[4]) noexcept; 
        Matrix4x4(const Unit& scalar) noexcept; 
        Matrix4x4(const glm::mat4& mat) noexcept; 
        Matrix4x4(glm::mat4&& mat) noexcept; 
        Matrix4x4(const FVector3& translate, const Quaternion& rotation) noexcept;
        Matrix4x4(const FVector3& translate, const FVector3& scale) noexcept;
        Matrix4x4(const FVector3& translate, const Quaternion& rotation, const FVector3& scale) noexcept;
        Matrix4x4(const Quaternion& rotation, const FVector3& scale) noexcept;
        Matrix4x4(const FVector3& translate, const Quaternion& rotation, const FVector3& scale, const FVector3& skew) noexcept;

        static Matrix4x4 CreateViewMat(Unit pitch = 0, Unit yaw = 0, Unit roll = 0);
        static Matrix4x4 Identity();
        static Matrix4x4 RotationYawPitchRoll(const FVector3& angles);
        static Matrix4x4 Perspective(float_t FOV, float_t aspect, float_t nearValue, float_t farValue);
        static Matrix4x4 FromEulers(const FVector3& eulers);
        static Matrix4x4 Ortho(Unit left, Unit right, Unit bottom, Unit top, Unit zNear, Unit zFar);
        static Matrix4x4 CreateTRS(const SR_MATH_NS::FVector3& translation, const SR_MATH_NS::Quaternion& rotation, const SR_MATH_NS::FVector3& scale);
        static Matrix4x4 LookAt(const SR_MATH_NS::FVector3& eye, const SR_MATH_NS::FVector3& center, const SR_MATH_NS::FVector3& up);
        SR_DEPRECATED_EX("FromQuaternion") static Matrix4x4 FromEulers(const Quaternion& quaternion);
        static Matrix4x4 FromQuaternion(const Quaternion& quaternion);
        static Matrix4x4 RotationAxis(const SR_MATH_NS::FVector4& axis, Unit angle);
        static Matrix4x4 RotationAxis(const SR_MATH_NS::FVector3& axis, Unit angle);
        static Matrix4x4 FromScale(const FVector3& scale);
        static Matrix4x4 FromTranslate(const FVector3& translation);

        SR_NODISCARD Matrix4x4 Inverse() const;
        SR_NODISCARD Matrix4x4 RotateAxis(const FVector3& axis, const double& angle) const;
        SR_NODISCARD Matrix4x4 Rotate(const FVector3& angle) const;
        SR_NODISCARD Matrix4x4 Rotate(const SR_MATH_NS::Quaternion& q) const;
        SR_NODISCARD Matrix4x4 OrthogonalNormalize() const;
        SR_NODISCARD const glm::mat4& ToGLM() const;
        SR_NODISCARD Matrix4x4 Translate(const FVector3& vec3) const;
        SR_NODISCARD FVector4 GetAxis(Axis axis) const;
        SR_NODISCARD FVector3 GetTranslate() const;
        SR_NODISCARD FVector3 GetScale() const;
        SR_NODISCARD bool IsFinite() const;

        bool Decompose(FVector3& translation, Quaternion& quaternion, FVector3& scale) const;
        bool Decompose(FVector3& translation, Quaternion& quaternion) const;
        bool Decompose(FVector3& translation, FVector3& eulers, FVector3& scale) const;
        bool Decompose(FVector3& translation, FVector3& eulers, FVector3& scale, FVector3& skew) const;
        bool Decompose(FVector3& translation, Quaternion& rotation, FVector3& scale, FVector3& skew) const;

        SR_NODISCARD FVector4 TransformPoint(const FVector3& point) const;
        SR_NODISCARD FVector4 TransformVector(const FVector3& point) const;
        SR_NODISCARD FVector4 TransformVector(const FVector4& point) const;
        SR_NODISCARD SR_MATH_NS::Unit GetSegmentLengthClipSpace(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, SR_MATH_NS::Unit displayRatio) const;
        SR_NODISCARD Quaternion GetQuat() const;
        SR_NODISCARD FVector3 GetEulers() const;

        const SR_MATH_NS::FVector4& operator[](int32_t row) const;
        SR_MATH_NS::FVector4& operator[](int32_t row);
        Matrix4x4 operator*(const Matrix4x4& mat) const;
        void operator*=(const Matrix4x4& right);
        Matrix4x4 operator+(const Matrix4x4& mat) const;
        void operator+=(const Matrix4x4& right);
        Matrix4x4 operator*(const Unit& scalar) const;
        void operator*=(const Unit& scalar);
        template<typename U> Vector4<U> operator*(const Vector4<U>& vector4) const;
        template<typename U> void operator*=(const Vector4<U>& vector4);
        Matrix4x4 operator/(Matrix4x4 mat);
        Matrix4x4 operator+(Matrix4x4 mat);
        Matrix4x4 operator-(Matrix4x4 mat);

    };

    SR_MAYBE_UNUSED FVector4 CalcTranslationPlanNormal(const Matrix4x4& model, const SR_MATH_NS::FVector3& cameraEye, const SR_MATH_NS::FVector3& cameraDir, Axis axis);
    SR_MAYBE_UNUSED FVector4 CalcRotationPlanNormal(const Matrix4x4& model, const SR_MATH_NS::FVector3& cameraDir, Axis axis);
    SR_MAYBE_UNUSED FVector4 CalcRotationPlanNormal(const SR_MATH_NS::FVector3& cameraDir, Axis axis);
    SR_MAYBE_UNUSED bool DecomposeTransform(const glm::mat4& matrix, FVector3& translation, FVector3& rotation, FVector3& scale);

    template<typename U> Vector4<U> Matrix4x4::operator*(const Vector4<U>& vector4) const {
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

    template<typename U> void Matrix4x4::operator*=(const Vector4<U>& vector4) {
        *this = *this * vector4;
    }
}

#endif //SR_ENGINE_MATH_MATRIX4X4_H
```


