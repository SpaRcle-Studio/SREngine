//
// Created by Monika on 16.01.2023.
//

#include <Utils/Math/Matrix4x4.h>

namespace SR_MATH_NS {
    #ifdef SR_SUPPORT_PARALLEL
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 SR_FASTCALL MultiplyGLMMat4x4(const glm::mat4& m1, const glm::mat4& m2) noexcept {
            glm::mat4 result;

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

            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    #pragma omp section
                    {
                        DstB0.x = SrcA0.x * SrcB0.x + SrcA1.x * SrcB0.y + SrcA2.x * SrcB0.z + SrcA3.x * SrcB0.w;
                    }
                    #pragma omp section
                    {
                        DstB0.y = SrcA0.y * SrcB0.x + SrcA1.y * SrcB0.y + SrcA2.y * SrcB0.z + SrcA3.y * SrcB0.w;
                    }
                    #pragma omp section
                    {
                        DstB0.z = SrcA0.z * SrcB0.x + SrcA1.z * SrcB0.y + SrcA2.z * SrcB0.z + SrcA3.z * SrcB0.w;
                    }
                    #pragma omp section
                    {
                        DstB0.w = SrcA0.w * SrcB0.x + SrcA1.w * SrcB0.y + SrcA2.w * SrcB0.z + SrcA3.w * SrcB0.w;
                    }
                }
                #pragma omp section
                {
                    #pragma omp section
                    {
                        DstB1.x = SrcA0.x * SrcB1.x + SrcA1.x * SrcB1.y + SrcA2.x * SrcB1.z + SrcA3.x * SrcB1.w;
                    }
                    #pragma omp section
                    {
                        DstB1.y = SrcA0.y * SrcB1.x + SrcA1.y * SrcB1.y + SrcA2.y * SrcB1.z + SrcA3.y * SrcB1.w;
                    }
                    #pragma omp section
                    {
                        DstB1.z = SrcA0.z * SrcB1.x + SrcA1.z * SrcB1.y + SrcA2.z * SrcB1.z + SrcA3.z * SrcB1.w;
                    }
                    #pragma omp section
                    {
                        DstB1.w = SrcA0.w * SrcB1.x + SrcA1.w * SrcB1.y + SrcA2.w * SrcB1.z + SrcA3.w * SrcB1.w;
                    }
                }
                #pragma omp section
                {
                    #pragma omp section
                    {
                        DstB2.x = SrcA0.x * SrcB2.x + SrcA1.x * SrcB2.y + SrcA2.x * SrcB2.z + SrcA3.x * SrcB2.w;
                    }
                    #pragma omp section
                    {
                        DstB2.y = SrcA0.y * SrcB2.x + SrcA1.y * SrcB2.y + SrcA2.y * SrcB2.z + SrcA3.y * SrcB2.w;
                    }
                    #pragma omp section
                    {
                        DstB2.z = SrcA0.z * SrcB2.x + SrcA1.z * SrcB2.y + SrcA2.z * SrcB2.z + SrcA3.z * SrcB2.w;
                    }
                    #pragma omp section
                    {
                        DstB2.w = SrcA0.w * SrcB2.x + SrcA1.w * SrcB2.y + SrcA2.w * SrcB2.z + SrcA3.w * SrcB2.w;
                    }
                }
                #pragma omp section
                {
                    #pragma omp section
                    {
                        DstB3.x = SrcA0.x * SrcB3.x + SrcA1.x * SrcB3.y + SrcA2.x * SrcB3.z + SrcA3.x * SrcB3.w;
                    }
                    #pragma omp section
                    {
                        DstB3.y = SrcA0.y * SrcB3.x + SrcA1.y * SrcB3.y + SrcA2.y * SrcB3.z + SrcA3.y * SrcB3.w;
                    }
                    #pragma omp section
                    {
                        DstB3.z = SrcA0.z * SrcB3.x + SrcA1.z * SrcB3.y + SrcA2.z * SrcB3.z + SrcA3.z * SrcB3.w;
                    }
                    #pragma omp section
                    {
                        DstB3.w = SrcA0.w * SrcB3.x + SrcA1.w * SrcB3.y + SrcA2.w * SrcB3.z + SrcA3.w * SrcB3.w;
                    }
                }
            }

            return result;
        }
    #endif

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
        self = glm::translate(self, {
                translate.x,
                translate.y,
                translate.z
        });

        self = SR_MATH_NS::MultiplyGLMMat4x4(self, mat4_cast(rotation.ToGLM()));
        self = glm::scale(self, scale.ToGLM());
    }

    Matrix4x4::Matrix4x4(const FVector3& translate, const Quaternion& rotation, const FVector3& scale, const FVector3& skew) noexcept
        : Matrix4x4()
    {
        self = glm::translate(self, {
                translate.x,
                translate.y,
                translate.z
        });

        self = glm::scale(self, skew.ToGLM());
        self = SR_MATH_NS::MultiplyGLMMat4x4(self, mat4_cast(rotation.ToGLM()));
        self = glm::scale(self, scale.ToGLM());
    }

    Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const {
#ifdef SR_SUPPORT_PARALLEL
        return Matrix4x4(MultiplyGLMMat4x4(self, mat.self));
#else
        return Matrix4x4(self * mat.self);
#endif
    }
}