//
// Created by kiper220 on 16.05.2020.
//


#ifndef EVOENGINE_VECTOR2_H
#define EVOENGINE_VECTOR2_H

#include <string>

namespace Framework::Helper::Math {
class Vector2 {
public:
    /**
     * \brief Default zero constructor
     */
    Vector2();

    /**
     * \brief Default data constructor
     */
    Vector2(float uX, float uY);

    /**
     * \brief Default copy constructor
     */
    Vector2(const Vector2 &vector2);

    /**
     * \brief Vector2 overload operator()(float, float)
     */
    Vector2 &operator()(float uX, float uY);

    /**
     * \brief Vector2 overload operator()(const Vector2&)
     */
    Vector2 &operator()(const Vector2 &vector2);

    /**
     * \brief Vector2 overload operator=(const Vector2&)
     */
    Vector2 &operator=(const Vector2 &vector2);

    /**
     * \brief Vector2 overload operator+=(const Vector2&)
     */
    Vector2 &operator+=(const Vector2 &vector2);

    /**
     * \brief Vector2 overload operator-=(const Vector2&)
     */
    Vector2 &operator-=(const Vector2 &vector2);

    /**
     * \brief Vector2 overload operator*=(float)
     */
    void operator*=(float s);

    /**
     * \brief Vector2 overload operator/=(float)
     */
    void operator/=(float s);

    /**
     * \brief Vector2 overload operator+(const Vector2&)
     * \return result of mathematical operation
     */
    Vector2 operator+(const Vector2 &vector2);

    /**
     * \brief Vector2 overload operator-(const Vector2&)
     * \return result of mathematical operation
     */
    Vector2 operator-(const Vector2 &vector2);

    /**
     * \brief Vector2 overload operator*(const Vector2&)
     * \return result of mathematical operation
     */
    float operator*(const Vector2 &vector2) const;

    /**
     * \brief Vector2 overload operator*(float)
     * \return result of mathematical operation
     */
    Vector2 operator*(float s) const;

    /**
     * \brief Vector2 overload operator*(const Vector2&)
     * \return result of mathematical operation
     */
    float operator%(const Vector2 &vector2);

    /**
     * \brief Vector2 overload operator/(float)
     * \return result of mathematical operation
     */
    Vector2 operator/(float s);

    /**
     * \brief Rotate vector about angle(float)(const)
     * \return result of mathematical operation
     */
    Vector2 RotateVectorAboutAngle(float uAngle) const;

    /**
     * \brief Vector2 cross (const Vector2&)(const)
     * \return result of mathematical operation
     */
    float cross(const Vector2 &vector2) const;

    /**
     * \brief Vector2 magnitude (const)
     * \return result of mathematical operation
     */
    float magnitude() const;

    /**
     * \brief Vector2 normalize
     * \return result of mathematical operation
     */
    void normalize();

    /**
     * \brief Vector2 overload operator==(const Vector2&)(const)
     * \return bool
     */
    bool operator==(const Vector2 &vector2) const;

    /**
     * \brief Vector2 overload operator==(const Vector2&)(const)
     * \return bool
     */
    bool operator!=(const Vector2 &vector2) const;

    /**
     * \brief Overload operator String(const)
     */
    operator std::string();

    /**
     * \brief Default destructor
     */
    ~Vector2();

    /**
     * \brief Vector2 data
     */
    float x, y;
};
}


#endif //EVOENGINE_VECTOR2_H
