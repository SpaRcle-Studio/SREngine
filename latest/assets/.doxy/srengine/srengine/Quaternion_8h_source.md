

# File Quaternion.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Math**](dir_3900fe4b4d95d895210b9082ab5cdd34.md) **>** [**Quaternion.h**](Quaternion_8h.md)

[Go to the documentation of this file](Quaternion_8h.md)


```C++
//
// Created by Nikita on 01.03.2021.
//

#ifndef SR_ENGINE_QUATERNION_H
#define SR_ENGINE_QUATERNION_H

#include <Utils/Math/Mathematics.h>

namespace SR_MATH_NS {
    template<typename T> struct Vector3;
    template<typename T> struct Vector4;

    class Matrix4x4;

    class SR_DLL_EXPORT Quaternion {
        friend Vector3<Unit>;
        using T = Unit;
    public:
        union {
            struct {
                float_t x;
                float_t y;
                float_t z;
                float_t w;
            };

            glm::quat self{};
        };
    public:
        SR_NODISCARD SR_FORCE_INLINE glm::quat ToGLM() const noexcept { return self; }
        SR_NODISCARD Vector4<Unit> Vector() const noexcept;
        SR_NODISCARD Matrix4x4 ToMat4x4() const;
        SR_NODISCARD SR_FORCE_INLINE glm::mat4 ToMat4x4GLM() const noexcept { return mat4_cast(self); }
        SR_NODISCARD Vector3<T> EulerAngle() const;
        SR_NODISCARD Quaternion Rotate(const Vector3<T>& v) const;

        SR_NODISCARD Quaternion RotateX(Unit angle) const;
        SR_NODISCARD Quaternion RotateY(Unit angle) const;
        SR_NODISCARD Quaternion RotateZ(Unit angle) const;

        SR_NODISCARD T X() const noexcept { return static_cast<T>(self.x); }
        SR_NODISCARD T Y() const noexcept { return static_cast<T>(self.y); }
        SR_NODISCARD T Z() const noexcept { return static_cast<T>(self.z); }
        SR_NODISCARD T W() const noexcept { return static_cast<T>(self.w); }

        constexpr Quaternion(const Quaternion &p_q)
            : x(p_q.x)
            , y(p_q.y)
            , z(p_q.z)
            , w(p_q.w)
        { }

        constexpr explicit Quaternion(const Matrix4x4& matrix);

        constexpr Quaternion() {
            x = y = z = static_cast<T>(0);
            w = static_cast<T>(1);
        }

        //, bool inRads = false
        Quaternion(const Vector3<Unit> &p_euler);

        Quaternion(const glm::quat &q) {
            self = q;
        }

        Quaternion(const Vector3<Unit>& axis, Unit angle);

        constexpr explicit Quaternion(T x, T y, T z, T w)
            : x(x)
            , y(y)
            , z(z)
            , w(w)
        { }

        static Quaternion FromEuler(const Vector3<Unit>& euler);

        constexpr static Quaternion Identity() {
            return Quaternion(0.0, 0.0, 0.0, 1.0);
        }

        SR_NODISCARD Quaternion Inverse() const {
            return Quaternion(glm::inverse(self));
        }

        SR_NODISCARD SR_FORCE_INLINE bool SR_FASTCALL IsEquals(const Quaternion& q, Unit tolerance) const noexcept {
        #if SR_SIMD_SUPPORT
            // Загружаем компоненты текущего кватерниона и значения в SIMD регистры
            __m128 this_vec = _mm_set_ps(w, z, y, x);
            __m128 value_vec = _mm_set_ps(q.w, q.z, q.y, q.x);

            // Вычисляем разницу между компонентами
            __m128 diff_vec = _mm_sub_ps(this_vec, value_vec);

            // Загружаем допуск в SIMD регистр
            __m128 tolerance_vec = _mm_set1_ps(tolerance);

            // Вычисляем абсолютное значение разницы
            __m128 abs_diff_vec = _mm_andnot_ps(_mm_set1_ps(-0.0f), diff_vec); // получаем abs
            abs_diff_vec = _mm_cmpge_ps(abs_diff_vec, tolerance_vec); // сравниваем на больше или равно по модулю

            // Проверяем, все ли компоненты проходят проверку на равенство
            int mask = _mm_movemask_ps(abs_diff_vec); // применяем маску
            return mask == 0; // если все 0, то результаты совпадают
        #else
            if (!SR_EQUALS_T(x, q.x, tolerance)) {
                return false;
            }

            if (!SR_EQUALS_T(y, q.y, tolerance)) {
                return false;
            }

            if (!SR_EQUALS_T(z, q.z, tolerance)) {
                return false;
            }

            if (!SR_EQUALS_T(w, q.w, tolerance)) {
                return false;
            }

            SR_NOOP;

            return true;
        #endif
        }

        SR_NODISCARD Quaternion Slerp(const Quaternion& q, Unit t) const {
        #if SR_SIMD_SUPPORT
            // Load q1 and q2 into SIMD registers
            __m128 q1_vec = _mm_set_ps(w, z, y, x); // Загрузка в обратном порядке для корректного выравнивания
            __m128 q2_vec = _mm_set_ps(q.w, q.z, q.y, q.x); // Загрузка в обратном порядке для корректного выравнивания

            // Compute the dot product
            __m128 dot_vec = _mm_dp_ps(q1_vec, q2_vec, 0xFF); // Вычисление dot product с использованием SIMD

            // Распаковка результатов
            float dot_result;
            _mm_store_ss(&dot_result, dot_vec);

            // Если dot product отрицателен, инвертируем один кватернион
            __m128 q2_copy = q2_vec;
            if (dot_result < 0.0f) {
                q2_copy = _mm_mul_ps(q2_vec, _mm_set1_ps(-1.0f));
                dot_result = -dot_result;
            }

            const float DOT_THRESHOLD = 0.9995f;
            if (dot_result > DOT_THRESHOLD) {
                // Если кватернионы слишком близки, выполняем линейную интерполяцию и нормализацию результата
                __m128 result_vec = _mm_add_ps(q1_vec, _mm_mul_ps(_mm_sub_ps(q2_copy, q1_vec), _mm_set1_ps(t)));
                float result_array[4];
                _mm_store_ps(result_array, result_vec);
                Quaternion result(result_array[0], result_array[1], result_array[2], result_array[3]);
                return result.Normalized();
            }

            // Вычисляем угол и sin(theta)
            float theta_0 = std::acos(dot_result); // Угол между входными векторами
            float theta = theta_0 * t;      // Угол между q1 и результатом
            float sin_theta = std::sin(theta);        // Вычисляем значение только один раз
            float sin_theta_0 = std::sin(theta_0);    // Вычисляем значение только один раз

            float s0 = std::cos(theta) - dot_result * sin_theta / sin_theta_0;  // == sin(theta_0 - theta) / sin(theta_0)
            float s1 = sin_theta / sin_theta_0;

            // Интерполируем
            __m128 s0_vec = _mm_set1_ps(s0);
            __m128 s1_vec = _mm_set1_ps(s1);
            __m128 interp_vec = _mm_add_ps(_mm_mul_ps(q1_vec, s0_vec), _mm_mul_ps(q2_copy, s1_vec));

            // Сохраняем результат
            float result_array[4];
            _mm_store_ps(result_array, interp_vec);
            return Quaternion(result_array[0], result_array[1], result_array[2], result_array[3]);
        #else
            return glm::slerp(self, q.self, static_cast<float_t>(t));
        #endif
        }

        SR_NODISCARD static Quaternion LookAt(const Vector3<Unit>& direction);
        SR_NODISCARD static Quaternion LookAt(const Vector3<Unit>& direction, const Vector3<Unit>& up);

        SR_NODISCARD Quaternion Normalized() const {
            return Normalize();
        }

        SR_NODISCARD Quaternion Normalize() const {
            return Quaternion(glm::normalize(self));
        }

        SR_NODISCARD Unit Roll() const noexcept {
            return static_cast<Unit>(atan2(static_cast<Unit>(2) * (x * y + w * z), w * w + x * x - y * y - z * z));
        }

        SR_NODISCARD Unit Pitch() const noexcept;
        SR_NODISCARD Unit SquaredNorm() const noexcept;

        SR_NODISCARD Unit Yaw() const noexcept {
            return asin(SR_CLAMP(static_cast<Unit>(-2) * (x * z - w * y), static_cast<Unit>(-1), static_cast<Unit>(1)));
        }

        SR_NODISCARD std::string ToString() const {
            return "(" + std::to_string(self.x) + ", " + std::to_string(self.y) + ", " + std::to_string(self.z) + ", " + std::to_string(self.w) + ")";
        }

        SR_FORCE_INLINE bool operator!=(const Quaternion& q) const noexcept {
            return !(*this == q);
        }

        SR_FORCE_INLINE bool operator==(const Quaternion& q) const noexcept {
            return
                SR_EQUALS(x, q.x) &&
                SR_EQUALS(y, q.y) &&
                SR_EQUALS(z, q.z) &&
                SR_EQUALS(w, q.w);
        }

        SR_NODISCARD Unit SR_FASTCALL Distance(const Quaternion& q) const;

        SR_NODISCARD Unit SR_FASTCALL Angle(const Quaternion& q) const {
            return Distance(q);
        }

        SR_NODISCARD bool IsFinite() const noexcept {
            return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w);
        }

        SR_NODISCARD bool IsIdentity() const noexcept {
            return
                SR_EQUALS(x, 1.f) &&
                SR_EQUALS(y, 1.f) &&
                SR_EQUALS(z, 1.f) &&
                SR_EQUALS(w, 1.f);
        }

        SR_FORCE_INLINE void operator+=(const Quaternion &p_q) {
            self += p_q.self;
        }
        SR_FORCE_INLINE void operator-=(const Quaternion &p_q) {
            self -= p_q.self;
        }
        SR_FORCE_INLINE void operator*=(const Quaternion &p_q) {
            self *= p_q.self;
        }
        SR_FORCE_INLINE void operator*=(const double &s){
            self *= s;
        }
        SR_FORCE_INLINE void operator/=(const double &s) {
            self *= 1.0 / s;
        }
        SR_FORCE_INLINE Quaternion operator+(const Quaternion &q2) const {
            const Quaternion &q1 = *this;
            return Quaternion(q1.self + q2.self);
        }
        SR_FORCE_INLINE Quaternion operator-(const Quaternion &q2) const {
            const Quaternion &q1 = *this;
            return Quaternion(q1.self - q2.self);
        }
        SR_FORCE_INLINE Quaternion operator-() const {
            const Quaternion &q2 = *this;
            return Quaternion(-q2.self);
        }
        SR_FORCE_INLINE Quaternion operator*(const double &s) const {
            glm::quat q = self;
            q *= s;
            return Quaternion(q);
        }
        SR_FORCE_INLINE Quaternion operator/(const double &s) const {
            glm::quat q = self;
            q *= 1.0 / s;
            return Quaternion(q);
        }

        Vector3<Unit> operator*(const Vector3<Unit> &v) const noexcept;
        Vector3<Unit> operator/(const Vector3<Unit> &v) const;
        Quaternion operator*(const Quaternion& rhs) const {
            return Quaternion(self * rhs.self);
        }
    };

    inline static const Quaternion InfinityQuaternion = Quaternion { UnitMAX, UnitMAX, UnitMAX, UnitMAX };
}

#endif //SR_ENGINE_QUATERNION_H
```


