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
    class SR_DLL_EXPORT Matrix4x4 {
        SR_INLINE_STATIC constexpr glm::mat4 GLM_IDENTITY_MAT4X4 = glm::mat4(1); /** NOLINT */
    public:
        static Matrix4x4 CreateViewMat(Unit pitch = 0, Unit yaw = 0, Unit roll = 0) {
            auto matrix = glm::rotate(glm::mat4(1), (float_t)pitch, { 1, 0, 0 });
            matrix = glm::rotate(matrix,            (float_t)yaw,   { 0, 1, 0 });
            matrix = glm::rotate(matrix,            (float_t)roll,  { 0, 0, 1 });
            return Matrix4x4(glm::translate(matrix, { 0, 0, 0 }));
        }

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

        constexpr Matrix4x4() noexcept
            : self(GLM_IDENTITY_MAT4X4)
        { }

        constexpr Matrix4x4(const Unit& scalar) noexcept /// NOLINT
            : self(glm::mat4(static_cast<float_t>(scalar)))
        { }

        constexpr Matrix4x4(const glm::mat4& mat) noexcept /// NOLINT
            : self(mat)
        { }

        Matrix4x4(glm::mat4&& mat) noexcept /// NOLINT
            : self(mat)
        { }

        Matrix4x4(const FVector3& translate, const Quaternion& rotation) noexcept;
        Matrix4x4(const FVector3& translate, const Quaternion& rotation, const FVector3& scale) noexcept;
        Matrix4x4(const FVector3& translate, const Quaternion& rotation, const FVector3& scale, const FVector3& skew) noexcept;

        static constexpr Matrix4x4 Identity() {
            return Matrix4x4(1); /// NOLINT
        }

        static Matrix4x4 RotationYawPitchRoll(const FVector3& angles) {
            return Matrix4x4(0.f, angles.ToQuat(), 1.f); /// NOLINT
        }

        static Matrix4x4 Perspective(float_t FOV, float_t aspect, float_t nearValue, float_t farValue) {
            return Matrix4x4(glm::perspective(FOV, aspect, nearValue, farValue)); /// NOLINT
        }

        static Matrix4x4 FromEulers(const FVector3& eulers) {
            return RotationYawPitchRoll(eulers.Radians());
        }

        static Matrix4x4 Ortho(Unit left, Unit right, Unit bottom, Unit top, Unit zNear, Unit zFar) {
            Matrix4x4 Result(1);
            Result[0][0] = static_cast<Unit>(2) / (right - left);
            Result[1][1] = static_cast<Unit>(2) / (top - bottom);
            Result[3][0] = - (right + left) / (right - left);
            Result[3][1] = - (top + bottom) / (top - bottom);

        #if GLM_DEPTH_CLIP_SPACE == GLM_DEPTH_ZERO_TO_ONE
            Result[2][2] = - static_cast<Unit>(1) / (zFar - zNear);
            Result[3][2] = - zNear / (zFar - zNear);
        #else
            Result[2][2] = - static_cast<T>(2) / (zFar - zNear);
			Result[3][2] = - (zFar + zNear) / (zFar - zNear);
        #endif

            return Result;
        }

        static Matrix4x4 LookAt(const SR_MATH_NS::FVector3& eye, const SR_MATH_NS::FVector3& center, const SR_MATH_NS::FVector3& up) {
            return Matrix4x4(glm::lookAtRH(eye.ToGLM(), center.ToGLM(), up.ToGLM()));
        }

        SR_DEPRECATED_EX("FromQuaternion") static Matrix4x4 FromEulers(const Quaternion& quaternion) {
            return Matrix4x4(0.f, quaternion, 1.f);
        }

        static Matrix4x4 FromQuaternion(const Quaternion& quaternion) {
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

        SR_NODISCARD Matrix4x4 OrthogonalNormalize() const {
            Matrix4x4 copy = *this;
            copy.v.right = copy.v.right.Normalize();
            copy.v.up = copy.v.up.Normalize();
            copy.v.dir = copy.v.dir.Normalize();
            return copy;
        }

        SR_NODISCARD const glm::mat4& ToGLM() const {
            return self;
        }

        SR_NODISCARD Matrix4x4 Translate(const FVector3& vec3) const {
            return Matrix4x4(glm::translate(self, vec3.ToGLM()));
        }

        SR_NODISCARD FVector4 GetAxis(AxisFlag axis) const {
            switch (axis) {
                case Axis::X: return value[0];
                case Axis::Y: return value[1];
                case Axis::Z: return value[2];
                default:
                    SRHalt("Wrong axis!");
                    return SR_MATH_NS::FVector4();
            }
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

        SR_NODISCARD FVector4 TransformPoint(const FVector3& point) const {
            FVector4 out;
            out.x = point.x * m00 + point.y * m10 + point.z * m20 + m30;
            out.y = point.x * m01 + point.y * m11 + point.z * m21 + m31;
            out.z = point.x * m02 + point.y * m12 + point.z * m22 + m32;
            out.w = point.x * m03 + point.y * m13 + point.z * m23 + m33;
            return out;
        }

        SR_NODISCARD FVector4 TransformVector(const FVector3& point) const {
            FVector4 out;
            out.x = point.x * m00 + point.y * m10 + point.z * m20;
            out.y = point.x * m01 + point.y * m11 + point.z * m21;
            out.z = point.x * m02 + point.y * m12 + point.z * m22;
            out.w = point.x * m03 + point.y * m13 + point.z * m23;
            return out;
        }

        SR_NODISCARD FVector4 TransformVector(const FVector4& point) const {
            FVector4 out;
            out.x = point.x * m00 + point.y * m10 + point.z * m20 + point.w * m30;
            out.y = point.x * m01 + point.y * m11 + point.z * m21 + point.w * m31;
            out.z = point.x * m02 + point.y * m12 + point.z * m22 + point.w * m32;
            out.w = point.x * m03 + point.y * m13 + point.z * m23 + point.w * m33;
            return out;
        }

        SR_NODISCARD SR_MATH_NS::Unit GetSegmentLengthClipSpace(
            const SR_MATH_NS::FVector3& start,
            const SR_MATH_NS::FVector3& end,
            SR_MATH_NS::Unit displayRatio
        ) const {
            auto&& startOfSegment = TransformPoint(start);
            if (fabsf(startOfSegment.w) > SR_FLT_EPSILON) {
                startOfSegment *= 1.f / startOfSegment.w;
            }

            auto&& endOfSegment = TransformPoint(end);
            if (fabsf(endOfSegment.w) > SR_FLT_EPSILON) {
                endOfSegment *= 1.f / endOfSegment.w;
            }

            auto&& clipSpaceAxis = (endOfSegment - startOfSegment).XY();

            if (displayRatio < 1.0) {
                clipSpaceAxis.x *= displayRatio;
            }
            else {
                clipSpaceAxis.y /= displayRatio;
            }

            const SR_MATH_NS::Unit segmentLengthInClipSpace = sqrtf(clipSpaceAxis.x * clipSpaceAxis.x + clipSpaceAxis.y * clipSpaceAxis.y);
            return segmentLengthInClipSpace;
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

    static FVector4 CalcPlanNormal(const Matrix4x4& model, const SR_MATH_NS::FVector3& cameraEye, const SR_MATH_NS::FVector3& cameraDir, AxisFlag axis) {
        SR_MATH_NS::FVector4 movePlanNormal[] = {
            model.v.right, // x
            model.v.up,    // y
            model.v.dir,   // z
            model.v.right, // yz
            model.v.up,    // zx
            model.v.dir,   // xy
            SR_MATH_NS::FVector4(-cameraDir, 0.f) // screen (xyz)
        };

        auto&& cameraToModelNormalized = SR_MATH_NS::FVector4((model.v.position.XYZ() - cameraEye).Normalize(), 0.f);

        for (uint8_t i = 0; i < 3; ++i) {
            auto&& orthogonalVector = movePlanNormal[i].Cross(cameraToModelNormalized);
            movePlanNormal[i] = (movePlanNormal[i].Cross(orthogonalVector)).Normalize();
        }

        switch (axis) {
            case Axis::XYZ: return movePlanNormal[6];
            case Axis::YZ: return movePlanNormal[3];
            case Axis::XZ: return movePlanNormal[4];
            case Axis::XY: return movePlanNormal[5];
            case Axis::X: return movePlanNormal[0];
            case Axis::Y: return movePlanNormal[1];
            case Axis::Z: return movePlanNormal[2];
            default:
                break;
        }

        SRHalt("Unknown axis!");

        return SR_MATH_NS::FVector4();
    }

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

#endif //SR_ENGINE_MATH_MATRIX4X4_H
