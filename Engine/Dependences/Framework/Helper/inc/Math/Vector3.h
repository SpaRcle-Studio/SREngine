//
// Created by kiper220 on 15.05.2020.
//

#ifndef EVOENGINE_VECTOR3_H
#define EVOENGINE_VECTOR3_H

#include <string>

namespace Framework::Helper::Math{
class Vector3 {
public:
    /**
     * \brief Default zero constructor
     */
    Vector3();
    /**
     * \brief Default data constructor
     */
    Vector3(float uX, float uY, float uZ);
    /**
     * \brief Default copy constructor
     */
    Vector3(const Vector3& vector3);

    /**
     * \brief Vector3 overload operator()(float, float, float)
     */
    Vector3& operator()(float uX, float uY, float uZ);
    /**
     * \brief Vector3 overload operator()(const Vector3&)
     */
    Vector3& operator()(const Vector3& vector3);
    /**
     * \brief Vector3 overload operator=(const Vector3&)
     */
    Vector3& operator =(const Vector3& vector3);

    /**
     * \brief Vector3 overload operator+=(const Vector3&)
     */
    Vector3& operator+=(const Vector3& vector3);
    /**
     * \brief Vector3 overload operator-=(const Vector3&)
     */
    Vector3& operator-=(const Vector3& vector3);
    /**
     * \brief Vector3 overload operator*=(const Vector3&)
     */
    void operator*=(float s);
    /**
     * \brief Vector3 overload operator%=(const Vector3&)
     */
    Vector3& operator %=(const Vector3& vector3);
    /**
     * \brief Vector3 overload operator/=(const Vector3&)
     */
    void operator /=(float s);

    /**
     * \brief Vector3 overload operator+(const Vector3&)
     * \return result of mathematical operation
     */
    Vector3 operator +(const Vector3& vector3);
    /**
     * \brief Vector3 overload operator-(const Vector3&)
     * \return result of mathematical operation
     */
    Vector3 operator -(const Vector3& vector3);
    /**
     * \brief Vector3 overload operator*(const Vector3&)
     * \return result of mathematical operation
     */
    float operator *(const Vector3& vector3) const;
    /**
     * \brief Vector3 overload operator*(float)
     * \return result of mathematical operation
     */
    Vector3 operator*(float s) const;
    /**
     * \brief Vector3 overload operator%(const Vector3&)
     * \return result of mathematical operation
     */
    Vector3 operator %(const Vector3& vector3);
    /**
     * \brief Vector3 overload operator/(float)
     * \return result of mathematical operation
     */
    Vector3 operator /(float s);

    /**
     * \brief Rotate vector about angle and axis(float, Vector3)(const)
     * \return result of mathematical operation
     */
    Vector3 RotateVectorAboutAngleAndAxis(float uAngle, Vector3 uAxis) const;
    /**
     * \brief Vector3 cross (const Vector3&)(const)
     * \return result of mathematical operation
     */
    Vector3 cross(const Vector3& vector3) const;
    /**
     * \brief Vector3 scale (const Vector3&)(const)
     * \return result of mathematical operation
     */
    Vector3 scale(const Vector3& vector3) const;
    /**
     * \brief Vector3 magnitude(const)
     * \return result of mathematical operation
     */
    float magnitude() const;
    /**
     * \brief Vector3 normalize(const)
     * \return result of mathematical operation
     */
    void normalize();

    /**
     * \brief Vector3 overload operator==(const Vector3&)(const)
     * \return bool
     */
    bool operator ==(const Vector3& vector3) const;
    /**
     * \brief Vector3 overload operator!=(const Vector3&)(const)
     * \return bool
     */
    bool operator !=(const Vector3& vector3) const;

    /**
     * \brief Overload operator String(const)
     */
    operator std::string();

    /**
     * \brief Default destructor
     */
    ~Vector3();

    /**
     * \brief Vector2 data
     */
    float x, y, z;
};
}


#endif //EVOENGINE_VECTOR3_H
