//
// Created by kiper220 on 16.05.2020.
//

#include <Math/Matrix3x3.h>
#include <Math/Vector3.h>
#include <string>

#include <Math/Mathematics.h>

using namespace Framework::Helper::Math;

Matrix3x3::Matrix3x3(){
    for(float& a: this->matrixData)
        a = 0.0;

    this->matrixData[0] = this->matrixData[4] = this->matrixData[8]=1.0f;
}
Matrix3x3::Matrix3x3(float m0, float m3, float m6, float m1, float m4, float m7, float m2, float m5, float m8) {
    matrixData[0] = m0;
    matrixData[3] = m3;
    matrixData[6] = m6;

    matrixData[1] = m1;
    matrixData[4] = m4;
    matrixData[7] = m7;

    matrixData[2] = m2;
    matrixData[5] = m5;
    matrixData[8] = m8;
}

Matrix3x3::Matrix3x3(const Matrix3x3& matrix3X3)  {
    matrixData[0] = matrix3X3.matrixData[0];
    matrixData[3] = matrix3X3.matrixData[3];
    matrixData[6] = matrix3X3.matrixData[6];

    matrixData[1] = matrix3X3.matrixData[1];
    matrixData[4] = matrix3X3.matrixData[4];
    matrixData[7] = matrix3X3.matrixData[7];

    matrixData[2] = matrix3X3.matrixData[2];
    matrixData[5] = matrix3X3.matrixData[5];
    matrixData[8] = matrix3X3.matrixData[8];
}

Matrix3x3& Matrix3x3::operator=(const Matrix3x3& matrix3X3) {
    matrixData[0] = matrix3X3.matrixData[0];
    matrixData[3] = matrix3X3.matrixData[3];
    matrixData[6] = matrix3X3.matrixData[6];

    matrixData[1] = matrix3X3.matrixData[1];
    matrixData[4] = matrix3X3.matrixData[4];
    matrixData[7] = matrix3X3.matrixData[7];

    matrixData[2] = matrix3X3.matrixData[2];
    matrixData[5] = matrix3X3.matrixData[5];
    matrixData[8] = matrix3X3.matrixData[8];

    return *this;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& matrix3X3) const  {
    Matrix3x3 matrix3X32;
    matrix3X32 = *this;
    matrix3X32.matrixData[0] += matrix3X3.matrixData[0];
    matrix3X32.matrixData[1] += matrix3X3.matrixData[1];
    matrix3X32.matrixData[2] += matrix3X3.matrixData[2];
    matrix3X32.matrixData[3] += matrix3X3.matrixData[3];
    matrix3X32.matrixData[4] += matrix3X3.matrixData[4];
    matrix3X32.matrixData[5] += matrix3X3.matrixData[5];
    matrix3X32.matrixData[6] += matrix3X3.matrixData[6];
    matrix3X32.matrixData[7] += matrix3X3.matrixData[7];
    matrix3X32.matrixData[8] += matrix3X3.matrixData[8];

    return matrix3X3;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& matrix3X3) const  {
    return Matrix3x3(
        this->matrixData[0] * matrix3X3.matrixData[0] + this->matrixData[3] * matrix3X3.matrixData[1] + this->matrixData[6] * matrix3X3.matrixData[2],
        this->matrixData[0] * matrix3X3.matrixData[3] + this->matrixData[3] * matrix3X3.matrixData[4] + this->matrixData[6] * matrix3X3.matrixData[5],
        this->matrixData[0] * matrix3X3.matrixData[6] + this->matrixData[3] * matrix3X3.matrixData[7] + this->matrixData[6] * matrix3X3.matrixData[8],

        this->matrixData[1] * matrix3X3.matrixData[0] + this->matrixData[4] * matrix3X3.matrixData[1] + this->matrixData[7] * matrix3X3.matrixData[2],
        this->matrixData[1] * matrix3X3.matrixData[3] + this->matrixData[4] * matrix3X3.matrixData[4] + this->matrixData[7] * matrix3X3.matrixData[5],
        this->matrixData[1] * matrix3X3.matrixData[6] + this->matrixData[4] * matrix3X3.matrixData[7] + this->matrixData[7] * matrix3X3.matrixData[8],

        this->matrixData[2] * matrix3X3.matrixData[0] + this->matrixData[5] * matrix3X3.matrixData[1] + this->matrixData[8] * matrix3X3.matrixData[2],
        this->matrixData[2] * matrix3X3.matrixData[3] + this->matrixData[5] * matrix3X3.matrixData[4] + this->matrixData[8] * matrix3X3.matrixData[5],
        this->matrixData[2] * matrix3X3.matrixData[6] + this->matrixData[5] * matrix3X3.matrixData[7] + this->matrixData[8] * matrix3X3.matrixData[8]
    );
}

Matrix3x3 Matrix3x3::operator*(float scalar) const  {
    Matrix3x3 matrix3X3;
    matrix3X3 = *this;
    matrix3X3.matrixData[0] *= scalar;
    matrix3X3.matrixData[1] *= scalar;
    matrix3X3.matrixData[2] *= scalar;
    matrix3X3.matrixData[3] *= scalar;
    matrix3X3.matrixData[4] *= scalar;
    matrix3X3.matrixData[5] *= scalar;
    matrix3X3.matrixData[6] *= scalar;
    matrix3X3.matrixData[7] *= scalar;
    matrix3X3.matrixData[8] *= scalar;

    return matrix3X3;
}

Vector3 Matrix3x3::operator*(const Vector3& vector3) const {
    return Vector3(this->matrixData[0] * vector3.x + this->matrixData[3] * vector3.y + this->matrixData[6] * vector3.z,
    this->matrixData[1] * vector3.x + this->matrixData[4] * vector3.y + this->matrixData[7] * vector3.z,
    this->matrixData[2] * vector3.x + this->matrixData[5] * vector3.y + this->matrixData[8] * vector3.z);
}

void Matrix3x3::operator+=(const Matrix3x3& matrix3X3) {
    this->matrixData[0] += matrix3X3.matrixData[0];
    this->matrixData[1] += matrix3X3.matrixData[1];
    this->matrixData[2] += matrix3X3.matrixData[2];
    this->matrixData[3] += matrix3X3.matrixData[3];
    this->matrixData[4] += matrix3X3.matrixData[4];
    this->matrixData[5] += matrix3X3.matrixData[5];
    this->matrixData[6] += matrix3X3.matrixData[6];
    this->matrixData[7] += matrix3X3.matrixData[7];
    this->matrixData[8] += matrix3X3.matrixData[8];
}

void Matrix3x3::operator*=(const Matrix3x3& matrix3X3) {
    float t1;
    float t2;
    float t3;

    t1 = this->matrixData[0] * matrix3X3.matrixData[0] + this->matrixData[3] * matrix3X3.matrixData[1] + this->matrixData[6] * matrix3X3.matrixData[2];
    t2 = this->matrixData[0] * matrix3X3.matrixData[3] + this->matrixData[3] * matrix3X3.matrixData[4] + this->matrixData[6] * matrix3X3.matrixData[5];
    t3 = this->matrixData[0] * matrix3X3.matrixData[6] + this->matrixData[3] * matrix3X3.matrixData[7] + this->matrixData[6] * matrix3X3.matrixData[8];

    this->matrixData[0]=t1;
    this->matrixData[3]=t2;
    this->matrixData[6]=t3;

    t1 = this->matrixData[1] * matrix3X3.matrixData[0] + this->matrixData[4] * matrix3X3.matrixData[1] + this->matrixData[7] * matrix3X3.matrixData[2];
    t2 = this->matrixData[1] * matrix3X3.matrixData[3] + this->matrixData[4] * matrix3X3.matrixData[4] + this->matrixData[7] * matrix3X3.matrixData[5];
    t3 = this->matrixData[1] * matrix3X3.matrixData[6] + this->matrixData[4] * matrix3X3.matrixData[7] + this->matrixData[7] * matrix3X3.matrixData[8];

    this->matrixData[1]=t1;
    this->matrixData[4]=t2;
    this->matrixData[7]=t3;


    t1 = this->matrixData[2] * matrix3X3.matrixData[0] + this->matrixData[5] * matrix3X3.matrixData[1] + this->matrixData[8] * matrix3X3.matrixData[2];
    t2 = this->matrixData[2] * matrix3X3.matrixData[3] + this->matrixData[5] * matrix3X3.matrixData[4] + this->matrixData[8] * matrix3X3.matrixData[5];
    t3 = this->matrixData[2] * matrix3X3.matrixData[6] + this->matrixData[5] * matrix3X3.matrixData[7] + this->matrixData[8] * matrix3X3.matrixData[8];

    this->matrixData[2]=t1;
    this->matrixData[5]=t2;
    this->matrixData[8]=t3;
}

void Matrix3x3::operator*=(float scalar) {
    this->matrixData[0] *= scalar;
    this->matrixData[1] *= scalar;
    this->matrixData[2] *= scalar;
    this->matrixData[3] *= scalar;
    this->matrixData[4] *= scalar;
    this->matrixData[5] *= scalar;
    this->matrixData[6] *= scalar;
    this->matrixData[7] *= scalar;
    this->matrixData[8] *= scalar;
}

void Matrix3x3::setMatrixAsIdentityMatrix() {
    for (float &i : this->matrixData)
        i=0.0f;

    this->matrixData[0] = this->matrixData[4] = this->matrixData[8]=1.0f;
}

void Matrix3x3::setMatrixAsInverseOfGivenMatrix(const Matrix3x3& matrix3X3) {
    float t1 = matrix3X3.matrixData[0] * matrix3X3.matrixData[4];
    float t2 = matrix3X3.matrixData[0] * matrix3X3.matrixData[7];
    float t3 = matrix3X3.matrixData[3] * matrix3X3.matrixData[1];
    float t4 = matrix3X3.matrixData[6] * matrix3X3.matrixData[1];
    float t5 = matrix3X3.matrixData[3] * matrix3X3.matrixData[2];
    float t6 = matrix3X3.matrixData[6] * matrix3X3.matrixData[2];

    //calculate the determinant

    float det=(
        t1 * matrix3X3.matrixData[8] - t2 * matrix3X3.matrixData[5] - t3 * matrix3X3.matrixData[8] +
        t4 * matrix3X3.matrixData[5] + t5 * matrix3X3.matrixData[7] - t6 * matrix3X3.matrixData[4]);

    //make sure the det is non-zero
    if (det==0.0) return;

    float invd = 1.0f / det;

    float m0=(
        matrix3X3.matrixData[4] * matrix3X3.matrixData[8] -
        matrix3X3.matrixData[7] * matrix3X3.matrixData[5]) * invd;

    float m3=-(
        matrix3X3.matrixData[3] * matrix3X3.matrixData[8] -
        matrix3X3.matrixData[6] * matrix3X3.matrixData[5]) * invd;

    float m6=(
        matrix3X3.matrixData[3] * matrix3X3.matrixData[7] -
        matrix3X3.matrixData[6] * matrix3X3.matrixData[4]) * invd;

    float m1=-(
        matrix3X3.matrixData[1] * matrix3X3.matrixData[8] -
        matrix3X3.matrixData[7] * matrix3X3.matrixData[2]) * invd;

    float m4=(matrix3X3.matrixData[0] * matrix3X3.matrixData[8] - t6) * invd;

    float m7=-(t2 - t4) * invd;

    float m2=(matrix3X3.matrixData[1] * matrix3X3.matrixData[5] - matrix3X3.matrixData[4] * matrix3X3.matrixData[2]) * invd;

    float m5=-(matrix3X3.matrixData[0] * matrix3X3.matrixData[5] - t5) * invd;

    float m8=(t1 - t3) * invd;

    this->matrixData[0] = m0;
    this->matrixData[3] = m3;
    this->matrixData[6] = m6;

    this->matrixData[1] = m1;
    this->matrixData[4] = m4;
    this->matrixData[7] = m7;

    this->matrixData[2] = m2;
    this->matrixData[5] = m5;
    this->matrixData[8] = m8;
}

Matrix3x3 Matrix3x3::getInverseOfMatrix() const {
    Matrix3x3 returnValue;
    returnValue.setMatrixAsInverseOfGivenMatrix(*this);
    return returnValue;
}

void Matrix3x3::setMatrixAsTransposeOfGivenMatrix(const Matrix3x3& matrix3X3) {
    this->matrixData[0] = matrix3X3.matrixData[0];
    this->matrixData[3] = matrix3X3.matrixData[1];
    this->matrixData[6] = matrix3X3.matrixData[2];

    this->matrixData[1] = matrix3X3.matrixData[3];
    this->matrixData[4] = matrix3X3.matrixData[4];
    this->matrixData[7] = matrix3X3.matrixData[5];

    this->matrixData[2] = matrix3X3.matrixData[6];
    this->matrixData[5] = matrix3X3.matrixData[7];
    this->matrixData[8] = matrix3X3.matrixData[8];
}

Matrix3x3 Matrix3x3::getTransposeOfMatrix() const {
    Matrix3x3 returnValue;
    returnValue.setMatrixAsTransposeOfGivenMatrix(*this);
    return returnValue;
}

void Matrix3x3::invertMatrix() {
    setMatrixAsInverseOfGivenMatrix(*this);
}

Vector3 Matrix3x3::transformVectorByMatrix(const Vector3& vector3) const {
    return (*this) * vector3;
}

Matrix3x3::operator std::string() const {
    return  std::string("[") + std::to_string(matrixData[0]) + "," + std::to_string(matrixData[3]) +
    "," + std::to_string(matrixData[6]) + ",\n " +
    std::to_string(matrixData[1]) + "," + std::to_string(matrixData[4]) +
    "," + std::to_string(matrixData[7]) + ",\n " +
    std::to_string(matrixData[2]) + "," + std::to_string(matrixData[5]) +
    "," + std::to_string(matrixData[8]) + "]";
}

Matrix3x3::~Matrix3x3() = default;
