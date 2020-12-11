//
// Created by kiper220 on 16.05.2020.
//

#include <Math/Vector3.h>

#ifndef EVOENGINE_Matrix3_H
#define EVOENGINE_Matrix3_H

namespace Framework::Helper::Math {
class Matrix3x3 {
public:
    /**
     * \brief Default zero constructor
     */
    Matrix3x3();
    /**
     * \brief Default set constructor
     */
    Matrix3x3(float m0, float m3, float m6, float m1, float m4, float m7, float m2, float m5, float m8);
    /**
     * \brief Default copy constructor
     */
    Matrix3x3(const Matrix3x3& matrix3x3);

    /**
     * \brief Default copy operator
     * \return this class reference
     */
    Matrix3x3& operator=(const Matrix3x3& matrix3x3);

    /**
     * \brief Matrix overload operator+(const Matrix3x3&)
     * \arg Matrix3x3 - target;
     * \return result of a mathematical operation
     */
    Matrix3x3 operator+(const Matrix3x3& matrix3x3) const;
    /**
     * \brief Matrix overload operator*(const Matrix3x&)
     * \arg Matrix3 - target;
     * \return result of a mathematical operation
     */
    Matrix3x3 operator*(const Matrix3x3& matrix3x3) const;
    /**
     * \brief Matrix overload operator*(float)
     * \arg Matrix3 - target;
     * \return result of a mathematical operation
     */
    Matrix3x3 operator*(float scalar) const;
    /**
     * \brief Matrix overload operator+(const Vector3&)
     * \arg Matrix3 - target;
     * \return result of a mathematical operation(Vector3)
     */
    Vector3 operator*(const Vector3& vector3) const;

    /**
     * \brief Matrix overload operator+=(const Matrix3&)
     * \return this class reference
     */
    void operator+=(const Matrix3x3& matrix3X3);
    /**
     * \brief Matrix overload operator*=(const Matrix3x3&)
     * \return this class reference
     */
    void operator*=(const Matrix3x3& matrix3X3);
    /**
     * \brief Matrix overload operator*=(float)
     * \return this class reference
     */
    void operator*=(float scalar);

    /**
     * \brief Set matrix as identity matrix function
     */
    void setMatrixAsIdentityMatrix();
    /**
     * \brief Set matrix as inverse of given matrix function
     */
    void setMatrixAsInverseOfGivenMatrix(const Matrix3x3& matrix3x3);
    /**
     * \brief Get inverse of matrix(const)
     */
    Matrix3x3 getInverseOfMatrix() const;
    /**
     * \brief Get transpose of matrix(const)
     */
    Matrix3x3 getTransposeOfMatrix() const;
    /**
     * \brief Set matrix as transpose of given matrix(const Matrix&)
     */
    void setMatrixAsTransposeOfGivenMatrix(const Matrix3x3& matrix3x3);
    /**
     * \brief Transform vector by matrix(const Vector3&)(const)
     */
    Vector3 transformVectorByMatrix(const Vector3& vector3) const;
    /**
     * \brief Invert matrix()
     */
    void invertMatrix();

    /**
     * \brief Overload operator String(const)
     */
    operator std::string() const;

    /**
     * \brief Standart destructor
     */
    ~Matrix3x3();

    /**
     * \brief Matrix Data
     */
    float matrixData[9] = {0.0};
};
}


#endif //EVOENGINE_Matrix3_H
