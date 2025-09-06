

# File Vector3.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Math**](dir_f20ff43999c2f98e3f122645c07885db.md) **>** [**Vector3.h**](Vector3_8h.md)

[Go to the documentation of this file](Vector3_8h.md)


```C++
//
// Created by Nikita on 01.03.2021.
//

#ifndef SR_ENGINE_VECTOR3_H
#define SR_ENGINE_VECTOR3_H

#include <Utils/Math/Vector2.h>
#include <Utils/Math/Quaternion.h>

namespace SR_MATH_NS {
    template<typename T> struct Vector3 {
    public:
        using ValueType = T;

        union {
            struct {
                T x;
                T y;
                T z;
            };

            T coord[3] = { 0 };
        };
    public:
        Vector3();

        Vector3(const Vector3<T>& vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }

        template<typename U> explicit Vector3(const Vector3<U>& vec) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
            z = static_cast<T>(vec.z);
        }

        template<typename U> explicit Vector3(const Vector2<U>& vec, U value) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
            z = static_cast<T>(value);
        }

        explicit Vector3(const float* vec) {
            x = (Unit)vec[0];
            y = (Unit)vec[1];
            z = (Unit)vec[2];
        }
        explicit Vector3(const uint8_t* axis) {
            x = (Unit)axis[0];
            y = (Unit)axis[1];
            z = (Unit)axis[2];
        }

        Vector3(T p_x, T p_y, T p_z) {
            x = p_x;
            y = p_y;
            z = p_z;
        }

        Vector3(T p) {
            x = p;
            y = p;
            z = p;
        }

        Vector3(const glm::vec3& v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }

    public:
        template<typename U> static Vector3<T> XY(const Vector2<U>& v, U value) {
            return Vector3<T>(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(value));
        }
        template<typename U> static Vector3<T> XZ(const Vector2<U>& v, U value) {
            return Vector3<T>(static_cast<T>(v.x), static_cast<T>(value), static_cast<T>(v.y));
        }
        template<typename U> static Vector3<T> YZ(const Vector2<U>& v, U value) {
            return Vector3<T>(static_cast<T>(value), static_cast<T>(v.x), static_cast<T>(v.y));
        }

        static Vector3<T> Zero() { return Vector3(static_cast<T>(0)); }
        static Vector3<T> One() { return Vector3(static_cast<T>(1)); }

        static Vector3<T> UnitX() { return Vector3(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }
        static Vector3<T> UnitY() { return Vector3(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }
        static Vector3<T> UnitZ() { return Vector3(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); }

        static Vector3<T> Right() { return UnitX(); }
        static Vector3<T> Up() { return UnitY(); }
        static Vector3<T> Forward() { return UnitZ(); }

        static Vector3<T> AxisByIndex(uint8_t axis) {
            switch (axis) {
                case 0: return UnitX();
                case 1: return UnitY();
                case 2: return UnitZ();
                default:
                    return Zero();
            }
        }

        template<typename U> static Vector3<T> XY(const Vector2<U>& v) { return XY(v, 0); }
        template<typename U> static Vector3<T> XZ(const Vector2<U>& v) { return XZ(v, 0); }
        template<typename U> static Vector3<T> YZ(const Vector2<U>& v) { return YZ(v, 0); }

    public:
        template<typename U> SR_NODISCARD Vector3<U> SR_FASTCALL Cast() const noexcept { return Vector3<U>(
                static_cast<U>(x), static_cast<U>(y), static_cast<U>(z)
            );
        }

        SR_NODISCARD Vector3<int32_t> CastToInt() const noexcept { return Cast<int32_t>(); }
        SR_NODISCARD Vector3<float_t> CastToFloat() const noexcept { return Cast<float_t>(); }
        SR_NODISCARD Vector3<uint32_t> CastToUInt() const noexcept { return Cast<uint32_t>(); }

        SR_NODISCARD T X() const noexcept { return x; }
        SR_NODISCARD T Y() const noexcept { return y; }
        SR_NODISCARD T Z() const noexcept { return z; }

        SR_NODISCARD T& X() noexcept { return x; }
        SR_NODISCARD T& Y() noexcept { return y; }
        SR_NODISCARD T& Z() noexcept { return z; }

        SR_NODISCARD Vector2<T> XY() const { return Vector2<T>(x, y); }
        SR_NODISCARD Vector2<T> XZ() const { return Vector2<T>(x, z); }
        SR_NODISCARD Vector2<T> YZ() const { return Vector2<T>(y, z); }

        SR_NODISCARD Vector3 Singular(const Vector3& segment) const { return Vector3(
                     x > 0 ? x + segment.x : x - segment.x,
                     y > 0 ? y + segment.y : y - segment.y,
                     z > 0 ? z + segment.z : z - segment.z
                );
        }
        SR_NODISCARD Vector3 DeSingular(const Vector3& segment) const { return Vector3(
                    x > 0 ? x - segment.x : x,
                    y > 0 ? y - segment.y : y,
                    z > 0 ? z - segment.z : z
            );
        }

        SR_NODISCARD T Max() const { return x > y && x > z ? x : y > x && y > z ? y : z; }
        SR_NODISCARD T Min() const { return x < y && x < z ? x : y < x && y < z ? y : z; }

        SR_NODISCARD Vector3<T> Max3() const { return Vector3<T>(Max()); }
        SR_NODISCARD Vector3<T> Min3() const { return Vector3<T>(Min()); }

        SR_NODISCARD bool Empty() const {
            return (x == 0 && y == 0 && z == 0);
        }

        SR_NODISCARD bool HasZero() const {
            return (x == 0 || y == 0 || z == 0);
        }

        SR_NODISCARD bool IsInfinity() const {
            return (x == UnitMAX && y == UnitMAX && z == UnitMAX); // TODO
        }

        SR_NODISCARD Vector3 Min(const Vector3& v) const {
            return Vector3(
                x < v.x ? x : v.x,
                y < v.y ? y : v.y,
                z < v.z ? z : v.z
            );
        }

        SR_NODISCARD Vector3 Max(const Vector3& v) const {
            return Vector3(
                x > v.x ? x : v.x,
                y > v.y ? y : v.y,
                z > v.z ? z : v.z
            );
        }

        SR_NODISCARD Vector3 Radians() const noexcept {
            return { static_cast<T>(SR_RAD(x)), static_cast<T>(SR_RAD(y)), static_cast<T>(SR_RAD(z)) };
        }
        SR_NODISCARD Vector3 Degrees() const noexcept {
            return { static_cast<T>(SR_DEG(x)), static_cast<T>(SR_DEG(y)), static_cast<T>(SR_DEG(z)) };
        }

        SR_NODISCARD T AngleCoefficientRadians(const Vector3& vector3) const {
            const T dot = Dot(vector3);
            const T length1 = Length();
            const T length2 = vector3.Length();

            if (length1 == static_cast<T>(0) || length2 == static_cast<T>(0)) {
                return 0.0;
            }

            const T angle = std::acos(dot / (length1 * length2));
            return angle;
        }

        SR_NODISCARD T AngleCoefficientEuler(const Vector3& vector3) const {
            return SR_DEG(AngleCoefficientRadians(vector3));
        }

        SR_NODISCARD T AngleCoefficient(const Vector3& vector3) const {
            const T coefficient = std::cos(AngleCoefficientRadians(vector3));
            return coefficient;
        }

        SR_NODISCARD Quaternion LookAt(const Vector3& target) const {
            const auto&& direction = (target - *this).Normalized();
            const auto&& cosAngle = UnitZ().Dot(direction);

            if (cosAngle >= 1.0 - static_cast<T>(SR_EPSILON)) {
                return Quaternion::Identity();
            }

            else if (cosAngle <= -1.0 + static_cast<T>(SR_EPSILON)) {
                return Quaternion(UnitY(), SR_PI);
            }

            const auto&& axis = UnitZ().Cross(direction);
            const auto&& angle = std::acos(cosAngle);

            return Quaternion(axis, angle);
        }

        SR_NODISCARD T SqrMagnitude() const { return x * x + y * y + z * z; }

        SR_NODISCARD T Angle(const Vector3<T>& to) const {
            if constexpr (std::is_same_v<T, bool>) {
                return static_cast<T>(0); 
            }
            else {

                const T denominator = static_cast<T>(sqrt(SqrMagnitude() * to.SqrMagnitude()));
                if (denominator < static_cast<T>(SR_EPSILON_NORMAL_SQRT)) {
                    return static_cast<T>(0);
                }

                const T dot = SR_CLAMP(Dot(to) / denominator, static_cast<T>(-1), static_cast<T>(1));
                return static_cast<T>(std::acos(dot) * SR_RAD_2_DEG);
            }
        }

        /*SR_NODISCARD Vector3<T> Angle(const Vector3<T>& vector3) {
            Vector3 angle;

            angle.x = (T)(std::atan2(vector3.y, vector3.z) - atan2(y, z));
            angle.y = (T)(std::atan2(vector3.x, vector3.z) - atan2(x, z));
            angle.z = (T)(std::atan2(vector3.y, vector3.x) - atan2(y, x));

            Vector3 degrees = Vector3(T(180)) * angle / SR_PI;
            return (Vector3(T(360)) + degrees.Round()) % Vector3(T(360));
        }*/

        SR_NODISCARD Vector3<T> ProjectOnPlane(const Vector3<T>& planeNormal) const {
            if constexpr (std::is_same_v<T, bool>) {
                return static_cast<T>(0); 
            }
            else {
                const T sqrMag = planeNormal.Dot(planeNormal);

                if (sqrMag < SR_EPSILON) {
                    return *this;
                }

                auto &&dot = Dot(planeNormal);

                return Vector3(
                        x - planeNormal.x * dot / sqrMag,
                        y - planeNormal.y * dot / sqrMag,
                        z - planeNormal.z * dot / sqrMag
                );
            }
        }

        SR_NODISCARD T SignedAngle(const Vector3& to, const Vector3& axis) const {
            const T unsignedAngle = Angle(to);

            const T cross_x = y * to.z - z * to.y;
            const T cross_y = z * to.x - x * to.z;
            const T cross_z = x * to.y - y * to.x;
            const T sign = SR_MATH_NS::Sign(axis.x * cross_x + axis.y * cross_y + axis.z * cross_z);

            return unsignedAngle * sign;
        }

        SR_NODISCARD Quaternion AngleAxis(const Vector3& target, const Vector3& axis = Vector3::UnitZ()) const {
            auto&& direction = (target - *this).Normalized();

            auto&& crossAxis = axis.Cross(direction);
            const Unit angle = acos(axis.Dot(direction));

            return Quaternion(crossAxis, angle);
        }

        SR_NODISCARD std::string ToString() const {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
        }

        SR_NODISCARD T SR_FASTCALL Distance(const Vector3& point) const {
            return sqrt(
                    pow(point.x - x, 2) +
                    pow(point.y - y, 2) +
                    pow(point.z - z, 2)
            );
        }

        SR_NODISCARD Vector3 Direction(const Vector3& point) const {
            if (point == *this)
                return Vector3();
            Vector3 heading = point - (*this);
            T distance = Magnitude(heading);
            return heading / distance;
        }

        SR_NODISCARD bool IsEquals(const Vector3& value, Unit tolerance) const noexcept {
        #if SR_SIMD_SUPPORT
            // Загружаем компоненты текущего вектора и значения в SIMD регистры
            __m128 this_vec = _mm_set_ps(0.0f, z, y, x); // загружаем в обратном порядке для корректного выравнивания
            __m128 value_vec = _mm_set_ps(0.0f, value.z, value.y, value.x); // загружаем в обратном порядке для корректного выравнивания

            // Вычисляем разницу между компонентами
            __m128 diff_vec = _mm_sub_ps(this_vec, value_vec);

            // Загружаем допуск в SIMD регистр
            __m128 tolerance_vec = _mm_set1_ps(tolerance);

            // Вычисляем абсолютное значение разницы
            __m128 abs_diff_vec = _mm_andnot_ps(_mm_set1_ps(-0.0f), diff_vec); // получаем abs
            abs_diff_vec = _mm_cmpge_ps(abs_diff_vec, tolerance_vec); // сравниваем на больше или равно по модулю

            // Проверяем, все ли компоненты проходят проверку на равенство
            const int mask = _mm_movemask_ps(abs_diff_vec); // применяем маску
            return mask == 0; // если все 0, то результаты совпадают
        #else
            if (!SR_EQUALS_T(x, value.x, tolerance)) {
                return false;
            }

            if (!SR_EQUALS_T(y, value.y, tolerance)) {
                return false;
            }

            if (!SR_EQUALS_T(z, value.z, tolerance)) {
                return false;
            }

            SR_NOOP;

            return true;
        #endif
        }

        SR_NODISCARD bool IsEqualsLikely(const Vector3& value, Unit tolerance) const noexcept {
            if (!SR_EQUALS_T(x, value.x, tolerance)) SR_UNLIKELY_ATTRIBUTE {
                return false;
            }

            if (!SR_EQUALS_T(y, value.y, tolerance)) SR_UNLIKELY_ATTRIBUTE {
                return false;
            }

            if (!SR_EQUALS_T(z, value.z, tolerance)) SR_UNLIKELY_ATTRIBUTE {
                return false;
            }

            return true;
        }

        SR_NODISCARD Vector3 Limits(int lim) const {
            int xi = (int)x / lim;
            int yi = (int)y / lim;
            int zi = (int)z / lim;

            T xd = x - lim * (T)xi;
            T yd = y - lim * (T)yi;
            T zd = z - lim * (T)zi;

            return Vector3(xd, yd, zd);
        }

        SR_NODISCARD bool IsFinite() const noexcept {
            return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
        }

        SR_NODISCARD bool ContainsNaN() const {
            return static_cast<float>(x) == SR_NAN || static_cast<float>(y) == SR_NAN || static_cast<float>(z) == SR_NAN;
        }

        SR_NODISCARD Vector3<T> Inverse() const {
            if constexpr (std::is_same_v<T, bool>) {
                return static_cast<T>(0); 
            }
            else {
                return Vector3(-x, -y, -z);
            }
        }

        SR_NODISCARD Vector3 SR_FASTCALL InverseAxis(Axis axis) const {
            Vector3 v = *this;

            switch (axis) {
                case Axis::X: v[0] = -v[0]; break;
                case Axis::Y: v[1] = -v[1]; break;
                case Axis::Z: v[2] = -v[2]; break;
                case Axis::XY: {
                    v[0] = -v[0];
                    v[1] = -v[1];
                    break;
                }
                case Axis::YZ: {
                    v[1] = -v[1];
                    v[2] = -v[2];
                    break;
                }
                case Axis::XZ: {
                    v[0] = -v[0];
                    v[2] = -v[2];
                    break;
                }
                case Axis::XYZ: {
                    v[0] = -v[0];
                    v[1] = -v[1];
                    v[2] = -v[2];
                    break;
                }
                default:
                    break;
            }

            return v;
        }

        SR_NODISCARD Vector3 SR_FASTCALL Swap(Axis axis) const {
            Vector3 v = *this;

            switch (axis) {
                case Axis::XY: std::swap(v.x, v.y); break;
                case Axis::YZ: std::swap(v.y, v.z); break;
                case Axis::XZ: std::swap(v.x, v.z); break;
                default:
                    break;
            }

            return v;
        }

        SR_NODISCARD Vector3 ZeroAxis(Axis axis) const {
            Vector3 v = *this;

            switch (axis) {
                case Axis::X: v[0] = 0; break;
                case Axis::Y: v[1] = 0; break;
                case Axis::Z: v[2] = 0; break;
                case Axis::XY: v[0] = v[1] = 0; break;
                case Axis::XZ: v[0] = v[1] = 0; break;
                case Axis::YZ: v[1] = v[2] = 0; break;
                case Axis::XYZ: v[0] = v[1] = v[2] = 0; break;
                default:
                    break;
            }

            return v;
        }

        SR_NODISCARD SR_FORCE_INLINE Vector3<T> SR_FASTCALL Lerp(const Vector3<T>& vector3, float_t t) const noexcept {
            if constexpr (!std::is_same_v<T, float_t>) {
                return *this;
            }
            else {
            #if SR_SIMD_SUPPORT
                const __m128 t_vec = _mm_set1_ps(t);
                const __m128 this_vec = _mm_set_ps(0.0f, z, y, x); // Вектор this, добавляем 0.0f для выравнивания
                const __m128 other_vec = _mm_set_ps(0.0f, vector3.z, vector3.y, vector3.x); // Вектор vector3, добавляем 0.0f для выравнивания

                const __m128 diff_vec = _mm_sub_ps(other_vec, this_vec); // vector3 - *this
                const __m128 mul_vec = _mm_mul_ps(diff_vec, t_vec); // (vector3 - *this) * t
                const __m128 result_vec = _mm_add_ps(this_vec, mul_vec); // *this + ((vector3 - *this) * t)

                alignas(16) float result_array[4];
                _mm_store_ps(result_array, result_vec); // Сохраняем результат в массив

                return { result_array[0], result_array[1], result_array[2] }; // Извлекаем значения из массива
            #else
                return static_cast<Vector3>(*this + (vector3 - *this) * t);
            #endif
            }
        }

        SR_NODISCARD Vector3<T> Normalized() const {
            return Normalize();
        }

        SR_NODISCARD Vector3<T> Normalize() const {
            if constexpr (std::is_same_v<T, bool>) {
                return *this; 
            }
            else {
                auto&& value = x * x + y * y + z * z;

                if (value > 0) {
                    const T len = static_cast<T>(std::sqrt(value));
                    Vector3 vec3 = *this;

                    if (len != static_cast<T>(0.)) {
                        vec3.x /= len;
                        vec3.y /= len;
                        vec3.z /= len;
                    }

                    return vec3;
                }

                return *this;
            }
        }

        SR_NODISCARD T SquaredNorm() const noexcept {
            return x * x + y * y + z * z;
        }

        SR_NODISCARD Vector3<T> Clamp(const Vector3<T>& upper, const Vector3<T>& lover) const {
            return Vector3<T>(
                SR_CLAMP(x, lover.x, upper.x),
                SR_CLAMP(y, lover.y, upper.y),
                SR_CLAMP(z, lover.z, upper.z)
            );
        }

        SR_NODISCARD Quaternion ToQuat() const;

        SR_FORCE_INLINE const T &operator[](int p_axis) const {
            return coord[p_axis];
        }

        SR_FORCE_INLINE T &operator[](int p_axis) {
            return coord[p_axis];
        }

        SR_NODISCARD SR_FORCE_INLINE T Length() const {
            if constexpr (std::is_same_v<T, float_t> || std::is_same_v<T, float>) {
                return static_cast<T>(sqrtf(x * x + y * y + z * z));
            }
            else {
                return static_cast<T>(sqrt(x * x + y * y + z * z));
            }
        }

        SR_NODISCARD Vector3 Replace(int from, int to) const {
            return Vector3(
                    x == from ? to : x,
                    y == from ? to : y,
                    z == from ? to : z);
        }

        SR_NODISCARD Vector3<T> Abs() const {
            return Vector3(static_cast<T>(SR_ABS(x)), static_cast<T>(SR_ABS(y)), static_cast<T>(SR_ABS(z)));
        }

        SR_NODISCARD Vector3<T> Sin() const {
            return Vector3(static_cast<T>(sin(x)), static_cast<T>(sin(y)), static_cast<T>(sin(z)));
        }

        SR_NODISCARD Vector3<T> Cos() const {
            return Vector3(static_cast<T>(cos(x)), static_cast<T>(cos(y)), static_cast<T>(cos(z)));
        }

        SR_NODISCARD Vector3<T> Round() const {
            return Vector3(static_cast<T>(std::round(x)), static_cast<T>(std::round(y)), static_cast<T>(std::round(z)));
        }

        SR_NODISCARD Vector3 FixEulerAngles() const {
            return Vector3(FixAxis(x), FixAxis(y), FixAxis(z));
        }

        SR_NODISCARD T Dot(const Vector3<T>& p_b) const { return x * p_b.x + y * p_b.y + z * p_b.z; }

        SR_NODISCARD Vector3<T> Cross(const Vector3<T>& p_b) const {
            Vector3 ret(
                    (y * p_b.z) - (z * p_b.y),
                    (z * p_b.x) - (x * p_b.z),
                    (x * p_b.y) - (y * p_b.x));

            return ret;
        }

        SR_NODISCARD Vector3<T> Rotate(const Quaternion& q) const;

        template<typename U> SR_FORCE_INLINE Vector3<T>& SR_FASTCALL TemplateOperatorPlusAssign(const Vector3<U> &p_v){
            if constexpr (!std::is_same_v<T, bool>) {
                x += static_cast<T>(p_v.x);
                y += static_cast<T>(p_v.y);
                z += static_cast<T>(p_v.z);
            }
            return *this;
        }

        SR_FORCE_INLINE Vector3<T>& SR_FASTCALL operator+=(const Vector3<float_t>& p_v) { return TemplateOperatorPlusAssign(p_v); }
        SR_FORCE_INLINE Vector3<T>& SR_FASTCALL operator+=(const Vector3<int32_t>& p_v) { return TemplateOperatorPlusAssign(p_v); }
        SR_FORCE_INLINE Vector3<T>& SR_FASTCALL operator+=(const Vector3<uint32_t>& p_v) { return TemplateOperatorPlusAssign(p_v); }

        template<typename U> SR_FORCE_INLINE Vector3<T> SR_FASTCALL TemplateOperatorPlus(const Vector3<U>& p_v) const noexcept {
            return Vector3<T>(x + static_cast<T>(p_v.x), y + static_cast<T>(p_v.y), z + static_cast<T>(p_v.z));
        }

        SR_FORCE_INLINE Vector3<T> SR_FASTCALL operator+(const Vector3<float_t>& p_v) const noexcept { return TemplateOperatorPlus(p_v); }
        SR_FORCE_INLINE Vector3<T> SR_FASTCALL operator+(const Vector3<int32_t>& p_v) const noexcept { return TemplateOperatorPlus(p_v); }
        SR_FORCE_INLINE Vector3<T> SR_FASTCALL operator+(const Vector3<uint32_t>& p_v) const noexcept { return TemplateOperatorPlus(p_v); }

        template<typename U> SR_FORCE_INLINE Vector3 operator%(const Vector3<U> &p_v) const {
            return Vector3(
                    static_cast<int32_t>(x) % static_cast<int32_t>(p_v.x),
                    static_cast<int32_t>(y) % static_cast<int32_t>(p_v.y),
                    static_cast<int32_t>(z) % static_cast<int32_t>(p_v.z)
                );
        }

        template<typename U> SR_FORCE_INLINE Vector3 &operator-=(const Vector3<U> &p_v) {
            x -= p_v.x;
            y -= p_v.y;
            z -= p_v.z;
            return *this;
        }
        template<typename U> SR_FORCE_INLINE Vector3 operator-(const Vector3<U> &p_v) const {
            return Vector3(x - p_v.x, y - p_v.y, z - p_v.z);
        }
        template<typename U> SR_FORCE_INLINE Vector3 &operator*=(const Vector3<U> &p_v) {
            x *= p_v.x;
            y *= p_v.y;
            z *= p_v.z;
            return *this;
        }
        template<typename U> SR_FORCE_INLINE Vector3 &operator%=(const Vector3<U> &p_v) {
            x %= p_v.x;
            y %= p_v.y;
            z %= p_v.z;
            return *this;
        }

        template<typename U> SR_FORCE_INLINE Vector3 operator*(const Vector3<U> &p_v) const {
            return Vector3(x * p_v.x, y * p_v.y, z * p_v.z);
        }

        template<typename U> SR_FORCE_INLINE Vector3 &operator/=(const Vector3<U> &p_v) {
            x /= p_v.x;
            y /= p_v.y;
            z /= p_v.z;
            return *this;
        }
        template<typename U> SR_FORCE_INLINE Vector3 operator/(const Vector3<U> &p_v) const {
            return Vector3(x / p_v.x, y / p_v.y, z / p_v.z);
        }

        template<typename U> SR_FORCE_INLINE Vector3 &operator*=(U p_scalar) {
            x *= p_scalar;
            y *= p_scalar;
            z *= p_scalar;
            return *this;
        }
        template<typename U> SR_FORCE_INLINE Vector3 operator*(U p_scalar) const {
            return Vector3(x * p_scalar, y * p_scalar, z * p_scalar);
        }
        template<typename U> SR_FORCE_INLINE Vector3 &operator/=(U p_scalar) {
            x /= p_scalar;
            y /= p_scalar;
            z /= p_scalar;
            return *this;
        }
        template<typename U> SR_FORCE_INLINE Vector3 operator/(U p_scalar) const {
            return Vector3(x / p_scalar, y / p_scalar, z / p_scalar);
        }

        template<typename U> SR_FORCE_INLINE bool operator>(U p_scalar) const { return *this > Vector3<U>(p_scalar); }
        template<typename U> SR_FORCE_INLINE bool operator<(U p_scalar) const { return *this < Vector3<U>(p_scalar); }
        template<typename U> SR_FORCE_INLINE bool operator>=(U p_scalar) const { return *this >= Vector3<U>(p_scalar); }
        template<typename U> SR_FORCE_INLINE bool operator<=(U p_scalar) const { return *this <= Vector3<U>(p_scalar); }
        template<typename U> SR_FORCE_INLINE bool operator==(U p_scalar) const { return *this == Vector3<U>(p_scalar); }
        template<typename U> SR_FORCE_INLINE bool operator!=(U p_scalar) const { return *this != Vector3<U>(p_scalar); }

        SR_FORCE_INLINE Vector3<T> operator-() const {
            if constexpr (std::is_same_v<T, bool>) {
                return *this;
            }
            else {
                return Vector3(-x, -y, -z);
            }
        }
        SR_FORCE_INLINE Vector3<T> operator+() const { return *this; }

        SR_FORCE_INLINE bool operator==(const Vector3<T>& p_v) const { return SR_EQUALS(x, p_v.x) && SR_EQUALS(y, p_v.y) && SR_EQUALS(z, p_v.z); }
        SR_FORCE_INLINE bool operator!=(const Vector3<T>& p_v) const { return !SR_EQUALS(x, p_v.x) || !SR_EQUALS(y, p_v.y) || !SR_EQUALS(z, p_v.z); }

        SR_FORCE_INLINE bool operator<=(const Vector3<T>& p_v) const { return x <= p_v.x && y <= p_v.y && z <= p_v.z; }
        SR_FORCE_INLINE bool operator>=(const Vector3<T>& p_v) const { return x >= p_v.x && y >= p_v.y && z >= p_v.z; }
        SR_FORCE_INLINE bool operator<(const Vector3<T>& p_v) const { return x < p_v.x && y < p_v.y && z < p_v.z; }
        SR_FORCE_INLINE bool operator>(const Vector3<T>& p_v) const { return x > p_v.x && y > p_v.y && z > p_v.z; }

    public:
        SR_NODISCARD glm::vec3 ToGLM() const noexcept {
            return *reinterpret_cast<glm::vec3*>((void*)this);
        }
        static Unit Magnitude(Vector3 vec) {
            return sqrt(SR_SQUARE(vec.x) + SR_SQUARE(vec.y) + SR_SQUARE(vec.z));
        }

        static T Dot(Vector3 lhs, Vector3 rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
        static Vector3 Cross(const Vector3 &p_a, const Vector3 &p_b) {
            Vector3 ret(
                    (p_a.y * p_b.z) - (p_a.z * p_b.y),
                    (p_a.z * p_b.x) - (p_a.x * p_b.z),
                    (p_a.x * p_b.y) - (p_a.y * p_b.x));
            return ret;
        }

        static T FixAxis(T axis) {
            if (axis == 0)
                return static_cast<T>(CMP_BIG_EPSILON);

            T absolute = std::abs(axis);
            if (SR_EQUALS(absolute, 90) || SR_EQUALS(absolute, 180) || SR_EQUALS(absolute, 270) || SR_EQUALS(absolute, 360))
                return axis - static_cast<T>(CMP_BIG_EPSILON);

            return axis;
        }
    };

    typedef Vector3<Unit> FVector3;
    typedef Vector3<int32_t> IVector3;
    typedef Vector3<uint32_t> UVector3;
    typedef Vector3<bool> BVector3;

    SR_INLINE static const FVector3 InfinityFV3 = FVector3 { UnitMAX, UnitMAX, UnitMAX };
    SR_INLINE static const FVector3 CmpEpsilonFV3 = FVector3 {
            static_cast<Unit>(CMP_EPSILON),
            static_cast<Unit>(CMP_EPSILON),
            static_cast<Unit>(CMP_EPSILON),
    };

    template<typename T> Vector3<T>::Vector3() {
        x = 0;
        y = 0;
        z = 0;
    }

#ifdef SR_COMMON_DLL_EXPORTS
    // bool inRads
    template<typename T>
    Quaternion Vector3<T>::ToQuat() const {
        return Quaternion(*this); //, inRads
    }

    template<typename T>
    Vector3<T> Vector3<T>::Rotate(const Quaternion &q) const  {
        // Extract the vector part of the quaternion
        Vector3 u(q.self.x, q.self.y, q.self.z);

        // Extract the scalar part of the quaternion
        auto s = q.self.w;

        Vector3 v = *this;

        // Do the math
        return u * 2.0f * Dot(u, v)
               + v * (s*s - Dot(u, u))
               + Cross(u, v) * 2.0f * s;
    }
#endif
}

namespace std {
    template <class T> static inline void hash_vector3_combine(std::size_t & s, const T & v) {
        std::hash<T> h;
        s^= h(v) + 0x9e3779b9 + (s<< 6) + (s>> 2);
    }

    template<typename U> struct hash<SR_MATH_NS::Vector3<U>> {
        size_t operator()(SR_MATH_NS::Vector3<U> const& vec) const {
            std::size_t res = 0;
            hash_vector3_combine<U>(res, vec.x);
            hash_vector3_combine<U>(res, vec.y);
            hash_vector3_combine<U>(res, vec.z);
            return res;
        }
    };
}

#endif //SR_ENGINE_VECTOR3_H
```


