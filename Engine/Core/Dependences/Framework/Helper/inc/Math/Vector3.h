//
// Created by Nikita on 01.03.2021.
//

#ifndef GAMEENGINE_VECTOR3_H
#define GAMEENGINE_VECTOR3_H

#include <Math/Vector2.h>
#include <Utils/GraphUtils.h>
#include <Math/Quaternion.h>

namespace Framework::Helper::Math {
    template<typename T> struct Vector3 {
    public:
        union {
            struct {
                T x;
                T y;
                T z;
            };

            T coord[3] = { 0 };
        };
    public:
        constexpr _FORCE_INLINE_ Vector3() {
            x = 0;
            y = 0;
            z = 0;
        }
        template<typename U> constexpr _FORCE_INLINE_ explicit Vector3(const Vector3<U>& vec) {
            x = static_cast<T>(vec.x);
            y = static_cast<T>(vec.y);
            z = static_cast<T>(vec.z);
        }
        _FORCE_INLINE_ constexpr explicit Vector3(const float* vec) {
            x = (Unit)vec[0];
            y = (Unit)vec[1];
            z = (Unit)vec[2];
        }
        _FORCE_INLINE_ constexpr explicit Vector3(const uint8_t* axis) {
            x = (Unit)axis[0];
            y = (Unit)axis[1];
            z = (Unit)axis[2];
        }
        _FORCE_INLINE_ constexpr Vector3(T p_x, T p_y, T p_z) {
            x = p_x;
            y = p_y;
            z = p_z;
        }
        _FORCE_INLINE_ constexpr Vector3(T p) {
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

        static constexpr Vector3<T> Zero() { return Vector3(static_cast<T>(0)); }
        static constexpr Vector3<T> One() { return Vector3(static_cast<T>(1)); }

        template<typename U> static Vector3<T> XY(const Vector2<U>& v) { return XY(v, 0); }
        template<typename U> static Vector3<T> XZ(const Vector2<U>& v) { return XZ(v, 0); }
        template<typename U> static Vector3<T> YZ(const Vector2<U>& v) { return YZ(v, 0); }

    public:
        template<typename U> [[nodiscard]] Vector3<U> Cast() const { return Vector3<U>(
                    static_cast<U>(x),
                    static_cast<U>(y),
                    static_cast<U>(z)
                );
        }

        [[nodiscard]] Vector2<T> XY() const { return Vector2<T>(x, y); }
        [[nodiscard]] Vector2<T> XZ() const { return Vector2<T>(x, z); }
        [[nodiscard]] Vector2<T> YZ() const { return Vector2<T>(y, z); }

        [[nodiscard]] Vector3 Singular(const Vector3& segment) const { return Vector3(
                     x > 0 ? x + segment.x : x - segment.x,
                     y > 0 ? y + segment.y : y - segment.y,
                     z > 0 ? z + segment.z : z - segment.z
                );
        }
        [[nodiscard]] Vector3 DeSingular(const Vector3& segment) const { return Vector3(
                    x > 0 ? x - segment.x : x,
                    y > 0 ? y - segment.y : y,
                    z > 0 ? z - segment.z : z
            );
        }

        [[nodiscard]] T Max() const {
            return x > y && x > z ? x : y > x && y > z ? y : z;
        }
        [[nodiscard]] T Min() const {
            return x < y && x < z ? x : y < x && y < z ? y : z;
        }

        [[nodiscard]] bool Empty() const {
            return (x == 0 && y == 0 && z == 0);
        }

        [[nodiscard]] bool HasZero() const {
            return (x == 0 || y == 0 || z == 0);
        }

        [[nodiscard]] bool IsInfinity() const {
            return (x == UnitMAX && y == UnitMAX && z == UnitMAX); // TODO
        }

        [[nodiscard]] Vector3 Radians() const {
            return { static_cast<T>(RAD(x)), static_cast<T>(RAD(y)), static_cast<T>(RAD(z)) };
        }
        [[nodiscard]] Vector3 Degrees() const {
            return { static_cast<T>(DEG(x)), static_cast<T>(DEG(y)), static_cast<T>(DEG(z)) };
        }

        [[nodiscard]] std::string ToString() const {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
        }

        [[nodiscard]] T Distance(Vector3 point) const {
            return sqrt(
                    pow(point.x - x, 2) +
                    pow(point.y - y, 2) +
                    pow(point.z - z, 2)
            );
        }

        [[nodiscard]] Vector3 Direction(Vector3 point) const {
            if (point == *this)
                return Vector3();
            Vector3 heading = point - (*this);
            T distance = Magnitude(heading);
            return heading / distance;
        }

        [[nodiscard]] Vector3 Limits(int lim) const {
            int xi = (int)x / lim;
            int yi = (int)y / lim;
            int zi = (int)z / lim;

            T xd = x - lim * (T)xi;
            T yd = y - lim * (T)yi;
            T zd = z - lim * (T)zi;

            return Vector3(xd, yd, zd);
        }

        [[nodiscard]] bool ContainsNaN() const {
            return static_cast<float>(x) == SR_NAN || static_cast<float>(y) == SR_NAN || static_cast<float>(z) == SR_NAN;
        }

        [[nodiscard]] Vector3 Inverse() const {
            return Vector3(-x, -y, -z);
        }

        [[nodiscard]] Vector3 InverseAxis(uint8_t axis) const {
            Vector3 v = *this;
            v[axis] = -v[axis];
            return v;
        }
        [[nodiscard]] Vector3 ZeroAxis(Axis axis) const {
            Vector3 v = *this;
            v[static_cast<int>(axis) - 1] = 0;
            return v;
        }

        [[nodiscard]] Vector3 Normalize() const {
            T len = static_cast<T>(std::sqrt(x * x + y * y + z * z));

            Vector3 vec3 = *this;

            if (len != static_cast<T>(0.)) {
                vec3.x /= len;
                vec3.y /= len;
                vec3.z /= len;
            }

            return vec3;
        }

        //bool inRads = false
        [[nodiscard]] Quaternion ToQuat() const;

        _FORCE_INLINE_ const T &operator[](int p_axis) const {
            return coord[p_axis];
        }

        _FORCE_INLINE_ T &operator[](int p_axis) {
            return coord[p_axis];
        }

        [[nodiscard]] _FORCE_INLINE_ T Length() const {
            return static_cast<T>(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
        }

        [[nodiscard]] Vector3 Replace(int from, int to) const {
            return Vector3(
                    x == from ? to : x,
                    y == from ? to : y,
                    z == from ? to : z);
        }

        [[nodiscard]] Vector3 Abs() const {
            return Vector3(static_cast<T>(abs(x)), static_cast<T>(abs(y)), static_cast<T>(abs(z)));
        }

        [[nodiscard]] Vector3 FixEulerAngles() const {
            return Vector3(FixAxis(x), FixAxis(y), FixAxis(z));
        }

        [[nodiscard]] T Dot(Vector3 p_b) const { return x * p_b.x + y * p_b.y + z * p_b.z; }

        [[nodiscard]] Vector3 Cross(const Vector3 &p_b) const {
            Vector3 ret(
                    (y * p_b.z) - (z * p_b.y),
                    (z * p_b.x) - (x * p_b.z),
                    (x * p_b.y) - (y * p_b.x));

            return ret;
        }

        [[nodiscard]] Vector3<T> Rotate(const Quaternion& q) const;

        template<typename U> _FORCE_INLINE_ Vector3 &operator+=(const Vector3<U> &p_v){
            x += p_v.x;
            y += p_v.y;
            z += p_v.z;
            return *this;
        }
        template<typename U> _FORCE_INLINE_ Vector3 operator+(const Vector3<U> &p_v) const {
            return Vector3(x + p_v.x, y + p_v.y, z + p_v.z);
        }
        template<typename U> _FORCE_INLINE_ Vector3 operator%(const Vector3<U> &p_v) const {
            return Vector3(
                    static_cast<int32_t>(x) % static_cast<int32_t>(p_v.x),
                    static_cast<int32_t>(y) % static_cast<int32_t>(p_v.y),
                    static_cast<int32_t>(z) % static_cast<int32_t>(p_v.z)
                );
        }

        template<typename U> _FORCE_INLINE_ Vector3 &operator-=(const Vector3<U> &p_v) {
            x -= p_v.x;
            y -= p_v.y;
            z -= p_v.z;
            return *this;
        }
        template<typename U> _FORCE_INLINE_ Vector3 operator-(const Vector3<U> &p_v) const {
            return Vector3(x - p_v.x, y - p_v.y, z - p_v.z);
        }
        template<typename U> _FORCE_INLINE_ Vector3 &operator*=(const Vector3<U> &p_v) {
            x *= p_v.x;
            y *= p_v.y;
            z *= p_v.z;
            return *this;
        }
        template<typename U> _FORCE_INLINE_ Vector3 &operator%=(const Vector3<U> &p_v) {
            x %= p_v.x;
            y %= p_v.y;
            z %= p_v.z;
            return *this;
        }

        template<typename U> _FORCE_INLINE_ Vector3 operator*(const Vector3<U> &p_v) const {
            return Vector3(x * p_v.x, y * p_v.y, z * p_v.z);
        }

        template<typename U> _FORCE_INLINE_ Vector3 &operator/=(const Vector3<U> &p_v) {
            x /= p_v.x;
            y /= p_v.y;
            z /= p_v.z;
            return *this;
        }
        template<typename U> _FORCE_INLINE_ Vector3 operator/(const Vector3<U> &p_v) const {
            return Vector3(x / p_v.x, y / p_v.y, z / p_v.z);
        }

        template<typename U> _FORCE_INLINE_ Vector3 &operator*=(U p_scalar) {
            x *= p_scalar;
            y *= p_scalar;
            z *= p_scalar;
            return *this;
        }
        template<typename U> _FORCE_INLINE_ Vector3 operator*(U p_scalar) const {
            return Vector3(x * p_scalar, y * p_scalar, z * p_scalar);
        }
        template<typename U> _FORCE_INLINE_ Vector3 &operator/=(U p_scalar) {
            x /= p_scalar;
            y /= p_scalar;
            z /= p_scalar;
            return *this;
        }
        template<typename U> _FORCE_INLINE_ Vector3 operator/(U p_scalar) const {
            return Vector3(x / p_scalar, y / p_scalar, z / p_scalar);
        }

        template<typename U> _FORCE_INLINE_ bool operator>(U p_scalar) const { return *this > Vector3<U>(p_scalar); }
        template<typename U> _FORCE_INLINE_ bool operator<(U p_scalar) const { return *this < Vector3<U>(p_scalar); }
        template<typename U> _FORCE_INLINE_ bool operator>=(U p_scalar) const { return *this >= Vector3<U>(p_scalar); }
        template<typename U> _FORCE_INLINE_ bool operator<=(U p_scalar) const { return *this <= Vector3<U>(p_scalar); }
        template<typename U> _FORCE_INLINE_ bool operator==(U p_scalar) const { return *this == Vector3<U>(p_scalar); }
        template<typename U> _FORCE_INLINE_ bool operator!=(U p_scalar) const { return *this != Vector3<U>(p_scalar); }

        _FORCE_INLINE_ Vector3 operator-() const { return Vector3(-x, -y, -z); }
        _FORCE_INLINE_ Vector3 operator+() const { return *this; }

        _FORCE_INLINE_ bool operator==(const Vector3 &p_v) const { return x == p_v.x && y == p_v.y && z == p_v.z; }
        _FORCE_INLINE_ bool operator!=(const Vector3 &p_v) const { return x != p_v.x || y != p_v.y || z != p_v.z; }

        _FORCE_INLINE_ bool operator<=(const Vector3 &p_v) const { return x <= p_v.x && y <= p_v.y && z <= p_v.z; }
        _FORCE_INLINE_ bool operator>=(const Vector3 &p_v) const { return x >= p_v.x && y >= p_v.y && z >= p_v.z; }
        _FORCE_INLINE_ bool operator<(const Vector3 &p_v) const { return x < p_v.x && y < p_v.y && z < p_v.z; }
        _FORCE_INLINE_ bool operator>(const Vector3 &p_v) const { return x > p_v.x && y > p_v.y && z > p_v.z; }

    public:
        [[nodiscard]] glm::vec3 ToGLM() const noexcept {
            return glm::vec3(x, y, z);
        }
        static Unit Magnitude(Vector3 vec) {
            return sqrt(SR_POW(vec.x) + SR_POW(vec.y) + SR_POW(vec.z));
        }

        static T Dot(Vector3 lhs, Vector3 rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
        static Vector3 Cross(const Vector3 &p_a, const Vector3 &p_b) {
            Vector3 ret(
                    (p_a.y * p_b.z) - (p_a.z * p_b.y),
                    (p_a.z * p_b.x) - (p_a.x * p_b.z),
                    (p_a.x * p_b.y) - (p_a.y * p_b.x));
            return ret;
        }

        [[nodiscard]] Vector3 ConvertAxis(Helper::Graph::PipeLine from, Helper::Graph::PipeLine to) const {
            auto vector = *this;

            if (from != to)
                switch (from) {
                    case Graph::PipeLine::OpenGL:
                        break;
                    case Graph::PipeLine::Vulkan:
                        break;
                    case Graph::PipeLine::DirectX:
                        break;
                }

            return vector;
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

    typedef Vector3<Unit> FVector3;
    typedef Vector3<int32_t> IVector3;
    typedef Vector3<uint32_t> UVector3;

    inline static const FVector3 InfinityFV3 = FVector3 { UnitMAX, UnitMAX, UnitMAX };
    inline static const FVector3 CmpEpsilonFV3 = FVector3 {
            static_cast<Unit>(CMP_EPSILON),
            static_cast<Unit>(CMP_EPSILON),
            static_cast<Unit>(CMP_EPSILON),
    };
}

namespace std {
    template <class T> static inline void hash_vector3_combine(std::size_t & s, const T & v) {
        std::hash<T> h;
        s^= h(v) + 0x9e3779b9 + (s<< 6) + (s>> 2);
    }

    template<typename U> struct hash<Framework::Helper::Math::Vector3<U>> {
        size_t operator()(Framework::Helper::Math::Vector3<U> const& vec) const {
            std::size_t res = 0;
            hash_vector3_combine<U>(res, vec.x);
            hash_vector3_combine<U>(res, vec.y);
            hash_vector3_combine<U>(res, vec.z);
            return res;
        }
    };
}

#endif //GAMEENGINE_VECTOR3_H
